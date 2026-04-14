#ifndef TODO_APP_HELPREQUESTVIEWCONTROLLER_HPP
#define TODO_APP_HELPREQUESTVIEWCONTROLLER_HPP

#include <QObject>
#include <QString>

#include "api/HelpRequestController.hpp"
#include "view/Models/headers/HelpRequestListModel.hpp"

class HelpRequestViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HelpRequestListModel *helpRequestModel READ helpRequestModel CONSTANT)

public:
    explicit HelpRequestViewController(HelpRequestController &helpRequestController,
                                       HelpRequestListModel *helpRequestModel,
                                       QObject *parent = nullptr);

    HelpRequestListModel *helpRequestModel() const;

    Q_INVOKABLE void loadHelpRequests(int userId);
    Q_INVOKABLE void createHelpRequest(int userId, int assignmentId, const QString &message);

signals:
    void loadHelpRequestsError(const QString &message);
    void createHelpRequestSuccess();
    void createHelpRequestError(const QString &message);

private:
    HelpRequestController &m_helpRequestController;
    HelpRequestListModel *m_helpRequestModel;
};

#endif
