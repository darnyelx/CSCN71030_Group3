#pragma once

#include <string>
#include <vector>
#include "AssignmentModel.hpp"

class IDatabase;

class AssignmentQueryController {
public:
	explicit AssignmentQueryController(IDatabase &database);

	std::vector<Assignment> searchAssignmentsByKeyword(int userId, const std::string &keyword);

	std::vector<Assignment> getFilteredAssignmentsByCourse(int userId, int courseId);
	std::vector<Assignment> getFilteredAssignmentsByPriority(int userId, int priority);
	std::vector<Assignment> getFilteredAssignmentsByStatus(int userId, const std::string &status);
	std::vector<Assignment> getFilteredAssignmentsByDueDateRange(int userId, const std::string &startDate,
	                                                             const std::string &endDate);

	std::vector<Assignment> getOrderedAssignmentsByDueDate(int userId);
	std::vector<Assignment> getOrderedAssignmentsByPriority(int userId);

private:
	IDatabase &db_;
};
