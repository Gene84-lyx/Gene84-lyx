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
#include <QSlider>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QAbstractItemView>

Mainwidgit::Mainwidgit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidgit)
{
    ui->setupUi(this);

    /*参数的初始化*/
    this->play_pause=2;//控制初始时点击播放按钮音乐的播放
    this->music_currentrow=0;//设置当前歌曲在列表中为第一首
    this->fd=open("MUSIC",O_WRONLY);//以只读的方式打开命名管道
    this->current_time_int=0;
    this->all_time_int=240;
    this->flag_press_slider=0;//用来控制只有在鼠标点击之后才能够使用槽函数中的内容
    this->flag_release_slider=0;
    this->judge_time=NULL;
    this->row_lrc=0;

    /*定义一个信号量，用来发送暂停信息的时候阻塞时间获取*/
    this->sem_write=sem_open("mysem",O_RDWR|O_CREAT,0666,1);
    sem_init(this->sem_write,0,0);

    /*设置主界面的一些属性*/
    this->setMinimumSize(1280,720);

    /*设置栅格布局区*/
    this->layout_widget=new QGridLayout();//整个界面的布局
    this->layout_change=new QGridLayout();//底部区域的布局（播放、上一曲、下一曲）
    this->layout_progress=new QGridLayout();//进度条时间的基本框的布局
    this->layout_botton_line=new QGridLayout();//底行基本框的布局

    /*设置栅格布局的属性*/
//    this->layout_botton_line->setSpacing(0);
//    this->layout_widget->setAlignment(Qt::AlignCenter);

/***********************************************************************************/
    /*设置底边的基本框*/
    this->label_bottom_line=new QLabel(this);
    this->label_bottom_line->setFixedSize(1020,100);
    this->layout_widget->addWidget(this->label_bottom_line,1,0,1,3,Qt::AlignLeft | Qt::AlignVCenter);

    /*设置暂停切歌基础框*/
    this->label_change=new Mlabel(this->label_bottom_line);
    this->label_change->setFixedSize(240,100);
    this->layout_botton_line->addWidget(this->label_change,0,0);

    /*设置（播放暂停）按钮*/
    this->label_pause=new Mlabel(this->label_change);
    this->label_pause->setFixedSize(60,60);
    this->label_pause->setStyleSheet("border-radius:30px");//圆形的命令（冒号后面的是半径）
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

    /*时间和进度条的基本框*/
    this->label_progress=new QLabel(this->label_bottom_line);
    this->label_progress->setFixedSize(750,100);
    this->layout_botton_line->addWidget(this->label_progress,0,1);

    /*添加一个此时歌曲播放时间的框*/
    this->label_time=new QLabel(this->label_progress);
    this->label_time->setFixedSize(120,50);
    this->ft.setPointSize(14);
    this->label_time->setFont(ft);
    this->layout_progress->addWidget(this->label_time,0,1);

    /*添加进度条*/
    this->slider_music=new QSlider(this->label_progress);
    this->slider_music->setFixedSize(600,50);
    this->slider_music->setOrientation(Qt::Horizontal);
    this->slider_music->setStyleSheet("background-color:transparent;");
    this->slider_music->setMinimum(0);
    this->slider_music->setMaximum(1000);

    this->layout_progress->addWidget(this->slider_music,0,0);

/***********************************************************************************/
    /*设置歌曲组列表*/
    this->toolbox_list=new QToolBox(this);
    this->toolbox_list->setStyleSheet("background-color:white;");//多个属性用QToolBox{background-color:white;}
    this->toolbox_list->setMinimumWidth(420);
    this->toolbox_list->setMaximumWidth(500);
    this->ft.setPointSize(24);
    this->toolbox_list->setFont(ft);//只有在父控件(QToolBox)中改变字体才能改变子控件(QToolBoxButton)中的字体大小，子控件自己无法该
    this->layout_widget->addWidget(this->toolbox_list,0,0,1,1);

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
/***********************************************************************************/
    /*歌词列表*/
    this->lrc_word_list=new QListWidget();
    this->lrc_word_list->setStyleSheet("background-color:white;");
    this->lrc_word_list->setMinimumSize(840,600);
    this->ft.setPointSize(24);
    this->lrc_word_list->setFont(ft);
    this->layout_widget->addWidget(this->lrc_word_list,0,1,1,2);

    this->lrc_word_list->setEnabled(false);

    this->lrc_list();//将歌曲读入QStringlist中
//    this->listwidget_button.at(7)->setBackground(QColor(0,0,0));
//    this->listwidget_button.at(7)->setTextColor(QColor(255,255,255));

//    this->lrc_word_list->scrollToItem(listwidget_button.at(7),QAbstractItemView::PositionAtCenter);//设置listwidget中的项目居中
    this->lrc_word_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不显示垂直滚动条
    this->lrc_word_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不显示横向滚动条


/***********************************************************************************/

    /*启用栅格布局*/
    this->setLayout(this->layout_widget);
    this->label_change->setLayout(this->layout_change);
    this->label_progress->setLayout(this->layout_progress);
    this->label_bottom_line->setLayout(this->layout_botton_line);

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

    /*控制QSlider(Horizontal)的变化*/
    connect(this->slider_music,SIGNAL(sliderPressed()),this,SLOT(press_slider()));
    connect(this->slider_music,SIGNAL(sliderReleased()),this,SLOT(release_slider()));
    connect(this->slider_music,SIGNAL(valueChanged(int)),this,SLOT(jump_music(int)));
}

