/**
 * @file AssignmentQueryController.hpp
 * @brief Read-only search, filter, and ordering helpers over a user's assignments.
 */

#pragma once

#include <string>
#include <vector>
#include "AssignmentModel.hpp"

class IDatabase;

/**
 * @brief Query surface used by tests and future UI features (keyword search, filters, sort).
 * @details Operates on data from `getAllAssignments` then filters/sorts in memory. Some filter APIs
 *          are stubs and return an empty vector until implemented.
 */
class AssignmentQueryController {
public:
	/**
	 * @brief Constructs controller with database dependency.
	 * @param database Must outlive this controller.
	 */
	explicit AssignmentQueryController(IDatabase &database);

	/**
	 * @brief Returns assignments whose title or description contains `keyword` (substring match).
	 * @param userId Owner whose assignments are searched.
	 * @param keyword Needle matched against title and description.
	 * @return Filtered subset; empty if none match.
	 */
	std::vector<Assignment> searchAssignmentsByKeyword(int userId, const std::string &keyword);

	/**
	 * @brief Filters assignments to a single course.
	 * @param userId Owner user id.
	 * @param courseId Course foreign key to match.
	 * @return Assignments with matching `course_id`.
	 */
	std::vector<Assignment> getFilteredAssignmentsByCourse(int userId, int courseId);

	/**
	 * @brief Filters assignments to a single priority value.
	 * @param userId Owner user id.
	 * @param priority Exact priority to match.
	 * @return Matching assignments.
	 */
	std::vector<Assignment> getFilteredAssignmentsByPriority(int userId, int priority);

	/**
	 * @brief Intended to filter by status string; @return Currently always an empty vector (not implemented).
	 */
	std::vector<Assignment> getFilteredAssignmentsByStatus(int userId, const std::string &status);

	/**
	 * @brief Intended to filter by due-date range; @return Currently always an empty vector (not implemented).
	 */
	std::vector<Assignment> getFilteredAssignmentsByDueDateRange(int userId, const std::string &startDate,
	                                                             const std::string &endDate);

	/**
	 * @brief Returns the user’s assignments sorted ascending by `dueDate` string (lexicographic).
	 * @param userId Owner user id.
	 * @return Sorted copy of the assignment list.
	 */
	std::vector<Assignment> getOrderedAssignmentsByDueDate(int userId);

	/**
	 * @brief Returns the user’s assignments sorted descending by priority (higher priority first).
	 * @param userId Owner user id.
	 * @return Sorted copy of the assignment list.
	 */
	std::vector<Assignment> getOrderedAssignmentsByPriority(int userId);

private:
	IDatabase &db_;
};
