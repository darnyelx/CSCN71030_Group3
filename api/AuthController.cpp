#include "AuthController.hpp"

LoginResult AuthController::login(const std::string& email, const std::string& password)
{
    // Dummy hardcoded login for now
    if (email == "admin@test.com" && password == "1234") {
        UserModel user(1, "John", "Doe");
        user.setEmail(email);

        return {
            true,
            "Login successful",
            user
        };
    }


    return {
        false,
        "Invalid email or password",
        std::nullopt
    };
}

LoginResult AuthController::registerUser(
    const std::string& firstName,
    const std::string& lastName,
    const std::string& email,
    const std::string& password
)
{
    // Very simple fake registration logic
    if (firstName.empty() || lastName.empty() || email.empty() || password.empty()) {
        return {
            false,
            "All fields are required",
            std::nullopt
        };
    }

    UserModel user(2, firstName, lastName);
    user.setEmail(email);
    user.setPassword(password);
	user.save(); // Save the user to the database (this is a dummy implementation)

    return {
        true,
        "Registration successful",
        user
    };
}