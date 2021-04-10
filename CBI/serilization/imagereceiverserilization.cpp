#include "imagereceiverserilization.h"

ImageReceiverSerilization::ImageReceiverSerilization(QObject *parent)
    : QObject(parent)
    , mBuffer(0)
{

}

void ImageReceiverSerilization::newImageData(QByteArray pBuffer)
{
    //start of JPEG image
    if(pBuffer[0] == (char)0xFF && pBuffer[1] == (char)0xD8){
        mBuffer.clear();
        mBuffer.append(pBuffer);
    }//end of JPEG image
    else if (pBuffer[pBuffer.size() - 2] == (char)0xFF && pBuffer[pBuffer.size() - 1] == (char)0xD9) {
        mBuffer.append(pBuffer);
        collectImageFromData();
    }else {
        mBuffer.append(pBuffer);
    }
}

void ImageReceiverSerilization::collectImageFromData()
{
    QImage img;
    img.loadFromData(mBuffer, "JPEG");
    emit onNewImage(img);
}
