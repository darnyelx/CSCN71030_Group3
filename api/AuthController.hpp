#pragma once
#include <string>
#include "UserModel.hpp"

class AuthController {
	
	public:
	// Function to handle user login
		UserModel login(const std::string& email, const std::string& password);
		// Function to handle user registration
		UserModel registerUser(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password);
	

};