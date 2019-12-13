#ifndef MAINWIDGIT_H
#define MAINWIDGIT_H

#include "mlabel.h"

#include <QWidget>
#include <QPixmap>
#include <QGridLayout>
#include <QListWidget>

namespace Ui {
class Mainwidgit;
}

class Mainwidgit : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidgit(QWidget *parent = 0);
    ~Mainwidgit();

    void closeEvent(QCloseEvent *e);

    pid_t kill_pid;//成员变量传参，将进程号传过来控制子进程

public slots:
    void label_func(int mod);

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

//    Mlabel *label_list;//设置歌曲列表栏的基本框
    QListWidget *list_list;//设置歌曲列表的基本框
    Mlabel *label_group;//歌曲的组名
    QListWidget *list_name;//存放歌曲的名字
};

#endif // MAINWIDGIT_H
