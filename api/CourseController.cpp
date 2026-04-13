//
// Created by Darnyelx on 2026-04-10.
//


#include "CourseController.hpp"
#include "CourseModel.hpp"
#include "DB.hpp"
#include <exception>

GetCoursesResult CourseController::getAllCourses()
{
    GetCoursesResult result;

    try {
        DB& db = DB::getInstance();

        // assuming DB has this method
       std::vector<Course> courses = db.getAllCourses();

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