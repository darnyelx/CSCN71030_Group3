#include <vector>
#include "CourseModel.hpp"

struct GetCoursesResult {
	bool success;
	std::string message;
	std::vector<Course> courses;
};

class CourseController {
public:
	GetCoursesResult getAllCourses();
};