/**
 * @file HelpRequestModel.cpp
 * @brief Help request field accessors and `save`/`remove` against `IDatabase`.
 */

#include "HelpRequestModel.hpp"
#include "IDatabase.hpp"

HelpRequestModel::HelpRequestModel(int id, int userId, const std::string &message, const std::string &createdAt) :
    id(id), userId(userId), assignment_id(-1), message(message), request_status(""), createdAt(createdAt),
    raiser_display_name("") {}

int HelpRequestModel::getId() const { return id; }

int HelpRequestModel::getUserId() const { return userId; }

const std::string &HelpRequestModel::getMessage() const { return message; }

const std::string &HelpRequestModel::getCreatedAt() const { return createdAt; }

void HelpRequestModel::setId(int id) { this->id = id; }

void HelpRequestModel::setUserId(int userId) { this->userId = userId; }

void HelpRequestModel::setCreatedAt(const std::string &createdAt) { this->createdAt = createdAt; }

void HelpRequestModel::setAssignmentId(int assignment_id) { this->assignment_id = assignment_id; }

void HelpRequestModel::setMessage(const std::string &message) { this->message = message; }

int HelpRequestModel::getAssignmentId() const { return assignment_id; }

const std::string &HelpRequestModel::getRequestStatus() const { return request_status; }

void HelpRequestModel::setRequestStatus(const std::string &request_status) {
    this->request_status = request_status;
}

const std::string &HelpRequestModel::getRaiserDisplayName() const { return raiser_display_name; }

void HelpRequestModel::setRaiserDisplayName(const std::string &name) { this->raiser_display_name = name; }

std::string HelpRequestModel::getTableName() { return tableName; }

bool HelpRequestModel::save(IDatabase &db) {
    return db.createHelpRequest(*this);
}
bool HelpRequestModel::remove(IDatabase &db) {
    return db.deleteHelpRequest(*this);
}
