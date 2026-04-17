/**
 * @file DB.cpp
 * @brief `DB` singleton: connection string from env/config, SQL for `IDatabase` operations.
 */

#include "DB.hpp"
#include <cctype>
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

std::string toDbPriority(int priority) {
    return priority >= 3 ? "HIGH" : "LOW";
}

int fromDbPriority(const pqxx::row &row) {
    const std::string raw = row["priority"].as<std::string>();
    if (raw == "HIGH") {
        return 3;
    }
    if (raw == "LOW") {
        return 1;
    }

    try {
        return std::stoi(raw);
    } catch (...) {
        return 1;
    }
}

/** Maps UI labels to DB values expected by assignments_status_check (typically snake_case). */
std::string toDbAssignmentStatus(const std::string &ui) {
    std::string s;
    s.reserve(ui.size());
    for (unsigned char c : ui) {
        s.push_back(static_cast<char>(std::tolower(c)));
    }
    if (s.empty()) {
        return "pending";
    }
    if (s == "pending") {
        return "pending";
    }
    if (s == "in progress" || s == "in_progress" || s == "inprogress") {
        return "in_progress";
    }
    if (s == "completed") {
        return "completed";
    }
    return "pending";
}

/** Maps DB status strings back to QML-friendly labels. */
std::string fromDbAssignmentStatus(const std::string &db) {
    std::string s;
    s.reserve(db.size());
    for (unsigned char c : db) {
        s.push_back(static_cast<char>(std::tolower(c)));
    }
    if (s == "in_progress" || s == "in progress") {
        return "In Progress";
    }
    if (s == "completed") {
        return "Completed";
    }
    if (s == "pending") {
        return "Pending";
    }
    return db;
}
} // namespace

std::string DB::connectionString(envConnectionString());

DB::DB() : connection(DB::connectionString) {
    if (connection.is_open()) {
        std::cout << "DB connection is opened" << std::endl;
    }
}

DB &DB::getInstance() {
    static DB instance;
    return instance;
}

pqxx::connection &DB::getConnection() {
    if (connection.is_open()) {

    } else {
        DB::connection = pqxx::connection(connectionString);
    }
    return connection;
}

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

std::vector<Assignment> DB::getAllAssignments(int userId) {
    std::vector<Assignment> assignments;

    try {
        pqxx::connection &connection = getConnection();

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            const std::string query =
                "SELECT a.id, a.user_id, a.title, a.description, a.due_date, a.course_id, a.priority, "
                "a.status, "
                "COALESCE(c.name, '') AS course_name "
                "FROM assignments a "
                "LEFT JOIN courses c ON c.id = a.course_id "
                "WHERE a.user_id = $1";
            pqxx::result result = transaction.exec_params(query, userId);

            for (auto const &row: result) {
                Assignment assignmentRow;

                assignmentRow.setId(row["id"].as<int>());
                assignmentRow.setUserId(row["user_id"].as<int>());
                assignmentRow.setTitle(row["title"].as<std::string>());
                assignmentRow.setDescription(row["description"].as<std::string>());
                assignmentRow.setDueDate(row["due_date"].as<std::string>());
                assignmentRow.setCourseId(row["course_id"].as<int>());
                assignmentRow.setPriority(fromDbPriority(row));
                if (row["status"].is_null()) {
                    assignmentRow.setStatus("Pending");
                } else {
                    assignmentRow.setStatus(fromDbAssignmentStatus(row["status"].as<std::string>()));
                }
                assignmentRow.setCourseName(row["course_name"].as<std::string>());

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
            std::cout << "Assignment ID " << assignment.getId() << std::endl;
            result = transaction.exec_params(
                R"(
                    UPDATE assignments
                    SET
                        title = $1,
                        description = $2,
                        due_date = $3,
                        course_id = $4,
                        user_id = $5,
                        priority = $6,
                        status = $7
                    WHERE id = $8
                )",
                assignment.getTitle(),
                assignment.getDescription(),
                assignment.getDueDate(),
                assignment.getCourseId(),
                assignment.getUserId(),
                toDbPriority(assignment.getPriority()),
                toDbAssignmentStatus(assignment.getStatus()),
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
                        priority,
                        status
                    )
                    VALUES
                    (
                        $1, $2, $3, $4, $5, $6, $7
                    )
                )",
                assignment.getTitle(),
                assignment.getDescription(),
                assignment.getDueDate(),
                assignment.getCourseId(),
                assignment.getUserId(),
                toDbPriority(assignment.getPriority()),
                toDbAssignmentStatus(assignment.getStatus())
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

        pqxx::result result = transaction.exec_params(
            "SELECT a.id, a.user_id, a.title, a.description, a.due_date, a.course_id, a.priority, "
            "a.status, "
            "COALESCE(c.name, '') AS course_name "
            "FROM assignments a "
            "LEFT JOIN courses c ON c.id = a.course_id "
            "WHERE a.id = $1",
            id);

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
        assignment.setPriority(fromDbPriority(result[0]));
        if (result[0]["status"].is_null()) {
            assignment.setStatus("Pending");
        } else {
            assignment.setStatus(fromDbAssignmentStatus(result[0]["status"].as<std::string>()));
        }
        assignment.setCourseName(result[0]["course_name"].as<std::string>());

        return assignment;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }
}

