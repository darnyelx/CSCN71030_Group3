#include <string>
#include <vector>
#include "AssignmentModel.hpp"
#include <pqxx/pqxx>

#include "UserModel.hpp"

class DB {

    DB();
    static std::string connectionString;
    pqxx::connection connection;
public:
    static DB& getInstance();
    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;
    pqxx::connection&  getConnection();
	std::vector<Assignment> getAllAssignments();
    std::optional<UserModel> getUserByID(int id);

    bool createUser(UserModel &userModel);
    std::vector<UserModel> getAllUsers();
};
