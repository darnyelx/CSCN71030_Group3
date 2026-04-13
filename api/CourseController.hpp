#pragma once

#include <string>
#include <vector>
#include "CourseModel.hpp"

class IDatabase;

struct GetCoursesResult {
	bool success;
	std::string message;
	std::vector<Course> courses;
};

class CourseController {
public:
	explicit CourseController(IDatabase &database);

	GetCoursesResult getAllCourses();

private:
	IDatabase &db_;
};
