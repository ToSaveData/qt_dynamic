#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>

class Paddle : public QWidget
{
public:
    Paddle(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent*);
};

#endif // PADDLE_H
