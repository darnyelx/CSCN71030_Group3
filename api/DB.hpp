#pragma once

#include <pqxx/pqxx>
#include <string>
#include <vector>

#include "AssignmentModel.hpp"
#include "CourseModel.hpp"
#include "HelpRequestModel.hpp"
#include "IDatabase.hpp"
#include "UserModel.hpp"

class DB : public IDatabase {
    DB();
    static std::string connectionString;
    pqxx::connection connection;

public:
    static DB &getInstance();
    DB(const DB &) = delete;
    DB &operator=(const DB &) = delete;

    pqxx::connection &getConnection();

    std::vector<Assignment> getAllAssignments(int id) override;
    std::optional<UserModel> getUserByID(int id) override;
    std::optional<UserModel> getUserByEmail(std::string &email) override;
    std::vector<UserModel> getAllUsers() override;
    bool createUser(UserModel &userModel) override;
    bool deleteUser(UserModel &userModel) override;
    bool createAssignment(Assignment &assignment) override;
    bool deleteAssignment(Assignment &assignment) override;
    bool createHelpRequest(HelpRequestModel &helpRequest) override;
    std::optional<HelpRequestModel> getHelpRequestById(int id) override;
    std::vector<HelpRequestModel> getAllHelpRequests(int id) override;
    std::optional<Assignment> getAssignmentByID(int id) override;
    bool deleteHelpRequest(HelpRequestModel &helpRequest) override;
    std::vector<Course> getAllCourses() override;
};
