#pragma once
#include <string>
#include "BaseModel.hpp"

class UserModel : public BaseModel {
protected:
	const std::string tableName = "users";
private:
	int id;
	std::string first_name;
	std::string last_name;
	std::string email;
	std::string password;
public:
	UserModel(int id, const std::string& first_name, const std::string& last_name);
	UserModel();
	int getId() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	UserModel& setFirstName(const std::string& first_name);
	UserModel& setLastName(const std::string& last_name);
	UserModel& setId(int id);
	UserModel& setEmail(const std::string& email);
	UserModel& setPassword(const std::string& password);
	std::string getTableName() override;
	void save() override;
	void remove() override;
};