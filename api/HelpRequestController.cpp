/**
 * @file HelpRequestController.cpp
 * @brief Help request creation and listing with timestamp formatting where needed.
 */

#include "HelpRequestController.hpp"
#include "IDatabase.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
std::string utcTimestampForDb()
{
	const std::time_t t = std::time(nullptr);
	std::tm tm{};
#if defined(_WIN32)
	gmtime_s(&tm, &t);
#else
	gmtime_r(&t, &tm);
#endif
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}
} // namespace

HelpRequestController::HelpRequestController(IDatabase &database) : db_(database) {}

HelpRequestResultPayload HelpRequestController::createHelpRequest(int userId, int assignmentId,
                                                                  const std::string &message) {
	HelpRequestModel helpRequest(-1, userId, message);
	helpRequest.setAssignmentId(assignmentId);
	helpRequest.setCreatedAt(utcTimestampForDb());
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
	return {true, std::move(helpRequests), ""};
}

GetAllHelpRequestResultPayload HelpRequestController::getHelpRequestsFromOtherUsers(int userId) {
	std::vector<HelpRequestModel> helpRequests = db_.getHelpRequestsFromOtherUsers(userId);
	return {true, std::move(helpRequests), ""};
}
