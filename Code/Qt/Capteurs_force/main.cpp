#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SensorBackend.h"
#include "SoleGeometry.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SoleGeometry>("Capteurs_force", 1, 0, "SoleGeometry");

    SensorBackend backend;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("sensorBackend", &backend);
    engine.loadFromModule("Capteurs_force", "Main");


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}