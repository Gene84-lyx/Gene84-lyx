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

int main(int argc, char *argv[])
{
    mkfifo("MUSIC",0777);

    /*创建进程，一个用来控制播放音乐等，一个用来控制界面*/
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
    }else if(pid==0)//子进程用来控制播放音乐
    {
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

        return a.exec();
    }

}
