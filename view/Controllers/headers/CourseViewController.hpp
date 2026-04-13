//
// Created by Darnyelx on 2026-04-10.
//

#ifndef TODO_APP_COURSEVIEWCONTROLLER_HPP
#define TODO_APP_COURSEVIEWCONTROLLER_HPP

#include <QObject>
#include <QString>
#include "view/Models/headers/CourseListModel.hpp"
#include "api/CourseController.hpp"

class CourseViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CourseListModel* courseModel READ getCourseModel CONSTANT)

public:
    explicit CourseViewController(CourseListModel *courseModel, QObject *parent = nullptr);

    Q_INVOKABLE void getCourses();
    CourseListModel* getCourseModel() const;

signals:
    void getCoursesError(const QString &message);

private:
    CourseListModel *m_courseModel{nullptr};
};

#endif // TODO_APP_COURSEVIEWCONTROLLER_HPP