#include <gtest/gtest.h>

#include "AssignmentController.hpp"
#include "stub_database.hpp"

static Assignment makeAssignment(int id, int userId, int courseId, const std::string &title,
                                 const std::string &desc = "") {
	Assignment a;
	a.setId(id).setUserId(userId).setCourseId(courseId).setTitle(title).setDescription(desc).setDueDate("2026-06-01").setPriority(1);
	return a;
}

TEST(AssignmentController, CreateAssignmentFailsWhenDatabaseRejects) {
	StubDatabase db;
	db.createAssignmentSucceeds = false;
	AssignmentController c(db);
	auto r = c.createAssignment("T", "D", 1, 10, "2026-06-15");
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.errorMessage, "Failed to create assignment");
	EXPECT_EQ(r.assignment->getTitle(), "T");
}

TEST(AssignmentController, CreateAssignmentSucceeds) {
	StubDatabase db;
	db.createAssignmentSucceeds = true;
	AssignmentController c(db);
	auto r = c.createAssignment("Essay", "Write five pages", 3, 7, "2026-07-01");
	EXPECT_TRUE(r.success);
	EXPECT_TRUE(r.assignment.has_value());
	EXPECT_EQ(r.assignment->getTitle(), "Essay");
	EXPECT_EQ(r.assignment->getUserId(), 7);
	EXPECT_EQ(r.assignment->getCourseId(), 3);
	EXPECT_EQ(db.assignments.size(), 1u);
}

TEST(AssignmentController, GetAssignmentNotFound) {
	StubDatabase db;
	AssignmentController c(db);
	auto r = c.getAssignment(99);
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.errorMessage, "Assignment not found");
}

TEST(AssignmentController, GetAssignmentFound) {
	StubDatabase db;
	db.assignmentById.emplace(5, makeAssignment(5, 1, 2, "Lab"));
	AssignmentController c(db);
	auto r = c.getAssignment(5);
	EXPECT_TRUE(r.success);
	ASSERT_TRUE(r.assignment.has_value());
	EXPECT_EQ(r.assignment->getTitle(), "Lab");
}

TEST(AssignmentController, UpdateAssignmentNotFound) {
	StubDatabase db;
	AssignmentController c(db);
	auto r = c.updateAssignment(1, "x", "y", 2);
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.errorMessage, "Assignment not found");
}

TEST(AssignmentController, UpdateAssignmentSucceeds) {
	StubDatabase db;
	db.assignmentById.emplace(2, makeAssignment(2, 1, 1, "Old", "Old desc"));
	db.assignments.push_back(db.assignmentById.find(2)->second);
	db.createAssignmentSucceeds = true;
	AssignmentController c(db);
	auto r = c.updateAssignment(2, "New", "New desc", 9);
	EXPECT_TRUE(r.success);
	ASSERT_TRUE(r.assignment.has_value());
	EXPECT_EQ(r.assignment->getTitle(), "New");
	EXPECT_EQ(r.assignment->getPriority(), 9);
}

TEST(AssignmentController, GetAllAssignmentsReturnsUserRows) {
	StubDatabase db;
	db.assignments.push_back(makeAssignment(1, 5, 1, "A"));
	db.assignments.push_back(makeAssignment(2, 5, 1, "B"));
	db.assignments.push_back(makeAssignment(3, 9, 1, "Other user"));
	AssignmentController c(db);
	auto r = c.getAllAssignments(5);
	EXPECT_TRUE(r.success);
	ASSERT_EQ(r.assignments.size(), 2u);
}

TEST(AssignmentController, DeleteAssignment) {
	StubDatabase db;
	Assignment row = makeAssignment(4, 1, 1, "X");
	db.assignments.push_back(row);
	db.assignmentById.emplace(4, row);
	db.deleteAssignmentSucceeds = true;
	AssignmentController c(db);
	auto r = c.deleteAssignment(4);
	EXPECT_TRUE(r.success);
	EXPECT_TRUE(db.assignmentById.find(4) == db.assignmentById.end());
}
