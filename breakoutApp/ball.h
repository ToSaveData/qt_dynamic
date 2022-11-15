#ifndef BALL_H
#define BALL_H

#include <QWidget>

class Ball : public QWidget
{
public:
    Ball(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent*);
};

#endif // BALL_H
