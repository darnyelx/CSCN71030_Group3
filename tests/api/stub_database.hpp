/**
 * @file stub_database.hpp
 * @brief In-memory `IDatabase` for unit tests; toggles success paths and stores fixture rows.
 */

#pragma once

#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "AssignmentModel.hpp"
#include "CourseModel.hpp"
#include "HelpRequestModel.hpp"
#include "IDatabase.hpp"
#include "UserModel.hpp"

/**
 * @brief Configurable fake database: no PostgreSQL required.
 * @details Public fields let tests arrange data and flip success flags before invoking controllers.
 *          Override methods implement simplified semantics matching production expectations for tests.
 */
class StubDatabase : public IDatabase {
public:
	std::vector<Assignment> assignments; /**< Linear store of assignment rows used by list APIs. */
	std::unordered_map<int, Assignment> assignmentById; /**< Fast lookup by assignment id. */
	bool createAssignmentSucceeds = false; /**< When false, `createAssignment` returns false without mutation. */
	bool deleteAssignmentSucceeds = false; /**< When false, `deleteAssignment` returns false without mutation. */
	int nextAssignmentId = 1; /**< Monotonic id assigned to new assignments when create succeeds. */

	std::vector<Course> courses; /**< Catalog returned by `getAllCourses`. */
	bool throwOnGetAllCourses = false; /**< When true, `getAllCourses` throws `std::runtime_error`. */

	std::vector<HelpRequestModel> helpRequests; /**< All help-request rows in insertion order. */
	std::unordered_map<int, HelpRequestModel> helpRequestByIdMap; /**< Lookup by help-request id. */
	bool createHelpRequestSucceeds = false; /**< When false, `createHelpRequest` returns false. */
	int nextHelpRequestId = 1; /**< Monotonic id for successful help-request inserts. */

	std::vector<UserModel> users; /**< User rows for `getUserByID` / `getAllUsers`. */
	std::optional<UserModel> userByEmailResult; /**< Fixed return for `getUserByEmail` (email param ignored). */
	bool createUserSucceeds = true; /**< When false, `createUser` returns false. */

	/** @copydoc IDatabase::getAllAssignments */
	std::vector<Assignment> getAllAssignments(int userId) override {
		std::vector<Assignment> out;
		for (const auto &a : assignments) {
			if (a.getUserId() == userId) {
				out.push_back(a);
			}
		}
		return out;
	}

	/** @copydoc IDatabase::getUserByID */
	std::optional<UserModel> getUserByID(int id) override {
		for (const auto &u : users) {
			if (u.getId() == id) {
				return u;
			}
		}
		return std::nullopt;
	}

	/** @copydoc IDatabase::getUserByEmail */
	std::optional<UserModel> getUserByEmail(std::string &email) override {
		(void)email;
		return userByEmailResult;
	}

	/** @copydoc IDatabase::getAllUsers */
	std::vector<UserModel> getAllUsers() override { return users; }

	/** @copydoc IDatabase::createUser */
	bool createUser(UserModel &userModel) override { (void)userModel; return createUserSucceeds; }

	/** @copydoc IDatabase::deleteUser */
	bool deleteUser(UserModel &userModel) override { (void)userModel; return false; }

	/** @copydoc IDatabase::createAssignment */
	bool createAssignment(Assignment &assignment) override {
		if (!createAssignmentSucceeds) {
			return false;
		}
		if (assignment.getId() <= 0) {
			assignment.setId(nextAssignmentId++);
			assignments.push_back(assignment);
			assignmentById.erase(assignment.getId());
			assignmentById.emplace(assignment.getId(), assignment);
		} else {
			const int aid = assignment.getId();
			std::vector<Assignment> next;
			for (const auto &a : assignments) {
				if (a.getId() != aid) {
					next.push_back(a);
				}
			}
			next.push_back(assignment);
			assignments = std::move(next);
			assignmentById.erase(aid);
			assignmentById.emplace(aid, assignment);
		}
		return true;
	}

	/** @copydoc IDatabase::deleteAssignment */
	bool deleteAssignment(Assignment &assignment) override {
		if (!deleteAssignmentSucceeds) {
			return false;
		}
		const int id = assignment.getId();
		std::vector<Assignment> next;
		for (const auto &a : assignments) {
			if (a.getId() != id) {
				next.push_back(a);
			}
		}
		assignments = std::move(next);
		assignmentById.erase(id);
		return true;
	}

	/** @copydoc IDatabase::createHelpRequest */
	bool createHelpRequest(HelpRequestModel &helpRequest) override {
		if (!createHelpRequestSucceeds) {
			return false;
		}
		const int hid = nextHelpRequestId++;
		helpRequest.setId(hid);
		helpRequests.push_back(helpRequest);
		helpRequestByIdMap.erase(hid);
		helpRequestByIdMap.emplace(hid, helpRequest);
		return true;
	}

	/** @copydoc IDatabase::getHelpRequestById */
	std::optional<HelpRequestModel> getHelpRequestById(int id) override {
		auto it = helpRequestByIdMap.find(id);
		if (it == helpRequestByIdMap.end()) {
			return std::nullopt;
		}
		return it->second;
	}

	/** @copydoc IDatabase::getAllHelpRequests */
	std::vector<HelpRequestModel> getAllHelpRequests(int userId) override {
		std::vector<HelpRequestModel> out;
		for (const auto &h : helpRequests) {
			if (h.getUserId() == userId) {
				out.push_back(h);
			}
		}
		return out;
	}

	/** @copydoc IDatabase::getHelpRequestsFromOtherUsers */
	std::vector<HelpRequestModel> getHelpRequestsFromOtherUsers(int userId) override {
		std::vector<HelpRequestModel> out;
		for (auto h : helpRequests) {
			if (h.getUserId() == userId) {
				continue;
			}
			std::string label;
			for (const auto &u : users) {
				if (u.getId() == h.getUserId()) {
					const std::string fn = u.getFirstName();
					const std::string ln = u.getLastName();
					label = (fn.empty() && ln.empty()) ? u.getEmail() : (fn + " " + ln);
					break;
				}
			}
			if (label.empty()) {
				label = "User #" + std::to_string(h.getUserId());
			}
			h.setRaiserDisplayName(label);
			out.push_back(std::move(h));
		}
		return out;
	}

	/** @copydoc IDatabase::getAssignmentByID */
	std::optional<Assignment> getAssignmentByID(int id) override {
		auto it = assignmentById.find(id);
		if (it == assignmentById.end()) {
			return std::nullopt;
		}
		return it->second;
	}

	/** @copydoc IDatabase::deleteHelpRequest */
	bool deleteHelpRequest(HelpRequestModel &helpRequest) override { (void)helpRequest; return false; }

	/** @copydoc IDatabase::getAllCourses */
	std::vector<Course> getAllCourses() override {
		if (throwOnGetAllCourses) {
			throw std::runtime_error("database unavailable");
		}
		return courses;
	}
};
