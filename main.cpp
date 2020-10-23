#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "videodecoder.h"
#include "previewframe.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<VideoDecoder>("com.video.decoder", 1, 0, "VideoDecoder");
    qmlRegisterType<PreviewFrame>("com.video.preview", 1, 0, "PreviewFrame");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
