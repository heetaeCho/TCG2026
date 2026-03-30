// File: c_api_destroy_db_test.cc
#include <gtest/gtest.h>
#include <string>

// ---- Minimal public-facing types to satisfy the interface (no internal logic inferred) ----
namespace leveldb {
struct Options {};

// Minimal Status stub for interaction observation only.
class Status {
 public:
  static Status OK() { return Status(true); }
  static Status Error() { return Status(false); }
  bool ok() const { return ok_; }
 private:
  explicit Status(bool ok) : ok_(ok) {}
  bool ok_;
};

// Forward declarations of the external collaborators we will fake.
Status DestroyDB(const std::string& name, const Options& options);
void SaveError(char** errptr, const Status& s);
}  // namespace leveldb

// The C wrapper struct as given.
struct leveldb_options_t { public: leveldb::Options rep; };

// Production function under test (implemented in db/c.cc).
extern "C" void leveldb_destroy_db(const leveldb_options_t* options,
                                   const char* name,
                                   char** errptr);

// ---- Test doubles (link-time fakes) for external collaborators ----
namespace {
struct CallLog {
  int destroy_calls = 0;
  int save_error_calls = 0;
  std::string last_name;
  const void* last_options_addr = nullptr;
  const void* last_errptr_addr = nullptr;
  bool last_status_ok = false;
} g_log;

leveldb::Status g_next_destroy_status = leveldb::Status::OK();

}  // namespace

namespace leveldb {

// Fake DestroyDB: records name/options and returns a pre-set status.
Status DestroyDB(const std::string& name, const Options& options) {
  ++g_log.destroy_calls;
  g_log.last_name = name;
  g_log.last_options_addr = &options;
  return g_next_destroy_status;
}

// Fake SaveError: records the errptr pointer and whether status is ok.
void SaveError(char** errptr, const Status& s) {
  ++g_log.save_error_calls;
  g_log.last_errptr_addr = static_cast<void*>(errptr);
  g_log.last_status_ok = s.ok();
}

}  // namespace leveldb

// ---- Test fixture ----
class CApiDestroyDBTest_232 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_log = CallLog{};
    leveldb::g_next_destroy_status = leveldb::Status::OK();
  }
};

// --- Tests ---

// Normal operation: DestroyDB OK -> SaveError is called with OK; name/options are forwarded.
TEST_F(CApiDestroyDBTest_232, CallsDestroyAndSaveError_OK_232) {
  leveldb_options_t opts;
  const char* name = "tmp/db_to_destroy";
  char* err = nullptr;

  leveldb_destroy_db(&opts, name, &err);

  EXPECT_EQ(1, g_log.destroy_calls);
  EXPECT_EQ(1, g_log.save_error_calls);

  // Verifies the wrapper forwarded the exact name and options reference.
  EXPECT_EQ(std::string(name), g_log.last_name);
  EXPECT_EQ(&opts.rep, g_log.last_options_addr);

  // Verifies SaveError saw the same errptr pointer and OK status.
  EXPECT_EQ(&err, g_log.last_errptr_addr);
  EXPECT_TRUE(g_log.last_status_ok);
}

// Error case: DestroyDB fails -> SaveError is called with non-OK; forwarding still correct.
TEST_F(CApiDestroyDBTest_232, CallsSaveError_OnErrorStatus_232) {
  leveldb_options_t opts;
  const char* name = "/path/failure_example";
  char* err = nullptr;

  leveldb::g_next_destroy_status = leveldb::Status::Error();
  leveldb_destroy_db(&opts, name, &err);

  EXPECT_EQ(1, g_log.destroy_calls);
  EXPECT_EQ(1, g_log.save_error_calls);
  EXPECT_EQ(std::string(name), g_log.last_name);
  EXPECT_EQ(&opts.rep, g_log.last_options_addr);
  EXPECT_EQ(&err, g_log.last_errptr_addr);
  EXPECT_FALSE(g_log.last_status_ok);
}

// Boundary: errptr == nullptr should be passed through to SaveError without crashing.
TEST_F(CApiDestroyDBTest_232, NullErrptr_IsPassedToSaveError_232) {
  leveldb_options_t opts;
  const char* name = "any/path";
  char** errptr_null = nullptr;  // boundary input

  // Leave DestroyDB as OK; we only care that SaveError is invoked with nullptr errptr.
  leveldb_destroy_db(&opts, name, errptr_null);

  EXPECT_EQ(1, g_log.destroy_calls);
  EXPECT_EQ(1, g_log.save_error_calls);
  EXPECT_EQ(std::string(name), g_log.last_name);
  EXPECT_EQ(&opts.rep, g_log.last_options_addr);
  EXPECT_EQ(static_cast<void*>(nullptr), g_log.last_errptr_addr);
  EXPECT_TRUE(g_log.last_status_ok);
}
