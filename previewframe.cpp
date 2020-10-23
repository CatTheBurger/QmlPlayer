#include "previewframe.h"

PreviewFrame::PreviewFrame(QQuickItem *parent)
{

}

void PreviewFrame::setFrame(QVariant fr)
{
    if (!fr.isValid()) {
        qDebug() << "Null on input!";
        return;
    }

    QImage img = qvariant_cast<QImage>(fr);

    qDebug() << img;

    frame = img;
}

void PreviewFrame::paint(QPainter *painter)
{
    painter->drawImage(0, 0, frame);
}
