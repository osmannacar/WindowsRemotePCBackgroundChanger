#include "athread.h"

AThread::AThread(QObject *parent)
    : QObject(parent)
{

}

AThread::~AThread()
{
    stop();
    moveToThread(QThread::currentThread());
}

void AThread::start()
{
    if(mIsRunnning){
        return;
    }
    moveToThread(&mThread);
    QObject::connect(&mThread, SIGNAL(started()), this, SLOT(outerLoop()));
    mIsRunnning = true;
    mThread.start();
}

void AThread::stop()
{
    if(!mIsRunnning){
        return;
    }
    QObject::disconnect(&mThread, SIGNAL(started()), this, SLOT(outerLoop()));
    mIsRunnning = false;
    mThread.wait();
}

bool AThread::isRunnning() const
{
    return mIsRunnning;
}

void AThread::outerLoop()
{
    mainLoop();
    mThread.quit();
}

