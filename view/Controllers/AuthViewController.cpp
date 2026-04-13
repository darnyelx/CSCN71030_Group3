#include "headers/AuthViewController.h"

#include "view/Models/headers/UserViewModel.h"

AuthViewController::AuthViewController(AuthController &authController, QObject *parent)
    : QObject(parent), m_authController(authController) {}

void AuthViewController::login(const QString &email, const QString &password) {
    //do validations
    if (email.trimmed().length() < 0 || password.trimmed().length() < 0) {
        emit loginFailed("Email and Password is required");
    }
    std::string emailStr = email.toStdString();
    std::string passwordStr = password.toStdString();

    LoginResult isLoggedIn = m_authController.login(emailStr, passwordStr);

    if (isLoggedIn.success && isLoggedIn.userModel.has_value()) {
        //convert C++ Model to QTUser Model
        UserViewModel userViewModel(*isLoggedIn.userModel, nullptr);
        emit loginSucceeded(&userViewModel);
    }else {
        QString errorMessage = QString::fromStdString(isLoggedIn.message);
        emit loginFailed(errorMessage);
    }
}

void AuthViewController::registerUser(const UserViewModel *userViewModel ) {
    //do validations
    if (userViewModel->email().trimmed().length() < 0 || userViewModel->password().trimmed().length() < 0 || userViewModel->firstName().trimmed().length() < 0 || userViewModel->lastName().trimmed().length() < 0 ) {
        emit loginFailed("Firstname, Lastname, Email and Password is required");
    }
    std::string emailStr = userViewModel->email().toStdString();
    std::string passwordStr = userViewModel->password().toStdString();
    std::string firstName = userViewModel->firstName().toStdString();
    std::string lastName = userViewModel->lastName().toStdString();

    //check if user is Logged In
    LoginResult isRegistered = m_authController.registerUser(firstName, lastName, emailStr, passwordStr);

    if (isRegistered.success && isRegistered.userModel.has_value()) {
        UserViewModel userViewModel(*isRegistered.userModel, nullptr);
        //convert C++ Model to QTUser Model
        emit loginSucceeded(&userViewModel);
    }else {
        QString errorMessage = QString::fromStdString(isRegistered.message);
        emit loginFailed(errorMessage);
    }
}
