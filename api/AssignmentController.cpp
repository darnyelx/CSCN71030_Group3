#include "AssignmentController.hpp"
#include "AssignmentModel.hpp"
#include "IDatabase.hpp"

AssignmentController::AssignmentController(IDatabase &database) : db_(database) {}

AssignmentResultPayload AssignmentController::createAssignment(const std::string title, const std::string description,
                                                             int courseId, int userId, std::string dueDate) {

	Assignment assignment;
	assignment.setTitle(title)
	    .setDescription(description)
	    .setCourseId(courseId)
	    .setUserId(userId)
	    .setDueDate(dueDate)
	    .setPriority(1);
	bool result = db_.createAssignment(assignment);
	return {
	    result,
	    result ? "" : "Failed to create assignment",
	    assignment,
	};
}

AssignmentResultPayload AssignmentController::updateAssignment(int id, const std::string &title,
                                                               const std::string &description, int priority) {
	std::optional<Assignment> assignment = db_.getAssignmentByID(id);
	if (!assignment.has_value()) {
		return {
		    false,
		    "Assignment not found",
		    std::nullopt,
		};
	}

	assignment->setTitle(title).setDescription(description).setPriority(priority);
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
