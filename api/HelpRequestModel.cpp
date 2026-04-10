#include "HelpRequestModel.hpp"
#include "DB.hpp"

HelpRequestModel::HelpRequestModel(int id, int userId, const std::string &question, const std::string &createdAt) :
    id(id), userId(userId), question(question), createdAt(createdAt) {}

int HelpRequestModel::getId() const { return id; }

int HelpRequestModel::getUserId() const { return userId; }

const std::string &HelpRequestModel::getQuestion() const { return question; }

const std::string &HelpRequestModel::getCreatedAt() const { return createdAt; }
