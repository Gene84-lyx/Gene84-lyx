#include "mainwidgit.h"
#include <QApplication>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <QTextCodec>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>
#include <QString>
#include <QStringList>
#include <pthread.h>
#include <QDebug>

struct mv_fd{
    Mainwidgit *w_copy;
    int fd_copy;
};

void* write_order(void *arg);
void* read_order_return(void *arg);
QString time_format(char *buf, int *time);

int main(int argc, char *argv[])
{
    /*创建命名管道，用来控制命令的输入*/
    mkfifo("MUSIC",0777);

    /*创建无名管道，用来接收mplayer的返回值*/
    int fd[2];
    pipe(fd);//fd[0]是读通道，fd[1]是写通道

    /*创建进程，一个用来控制播放音乐等，一个用来控制界面*/
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
    }else if(pid==0)//子进程用来控制播放音乐
    {
        dup2(fd[1],1);//重定向标准输出到fd[1]中
        execlp("mplayer","mplayer","-slave","-quiet","-idle","-input","file=./MUSIC",NULL);
    }else//父进程用来控制界面的显示
    {
        /*解决汉字乱码问题*/
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");//UTF-8
        QTextCodec::setCodecForLocale(codec);
        /*这两句在qt5中不能有，但在其他版本可能需要*/
        QTextCodec::setCodecForTr(codec);
        QTextCodec::setCodecForCStrings(codec);

        /*主界面*/
        QApplication a(argc, argv);
        Mainwidgit w;
        w.show();
        w.kill_pid=pid;//将子进程的进程号传入mainwidgit

        struct mv_fd arg;
        arg.w_copy=&w;
        arg.fd_copy=fd[0];

        pthread_t tid_w,tid_r;
        pthread_create(&tid_w,NULL,write_order,(void*)&arg);
        pthread_create(&tid_r,NULL,read_order_return,(void*)&arg);

        return a.exec();
    }
}

void* write_order(void *arg)
{
    int fd_music;
    mkfifo("MUSIC",0777);
    fd_music=open("MUSIC",O_WRONLY);

    while(1)//无法用同步锁进行控制，因为无法保证read是否能读到数据
    {
        sem_wait(((struct mv_fd*)arg)->w_copy->sem_write);
        write(fd_music,"get_time_pos\n",strlen("get_time_pos\n"));
        usleep(100000);
        write(fd_music,"get_time_length\n",strlen("get_time_length\n"));
        usleep(100000);
        write(fd_music,"get_percent_pos\n",strlen("get_percent_pos\n"));
        usleep(100000);
        sem_post(((struct mv_fd*)arg)->w_copy->sem_write); 
        usleep(200000);
    }
    close(fd_music);
}

void* read_order_return(void *arg)
{
    Mainwidgit *wc=((struct mv_fd*)arg)->w_copy;

    ((struct mv_fd*)arg)->w_copy->label_time->setText("00:00/00:00");
    QString current_time="00:00";
    QString all_time="00:00";
    while(1)
    {
        char buf[128]={0};
        read(((struct mv_fd*)arg)->fd_copy,buf,sizeof(buf));
        if(strncmp(buf,"ANS_TIME_POSITION",strlen("ANS_TIME_POSITION"))==0)//这是对比当前时间返回的标志位
        {
            int time_current=0;
            current_time=time_format(buf,&time_current);//这个函数是将时间转换成00：00格式
            ((struct mv_fd*)arg)->w_copy->current_time_int=time_current;//将当前时间赋值给current_time_int
            if(time_current>wc->judge_time[wc->row_lrc]&&wc->flag_press_slider==0)
            {
                wc->listwidget_button.at(wc->row_lrc+1)->setBackground(QColor(0,0,0));
                wc->listwidget_button.at(wc->row_lrc+1)->setTextColor(QColor(255,255,255));
                wc->row_lrc++;
                wc->listwidget_button.at(wc->row_lrc+1)->setBackground(QColor(240,120,70));
                wc->listwidget_button.at(wc->row_lrc+1)->setTextColor(QColor(255,255,255));
                wc->lrc_word_list->scrollToItem(wc->listwidget_button.at(wc->row_lrc+1),QAbstractItemView::PositionAtCenter);
            }
        }
        if(strncmp(buf,"ANS_LENGTH",strlen("ANS_LENGTH"))==0)//这是对比时间总的长度的标志位
        {
            int time_all=0;
            all_time=time_format(buf,&time_all);//这个函数是将时间转换成00：00格式
            if(time_all!=0&&((struct mv_fd*)arg)->w_copy->all_time_int!=time_all)
            {
                ((struct mv_fd*)arg)->w_copy->slider_music->setMaximum((int)(time_all/100)-2);
                ((struct mv_fd*)arg)->w_copy->all_time_int=time_all;//将当前时间赋值给all_time_int
            }
            if(((struct mv_fd*)arg)->w_copy->flag_press_slider==0)
            {
                ((struct mv_fd*)arg)->w_copy->label_time->setText(current_time+"/"+all_time);//这个是先将两个时间拼接起来，之后再输出到qt界面上
            }
        }
        if(strncmp(buf,"ANS_PERCENT_POSITION",strlen("ANS_PERCENT_POSITION"))==0)
        {
            QString flag_percent=QString::fromLocal8Bit(buf);
            QStringList percent=flag_percent.split("=");
            if(((struct mv_fd*)arg)->w_copy->flag_press_slider==0)
            {
                int simple=((struct mv_fd*)arg)->w_copy->all_time_int;
                ((struct mv_fd*)arg)->w_copy->slider_music->setValue((int)(percent[1].toInt()*(simple)/10000));//设置进度条
            }
        }
    }
}

QString time_format(char* buf,int *time)
{
    QString flag_time=QString::fromLocal8Bit(buf);//将读取到的数组转成QString中
    QStringList s_ms=flag_time.split("=");//切割，将等号前面的内容舍弃

    (*time)=(int)((s_ms[1].toDouble())*100);

    QStringList only_s=s_ms[1].split(".");//切割，将百毫秒舍弃
    int timenum=only_s[0].toInt();//字符串秒转换成数字秒
    int minnum=timenum/60;//取分钟数
    int secnum=timenum%60;//取秒钟数
    QString minstr=QString::number(minnum);//将分钟转成QString类型
    QString secstr=QString::number(secnum);//将秒钟转成QString类型

    if(timenum<10)//此时的时间小于10秒的情况
    {
        only_s[0]="00:0"+only_s[0];
    }else if(timenum<60)//此时的时间大于10秒小于60秒的情况
    {
        only_s[0]="00:"+only_s[0];
    }else if(minnum<10)//此时时间大于60秒的情况
    {
        if(secnum<10)
        {
            only_s[0]="0"+minstr+":0"+secstr;
        }else
        {
            only_s[0]="0"+minstr+":"+secstr;
        }
    }else if(minnum>=10)
    {
        if(secnum<10)
        {
            only_s[0]=minstr+":0"+secstr;
        }else
        {
            only_s[0]=minstr+":"+secstr;
        }
    }
    return only_s[0];
}
