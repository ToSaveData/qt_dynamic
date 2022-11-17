#include "thread.h"

Thread::Thread(QObject *obj)
    : m_stopFlag(Play)
{
    m_label = qobject_cast<QLabel*>(obj);
}

Thread::~Thread()
{
}

void Thread::run()
{
    Q_FOREVER
    {
        m_mutex.lock();
        if(m_stopFlag == Stop)   m_waitCondition.wait(&m_mutex);
        m_mutex.unlock();

        emit setLabeled(QString("run %1").arg(count++));
        msleep(100);
    }
}

void Thread::stopThread()
{
    m_stopFlag = Stop;
}

void Thread::resumeThread()
{
    m_mutex.lock();
    m_stopFlag = Play;
    m_waitCondition.wakeAll();
    m_mutex.unlock();
}
