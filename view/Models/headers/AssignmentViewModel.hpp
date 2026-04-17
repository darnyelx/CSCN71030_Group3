/**
 * @file AssignmentViewModel.hpp
 * @brief QML property object for one assignment row, bidirectionally mapped to `Assignment`.
 */

#pragma once

#include <QObject>
#include <QString>
#include "api/AssignmentModel.hpp"

/**
 * @brief Mirrors assignment columns for forms and list delegates; `toModel()` feeds persistence.
 */
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
    Q_PROPERTY(QString courseName READ courseName WRITE setCourseName NOTIFY courseNameChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(int priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    /** @brief Default-constructs with sentinel id and empty strings. */
    explicit AssignmentViewModel(QObject *parent = nullptr);
    /**
     * @brief Initializes all properties from a domain `Assignment`.
     * @param assignment Source row (e.g. from list population).
     * @param parent Optional Qt parent.
     */
    explicit AssignmentViewModel(const Assignment& assignment, QObject *parent = nullptr);

    /** @return Assignment primary key (or sentinel). */
    int id() const;
    /** @return Title string for QML. */
    QString title() const;
    /** @return Description string for QML. */
    QString description() const;
    /** @return Created-at timestamp string. */
    QString createdAt() const;
    /** @return Updated-at timestamp string. */
    QString updatedAt() const;
    /** @return Due date string. */
    QString dueDate() const;
    /** @return Course foreign key. */
    int courseId() const;
    /** @return Denormalized course display name. */
    QString courseName() const;
    /** @return Owning user id. */
    int userId() const;
    /** @return Priority integer. */
    int priority() const;
    /** @return Status string (Pending / In Progress / Completed). */
    QString status() const;

    /** @brief Sets id property; notifies on change. */
    void setId(int value);
    /** @brief Sets title; notifies on change. */
    void setTitle(const QString& value);
    /** @brief Sets description; notifies on change. */
    void setDescription(const QString& value);
    /** @brief Sets created-at; notifies on change. */
    void setCreatedAt(const QString& value);
    /** @brief Sets updated-at; notifies on change. */
    void setUpdatedAt(const QString& value);
    /** @brief Sets due date; notifies on change. */
    void setDueDate(const QString& value);
    /** @brief Sets course id; notifies on change. */
    void setCourseId(int value);
    /** @brief Sets course display name; notifies on change. */
    void setCourseName(const QString &value);
    /** @brief Sets owner user id; notifies on change. */
    void setUserId(int value);
    /** @brief Sets priority; notifies on change. */
    void setPriority(int value);
    /** @brief Sets status; notifies on change. */
    void setStatus(const QString &value);

    /**
     * @brief QML-invokable: replaces all fields from `assignment` and emits notifications.
     * @param assignment Backend source row.
     */
    Q_INVOKABLE void fromModel(const Assignment& assignment);

    /**
     * @brief Builds an `Assignment` with `std::string` fields from current `QString` properties.
     * @return Domain object suitable for `AssignmentController` calls.
     */
    Assignment toModel() const;

signals:
    /** @brief Emitted when `id` changes. */
    void idChanged();
    /** @brief Emitted when `title` changes. */
    void titleChanged();
    /** @brief Emitted when `description` changes. */
    void descriptionChanged();
    /** @brief Emitted when `createdAt` changes. */
    void createdAtChanged();
    /** @brief Emitted when `updatedAt` changes. */
    void updatedAtChanged();
    /** @brief Emitted when `dueDate` changes. */
    void dueDateChanged();
    /** @brief Emitted when `courseId` changes. */
    void courseIdChanged();
    /** @brief Emitted when `courseName` changes. */
    void courseNameChanged();
    /** @brief Emitted when `userId` changes. */
    void userIdChanged();
    /** @brief Emitted when `priority` changes. */
    void priorityChanged();
    /** @brief Emitted when `status` changes. */
    void statusChanged();

private:
    int m_id;
    QString m_title;
    QString m_description;
    QString m_createdAt;
    QString m_updatedAt;
    QString m_dueDate;
    int m_courseId;
    QString m_courseName;
    int m_userId;
    int m_priority;
    QString m_status;
};
