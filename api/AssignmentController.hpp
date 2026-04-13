#pragma once

#include "AssignmentModel.hpp"
#include <vector>

struct AssignmentResultPayload {
	bool success;
	std::string errorMessage;
	std::optional<Assignment> assignment;
};

struct GetAllAssignmentResultPayload {
	bool success;
	std::vector<Assignment> assignments;
	std::string errorMessage;
};



class AssignmentController {
	public:
		AssignmentResultPayload createAssignment( const std::string title, const  std::string description, int courseId, int userId, std::string dueDate );

		AssignmentResultPayload getAssignment(int id);

		GetAllAssignmentResultPayload getAllAssignments(int userId);

		AssignmentResultPayload updateAssignment(int id, const std::string& title, const std::string& description, int priority);

		AssignmentResultPayload deleteAssignment(int id);
};

