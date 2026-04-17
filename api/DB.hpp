/**
 * @file DB.hpp
 * @brief Singleton `IDatabase` implementation using libpqxx.
 */

#pragma once

#include <pqxx/pqxx>
#include <string>
#include <vector>

#include "AssignmentModel.hpp"
#include "CourseModel.hpp"
#include "HelpRequestModel.hpp"
#include "IDatabase.hpp"
#include "UserModel.hpp"

/**
 * @brief Process-wide database access: one `pqxx::connection`, implements all `IDatabase` queries.
 * @details The singleton reads `connectionString` from the `DBConnectionString` environment variable
 *          at process startup (set `Config::load` / `config.env` before first use so the variable is populated).
 *          Copying is disabled to preserve a single connection lifecycle.
 */
class DB : public IDatabase {
    /**
     * @brief Opens the libpqxx connection using `connectionString` and prepares the singleton instance.
     * @details Not callable publicly; use `getInstance()` exactly once per process for shared access.
     */
    DB();
    static std::string connectionString;
    pqxx::connection connection;

public:
    /**
     * @brief Returns the unique `DB` instance, constructing it on first use.
     * @return Reference to the singleton; connection is opened using `connectionString`.
     */
    static DB &getInstance();
    DB(const DB &) = delete;
    DB &operator=(const DB &) = delete;

    /**
     * @brief Exposes the underlying libpqxx connection for advanced queries or transactions.
     * @return Reference to the active `pqxx::connection`.
     */
    pqxx::connection &getConnection();

    /** @copydoc IDatabase::getAllAssignments */
    std::vector<Assignment> getAllAssignments(int userId) override;
    /** @copydoc IDatabase::getUserByID */
    std::optional<UserModel> getUserByID(int id) override;
    /** @copydoc IDatabase::getUserByEmail */
    std::optional<UserModel> getUserByEmail(std::string &email) override;
    /** @copydoc IDatabase::getAllUsers */
    std::vector<UserModel> getAllUsers() override;
    /** @copydoc IDatabase::createUser */
    bool createUser(UserModel &userModel) override;
    /** @copydoc IDatabase::deleteUser */
    bool deleteUser(UserModel &userModel) override;
    /** @copydoc IDatabase::createAssignment */
    bool createAssignment(Assignment &assignment) override;
    /** @copydoc IDatabase::deleteAssignment */
    bool deleteAssignment(Assignment &assignment) override;
    /** @copydoc IDatabase::createHelpRequest */
    bool createHelpRequest(HelpRequestModel &helpRequest) override;
    /** @copydoc IDatabase::getHelpRequestById */
    std::optional<HelpRequestModel> getHelpRequestById(int id) override;
    /** @copydoc IDatabase::getAllHelpRequests */
    std::vector<HelpRequestModel> getAllHelpRequests(int userId) override;
    /** @copydoc IDatabase::getHelpRequestsFromOtherUsers */
    std::vector<HelpRequestModel> getHelpRequestsFromOtherUsers(int userId) override;
    /** @copydoc IDatabase::getAssignmentByID */
    std::optional<Assignment> getAssignmentByID(int id) override;
    /** @copydoc IDatabase::deleteHelpRequest */
    bool deleteHelpRequest(HelpRequestModel &helpRequest) override;
    /** @copydoc IDatabase::getAllCourses */
    std::vector<Course> getAllCourses() override;
};
