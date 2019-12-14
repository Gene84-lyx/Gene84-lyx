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

Mainwidgit::Mainwidgit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidgit)
{
    ui->setupUi(this);

    /*设置主界面的一些属性*/
//    this->resize(1280,720);
    this->setMinimumSize(1280,720);

    /*设置栅格布局区*/
    this->layout_widget=new QGridLayout();//整个界面的布局
    this->layout_change=new QGridLayout();//底部区域的布局（播放、上一曲、下一曲）
//    this->layout_list=new QGridLayout();//歌曲列表框的布局

/***********************************************************************************/
    /*设置暂停切歌基础框*/
    this->label_change=new Mlabel(this);
    this->label_change->setFixedSize(180,70);
//    this->label_change->setStyleSheet("QLabel{border:5px solid #000;}");
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

/***********************************************************************************/
    /*设置歌曲组列表*/
    this->toolbox_list=new QToolBox(this);
    //多个属性用QToolBox{background-color:white;}
    this->toolbox_list->setStyleSheet("background-color:white;");
//    this->toolbox_list->setStyleSheet("QToolBox::tab:last {background: #FFFFFF;border-color:white;}");

    this->layout_widget->addWidget(this->toolbox_list,0,0);

    /*本地歌曲列表*/
    this->list_bendi=new QListWidget();
    this->list_bendi->setMinimumSize(500,500);
    this->list_bendi->setStyleSheet("background-color:white;");

    this->music_list();
    for(int i=0;i<this->music_num;i++)
    {
        this->list_bendi->addItem(this->music_all_name[i]);
    }
    this->ft.setPointSize(24);
    this->list_bendi->setFont(ft);

    this->toolbox_list->addItem(this->list_bendi,tr("第一行"));

    /*默认歌曲列表*/
    this->list_moren=new QListWidget();
    this->list_moren->resize(500,500);
    this->list_moren->setStyleSheet("background-color:white;");

    this->list_moren->addItem("本地列表");
    this->list_moren->addItem("本地列表");
    this->ft.setPointSize(24);
    this->list_moren->setFont(ft);

    this->toolbox_list->addItem(this->list_moren,tr("第二行"));

    /*加一个空白的QToolboxButton,用来实现自开自关*/
    this->list_last=new QListWidget();
    this->list_last->setStyleSheet("background-color:white;");
    this->list_last->setStyleSheet("border:0px solid white;");

    this->toolbox_list->addItem(this->list_last,tr(""));
    this->toolbox_list->setItemEnabled(2,false);//禁止点击使用

    /*获取toolbox下Qtoolboxbutton的指针,并存放在Qlist类toolbox_button中*/
    this->toolbox_button=this->toolbox_list->findChildren<QAbstractButton*>();
    this->toolbox_button.at(2)->setStyleSheet("background:transparent;");

    /*设置初始为2toolbutton*/
    this->toolbox_list->setCurrentIndex(2);

    /*启用栅格布局*/
    this->setLayout(layout_widget);
    this->label_change->setLayout(this->layout_change);


/*************************************************************************/
    connect(this->label_pause,SIGNAL(label_signal(int)),this,SLOT(label_func(int)));
    connect(this->label_back,SIGNAL(label_signal(int)),this,SLOT(label_func(int)));
    connect(this->label_front,SIGNAL(label_signal(int)),this,SLOT(label_func(int)));

    connect(this->toolbox_button.at(0),SIGNAL(clicked()),this,SLOT(close_list()));
    connect(this->toolbox_button.at(1),SIGNAL(clicked()),this,SLOT(close_list()));
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
            save_all_name=QString::fromLocal8Bit(dire->d_name);;
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

/******************************槽函数**********************************/
void Mainwidgit::label_func(int mod)
{
    Mlabel *label=qobject_cast<Mlabel*>(sender());
    QString pic_path,pic_path1;

    if(label==this->label_pause)
    {
        static int play_pause=2;
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
            this->label_pause->setPixmap(this->pixmap);
            break;
        case 2:
            this->pixmap.load(pic_path1);
            this->label_pause->setPixmap(this->pixmap);
            break;
        case 3:
            /*使用命名管道向Mplayer的进程写入命令*/
            mkfifo("MUSIC",0777);
            int fd;
            fd=open("MUSIC",O_WRONLY);
            if(play_pause==2)//控制开始的时候只播放一次
            {
                write(fd,"loadfile /home/lyx/Qt5.8.0/1_object/1_program/Mplayer/song/爱上你很快乐.mp3\n",\
                      strlen("loadfile /home/lyx/Qt5.8.0/1_object/1_program/Mplayer/song/爱上你很快乐.mp3\n"));
            }else//其他的时候由pause进行播放停止的控制
            {
                write(fd,"pause\n",strlen("pause\n"));
            }
            /*切换图片（播放和暂停之间切换）*/
            if(play_pause>0)
            {
                play_pause=0;
            }else
            {
                play_pause=1;
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
            this->label_pause->setPixmap(pixmap);
            break;
        case 4:
            this->pixmap.load(pic_path);
            this->label_pause->setPixmap(pixmap);
            break;
        }
    }else if(label==this->label_back)
    {
        switch(mod)
        {
        case 1:
            this->pixmap.load(":/image/button_style/back.png");
            this->label_back->setPixmap(pixmap);
            break;
        case 2:
            this->pixmap.load(":/image/button_style/back1.png");
            this->label_back->setPixmap(pixmap);
            break;
        case 3:
            this->pixmap.load(":/image/button_style/back1.png");
            this->label_back->setPixmap(pixmap);
            break;
        case 4:
            this->pixmap.load(":/image/button_style/back.png");
            this->label_back->setPixmap(pixmap);
            break;
        }
    }else if(label==this->label_front)
    {
        switch(mod)
        {
        case 1:
            this->pixmap.load(":/image/button_style/front.png");
            this->label_front->setPixmap(pixmap);
            break;
        case 2:
            this->pixmap.load(":/image/button_style/front1.png");
            this->label_front->setPixmap(pixmap);
            break;
        case 3:
            this->pixmap.load(":/image/button_style/front1.png");
            this->label_front->setPixmap(pixmap);
            break;
        case 4:
            this->pixmap.load(":/image/button_style/front.png");
            this->label_front->setPixmap(pixmap);
            break;
        }
    }
}

void Mainwidgit::close_list()
{
    static int n=0;
    if(this->toolbox_list->currentIndex()!=2)
    {
        if(n==0)
        {
            this->toolbox_list->setCurrentIndex(2);
            n=2;
        }else if(n==2)
        {
            n=0;
        }
    }
}
