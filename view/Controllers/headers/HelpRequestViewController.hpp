/**
 * @file HelpRequestViewController.hpp
 * @brief QML bridge for loading and creating help requests (mine vs. others' lists).
 */

#ifndef TODO_APP_HELPREQUESTVIEWCONTROLLER_HPP
#define TODO_APP_HELPREQUESTVIEWCONTROLLER_HPP

#include <QObject>
#include <QString>

#include "api/HelpRequestController.hpp"
#include "view/Models/headers/HelpRequestListModel.hpp"

/**
 * @brief Binds two `HelpRequestListModel` instances: current user's requests and peers' requests.
 */
class HelpRequestViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HelpRequestListModel *helpRequestModel READ helpRequestModel CONSTANT)
    Q_PROPERTY(HelpRequestListModel *othersHelpRequestModel READ othersHelpRequestModel CONSTANT)

public:
    /**
     * @brief Constructs the controller with backend and two list models.
     * @param helpRequestController Help-request API.
     * @param myHelpRequestsModel Model populated by `loadHelpRequests`.
     * @param othersHelpRequestsModel Model populated by `loadOthersHelpRequests`.
     * @param parent Optional Qt parent.
     */
    explicit HelpRequestViewController(HelpRequestController &helpRequestController,
                                       HelpRequestListModel *myHelpRequestsModel,
                                       HelpRequestListModel *othersHelpRequestsModel,
                                       QObject *parent = nullptr);

    /** @return Model for the signed-in user’s own help requests. */
    HelpRequestListModel *helpRequestModel() const;
    /** @return Model for other users’ help requests (with display names when available). */
    HelpRequestListModel *othersHelpRequestModel() const;

    /**
     * @brief Loads `getAllHelpRequests(userId)` into `helpRequestModel`.
     * @param userId Current user id.
     */
    Q_INVOKABLE void loadHelpRequests(int userId);

    /**
     * @brief Loads `getHelpRequestsFromOtherUsers(userId)` into `othersHelpRequestModel`.
     * @param userId Current user id (used to exclude own requests).
     */
    Q_INVOKABLE void loadOthersHelpRequests(int userId);

    /**
     * @brief Creates a help request for an assignment and signals success or error.
     * @param userId Raiser id.
     * @param assignmentId Target assignment.
     * @param message Request body text.
     */
    Q_INVOKABLE void createHelpRequest(int userId, int assignmentId, const QString &message);

signals:
    /** @brief Emitted when loading “my” requests fails. */
    void loadHelpRequestsError(const QString &message);
    /** @brief Emitted when loading others’ requests fails. */
    void loadOthersHelpRequestsError(const QString &message);
    /** @brief Emitted after successful create. */
    void createHelpRequestSuccess();
    /** @brief Emitted when create fails (includes backend message). */
    void createHelpRequestError(const QString &message);

private:
    HelpRequestController &m_helpRequestController;
    HelpRequestListModel *m_myHelpRequestsModel;
    HelpRequestListModel *m_othersHelpRequestsModel;
};

#endif // TODO_APP_HELPREQUESTVIEWCONTROLLER_HPP
