#ifndef BRICK_H
#define BRICK_H

#include <QWidget>

class Brick : public QWidget
{
public:
    Brick(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent*);
};

#endif // BRICK_H
