#include "mainwidgit.h"
#include <QApplication>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    /*创建进程，一个用来控制播放音乐等，一个用来控制界面*/
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
    }else if(pid==0)//子进程用来控制播放音乐
    {

    }else//父进程用来控制界面的显示
    {
        QApplication a(argc, argv);
        Mainwidgit w;
        w.show();

        return a.exec();
    }

}
