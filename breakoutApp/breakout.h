#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include "ball.h"
#include "brick.h"
#include "paddle.h"

class QLabel;
class QMediaPlayer;
class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();
protected:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent*);
    static const int MOVE_SPEED = 3;
    void timerEvent(QTimerEvent*);
    void moveObjects();
    void checkCollision();
//    int countScore();
private:
    static const int NO_OF_BRICKS = 30;
#if 0
    QLabel *ball;
    QLabel *paddle;
    QLabel *bricks[NO_OF_BRICKS];
#else
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[NO_OF_BRICKS];
#endif
    QLabel *scoreCount;
    int score = 0;
    QMediaPlayer *bgPlayer;
    QMediaPlayer *effectPlayer;
    int timeId;
    int xDir, yDir;
};
#endif // BREAKOUT_H
