#pragma once

#include <optional>
#include <string>
#include <vector>
#include "HelpRequestModel.hpp"

class IDatabase;

struct HelpRequestResultPayload {
	bool success;
	std::string errorMessage;
	std::optional<HelpRequestModel> helpRequest;
};

struct GetAllHelpRequestResultPayload {
	bool success;
	std::vector<HelpRequestModel> helpRequests;
	std::string errorMessage;
};

class HelpRequestController {
public:
	explicit HelpRequestController(IDatabase &database);

	HelpRequestResultPayload createHelpRequest(int userId, int assignmentId, const std::string &message);
	HelpRequestResultPayload getHelpRequestById(int id);
	GetAllHelpRequestResultPayload getAllHelpRequests(int userId);

private:
	IDatabase &db_;
};
