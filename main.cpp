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
#include <string.h>
#include <QString>
#include <QStringList>
#include <pthread.h>

struct mv_fd{
    Mainwidgit *w_copy;
    int fd_copy;
};

void* write_order(void *arg);
void* read_order_return(void *arg);
QString time_format(QString time);

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

    while(1)
    {
        write(fd_music,"get_time_pos\n",strlen("get_time_pos\n"));
        usleep(100000);
    }
    close(fd_music);
}

void* read_order_return(void *arg)
{
    ((struct mv_fd*)arg)->w_copy->label_time->setText("00:00");
    while(1)
    {
        char buf[128]={0};
        read(((struct mv_fd*)arg)->fd_copy,buf,sizeof(buf));
        if(strncmp(buf,"ANS_TIME_POSITION",strlen("ANS_TIME_POSITION"))==0)
        {
            QString flag_time=QString::fromLocal8Bit(buf);
            QStringList s_ms=flag_time.split("=");
            QStringList only_s=s_ms[1].split(".");
            only_s[0]=time_format(only_s[0]);
            ((struct mv_fd*)arg)->w_copy->label_time->setText(only_s[0]);
        }
    }
}

QString time_format(QString time)
{
    int timenum=time.toInt();
    int minnum=timenum/60;
    int secnum=timenum%60;
    QString minstr=QString::number(minnum);
    QString secstr=QString::number(secnum);

    if(timenum<10)
    {
        time="00:0"+time;
    }else if(timenum<60)
    {
        time="00:"+time;
    }else if(minnum<10)
    {
        if(secnum<10)
        {
            time="0"+minstr+":0"+secstr;
        }else
        {
            time="0"+minstr+":"+secstr;
        }
    }else if(minnum>=10)
    {
        if(secnum<10)
        {
            time=minstr+":0"+secstr;
        }else
        {
            time=minstr+":"+secstr;
        }
    }
    return time;
}
