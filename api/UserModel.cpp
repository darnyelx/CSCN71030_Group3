#include "UserModel.hpp"
#include "IDatabase.hpp"

UserModel::UserModel(int id, const std::string& first_name, const std::string& last_name) 
	: id(id), first_name(first_name), last_name(last_name) {
}

UserModel::UserModel()
	: id(0), first_name(""), last_name(""), email(""), password("") {
}


int UserModel::getId() const {
	return id;
}

std::string UserModel::getFirstName() const {
	return first_name;
}

std::string UserModel::getLastName() const {
	return last_name;
}

std::string UserModel::getEmail() const {
	return email;
}

std::string UserModel::getPassword() const {
	return password;
}

UserModel& UserModel::setFirstName(const std::string& first_name) {
	this->first_name = first_name;
	return *this;
}

UserModel& UserModel::setLastName(const std::string& last_name) {
	this->last_name = last_name;
	return *this;
}

UserModel& UserModel::setId(int id) {
	this->id = id;
	return *this;
}

UserModel& UserModel::setEmail(const std::string& email) {
	this->email = email;
	return *this;
}

UserModel& UserModel::setPassword(const std::string& password) {
	this->password = password;
	return *this;
}
std::string UserModel::getTableName()  {
	return this->tableName;
}


bool UserModel::save(IDatabase &db) {
	return db.createUser(*this);
}
bool UserModel::remove(IDatabase &db) {
	return db.deleteUser(*this);
}


