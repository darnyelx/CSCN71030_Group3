//
// Created by Darnyelx on 2026-04-10.
//

#ifndef TODO_APP_COURSEVIEWMODEL_HPP
#define TODO_APP_COURSEVIEWMODEL_HPP

#include <QObject>
#include <QString>
#include "api/CourseModel.hpp"

class CourseViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit CourseViewModel(QObject *parent = nullptr);
    explicit CourseViewModel(const Course &course, QObject *parent = nullptr);

    int id() const;
    QString name() const;

    void setId(int value);
    void setName(const QString &value);

    void fromModel(const Course &course);

signals:
    void idChanged();
    void nameChanged();

private:
    int m_id{-1};
    QString m_name;
};

#endif // TODO_APP_COURSEVIEWMODEL_HPP