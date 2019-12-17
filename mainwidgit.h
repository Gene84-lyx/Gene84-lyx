#ifndef MAINWIDGIT_H
#define MAINWIDGIT_H

#include "mlabel.h"

#include <QWidget>
#include <QPixmap>
#include <QGridLayout>
#include <QListWidget>
#include <QToolBox>
#include <QList>
#include <QAbstractButton>
#include <dirent.h>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <semaphore.h>
#include <QSlider>

namespace Ui {
class Mainwidgit;
}

class Mainwidgit : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidgit(QWidget *parent = 0);
    ~Mainwidgit();

    /*事件函数*/
    void closeEvent(QCloseEvent *e);

    /*普通函数*/
    void music_list();//将文件中的所有歌曲存入列表中
    void play_music(int row);//拼接路径、名字、文件类型，然后输入到终端播放
    void label_pause_func(int mod);//播放与暂停按钮功能实现的函数
    void label_back_func(int mod);//控制上一首的按钮
    void label_front_func(int mod);//控制下一首的按钮

    /*公有成员变量（因为需要类外使用，所以定义为公有的）*/
    pid_t kill_pid;//成员变量传参，将进程号传过来控制子进程
    QLabel *label_time;//用以在主函数的线程中设置时间的显示
    sem_t *sem_write;//定义一个信号量，用来控制写的阻塞
    int current_time_int;//存储当前的时间
    int all_time_int;//存储总的时间
    QSlider *slider_music;//定义一个进度条控件
    int flag_press_slider;//用来控制只有在鼠标点击之后才能够使用槽函数中的内容
    int flag_release_slider;
    int old_percent;//保存改变之前的进度条进度

public slots:
    void label_func(int mod);//控制播放按钮
    void close_list();//能够自关列表
    void set_current_list(int row);//设置当前的toolboxbutton是哪个
    void change_music();//双击，下一曲，上一曲播放会被打开，需要调整锁和图片
    void play_list_music();//播放列表中的歌曲
    void press_slider();//按压slider信号
    void release_slider();//释放slider信号
    void jump_music(int value);//跳转到多少秒后或跳转到多少秒前

signals:
    void kill_mplayer();

private:
    Ui::Mainwidgit *ui;
    QPixmap pixmap;//实例化设置图片的对象

    QFont ft;//设置字体大小

    QGridLayout *layout_widget;//主界面的布局
    QGridLayout *layout_botton_line;//底行基本框的布局
    QGridLayout *layout_change;//播放、下一首、上一首的布局
    QGridLayout *layout_progress;//进度条时间的基本框的布局

    QLabel *label_bottom_line;//设置底行的基本框

    Mlabel *label_change;//设置（播放、下一首、上一首）的框
    Mlabel *label_pause;//设置（播放和暂停）按键
    Mlabel *label_back;//设置切换上一首歌按钮
    Mlabel *label_front;//设置切换下一首歌按钮
    int play_pause;//控制暂停播放按钮的图片加载
    int fd;//控制打开管道，进行命令的输入或读取

    QLabel *label_progress;//进度条、时间的基本框

    QToolBox *toolbox_list;//设置
    QList<QAbstractButton *>toolbox_button;//这个是用来存放toolbox_list下级的按钮指针
    QListWidget *list_bendi;
    QListWidget *list_moren;
    QListWidget *list_last;//设为最后一个作为自关的显示
    int toolbox_list_num;//存储的是当前toolboxbutton的号
    int toolbox_list_mod;//存储的是此时应当开还是关

    int music_num;//获得总共歌曲的数量，方便输入列表
    int music_currentrow;//当前歌曲在列表中的位置，如果重新读取本地文件夹一切重置
    QStringList music_all_name;//将歌曲的名字存入链表中
};

#endif // MAINWIDGIT_H
