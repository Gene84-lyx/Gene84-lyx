#include "mainwidgit.h"
#include "ui_mainwidgit.h"
#include "mlabel.h"

#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <QDebug>
#include <signal.h>
#include <QDebug>
#include <QList>
#include <QAbstractButton>
#include <QToolButton>
#include <QPushButton>
#include <string.h>
#include <QByteArray>
#include <QTextCodec>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>

Mainwidgit::Mainwidgit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidgit)
{
    ui->setupUi(this);

    /*参数的初始化*/
    this->play_pause=2;//控制初始时点击播放按钮音乐的播放
    this->music_currentrow=0;//设置当前歌曲在列表中为第一首
    this->fd=open("MUSIC",O_WRONLY);//以只读的方式打开命名管道

    /*定义一个信号量，用来发送暂停信息的时候阻塞时间获取*/
    this->sem_write=sem_open("mysem",O_RDWR|O_CREAT,0666,1);
    sem_init(this->sem_write,0,0);

    /*设置主界面的一些属性*/
    this->setMinimumSize(1280,720);

    /*设置栅格布局区*/
    this->layout_widget=new QGridLayout();//整个界面的布局
    this->layout_change=new QGridLayout();//底部区域的布局（播放、上一曲、下一曲）

/***********************************************************************************/
    /*设置暂停切歌基础框*/
    this->label_change=new Mlabel(this);
    this->label_change->setFixedSize(400,70);
    layout_widget->addWidget(this->label_change,2,0);

    /*设置（播放暂停）按钮*/
    this->label_pause=new Mlabel(this->label_change);
    this->label_pause->setFixedSize(50,50);
    this->label_pause->setStyleSheet("border-radius:25px");//圆形的命令（冒号后面的是半径）
    pixmap.load(":/image/button_style/play1.png");//载入初始图片
    this->label_pause->setPixmap(pixmap);
    this->label_pause->setScaledContents(true);//图片自适应大小
    this->layout_change->addWidget(this->label_pause,0,1);//栅格布局

    /*切换上一首歌按钮*/
    this->label_back=new Mlabel(this->label_change);
    this->label_back->setFixedSize(50,50);
    this->label_back->setStyleSheet("border-radius:25px");
    pixmap.load(":/image/button_style/back1.png");
    this->label_back->setPixmap(pixmap);
    this->label_back->setScaledContents(true);
    this->layout_change->addWidget(this->label_back,0,0);

    /*切换下一首歌按钮*/
    this->label_front=new Mlabel(this->label_change);
    this->label_front->setFixedSize(50,50);
    this->label_front->setStyleSheet("border-radius:25px");
    pixmap.load(":/image/button_style/front1.png");
    this->label_front->setPixmap(pixmap);
    this->label_front->setScaledContents(true);
    this->layout_change->addWidget(this->label_front,0,2);

    /*添加一个此时歌曲播放时间的框*/
    this->label_time=new QLabel(this->label_change);
    this->label_time->setFixedSize(200,50);
    this->ft.setPointSize(24);
    this->label_time->setFont(ft);
    this->layout_change->addWidget(this->label_time,0,3);

/***********************************************************************************/
    /*设置歌曲组列表*/
    this->toolbox_list=new QToolBox(this);
    this->toolbox_list->setStyleSheet("background-color:white;");//多个属性用QToolBox{background-color:white;}
    this->ft.setPointSize(24);
    this->toolbox_list->setFont(ft);//只有在父控件(QToolBox)中改变字体才能改变子控件(QToolBoxButton)中的字体大小，子控件自己无法该
    this->layout_widget->addWidget(this->toolbox_list,0,0);

    /*本地歌曲列表*/
    this->list_bendi=new QListWidget();
    this->list_bendi->setStyleSheet("background-color:white;");

    this->music_list();//将歌曲读入QStringlist中
    for(int i=0;i<this->music_num;i++)//循环将歌曲写入到界面列表中
    {
        this->list_bendi->addItem(this->music_all_name[i]);
    }

    this->ft.setPointSize(24);
    this->list_bendi->setFont(ft);
    this->list_bendi->setCurrentRow(0);//设置初始打开时列表是第一个
    this->toolbox_list->addItem(this->list_bendi,tr("本地歌曲"));

    /*默认歌曲列表*/
    this->list_moren=new QListWidget();
    this->list_moren->setStyleSheet("background-color:white;");

    this->list_moren->addItem("本地列表");
    this->list_moren->addItem("本地列表");
    this->ft.setPointSize(24);
    this->list_moren->setFont(ft);

    this->toolbox_list->addItem(this->list_moren,tr("默认歌曲"));

    /*加一个空白的QToolboxButton,用来实现自开自关*/
    this->list_last=new QListWidget();
    this->list_last->setStyleSheet("border:0px solid white;");//设置列表没有边框

    this->toolbox_list->addItem(this->list_last,tr(""));
    this->toolbox_list->setItemEnabled(2,false);//禁止点击使用

    /*获取toolbox下Qtoolboxbutton的指针,并存放在Qlist类toolbox_button中*/
    this->toolbox_button=this->toolbox_list->findChildren<QAbstractButton*>();

    /*控制toolbox里的子控件的属性*/
    this->toolbox_button.at(0)->setMinimumHeight(60);//设置最小的大小
    this->toolbox_button.at(1)->setMinimumHeight(60);
    this->toolbox_button.at(2)->setMaximumHeight(0);//设置最大高度为0也可以隐形
    this->toolbox_button.at(2)->setStyleSheet("background:transparent;");//设置

    /*设置初始为2toolbutton*/
    this->toolbox_list->setCurrentIndex(2);//只需要功能不需要显示的

    /*启用栅格布局*/
    this->setLayout(layout_widget);
    this->label_change->setLayout(this->layout_change);

/*************************************************************************/
    /*控制的是播放按钮和切歌按钮*/
    connect(this->label_pause,SIGNAL(label_signal(int)),this,SLOT(label_func(int)));
    connect(this->label_back,SIGNAL(label_signal(int)),this,SLOT(label_func(int)));
    connect(this->label_front,SIGNAL(label_signal(int)),this,SLOT(label_func(int)));

    /*控制的是歌曲列表框的变化*/
    connect(this->toolbox_button.at(0),SIGNAL(clicked()),this,SLOT(close_list()));
    connect(this->toolbox_button.at(1),SIGNAL(clicked()),this,SLOT(close_list()));

    /*控制listwidget获得歌曲信息，从而播放歌曲*/
    connect(this->list_bendi,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(play_list_music()));
}