std::vector<HelpRequestModel> DB::getAllHelpRequests(int userId) {
    std::vector<HelpRequestModel> helpRequests;

    try {
        pqxx::connection &connection = getConnection();

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            std::string query = "SELECT * FROM help_requests WHERE user_id = $1";
            pqxx::result result = transaction.exec_params(query, userId);

            for (auto const &row: result) {
                HelpRequestModel helpRequestRow;
                helpRequestRow.setId(row["id"].as<int>());
                helpRequestRow.setUserId(row["user_id"].as<int>());
                if (row["assignment_id"].is_null()) {
                    helpRequestRow.setAssignmentId(-1);
                } else {
                    helpRequestRow.setAssignmentId(row["assignment_id"].as<int>());
                }
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

std::vector<HelpRequestModel> DB::getHelpRequestsFromOtherUsers(int userId) {
    std::vector<HelpRequestModel> helpRequests;

    try {
        pqxx::connection &connection = getConnection();

        if (connection.is_open()) {
            pqxx::work transaction(connection);

            const std::string query =
                "SELECT hr.id, hr.user_id, hr.assignment_id, hr.message, hr.created_at, "
                "COALESCE("
                "NULLIF(TRIM(BOTH ' ' FROM (COALESCE(TRIM(u.first_name), '') || ' ' || "
                "COALESCE(TRIM(u.last_name), ''))), ''), "
                "u.email, "
                "'User #' || hr.user_id::text) AS raiser_name "
                "FROM help_requests hr "
                "LEFT JOIN users u ON u.id = hr.user_id "
                "WHERE hr.user_id <> $1 "
                "ORDER BY hr.created_at DESC";

            pqxx::result result = transaction.exec_params(query, userId);

            for (const auto &row : result) {
                HelpRequestModel helpRequestRow;
                helpRequestRow.setId(row["id"].as<int>());
                helpRequestRow.setUserId(row["user_id"].as<int>());
                if (row["assignment_id"].is_null()) {
                    helpRequestRow.setAssignmentId(-1);
                } else {
                    helpRequestRow.setAssignmentId(row["assignment_id"].as<int>());
                }
                helpRequestRow.setMessage(row["message"].as<std::string>());
                helpRequestRow.setCreatedAt(row["created_at"].as<std::string>());
                helpRequestRow.setRaiserDisplayName(row["raiser_name"].as<std::string>());
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
		if (result[0]["assignment_id"].is_null()) {
			hr.setAssignmentId(-1);
		} else {
			hr.setAssignmentId(result[0]["assignment_id"].as<int>());
		}
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
                    $1, NULLIF($2::int, -1), $3, $4::timestamp
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


