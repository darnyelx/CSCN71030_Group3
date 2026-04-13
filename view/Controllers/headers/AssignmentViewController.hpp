#ifndef TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
#define TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP

#include "api/AssignmentController.hpp"
#include "view/Models/headers/AssignmentListModel.hpp"
#include <QObject>
#include <QString>

class AssignmentViewController : public QObject {
	Q_OBJECT
	Q_PROPERTY(AssignmentListModel* assignmentModel READ getAssignmentModel CONSTANT)

    public:
	explicit AssignmentViewController(AssignmentListModel *assignmentModel, QObject *parent = nullptr);

	Q_INVOKABLE void getUserAssignments(int userId);
	Q_INVOKABLE void createAssignment(AssignmentViewModel *assignmentModel);
	Q_INVOKABLE void getFilteredAssignmentsByCourse();

	AssignmentListModel* getAssignmentModel() const;

	signals:
	    void createAssignmentError(const QString &message);
		void createAssignmentSuccess();
		void userAssignmentGetError();

private:
	AssignmentListModel *m_assignmentModel;
};

#endif // TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP