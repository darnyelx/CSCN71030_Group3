/**
 * @file CourseController.cpp
 * @brief Loads all courses via `IDatabase::getAllCourses` into `GetCoursesResult`.
 */

#include "CourseController.hpp"
#include "CourseModel.hpp"
#include "IDatabase.hpp"
#include <exception>

CourseController::CourseController(IDatabase &database) : db_(database) {}

GetCoursesResult CourseController::getAllCourses()
{
    GetCoursesResult result;

    try {
       std::vector<Course> courses = db_.getAllCourses();

      return {
          true,
          "",
          courses
      };


    } catch (const std::exception& e) {
        result.success = false;
        result.message = e.what();
        result.courses = std::vector<Course>{};
        return result;
    }

}