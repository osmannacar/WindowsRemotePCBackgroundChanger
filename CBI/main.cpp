#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include <QDesktopServices>
#include <QStandardPaths>
#include "udp/asyncudpreceiver.h"
#include "serilization/imagereceiverserilization.h"
#include "shobjidl.h"
#include "Windows.h"

static int IMG_COUNT = 1;
void addToStartup(){

    QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    QFile::link(QCoreApplication::applicationFilePath(), QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)
                + "/Startup/" + fileInfo.completeBaseName() + ".lnk");

}

void ChangeBackgroundImage(QString path){

    HRESULT hr = CoInitialize(nullptr);
    IDesktopWallpaper* pDesktopWallpaper = nullptr;
    hr = CoCreateInstance(__uuidof(DesktopWallpaper), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pDesktopWallpaper));
    if (FAILED(hr))
    {
        qDebug() << "error";
    }
    else
    {
        pDesktopWallpaper->SetWallpaper(nullptr, path.toStdWString().c_str());
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AsyncUdpReceiver *receiver = new AsyncUdpReceiver(13589, QHostAddress("224.0.0.1"));
    ImageReceiverSerilization *serilization = new ImageReceiverSerilization();
    QObject::connect(receiver, &AsyncUdpReceiver::onNewMessage, receiver,[serilization](QByteArray buffer){
        serilization->newImageData(buffer);
    });

    QObject::connect(serilization, &ImageReceiverSerilization::onNewImage, receiver, [serilization](QImage img){
        QString tPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        QString tImagePath = QString("%1/%2.jpg").arg(tPath, QString::number(IMG_COUNT));

        img.save(tImagePath,"JPEG");
        ++IMG_COUNT;


        ChangeBackgroundImage(tImagePath);
    });

    receiver->start();

    addToStartup();


    return a.exec();
}
