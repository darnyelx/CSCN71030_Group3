#include <string>
#include <vector>
#include "AssignmentModel.hpp"

class AssignmentQueryController {
	public:

		std::vector<Assignment> getFilteredAssignmentByDueDateRange(const std::string& startDate, const std::string& endDate);
		std::vector<Assignment> getFilteredAssignmentByCourse(int courseId);
		std::vector<Assignment> getFilteredAssignmentByPriority(int priority);
		std::vector<Assignment> getFilteredAssignmentByKeyword(const std::string& keyword);
		std::vector<Assignment> getOrderedAssignmentByDueDate(const std::string& keyword);
		std::vector<Assignment> getOrderedAssignmentByPriority(const std::string& keyword); 


};