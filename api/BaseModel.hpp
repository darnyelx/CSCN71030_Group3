#pragma once

#include <string>

class IDatabase;

class BaseModel {
public:
    virtual ~BaseModel() = default;
    virtual std::string getTableName() = 0;
    virtual bool save(IDatabase &db) = 0;
    virtual bool remove(IDatabase &db) = 0;
};
