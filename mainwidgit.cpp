#include "mainwidgit.h"
#include "ui_mainwidgit.h"
#include "mlabel.h"

#include <QLabel>
#include <QGridLayout>

Mainwidgit::Mainwidgit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidgit)
{
    ui->setupUi(this);

    /*实例化设置图片的对象*/
    QPixmap pixmap;

    /*设置栅格布局区*/
    QGridLayout *layout_widget=new QGridLayout();
    QGridLayout *layout_change=new QGridLayout();

    /*设置暂停切歌按钮*/
    Mlabel *label_change=new Mlabel(this);
    label_change->setFixedSize(100,100);
    layout_widget->addWidget(label_change,0,0);

    /*设置暂停按钮*/
    Mlabel *label_pause=new Mlabel(label_change);
    label_pause->setFixedSize(50,50);
    label_pause->setStyleSheet("border-radius:25px");
    pixmap.load(":/image/button_style/pause1.png");
    label_pause->setPixmap(pixmap);
    label_pause->setScaledContents(true);
    layout_change->addWidget(label_pause,0,0);

    /*启用栅格布局*/
    this->setLayout(layout_widget);
    label_change->setLayout(layout_change);
}

Mainwidgit::~Mainwidgit()
{
    delete ui;
}
