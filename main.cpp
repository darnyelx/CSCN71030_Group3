#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include <qqmlcontext.h>
#include <iostream>
#include <string>

#include <view/Controllers/headers/CourseViewController.hpp>
#include "api/Config.hpp"
#include "api/AssignmentController.hpp"
#include "api/AuthController.hpp"
#include "api/CourseController.hpp"
#include "api/DB.hpp"
#include "api/HelpRequestController.hpp"
#include "view/Controllers/headers/AssignmentViewController.hpp"
#include "view/Controllers/headers/AuthViewController.h"
#include "view/Controllers/headers/HelpRequestViewController.hpp"
#include "view/Models/headers/AssignmentFilterProxyModel.hpp"
#include "view/Models/headers/HelpRequestListModel.hpp"
#include "view/Models/headers/UserViewModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    const std::string configPath =
        QCoreApplication::applicationDirPath().toStdString() + "/config.env";

    if (!Config::load(configPath)) {
        std::cerr << "Could not load config.env from: "
                  << configPath << std::endl;
    }

    const std::string dbconnectionkey = "DBConnectionString";
    std::string dbConnection = Config::get(dbconnectionkey);

    // Optional debug
    std::cout << "DB connection: " << dbConnection << std::endl;
    // std::cout << "Env DB connection: "
    //           << (std::getenv("DB_CONNECTION") ? std::getenv("DB_CONNECTION") : "NOT SET")
    //           << std::endl;

    DB &database = DB::getInstance();
    AuthController authController(database);
    AssignmentController assignmentController(database);
    CourseController courseController(database);
    HelpRequestController helpRequestController(database);

    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/todo_app/Main.qml"));

    AssignmentListModel assignmentListModel;
    CourseListModel courseListModel;
    HelpRequestListModel helpRequestListModel;
    HelpRequestListModel othersHelpRequestListModel;

    AuthViewController authViewController(authController);
    AssignmentViewController assignmentViewController(assignmentController, &assignmentListModel);
    CourseViewController courseViewController(courseController, &courseListModel);
    HelpRequestViewController helpRequestViewController(
        helpRequestController,
        &helpRequestListModel,
        &othersHelpRequestListModel
    );

    engine.rootContext()->setContextProperty("authViewController", &authViewController);
    engine.rootContext()->setContextProperty("assignmentController", &assignmentViewController);
    engine.rootContext()->setContextProperty("courseViewController", &courseViewController);
    engine.rootContext()->setContextProperty("helpRequestController", &helpRequestViewController);

    qmlRegisterType<UserViewModel>("App", 1, 0, "UserViewModel");
    qmlRegisterType<AssignmentViewModel>("App", 1, 0, "AssignmentViewModel");
    qmlRegisterUncreatableType<AssignmentFilterProxyModel>(
        "App", 1, 0, "AssignmentFilterProxyModel",
        QStringLiteral("AssignmentFilterProxyModel is exposed on assignmentController.assignmentFilter"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    engine.load(url);

    return app.exec();
}