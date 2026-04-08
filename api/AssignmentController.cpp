#include "AssignmentController.hpp"
#include "AssignmentModel.hpp"

Assignment AssignmentController::createAssignment(const std::string& title, const std::string& description, int courseId, int userId) {
	//do validations here

	Assignment assignment = Assignment();
	assignment.setTitle(title)
			  .setDescription(description)
			  .setCourseId(courseId)
			   .setPriority(1); // default priority

	return assignment;
}
