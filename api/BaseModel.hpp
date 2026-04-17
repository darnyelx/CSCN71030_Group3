/**
 * @file BaseModel.hpp
 * @brief Minimal interface for domain rows that know their table name and can persist.
 */

#pragma once

#include <string>

class IDatabase;

/**
 * @brief Base type for entities mapped to SQL tables (`UserModel`, `Assignment`, etc.).
 * @details Concrete models implement `getTableName` for logging or generic SQL helpers, and
 *          `save` / `remove` to delegate writes to an `IDatabase` implementation.
 */
class BaseModel {
public:
    /** @brief Ensures derived destructors run when deleting through `BaseModel*`. */
    virtual ~BaseModel() = default;

    /**
     * @brief SQL table name associated with this entity (e.g. `"users"`, `"assignments"`).
     * @return Non-owning logical table identifier as a string.
     */
    virtual std::string getTableName() = 0;

    /**
     * @brief Inserts or updates this row through the given database port.
     * @param db Database used for persistence.
     * @return true if the operation succeeded.
     */
    virtual bool save(IDatabase &db) = 0;

    /**
     * @brief Deletes this row from the database.
     * @param db Database used for persistence.
     * @return true if the operation succeeded.
     */
    virtual bool remove(IDatabase &db) = 0;
};
