#include "view/Controllers/headers/AssignmentViewController.hpp"
#include <iostream>

AssignmentViewController::AssignmentViewController(AssignmentController &assignmentController,
                                                   AssignmentListModel *assignmentModel, QObject *parent)
    : QObject(parent), m_assignmentController(assignmentController), m_assignmentModel(assignmentModel) {}

AssignmentListModel* AssignmentViewController::getAssignmentModel() const
{
    return m_assignmentModel;
}
void AssignmentViewController::createAssignment(AssignmentViewModel *assignmentModel) {
    if (!assignmentModel) {
        emit createAssignmentError("Invalid assignment");
        return;
    }
    std::cout << "user ID" << assignmentModel->userId() << std::endl;
    auto r = m_assignmentController.createAssignment(assignmentModel->title().toStdString(),
                                                     assignmentModel->description().toStdString(),
                                                     assignmentModel->courseId(), assignmentModel->userId(),
                                                     assignmentModel->dueDate().toStdString());
    if (r.success) {
        emit createAssignmentSuccess();
    } else {
        emit createAssignmentError(QString::fromStdString(r.errorMessage));
    }
}

void AssignmentViewController::updateAssignment(int assignmentId, AssignmentViewModel *assignmentModel) {
    if (!assignmentModel) {
        emit updateAssignmentError("Invalid assignment");
        return;
    }
    auto r = m_assignmentController.updateAssignment(assignmentId, assignmentModel->title().toStdString(),
                                                     assignmentModel->description().toStdString(),
                                                     assignmentModel->courseId(),
                                                     assignmentModel->dueDate().toStdString(),
                                                     assignmentModel->priority());
    if (r.success) {
        emit updateAssignmentSuccess();
    } else {
        emit updateAssignmentError(QString::fromStdString(r.errorMessage));
    }
}
void AssignmentViewController::getUserAssignments(int userId)
{
    std::cout << "Getting user's assignments: "<< userId << std::endl;
     GetAllAssignmentResultPayload assignmentsPayload = m_assignmentController.getAllAssignments(userId);

    if (!m_assignmentModel) {
        emit createAssignmentError("Assignment model is not initialized");
        return;
    }
    if (assignmentsPayload.success) {
        std::cout<<"Assignment gotten: " << assignmentsPayload.assignments.size() << std::endl;

        m_assignmentModel->setAssignments(assignmentsPayload.assignments);
    } else {
        m_assignmentModel->clear();
        emit createAssignmentError(QString::fromStdString(assignmentsPayload.errorMessage));
    }
}

void AssignmentViewController::getFilteredAssignmentsByCourse()
{
}