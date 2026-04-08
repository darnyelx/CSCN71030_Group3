#pragma once
#include <string>
class BaseModel {
	public:
	virtual ~BaseModel() = default;
	virtual std::string getTableName() = 0;
	virtual bool save() = 0;
	virtual  bool remove() = 0;
};
