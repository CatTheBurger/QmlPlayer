#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <QObject>
#include <QImage>
#include <QtQuick/QQuickItem>
#include <QDebug>
extern "C" {
#include <libavresample/avresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
}

class VideoDecoder : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE VideoDecoder(QObject *parent = nullptr);

    Q_INVOKABLE void setFile(QString p);
    Q_INVOKABLE QImage extractQImage();

    QString path;
    AVCodecContext *ctx;
    AVCodec *codec;
    AVFormatContext *format;
    AVPacket *pkt;
    int video_stream = -1;
};

#endif // VIDEODECODER_H
