#ifndef PREVIEWFRAME_H
#define PREVIEWFRAME_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QtQuick/QQuickPaintedItem>

class PreviewFrame : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Q_INVOKABLE PreviewFrame(QQuickItem *parent = 0);

    Q_INVOKABLE void setFrame(QVariant fr);
    void paint(QPainter *painter) override;

    QImage frame;
};

#endif // PREVIEWFRAME_H
