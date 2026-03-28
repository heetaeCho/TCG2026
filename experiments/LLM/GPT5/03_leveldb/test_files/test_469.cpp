// File: write_string_to_file_test_469.cc

#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "gtest/gtest.h"

namespace {

// ---------- Test seam for the external collaborator ----------
// We interpose a test-only replacement for DoWriteStringToFile so we can
// observe the parameters passed by WriteStringToFile and control the Status
// it returns. This is allowed as we're mocking an *external* collaborator
// (not simulating internal behavior of the function under test).

struct CapturedCall {
  const leveldb::Env* env = nullptr;
  std::string data;          // capture data contents for observation
  std::string fname;         // capture file name
  bool sync_flag = true;     // will verify this becomes false
  bool was_called = false;
};

CapturedCall g_captured;
leveldb::Status g_return_status;  // set per-test to control the return

}  // namespace

namespace leveldb {

// Forward declaration of the production function under test.
Status WriteStringToFile(Env* env, const Slice& data, const std::string& fname);

// Test double for the external dependency that WriteStringToFile calls.
Status DoWriteStringToFile(Env* env,
                           const Slice& data,
                           const std::string& fname,
                           bool should_sync) {
  g_captured.was_called = true;
  g_captured.env = env;
  g_captured.data.assign(data.data(), data.size());
  g_captured.fname = fname;
  g_captured.sync_flag = should_sync;
  // Return the status configured by the test case.
  return g_return_status;
}

}  // namespace leveldb

// Minimal concrete Env so we can pass a stable pointer through; we never invoke
// any methods on it in these tests.
class DummyEnv_469 : public leveldb::Env {};

class WriteStringToFileTest_469 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset capture between tests
    g_captured = CapturedCall{};
    // Default to OK; individual tests override as needed
    g_return_status = leveldb::Status::OK();
  }
};

// Verifies that WriteStringToFile forwards all parameters correctly and sets
// should_sync = false when delegating to DoWriteStringToFile.
TEST_F(WriteStringToFileTest_469, DelegatesWithSyncFalse_469) {
  DummyEnv_469 env;
  const std::string contents = "hello";
  const std::string fname = "tmp/file.txt";

  leveldb::Status s =
      leveldb::WriteStringToFile(&env, leveldb::Slice(contents), fname);

  ASSERT_TRUE(g_captured.was_called) << "DoWriteStringToFile should be called";
  EXPECT_EQ(&env, g_captured.env);
  EXPECT_EQ(contents, g_captured.data);
  EXPECT_EQ(fname, g_captured.fname);
  EXPECT_FALSE(g_captured.sync_flag) << "WriteStringToFile must pass sync=false";
  EXPECT_TRUE(s.ok()) << "Status should be propagated from DoWriteStringToFile";
}

// Verifies that the Status returned by DoWriteStringToFile is propagated
// unchanged to the caller of WriteStringToFile (observable via ok()).
TEST_F(WriteStringToFileTest_469, PropagatesErrorStatus_469) {
  DummyEnv_469 env;
  // Configure the seam to return a non-OK status.
  g_return_status = leveldb::Status::IOError("boom");

  leveldb::Status s =
      leveldb::WriteStringToFile(&env, leveldb::Slice("x"), "a.txt");

  ASSERT_TRUE(g_captured.was_called);
  EXPECT_FALSE(s.ok()) << "Non-OK status must propagate to caller";
}

// Verifies behavior with boundary input: empty data slice is forwarded as-is
// and still uses sync=false.
TEST_F(WriteStringToFileTest_469, HandlesEmptyData_469) {
  DummyEnv_469 env;
  leveldb::Slice empty;  // default-constructed -> empty

  leveldb::Status s =
      leveldb::WriteStringToFile(&env, empty, "empty.txt");

  ASSERT_TRUE(g_captured.was_called);
  EXPECT_EQ("", g_captured.data);
  EXPECT_EQ("empty.txt", g_captured.fname);
  EXPECT_FALSE(g_captured.sync_flag);
  EXPECT_TRUE(s.ok());
}
