/**
 * @file AssignmentController.hpp
 * @brief CRUD-style operations on assignments for the signed-in user scope.
 */

#pragma once

#include "AssignmentModel.hpp"
#include <optional>
#include <vector>

class IDatabase;

/**
 * @brief Single-assignment operation result (create, read, update, delete).
 */
struct AssignmentResultPayload {
	bool success; /**< true when the requested operation completed without error. */
	std::string errorMessage; /**< Empty on success; otherwise user-facing failure reason. */
	std::optional<Assignment> assignment; /**< Populated row on read/create/update success where applicable. */
};

/**
 * @brief Result of listing all assignments for a user.
 */
struct GetAllAssignmentResultPayload {
	bool success; /**< Currently always true when the call returns (list may be empty). */
	std::vector<Assignment> assignments; /**< All assignments returned by `getAllAssignments` for the user. */
	std::string errorMessage; /**< Reserved for future error propagation; often empty. */
};

/**
 * @brief Validates inputs and maps persistence errors to `AssignmentResultPayload`.
 * @details `updateAssignment` reuses `createAssignment` on the database layer (upsert semantics in `DB`).
 */
class AssignmentController {
public:
	/**
	 * @brief Constructs controller with database dependency.
	 * @param database Must outlive this controller.
	 */
	explicit AssignmentController(IDatabase &database);

	/**
	 * @brief Builds a new `Assignment`, defaulting empty status to `"Pending"`, priority to 1, and inserts.
	 * @param title Assignment title.
	 * @param description Body text.
	 * @param courseId Foreign key to course.
	 * @param userId Owning user id.
	 * @param dueDate Due date string passed to persistence.
	 * @param status Workflow status; empty becomes `"Pending"`.
	 * @return Payload with `success` reflecting insert result; `assignment` holds the in-memory row attempted.
	 */
	AssignmentResultPayload createAssignment(const std::string title, const std::string description, int courseId,
	                                         int userId, std::string dueDate, const std::string &status);

	/**
	 * @brief Loads one assignment by id.
	 * @param id Primary key.
	 * @return Success with `assignment` set, or failure with `"Assignment not found"`.
	 */
	AssignmentResultPayload getAssignment(int id);

	/**
	 * @brief Lists every assignment for the given user id.
	 * @param userId Owner user primary key.
	 * @return Vector of assignments (may be empty).
	 */
	GetAllAssignmentResultPayload getAllAssignments(int userId);

	/**
	 * @brief Updates fields on an existing assignment then persists via upsert path.
	 * @param id Assignment primary key.
	 * @param title New title.
	 * @param description New description.
	 * @param courseId New course id.
	 * @param dueDate New due date string.
	 * @param priority New priority value.
	 * @param status New status; empty preserves existing or defaults to Pending when missing.
	 * @return Failure if row not found or persist fails; success includes updated snapshot when ok.
	 */
	AssignmentResultPayload updateAssignment(int id, const std::string &title, const std::string &description,
	                                         int courseId, const std::string &dueDate, int priority,
	                                         const std::string &status);

	/**
	 * @brief Deletes an assignment by primary key.
	 * @param id Row to delete.
	 * @return Success/failure with appropriate `errorMessage`.
	 */
	AssignmentResultPayload deleteAssignment(int id);

private:
	IDatabase &db_;
};
