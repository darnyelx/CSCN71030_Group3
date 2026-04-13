#include "AssignmentQueryController.hpp"
#include "DB.hpp"
#include <algorithm>
#include <iterator>

// ------------------------------------------------------------------
// HELPER FUNCTION (Private to this file)
// ------------------------------------------------------------------
// Fetches all assignments from the DB and filters out only the ones 
// belonging to the requesting user.
std::vector<Assignment> getBaseUserAssignments(int userId) {
    DB& db = DB::getInstance();
    std::vector<Assignment> allAssignments = db.getAllAssignments();
    std::vector<Assignment> userAssignments;

    std::copy_if(allAssignments.begin(), allAssignments.end(), std::back_inserter(userAssignments),
        [userId](const Assignment& a) {
            // *** TEAMMATE ACTION REQUIRED ***
            // The team MUST add getUserId() to AssignmentViewModel.hpp for this to compile.
            return a.getUserId() == userId;
        });

    return userAssignments;
}

// ------------------------------------------------------------------
// SEARCHING
// ------------------------------------------------------------------
std::vector<Assignment> AssignmentQueryController::searchAssignmentsByKeyword(int userId, const std::string& keyword) {
    std::vector<Assignment> userAssignments = getBaseUserAssignments(userId);
    std::vector<Assignment> filtered;

    std::copy_if(userAssignments.begin(), userAssignments.end(), std::back_inserter(filtered),
        [&keyword](const Assignment& a) {
            // Checks if the keyword is in the title or the description
            bool inTitle = a.getTitle().find(keyword) != std::string::npos;
            bool inDesc = a.getDescription().find(keyword) != std::string::npos;
            return inTitle || inDesc;
        });

    return filtered;
}
