#pragma once

#include <string>
#include <vector>
#include "AssignmentModel.hpp"

class AssignmentQueryController {
public:
    // ==========================================
    // SEARCHING
    // ==========================================
    // Searches titles and descriptions for a keyword
    std::vector<Assignment> searchAssignmentsByKeyword(int userId, const std::string& keyword);

    // ==========================================
    // FILTERING
    // ==========================================
    std::vector<Assignment> getFilteredAssignmentsByCourse(int userId, int courseId);
    std::vector<Assignment> getFilteredAssignmentsByPriority(int userId, int priority);
    std::vector<Assignment> getFilteredAssignmentsByStatus(int userId, const std::string& status);
    std::vector<Assignment> getFilteredAssignmentsByDueDateRange(int userId, const std::string& startDate, const std::string& endDate);

    // ==========================================
    // SORTING
    // ==========================================
    // Sorts by closest due date first
    std::vector<Assignment> getOrderedAssignmentsByDueDate(int userId);
    // Sorts by highest priority first
    std::vector<Assignment> getOrderedAssignmentsByPriority(int userId);
};