# Test Plan — todo_app (CSCN71030 Group3)

**Document version:** 1.0  
**Product:** Assignment coordinator (Qt 6 Quick + PostgreSQL API)  
**Scope:** Automated tests under `tests/api/` and optional DB integration tests.

---

## 1. Introduction

This plan describes how automated testing is organized for the project: objectives, what is in and out of scope, environments, how tests are executed, and pass/fail criteria. Implementation uses **GoogleTest** via CMake `CTest`.

---

## 2. Objectives

| ID | Objective |
|----|-----------|
| O1 | Verify API controllers behave correctly for success and failure paths when backed by a controlled in-memory database (`StubDatabase`). |
| O2 | Verify domain models expose expected table names and field behavior used by persistence and UI layers. |
| O3 | When enabled, verify **register** and **login** flows against a **live PostgreSQL** instance using the real `DB` implementation. |
| O4 | Provide repeatable execution via `ctest` for CI and local development. |

---

## 3. Scope

### 3.1 In scope

- **Unit / API tests** (`api_tests` executable): `AuthController`, `AssignmentController`, `CourseController`, `AssignmentQueryController`, `HelpRequestController`, and domain models (`UserModel`, `Assignment`, `Course`, `HelpRequestModel`) using `StubDatabase`.
- **Integration tests** (`api_integration_tests` executable, optional build): `AuthController` + `DB` — register, login, wrong password; cleanup via `deleteUser`.
- **Build configuration:** `TODO_APP_BUILD_TESTS`, `TODO_APP_DB_INTEGRATION_TESTS`, `TODO_APP_DB_CONNECTION_STRING` (see `CMakeLists.txt`).

### 3.2 Out of scope (current automated suite)

- Qt Quick / QML UI tests (no Squish, no `Qt Test` QML harness in repo).
- End-to-end browser tests.
- Load and stress testing.
- Formal security audit (beyond login rejection of wrong password in integration).

---

## 4. Test levels

| Level | Target | Dependency | Location |
|-------|--------|--------------|----------|
| **API unit** | Controllers + models | `StubDatabase`, libsodium (auth hashing) | `tests/api/*.cpp` → `api_tests` |
| **API integration** | Auth vs PostgreSQL | `DB`, libpqxx, `DBConnectionString` from env / CTest injection from `config.env` | `tests/api/integration/auth_db_integration_test.cpp` → `api_integration_tests` |

---

## 5. Test items (inventory)

### 5.1 Domain models (`models_test.cpp`)

| Test case | Description |
|------------|-------------|
| `UserModel.TableNameAndFluentSetters` | Table name and chained setters. |
| `Assignment.TableNameAndFields` | Assignment table name and core fields. |
| `Course.TableNameAndFields` | Course table name and fields. |
| `HelpRequestModel.TableNameAndSetters` | Help request table name and setters. |

### 5.2 Auth controller (`auth_controller_test.cpp`)

| Test case | Description |
|------------|-------------|
| `AuthController.RegisterUserRejectsEmptyFirstName` | Registration validation. |
| `AuthController.RegisterUserRejectsEmptyLastName` | Registration validation. |
| `AuthController.RegisterUserRejectsEmptyEmail` | Registration validation. |
| `AuthController.RegisterUserRejectsEmptyPassword` | Registration validation. |

### 5.3 Assignment controller (`assignment_controller_test.cpp`)

| Test case | Description |
|------------|-------------|
| `AssignmentController.CreateAssignmentFailsWhenDatabaseRejects` | Error path when DB returns false. |
| `AssignmentController.CreateAssignmentSucceeds` | Happy path create. |
| `AssignmentController.GetAssignmentNotFound` | Missing id. |
| `AssignmentController.GetAssignmentFound` | Load by id. |
| `AssignmentController.UpdateAssignmentNotFound` | Update missing row. |
| `AssignmentController.UpdateAssignmentSucceeds` | Update happy path. |
| `AssignmentController.GetAllAssignmentsReturnsUserRows` | List filtering by user. |
| `AssignmentController.DeleteAssignment` | Delete path. |

### 5.4 Course controller (`course_controller_test.cpp`)

