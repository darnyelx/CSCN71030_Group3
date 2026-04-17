/**
 * @file CourseViewController.hpp
 * @brief QML adapter that loads courses into `CourseListModel`.
 */

#ifndef TODO_APP_COURSEVIEWCONTROLLER_HPP
#define TODO_APP_COURSEVIEWCONTROLLER_HPP

#include <QObject>
#include <QString>
#include "view/Models/headers/CourseListModel.hpp"
#include "api/CourseController.hpp"

/**
 * @brief Invokes `CourseController::getAllCourses` and populates the bound list model.
 */
class CourseViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CourseListModel* courseModel READ getCourseModel CONSTANT)

public:
    /**
     * @brief Constructs the bridge with backend and target list model.
     * @param courseController Course API implementation.
     * @param courseModel Model cleared/repopulated by `getCourses`.
     * @param parent Optional Qt parent.
     */
    explicit CourseViewController(CourseController &courseController, CourseListModel *courseModel,
                                  QObject *parent = nullptr);

    /**
     * @brief Fetches all courses from the backend and calls `setCourses` on the list model.
     * @details On failure emits `getCoursesError` with the backend message and clears the model.
     */
    Q_INVOKABLE void getCourses();

    /** @return Course list model bound to QML as `courseModel`. */
    CourseListModel* getCourseModel() const;

signals:
    /** @brief Emitted when `getCourses` cannot load the catalog (includes exception text when mapped). */
    void getCoursesError(const QString &message);

private:
    CourseController &m_courseController;
    CourseListModel *m_courseModel{nullptr};
};

#endif // TODO_APP_COURSEVIEWCONTROLLER_HPP
