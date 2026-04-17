/**
 * @file CourseViewController.cpp
 * @brief Fetches courses and writes them into `CourseListModel`.
 */

#include "view/Controllers/headers/CourseViewController.hpp"

CourseViewController::CourseViewController(CourseController &courseController, CourseListModel *courseModel,
                                         QObject *parent)
    : QObject(parent), m_courseController(courseController), m_courseModel(courseModel) {}

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

    auto coursesPayload = m_courseController.getAllCourses();

    if (coursesPayload.success) {
        m_courseModel->setCourses(coursesPayload.courses);
    } else {
        m_courseModel->clear();
        emit getCoursesError(QString::fromStdString(coursesPayload.message));
    }
}