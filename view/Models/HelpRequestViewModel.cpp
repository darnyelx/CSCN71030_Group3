#include "view/Models/headers/HelpRequestViewModel.hpp"
#include "api/HelpRequestModel.hpp"

HelpRequestViewModel::HelpRequestViewModel(QObject *parent)
    : QObject(parent),
      m_id(-1),
      m_userId(-1),
      m_assignmentId(-1)
{
}

HelpRequestViewModel::HelpRequestViewModel(const HelpRequestModel &model, QObject *parent)
    : QObject(parent),
      m_id(-1),
      m_userId(-1),
      m_assignmentId(-1)
{
    fromModel(model);
}

int HelpRequestViewModel::id() const { return m_id; }
int HelpRequestViewModel::userId() const { return m_userId; }
int HelpRequestViewModel::assignmentId() const { return m_assignmentId; }
QString HelpRequestViewModel::message() const { return m_message; }
QString HelpRequestViewModel::createdAt() const { return m_createdAt; }
QString HelpRequestViewModel::requestStatus() const { return m_requestStatus; }
QString HelpRequestViewModel::raiserDisplayName() const { return m_raiserDisplayName; }

void HelpRequestViewModel::setId(int value)
{
    if (m_id == value)
        return;
    m_id = value;
    emit idChanged();
}

void HelpRequestViewModel::setUserId(int value)
{
    if (m_userId == value)
        return;
    m_userId = value;
    emit userIdChanged();
}

void HelpRequestViewModel::setAssignmentId(int value)
{
    if (m_assignmentId == value)
        return;
    m_assignmentId = value;
    emit assignmentIdChanged();
}

void HelpRequestViewModel::setMessage(const QString &value)
{
    if (m_message == value)
        return;
    m_message = value;
    emit messageChanged();
}

void HelpRequestViewModel::setCreatedAt(const QString &value)
{
    if (m_createdAt == value)
        return;
    m_createdAt = value;
    emit createdAtChanged();
}

void HelpRequestViewModel::setRequestStatus(const QString &value)
{
    if (m_requestStatus == value)
        return;
    m_requestStatus = value;
    emit requestStatusChanged();
}

void HelpRequestViewModel::setRaiserDisplayName(const QString &value)
{
    if (m_raiserDisplayName == value)
        return;
    m_raiserDisplayName = value;
    emit raiserDisplayNameChanged();
}

void HelpRequestViewModel::fromModel(const HelpRequestModel &model)
{
    setId(model.getId());
    setUserId(model.getUserId());
    setAssignmentId(model.getAssignmentId());
    setMessage(QString::fromStdString(model.getMessage()));
    setCreatedAt(QString::fromStdString(model.getCreatedAt()));
    setRequestStatus(QString::fromStdString(model.getRequestStatus()));
    setRaiserDisplayName(QString::fromStdString(model.getRaiserDisplayName()));
}
