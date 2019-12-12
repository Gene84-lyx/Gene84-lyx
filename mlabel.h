#ifndef MLABEL_H
#define MLABEL_H

#include <QLabel>

namespace Ui {
class Mlabel;
}

class Mlabel : public QLabel
{
    Q_OBJECT

public:
    explicit Mlabel(QWidget *parent = 0);
    ~Mlabel();
    /*事件函数重定义*/
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void label_signal(int mod);

private:
    Ui::Mlabel *ui;
};

#endif // MLABEL_H
