#include "view/Models/headers/AssignmentListModel.hpp"
#include "view/Models/headers/AssignmentViewModel.hpp"

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
        case UserIdRole:
            return assignment->userId();
        case PriorityRole:
            return assignment->priority();
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
        { UserIdRole, "userId" },
        { PriorityRole, "priority" }
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

    endResetModel();
}

void AssignmentListModel::clear()
{
    beginResetModel();
    qDeleteAll(m_assignments);
    m_assignments.clear();
    endResetModel();
}

AssignmentViewModel* AssignmentListModel::get(int index) const
{
    if (index < 0 || index >= m_assignments.size()) {
        return nullptr;
    }

    return m_assignments.at(index);
}