/**
 * @file HelpRequestController.hpp
 * @brief Create and list help requests for the current user and for peer visibility.
 */

#pragma once

#include <optional>
#include <string>
#include <vector>
#include "HelpRequestModel.hpp"

class IDatabase;

/**
 * @brief Single help-request operation result.
 */
struct HelpRequestResultPayload {
	bool success; /**< true when create or get succeeded. */
	std::string errorMessage; /**< Empty on success. */
	std::optional<HelpRequestModel> helpRequest; /**< Row data on success. */
};

/**
 * @brief List result for help requests with optional error message.
 */
struct GetAllHelpRequestResultPayload {
	bool success; /**< Currently true when returning from list methods. */
	std::vector<HelpRequestModel> helpRequests; /**< Result rows. */
	std::string errorMessage; /**< Reserved / empty in current implementation. */
};

/**
 * @brief Coordinates help-request persistence and cross-user listing rules.
 * @details `createHelpRequest` stamps UTC `createdAt` before insert.
 */
class HelpRequestController {
public:
	/**
	 * @brief Constructs controller with database dependency.
	 * @param database Must outlive this controller.
	 */
	explicit HelpRequestController(IDatabase &database);

	/**
	 * @brief Creates a help request for an assignment from a user, with server-side timestamp.
	 * @param userId Raiser’s user id.
	 * @param assignmentId Target assignment.
	 * @param message User-visible request text.
	 * @return Payload with inserted model on success, or error message on failure.
	 */
	HelpRequestResultPayload createHelpRequest(int userId, int assignmentId, const std::string &message);

	/**
	 * @brief Fetches one help request by id.
	 * @param id Primary key.
	 * @return Not-found error or success with model.
	 */
	HelpRequestResultPayload getHelpRequestById(int id);

	/**
	 * @brief Lists all help requests raised by `userId`.
	 * @param userId Raiser filter.
	 * @return Vector (possibly empty).
	 */
	GetAllHelpRequestResultPayload getAllHelpRequests(int userId);

	/**
	 * @brief Lists help requests from other users (excludes `userId`), with display names when DB provides them.
	 * @param userId Current user to exclude from results.
	 * @return Vector of other users’ requests.
	 */
	GetAllHelpRequestResultPayload getHelpRequestsFromOtherUsers(int userId);

private:
	IDatabase &db_;
};
