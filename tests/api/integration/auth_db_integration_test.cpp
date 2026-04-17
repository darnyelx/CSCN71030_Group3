/**
 * @file auth_db_integration_test.cpp
 * @brief Integration tests: `AuthController` register + login against real `DB`.
 *
 * `DB` reads `DBConnectionString` from the environment at process startup (see `DB.cpp`). CMake passes
 * the value from `config.env` when running these tests via CTest. To run the binary manually:
 *   export DBConnectionString="host=... port=... dbname=... user=... password=..."
 */

#include <chrono>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string>

#include "AuthController.hpp"
#include "DB.hpp"
#include "UserModel.hpp"

namespace {

std::string uniqueEmail(const char *prefix) {
    const auto ms = static_cast<unsigned long long>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count());
    return std::string(prefix) + "_" + std::to_string(ms) + "@db_integration.test";
}

bool dbConnectionAvailable() {
    const char *s = std::getenv("DBConnectionString");
    return s != nullptr && s[0] != '\0';
}

void skipIfNoDbEnv() {
    if (!dbConnectionAvailable()) {
        GTEST_SKIP() << "DBConnectionString is not set (run via CTest so CMake injects it from config.env, "
                        "or export it manually).";
    }
}

} // namespace

TEST(AuthDbIntegration, RegisterThenLogin) {
    skipIfNoDbEnv();

    DB &db = DB::getInstance();
    if (!db.getConnection().is_open()) {
        GTEST_SKIP() << "Database connection is not open (check DBConnectionString / network).";
    }

    AuthController auth(db);
    const std::string email = uniqueEmail("it_reg");
    const std::string password = "IntegrationTestPass1!";

    LoginResult reg = auth.registerUser("Integration", "RegisterLogin", email, password);
    ASSERT_TRUE(reg.success) << reg.message;
    ASSERT_TRUE(reg.userModel.has_value());
    const int userId = reg.userModel->getId();
    ASSERT_GT(userId, 0);

    std::string loginEmail = email;
    LoginResult login = auth.login(loginEmail, password);
    EXPECT_TRUE(login.success) << login.message;
    ASSERT_TRUE(login.userModel.has_value());
    EXPECT_EQ(login.userModel->getId(), userId);
    EXPECT_EQ(login.userModel->getEmail(), email);

    UserModel toDelete;
    toDelete.setId(userId);
    ASSERT_TRUE(db.deleteUser(toDelete)) << "Cleanup: delete test user";
}

TEST(AuthDbIntegration, LoginFailsForWrongPassword) {
    skipIfNoDbEnv();

    DB &db = DB::getInstance();
    if (!db.getConnection().is_open()) {
        GTEST_SKIP() << "Database connection is not open.";
    }

    AuthController auth(db);
    const std::string email = uniqueEmail("it_wrongpw");
    const std::string password = "CorrectPass123!";

    LoginResult reg = auth.registerUser("Int", "WrongPw", email, password);
    ASSERT_TRUE(reg.success) << reg.message;
    const int userId = reg.userModel->getId();

    std::string loginEmail = email;
    LoginResult bad = auth.login(loginEmail, "WrongPassword!!!");
    EXPECT_FALSE(bad.success);

    UserModel toDelete;
    toDelete.setId(userId);
    (void)db.deleteUser(toDelete);
}
