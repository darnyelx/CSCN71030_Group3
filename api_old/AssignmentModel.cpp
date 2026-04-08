#pragma once
#include "AssignmentModel.hpp"

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

Assignment& Assignment::setDueDate(const std::string& due_date) {
	this->due_date = due_date;
	return *this;
}

Assignment& Assignment::setCourseId(int course_id) {
	this->course_id = course_id;
	return *this;
}

Assignment& Assignment::setPriority(int priority) {
	this->priority = priority;
	return *this;
}

void Assignment::save()  {}
void Assignment::remove() {

}

std::string Assignment::getTableName()  {
	return "assignments";
}

void Assignment::load() {}

