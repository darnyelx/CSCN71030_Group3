#ifndef TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
#define TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP

#include "api/AssignmentController.hpp"
#include "view/Models/headers/AssignmentFilterProxyModel.hpp"
#include "view/Models/headers/AssignmentListModel.hpp"
#include <QObject>
#include <QString>

class AssignmentViewController : public QObject {
	Q_OBJECT
	Q_PROPERTY(AssignmentListModel* assignmentModel READ getAssignmentModel CONSTANT)
	Q_PROPERTY(AssignmentFilterProxyModel* assignmentFilter READ assignmentFilter CONSTANT)

public:
	explicit AssignmentViewController(AssignmentController &assignmentController,
	                                  AssignmentListModel *assignmentModel, QObject *parent = nullptr);

	Q_INVOKABLE void getUserAssignments(int userId);
	Q_INVOKABLE void createAssignment(AssignmentViewModel *assignmentModel);
	Q_INVOKABLE void updateAssignment(int assignmentId, AssignmentViewModel *assignmentModel);
	Q_INVOKABLE void getFilteredAssignmentsByCourse();

	AssignmentListModel* getAssignmentModel() const;
	AssignmentFilterProxyModel *assignmentFilter() const;

signals:
	void createAssignmentError(const QString &message);
	void createAssignmentSuccess();
	void updateAssignmentError(const QString &message);
	void updateAssignmentSuccess();
	void userAssignmentGetError();

private:
	AssignmentController &m_assignmentController;
	AssignmentListModel *m_assignmentModel;
	AssignmentFilterProxyModel *m_assignmentFilter = nullptr;
};

#endif // TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
