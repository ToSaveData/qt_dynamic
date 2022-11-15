#include "brick.h"
#include <QPainter>
#define WIDTH 50
#define HEIGHT 12

Brick::Brick(QWidget *parent)
    : QWidget(parent)
{
    resize(WIDTH, HEIGHT);
//    setPixmap(QPixmap("brick.png").scaled(WIDTH,HEIGHT));
    setStyleSheet("background-color:rgba(0,0,0,0)");
}

void Brick::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter p(this);
    p.setBrush(QColor(Qt::white));
    p.drawRect(0,0,WIDTH, HEIGHT);
}
