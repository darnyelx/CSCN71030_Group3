/**
 * @file UserModel.hpp
 * @brief Domain model for the `users` table (names, email, password hash).
 */

#pragma once
#include <string>
#include "BaseModel.hpp"

/**
 * @brief Mutable in-memory representation of a user row.
 * @details `save` delegates to `IDatabase::createUser`. Password field stores a libsodium
 *          `crypto_pwhash_str` output string, not plain text, after registration flows.
 */
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
	/**
	 * @brief Constructs a user with identifier and display names; email/password default empty until set.
	 * @param id Database id or sentinel (e.g. -1) before insert.
	 * @param first_name Given name.
	 * @param last_name Family name.
	 */
	UserModel(int id, const std::string& first_name, const std::string& last_name);
	/** @brief Default construct: zero id and empty strings. */
	UserModel();
	/** @return Current user primary key. */
	int getId() const;
	/** @return Given name. */
	std::string getFirstName() const;
	/** @return Family name. */
	std::string getLastName() const;
	/** @return Email address string. */
	std::string getEmail() const;
	/** @return Stored password hash string (never log as plain text). */
	std::string getPassword() const;

	/** @brief Sets given name. @return `*this` for chaining. */
	UserModel& setFirstName(const std::string& first_name);
	/** @brief Sets family name. @return `*this` for chaining. */
	UserModel& setLastName(const std::string& last_name);
	/** @brief Sets primary key. @return `*this` for chaining. */
	UserModel& setId(int id);
	/** @brief Sets email. @return `*this` for chaining. */
	UserModel& setEmail(const std::string& email);
	/** @brief Sets password hash string. @return `*this` for chaining. */
	UserModel& setPassword(const std::string& password);
	/** @return Logical table name `"users"`. */
	std::string getTableName() override;
	/** @brief Calls `IDatabase::createUser` with this object. */
	bool save(IDatabase &db) override;
	/** @brief Calls `IDatabase::deleteUser` with this object. */
	bool remove(IDatabase &db) override;
};
