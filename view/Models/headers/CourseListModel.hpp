//
// Created by Darnyelx on 2026-04-10.
//

#ifndef TODO_APP_COURSELISTMODEL_HPP
#define TODO_APP_COURSELISTMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <vector>
#include "api/CourseModel.hpp"
#include "view/Models/headers/CourseViewModel.hpp"

class CourseListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CourseListModel(QObject *parent = nullptr);
    ~CourseListModel() override;

    enum CourseRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setCourses(const std::vector<Course> &courses);
    void clear();

    Q_INVOKABLE CourseViewModel* get(int index) const;

private:
    QList<CourseViewModel*> m_courses;
};

#endif // TODO_APP_COURSELISTMODEL_HPP