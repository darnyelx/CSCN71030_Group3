/**
 * @file CourseController.hpp
 * @brief Fetches the global course catalog from the database.
 */

#pragma once

#include <string>
#include <vector>
#include "CourseModel.hpp"

class IDatabase;

/**
 * @brief Result of `getAllCourses` with success flag and message for errors.
 */
struct GetCoursesResult {
	bool success; /**< false when an exception was caught (e.g. DB unavailable). */
	std::string message; /**< Empty on success; otherwise exception `what()` or similar. */
	std::vector<Course> courses; /**< Catalog rows on success; empty on failure. */
};

/**
 * @brief Thin wrapper over `IDatabase::getAllCourses` with exception-to-message mapping.
 */
class CourseController {
public:
	/**
	 * @brief Constructs controller with database dependency.
	 * @param database Must outlive this controller.
	 */
	explicit CourseController(IDatabase &database);

	/**
	 * @brief Loads the full course list exposed by the database layer.
	 * @return `GetCoursesResult` with courses on success; on exception, `success` false and `message` set.
	 */
	GetCoursesResult getAllCourses();

private:
	IDatabase &db_;
};
