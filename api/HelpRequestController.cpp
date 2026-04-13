#include "HelpRequestController.hpp"
#include "IDatabase.hpp"

HelpRequestController::HelpRequestController(IDatabase &database) : db_(database) {}

HelpRequestResultPayload HelpRequestController::createHelpRequest(int userId, int assignmentId,
                                                                  const std::string &message) {
	HelpRequestModel helpRequest(-1, userId, message);
	helpRequest.setAssignmentId(assignmentId);
	bool success = db_.createHelpRequest(helpRequest);
	if (success) {
		return {true, "", helpRequest};
	}
	return {false, "Failed to create help request", std::nullopt};
}

HelpRequestResultPayload HelpRequestController::getHelpRequestById(int id) {
	std::optional<HelpRequestModel> hr = db_.getHelpRequestById(id);
	if (!hr.has_value()) {
		return {false, "Help request not found", std::nullopt};
	}
	return {true, "", hr};
}

GetAllHelpRequestResultPayload HelpRequestController::getAllHelpRequests(int userId) {
	std::vector<HelpRequestModel> helpRequests = db_.getAllHelpRequests(userId);
	if (helpRequests.empty()) {
		return {false, {}, "No help requests found"};
	}
	return {true, helpRequests, ""};
}
