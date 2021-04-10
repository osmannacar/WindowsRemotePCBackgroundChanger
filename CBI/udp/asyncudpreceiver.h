#ifndef ASYNCUDPRECEIVER_H
#define ASYNCUDPRECEIVER_H

#include "thread/athread.h"

#include <QHostAddress>

class AsyncUdpReceiver : public AThread
{
    Q_OBJECT
public:
    explicit AsyncUdpReceiver(const uint16_t pPort, const QHostAddress pHost, QObject *parent = nullptr);
    void mainLoop() override;

signals:
    void onNewMessage(QByteArray pBuffer);

private slots:
    void error(QAbstractSocket::SocketError pError);
private:
    uint16_t mPort;
    QHostAddress mHost;
    const static uint8_t TIME_OUT = 20;
};

#endif // ASYNCUDPRECEIVER_H