Mainwidgit::~Mainwidgit()
{
    delete ui;
}
/******************************事件函数**********************************/
void Mainwidgit::closeEvent(QCloseEvent *e)
{
    kill(this->kill_pid,2);
}

/******************************普通函数**********************************/
void Mainwidgit::music_list()
{
    DIR *dir=opendir("/home/lyx/Qt5.8.0/1_object/1_program/Mplayer/song");
    QString save_all_name;
    QStringList cut_name;
    struct dirent *dire;
    this->music_num=0;
    while(1)
    {
        dire=readdir(dir);
        if(dire==NULL)
        {
            break;
        }else if(dire->d_type==DT_REG)
        {
            save_all_name=QString::fromLocal8Bit(dire->d_name);
            cut_name=save_all_name.split(".");
            if(cut_name[1]=="mp3")
            {
                this->music_num++;
                this->music_all_name.append(cut_name[0]);
            }
        }
    }
    putchar(10);
    closedir(dir);
}

void Mainwidgit::play_music(int row)
{
    QString path="loadfile \"/home/lyx/Qt5.8.0/1_object/1_program/Mplayer/song/";//路径
    QString postfix=".mp3\"\n";//文件类型名
    QString path_add_name=path+this->music_all_name[row]+postfix;//将路径和文件名相加起来
    QByteArray ba = path_add_name.toUtf8();//转换格式为ubuntu识别的UTF-8格式（中文不乱码）
    mkfifo("MUSIC",0777);//创建命名管道（即使存在也没事）
    write(this->fd,ba.data(),strlen(ba.data()));//向终端写入命令，操控mplayer
}

void Mainwidgit::label_pause_func(int mod)
{
    QString pic_path,pic_path1;
    if(play_pause>0)
    {
        pic_path=":/image/button_style/play.png";
        pic_path1=":/image/button_style/play1.png";
    }else
    {
        pic_path=":/image/button_style/pause.png";
        pic_path1=":/image/button_style/pause1.png";
    }
    switch(mod)
    {
    case 1:
        this->pixmap.load(pic_path);
        break;
    case 2:
        this->pixmap.load(pic_path1);
        break;
    case 3:
        /*使用命名管道向Mplayer的进程写入命令*/
        mkfifo("MUSIC",0777);
        if(play_pause==2)//控制开始的时候只播放一次，2的时候是播放第一曲
        {
            this->play_music(0);
            this->music_currentrow=0;
        }else//其他的时候由pause进行播放停止的控制
        {
            write(this->fd,"pause\n",strlen("pause\n"));
        }
        /*切换图片（播放和暂停之间切换）*/
        if(play_pause>0)
        {
            play_pause=0;//0的时候是播放
            sem_post(this->sem_write);//解锁
        }else
        {
            play_pause=1;//1的时候是暂停
            sem_wait(this->sem_write);//上锁
        }
        /*切换图片的路径*/
        if(play_pause>0)
        {
            pic_path=":/image/button_style/play.png";
            pic_path1=":/image/button_style/play1.png";
        }else
        {
            pic_path=":/image/button_style/pause.png";
            pic_path1=":/image/button_style/pause1.png";
        }
        /*载入图片*/
        this->pixmap.load(pic_path1);
        break;
    case 4:
        this->pixmap.load(pic_path);
        break;
    }
    this->label_pause->setPixmap(pixmap);
}

