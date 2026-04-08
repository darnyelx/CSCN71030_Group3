#include "AuthController.hpp"
#include "DB.hpp"

LoginResult AuthController::login(const std::string &email, const std::string &password) {

    DB& DBInstance = DB::getInstance();
    std::optional<UserModel> user = DBInstance.getUserByEmail(email);
    if (!user.has_value()) {
        return {false, "Invalid email or password", std::nullopt};
    }

    return {true, "Login successful", user};

    return {false, "Invalid email or password", std::nullopt};
}

LoginResult AuthController::registerUser(const std::string &firstName, const std::string &lastName,
                                         const std::string &email, const std::string &password) {
    // Very simple fake registration logic
    if (firstName.empty() || lastName.empty() || email.empty() || password.empty()) {
        return {false, "All fields are required", std::nullopt};
    }

    UserModel user(2, firstName, lastName);
    user.setEmail(email);
    user.setPassword(password);
    user.save(); // Save the user to the database (this is a dummy implementation)

    return {true, "Registration successful", user};
}
