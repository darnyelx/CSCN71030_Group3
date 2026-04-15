#pragma once

#include <QAbstractListModel>
#include <QList>
#include "view/Models/headers/AssignmentViewModel.hpp"

class AssignmentListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int totalCount READ totalCount NOTIFY assignmentCountsChanged)
    Q_PROPERTY(int pendingCount READ pendingCount NOTIFY assignmentCountsChanged)
    Q_PROPERTY(int inProgressCount READ inProgressCount NOTIFY assignmentCountsChanged)
    Q_PROPERTY(int completedCount READ completedCount NOTIFY assignmentCountsChanged)

public:
    explicit AssignmentListModel(QObject *parent = nullptr);
    ~AssignmentListModel() override;

    enum AssignmentRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        DescriptionRole,
        CreatedAtRole,
        UpdatedAtRole,
        DueDateRole,
        CourseIdRole,
        CourseNameRole,
        UserIdRole,
        PriorityRole,
        StatusRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setAssignments(const std::vector<Assignment> &assignments);
    void clear();

    Q_INVOKABLE AssignmentViewModel *get(int index) const;

    int totalCount() const { return m_totalCount; }
    int pendingCount() const { return m_pendingCount; }
    int inProgressCount() const { return m_inProgressCount; }
    int completedCount() const { return m_completedCount; }

signals:
    void assignmentCountsChanged();

private:
    void refreshCounts();

    QList<AssignmentViewModel *> m_assignments;
    int m_totalCount = 0;
    int m_pendingCount = 0;
    int m_inProgressCount = 0;
    int m_completedCount = 0;
};