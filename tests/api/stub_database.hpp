#pragma once

#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "AssignmentModel.hpp"
#include "CourseModel.hpp"
#include "HelpRequestModel.hpp"
#include "IDatabase.hpp"
#include "UserModel.hpp"

class StubDatabase : public IDatabase {
public:
	std::vector<Assignment> assignments;
	std::unordered_map<int, Assignment> assignmentById;
	bool createAssignmentSucceeds = false;
	bool deleteAssignmentSucceeds = false;
	int nextAssignmentId = 1;

	std::vector<Course> courses;
	bool throwOnGetAllCourses = false;

	std::vector<HelpRequestModel> helpRequests;
	std::unordered_map<int, HelpRequestModel> helpRequestByIdMap;
	bool createHelpRequestSucceeds = false;
	int nextHelpRequestId = 1;

	std::vector<UserModel> users;
	std::optional<UserModel> userByEmailResult;
	bool createUserSucceeds = true;

	std::vector<Assignment> getAllAssignments(int userId) override {
		std::vector<Assignment> out;
		for (const auto &a : assignments) {
			if (a.getUserId() == userId) {
				out.push_back(a);
			}
		}
		return out;
	}

	std::optional<UserModel> getUserByID(int id) override {
		for (const auto &u : users) {
			if (u.getId() == id) {
				return u;
			}
		}
		return std::nullopt;
	}

	std::optional<UserModel> getUserByEmail(std::string &email) override {
		(void)email;
		return userByEmailResult;
	}

	std::vector<UserModel> getAllUsers() override { return users; }

	bool createUser(UserModel &) override { return createUserSucceeds; }

	bool deleteUser(UserModel &) override { return false; }

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

	bool createHelpRequest(HelpRequestModel &hr) override {
		if (!createHelpRequestSucceeds) {
			return false;
		}
		const int hid = nextHelpRequestId++;
		hr.setId(hid);
		helpRequests.push_back(hr);
		helpRequestByIdMap.erase(hid);
		helpRequestByIdMap.emplace(hid, hr);
		return true;
	}

	std::optional<HelpRequestModel> getHelpRequestById(int id) override {
		auto it = helpRequestByIdMap.find(id);
		if (it == helpRequestByIdMap.end()) {
			return std::nullopt;
		}
		return it->second;
	}

	std::vector<HelpRequestModel> getAllHelpRequests(int userId) override {
		std::vector<HelpRequestModel> out;
		for (const auto &h : helpRequests) {
			if (h.getUserId() == userId) {
				out.push_back(h);
			}
		}
		return out;
	}

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

	std::optional<Assignment> getAssignmentByID(int id) override {
		auto it = assignmentById.find(id);
		if (it == assignmentById.end()) {
			return std::nullopt;
		}
		return it->second;
	}

	bool deleteHelpRequest(HelpRequestModel &) override { return false; }

	std::vector<Course> getAllCourses() override {
		if (throwOnGetAllCourses) {
			throw std::runtime_error("database unavailable");
		}
		return courses;
	}
};
