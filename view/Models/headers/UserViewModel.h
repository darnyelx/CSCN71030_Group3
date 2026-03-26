#pragma once

#include <QObject>
#include <QString>
#include "api/UserModel.hpp"

class UserViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)


public:
    explicit UserViewModel(QObject *parent = nullptr);

    // Optional helper constructor from backend model
    explicit UserViewModel(const UserModel& user, QObject *parent = nullptr);

    int id() const;
    QString firstName() const;
    QString lastName() const;
    QString email() const;
    QString password() const;

    void setId(int id);
    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setEmail(const QString& email);
    void setPassword(const QString& password);

    // Convert backend model -> QML object
    void fromModel(const UserModel& user);

    signals:
        void idChanged();
    void firstNameChanged();
    void lastNameChanged();
    void emailChanged();
    void passwordChanged();

private:
    int m_id = 0;
    QString m_firstName;
    QString m_lastName;
    QString m_email;
    QString m_password;
};