#ifndef ATHREAD_H
#define ATHREAD_H

#include <QObject>
#include <QThread>

class AThread : public QObject
{
    Q_OBJECT
public:
    explicit AThread(QObject *parent = nullptr);
    ~AThread();

    void start();
    void stop();

protected:
    bool isRunnning() const;
    virtual void mainLoop() = 0;

public slots:
    void outerLoop();

private:
    bool mIsRunnning = false;
    QThread mThread;
};

#endif // ATHREAD_H
