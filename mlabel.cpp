#include "mlabel.h"
#include "ui_mlabel.h"

#include <QPixmap>

Mlabel::Mlabel(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::Mlabel)
{
    ui->setupUi(this);
}

Mlabel::~Mlabel()
{
    delete ui;
}

void Mlabel::enterEvent(QEvent *e)
{
    emit this->label_signal(1);
}

void Mlabel::leaveEvent(QEvent *e)
{
    emit this->label_signal(2);
}

void Mlabel::mousePressEvent(QMouseEvent *e)
{
    emit this->label_signal(3);
}

void Mlabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit this->label_signal(4);
}
