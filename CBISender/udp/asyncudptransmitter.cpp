#include "asyncudptransmitter.h"
#include <QDebug>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

AsyncUdpTransmitter::AsyncUdpTransmitter(const uint16_t pPort, const QHostAddress pHost ,QObject *parent)
    : AThread(parent)
    , mHost(pHost)
    , mPort(pPort)
    , mUdpSocket(nullptr)
{

}

void AsyncUdpTransmitter::mainLoop()
{
    mUdpSocket = new QUdpSocket;
    mUdpSocket->open(QIODevice::WriteOnly);
    mUdpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    while (isRunnning()) {
        if(QThread::currentThread()->eventDispatcher()->hasPendingEvents()){
            qApp->processEvents();
        }else {
            QThread::msleep(1);
        }
    }

    mUdpSocket->close();
    mUdpSocket->deleteLater();
}

void AsyncUdpTransmitter::send(QByteArray pBuffer)
{
    uint index = 0;
    char *data = pBuffer.data();
    const uint tSize = pBuffer.size();
    while (tSize != index) {
        uint sendSize = qMin(BYTE_SIZE, tSize - index);
        if(mUdpSocket->writeDatagram(data + index, sendSize, mHost, mPort) == -1){
            qDebug() << "AsyncUdpTransmitter::sendToRemote error:" << mUdpSocket->error();
        }
        index += sendSize;
    }
}

void AsyncUdpTransmitter::error(QAbstractSocket::SocketError pError)
{
    qDebug() << "AsyncUdpTransmitter::error:" << pError;
}
