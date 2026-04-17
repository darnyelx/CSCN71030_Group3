/**
 * @file AssignmentController.cpp
 * @brief Implements assignment CRUD orchestration and payload error strings.
 */

#include "AssignmentController.hpp"
#include "AssignmentModel.hpp"
#include "IDatabase.hpp"

AssignmentController::AssignmentController(IDatabase &database) : db_(database) {}

AssignmentResultPayload AssignmentController::createAssignment(const std::string title, const std::string description,
                                                             int courseId, int userId, std::string dueDate,
                                                             const std::string &status) {

	Assignment assignment;
	std::string st = status;
	if (st.empty()) {
		st = "Pending";
	}
	assignment.setTitle(title)
	    .setDescription(description)
	    .setCourseId(courseId)
	    .setUserId(userId)
	    .setDueDate(dueDate)
	    .setPriority(1)
	    .setStatus(st);
	bool result = db_.createAssignment(assignment);
	return {
	    result,
	    result ? "" : "Failed to create assignment",
	    assignment,
	};
}

AssignmentResultPayload AssignmentController::updateAssignment(int id, const std::string &title,
                                                               const std::string &description, int courseId,
                                                               const std::string &dueDate, int priority,
                                                               const std::string &status) {
	std::optional<Assignment> assignment = db_.getAssignmentByID(id);
	if (!assignment.has_value()) {
		return {
		    false,
		    "Assignment not found",
		    std::nullopt,
		};
	}

	std::string st = status;
	if (st.empty()) {
		st = assignment->getStatus().empty() ? "Pending" : assignment->getStatus();
	}
	assignment->setTitle(title)
	    .setDescription(description)
	    .setCourseId(courseId)
	    .setDueDate(dueDate)
	    .setPriority(priority)
	    .setStatus(st);
	bool ok = db_.createAssignment(*assignment);
	return {
	    ok,
	    ok ? "" : "Failed to update assignment",
	    assignment,
	};
}

GetAllAssignmentResultPayload AssignmentController::getAllAssignments(int id) {
	std::vector<Assignment> assignments = db_.getAllAssignments(id);
	return {
	    true,
	    assignments,
	    "",
	};
}

AssignmentResultPayload AssignmentController::getAssignment(int id) {
	std::optional<Assignment> assignment = db_.getAssignmentByID(id);
	if (!assignment.has_value()) {
		return {false, "Assignment not found", std::nullopt};
	}
	return {true, "", assignment};
}

AssignmentResultPayload AssignmentController::deleteAssignment(int id) {
	Assignment assignment;
	assignment.setId(id);
	bool ok = db_.deleteAssignment(assignment);
	return {
	    ok,
	    ok ? "" : "Failed to delete assignment",
	    std::nullopt,
	};
}
