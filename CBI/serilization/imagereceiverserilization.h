#ifndef IMAGERECEIVERSERILIZATION_H
#define IMAGERECEIVERSERILIZATION_H

#include <QObject>
#include <QImage>

class ImageReceiverSerilization : public QObject
{
    Q_OBJECT
public:
    explicit ImageReceiverSerilization(QObject *parent = nullptr);
signals:
    void onNewImage(QImage pImage);

public slots:
    void newImageData(QByteArray pBuffer);

private:
    void collectImageFromData();

private:
    QByteArray mBuffer;
};

#endif // IMAGERECEIVERSERILIZATION_H
