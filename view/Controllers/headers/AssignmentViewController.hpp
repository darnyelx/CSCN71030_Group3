
#ifndef TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
#define TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP
#include "api/AssignmentController.hpp"
#include "view/Models/headers/AssignmentModel.hpp"
#include <QObject>
#include <QString>

class AssignmentViewController  : public QObject {
	Q_OBJECT

	public:
		explicit AssignmentViewController(QObject *parent = nullptr);
		void getAllAssignments(int userId);
		void getFilteredAssignmentsByCourse();

	signals:
		// void assignmentsGotten(std::vector<AssignmentViewModel> assignments);
};


#endif //TODO_APP_ASSIGNMENTVIEWCONTROLLER_HPP