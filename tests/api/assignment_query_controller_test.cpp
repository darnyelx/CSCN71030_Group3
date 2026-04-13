#include <gtest/gtest.h>

#include "AssignmentQueryController.hpp"
#include "stub_database.hpp"

static Assignment A(int id, int userId, int courseId, int priority, std::string due, std::string title,
                  std::string desc = "") {
	Assignment a;
	a.setId(id)
	    .setUserId(userId)
	    .setCourseId(courseId)
	    .setPriority(priority)
	    .setDueDate(std::move(due))
	    .setTitle(std::move(title))
	    .setDescription(std::move(desc));
	return a;
}

TEST(AssignmentQueryController, SearchByKeywordMatchesTitleOrDescription) {
	StubDatabase db;
	db.assignments.push_back(A(1, 1, 10, 1, "2026-01-02", "Project outline", "intro only"));
	db.assignments.push_back(A(2, 1, 10, 1, "2026-01-03", "Draft", "full project spec inside"));
	db.assignments.push_back(A(3, 9, 10, 1, "2026-01-04", "Other user", "outline here"));
	AssignmentQueryController q(db);
	auto byTitle = q.searchAssignmentsByKeyword(1, "outline");
	ASSERT_EQ(byTitle.size(), 1u);
	EXPECT_EQ(byTitle[0].getId(), 1);
	auto byDesc = q.searchAssignmentsByKeyword(1, "spec");
	ASSERT_EQ(byDesc.size(), 1u);
	EXPECT_EQ(byDesc[0].getId(), 2);
}

TEST(AssignmentQueryController, FilterByCourse) {
	StubDatabase db;
	db.assignments.push_back(A(1, 2, 100, 1, "2026-02-01", "a"));
	db.assignments.push_back(A(2, 2, 200, 1, "2026-02-02", "b"));
	AssignmentQueryController q(db);
	auto r = q.getFilteredAssignmentsByCourse(2, 200);
	ASSERT_EQ(r.size(), 1u);
	EXPECT_EQ(r[0].getId(), 2);
}

TEST(AssignmentQueryController, FilterByPriority) {
	StubDatabase db;
	db.assignments.push_back(A(1, 3, 1, 1, "2026-03-01", "low"));
	db.assignments.push_back(A(2, 3, 1, 2, "2026-03-02", "high"));
	AssignmentQueryController q(db);
	auto r = q.getFilteredAssignmentsByPriority(3, 2);
	ASSERT_EQ(r.size(), 1u);
	EXPECT_EQ(r[0].getId(), 2);
}

TEST(AssignmentQueryController, OrderByDueDate) {
	StubDatabase db;
	db.assignments.push_back(A(1, 4, 1, 1, "2026-12-01", "late"));
	db.assignments.push_back(A(2, 4, 1, 1, "2026-01-01", "early"));
	AssignmentQueryController q(db);
	auto r = q.getOrderedAssignmentsByDueDate(4);
	ASSERT_EQ(r.size(), 2u);
	EXPECT_EQ(r[0].getTitle(), "early");
	EXPECT_EQ(r[1].getTitle(), "late");
}

TEST(AssignmentQueryController, OrderByPriorityDescending) {
	StubDatabase db;
	db.assignments.push_back(A(1, 5, 1, 1, "2026-01-01", "low"));
	db.assignments.push_back(A(2, 5, 1, 5, "2026-01-02", "high"));
	AssignmentQueryController q(db);
	auto r = q.getOrderedAssignmentsByPriority(5);
	ASSERT_EQ(r.size(), 2u);
	EXPECT_EQ(r[0].getPriority(), 5);
	EXPECT_EQ(r[1].getPriority(), 1);
}