Mainwidgit::~Mainwidgit()
{
    delete ui;
}
/******************************事件函数**********************************/
void Mainwidgit::closeEvent(QCloseEvent *e)
{
    if(this->judge_time!=NULL)
    {
        free(this->judge_time);
        this->judge_time=NULL;
    }
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

void Mainwidgit::lrc_list()
{
    DIR *dir=opendir("/home/lyx/Qt5.8.0/1_object/1_program/Mplayer/lyrics");
    QString save_all_name;
    QStringList cut_name;
    struct dirent *dire;
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
            if(cut_name[1]=="lrc")
            {
                this->lrc_all_name.append(cut_name[0]);
            }
        }
    }
    putchar(10);
    closedir(dir);
}

QString Mainwidgit::find_lrc_name()
{
    QString lrc_name="";
    for(int i=0;i<this->lrc_all_name.count();i++)
    {
        if(this->music_all_name[this->music_currentrow]==this->lrc_all_name[i])
        {
            lrc_name=lrc_all_name[i];
        }
    }
    return lrc_name;
}

void Mainwidgit::cut_lrc()
{
    /*每次初始化歌词listwidget(lrc_word_list)*/
    this->lrc_word_list->clear();
    this->listwidget_button.clear();
    this->row_lrc=0;

    if(this->find_lrc_name()!="")//当没有找到了对应的歌词时
    {
        /*拼接要打开的歌曲的路径路径*/
        QString path="/home/lyx/Qt5.8.0/1_object/1_program/Mplayer/lyrics/";//路径
        QString postfix=".lrc";//文件类型名
        QString path_add_name=path+this->find_lrc_name()+postfix;//将路径和文件名相加起来
        QByteArray ba = path_add_name.toUtf8();//转换格式为ubuntu识别的UTF-8格式（中文不乱码）

        /*一致的的方式打开打开歌词文件(lrc)，获得流指针*/
        this->file_lrc=fopen(ba.data(),"r");

        /*从文件中读取歌词存入QString中*/
        char temp[128]={0};
        QStringList oneline_lrc;//用来存放一行歌词
        while(fgets(temp,128,this->file_lrc)!=NULL)
        {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString temp_str=codec->toUnicode(temp);
            oneline_lrc.append((temp_str.split("\r\n")[0]));
        }

        /*关闭文件流指针*/
        fclose(this->file_lrc);

        /*将歌词切割成时间和语句*/
        QStringList oneline_time;
        QStringList oneline_sentence;
        for(int i=0;i<oneline_lrc.count();i++)
        {
            QStringList temp=oneline_lrc[i].split("]");
            if(temp[1].size()!=0)
            {
                oneline_time.append(temp[0]);
                oneline_sentence.append(temp[1]);
            }
        }

        /*将时间转换成转换成十毫秒*/
        if(judge_time!=NULL)
        {
            free(judge_time);
            judge_time=NULL;
        }
        judge_time=(int*)malloc(oneline_time.count()*sizeof(int)+8);
        for(int i=0;i<oneline_time.count();i++)
        {
            QStringList temp_time=oneline_time[i].split("[");
            temp_time=temp_time[1].split(":");
            int min_num=temp_time[0].toInt();
            temp_time=temp_time[1].split(".");
            int sec_num=temp_time[0].toInt();
            int msec_num=temp_time[1].toInt();
            int all_num=min_num*6000+sec_num*100+msec_num;
            judge_time[i]=all_num;
        }

        /*切割歌词*/
        for(int i=0;i<oneline_sentence.count()+2;i++)//前两格和后两格为空
        {
            if(i<2)
            {
                QListWidgetItem *item = new QListWidgetItem(QString(""));
                this->listwidget_button.append(item);
                item->setTextAlignment(Qt::AlignCenter);
                item->setSizeHint(QSize(840,(this->lrc_word_list->height()/5)));
                this->listwidget_button.at(0)->setBackground(QColor(0,0,0));
                this->lrc_word_list->addItem(item);
            }else
            {
                QListWidgetItem *item = new QListWidgetItem(oneline_sentence[i-2]);
                this->listwidget_button.append(item);
                item->setTextAlignment(Qt::AlignCenter);
                item->setSizeHint(QSize(840,(this->lrc_word_list->height()/5)));
                item->setTextColor(QColor(0,0,0));
                this->lrc_word_list->addItem(item);
            }
        }

//        this->listwidget_button.at(0)->setBackground(QColor(240,120,70));
//        this->listwidget_button.at(0)->setTextColor(QColor(255,255,255));
        this->lrc_word_list->scrollToItem(listwidget_button.at(2),QAbstractItemView::PositionAtCenter);//设置listwidget中的项目居中

    }
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
            this->play_music(this->music_currentrow);
            this->set_current_list(0);//设置当前打开的toolboxbutton
            this->cut_lrc();
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
        this->set_current_list(0);//设置当前打开的toolboxbutton
        this->change_music();//双击，下一曲，上一曲播放会被打开，需要调整锁和图片

        this->cut_lrc();

        this->pixmap.load(":/image/button_style/back.png");
    }
    this->label_back->setPixmap(pixmap);
}

