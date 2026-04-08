#include "AssignmentQueryController.hpp"
#include "DB.hpp"

std::vector<Assignment>  AssignmentQueryController::getFilteredAssignmentByCourse(int courseId) {
	DB db = DB();
	std::vector<Assignment> assignments = db.getAllAssignments();
	Assignment testAssignment = Assignment();
	testAssignment.save();
	//for loop
}