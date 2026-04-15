#include "view/Controllers/headers/HelpRequestViewController.hpp"

#include <string>

HelpRequestViewController::HelpRequestViewController(HelpRequestController &helpRequestController,
                                                     HelpRequestListModel *myHelpRequestsModel,
                                                     HelpRequestListModel *othersHelpRequestsModel,
                                                     QObject *parent)
    : QObject(parent),
      m_helpRequestController(helpRequestController),
      m_myHelpRequestsModel(myHelpRequestsModel),
      m_othersHelpRequestsModel(othersHelpRequestsModel)
{
}

HelpRequestListModel *HelpRequestViewController::helpRequestModel() const
{
    return m_myHelpRequestsModel;
}

HelpRequestListModel *HelpRequestViewController::othersHelpRequestModel() const
{
    return m_othersHelpRequestsModel;
}

void HelpRequestViewController::loadHelpRequests(int userId)
{
    if (!m_myHelpRequestsModel) {
        emit loadHelpRequestsError(QStringLiteral("Help request model is not initialized"));
        return;
    }
    if (userId <= 0) {
        m_myHelpRequestsModel->clear();
        return;
    }

    GetAllHelpRequestResultPayload payload = m_helpRequestController.getAllHelpRequests(userId);
    if (payload.success) {
        m_myHelpRequestsModel->setHelpRequests(payload.helpRequests);
    } else {
        m_myHelpRequestsModel->clear();
        emit loadHelpRequestsError(QString::fromStdString(payload.errorMessage));
    }
}

void HelpRequestViewController::loadOthersHelpRequests(int userId)
{
    if (!m_othersHelpRequestsModel) {
        emit loadOthersHelpRequestsError(QStringLiteral("Others help request model is not initialized"));
        return;
    }
    if (userId <= 0) {
        m_othersHelpRequestsModel->clear();
        return;
    }

    GetAllHelpRequestResultPayload payload =
        m_helpRequestController.getHelpRequestsFromOtherUsers(userId);
    if (payload.success) {
        m_othersHelpRequestsModel->setHelpRequests(payload.helpRequests);
    } else {
        m_othersHelpRequestsModel->clear();
        emit loadOthersHelpRequestsError(QString::fromStdString(payload.errorMessage));
    }
}

void HelpRequestViewController::createHelpRequest(int userId, int assignmentId, const QString &message)
{
    if (userId <= 0) {
        emit createHelpRequestError(QStringLiteral("You must be signed in to request help"));
        return;
    }
    if (assignmentId <= 0) {
        emit createHelpRequestError(QStringLiteral("Missing assignment for this help request"));
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
