//
// Created by Darnyelx on 2026-03-26.
//

#include "DB.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "UserModel.hpp"
#include "AssignmentModel.hpp"

using namespace std;


std::string DB::connectionString = getenv("DBConnectionString");

DB::DB():connection( DB::connectionString ) {
  if (connection.is_open()) {
      std::cout << "Connection opened" << std::endl;
  }
}

DB &DB::getInstance() {
    try {
        static DB instance;
        return instance;
    }catch(std::exception const &e) {
        std::cout << e.what() << std::endl;
    }

}

 pqxx::connection& DB::getConnection() {
     return connection;
}

std::optional<UserModel> DB::getUserByID(int id) {
    try {
        pqxx::connection& connection = getConnection();
        UserModel user;
        if (connection.is_open()) {
            pqxx::work transaction(connection);
            pqxx::result result = transaction.exec("select * from" + user.getTableName() + " where user_id= $1", pqxx::params{transaction, id});
            if (result.empty()) {
                return std::nullopt;
            }else {
                user.setFirstName(result[0]["first_name"].as<std::string>());
                user.setLastName(result[0]["last_name"].as<std::string>());
                user.setEmail(result[0]["email"].as<std::string>());
                user.setId(result[0]["id"].as<int>());
                user.setPassword(result[0]["password"].as<std::string>());
                user.setId(result[0]["id"].as<int>());
                return user;
            }
        }
    }catch(std::exception const &e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }

    return nullopt;
}

#include <vector>
#include <iostream>

std::vector<UserModel> DB::getAllUsers() {
    std::vector<UserModel> users;

    try {
        pqxx::connection& connection = getConnection();
        UserModel user;

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            std::string query = "SELECT * FROM " + user.getTableName();
            pqxx::result result = transaction.exec(query);

            for (auto const& row : result) {
                UserModel userRow;
                userRow.setFirstName(row["first_name"].as<std::string>());
                userRow.setLastName(row["last_name"].as<std::string>());
                userRow.setEmail(row["email"].as<std::string>());
                userRow.setId(row["id"].as<int>());
                userRow.setPassword(row["password"].as<std::string>());

                users.push_back(userRow);
            }
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return users;
}

std::vector<Assignment> DB::getAllAssignments() {
    std::vector<Assignment> assignments;

    try {
        pqxx::connection& connection = getConnection();
        Assignment assignment;

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            std::string query = "SELECT * FROM " + assignment.getTableName();
            pqxx::result result = transaction.exec(query);

            for (auto const& row : result) {
                Assignment assignmentRow;

                assignmentRow.setId(row["id"].as<int>());
                assignmentRow.setTitle(row["title"].as<std::string>());
                assignmentRow.setDescription(row["description"].as<std::string>());
                assignmentRow.setDueDate(row["due_date"].as<std::string>());
                assignmentRow.setCourseId(row["course_id"].as<int>());

                assignments.push_back(assignmentRow);
            }
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return assignments;
}


