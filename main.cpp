#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include <qqmlcontext.h>
#include <view/Controllers/headers/CourseViewController.hpp>

#include "api/DB.hpp"
#include "view/Controllers/headers/AssignmentViewController.hpp"
#include "view/Controllers/headers/AuthViewController.h"
#include "view/Models/headers/UserViewModel.h"

int main(int argc, char *argv[])
{
    DB& instance = DB::getInstance();
    
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/todo_app/Main.qml"));

    // do not trigger "style does not support customization" warnings.
    QQuickStyle::setStyle("Fusion");
    AuthViewController authViewController;
    AssignmentListModel assignmentListModel;
    AssignmentViewController assignmentViewController(&assignmentListModel);
    CourseListModel courseListModel;
    CourseViewController courseViewController(&courseListModel);

    engine.rootContext()->setContextProperty("authViewController", &authViewController);
    engine.rootContext()->setContextProperty("assignmentController", &assignmentViewController);
    engine.rootContext()->setContextProperty("courseViewController", &courseViewController);

    qmlRegisterType<UserViewModel>("App", 1, 0, "UserViewModel");
    qmlRegisterType<AssignmentViewModel>("App", 1, 0, "AssignmentViewModel");



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
