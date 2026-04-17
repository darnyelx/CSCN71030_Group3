/**
 * @file AssignmentModel.cpp
 * @brief Assignment field accessors and database save/remove paths.
 */

#include "AssignmentModel.hpp"
#include "IDatabase.hpp"

Assignment::Assignment(int id, const std::string& title, const std::string& description)
	: id(id), title(title), description(description) {
}

int Assignment::getId() const {
	return id;
}

std::string Assignment::getTitle() const {
	return title;
}

std::string Assignment::getDescription() const {
	return description;
}

Assignment& Assignment::setId(int id) {
	this->id = id;
	return *this;
}

Assignment& Assignment::setTitle(const std::string& title) {
	this->title = title;
	return *this;
}

Assignment& Assignment::setDescription(const std::string& description) {
	this->description = description;
	return *this;
}

Assignment& Assignment::setCreatedAt(const std::string& created_at) {
	this->created_at = created_at;
	return *this;
}

Assignment& Assignment::setUpdatedAt(const std::string& updated_at) {
	this->updated_at = updated_at;
	return *this;
}

Assignment& Assignment::setUserId(int user_id) {
	this->user_id = user_id;
	return *this;
}

Assignment& Assignment::setDueDate(const std::string& due_date) {
	this->due_date = due_date;
	return *this;
}

Assignment& Assignment::setCourseId(int course_id) {
	this->course_id = course_id;
	return *this;
}

Assignment& Assignment::setCourseName(const std::string &name) {
	this->course_name = name;
	return *this;
}

Assignment& Assignment::setPriority(int priority) {
	this->priority = priority;
	return *this;
}

std::string Assignment::getTableName()  {
	return "assignments";
}

int Assignment::getCourseId() const {
	return course_id;
}

std::string Assignment::getCourseName() const {
	return course_name;
}

int Assignment::getUserId() const {
	return user_id;
}

std::string Assignment::getDueDate() const {
    return due_date;
}
int Assignment::getPriority() const {
    return priority;
}

std::string Assignment::getStatus() const {
    return status;
}

Assignment &Assignment::setStatus(const std::string &s) {
    status = s;
    return *this;
}

std::string Assignment::getCreatedAt() const {
    return created_at;
}

std::string Assignment::getUpdatedAt() const {
    return updated_at;
}

void Assignment::load() {}

bool Assignment::save(IDatabase &db) {
	return db.createAssignment(*this);
}

bool Assignment::remove(IDatabase &db) {
	return db.deleteAssignment(*this);
}
