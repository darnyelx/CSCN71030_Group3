#include <gtest/gtest.h>

#include "HelpRequestController.hpp"
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

TEST(HelpRequestController, GetAllEmptyYieldsFailurePayload) {
	StubDatabase db;
	HelpRequestController c(db);
	auto r = c.getAllHelpRequests(1);
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.errorMessage, "No help requests found");
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
