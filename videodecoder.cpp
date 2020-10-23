#include "videodecoder.h"

VideoDecoder::VideoDecoder(QObject *parent) : QObject(parent)
{
    format = avformat_alloc_context();
    pkt = av_packet_alloc();
}

void VideoDecoder::setFile(QString p)
{
    path = p;

    if (avformat_open_input(&format, path.toStdString().c_str(), NULL, NULL) < 0)
    {
        qDebug() << "cant open input";
        return;
    }

    if (avformat_find_stream_info(format, NULL) < 0)
    {
        qDebug() << "cant find streams";
        return;
    }

    for(int i = 0;i < format->nb_streams;i++)
    {
        if(format->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream = i;
            break;
        }
    }

    if(video_stream == -1)
    {
        qDebug() << "no video stream";
        return;
    }

    ctx = format->streams[video_stream]->codec;
    codec = avcodec_find_decoder(ctx->codec_id);

    if (avcodec_open2(ctx, codec, NULL) < 0)
    {
        qDebug() << "cant open codec " << codec->name;
        return;
    }
}

QImage VideoDecoder::extractQImage()
{
    QImage image(ctx->width, ctx->height, QImage::Format_RGB888);

    AVFrame *frame = av_frame_alloc();
    AVPacket *packet = av_packet_alloc();
    int frame_check;

    //av_seek_frame(format, video_stream, index, AVSEEK_FLAG_ANY);

    while (true) {
        if (av_read_frame(format, packet) < 0) {
            qDebug() << "Cant read frame";
            image.fill(QColor(255, 0, 0));
            return image;
        }

        if (packet->stream_index != video_stream) {
            qDebug() << "stream error";
            continue;
        }

        avcodec_decode_video2(ctx, frame, &frame_check, packet);

        if (frame_check) {
            for (int y = 0; y < frame->height; y++) {
                for (int x = 0; x < frame->width; x++) {
                    const int xx = x >> 1;
                    const int yy = y >> 1;
                    const int Y = frame->data[0][y * frame->linesize[0] + x] - 16;
                    const int U = frame->data[1][yy * frame->linesize[1] + xx] - 128;
                    const int V = frame->data[2][yy * frame->linesize[2] + xx] - 128;
                    const int r = qBound(0, (298 * Y + 409 * V + 128) >> 8, 255);
                    const int g = qBound(0, (298 * Y - 100 * U - 208 * V + 128) >> 8, 255);
                    const int b = qBound(0, (298 * Y + 516 * U + 128) >> 8, 255);

                    image.setPixel(x, y, qRgb(r, g, b));
                }
            }
            qDebug() << "end";

            break;
        }
    }

    av_free_packet(packet);
    av_frame_unref(frame);

    return image;
}
