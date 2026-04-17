/**
 * @file CourseViewModel.hpp
 * @brief QML-friendly subset of `Course` (id and name) for pickers and delegates.
 */

#ifndef TODO_APP_COURSEVIEWMODEL_HPP
#define TODO_APP_COURSEVIEWMODEL_HPP

#include <QObject>
#include <QString>
#include "api/CourseModel.hpp"

/**
 * @brief Minimal course row for QML; description is omitted from properties here.
 */
class CourseViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    /** @brief Constructs with default id -1 and empty name. */
    explicit CourseViewModel(QObject *parent = nullptr);
    /**
     * @brief Initializes id and name from a `Course`.
     * @param course Backend row.
     * @param parent Optional Qt parent.
     */
    explicit CourseViewModel(const Course &course, QObject *parent = nullptr);

    /** @return Course id property. */
    int id() const;
    /** @return Course name as `QString`. */
    QString name() const;

    /** @brief Sets id; emits `idChanged` when value changes. */
    void setId(int value);
    /** @brief Sets name; emits `nameChanged` when value changes. */
    void setName(const QString &value);

    /**
     * @brief Copies id and display name from `course`.
     * @param course Backend course row.
     */
    void fromModel(const Course &course);

signals:
    /** @brief Emitted when the course `id` property changes. */
    void idChanged();
    /** @brief Emitted when the course `name` property changes. */
    void nameChanged();

private:
    int m_id{-1};
    QString m_name;
};

#endif // TODO_APP_COURSEVIEWMODEL_HPP
