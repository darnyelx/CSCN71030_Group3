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
    explicit AuthViewController(QObject *parent = nullptr);

    Q_INVOKABLE void login(const QString &email, const QString &password);
    Q_INVOKABLE void registerUser(const UserViewModel &userViewModel);

    // Q_INVOKABLE void logout();

signals:
    void loginSucceeded(UserViewModel* usermodel);
    void loginFailed(const QString &message);
    void logoutSucceeded();
};

#endif //