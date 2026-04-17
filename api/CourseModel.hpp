/**
 * @file CourseModel.hpp
 * @brief Domain model for the `courses` table.
 */

#pragma once
#include "BaseModel.hpp"
#include <string>

/**
 * @brief Course record associated with a user (`user_id` foreign key).
 * @details In this application `save`/`remove` return false from `Course` (catalog is maintained
 *          elsewhere); the type is mainly used for read results from `getAllCourses`.
 */
class Course : public BaseModel {
	protected:
		const std::string tableName = "courses";	
private:
	int id;
	std::string name;
	std::string description;
	int user_id; ///< Foreign key: course owner

public:
	/**
	 * @brief Constructs a course with id, display name, and description text.
	 * @param id Primary key or sentinel.
	 * @param name Short course title.
	 * @param description Longer catalog description.
	 */
	Course(int id, const std::string& name, const std::string& description);
    /** @brief Default construct; leaves fields in a defined but empty/default numeric state. */
    Course();
    /** @return Course primary key. */
    int getId() const;
	/** @return Owning user id. */
	int getUserId() const;
	/** @return Course name. */
	std::string getName() const;
	/** @return Course description body. */
	std::string getDescription() const;
	/** @brief Sets id; @return `*this` for chaining. */
	Course& setId(int id);
	/** @brief Sets name; @return `*this` for chaining. */
	Course& setName(const std::string& name);
	/** @brief Sets description; @return `*this` for chaining. */
	Course& setDescription(const std::string& description);
	/** @brief Sets owner user id; @return `*this` for chaining. */
	Course& setUserId(int user_id);
	/** @brief No-op write in current build. @return always false. */
	bool save(IDatabase &db) override;
	/** @brief Reserved hook; current implementation is a no-op. */
	void load();
	/** @brief No-op delete in current build. @return always false. */
	bool remove(IDatabase &db) override;
	/** @return Logical table name `"courses"`. */
	std::string getTableName() override;


};
