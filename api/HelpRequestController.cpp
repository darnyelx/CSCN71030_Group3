#include "HelpRequestController.hpp"
#include "DB.hpp"


HelpRequestResultPayload createHelpRequest(int userId, int assignmentId, const std::string &message) {
    DB &db = DB::getInstance();
    HelpRequestModel helpRequest(-1, userId, message);
    helpRequest.setAssignmentId(assignmentId);
    bool success = db.createHelpRequest(helpRequest);
    if (success) {
        return {true, "", helpRequest};
    } else {
        return {false, "Failed to create help request", std::nullopt};
    }
}
GetAllHelpRequestResultPayload HelpRequestController::getAllHelpRequests(int userId) {
    DB &db = DB::getInstance();
    std::vector<HelpRequestModel> helpRequests = db.getAllHelpRequests(userId);
    if (helpRequests.empty()) {
        return {false, {}, "No help requests found"};
    }
    return {true, helpRequests, ""};
}
