/**
 * @file HelpRequestViewModel.hpp
 * @brief QML property object for a help request, including optional raiser display name.
 */

#ifndef TODO_APP_HELPREQUESTVIEWMODEL_HPP
#define TODO_APP_HELPREQUESTVIEWMODEL_HPP

#include <QObject>
#include <QString>

class HelpRequestModel;

/**
 * @brief Mirrors `HelpRequestModel` fields for delegates and detail panes.
 */
class HelpRequestViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(int assignmentId READ assignmentId WRITE setAssignmentId NOTIFY assignmentIdChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString requestStatus READ requestStatus WRITE setRequestStatus NOTIFY requestStatusChanged)
    Q_PROPERTY(QString raiserDisplayName READ raiserDisplayName WRITE setRaiserDisplayName NOTIFY raiserDisplayNameChanged)

public:
    /** @brief Default-constructs with sentinel ids and empty strings. */
    explicit HelpRequestViewModel(QObject *parent = nullptr);
    /**
     * @brief Initializes from a backend help-request row.
     * @param model Source `HelpRequestModel`.
     * @param parent Optional Qt parent.
     */
    explicit HelpRequestViewModel(const HelpRequestModel &model, QObject *parent = nullptr);

    /** @return Help request id. */
    int id() const;
    /** @return Raiser user id. */
    int userId() const;
    /** @return Related assignment id. */
    int assignmentId() const;
    /** @return Message body. */
    QString message() const;
    /** @return Creation timestamp string. */
    QString createdAt() const;
    /** @return Request status string. */
    QString requestStatus() const;
    /** @return Display name for raiser (others’ list). */
    QString raiserDisplayName() const;

    /** @brief Sets id; notifies on change. */
    void setId(int value);
    /** @brief Sets raiser user id; notifies on change. */
    void setUserId(int value);
    /** @brief Sets assignment id; notifies on change. */
    void setAssignmentId(int value);
    /** @brief Sets message; notifies on change. */
    void setMessage(const QString &value);
    /** @brief Sets created-at; notifies on change. */
    void setCreatedAt(const QString &value);
    /** @brief Sets request status; notifies on change. */
    void setRequestStatus(const QString &value);
    /** @brief Sets raiser display name; notifies on change. */
    void setRaiserDisplayName(const QString &value);

    /**
     * @brief Copies all fields from `model` into this object.
     * @param model Backend help request.
     */
    void fromModel(const HelpRequestModel &model);

signals:
    /** @brief Emitted when `id` changes. */
    void idChanged();
    /** @brief Emitted when `userId` changes. */
    void userIdChanged();
    /** @brief Emitted when `assignmentId` changes. */
    void assignmentIdChanged();
    /** @brief Emitted when `message` changes. */
    void messageChanged();
    /** @brief Emitted when `createdAt` changes. */
    void createdAtChanged();
    /** @brief Emitted when `requestStatus` changes. */
    void requestStatusChanged();
    /** @brief Emitted when `raiserDisplayName` changes. */
    void raiserDisplayNameChanged();

private:
    int m_id;
    int m_userId;
    int m_assignmentId;
    QString m_message;
    QString m_createdAt;
    QString m_requestStatus;
    QString m_raiserDisplayName;
};

#endif // TODO_APP_HELPREQUESTVIEWMODEL_HPP
