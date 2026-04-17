/**
 * @file CourseModel.cpp
 * @brief Course accessors and persistence helpers.
 */

#include <iostream>
#include "CourseModel.hpp"

Course::Course(int id, const std::string& name, const std::string& description)
	: id(id), name(name), description(description) {
}

Course::Course() {

}

int Course::getId() const {
	return id;
}

std::string Course::getName() const {
	return name;
}

std::string Course::getDescription() const {
	return description;
}

int Course::getUserId() const {
	return user_id;
}

Course& Course::setId(int id) {
	this->id = id;
	return *this;
}

Course& Course::setName(const std::string& name) {
	this->name = name;
	return *this;
}

Course& Course::setDescription(const std::string& description) {
	this->description = description;
	return *this;
}

Course& Course::setUserId(int user_id) {
	this->user_id = user_id;
	return *this;
}


bool Course::save(IDatabase &) {
	return false;
}
bool Course::remove(IDatabase &) {
	return false;
}

std::string Course::getTableName()  {
	return "courses";
}

void Course::load() {}