void Mainwidgit::label_front_func(int mod,int auto_next)
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
        this->set_current_list(0);//设置当前打开的toolboxbutton
        this->change_music();//双击，下一曲，上一曲播放会被打开，需要调整锁和图片

        this->cut_lrc();
        if(auto_next==0)
        {
            this->pixmap.load(":/image/button_style/front.png");
        }
    }
    if(auto_next==0)
    {
        this->label_front->setPixmap(pixmap);
    }
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

void Mainwidgit::set_current_list(int row)
{
    this->toolbox_list->setCurrentIndex(row);//设置转到当前toolboxbutton中
    toolbox_list_mod=1;//表示已经打开了
    toolbox_list_num=row;//存储当前改变的行数
}

void Mainwidgit::change_music()
{
    if(play_pause>0)//控制阻塞（暂停的时候切歌会导致暂停重开），暂停功能的延伸补充
    {
        sem_post(this->sem_write);//解锁
    }
    this->play_pause=0;//设为播放
    this->pixmap.load(":/image/button_style/pause1.png");//在暂停播放按钮中载入合适的图片
    this->label_pause->setPixmap(pixmap);
}

/*此函数控制的是《列表双击事件》播放歌曲*/
void Mainwidgit::play_list_music()
{
    this->play_music(this->list_bendi->currentRow());//控制歌曲播放的函数
    this->music_currentrow=this->list_bendi->currentRow();//获得当前歌曲在列表中的位置
    this->change_music();//双击，下一曲，上一曲播放会被打开，需要调整锁和图片
    this->cut_lrc();
}

