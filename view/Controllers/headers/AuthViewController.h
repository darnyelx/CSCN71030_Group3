#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include <QString>
#include "api/AuthController.hpp"
#include "view/Models/headers/UserViewModel.h"

class AuthViewController : public QObject
{
    Q_OBJECT

public:
    explicit AuthViewController(AuthController &authController, QObject *parent = nullptr);

    Q_INVOKABLE void login(const QString &email, const QString &password);
    Q_INVOKABLE void registerUser(const UserViewModel *userViewModel);

signals:
    void loginSucceeded(UserViewModel* usermodel);
    void loginFailed(const QString &message);
    void logoutSucceeded();

private:
    AuthController &m_authController;
};

#endif // AUTHCONTROLLER_H
