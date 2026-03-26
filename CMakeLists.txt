cmake_minimum_required(VERSION 3.16)

project(todo_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)


qt_add_executable(apptodo_app
    main.cpp
        main.cpp
        view/Controllers/headers/AuthViewController.h
        view/Controllers/AuthViewController.cpp
        view/Models/UserViewModel.cpp
        view/Models/headers/UserViewModel.h
        api/AuthController.hpp
        api/AuthController.cpp
        api/UserModel.hpp
        api/UserModel.cpp

)

qt_add_qml_module(apptodo_app
    URI todo_app
    VERSION 1.0
    QML_FILES
        Main.qml
        view/AssignmentCoordinatorView.qml
        view/LoginView.qml
        view/Store/UserStore.qml
        view/RegisterView.qml
        view/Store/Routes.qml
    RESOURCES
        view/Store/qmldir

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptodo_app PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptodo_app
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptodo_app
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS apptodo_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
