/**
 * @file HelpRequestListModel.hpp
 * @brief `QAbstractListModel` of `HelpRequestViewModel` for "my requests" and "others'" lists.
 */

#ifndef TODO_APP_HELPREQUESTLISTMODEL_HPP
#define TODO_APP_HELPREQUESTLISTMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <vector>

#include "api/HelpRequestModel.hpp"

class HelpRequestViewModel;

/**
 * @brief Role names align with QML bindings for list delegates.
 * @details Two instances are typically used in parallel: one for the current user’s requests and one for peers.
 */
class HelpRequestListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /** @brief Constructs an empty help-request list. */
    explicit HelpRequestListModel(QObject *parent = nullptr);
    /** @brief Destroys owned `HelpRequestViewModel` rows. */
    ~HelpRequestListModel() override;

    /**
     * @brief Custom roles exposed to QML `ListView`.
     */
    enum Roles {
        IdRole = Qt::UserRole + 1, /**< Help request id. */
        UserIdRole, /**< Raiser user id. */
        AssignmentIdRole, /**< Target assignment id. */
        MessageRole, /**< Request body. */
        CreatedAtRole, /**< Creation timestamp. */
        RequestStatusRole, /**< Status string. */
        RaiserDisplayNameRole /**< Display name when listing others’ requests. */
    };

    /**
     * @brief Row count for the flat list.
     * @param parent Must be invalid for top-level row count.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns the field identified by `role` for the given row.
     * @param index Row index; column unused.
     * @param role One of `Roles` or display role.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Maps integer roles to role names (`"id"`, `"userId"`, etc.) for QML.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Replaces all rows with view models built from backend items.
     * @param items Help requests from `HelpRequestController` (or stub DB).
     */
    void setHelpRequests(const std::vector<HelpRequestModel> &items);

    /** @brief Clears all rows from the model. */
    void clear();

    /**
     * @brief Returns the view model at `index` (owned by this model; do not delete).
     * @param index Zero-based row.
     */
    Q_INVOKABLE HelpRequestViewModel *get(int index) const;

    /**
     * @brief QML helper returning `rowCount` for the root index.
     * @return Number of entries currently in the model.
     */
    Q_INVOKABLE int entryCount() const;

private:
    QList<HelpRequestViewModel *> m_items;
};

#endif // TODO_APP_HELPREQUESTLISTMODEL_HPP
