/**
 * @file CourseListModel.hpp
 * @brief `QAbstractListModel` exposing courses as `CourseViewModel` items for QML views.
 */

#ifndef TODO_APP_COURSELISTMODEL_HPP
#define TODO_APP_COURSELISTMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <vector>
#include "api/CourseModel.hpp"
#include "view/Models/headers/CourseViewModel.hpp"

/**
 * @brief Populated by `CourseViewController::getCourses` from `std::vector<Course>`.
 */
class CourseListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /** @brief Constructs an empty course list. */
    explicit CourseListModel(QObject *parent = nullptr);
    /** @brief Destroys owned `CourseViewModel` instances. */
    ~CourseListModel() override;

    /** @brief Delegate roles for QML bindings. */
    enum CourseRoles {
        IdRole = Qt::UserRole + 1, /**< Course primary key. */
        NameRole /**< Course display name. */
    };

    /**
     * @brief Returns the number of course rows.
     * @param parent Parent index; must be invalid for a flat list.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /** @brief Returns `id` or `name` for the row depending on `role`. */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    /** @brief Maps roles to `"id"` and `"name"` names for QML. */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Rebuilds the model from backend courses.
     * @param courses Vector of catalog rows.
     */
    void setCourses(const std::vector<Course> &courses);

    /** @brief Removes all courses and resets the model. */
    void clear();

    /**
     * @brief Returns the course view model at `index` (owned by this model).
     * @param index Row index.
     */
    Q_INVOKABLE CourseViewModel* get(int index) const;

private:
    QList<CourseViewModel*> m_courses;
};

#endif // TODO_APP_COURSELISTMODEL_HPP
