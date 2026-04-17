/**
 * @file AuthController.cpp
 * @brief Libsodium password hashing and `LoginResult` mapping for login/register.
 */

#include "AuthController.hpp"
#include <sodium.h>
#include "IDatabase.hpp"

AuthController::AuthController(IDatabase &database) : db_(database) {}

LoginResult AuthController::login(std::string &email, const std::string &password) {

    std::optional<UserModel> user = db_.getUserByEmail(email);
    if (!user.has_value()) {
        return {false, "Invalid email or password", std::nullopt};
    }

    // Verify the password using the stored hash
    if (crypto_pwhash_str_verify(user->getPassword().c_str(), password.c_str(), password.length()) != 0) {
        return {false, "Invalid email or password", std::nullopt};
    }


    return {true, "Login successful", user};
}

LoginResult AuthController::registerUser(const std::string &firstName, const std::string &lastName,
                                         const std::string &email, const std::string &password) {
    // Very simple fake registration logic
    if (firstName.empty() || lastName.empty() || email.empty() || password.empty()) {
        return {false, "All fields are required", std::nullopt};
    }

    char hashed[crypto_pwhash_STRBYTES];

    // Create a secure password hash
    if (crypto_pwhash_str(hashed, password.c_str(), password.length(), crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {

        return {false, "Internal Server Error", std::nullopt};
    }


    UserModel user(-1, firstName, lastName);
    user.setEmail(email);
    user.setPassword(hashed);
    bool result = db_.createUser(user);
    if (result) {
        //get user by email
        std::string userEmail = user.getEmail();
        std::optional<UserModel> registeredUser =  db_.getUserByEmail(userEmail);
        if (registeredUser.has_value()) {
            return {true, "Registration successful", registeredUser};
        }
        return {false, "Registration ", user};

    }



}