void Mainwidgit::press_slider()
{
    this->flag_press_slider=1;//用来控制只有在鼠标点击之后才能够使用槽函数中的内容
    this->old_percent=this->slider_music->value();
}

void Mainwidgit::release_slider()
{
    if(this->flag_press_slider==1)
    {
        int current_percent=this->slider_music->value();
        int current_time=(int)(this->current_time_int/100);
        int all_music_time=(int)(this->all_time_int/100);
        int jump_time=current_percent-current_time;
        if((current_time+jump_time)>=all_music_time)
        {
            jump_time=jump_time-2;
        }
        QString change_time=QString::number(jump_time);
        QString seek_add_time="seek "+change_time+"\n";
        QByteArray seek_time = seek_add_time.toUtf8();//转换格式为ubuntu识别的UTF-8格式（中文不乱码）
        write(this->fd,seek_time.data(),strlen(seek_time.data()));
        usleep(500000);
        this->flag_press_slider=0;
        this->change_music();
    }
    if(this->slider_music->value()>=((int)(this->all_time_int/100)-4)&&this->flag_press_slider!=1)
    {
        this->label_front_func(4,1);
    }
}

void Mainwidgit::jump_music(int value)
{
    if(this->flag_press_slider==1)
    {
        int sec_all=(int)(this->all_time_int/100)%60;
        int min_all=(int)(this->all_time_int/100)/60;
        QString atime=QString("%1:%2").arg(min_all, 2, 10, QChar('0')).arg(sec_all, 2, 10, QChar('0'));
        int sec_cur=(int)(value)%60;
        int min_cur=(int)(value)/60;
        QString ctime=QString("%1:%2").arg(min_cur, 2, 10, QChar('0')).arg(sec_cur, 2, 10, QChar('0'));
        this->label_time->setText(ctime+"/"+atime);
    }
    if(this->slider_music->value()>=((int)(this->all_time_int/100)-4)&&this->flag_press_slider!=1)
    {
        this->label_front_func(4,1);
    }
    if((value*100)>=this->judge_time[this->row_lrc]&&this->flag_press_slider==1&&value>this->old_percent)
    {
        this->listwidget_button.at(this->row_lrc+1)->setBackground(QColor(0,0,0));
        this->listwidget_button.at(this->row_lrc+1)->setTextColor(QColor(255,255,255));
        this->row_lrc++;
        this->listwidget_button.at(this->row_lrc+1)->setBackground(QColor(240,120,70));
        this->listwidget_button.at(this->row_lrc+1)->setTextColor(QColor(255,255,255));
        this->lrc_word_list->scrollToItem(this->listwidget_button.at(this->row_lrc+1),QAbstractItemView::PositionAtCenter);
        this->old_percent=value;
    }else if((value*100)<this->judge_time[this->row_lrc]&&this->flag_press_slider==1&&value<this->old_percent)
    {
        this->listwidget_button.at(this->row_lrc+1)->setBackground(QColor(255,255,255));
        this->listwidget_button.at(this->row_lrc+1)->setTextColor(QColor(0,0,0));
        this->row_lrc--;
        this->listwidget_button.at(this->row_lrc+1)->setBackground(QColor(240,120,70));
        this->listwidget_button.at(this->row_lrc+1)->setTextColor(QColor(255,255,255));
        this->lrc_word_list->scrollToItem(this->listwidget_button.at(this->row_lrc+1),QAbstractItemView::PositionAtCenter);
        this->old_percent=value;
    }
}
