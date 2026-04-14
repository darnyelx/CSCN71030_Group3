#ifndef TODO_APP_HELPREQUESTLISTMODEL_HPP
#define TODO_APP_HELPREQUESTLISTMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <vector>

#include "api/HelpRequestModel.hpp"

class HelpRequestViewModel;

class HelpRequestListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit HelpRequestListModel(QObject *parent = nullptr);
    ~HelpRequestListModel() override;

    enum Roles {
        IdRole = Qt::UserRole + 1,
        UserIdRole,
        AssignmentIdRole,
        MessageRole,
        CreatedAtRole,
        RequestStatusRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setHelpRequests(const std::vector<HelpRequestModel> &items);
    void clear();

    Q_INVOKABLE HelpRequestViewModel *get(int index) const;
    Q_INVOKABLE int entryCount() const;

private:
    QList<HelpRequestViewModel *> m_items;
};

#endif
