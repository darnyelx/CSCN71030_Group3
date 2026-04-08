#pragma once
#include <string>
class BaseModel {
	public:
	virtual ~BaseModel() = default;
	virtual std::string getTableName() = 0;
	virtual void save() = 0;
	virtual  void remove() = 0;
};
