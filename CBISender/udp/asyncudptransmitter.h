#ifndef ASYNCUDPTRANSMITTER_H
#define ASYNCUDPTRANSMITTER_H

#include <QUdpSocket>
#include "thread/athread.h"

class AsyncUdpTransmitter : public AThread
{
public:
    explicit AsyncUdpTransmitter(const uint16_t pPort, const QHostAddress pHost ,QObject *parent = nullptr);

    void mainLoop() override;
public slots:
    void send(QByteArray pBuffer);
private slots:
    void error(QAbstractSocket::SocketError pError);
private:
    uint16_t mPort;
    QHostAddress mHost;
    QUdpSocket *mUdpSocket;
    inline const static uint BYTE_SIZE = 1024;
};

#endif // ASYNCUDPTRANSMITTER_H
