/**
 * @file AssignmentListModel.hpp
 * @brief `QAbstractListModel` of `AssignmentViewModel` rows with aggregate status counts for the UI.
 */

#pragma once

#include <QAbstractListModel>
#include <QList>
#include "view/Models/headers/AssignmentViewModel.hpp"

/**
 * @brief Backing model for assignment lists; roles map to delegate bindings.
 * @details Owns `AssignmentViewModel` pointers; `setAssignments` replaces content and recomputes status counts.
 */
class AssignmentListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int totalCount READ totalCount NOTIFY assignmentCountsChanged)
    Q_PROPERTY(int pendingCount READ pendingCount NOTIFY assignmentCountsChanged)
    Q_PROPERTY(int inProgressCount READ inProgressCount NOTIFY assignmentCountsChanged)
    Q_PROPERTY(int completedCount READ completedCount NOTIFY assignmentCountsChanged)

public:
    /** @brief Constructs an empty model. */
    explicit AssignmentListModel(QObject *parent = nullptr);
    /** @brief Destroys owned view models. */
    ~AssignmentListModel() override;

    /**
     * @brief Custom roles for QML `ListView` delegates (beyond `Qt::DisplayRole`).
     */
    enum AssignmentRoles {
        IdRole = Qt::UserRole + 1, /**< Primary key. */
        TitleRole, /**< Title string. */
        DescriptionRole, /**< Body text. */
        CreatedAtRole, /**< Created timestamp. */
        UpdatedAtRole, /**< Updated timestamp. */
        DueDateRole, /**< Due date. */
        CourseIdRole, /**< Course fk. */
        CourseNameRole, /**< Joined course name. */
        UserIdRole, /**< Owner user id. */
        PriorityRole, /**< Priority value. */
        StatusRole /**< Status string. */
    };

    /**
     * @brief Returns the number of assignment rows.
     * @param parent Parent index; must be invalid for a flat list (otherwise returns 0).
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns data for the given index and role (title, status, etc.).
     * @param index Row in the list; column ignored.
     * @param role `AssignmentRoles` or display role.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Maps integer roles to QML role names.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Replaces all rows with view models built from `assignments`.
     * @param assignments Backend rows (typically from controller fetch).
     */
    void setAssignments(const std::vector<Assignment> &assignments);

    /** @brief Removes all rows and resets counts to zero. */
    void clear();

    /**
     * @brief Returns the view model at `index` for QML detail dialogs (caller must not delete).
     * @param index Zero-based row.
     * @return Pointer owned by this model, or nullptr if out of range.
     */
    Q_INVOKABLE AssignmentViewModel *get(int index) const;

    /** @return Total number of assignments in the model. */
    int totalCount() const { return m_totalCount; }
    /** @return Count whose status normalizes to Pending. */
    int pendingCount() const { return m_pendingCount; }
    /** @return Count whose status normalizes to In Progress. */
    int inProgressCount() const { return m_inProgressCount; }
    /** @return Count whose status normalizes to Completed/Done. */
    int completedCount() const { return m_completedCount; }

signals:
    /** @brief Emitted when any of the aggregate count properties change after a data reload. */
    void assignmentCountsChanged();

private:
    /** @brief Recomputes `m_*Count` from current rows and emits `assignmentCountsChanged` if needed. */
    void refreshCounts();

    QList<AssignmentViewModel *> m_assignments;
    int m_totalCount = 0;
    int m_pendingCount = 0;
    int m_inProgressCount = 0;
    int m_completedCount = 0;
};
