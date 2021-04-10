#include "asyncudpreceiver.h"
#include <QUdpSocket>

AsyncUdpReceiver::AsyncUdpReceiver(const uint16_t pPort, const QHostAddress pHost, QObject *parent)
    : AThread(parent)
    , mHost(pHost)
    , mPort(pPort)
{

}

void AsyncUdpReceiver::mainLoop()
{
    QUdpSocket udpSocket;
    udpSocket.open(QIODevice::ReadOnly);

    if(!udpSocket.bind(QHostAddress::AnyIPv4, mPort, QUdpSocket::ShareAddress)){
        qDebug() << "AsyncUdpReceiver::mainLoop error:" << udpSocket.error();
        return;
    }
    if(!udpSocket.joinMulticastGroup(mHost)){
        qDebug() << this->objectName() << "AsyncUdpReceiver::mainLoop QUDPSocket joinMulticastGroup error " << udpSocket.error();
        return;
    }

    udpSocket.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    QObject::connect(&udpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    while (isRunnning()) {
        if(udpSocket.waitForReadyRead(TIME_OUT) && udpSocket.state() == QAbstractSocket::BoundState){
            QByteArray buffer;
            QHostAddress senderHost;
            uint16_t senderPort;
            buffer.resize(udpSocket.pendingDatagramSize());
            udpSocket.readDatagram(buffer.data(), buffer.size(), &senderHost, &senderPort);
            emit onNewMessage(buffer);
        }
    }
}

void AsyncUdpReceiver::error(QAbstractSocket::SocketError pError)
{
    if(pError != QAbstractSocket::SocketError::SocketTimeoutError)
        qDebug() << "AsyncUdpReceiver::error:" << pError;
}
