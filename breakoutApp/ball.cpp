#include "ball.h"
#include <QPainter>
#define RADIUS 10

Ball::Ball(QWidget *parent)
    : QWidget(parent)
{
    resize(RADIUS, RADIUS);
//    setPixmap(QPixmap("ball.png"));
    setStyleSheet("background-color: rgba(0,0,0,0");
}

void Ball::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter p(this);
    p.setPen(QColor(Qt::transparent));
    p.setBrush(QColor(Qt::darkBlue));
    p.drawEllipse(0,0,RADIUS,RADIUS);
}
