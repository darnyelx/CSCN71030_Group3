//
// Created by Darnyelx on 2026-04-10.
//

#include "view/Models/headers/CourseListModel.hpp"
#include <QVariant>

CourseListModel::CourseListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

CourseListModel::~CourseListModel()
{
    qDeleteAll(m_courses);
    m_courses.clear();
}

int CourseListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_courses.size();
}

QVariant CourseListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_courses.size()) {
        return {};
    }

    CourseViewModel *course = m_courses.at(index.row());
    if (!course) {
        return {};
    }

    switch (role) {
        case IdRole:
            return course->id();
        case NameRole:
            return course->name();
        default:
            return {};
    }
}

QHash<int, QByteArray> CourseListModel::roleNames() const
{
    return {
            { IdRole, "id" },
            { NameRole, "name" }
    };
}

void CourseListModel::setCourses(const std::vector<Course> &courses)
{
    beginResetModel();

    qDeleteAll(m_courses);
    m_courses.clear();

    for (const auto &course : courses) {
        auto *courseViewModel = new CourseViewModel(this);
        courseViewModel->fromModel(course);
        m_courses.append(courseViewModel);
    }

    endResetModel();
}

void CourseListModel::clear()
{
    beginResetModel();
    qDeleteAll(m_courses);
    m_courses.clear();
    endResetModel();
}

CourseViewModel* CourseListModel::get(int index) const
{
    if (index < 0 || index >= m_courses.size()) {
        return nullptr;
    }

    return m_courses.at(index);
}