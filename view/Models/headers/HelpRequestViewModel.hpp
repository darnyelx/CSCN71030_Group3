#ifndef TODO_APP_HELPREQUESTVIEWMODEL_HPP
#define TODO_APP_HELPREQUESTVIEWMODEL_HPP

#include <QObject>
#include <QString>

class HelpRequestModel;

class HelpRequestViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(int assignmentId READ assignmentId WRITE setAssignmentId NOTIFY assignmentIdChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString requestStatus READ requestStatus WRITE setRequestStatus NOTIFY requestStatusChanged)

public:
    explicit HelpRequestViewModel(QObject *parent = nullptr);
    explicit HelpRequestViewModel(const HelpRequestModel &model, QObject *parent = nullptr);

    int id() const;
    int userId() const;
    int assignmentId() const;
    QString message() const;
    QString createdAt() const;
    QString requestStatus() const;

    void setId(int value);
    void setUserId(int value);
    void setAssignmentId(int value);
    void setMessage(const QString &value);
    void setCreatedAt(const QString &value);
    void setRequestStatus(const QString &value);

    void fromModel(const HelpRequestModel &model);

signals:
    void idChanged();
    void userIdChanged();
    void assignmentIdChanged();
    void messageChanged();
    void createdAtChanged();
    void requestStatusChanged();

private:
    int m_id;
    int m_userId;
    int m_assignmentId;
    QString m_message;
    QString m_createdAt;
    QString m_requestStatus;
};

#endif
