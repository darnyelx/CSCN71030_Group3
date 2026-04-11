#pragma once

#include <QObject>
#include <QString>
#include "api/AssignmentModel.hpp"

class AssignmentViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QString dueDate READ dueDate WRITE setDueDate NOTIFY dueDateChanged)
    Q_PROPERTY(int courseId READ courseId WRITE setCourseId NOTIFY courseIdChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(int priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    explicit AssignmentViewModel(QObject *parent = nullptr);
    explicit AssignmentViewModel(const Assignment& assignment, QObject *parent = nullptr);

    int id() const;
    QString title() const;
    QString description() const;
    QString createdAt() const;
    QString updatedAt() const;
    QString dueDate() const;
    int courseId() const;
    int userId() const;
    int priority() const;

    void setId(int value);
    void setTitle(const QString& value);
    void setDescription(const QString& value);
    void setCreatedAt(const QString& value);
    void setUpdatedAt(const QString& value);
    void setDueDate(const QString& value);
    void setCourseId(int value);
    void setUserId(int value);
    void setPriority(int value);

    Q_INVOKABLE void fromModel(const Assignment& assignment);
    Assignment toModel() const;

signals:
    void idChanged();
    void titleChanged();
    void descriptionChanged();
    void createdAtChanged();
    void updatedAtChanged();
    void dueDateChanged();
    void courseIdChanged();
    void userIdChanged();
    void priorityChanged();

private:
    int m_id;
    QString m_title;
    QString m_description;
    QString m_createdAt;
    QString m_updatedAt;
    QString m_dueDate;
    int m_courseId;
    int m_userId;
    int m_priority;
};