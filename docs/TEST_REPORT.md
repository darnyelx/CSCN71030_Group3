# Test Report — todo_app (CSCN71030 Group3)

**Report date:** 2026-04-17  
**Document version:** 1.0  
**Execution tool:** CTest (GoogleTest)  
**Build directory:** `build/` (example)

---

## 1. Executive summary

Automated tests cover the **API layer** with an in-memory **`StubDatabase`** (30 cases) and, when the integration target is built, **two** additional tests that exercise **`AuthController`** against the real **`DB`** / PostgreSQL (**32** total discovered tests in the configuration used for this report).

**Result (this run):** **32 / 32 passed**, **0 failed** (total wall time ~7 s; integration cases dominate runtime).

---

## 2. Configuration under test

| Setting | Value (this report) |
|---------|---------------------|
| `TODO_APP_BUILD_TESTS` | ON |
| `TODO_APP_DB_INTEGRATION_TESTS` | ON (integration binary + tests present) |
| `DBConnectionString` for CTest | Injected from repository `config.env` at CMake configure time (see `CMakeLists.txt`) |

---

## 3. Suite breakdown

| Suite | Executable | Tests | Role |
|-------|------------|------:|------|
| API unit / controller | `api_tests` | 30 | Stub DB, no PostgreSQL |
| Auth + DB integration | `api_integration_tests` | 2 | Live PostgreSQL |

---

## 4. Detailed results

### 4.1 `api_tests` (30 tests)

| # | Test name | Result | Time (approx.) |
|---|-----------|--------|------------------|
| 1 | `UserModel.TableNameAndFluentSetters` | Passed | sub-second |
| 2 | `Assignment.TableNameAndFields` | Passed | sub-second |
| 3 | `Course.TableNameAndFields` | Passed | sub-second |
| 4 | `HelpRequestModel.TableNameAndSetters` | Passed | sub-second |
| 5 | `AuthController.RegisterUserRejectsEmptyFirstName` | Passed | sub-second |
| 6 | `AuthController.RegisterUserRejectsEmptyLastName` | Passed | sub-second |
| 7 | `AuthController.RegisterUserRejectsEmptyEmail` | Passed | sub-second |
| 8 | `AuthController.RegisterUserRejectsEmptyPassword` | Passed | sub-second |
| 9 | `AssignmentController.CreateAssignmentFailsWhenDatabaseRejects` | Passed | sub-second |
| 10 | `AssignmentController.CreateAssignmentSucceeds` | Passed | sub-second |
| 11 | `AssignmentController.GetAssignmentNotFound` | Passed | sub-second |
| 12 | `AssignmentController.GetAssignmentFound` | Passed | sub-second |
| 13 | `AssignmentController.UpdateAssignmentNotFound` | Passed | sub-second |
| 14 | `AssignmentController.UpdateAssignmentSucceeds` | Passed | sub-second |
| 15 | `AssignmentController.GetAllAssignmentsReturnsUserRows` | Passed | sub-second |
| 16 | `AssignmentController.DeleteAssignment` | Passed | sub-second |
| 17 | `CourseController.GetAllCoursesSuccess` | Passed | sub-second |
| 18 | `CourseController.GetAllCoursesHandlesException` | Passed | sub-second |
| 19 | `AssignmentQueryController.SearchByKeywordMatchesTitleOrDescription` | Passed | sub-second |
| 20 | `AssignmentQueryController.FilterByCourse` | Passed | sub-second |
| 21 | `AssignmentQueryController.FilterByPriority` | Passed | sub-second |
| 22 | `AssignmentQueryController.OrderByDueDate` | Passed | sub-second |
| 23 | `AssignmentQueryController.OrderByPriorityDescending` | Passed | sub-second |
| 24 | `HelpRequestController.CreateFailsWhenDatabaseRejects` | Passed | sub-second |
| 25 | `HelpRequestController.CreateSucceeds` | Passed | sub-second |
| 26 | `HelpRequestController.GetByIdNotFound` | Passed | sub-second |
| 27 | `HelpRequestController.GetByIdFound` | Passed | sub-second |
| 28 | `HelpRequestController.GetAllEmptyReturnsSuccessWithEmptyList` | Passed | sub-second |
| 29 | `HelpRequestController.GetAllReturnsUserRows` | Passed | sub-second |
| 30 | `HelpRequestController.GetHelpRequestsFromOtherUsersExcludesCurrentUser` | Passed | sub-second |

### 4.2 `api_integration_tests` (2 tests)

| # | Test name | Result | Time (approx.) |
|---|-----------|--------|------------------|
| 31 | `AuthDbIntegration.RegisterThenLogin` | Passed | ~3.5 s |
| 32 | `AuthDbIntegration.LoginFailsForWrongPassword` | Passed | ~3.4 s |

*Note:* Integration duration depends on network latency to the configured PostgreSQL host.

---

## 5. Summary metrics

| Metric | Value |
|--------|------:|
| Total tests executed | 32 |
| Passed | 32 |
| Failed | 0 |
| Skipped | 0 |
| Approx. total time | 7.0 s |

---

## 6. How to reproduce this report

```bash
cmake -S . -B build -DTODO_APP_BUILD_TESTS=ON -DTODO_APP_DB_INTEGRATION_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

With **`TODO_APP_DB_INTEGRATION_TESTS=OFF`**, expect **30** tests (integration binary not built / not discovered).

---

## 7. Known gaps (not defects in this run)

- No automated **QML/UI** tests.
- Integration coverage is limited to **auth register/login** (not assignments/courses/help requests against `DB`).
- `AuthController::registerUser` has a compiler warning (non-void path) in `AuthController.cpp`; worth fixing separately.

---


