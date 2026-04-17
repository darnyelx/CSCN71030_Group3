/**
 * @file AssignmentViewController.hpp
 * @brief QML bridge for assignment CRUD and the list/filter models used by the coordinator view.
 */

#ifndef TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
#define TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP

#include "api/AssignmentController.hpp"
#include "view/Models/headers/AssignmentFilterProxyModel.hpp"
#include "view/Models/headers/AssignmentListModel.hpp"
#include <QObject>
#include <QString>

/**
 * @brief Wires `AssignmentController` to `AssignmentListModel` and `AssignmentFilterProxyModel` for QML.
 * @details Creates an internal `AssignmentFilterProxyModel` whose source is the injected list model.
 */
class AssignmentViewController : public QObject {
	Q_OBJECT
	Q_PROPERTY(AssignmentListModel* assignmentModel READ getAssignmentModel CONSTANT)
	Q_PROPERTY(AssignmentFilterProxyModel* assignmentFilter READ assignmentFilter CONSTANT)

public:
	/**
	 * @brief Constructs the controller and attaches the filter proxy to `assignmentModel`.
	 * @param assignmentController Backend assignment API.
	 * @param assignmentModel List model updated by fetch/create/update flows.
	 * @param parent Optional Qt parent.
	 */
	explicit AssignmentViewController(AssignmentController &assignmentController,
	                                  AssignmentListModel *assignmentModel, QObject *parent = nullptr);

	/**
	 * @brief Loads assignments for `userId` into `assignmentModel`, or clears and signals on failure.
	 * @param userId Signed-in user’s id.
	 */
	Q_INVOKABLE void getUserAssignments(int userId);

	/**
	 * @brief Creates an assignment from QML-bound fields (title, description, course, user, due date, status).
	 * @param assignmentModel Non-null view model; null emits `createAssignmentError`.
	 */
	Q_INVOKABLE void createAssignment(AssignmentViewModel *assignmentModel);

	/**
	 * @brief Updates an existing row identified by `assignmentId` using fields from `assignmentModel`.
	 * @param assignmentId Primary key of the row to update.
	 * @param assignmentModel Non-null source of new field values.
	 */
	Q_INVOKABLE void updateAssignment(int assignmentId, AssignmentViewModel *assignmentModel);

	/**
	 * @brief Placeholder for course-filtered fetch from the backend; currently no-op.
	 */
	Q_INVOKABLE void getFilteredAssignmentsByCourse();

	/** @return Underlying list model exposed to QML as `assignmentModel`. */
	AssignmentListModel* getAssignmentModel() const;
	/** @return Proxy model for search/status filtering over assignments. */
	AssignmentFilterProxyModel *assignmentFilter() const;

signals:
	/** @brief Emitted when create fails (validation, null model, or backend error message). */
	void createAssignmentError(const QString &message);
	/** @brief Emitted when `createAssignment` completes successfully. */
	void createAssignmentSuccess();
	/** @brief Emitted when update fails. */
	void updateAssignmentError(const QString &message);
	/** @brief Emitted when update succeeds. */
	void updateAssignmentSuccess();
	/** @brief Emitted when assignment list fetch fails (currently unused vs. createAssignmentError reuse). */
	void userAssignmentGetError();

private:
	AssignmentController &m_assignmentController;
	AssignmentListModel *m_assignmentModel;
	AssignmentFilterProxyModel *m_assignmentFilter = nullptr;
};

#endif // TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
