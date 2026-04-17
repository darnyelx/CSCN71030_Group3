/**
 * @file AssignmentModel.hpp
 * @brief Domain model for the `assignments` table and related UI fields (course name from joins).
 */

#pragma once
#include "BaseModel.hpp"
#include <string>	

/**
 * @brief Assignment owned by a user, linked to a course, with scheduling and workflow status.
 * @details `save` maps to `createAssignment` on the database (upsert/update path in `DB`).
 *          `course_name` is optional UI data from joins, not stored on the assignment row itself.
 */
class Assignment : public BaseModel {
protected: 
	const std::string tableName = "assignments";
private:
	int id;
	std::string title;
	std::string description;
	std::string created_at;
	std::string updated_at;
	std::string due_date;
	int course_id{};
	int user_id{};
	int priority{};
	/** DB column `status`: Pending | In Progress | Completed */
	std::string status;
	/** Filled when loaded via JOIN with courses; not a DB column on assignments. */
	std::string course_name;

public:
	/**
	 * @brief Constructs an assignment with optional id/title/description; other fields default.
	 * @param id Row id or negative sentinel for “not yet persisted”.
	 * @param title Short title shown in lists.
	 * @param description Longer body text.
	 */
	Assignment(int id = -1, const std::string& title = "", const std::string& description = "");
	/** @return Primary key or sentinel id. */
	int getId() const;
	/** @return Assignment title. */
	std::string getTitle() const;
	/** @return Assignment description body. */
	std::string getDescription() const;
	/** @return Foreign key `course_id`. */
	int getCourseId() const;
	/** @return Display name from join when populated. */
	std::string getCourseName() const;
	/** @return Owning user id. */
	int getUserId() const;
	/** @return Numeric priority (higher may mean more urgent depending on UI). */
	int getPriority() const;
	/** @return Workflow status string (Pending / In Progress / Completed). */
	std::string getStatus() const;
	/** @return Due date/time string as stored or formatted for display. */
	std::string getDueDate() const;
	/** @return Creation timestamp string from the database. */
	std::string getCreatedAt() const;
	/** @return Last update timestamp string from the database. */
	std::string getUpdatedAt() const;
	/** @return Logical table name `"assignments"`. */
	std::string getTableName() override;
	/** @brief Sets primary key; @return `*this` for chaining. */
	Assignment& setId(int id);
	/** @brief Sets title; @return `*this` for chaining. */
	Assignment& setTitle(const std::string& title);
	/** @brief Sets description; @return `*this` for chaining. */
	Assignment& setDescription(const std::string& description);
	/** @brief Sets created-at string; @return `*this` for chaining. */
	Assignment& setCreatedAt(const std::string& created_at);
	/** @brief Sets updated-at string; @return `*this` for chaining. */
	Assignment& setUpdatedAt(const std::string& updated_at);
	/** @brief Sets due date string; @return `*this` for chaining. */
	Assignment& setDueDate(const std::string& due_date);
	/** @brief Sets course foreign key; @return `*this` for chaining. */
	Assignment& setCourseId(int course_id);
	/** @brief Sets denormalized course display name (UI); @return `*this` for chaining. */
	Assignment& setCourseName(const std::string &name);
	/** @brief Sets priority; @return `*this` for chaining. */
	Assignment& setPriority(int priority);
	/** @brief Sets status string; @return `*this` for chaining. */
	Assignment& setStatus(const std::string &status);
	/** @brief Sets owning user id; @return `*this` for chaining. */
	Assignment& setUserId(int user_id);
	/** @brief Persists via `IDatabase::createAssignment`. */
	bool save(IDatabase &db) override;
	/** @brief Reserved hook; current implementation is a no-op. */
	void load();
	/** @brief Deletes via `IDatabase::deleteAssignment`. */
	bool remove(IDatabase &db) override;


};
