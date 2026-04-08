#include <pqxx/pqxx>
#include <string>
#include <vector>
#include "AssignmentModel.hpp"

#include "UserModel.hpp"

class DB {

    DB();
    static std::string connectionString;
    pqxx::connection connection;

public:
    static DB &getInstance();
    DB(const DB &) = delete;
    DB &operator=(const DB &) = delete;
    pqxx::connection &getConnection();
    std::vector<Assignment> getAllAssignments();
    std::optional<UserModel> getUserByID(int id);
    std::optional<UserModel> getUserByEmail(std::string &email);
    std::vector<UserModel> getAllUsers();
    bool createUser(UserModel &userModel);
    bool deleteUser(UserModel &userModel);
    bool createAssignment(Assignment &assignment);
    bool deleteAssignment(Assignment &assignment);
    bool createHelpRequest(HelpRequest &helpRequest);
    bool deleteHelpRequest(HelpRequest &helpRequest);
    std::optional<Assignment> getAssignmentByID(int id);
};
