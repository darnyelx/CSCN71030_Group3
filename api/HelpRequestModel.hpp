/**
 * @file HelpRequestModel.hpp
 * @brief Domain model for help requests tied to an assignment and a raising user.
 */

#pragma once

#include <string>
#include "BaseModel.hpp"

/**
 * @brief Row in `help_requests` plus optional UI-only raiser display name.
 * @details `save` inserts via `IDatabase::createHelpRequest`. `remove` calls `deleteHelpRequest`.
 *          `raiser_display_name` is filled when listing other users’ requests, not written to the DB.
 */
class HelpRequestModel : public BaseModel {
protected:
    const std::string tableName = "help_requests";

private:
    int id;
    int userId;
    int assignment_id;
    std::string message;
    std::string request_status;
    std::string createdAt;
    /** Populated when listing other users' requests (not persisted). */
    std::string raiser_display_name;

public:
    /**
     * @brief Constructs a help request with optional id, raiser, message, and timestamp strings.
     * @param id Row id or negative before insert.
     * @param userId User who raised the request.
     * @param message Body text shown to coordinators.
     * @param createdAt Timestamp string; may be overwritten by controllers on create.
     */
    HelpRequestModel(int id = -1, int userId = -1, const std::string &message = "", const std::string &createdAt = "");
    /** @return Primary key. */
    int getId() const;
    /** @return Raiser’s user id. */
    int getUserId() const;
    /** @return Target assignment id. */
    int getAssignmentId() const;
    /** @return Request message body. */
    const std::string &getMessage() const;
    /** @return Workflow/status string for the request. */
    const std::string &getRequestStatus() const;
    /** @return Creation timestamp string. */
    const std::string &getCreatedAt() const;
    /** @brief Sets primary key. */
    void setId(int id);
    /** @brief Sets raiser user id. */
    void setUserId(int userId);
    /** @brief Sets creation timestamp string. */
    void setCreatedAt(const std::string &createdAt);
    /** @brief Sets related assignment id. */
    void setAssignmentId(int assignment_id);
    /** @brief Sets message body. */
    void setMessage(const std::string &message);
    /** @brief Sets request status string. */
    void setRequestStatus(const std::string &request_status);
    /** @return Display label for the raiser (list “others” view). */
    const std::string &getRaiserDisplayName() const;
    /** @brief Sets denormalized display name for UI lists. */
    void setRaiserDisplayName(const std::string &name);
    /** @brief Inserts via `IDatabase::createHelpRequest`. */
    bool save(IDatabase &db) override;
    /** @brief Deletes via `IDatabase::deleteHelpRequest`. */
    bool remove(IDatabase &db) override;

    /** @return Logical table name `"help_requests"`. */
    std::string getTableName() override;
};
