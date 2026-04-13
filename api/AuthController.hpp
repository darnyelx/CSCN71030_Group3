#pragma once
#include <optional>
#include <string>
#include "UserModel.hpp"

class IDatabase;

struct LoginResult {
	bool success;
	std::string message;
    std::optional<UserModel> userModel;
};

class AuthController {
public:
	explicit AuthController(IDatabase &database);

	LoginResult login(std::string &email, const std::string &password);
	LoginResult registerUser(const std::string &firstName, const std::string &lastName, const std::string &email,
	                         const std::string &password);

private:
	IDatabase &db_;
};
