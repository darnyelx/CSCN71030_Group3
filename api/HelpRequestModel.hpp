#include <string>
#include "AssignmentModel.hpp"

class HelpRequestModel : public Assignment {
protected:
    const std::string tableName = "help_requests";

private:
    int id;
    int userId;
    int assignment_id;
    std::string message;
    std::string request_status;
    std::string createdAt;

public:
    HelpRequestModel(int id = -1, int userId = -1, const std::string &question = "", const std::string &createdAt = "");
    int getId() const;
    int getUserId() const;
    int getAssignmentId() const;
    const std::string &getMessage() const;
    const std::string &getRequestStatus() const;
    const std::string &getCreatedAt() const;
};
