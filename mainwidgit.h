#ifndef MAINWIDGIT_H
#define MAINWIDGIT_H

#include <QWidget>

namespace Ui {
class Mainwidgit;
}

class Mainwidgit : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidgit(QWidget *parent = 0);
    ~Mainwidgit();

private:
    Ui::Mainwidgit *ui;
};

#endif // MAINWIDGIT_H