| Test case | Description |
|------------|-------------|
| `CourseController.GetAllCoursesSuccess` | Catalog success. |
| `CourseController.GetAllCoursesHandlesException` | Exception mapped to failure result. |

### 5.5 Assignment query controller (`assignment_query_controller_test.cpp`)

| Test case | Description |
|------------|-------------|
| `AssignmentQueryController.SearchByKeywordMatchesTitleOrDescription` | Keyword search. |
| `AssignmentQueryController.FilterByCourse` | Filter by `course_id`. |
| `AssignmentQueryController.FilterByPriority` | Filter by priority. |
| `AssignmentQueryController.OrderByDueDate` | Sort by due date. |
| `AssignmentQueryController.OrderByPriorityDescending` | Sort by priority descending. |

### 5.6 Help request controller (`help_request_controller_test.cpp`)

| Test case | Description |
|------------|-------------|
| `HelpRequestController.CreateFailsWhenDatabaseRejects` | Create failure. |
| `HelpRequestController.CreateSucceeds` | Create success. |
| `HelpRequestController.GetByIdNotFound` | Lookup miss. |
| `HelpRequestController.GetByIdFound` | Lookup hit. |
| `HelpRequestController.GetAllEmptyReturnsSuccessWithEmptyList` | Empty list semantics. |
| `HelpRequestController.GetAllReturnsUserRows` | Rows for user. |
| `HelpRequestController.GetHelpRequestsFromOtherUsersExcludesCurrentUser` | Peer listing rules. |

### 5.7 DB integration — auth (`auth_db_integration_test.cpp`)

| Test case | Description |
|------------|-------------|
| `AuthDbIntegration.RegisterThenLogin` | Register unique user, login, assert user id/email, `deleteUser` cleanup. |
| `AuthDbIntegration.LoginFailsForWrongPassword` | Wrong password rejected; cleanup user. |

*Prerequisites:* `TODO_APP_DB_INTEGRATION_TESTS=ON`, reachable PostgreSQL, `DBConnectionString` available to the process (CTest injects from `config.env` at configure time when possible).

---

## 6. Test environment

| Component | Unit (`api_tests`) | Integration (`api_integration_tests`) |
|-----------|-------------------|----------------------------------------|
| OS | Developer / CI host (e.g. macOS arm64) | Same |
| Compiler | C++20 | Same |
| Database | None (stub) | PostgreSQL per `DBConnectionString` |
| Secrets | N/A | `config.env` / env vars — treat as confidential |

---

## 7. Entry criteria

- Project configures with `TODO_APP_BUILD_TESTS=ON`.
- For integration: `TODO_APP_DB_INTEGRATION_TESTS=ON` and valid `DBConnectionString` (from `config.env` parse or `-DTODO_APP_DB_CONNECTION_STRING=...`).

---

## 8. Exit criteria

- All executed `CTest` tests **Passed** for the agreed configuration.
- No unplanned crashes; integration tests remove created users.

---

## 9. Execution procedure

```bash
cmake -S . -B build -DTODO_APP_BUILD_TESTS=ON
# Optional integration:
cmake -S . -B build -DTODO_APP_BUILD_TESTS=ON -DTODO_APP_DB_INTEGRATION_TESTS=ON

cmake --build build --target api_tests
cmake --build build --target api_integration_tests   # if integration enabled

ctest --test-dir build --output-on-failure
# Or filter:
ctest --test-dir build -R "AuthController|AssignmentController"
```

---

## 10. Risks and mitigations

| Risk | Mitigation |
|------|------------|
| Integration tests mutate real DB | Unique emails; explicit `deleteUser` cleanup. |
| `config.env` contains secrets | Do not commit real production credentials; use disposable DB for CI. |
| Network / RDS unavailable | Skips or failures; run integration only when DB is reachable. |
| Static `DBConnectionString` read before env set | CTest `ENVIRONMENT` sets variables **before** process start; document manual `export` for ad-hoc runs. |

---

## 11. Maintenance

- Add new `TEST(...)` cases beside the code they protect; re-run `cmake` so `gtest_discover_tests` picks up new names.
- Update this plan when new suites (e.g. QML) are added.
