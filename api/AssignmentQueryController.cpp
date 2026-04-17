/**
 * @file AssignmentQueryController.cpp
 * @brief In-memory filtering/sorting helpers over vectors from `IDatabase` (tests and future UI).
 */

#include "AssignmentQueryController.hpp"
#include "IDatabase.hpp"
#include <algorithm>
#include <iterator>
#include <list>

namespace {

std::vector<Assignment> getBaseUserAssignments(IDatabase &db, int userId) {
	std::vector<Assignment> allAssignments = db.getAllAssignments(userId);
	std::vector<Assignment> userAssignments;

	std::copy_if(allAssignments.begin(), allAssignments.end(), std::back_inserter(userAssignments),
	             [userId](const Assignment &a) { return a.getUserId() == userId; });

	return userAssignments;
}

} // namespace

AssignmentQueryController::AssignmentQueryController(IDatabase &database) : db_(database) {}

std::vector<Assignment> AssignmentQueryController::searchAssignmentsByKeyword(int userId,
                                                                                const std::string &keyword) {
	std::vector<Assignment> userAssignments = getBaseUserAssignments(db_, userId);
	std::vector<Assignment> filtered;

	std::copy_if(userAssignments.begin(), userAssignments.end(), std::back_inserter(filtered),
	             [&keyword](const Assignment &a) {
		             bool inTitle = a.getTitle().find(keyword) != std::string::npos;
		             bool inDesc = a.getDescription().find(keyword) != std::string::npos;
		             return inTitle || inDesc;
	             });

	return filtered;
}

std::vector<Assignment> AssignmentQueryController::getFilteredAssignmentsByCourse(int userId, int courseId) {
	auto userAssignments = getBaseUserAssignments(db_, userId);
	std::vector<Assignment> filtered;
	std::copy_if(userAssignments.begin(), userAssignments.end(), std::back_inserter(filtered),
	             [courseId](const Assignment &a) { return a.getCourseId() == courseId; });
	return filtered;
}

std::vector<Assignment> AssignmentQueryController::getFilteredAssignmentsByPriority(int userId, int priority) {
	auto userAssignments = getBaseUserAssignments(db_, userId);
	std::vector<Assignment> filtered;
	std::copy_if(userAssignments.begin(), userAssignments.end(), std::back_inserter(filtered),
	             [priority](const Assignment &a) { return a.getPriority() == priority; });
	return filtered;
}

std::vector<Assignment> AssignmentQueryController::getFilteredAssignmentsByStatus(int, const std::string &) {
	return {};
}

std::vector<Assignment> AssignmentQueryController::getFilteredAssignmentsByDueDateRange(int, const std::string &,
                                                                                        const std::string &) {
	return {};
}

std::vector<Assignment> AssignmentQueryController::getOrderedAssignmentsByDueDate(int userId) {
	std::vector<Assignment> v = getBaseUserAssignments(db_, userId);
	std::list<Assignment> order(v.begin(), v.end());
	order.sort([](const Assignment &a, const Assignment &b) { return a.getDueDate() < b.getDueDate(); });
	return std::vector<Assignment>(order.begin(), order.end());
}

std::vector<Assignment> AssignmentQueryController::getOrderedAssignmentsByPriority(int userId) {
	std::vector<Assignment> v = getBaseUserAssignments(db_, userId);
	std::list<Assignment> order(v.begin(), v.end());
	order.sort([](const Assignment &a, const Assignment &b) { return a.getPriority() > b.getPriority(); });
	return std::vector<Assignment>(order.begin(), order.end());
}
