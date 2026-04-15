#pragma once

#include <QAbstractListModel>
#include <QList>
#include "view/Models/headers/AssignmentViewModel.hpp"

class AssignmentListModel : public QAbstractListModel
{
    Q_OBJECT

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

private:
    QList<AssignmentViewModel*> m_assignments;
};