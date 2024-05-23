# include <QGuiApplication>
# include <QQmlApplicationEngine>
# include "Logger.hpp"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    qmlRegisterType<Logger>("pLogger", 1, 0, "Logger");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/RealTest/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    engine.load(url);

    return app.exec();
}
