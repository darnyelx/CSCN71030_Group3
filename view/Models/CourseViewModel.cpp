/**
 * @file CourseViewModel.cpp
 * @brief Course id/name properties and `fromModel` for QML.
 */

#include "view/Models/headers/CourseViewModel.hpp"

CourseViewModel::CourseViewModel(QObject *parent)
    : QObject(parent)
{
}

CourseViewModel::CourseViewModel(const Course &course, QObject *parent)
    : QObject(parent)
{
    fromModel(course);
}

int CourseViewModel::id() const
{
    return m_id;
}

QString CourseViewModel::name() const
{
    return m_name;
}

void CourseViewModel::setId(int value)
{
    if (m_id == value) return;
    m_id = value;
    emit idChanged();
}

void CourseViewModel::setName(const QString &value)
{
    if (m_name == value) return;
    m_name = value;
    emit nameChanged();
}

void CourseViewModel::fromModel(const Course &course)
{
    setId(course.getId());
    setName(QString::fromStdString(course.getName()));
}