/**
 * @file UserViewModel.h
 * @brief QML property object mirroring `UserModel` for registration and session display.
 */

#pragma once

#include <QObject>
#include <QString>
#include "api/UserModel.hpp"

/**
 * @brief Qt Quick–friendly user fields (`Q_PROPERTY`) with conversion from `UserModel`.
 * @details Property accessors emit change notifications for QML bindings. Password is exposed for forms only;
 *          avoid logging or displaying it in production UIs.
 */
class UserViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)


public:
    /** @brief Constructs an empty user view model. */
    explicit UserViewModel(QObject *parent = nullptr);

    /**
     * @brief Constructs a view model initialized from a backend `UserModel`.
     * @param user Source domain row (e.g. after login).
     * @param parent Optional Qt parent.
     */
    explicit UserViewModel(const UserModel& user, QObject *parent = nullptr);

    /** @return Bound user id property. */
    int id() const;
    /** @return Given name as `QString`. */
    QString firstName() const;
    /** @return Family name as `QString`. */
    QString lastName() const;
    /** @return Email as `QString`. */
    QString email() const;
    /** @return Password field for forms (plain text in memory). */
    QString password() const;

    /** @brief Sets user id; emits `idChanged` when the value changes. */
    void setId(int id);
    /** @brief Sets given name; emits `firstNameChanged` when the value changes. */
    void setFirstName(const QString& firstName);
    /** @brief Sets family name; emits `lastNameChanged` when the value changes. */
    void setLastName(const QString& lastName);
    /** @brief Sets email; emits `emailChanged` when the value changes. */
    void setEmail(const QString& email);
    /** @brief Sets password field; emits `passwordChanged` when the value changes. */
    void setPassword(const QString& password);

    /**
     * @brief Copies all fields from `user` into this object and notifies QML.
     * @param user Backend model (UTF-8 strings converted to `QString`).
     */
    void fromModel(const UserModel& user);

signals:
    /** @brief Emitted when `id` changes. */
    void idChanged();
    /** @brief Emitted when `firstName` changes. */
    void firstNameChanged();
    /** @brief Emitted when `lastName` changes. */
    void lastNameChanged();
    /** @brief Emitted when `email` changes. */
    void emailChanged();
    /** @brief Emitted when `password` changes. */
    void passwordChanged();

private:
    int m_id = 0;
    QString m_firstName;
    QString m_lastName;
    QString m_email;
    QString m_password;
};
