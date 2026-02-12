#pragma once

#include "AssignmentModel.hpp"
#include <vector>

class AssignmentController {
	public:
		Assignment createAssignment(const std::string& title, const std::string& description, int courseId, int userId);

		Assignment getAssignment(int id);

		std::vector<Assignment> getAllAssignments(int userId);

		Assignment updateAssignment(int id, const std::string& title, const std::string& description, int priority);

		bool deleteAssignment(int id);
};