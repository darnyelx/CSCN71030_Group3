cmake_minimum_required(VERSION 3.21)

project(todo_app VERSION 0.1 LANGUAGES CXX)

option(TODO_APP_BUILD_TESTS "Build GoogleTest suite for api/" ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)
find_package(libpqxx CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

qt_add_executable(apptodo_app
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
    api/HelpRequestModel.cpp
    api/AssignmentController.cpp
    api/AssignmentQueryController.cpp
    view/Controllers/headers/AssignmentViewController.hpp
    view/Controllers/AssignmentViewController.cpp
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

set_target_properties(apptodo_app PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptodo_app
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE unofficial-sodium::sodium
    PRIVATE libpqxx::pqxx
)

if(TODO_APP_BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
        URL_HASH SHA256=8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(api_tests
        tests/api/models_test.cpp
        tests/api/auth_controller_test.cpp
        tests/api/assignment_controller_test.cpp
        tests/api/course_controller_test.cpp
        tests/api/assignment_query_controller_test.cpp
        tests/api/help_request_controller_test.cpp
    )
    target_include_directories(api_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/api
        ${CMAKE_SOURCE_DIR}/tests/api
    )
    target_sources(api_tests PRIVATE
        api/UserModel.cpp
        api/AssignmentModel.cpp
        api/CourseModel.cpp
        api/HelpRequestModel.cpp
        api/AuthController.cpp
        api/AssignmentController.cpp
        api/AssignmentQueryController.cpp
        api/CourseController.cpp
        api/HelpRequestController.cpp
    )
    target_link_libraries(api_tests PRIVATE
        GTest::gtest_main
        unofficial-sodium::sodium
    )
    set_target_properties(api_tests PROPERTIES AUTOMOC OFF)
    include(GoogleTest)
    gtest_discover_tests(api_tests)
endif()

include(GNUInstallDirs)
install(TARGETS apptodo_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
