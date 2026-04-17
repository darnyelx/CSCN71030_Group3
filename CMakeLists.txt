cmake_minimum_required(VERSION 3.21)

project(todo_app VERSION 0.1 LANGUAGES CXX)

option(TODO_APP_BUILD_TESTS "Build GoogleTest suite for api/" ON)
option(TODO_APP_DB_INTEGRATION_TESTS "Build api_integration_tests (Auth register/login vs real DB; needs config.env or cache override)" OFF)
set(TODO_APP_DB_CONNECTION_STRING "" CACHE STRING "Optional: libpq connection string for api_integration_tests (overrides parsing config.env)")

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
    api/HelpRequestController.cpp
    view/Controllers/headers/AssignmentViewController.hpp
    view/Controllers/AssignmentViewController.cpp
    view/Models/AssignmentViewModel.cpp
    view/Models/headers/AssignmentViewModel.hpp
    view/Models/AssignmentListModel.cpp
    view/Models/headers/AssignmentListModel.hpp
    view/Models/AssignmentFilterProxyModel.cpp
    view/Models/headers/AssignmentFilterProxyModel.hpp
    view/Models/CourseViewModel.cpp
    view/Models/headers/CourseViewModel.hpp
    view/Models/CourseListModel.cpp
    view/Models/headers/CourseListModel.hpp
    view/Controllers/CourseViewController.cpp
    view/Controllers/headers/CourseViewController.hpp
    view/Models/HelpRequestViewModel.cpp
    view/Models/headers/HelpRequestViewModel.hpp
    view/Models/HelpRequestListModel.cpp
    view/Models/headers/HelpRequestListModel.hpp
    view/Controllers/HelpRequestViewController.cpp
    view/Controllers/headers/HelpRequestViewController.hpp
    api/CourseController.cpp
        api/Config.cpp
        api/Config.hpp
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

    if(TODO_APP_DB_INTEGRATION_TESTS)
        # Value for CTest: read DBConnectionString from config.env (same key as the app). Optional override: -DTODO_APP_DB_CONNECTION_STRING=...
        set(TODO_APP_INTEGRATION_DB_CONN "")
        if(TODO_APP_DB_CONNECTION_STRING)
            set(TODO_APP_INTEGRATION_DB_CONN "${TODO_APP_DB_CONNECTION_STRING}")
        elseif(EXISTS "${CMAKE_SOURCE_DIR}/config.env")
            file(STRINGS "${CMAKE_SOURCE_DIR}/config.env" _todo_app_config_lines)
            foreach(_todo_app_ln IN LISTS _todo_app_config_lines)
                string(STRIP "${_todo_app_ln}" _todo_app_ln)
                if(_todo_app_ln MATCHES "^#" OR _todo_app_ln STREQUAL "")
                    continue()
                endif()
                if(_todo_app_ln MATCHES "^DBConnectionString[ \t]*=(.*)$")
                    set(TODO_APP_INTEGRATION_DB_CONN "${CMAKE_MATCH_1}")
                    string(STRIP "${TODO_APP_INTEGRATION_DB_CONN}" TODO_APP_INTEGRATION_DB_CONN)
                    break()
                endif()
            endforeach()
        endif()

        add_executable(api_integration_tests
            tests/api/integration/auth_db_integration_test.cpp
        )
        target_include_directories(api_integration_tests PRIVATE
            ${CMAKE_SOURCE_DIR}/api
        )
        target_sources(api_integration_tests PRIVATE
            api/DB.cpp
            api/UserModel.cpp
            api/AssignmentModel.cpp
            api/CourseModel.cpp
            api/HelpRequestModel.cpp
            api/AuthController.cpp
        )
        target_link_libraries(api_integration_tests PRIVATE
            GTest::gtest_main
            unofficial-sodium::sodium
            libpqxx::pqxx
        )
        set_target_properties(api_integration_tests PROPERTIES AUTOMOC OFF)

        if(NOT TODO_APP_INTEGRATION_DB_CONN STREQUAL "")
            string(LENGTH "${TODO_APP_INTEGRATION_DB_CONN}" _dbc_len)
            message(STATUS "api_integration_tests: DBConnectionString for CTest is set (length ${_dbc_len}, not printed).")
            gtest_discover_tests(api_integration_tests
                PROPERTIES ENVIRONMENT "DBConnectionString=${TODO_APP_INTEGRATION_DB_CONN}"
            )
        else()
            message(WARNING "api_integration_tests: could not read DBConnectionString from config.env; tests will skip unless you export DBConnectionString before running the binary.")
            gtest_discover_tests(api_integration_tests)
        endif()
    endif()
endif()

include(GNUInstallDirs)
install(TARGETS apptodo_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_custom_command(TARGET apptodo_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.env
        $<TARGET_FILE_DIR:apptodo_app>/config.env
)