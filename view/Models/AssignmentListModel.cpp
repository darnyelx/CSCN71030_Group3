/**
 * @file AssignmentListModel.cpp
 * @brief Model indexes, roles, and status count maintenance for assignment rows.
 */

#include "view/Models/headers/AssignmentListModel.hpp"
#include "view/Models/headers/AssignmentViewModel.hpp"

#include <QString>

AssignmentListModel::AssignmentListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

AssignmentListModel::~AssignmentListModel()
{
    qDeleteAll(m_assignments);
    m_assignments.clear();
}

int AssignmentListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_assignments.size();
}

QVariant AssignmentListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_assignments.size()) {
        return {};
    }

    AssignmentViewModel *assignment = m_assignments.at(index.row());
    if (!assignment) {
        return {};
    }

    switch (role) {
        case IdRole:
            return assignment->id();
        case TitleRole:
            return assignment->title();
        case DescriptionRole:
            return assignment->description();
        case CreatedAtRole:
            return assignment->createdAt();
        case UpdatedAtRole:
            return assignment->updatedAt();
        case DueDateRole:
            return assignment->dueDate();
        case CourseIdRole:
            return assignment->courseId();
        case CourseNameRole:
            return assignment->courseName();
        case UserIdRole:
            return assignment->userId();
        case PriorityRole:
            return assignment->priority();
        case StatusRole:
            return assignment->status();
        default:
            return {};
    }
}

QHash<int, QByteArray> AssignmentListModel::roleNames() const
{
    return {
        { IdRole, "id" },
        { TitleRole, "title" },
        { DescriptionRole, "description" },
        { CreatedAtRole, "createdAt" },
        { UpdatedAtRole, "updatedAt" },
        { DueDateRole, "dueDate" },
        { CourseIdRole, "courseId" },
        { CourseNameRole, "courseName" },
        { UserIdRole, "userId" },
        { PriorityRole, "priority" },
        { StatusRole, "status" }
    };
}

void AssignmentListModel::setAssignments(const std::vector<Assignment> &assignments)
{
    beginResetModel();

    qDeleteAll(m_assignments);
    m_assignments.clear();

    for (const auto &assignment : assignments) {
        auto *assignmentViewModel = new AssignmentViewModel(this);
        assignmentViewModel->fromModel(assignment);
        m_assignments.append(assignmentViewModel);
    }

    refreshCounts();
    endResetModel();
    emit assignmentCountsChanged();
}

void AssignmentListModel::clear()
{
    beginResetModel();
    qDeleteAll(m_assignments);
    m_assignments.clear();
    refreshCounts();
    endResetModel();
    emit assignmentCountsChanged();
}

AssignmentViewModel* AssignmentListModel::get(int index) const
{
    if (index < 0 || index >= m_assignments.size()) {
        return nullptr;
    }

    return m_assignments.at(index);
}

void AssignmentListModel::refreshCounts()
{
    m_totalCount = m_assignments.size();
    m_pendingCount = 0;
    m_inProgressCount = 0;
    m_completedCount = 0;

    for (AssignmentViewModel *assignment : m_assignments) {
        if (!assignment) {
            continue;
        }
        const QString status = assignment->status();
        if (status == QStringLiteral("Pending")) {
            ++m_pendingCount;
        } else if (status == QStringLiteral("In Progress")) {
            ++m_inProgressCount;
        } else if (status == QStringLiteral("Completed")) {
            ++m_completedCount;
        } else {
            ++m_pendingCount;
        }
    }
}