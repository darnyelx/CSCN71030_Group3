/**
 * @file AssignmentViewModel.cpp
 * @brief `Assignment` ↔ `AssignmentViewModel` mapping for forms and delegates.
 */

#include "view/Models/headers/AssignmentViewModel.hpp"
#include "api/AssignmentModel.hpp"

AssignmentViewModel::AssignmentViewModel(QObject *parent)
    : QObject(parent),
      m_id(-1),
      m_courseId(0),
      m_userId(0),
      m_priority(0),
      m_status(QStringLiteral("Pending"))
{
}

AssignmentViewModel::AssignmentViewModel(const Assignment& assignment, QObject *parent)
    : QObject(parent),
      m_id(-1),
      m_courseId(0),
      m_userId(0),
      m_priority(0)
{
    fromModel(assignment);
}

int AssignmentViewModel::id() const
{
    return m_id;
}

QString AssignmentViewModel::title() const
{
    return m_title;
}

QString AssignmentViewModel::description() const
{
    return m_description;
}

QString AssignmentViewModel::createdAt() const
{
    return m_createdAt;
}

QString AssignmentViewModel::updatedAt() const
{
    return m_updatedAt;
}

QString AssignmentViewModel::dueDate() const
{
    return m_dueDate;
}

int AssignmentViewModel::courseId() const
{
    return m_courseId;
}

QString AssignmentViewModel::courseName() const
{
    return m_courseName;
}

int AssignmentViewModel::userId() const
{
    return m_userId;
}

int AssignmentViewModel::priority() const
{
    return m_priority;
}

QString AssignmentViewModel::status() const
{
    return m_status;
}

void AssignmentViewModel::setId(int value)
{
    if (m_id == value) return;
    m_id = value;
    emit idChanged();
}

void AssignmentViewModel::setTitle(const QString& value)
{
    if (m_title == value) return;
    m_title = value;
    emit titleChanged();
}

void AssignmentViewModel::setDescription(const QString& value)
{
    if (m_description == value) return;
    m_description = value;
    emit descriptionChanged();
}

void AssignmentViewModel::setCreatedAt(const QString& value)
{
    if (m_createdAt == value) return;
    m_createdAt = value;
    emit createdAtChanged();
}

void AssignmentViewModel::setUpdatedAt(const QString& value)
{
    if (m_updatedAt == value) return;
    m_updatedAt = value;
    emit updatedAtChanged();
}

void AssignmentViewModel::setDueDate(const QString& value)
{
    if (m_dueDate == value) return;
    m_dueDate = value;
    emit dueDateChanged();
}

void AssignmentViewModel::setCourseId(int value)
{
    if (m_courseId == value) return;
    m_courseId = value;
    emit courseIdChanged();
}

void AssignmentViewModel::setCourseName(const QString &value)
{
    if (m_courseName == value) return;
    m_courseName = value;
    emit courseNameChanged();
}

void AssignmentViewModel::setUserId(int value)
{
    if (m_userId == value) return;
    m_userId = value;
    emit userIdChanged();
}

void AssignmentViewModel::setPriority(int value)
{
    if (m_priority == value) return;
    m_priority = value;
    emit priorityChanged();
}

void AssignmentViewModel::setStatus(const QString &value)
{
    if (m_status == value) return;
    m_status = value;
    emit statusChanged();
}

void AssignmentViewModel::fromModel(const Assignment& assignment)
{
    setId(assignment.getId());
    setTitle(QString::fromStdString(assignment.getTitle()));
    setDescription(QString::fromStdString(assignment.getDescription()));
    setCreatedAt(QString::fromStdString(assignment.getCreatedAt()));
    setUpdatedAt(QString::fromStdString(assignment.getUpdatedAt()));
    setDueDate(QString::fromStdString(assignment.getDueDate()));
    setCourseId(assignment.getCourseId());
    setCourseName(QString::fromStdString(assignment.getCourseName()));
    setUserId(assignment.getUserId());
    setPriority(assignment.getPriority());
    setStatus(QString::fromStdString(assignment.getStatus()));
}

Assignment AssignmentViewModel::toModel() const
{
    Assignment assignment;
    assignment
        .setId(m_id)
        .setTitle(m_title.toStdString())
        .setDescription(m_description.toStdString())
        .setCreatedAt(m_createdAt.toStdString())
        .setUpdatedAt(m_updatedAt.toStdString())
        .setDueDate(m_dueDate.toStdString())
        .setCourseId(m_courseId)
        .setUserId(m_userId)
        .setPriority(m_priority)
        .setStatus(m_status.toStdString());

    return assignment;
}