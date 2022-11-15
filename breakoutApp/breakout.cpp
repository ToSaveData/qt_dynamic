#include <QLabel>
#include <QApplication>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QtMultimedia/QtMultimedia>
#include <QMessageBox>

#include "breakout.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"

#define WIDTH 50
#define HEIGHT 12
#define SCR_WIDTH 300
#define SCR_HEIGHT 400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)
{
#if 0
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel { background-color:red; border-radius: 5px; }");
    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7,SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    paddle->setStyleSheet("QLabel { background-color:blue; }");

    QVector<QString> v;
    v.append("lightcoral");
    v.append("burlywood");
    v << "tomato" << "darksalmon" << "darkorange";

    for(int y = 0, i = 0; y < 5; y++)
    {
        for(int x = 0; x < 6; x++, i++)
        {
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel { background-color: " + v[y] + ";"
                                                                            "border: 1px solid gray}");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
        resize(SCR_WIDTH, SCR_HEIGHT);
    }
#else
    ball = new Ball(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    paddle = new Paddle(this);
    paddle->setGeometry(SCR_WIDTH*0.7,SCR_HEIGHT*0.9, WIDTH, HEIGHT);

    for(int y = 0, i = 0; y < 5; y++)
    {
        for(int x = 0; x < 6; x++, i++)
        {
            bricks[i] = new Brick(this);
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
        resize(SCR_WIDTH, SCR_HEIGHT);
    }
#endif
    setMouseTracking(true);
    timeId = startTimer(5);

    QAudioOutput *bgAudioOutput = new QAudioOutput;
    bgAudioOutput->setVolume(10);

    bgPlayer = new QMediaPlayer();
    bgPlayer->setAudioOutput(bgAudioOutput);
    bgPlayer->setLoops(QMediaPlayer::Infinite);         /* 무한 반복 */
    bgPlayer->setSource(QUrl::fromLocalFile(QFileInfo("bgm.wav").absoluteFilePath()));
    bgPlayer->play();

    /* 효과음 출력을 위한 플레이어 */
    QAudioOutput *bgEffectOutput = new QAudioOutput;
    bgEffectOutput->setVolume(100);

    effectPlayer = new QMediaPlayer();
    effectPlayer->setAudioOutput(bgEffectOutput);
    effectPlayer->setLoops(QMediaPlayer::Once);
    effectPlayer->setSource(QUrl::fromLocalFile(QFileInfo("effect.wav").absoluteFilePath( )));

    scoreCount = new QLabel("SCORE: " + QString::number(score), this);
    scoreCount->setGeometry(10,10,100,20);
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i = 0; i < NO_OF_BRICKS; i++)   delete bricks[i];
}

void Breakout::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Left:
    {
        if(paddle->x()>0)   paddle->move(paddle->x()-MOVE_SPEED,paddle->y());
        else    paddle->setGeometry(0, paddle->y(), WIDTH, HEIGHT);
        break;
    }
    case Qt::Key_Right:
    {
        if(paddle->x() < WIDTH*5)   paddle->move(paddle->x() + MOVE_SPEED, paddle->y());
        else    paddle->setGeometry(WIDTH*5, paddle->y(), WIDTH, HEIGHT);
        break;
    }
    case Qt::Key_Escape:
    {
        qApp->exit();
        break;
    }
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    x = (x<0)?0:(x+WIDTH>width())?width()-WIDTH:x; //경계검사
    paddle->move(x, paddle->y());
}

void Breakout::timerEvent(QTimerEvent* e) //override 된 timerEvent 함수
{
    Q_UNUSED(e);
    moveObjects();
}
void Breakout::moveObjects()
{
    ball->move(ball->x() + xDir, ball->y() + yDir);

    if((ball->x() <= 0) || (ball->x() + 10 >= SCR_WIDTH))
    {
        xDir *= -1;
    }
    if(ball->y() <= 0)  yDir = 1;

    checkCollision();
}

void Breakout::checkCollision()
{


    if(ball->geometry().bottom() > height())
    {
        killTimer(timeId);
        qDebug("Game lost");
        effectPlayer->play();
        QMessageBox::information(this, "Game Result", "Game Over", QMessageBox::Ok);
    }

    int j = 0;
    for(int i = 0; i < NO_OF_BRICKS; i++)
        if(bricks[i]->isHidden())   j++;

    if(j == NO_OF_BRICKS)
    {
        killTimer(timeId);
        qDebug("Victory");
        QMessageBox::information(this, "Game Result", "Clear!!", QMessageBox::Ok);
    }

    /*사용자와 충돌을 처리*/
    if((ball->geometry()).intersects(paddle->geometry()))
    {
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        /*패들의 맞은 부분에 따라서 공의 반사되는 방향 조정*/
        if(ballLPos < first)    xDir = -1; yDir = -1;
        if(ballLPos >= first && ballLPos < second)    xDir = -2; yDir *= -1;
        if(ballLPos >= second && ballLPos < third)    xDir = 0; yDir = -1;
        if(ballLPos >= third && ballLPos < fourth)    xDir = 2; yDir *= -1;
        if(ballLPos > fourth)    xDir = 1; yDir = -1;
        effectPlayer->stop();
        effectPlayer->play();
    }

    /*블록의 충돌을 처리*/
    for(int i = 0; i < NO_OF_BRICKS; i++)
    {
        if((ball->geometry()).intersects(bricks[i]->geometry()))
        {
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();
            /*현재 블록의 위치를 계산*/
            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop - 1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);
            if(!bricks[i]->isHidden()) /*공과 블록의 충돌검사*/
            {
                if(bricks[i]->geometry().contains(pointRight)) xDir = -1;
                else if(bricks[i]->geometry().contains(pointLeft))  xDir = 1;
                if(bricks[i]->geometry().contains(pointTop))    yDir = 1;
                else if(bricks[i]->geometry().contains(pointBottom))    yDir = -1;
                bricks[i]->setHidden(true);

                effectPlayer->play();
                score++;
                scoreCount->setText("SCORE: " + QString::number(score));
            }
        }
    }
    if(ball->geometry().left() == 0 || ball->geometry().left() + 10 == 300 ||
            ball->geometry().top() == 0)
    {
        effectPlayer->stop();
        effectPlayer->play();
    }
}

//int Breakout::countScore()
//{
//    int a= 0;
//    for(int i = 0; i < NO_OF_BRICKS; i++)
//    {
//        if(bricks[i]->isHidden())  a++;
//    }
//    return score = a;
//}
