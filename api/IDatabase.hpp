#pragma once

#include <optional>
#include <string>
#include <vector>

class Assignment;
class UserModel;
class HelpRequestModel;
class Course;

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual std::vector<Assignment> getAllAssignments(int userId) = 0;
    virtual std::optional<UserModel> getUserByID(int id) = 0;
    virtual std::optional<UserModel> getUserByEmail(std::string &email) = 0;
    virtual std::vector<UserModel> getAllUsers() = 0;
    virtual bool createUser(UserModel &userModel) = 0;
    virtual bool deleteUser(UserModel &userModel) = 0;
    virtual bool createAssignment(Assignment &assignment) = 0;
    virtual bool deleteAssignment(Assignment &assignment) = 0;
    virtual bool createHelpRequest(HelpRequestModel &helpRequest) = 0;
    virtual std::optional<HelpRequestModel> getHelpRequestById(int id) = 0;
    virtual std::vector<HelpRequestModel> getAllHelpRequests(int userId) = 0;
    virtual std::optional<Assignment> getAssignmentByID(int id) = 0;
    virtual bool deleteHelpRequest(HelpRequestModel &helpRequest) = 0;
    virtual std::vector<Course> getAllCourses() = 0;
};
