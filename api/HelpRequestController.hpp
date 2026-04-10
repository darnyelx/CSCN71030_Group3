#include "DB.hpp"
#include "HelpRequestModel.hpp"


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
    HelpRequestResultPayload createHelpRequest(int userId, int assignmentId, const std::string &message);
    HelpRequestResultPayload getHelpRequestById(int id);
    GetAllHelpRequestResultPayload getAllHelpRequests(int userId);
};
