/**
 * @file AuthViewController.h
 * @brief QML-facing adapter for `AuthController`: login/register and Qt signals for the UI.
 */

#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include <QString>
#include "api/AuthController.hpp"
#include "view/Models/headers/UserViewModel.h"

/**
 * @brief Exposes authentication actions to QML and translates `LoginResult` into signals.
 * @details Invokes `AuthController` methods on the GUI thread; builds `UserViewModel` from successful results.
 */
class AuthViewController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the bridge with a shared `AuthController`.
     * @param authController Backend controller (must outlive this object).
     * @param parent Optional Qt object parent.
     */
    explicit AuthViewController(AuthController &authController, QObject *parent = nullptr);

    /**
     * @brief QML-callable login: validates credentials and emits success or failure.
     * @param email User-entered email.
     * @param password User-entered plain password.
     */
    Q_INVOKABLE void login(const QString &email, const QString &password);

    /**
     * @brief QML-callable registration using fields from a `UserViewModel`.
     * @param userViewModel Non-null view model carrying first/last name, email, password.
     */
    Q_INVOKABLE void registerUser(const UserViewModel *userViewModel);

signals:
    /** @brief Emitted after successful login with a populated session user object (owned by caller context). */
    void loginSucceeded(UserViewModel* usermodel);
    /** @brief Emitted when login or registration fails; `message` is user-visible. */
    void loginFailed(const QString &message);
    /** @brief Reserved for explicit logout flows from QML (hook for future use). */
    void logoutSucceeded();

private:
    AuthController &m_authController;
};

#endif // AUTHCONTROLLER_H
