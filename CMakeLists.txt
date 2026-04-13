cmake_minimum_required(VERSION 3.21)

project(todo_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)
find_package(libpqxx CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

qt_add_executable(apptodo_app
    main.cpp
        main.cpp
        view/Controllers/headers/AuthViewController.h
        view/Controllers/AuthViewController.cpp
        view/Models/UserViewModel.cpp
        view/Models/headers/UserViewModel.h
        api/AuthController.hpp
        api/AuthController.cpp
        api/DB.hpp
        api/DB.cpp
        api/UserModel.hpp
        api/UserModel.cpp
        api/AssignmentModel.cpp
        api/CourseModel.hpp
        api/CourseModel.cpp
        api/AssignmentController.cpp
        api/AssignmentQueryController.cpp
        view/Controllers/headers/AssignmentViewController.hpp
        view/Controllers/AssignmentViewController.cpp
        view/Controllers/headers/AssignmentViewController.hpp
        view/Models/AssignmentViewModel.cpp
        view/Models/headers/AssignmentViewModel.hpp
        view/Models/AssignmentListModel.cpp
        view/Models/headers/AssignmentListModel.hpp
        view/Models/CourseViewModel.cpp
        view/Models/headers/CourseViewModel.hpp
        view/Models/CourseListModel.cpp
        view/Models/headers/CourseListModel.hpp
        view/Controllers/CourseViewController.cpp
        view/Controllers/headers/CourseViewController.hpp
        api/BaseModel.cpp
        api/CourseController.cpp
        api/CourseController.cpp


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
    PRIVATE unofficial-sodium::sodium
)

target_link_libraries(apptodo_app PRIVATE libpqxx::pqxx)

include(GNUInstallDirs)
install(TARGETS apptodo_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
