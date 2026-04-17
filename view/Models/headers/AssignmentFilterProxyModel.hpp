/**
 * @file AssignmentFilterProxyModel.hpp
 * @brief Client-side filter for assignments: status and case-insensitive substring on title/description.
 */

#pragma once

#include <QSortFilterProxyModel>

class AssignmentListModel;
class AssignmentViewModel;

/**
 * @brief Sits on top of `AssignmentListModel`; `statusFilter` uses 0=All, 1=Pending, 2=In Progress, 3=Done.
 * @details `filterAcceptsRow` combines substring search on title/description with optional status bucket.
 */
class AssignmentFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY filterChanged)
    Q_PROPERTY(int statusFilter READ statusFilter WRITE setStatusFilter NOTIFY filterChanged)

public:
    /** @brief Constructs an unconnected proxy (call `setSourceAssignments` before use). */
    explicit AssignmentFilterProxyModel(QObject *parent = nullptr);

    /**
     * @brief Sets the source model to an `AssignmentListModel` and enables dynamic filtering.
     * @param source Concrete list model; may be nullptr to detach.
     */
    void setSourceAssignments(AssignmentListModel *source);

    /** @return Current stored search string (filtering compares case-insensitively). */
    QString searchText() const { return m_searchText; }
    /**
     * @brief Sets substring filter text, invalidates filter, emits `filterChanged`.
     * @param text New search string (empty shows all titles/descriptions).
     */
    void setSearchText(const QString &text);

    /** @return Status bucket: 0 All, 1 Pending, 2 In Progress, 3 Done (Completed). */
    int statusFilter() const { return m_statusFilter; }
    /**
     * @brief Sets status bucket and reapplies the filter.
     * @param value One of 0–3 as documented on the property.
     */
    void setStatusFilter(int value);

    /**
     * @brief Maps a proxy row index to the underlying `AssignmentViewModel` (for QML delegates).
     * @param row Index in the filtered (proxy) model.
     * @return Source view model or nullptr if invalid.
     */
    Q_INVOKABLE AssignmentViewModel *get(int row) const;

signals:
    /** @brief Emitted when `searchText` or `statusFilter` changes. */
    void filterChanged();

protected:
    /**
     * @brief Qt hook: returns whether the source row passes text and status filters.
     * @param sourceRow Row index in the source model.
     * @param sourceParent Parent index (unused for flat list).
     */
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_searchText;
    int m_statusFilter = 0;
};
