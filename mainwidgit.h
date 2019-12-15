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

    /*公有成员变量*/
    pid_t kill_pid;//成员变量传参，将进程号传过来控制子进程（因为需要类外使用，所以定义为公有的）

public slots:
    void label_func(int mod);//控制播放按钮
    void close_list();//能够自关列表
    void play_list_music();//播放列表中的歌曲

signals:
    void kill_mplayer();

private:
    Ui::Mainwidgit *ui;
    QPixmap pixmap;//实例化设置图片的对象

    QFont ft;//设置字体大小

    QGridLayout *layout_widget;//主界面的布局
    QGridLayout *layout_change;//播放、下一首、上一首的布局
    QGridLayout *layout_list;//歌曲列表的布局

    Mlabel *label_change;//设置（播放、下一首、上一首）的框
    Mlabel *label_pause;//设置（播放和暂停）按键
    Mlabel *label_back;//设置切换上一首歌按钮
    Mlabel *label_front;//设置切换下一首歌按钮
    int play_pause;//控制暂停播放按钮的图片加载
    int fd;//控制打开管道，进行命令的输入或读取

    QToolBox *toolbox_list;//设置
    QList<QAbstractButton *>toolbox_button;//这个是用来存放toolbox_list下级的按钮指针
    QListWidget *list_bendi;
    QListWidget *list_moren;
    QListWidget *list_last;//设为最后一个作为自关的显示

    int music_num;//获得总共歌曲的数量，方便输入列表
    int music_currentrow;//当前歌曲在列表中的位置，如果重新读取本地文件夹一切重置
    QStringList music_all_name;//将歌曲的名字存入链表中
};

#endif // MAINWIDGIT_H
