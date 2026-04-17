/**
 * @file help_request_controller_test.cpp
 * @brief Tests for help-request create/list flows with `StubDatabase`.
 */

#include <gtest/gtest.h>

#include "HelpRequestController.hpp"
#include "UserModel.hpp"
#include "stub_database.hpp"

TEST(HelpRequestController, CreateFailsWhenDatabaseRejects) {
	StubDatabase db;
	db.createHelpRequestSucceeds = false;
	HelpRequestController c(db);
	auto r = c.createHelpRequest(1, 42, "Need help");
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.errorMessage, "Failed to create help request");
	EXPECT_FALSE(r.helpRequest.has_value());
}

TEST(HelpRequestController, CreateSucceeds) {
	StubDatabase db;
	db.createHelpRequestSucceeds = true;
	HelpRequestController c(db);
	auto r = c.createHelpRequest(7, 3, "Stuck on part B");
	EXPECT_TRUE(r.success);
	ASSERT_TRUE(r.helpRequest.has_value());
	EXPECT_EQ(r.helpRequest->getUserId(), 7);
	EXPECT_EQ(r.helpRequest->getAssignmentId(), 3);
	EXPECT_EQ(r.helpRequest->getMessage(), "Stuck on part B");
	EXPECT_GE(r.helpRequest->getId(), 1);
	EXPECT_FALSE(r.helpRequest->getCreatedAt().empty());
}

TEST(HelpRequestController, GetByIdNotFound) {
	StubDatabase db;
	HelpRequestController c(db);
	auto r = c.getHelpRequestById(999);
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.errorMessage, "Help request not found");
}

TEST(HelpRequestController, GetByIdFound) {
	StubDatabase db;
	HelpRequestModel hr(5, 2, "msg", "2026-04-01");
	hr.setAssignmentId(10);
	db.helpRequestByIdMap.emplace(5, hr);
	HelpRequestController c(db);
	auto r = c.getHelpRequestById(5);
	EXPECT_TRUE(r.success);
	ASSERT_TRUE(r.helpRequest.has_value());
	EXPECT_EQ(r.helpRequest->getMessage(), "msg");
}

TEST(HelpRequestController, GetAllEmptyReturnsSuccessWithEmptyList) {
	StubDatabase db;
	HelpRequestController c(db);
	auto r = c.getAllHelpRequests(1);
	EXPECT_TRUE(r.success);
	EXPECT_TRUE(r.errorMessage.empty());
	EXPECT_TRUE(r.helpRequests.empty());
}

TEST(HelpRequestController, GetAllReturnsUserRows) {
	StubDatabase db;
	HelpRequestModel a(-1, 8, "a", "t1");
	a.setAssignmentId(1);
	HelpRequestModel b(-1, 8, "b", "t2");
	b.setAssignmentId(2);
	db.helpRequests.push_back(a);
	db.helpRequests.push_back(b);
	HelpRequestController c(db);
	auto r = c.getAllHelpRequests(8);
	EXPECT_TRUE(r.success);
	ASSERT_EQ(r.helpRequests.size(), 2u);
}

TEST(HelpRequestController, GetHelpRequestsFromOtherUsersExcludesCurrentUser) {
	StubDatabase db;
	HelpRequestModel mine(-1, 1, "mine", "t1");
	mine.setAssignmentId(10);
	HelpRequestModel other(-1, 9, "other msg", "t2");
	other.setAssignmentId(20);
	db.helpRequests.push_back(mine);
	db.helpRequests.push_back(other);
	UserModel u(9, "Sam", "Jones");
	u.setEmail("sam@example.com");
	db.users.push_back(u);
	HelpRequestController c(db);
	auto r = c.getHelpRequestsFromOtherUsers(1);
	EXPECT_TRUE(r.success);
	ASSERT_EQ(r.helpRequests.size(), 1u);
	EXPECT_EQ(r.helpRequests[0].getUserId(), 9);
	EXPECT_EQ(r.helpRequests[0].getMessage(), "other msg");
	EXPECT_FALSE(r.helpRequests[0].getRaiserDisplayName().empty());
}
