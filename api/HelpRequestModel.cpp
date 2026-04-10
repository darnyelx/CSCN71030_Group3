#include "HelpRequestModel.hpp"
#include "DB.hpp"

HelpRequestModel::HelpRequestModel(int id, int userId, const std::string &message, const std::string &createdAt) :
    id(id), userId(userId), message(message), createdAt(createdAt) {}

int HelpRequestModel::getId() const { return id; }

int HelpRequestModel::getUserId() const { return userId; }

const std::string &HelpRequestModel::getMessage() const { return message; }

const std::string &HelpRequestModel::getCreatedAt() const { return createdAt; }

void HelpRequestModel::setId(int id) { this->id = id; }

void HelpRequestModel::setUserId(int userId) { this->userId = userId; }

void HelpRequestModel::setAssignmentId(int assignment_id) { this->assignment_id = assignment_id; }

void HelpRequestModel::setMessage(const std::string &message) { this->message = message; }
bool HelpRequestModel::save() {
    DB &db = DB::getInstance();
    return db.createHelpRequest(*this);
}
bool HelpRequestModel::remove() {
    DB &db = DB::getInstance();
    return db.deleteHelpRequest(*this);
}
