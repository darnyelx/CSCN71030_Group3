#include "view/Controllers/headers/HelpRequestViewController.hpp"

#include <string>

HelpRequestViewController::HelpRequestViewController(HelpRequestController &helpRequestController,
                                                     HelpRequestListModel *helpRequestModel,
                                                     QObject *parent)
    : QObject(parent),
      m_helpRequestController(helpRequestController),
      m_helpRequestModel(helpRequestModel)
{
}

HelpRequestListModel *HelpRequestViewController::helpRequestModel() const
{
    return m_helpRequestModel;
}

void HelpRequestViewController::loadHelpRequests(int userId)
{
    if (!m_helpRequestModel) {
        emit loadHelpRequestsError(QStringLiteral("Help request model is not initialized"));
        return;
    }
    if (userId <= 0) {
        m_helpRequestModel->clear();
        return;
    }

    GetAllHelpRequestResultPayload payload = m_helpRequestController.getAllHelpRequests(userId);
    if (payload.success) {
        m_helpRequestModel->setHelpRequests(payload.helpRequests);
    } else {
        m_helpRequestModel->clear();
        emit loadHelpRequestsError(QString::fromStdString(payload.errorMessage));
    }
}

void HelpRequestViewController::createHelpRequest(int userId, int assignmentId, const QString &message)
{
    if (!m_helpRequestModel) {
        emit createHelpRequestError(QStringLiteral("Help request model is not initialized"));
        return;
    }
    if (userId <= 0) {
        emit createHelpRequestError(QStringLiteral("You must be signed in to request help"));
        return;
    }

    const QString trimmed = message.trimmed();
    if (trimmed.isEmpty()) {
        emit createHelpRequestError(QStringLiteral("Please describe what you need help with"));
        return;
    }

    const std::string msg = trimmed.toStdString();
    HelpRequestResultPayload r =
        m_helpRequestController.createHelpRequest(userId, assignmentId, msg);
    if (r.success) {
        emit createHelpRequestSuccess();
    } else {
        emit createHelpRequestError(QString::fromStdString(r.errorMessage));
    }
}
