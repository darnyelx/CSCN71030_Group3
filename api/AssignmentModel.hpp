#pragma once
#include "BaseModel.hpp"
#include <string>	

class Assignment : public BaseModel {
protected: 
	//overwriting the tableName from BaseModel
	const std::string tableName = "assignments";
private:
	int id;
	std::string title;
	std::string description;
	std::string created_at;
	std::string updated_at;
	std::string due_date;
	int course_id;
	int priority;

public:
	Assignment(int id = -1, const std::string& title = "", const std::string& description = "");
	int getId() const;
	std::string getTitle() const;
	std::string getDescription() const;
	std::string getTableName() override;
	Assignment& setId(int id);
	Assignment& setTitle(const std::string& title);
	Assignment& setDescription(const std::string& description);
	Assignment& setCreatedAt(const std::string& created_at);
	Assignment& setUpdatedAt(const std::string& updated_at);
	Assignment& setDueDate(const std::string& due_date);
	Assignment& setCourseId(int course_id);
	Assignment& setPriority(int priority);
	void save() override;
	void load();
	void remove() override;


};