void Mainwidgit::label_back_func(int mod)
{
    if(mod==1)
    {
        this->pixmap.load(":/image/button_style/back.png");
    }else if(mod==2||mod==3)
    {
        this->pixmap.load(":/image/button_style/back1.png");
    }else if(mod==4)
    {
        if(this->music_currentrow==0)//上一首歌的变换规则
        {
            this->music_currentrow=this->music_num-1;
        }else
        {
            this->music_currentrow--;
        }
        this->play_music(this->music_currentrow);//播放函数
        this->list_bendi->setCurrentRow(this->music_currentrow);//设置列表变化
        if(play_pause>0)//控制阻塞（暂停的时候切歌会导致暂停重开），暂停功能的延伸补充
        {
            sem_post(this->sem_write);//解锁
        }
        this->play_pause=0;//设为播放
        this->pixmap.load(":/image/button_style/pause1.png");//在暂停播放按钮中载入合适的图片
        this->label_pause->setPixmap(pixmap);

        this->pixmap.load(":/image/button_style/back.png");
    }
    this->label_back->setPixmap(pixmap);
}

void Mainwidgit::label_front_func(int mod)
{
    if(mod==1)
    {
        this->pixmap.load(":/image/button_style/front.png");
    }else if(mod==2||mod==3)
    {
        this->pixmap.load(":/image/button_style/front1.png");
    }else if(mod==4)
    {
        if(this->music_currentrow==music_num-1)//下一首歌的变换规则
        {
            this->music_currentrow=0;
        }else
        {
            this->music_currentrow++;
        }
        this->play_music(this->music_currentrow);//播放函数
        this->list_bendi->setCurrentRow(this->music_currentrow);//设置列表变化
        if(play_pause>0)//控制阻塞（暂停的时候切歌会导致暂停重开），暂停功能的延伸补充
        {
            sem_post(this->sem_write);//解锁
        }
        this->play_pause=0;//设为播放
        this->pixmap.load(":/image/button_style/pause1.png");//在暂停播放按钮中载入合适的图片
        this->label_pause->setPixmap(pixmap);

        this->pixmap.load(":/image/button_style/front.png");
    }
    this->label_front->setPixmap(pixmap);
}

/******************************槽函数**********************************/
void Mainwidgit::label_func(int mod)//这是
{
    Mlabel *label=qobject_cast<Mlabel*>(sender());

    if(label==this->label_pause)
    {
        this->label_pause_func(mod);
    }else if(label==this->label_back)
    {
        this->label_back_func(mod);
    }else if(label==this->label_front)
    {
        this->label_front_func(mod);
    }
}

/*这个函数是控制QToolBox控件的子控件(QToolBoxButton)点击事件（可以实现自开自关）*/
void Mainwidgit::close_list()
{
    static int toolbox_list_num=this->toolbox_list->currentIndex();//在子控件的点击事件中currentIndex返回的是点击的空间的当前行数
    static int toolbox_list_mod=0;//控制切换（开还是关）
    if(this->toolbox_list->currentIndex()==toolbox_list_num)//只有当当前点击的和之前点击的相同时才会切换
    {
        if(toolbox_list_mod==0)//这是子控件本来就关闭的情况
        {
            toolbox_list_mod=1;
        }else//这是子控件开启的情况
        {
            this->toolbox_list->setCurrentIndex(2);//这个是实现关闭的函数（及切换为另一个）
            toolbox_list_mod=0;
        }
    }else if(this->toolbox_list->currentIndex()!=toolbox_list_num)//当不相同时不发生自定义的改变
    {
        toolbox_list_num=this->toolbox_list->currentIndex();
        toolbox_list_mod=1;
    }
}

/*此函数控制的是《列表双击事件》播放歌曲*/
void Mainwidgit::play_list_music()
{
    this->play_music(this->list_bendi->currentRow());//控制歌曲播放的函数
    this->music_currentrow=this->list_bendi->currentRow();//设置当前歌曲在列表中的位置
    this->play_pause=0;//设为播放
    this->pixmap.load(":/image/button_style/pause1.png");//在暂停播放按钮中载入合适的图片
    this->label_pause->setPixmap(pixmap);
}
