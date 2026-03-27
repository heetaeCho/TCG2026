// c_open_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <functional>

// --- Public-facing C API under test (forward decls that match production) ---
struct leveldb_t;
struct leveldb_options_t;

extern "C" leveldb_t* leveldb_open(const leveldb_options_t* options,
                                   const char* name,
                                   char** errptr);

// --- Minimal API surface for the external collaborator we need to control ---
// These declarations mirror the production signatures so the test links cleanly.
namespace leveldb {

class Status {
 public:
  Status() : ok_(true) {}
  static Status OK() { return Status(true); }
  static Status NotFound() { return Status(false); }
  bool ok() const { return ok_; }

 private:
  explicit Status(bool ok) : ok_(ok) {}
  bool ok_;
};

struct Options {};

// DB interface surface needed by leveldb_open
class DB {
 public:
  virtual ~DB() = default;
  static Status Open(const Options& options, const std::string& name, DB** dbptr);
};

// A tiny concrete DB we can hand back through DB::Open
class FakeDB : public DB {
 public:
  ~FakeDB() override = default;
};

}  // namespace leveldb

// The opaque C wrappers used by leveldb_open.
// We forward-declare shapes that match production for type compatibility.
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_options_t { leveldb::Options rep; };

// ---- Link seam for leveldb::DB::Open --------------------------------------
// We provide a test-controlled definition of DB::Open. The production object
// file will bind to this symbol at link time in tests, letting us drive outcomes.
namespace {
using OpenFn = std::function<leveldb::Status(const leveldb::Options&,
                                             const std::string&,
                                             leveldb::DB**)>;

OpenFn& OpenBehavior() {
  static OpenFn fn;
  return fn;
}
}  // namespace

namespace leveldb {
Status DB::Open(const Options& options, const std::string& name, DB** dbptr) {
  // Delegate to the test-controlled behavior.
  if (OpenBehavior()) {
    return OpenBehavior()(options, name, dbptr);
  }
  // Default: succeed and provide a DB.
  if (dbptr) *dbptr = new FakeDB();
  return Status::OK();
}
}  // namespace leveldb

// --------------------------- Test Fixture -----------------------------------
class CApiOpenTest_220 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset behavior for each test to a known state.
    OpenBehavior() = nullptr;
  }

  static leveldb_options_t MakeDefaultOptions() {
    leveldb_options_t opts{};
    return opts;
  }
};

// =============================== TESTS =======================================

// Normal operation: DB::Open returns OK and provides a DB*.
// Expect: non-null handle, handle->rep is the same DB* pointer, errptr remains null.
TEST_F(CApiOpenTest_220, OpenSuccess_ReturnsHandleAndRepSet_220) {
  auto* expected_db = new leveldb::FakeDB();
  OpenBehavior() = [expected_db](const leveldb::Options&, const std::string& name, leveldb::DB** out) {
    // Provide a DB instance and succeed.
    if (out) *out = expected_db;
    // Name should be passed through as-is; we won’t assert on content beyond being non-empty.
    EXPECT_FALSE(name.empty());
    return leveldb::Status::OK();
  };

  leveldb_options_t opts = MakeDefaultOptions();
  char* err = nullptr;

  leveldb_t* handle = leveldb_open(&opts, "test-db", &err);

  ASSERT_NE(handle, nullptr) << "On success, leveldb_open must return a handle";
  EXPECT_EQ(handle->rep, expected_db) << "Handle must wrap the DB* returned by DB::Open";
  EXPECT_EQ(err, nullptr) << "On success, errptr should remain null";

  // Clean up the fake DB to avoid a leak in the test.
  delete handle->rep;
  delete handle;
}

// Error path: DB::Open returns a non-OK Status.
// Expect: nullptr handle, and errptr is set (some non-null error string).
TEST_F(CApiOpenTest_220, OpenError_ReturnsNullAndSetsErr_220) {
  OpenBehavior() = [](const leveldb::Options&, const std::string& /*name*/, leveldb::DB** out) {
    if (out) *out = nullptr;               // Simulate failure: no DB produced
    return leveldb::Status::NotFound();    // Non-OK status
  };

  leveldb_options_t opts = MakeDefaultOptions();
  char* err = nullptr;

  leveldb_t* handle = leveldb_open(&opts, "missing-db", &err);

  EXPECT_EQ(handle, nullptr) << "On error, leveldb_open must return nullptr";
  // Observable behavior via the C API: errptr should be set to a non-null error message.
  EXPECT_NE(err, nullptr) << "On error, errptr should be set";
  // Caller usually frees err via free(); we can't assume allocator here, so we don't free it.
}

// Boundary-ish collaborator behavior: DB::Open returns OK but forgets to set *dbptr.
// We don't assume internal checks in leveldb_open; we only verify observable outcome.
// Expect: a non-null handle is still created (since code allocates leveldb_t on OK path),
// but its rep may be nullptr because DB::Open gave no DB*. That’s observable via public fields.
TEST_F(CApiOpenTest_220, OpenSuccess_NoDBProvided_HandleRepIsNull_220) {
  OpenBehavior() = [](const leveldb::Options&, const std::string&, leveldb::DB** out) {
    if (out) *out = nullptr;            // Buggy provider: succeeds without a DB
    return leveldb::Status::OK();       // Status reports success
  };

  leveldb_options_t opts = MakeDefaultOptions();
  char* err = nullptr;

  leveldb_t* handle = leveldb_open(&opts, "ok-but-empty", &err);

  ASSERT_NE(handle, nullptr) << "On reported success, leveldb_open should return a handle";
  EXPECT_EQ(handle->rep, nullptr) << "When DB::Open doesn't supply a DB*, rep should be null";
  EXPECT_EQ(err, nullptr) << "On reported success, errptr should remain null";

  delete handle;  // handle->rep is nullptr, so only delete handle itself.
}

