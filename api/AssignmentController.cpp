#include "AssignmentController.hpp"
#include "AssignmentModel.hpp"
#include "DB.hpp"

AssignmentResultPayload AssignmentController::createAssignment(const std::string& title, const std::string& description, int courseId, int userId) {
	
	
	Assignment assignment;
	assignment.setTitle(title)
			  .setDescription(description)
			  .setCourseId(courseId)
			   .setPriority(1); // default priority
	DB& db = DB::getInstance();
	bool result = db.createAssignment(assignment);
	return { 
		result, 
		result ? "" : "Failed to create assignment",	 
		assignment
	};

}
AssignmentResultPayload updateAssignment(int id, const std::string& title, const std::string& description, int priority){
	//get DB instance
	DB& db = DB::getInstance();
	std::optional<Assignment> assignment = db.getAssignmentByID(id);
	//if it doesn't exist, return error
	if (!assignment.has_value()) {
		return {
			false,
			"Assignment not found",
			std::nullopt
		};
	}

	assignment->setTitle(title)
			  .setDescription(description)
			.setPriority(priority)
            .save();
	return {
		true,
		"",
		assignment
	};
		
}
