#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>
#include "authenticationController.h"
#include "movieController.h"
#include "movieView.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
