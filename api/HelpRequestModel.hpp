#include <string>
#include "BaseModel.hpp"
#pragma once

class HelpRequestModel : public BaseModel {
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
    HelpRequestModel(int id = -1, int userId = -1, const std::string &message = "", const std::string &createdAt = "");
    int getId() const;
    int getUserId() const;
    int getAssignmentId() const;
    const std::string &getMessage() const;
    const std::string &getRequestStatus() const;
    const std::string &getCreatedAt() const;
    void setId(int id);
    void setUserId(int userId);
    void setAssignmentId(int assignment_id);
    void setMessage(const std::string &message);
    void setRequestStatus(const std::string &request_status);
    bool save() override;
    bool remove() override;

    std::string getTableName() override;
};
