/**
 * @file models_test.cpp
 * @brief GoogleTest coverage for domain model construction and table names.
 */

#include <gtest/gtest.h>

#include "AssignmentModel.hpp"
#include "CourseModel.hpp"
#include "HelpRequestModel.hpp"
#include "UserModel.hpp"

TEST(UserModel, TableNameAndFluentSetters) {
    UserModel u;
    EXPECT_EQ(u.getTableName(), "users");
    u.setFirstName("Ada").setLastName("Lovelace").setEmail("ada@example.com").setId(42).setPassword("x");
    EXPECT_EQ(u.getFirstName(), "Ada");
    EXPECT_EQ(u.getLastName(), "Lovelace");
    EXPECT_EQ(u.getEmail(), "ada@example.com");
    EXPECT_EQ(u.getId(), 42);
    EXPECT_EQ(u.getPassword(), "x");
}

TEST(Assignment, TableNameAndFields) {
    Assignment a;
    EXPECT_EQ(a.getTableName(), "assignments");
    a.setId(1)
        .setTitle("Read chapter 3")
        .setDescription("Focus on diagrams")
        .setDueDate("2026-05-01")
        .setCourseId(10)
        .setUserId(20)
        .setPriority(2)
        .setStatus("In Progress");
    EXPECT_EQ(a.getId(), 1);
    EXPECT_EQ(a.getTitle(), "Read chapter 3");
    EXPECT_EQ(a.getDescription(), "Focus on diagrams");
    EXPECT_EQ(a.getDueDate(), "2026-05-01");
    EXPECT_EQ(a.getCourseId(), 10);
    EXPECT_EQ(a.getUserId(), 20);
    EXPECT_EQ(a.getPriority(), 2);
    EXPECT_EQ(a.getStatus(), "In Progress");
}

TEST(Course, TableNameAndFields) {
    Course c;
    EXPECT_EQ(c.getTableName(), "courses");
    c.setId(3).setName("CSCN71030").setDescription("Group project").setUserId(7);
    EXPECT_EQ(c.getId(), 3);
    EXPECT_EQ(c.getName(), "CSCN71030");
    EXPECT_EQ(c.getDescription(), "Group project");
    EXPECT_EQ(c.getUserId(), 7);
}

TEST(HelpRequestModel, TableNameAndSetters) {
    HelpRequestModel h(-1, 5, "Need help", "2026-04-13");
    EXPECT_EQ(h.getTableName(), "help_requests");
    EXPECT_EQ(h.getUserId(), 5);
    EXPECT_EQ(h.getMessage(), "Need help");
    EXPECT_EQ(h.getCreatedAt(), "2026-04-13");
    h.setId(99);
    h.setUserId(1);
    h.setAssignmentId(12);
    h.setMessage("Updated");
    h.setRequestStatus("open");
    h.setCreatedAt("2026-04-14");
    EXPECT_EQ(h.getId(), 99);
    EXPECT_EQ(h.getUserId(), 1);
    EXPECT_EQ(h.getAssignmentId(), 12);
    EXPECT_EQ(h.getMessage(), "Updated");
    EXPECT_EQ(h.getRequestStatus(), "open");
    EXPECT_EQ(h.getCreatedAt(), "2026-04-14");
}
