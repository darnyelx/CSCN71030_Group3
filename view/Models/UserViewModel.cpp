#include "headers/UserViewModel.h"

UserViewModel::UserViewModel(QObject *parent)
    : QObject(parent)
{
}

UserViewModel::UserViewModel(const UserModel& user, QObject *parent)
    : QObject(parent)
{
    fromModel(user);
}

void UserViewModel::fromModel(const UserModel& user)
{
    m_id = user.getId();
    m_firstName = QString::fromStdString(user.getFirstName());
    m_lastName = QString::fromStdString(user.getLastName());

    // Only if you later add getEmail() in UserModel
    // m_email = QString::fromStdString(user.getEmail());
}

int UserViewModel::id() const
{
    return m_id;
}

QString UserViewModel::firstName() const
{
    return m_firstName;
}

QString UserViewModel::lastName() const
{
    return m_lastName;
}

QString UserViewModel::email() const
{
    return m_email;
}

QString UserViewModel::password() const {
    return m_password;
}

void UserViewModel::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

void UserViewModel::setFirstName(const QString& firstName)
{
    if (m_firstName == firstName)
        return;

    m_firstName = firstName;
    emit firstNameChanged();
}

void UserViewModel::setLastName(const QString& lastName)
{
    if (m_lastName == lastName)
        return;

    m_lastName = lastName;
    emit lastNameChanged();
}

void UserViewModel::setEmail(const QString& email)
{
    if (m_email == email)
        return;

    m_email = email;
    emit emailChanged();
}

void UserViewModel::setPassword(const QString& password) {
    if (m_password == password) {
        return;
    }
    m_password = password;
    emit passwordChanged();
}