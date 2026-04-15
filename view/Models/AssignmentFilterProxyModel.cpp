#include "view/Models/headers/AssignmentFilterProxyModel.hpp"
#include "view/Models/headers/AssignmentListModel.hpp"
#include "view/Models/headers/AssignmentViewModel.hpp"

AssignmentFilterProxyModel::AssignmentFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(false);
}

void AssignmentFilterProxyModel::setSourceAssignments(AssignmentListModel *source)
{
    setSourceModel(source);
}

void AssignmentFilterProxyModel::setSearchText(const QString &text)
{
    if (text == m_searchText) {
        return;
    }
    beginFilterChange();
    m_searchText = text;
    endFilterChange(Direction::Rows);
    emit filterChanged();
}

void AssignmentFilterProxyModel::setStatusFilter(int value)
{
    if (value < 0) {
        value = 0;
    }
    if (value > 3) {
        value = 3;
    }
    if (value == m_statusFilter) {
        return;
    }
    beginFilterChange();
    m_statusFilter = value;
    endFilterChange(Direction::Rows);
    emit filterChanged();
}

bool AssignmentFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (sourceParent.isValid()) {
        return false;
    }

    const QAbstractItemModel *src = sourceModel();
    if (!src) {
        return false;
    }

    const QModelIndex idx = src->index(sourceRow, 0);
    if (!idx.isValid()) {
        return false;
    }

    const QString status = src->data(idx, AssignmentListModel::StatusRole).toString();

    switch (m_statusFilter) {
    case 1:
        if (status != QStringLiteral("Pending")) {
            return false;
        }
        break;
    case 2:
        if (status != QStringLiteral("In Progress")) {
            return false;
        }
        break;
    case 3:
        if (status != QStringLiteral("Completed")) {
            return false;
        }
        break;
    default:
        break;
    }

    const QString needle = m_searchText.trimmed();
    if (needle.isEmpty()) {
        return true;
    }

    const QString title = src->data(idx, AssignmentListModel::TitleRole).toString();
    const QString desc = src->data(idx, AssignmentListModel::DescriptionRole).toString();
    return title.contains(needle, Qt::CaseInsensitive) || desc.contains(needle, Qt::CaseInsensitive);
}

AssignmentViewModel *AssignmentFilterProxyModel::get(int row) const
{
    const QModelIndex proxyIndex = index(row, 0);
    if (!proxyIndex.isValid()) {
        return nullptr;
    }
    const QModelIndex sourceIndex = mapToSource(proxyIndex);
    if (!sourceIndex.isValid()) {
        return nullptr;
    }
    auto *list = qobject_cast<AssignmentListModel *>(sourceModel());
    if (!list) {
        return nullptr;
    }
    return list->get(sourceIndex.row());
}
