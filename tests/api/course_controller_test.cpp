#include <gtest/gtest.h>

#include "CourseController.hpp"
#include "stub_database.hpp"

TEST(CourseController, GetAllCoursesSuccess) {
	StubDatabase db;
	Course c1;
	c1.setId(1).setName("CS101");
	Course c2;
	c2.setId(2).setName("MATH200");
	db.courses.push_back(c1);
	db.courses.push_back(c2);
	CourseController controller(db);
	auto r = controller.getAllCourses();
	EXPECT_TRUE(r.success);
	EXPECT_TRUE(r.message.empty());
	ASSERT_EQ(r.courses.size(), 2u);
	EXPECT_EQ(r.courses[0].getName(), "CS101");
}

TEST(CourseController, GetAllCoursesHandlesException) {
	StubDatabase db;
	db.throwOnGetAllCourses = true;
	CourseController controller(db);
	auto r = controller.getAllCourses();
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.message, "database unavailable");
	EXPECT_TRUE(r.courses.empty());
}
