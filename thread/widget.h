#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Thread;
class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

private:
    Thread *thread;

public slots:
    void threadControl(bool);
};

#endif // WIDGET_H
