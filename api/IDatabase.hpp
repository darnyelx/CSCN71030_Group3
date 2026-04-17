/**
 * @file IDatabase.hpp
 * @brief Abstract persistence layer for users, assignments, help requests, and courses.
 */

#pragma once

#include <optional>
#include <string>
#include <vector>

class Assignment;
class UserModel;
class HelpRequestModel;
class Course;

/**
 * @brief Port for PostgreSQL-backed operations used by controllers and `BaseModel` implementations.
 * @details Implementations (for example `DB`) execute SQL and map rows to the domain types declared
 *          in this interface. Controllers depend on this abstraction for testability.
 */
class IDatabase {
public:
    /** @brief Virtual destructor allows polymorphic deletion through `IDatabase*`. */
    virtual ~IDatabase() = default;

    /**
     * @brief Loads every assignment row owned by the given user (typically filtered by `user_id`).
     * @param userId Primary key of the user whose assignments are requested.
     * @return Collection of `Assignment` objects; may be empty if the user has none.
     */
    virtual std::vector<Assignment> getAllAssignments(int userId) = 0;

    /**
     * @brief Looks up a user by primary key.
     * @param id `users.id` value.
     * @return Populated `UserModel` if found, otherwise `std::nullopt`.
     */
    virtual std::optional<UserModel> getUserByID(int id) = 0;

    /**
     * @brief Looks up a user by email address (case rules depend on implementation).
     * @param email In/out email string; some implementations may normalize or ignore contents after lookup.
     * @return Populated `UserModel` if a row matches, otherwise `std::nullopt`.
     */
    virtual std::optional<UserModel> getUserByEmail(std::string &email) = 0;

    /**
     * @brief Returns all user rows (admin or diagnostic use; scope depends on deployment).
     * @return Vector of every user the backing store exposes to this call.
     */
    virtual std::vector<UserModel> getAllUsers() = 0;

    /**
     * @brief Inserts or upserts a user row according to implementation (registration path).
     * @param userModel User fields including hashed password where applicable; may receive generated `id`.
     * @return true if persistence succeeded, false on constraint or I/O failure.
     */
    virtual bool createUser(UserModel &userModel) = 0;

    /**
     * @brief Deletes the user row identified by `userModel` (typically by primary key).
     * @param userModel User whose `id` (or unique key) selects the row to remove.
     * @return true if a row was deleted or the operation completed successfully.
     */
    virtual bool deleteUser(UserModel &userModel) = 0;

    /**
     * @brief Persists a new or updated assignment (implementations often use upsert semantics).
     * @param assignment Domain object with course, user, dates, status, etc.
     * @return true if the database accepted the write.
     */
    virtual bool createAssignment(Assignment &assignment) = 0;

    /**
     * @brief Removes the assignment identified by `assignment` (usually by `id`).
     * @param assignment Object carrying at least the primary key of the row to delete.
     * @return true if the delete succeeded.
     */
    virtual bool deleteAssignment(Assignment &assignment) = 0;

    /**
     * @brief Inserts a help request for an assignment from a given user.
     * @param helpRequest Populated model; implementation may assign `id` and timestamps.
     * @return true if the insert succeeded.
     */
    virtual bool createHelpRequest(HelpRequestModel &helpRequest) = 0;

    /**
     * @brief Fetches a single help request by primary key.
     * @param id `help_requests.id`.
     * @return Model if found, otherwise `std::nullopt`.
     */
    virtual std::optional<HelpRequestModel> getHelpRequestById(int id) = 0;

    /**
     * @brief Lists help requests raised by the specified user.
     * @param userId Raiser’s user id (`help_requests.user_id`).
     * @return All matching rows, possibly empty.
     */
    virtual std::vector<HelpRequestModel> getAllHelpRequests(int userId) = 0;

    /**
     * @brief Lists help requests from every user except `userId`, with display metadata where supported.
     * @param userId Current user; their own requests are excluded from the result.
     * @return Other users’ requests (implementation may attach `raiser_display_name`, etc.).
     */
    virtual std::vector<HelpRequestModel> getHelpRequestsFromOtherUsers(int userId) = 0;

    /**
     * @brief Loads one assignment by primary key (any user, subject to implementation rules).
     * @param id `assignments.id`.
     * @return Assignment if found, otherwise `std::nullopt`.
     */
    virtual std::optional<Assignment> getAssignmentByID(int id) = 0;

    /**
     * @brief Deletes a help request row.
     * @param helpRequest Object identifying the row (typically by `id`).
     * @return true if deletion succeeded.
     */
    virtual bool deleteHelpRequest(HelpRequestModel &helpRequest) = 0;

    /**
     * @brief Returns the course catalog visible to the application (often all courses).
     * @return List of `Course` rows.
     */
    virtual std::vector<Course> getAllCourses() = 0;
};
