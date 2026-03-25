#include "headers/AuthViewController.h"

#include "view/Models/headers/UserViewModel.h"

AuthViewController::AuthViewController(QObject *parent ) {

}

void AuthViewController::login(const QString &email, const QString &password) {
    //do validations
    if (email.trimmed().length() < 0 || password.trimmed().length() < 0) {
        emit loginFailed("Email and Password is required");
    }
    AuthController authController;
    //convert email and password to stdstring
    std::string emailStr = email.toStdString();
    std::string passwordStr = password.toStdString();

    //check if user is Logged In
    LoginResult isLoggedIn = authController.login(emailStr,passwordStr);

    if (isLoggedIn.success && isLoggedIn.userModel.has_value()) {
        UserViewModel userViewModel(*isLoggedIn.userModel, nullptr);
        //convert C++ Model to QTUser Model
        emit loginSucceeded(&userViewModel);
    }else {
        QString errorMessage = QString::fromStdString(isLoggedIn.message);
        emit loginFailed(errorMessage);
    }
}
