#pragma once
#include <string>
#include "UserModel.hpp"

struct LoginResult {
	bool success;
	std::string message;
    std::optional<UserModel> userModel;
};



class AuthController {
	
	public:
	// Function to handle user login
		LoginResult login(const std::string& email, const std::string& password);
		// Function to handle user registration
		LoginResult registerUser(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password);
	

};