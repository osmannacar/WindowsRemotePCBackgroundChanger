#include <QBuffer>
#include <QCoreApplication>
#include <QTimer>
#include <qimage.h>
#include "udp/asyncudptransmitter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AsyncUdpTransmitter *transmitter = new AsyncUdpTransmitter(13589, QHostAddress("224.0.0.1"));
    transmitter->start();
    QTimer::singleShot(1000, transmitter, [transmitter](){
//        QImage img("C:/Users/osman.nacar/Downloads/emilia-3.jpg");

        QImage img("C:/Users/osman.nacar/Downloads/NarutoUzumaki.jpg");
//        QImage img("C:/Users/osman.nacar/Downloads/gari.jpg");
//        QImage img("C:/Users/osman.nacar/Downloads/kedicik.jpg");
        QByteArray arr;
        QBuffer buffer(&arr);
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer, "JPEG");
        transmitter->send(arr);
        qDebug() << "sended";

    });

    return a.exec();
}
