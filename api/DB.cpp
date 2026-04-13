//
// Created by Darnyelx on 2026-03-26.
//

#include "DB.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "AssignmentModel.hpp"
#include "UserModel.hpp"
using namespace std;


namespace {
const char *envConnectionString() {
    const char *s = std::getenv("DBConnectionString");
    return (s != nullptr) ? s : "";
}
} // namespace

std::string DB::connectionString = envConnectionString();

DB::DB():connection( DB::connectionString ) {
  if (connection.is_open()) {
      std::cout << "DB connection is opened" << std::endl;
  }
}

DB &DB::getInstance() {
    try {
        static DB instance;
        return instance;
    } catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
    }
}

pqxx::connection &DB::getConnection() { return connection; }

bool DB::createUser(UserModel &user) {
    try {
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return false;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec_params(
                R"(
                INSERT INTO users (first_name, last_name, email, password)
                VALUES ($1, $2, $3, $4)
                ON CONFLICT (email)
                DO UPDATE SET
                    first_name = EXCLUDED.first_name,
                    last_name  = EXCLUDED.last_name,
                    password   = EXCLUDED.password
            )",
                user.getFirstName(), user.getLastName(), user.getEmail(), user.getPassword());

        transaction.commit();

        return result.affected_rows() > 0;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool DB::deleteUser(UserModel &user) {
    try {
        int id = user.getId();
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return false;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec_params("DELETE FROM users WHERE id = $1", id);

        transaction.commit();

        return result.affected_rows() > 0;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

std::optional<UserModel> DB::getUserByID(int id) {
    try {
        pqxx::connection &connection = getConnection();
        UserModel user;
        if (connection.is_open()) {
            pqxx::work transaction(connection);
            pqxx::result result = transaction.exec("select * from " + user.getTableName() + " where user_id= $1",
                                                   pqxx::params{transaction, id});
            if (result.empty()) {
                return std::nullopt;
            } else {
                user.setFirstName(result[0]["first_name"].as<std::string>());
                user.setLastName(result[0]["last_name"].as<std::string>());
                user.setEmail(result[0]["email"].as<std::string>());
                user.setId(result[0]["id"].as<int>());
                user.setPassword(result[0]["password"].as<std::string>());
                user.setId(result[0]["id"].as<int>());
                return user;
            }
        }
    } catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }

    return nullopt;
}


std::optional<UserModel> DB::getUserByEmail(std::string &email) {
    try {
        pqxx::connection &connection = getConnection();
        UserModel user;
        if (connection.is_open()) {
            pqxx::work transaction(connection);
            pqxx::result result = transaction.exec("select * from " + user.getTableName() + " where email= $1",
                                                   pqxx::params{transaction, email});
            if (result.empty()) {
                return std::nullopt;
            } else {
                user.setFirstName(result[0]["first_name"].as<std::string>());
                user.setLastName(result[0]["last_name"].as<std::string>());
                user.setEmail(result[0]["email"].as<std::string>());
                user.setId(result[0]["id"].as<int>());
                user.setPassword(result[0]["password"].as<std::string>());
                user.setId(result[0]["id"].as<int>());
                return user;
            }
        }
    } catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }

    return nullopt;
}


std::vector<UserModel> DB::getAllUsers() {
    std::vector<UserModel> users;

    try {
        pqxx::connection &connection = getConnection();
        UserModel user;

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            std::string query = "SELECT * FROM " + user.getTableName();
            pqxx::result result = transaction.exec(query);

            for (auto const &row: result) {
                UserModel userRow;
                userRow.setFirstName(row["first_name"].as<std::string>());
                userRow.setLastName(row["last_name"].as<std::string>());
                userRow.setEmail(row["email"].as<std::string>());
                userRow.setId(row["id"].as<int>());
                userRow.setPassword(row["password"].as<std::string>());

                users.push_back(userRow);
            }
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return users;
}

std::vector<Assignment> DB::getAllAssignments(int id) {
    std::vector<Assignment> assignments;

    try {
        pqxx::connection &connection = getConnection();
        Assignment assignment;

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            std::string query = "SELECT * FROM " + assignment.getTableName()+" WHERE user_id = $1";
            pqxx::result result = transaction.exec_params(query, id);

            for (auto const &row: result) {
                Assignment assignmentRow;

                assignmentRow.setId(row["id"].as<int>());
                assignmentRow.setUserId(row["user_id"].as<int>());
                assignmentRow.setTitle(row["title"].as<std::string>());
                assignmentRow.setDescription(row["description"].as<std::string>());
                assignmentRow.setDueDate(row["due_date"].as<std::string>());
                assignmentRow.setCourseId(row["course_id"].as<int>());

                assignments.push_back(assignmentRow);
            }
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return assignments;
}

bool DB::createAssignment(Assignment &assignment) {
    try {
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return false;
        }

        pqxx::work transaction(connection);

        pqxx::result result;

        if (assignment.getId() > 0) {
            result = transaction.exec_params(
                R"(
                    UPDATE assignments
                    SET
                        title = $1,
                        description = $2,
                        due_date = $3,
                        course_id = $4,
                        user_id = $5,
                        priority = $6
                    WHERE id = $7
                )",
                assignment.getTitle(),
                assignment.getDescription(),
                assignment.getDueDate(),
                assignment.getCourseId(),
                assignment.getUserId(),
                assignment.getPriority(),
                assignment.getId()
            );
        } else {
            result = transaction.exec_params(
                R"(
                    INSERT INTO assignments
                    (
                        title,
                        description,
                        due_date,
                        course_id,
                        user_id,
                        priority
                    )
                    VALUES
                    (
                        $1, $2, $3, $4, $5, $6
                    )
                )",
                assignment.getTitle(),
                assignment.getDescription(),
                assignment.getDueDate(),
                assignment.getCourseId(),
                assignment.getUserId(),
                assignment.getPriority() == 1 ? "HIGH":"LOW"
            );
        }

        transaction.commit();
        return result.affected_rows() > 0;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool DB::deleteAssignment(Assignment &assignment) {
    int id = assignment.getId();
    try {
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return false;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec_params("DELETE FROM assignments WHERE id = $1", id);

        transaction.commit();

        return result.affected_rows() > 0;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

std::optional<Assignment> DB::getAssignmentByID(int id) {
    try {
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return std::nullopt;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec_params("SELECT * FROM assignments WHERE id = $1", id);

        if (result.empty()) {
            return std::nullopt;
        }

        Assignment assignment;
        assignment.setId(result[0]["id"].as<int>());
        assignment.setUserId(result[0]["user_id"].as<int>());
        assignment.setTitle(result[0]["title"].as<std::string>());
        assignment.setDescription(result[0]["description"].as<std::string>());
        assignment.setDueDate(result[0]["due_date"].as<std::string>());
        assignment.setCourseId(result[0]["course_id"].as<int>());
        assignment.setPriority(result[0]["priority"].as<int>());

        return assignment;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }
}

std::vector<HelpRequestModel> DB::getAllHelpRequests(int id) {
    std::vector<HelpRequestModel> helpRequests;

    try {
        pqxx::connection &connection = getConnection();

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            std::string query = "SELECT * FROM help_requests WHERE user_id = $1";
            pqxx::result result = transaction.exec_params(query, id);

            for (auto const &row: result) {
                HelpRequestModel helpRequestRow;
                helpRequestRow.setId(row["id"].as<int>());
                helpRequestRow.setUserId(row["user_id"].as<int>());
                helpRequestRow.setAssignmentId(row["assignment_id"].as<int>());
                helpRequestRow.setMessage(row["message"].as<std::string>());
                helpRequestRow.setCreatedAt(row["created_at"].as<std::string>());

                helpRequests.push_back(helpRequestRow);
            }
            return helpRequests;
        }
        throw std::runtime_error("Connection closed");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return helpRequests;
}
std::optional<HelpRequestModel> DB::getHelpRequestById(int id) {
	try {
		pqxx::connection &connection = getConnection();

		if (!connection.is_open()) {
			std::cout << "Connection closed" << std::endl;
			return std::nullopt;
		}

		pqxx::work transaction(connection);
		pqxx::result result = transaction.exec_params("SELECT * FROM help_requests WHERE id = $1", id);

		if (result.empty()) {
			return std::nullopt;
		}

		HelpRequestModel hr;
		hr.setId(result[0]["id"].as<int>());
		hr.setUserId(result[0]["user_id"].as<int>());
		hr.setAssignmentId(result[0]["assignment_id"].as<int>());
		hr.setMessage(result[0]["message"].as<std::string>());
		hr.setCreatedAt(result[0]["created_at"].as<std::string>());

		return hr;

	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return std::nullopt;
	}
}

bool DB::createHelpRequest(HelpRequestModel &helpRequest) {
    try {
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return false;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec_params(
                R"(
                INSERT INTO help_requests
                (
                    user_id,
                    assignment_id,
                    message,
                    created_at
                )
                VALUES
                (
                    $1, $2, $3, $4
                )
            )",
                helpRequest.getUserId(), helpRequest.getAssignmentId(), helpRequest.getMessage(),
                helpRequest.getCreatedAt());

        transaction.commit();
        return result.affected_rows() > 0;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool DB::deleteHelpRequest(HelpRequestModel &helpRequest) {
    int id = helpRequest.getId();
    try {
        pqxx::connection &connection = getConnection();

        if (!connection.is_open()) {
            std::cout << "Connection closed" << std::endl;
            return false;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec_params("DELETE FROM help_requests WHERE id = $1", id);

        transaction.commit();
        return result.affected_rows() > 0;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}
std::vector<Course> DB::getAllCourses()
{
    std::vector<Course> courses;

    try {
        pqxx::connection& conn = getConnection(); // your existing method
        pqxx::work txn(conn);

        pqxx::result result = txn.exec(
            "SELECT id, name FROM courses ORDER BY name ASC"
        );

        for (const auto& row : result) {
            Course course;

            course.setId(row["id"].as<int>());
            course.setName(row["name"].as<std::string>());

            courses.push_back(course);
        }

        txn.commit();

    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to fetch courses: ") + e.what());
    }

    return courses;
}


