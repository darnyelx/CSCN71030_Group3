#include "AssignmentController.hpp"
#include "AssignmentModel.hpp"
#include "DB.hpp"
#include <optional>


AssignmentResultPayload AssignmentController::createAssignment( const std::string title, const std::string description, int courseId, int userId, std::string dueDate ) {
	
	
	Assignment assignment;
	assignment.setTitle(title)
			  .setDescription(description)
			  .setCourseId(courseId)
    .setUserId(userId)
    .setDueDate(dueDate)
			   .setPriority(1); // default priority
	DB& db = DB::getInstance();
	bool result = db.createAssignment(assignment);
	return { 
		result, 
		result ? "" : "Failed to create assignment",	 
		assignment
	};

}
AssignmentResultPayload  AssignmentController::updateAssignment(int id, const std::string& title, const std::string& description, int priority){
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

    // return {
    //     result,
    //     result ? "" : "Failed to create assignment",
    //     result ? std::optional<Assignment>(assignment) : std::nullopt
    // };
}

GetAllAssignmentResultPayload AssignmentController::getAllAssignments(int id) {
    DB& db = DB::getInstance();
    std::vector<Assignment> assignments;
     return {
         true,
         assignments,
         ""
     };
}
