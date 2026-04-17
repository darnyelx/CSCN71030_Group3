/**
 * @file auth_controller_test.cpp
 * @brief Tests for `AuthController` against `StubDatabase`.
 */

#include <gtest/gtest.h>

#include "AuthController.hpp"
#include "stub_database.hpp"

TEST(AuthController, RegisterUserRejectsEmptyFirstName) {
	StubDatabase db;
	AuthController auth(db);
	LoginResult r = auth.registerUser("", "Last", "a@b.co", "secret123");
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.message, "All fields are required");
	EXPECT_FALSE(r.userModel.has_value());
}

TEST(AuthController, RegisterUserRejectsEmptyLastName) {
	StubDatabase db;
	AuthController auth(db);
	LoginResult r = auth.registerUser("First", "", "a@b.co", "secret123");
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.message, "All fields are required");
}

TEST(AuthController, RegisterUserRejectsEmptyEmail) {
	StubDatabase db;
	AuthController auth(db);
	LoginResult r = auth.registerUser("First", "Last", "", "secret123");
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.message, "All fields are required");
}

TEST(AuthController, RegisterUserRejectsEmptyPassword) {
	StubDatabase db;
	AuthController auth(db);
	LoginResult r = auth.registerUser("First", "Last", "a@b.co", "");
	EXPECT_FALSE(r.success);
	EXPECT_EQ(r.message, "All fields are required");
}
