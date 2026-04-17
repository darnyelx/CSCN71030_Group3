/**
 * @file HelpRequestListModel.cpp
 * @brief List model roles and ownership of `HelpRequestViewModel` rows.
 */

#include "view/Models/headers/HelpRequestListModel.hpp"
#include "view/Models/headers/HelpRequestViewModel.hpp"

HelpRequestListModel::HelpRequestListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

HelpRequestListModel::~HelpRequestListModel()
{
    qDeleteAll(m_items);
    m_items.clear();
}

int HelpRequestListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_items.size();
}

QVariant HelpRequestListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return {};

    HelpRequestViewModel *row = m_items.at(index.row());
    if (!row)
        return {};

    switch (role) {
    case IdRole:
        return row->id();
    case UserIdRole:
        return row->userId();
    case AssignmentIdRole:
        return row->assignmentId();
    case MessageRole:
        return row->message();
    case CreatedAtRole:
        return row->createdAt();
    case RequestStatusRole:
        return row->requestStatus();
    case RaiserDisplayNameRole:
        return row->raiserDisplayName();
    default:
        return {};
    }
}

QHash<int, QByteArray> HelpRequestListModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {UserIdRole, "userId"},
        {AssignmentIdRole, "assignmentId"},
        {MessageRole, "message"},
        {CreatedAtRole, "createdAt"},
        {RequestStatusRole, "requestStatus"},
        {RaiserDisplayNameRole, "raiserDisplayName"},
    };
}

void HelpRequestListModel::setHelpRequests(const std::vector<HelpRequestModel> &items)
{
    beginResetModel();
    qDeleteAll(m_items);
    m_items.clear();
    for (const auto &hr : items) {
        auto *vm = new HelpRequestViewModel(hr, this);
        m_items.append(vm);
    }
    endResetModel();
}

void HelpRequestListModel::clear()
{
    beginResetModel();
    qDeleteAll(m_items);
    m_items.clear();
    endResetModel();
}

HelpRequestViewModel *HelpRequestListModel::get(int index) const
{
    if (index < 0 || index >= m_items.size())
        return nullptr;
    return m_items.at(index);
}

int HelpRequestListModel::entryCount() const
{
    return m_items.size();
}
