//
// Created by Darnyelx on 2026-04-10.
//

#include "view/Controllers/headers/CourseViewController.hpp"

CourseViewController::CourseViewController(CourseListModel *courseModel, QObject *parent)
    : QObject(parent),
      m_courseModel(courseModel)
{
}

CourseListModel* CourseViewController::getCourseModel() const
{
    return m_courseModel;
}

void CourseViewController::getCourses()
{
    if (!m_courseModel) {
        emit getCoursesError("Course model is not initialized");
        return;
    }

    CourseController courseController;
    auto coursesPayload = courseController.getAllCourses();

    if (coursesPayload.success) {
        m_courseModel->setCourses(coursesPayload.courses);
    } else {
        m_courseModel->clear();
        emit getCoursesError(QString::fromStdString(coursesPayload.message));
    }
}