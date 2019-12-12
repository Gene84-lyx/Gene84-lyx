#include "mainwidgit.h"
#include <QApplication>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    /*创建进程*/
    pid_t pid=fork();

    /*分两个进程，分别控制界面和播放歌曲获取信息*/
    if(pid<0)
    {
        perror("fork");
    }else if(pid==0)//子进程用来控制播放音乐、获得音乐信息
    {

    }else//父进程用来控制界面的变化
    {
        QApplication a(argc, argv);
        Mainwidgit w;
        w.show();
        return a.exec();
    }
    return 0;
}
