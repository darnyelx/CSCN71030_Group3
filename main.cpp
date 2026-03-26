#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>
#include <QtQuickControls2/QQuickStyle>
#include "view/Controllers/headers/AuthViewController.h"
#include "view/Models/headers/UserViewModel.h"
#include "api/DB.hpp"

int main(int argc, char *argv[])
{
    DB& instance = DB::getInstance();
    
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/todo_app/Main.qml"));

    // do not trigger "style does not support customization" warnings.
    QQuickStyle::setStyle("Fusion");
    AuthViewController authViewController;
    engine.rootContext()->setContextProperty("authViewController", &authViewController);
    qmlRegisterType<UserViewModel>("App", 1, 0, "UserViewModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
