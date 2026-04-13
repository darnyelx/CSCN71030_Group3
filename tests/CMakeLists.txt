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
    api/models_test.cpp
    api/auth_controller_test.cpp
    api/assignment_controller_test.cpp
    api/course_controller_test.cpp
    api/assignment_query_controller_test.cpp
    api/help_request_controller_test.cpp
)

target_include_directories(api_tests PRIVATE
    "${CMAKE_SOURCE_DIR}/api"
    "${CMAKE_SOURCE_DIR}/tests/api"
)

target_sources(api_tests PRIVATE
    "${CMAKE_SOURCE_DIR}/api/UserModel.cpp"
    "${CMAKE_SOURCE_DIR}/api/AssignmentModel.cpp"
    "${CMAKE_SOURCE_DIR}/api/CourseModel.cpp"
    "${CMAKE_SOURCE_DIR}/api/HelpRequestModel.cpp"
    "${CMAKE_SOURCE_DIR}/api/AuthController.cpp"
    "${CMAKE_SOURCE_DIR}/api/AssignmentController.cpp"
    "${CMAKE_SOURCE_DIR}/api/AssignmentQueryController.cpp"
    "${CMAKE_SOURCE_DIR}/api/CourseController.cpp"
    "${CMAKE_SOURCE_DIR}/api/HelpRequestController.cpp"
)

target_link_libraries(api_tests PRIVATE
    GTest::gtest_main
    unofficial-sodium::sodium
)

set_target_properties(api_tests PROPERTIES AUTOMOC OFF)

include(GoogleTest)
gtest_discover_tests(api_tests)
