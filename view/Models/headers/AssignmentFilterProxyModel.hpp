#pragma once

#include <QSortFilterProxyModel>

class AssignmentListModel;
class AssignmentViewModel;

/**
 * Client-side filter for assignments: status (All / Pending / In Progress / Done)
 * and case-insensitive substring match on title and description.
 */
class AssignmentFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY filterChanged)
    Q_PROPERTY(int statusFilter READ statusFilter WRITE setStatusFilter NOTIFY filterChanged)

public:
    explicit AssignmentFilterProxyModel(QObject *parent = nullptr);

    void setSourceAssignments(AssignmentListModel *source);

    QString searchText() const { return m_searchText; }
    void setSearchText(const QString &text);

    /** 0 = All, 1 = Pending, 2 = In Progress, 3 = Done (Completed) */
    int statusFilter() const { return m_statusFilter; }
    void setStatusFilter(int value);

    Q_INVOKABLE AssignmentViewModel *get(int row) const;

signals:
    void filterChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_searchText;
    int m_statusFilter = 0;
};
