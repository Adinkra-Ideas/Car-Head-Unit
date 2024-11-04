#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// #include "src_CPP/Car.hpp"
// #include "src_CPP/Props.hpp"
#include "Car.hpp"
#include "Props.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Car car(&app);
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("car", &car);

    Props & props = car;
    QObject::connect(&app, &QGuiApplication::aboutToQuit, &props, &Props::safeQuitAllThreads);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("head_unit", "Main");

    return app.exec();
}
