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
    void music_list();

    pid_t kill_pid;//成员变量传参，将进程号传过来控制子进程

public slots:
    void label_func(int mod);
    void close_list();

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

    QToolBox *toolbox_list;//设置
    QList<QAbstractButton *>toolbox_button;//这个是用来存放toolbox_list下级的按钮指针
//    int n;//用来控制(toolbox_list)按钮的自开自关
    QListWidget *list_bendi;
    QListWidget *list_moren;
    QListWidget *list_last;//设为最后一个作为自关的显示

    int music_num;
    QStringList music_all_name;
};

#endif // MAINWIDGIT_H
