/**
 * @file AuthController.hpp
 * @brief Use-case layer for login and registration (password hashing, `IDatabase` access).
 */

#pragma once
#include <optional>
#include <string>
#include "UserModel.hpp"

class IDatabase;

/**
 * @brief Outcome of `login` or `registerUser` for the UI or tests to interpret.
 */
struct LoginResult {
	bool success; /**< true when credentials validated or registration completed. */
	std::string message; /**< Human-readable status (error text or success notice). */
    std::optional<UserModel> userModel; /**< Populated user row on success when available. */
};

/**
 * @brief Stateless controller wrapping auth-related database operations.
 * @details Uses libsodium `crypto_pwhash_str` / `crypto_pwhash_str_verify` for password handling.
 */
class AuthController {
public:
	/**
	 * @brief Constructs a controller bound to a database implementation.
	 * @param database Reference retained for the lifetime of this controller (must outlive it).
	 */
	explicit AuthController(IDatabase &database);

	/**
	 * @brief Validates email/password against stored hash.
	 * @param email Account email (mutable for legacy `getUserByEmail` signature).
	 * @param password Plain text password from the client.
	 * @return `LoginResult` with `success` false and generic message if user missing or hash mismatch;
	 *         on success includes loaded `UserModel`.
	 */
	LoginResult login(std::string &email, const std::string &password);

	/**
	 * @brief Registers a new user: validates non-empty fields, hashes password, calls `createUser`, then reloads by email.
	 * @param firstName Given name.
	 * @param lastName Family name.
	 * @param email Unique email for login.
	 * @param password Plain text; stored only as hash.
	 * @return Success with loaded user on insert + fetch; failure with reason if validation, hashing, or insert fails.
	 */
	LoginResult registerUser(const std::string &firstName, const std::string &lastName, const std::string &email,
	                         const std::string &password);

private:
	IDatabase &db_;
};
