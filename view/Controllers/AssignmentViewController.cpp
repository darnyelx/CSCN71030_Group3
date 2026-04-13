#include "view/Controllers/headers/AssignmentViewController.hpp"
#include "api/AssignmentController.hpp"
#include  <iostream>


AssignmentViewController::AssignmentViewController(AssignmentListModel *assignmentModel, QObject *parent)
    : QObject(parent),
      m_assignmentModel(assignmentModel)
{
}

AssignmentListModel* AssignmentViewController::getAssignmentModel() const
{
    return m_assignmentModel;
}
void AssignmentViewController::createAssignment(AssignmentViewModel *assignmentModel) {
    AssignmentController controller;
    std::cout << "user ID" << assignmentModel->userId() << std::endl;
    controller.createAssignment(assignmentModel->title().toStdString(), assignmentModel->description().toStdString(), assignmentModel->courseId(),assignmentModel->userId(), assignmentModel->dueDate().toStdString());

}
void AssignmentViewController::getUserAssignments(int userId)
{
    std::cout << "Getting user's assignments: "<< userId << std::endl;
    AssignmentController controller;
     GetAllAssignmentResultPayload assignmentsPayload = controller.getAllAssignments(userId);

    if (!m_assignmentModel) {
        emit createAssignmentError("Assignment model is not initialized");
        return;
    }
    std::cout<<"Assignment gotten: " << assignmentsPayload.assignments.size() << std::endl;
    if (assignmentsPayload.success) {

        m_assignmentModel->setAssignments(assignmentsPayload.assignments);
    } else {
        m_assignmentModel->clear();
        emit createAssignmentError(QString::fromStdString(assignmentsPayload.errorMessage));
    }
}

void AssignmentViewController::getFilteredAssignmentsByCourse()
{
}