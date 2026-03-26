#pragma once
#include "BaseModel.hpp"
#include <string>

class Course : public BaseModel {
	protected:
		const std::string tableName = "courses";	
private:
	int id;
	std::string name;
	std::string description;
	int user_id; // Foreign key to associate course with a user

public:
	Course(int id, const std::string& name, const std::string& description);
	int getId() const;
	int getUserId() const;
	std::string getName() const;
	std::string getDescription() const;
	Course& setId(int id);
	Course& setName(const std::string& name);
	Course& setDescription(const std::string& description);
	Course& setUserId(int user_id);
	void save() override;
	void load();
	void remove() override;
	std::string getTableName() override;


};