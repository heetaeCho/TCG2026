// File: write_string_to_file_sync_test.cc

#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

namespace leveldb {

// Forward declare the function under test (normally comes from a header).
Status WriteStringToFileSync(Env* env, const Slice& data, const std::string& fname);

// ---- Test double for the external collaborator: DoWriteStringToFile ----
// We *do not* simulate internal behavior of the class under test. We simply
// intercept the free function dependency to observe the call and return a
// preselected Status, which is an observable outcome at the public interface.

static Env* g_last_env = nullptr;
static std::string g_last_fname;
static std::string g_last_data;
static bool g_last_sync_flag = false;
static Status g_status_to_return = Status::OK();

Status DoWriteStringToFile(Env* env,
                           const Slice& data,
                           const std::string& fname,
                           bool should_sync) {
  g_last_env = env;
  g_last_fname = fname;
  g_last_data.assign(data.data(), data.size());
  g_last_sync_flag = should_sync;
  return g_status_to_return;
}

}  // namespace leveldb

namespace {

using namespace leveldb;

class WriteStringToFileSyncTest_470 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_last_env = nullptr;
    g_last_fname.clear();
    g_last_data.clear();
    g_last_sync_flag = false;
    g_status_to_return = Status::OK();
  }

  // Minimal Env subclass to supply a distinct pointer (no behavior relied upon).
  struct DummyEnv : public Env {};
};

// Normal operation: forwards args and returns OK.
TEST_F(WriteStringToFileSyncTest_470, ForwardsArgsAndSyncs_470) {
  DummyEnv env;
  const std::string fname = "test-file.data";
  const std::string payload = "hello";

  g_status_to_return = Status::OK();

  Status s = WriteStringToFileSync(&env, Slice(payload), fname);

  // Observable result
  EXPECT_TRUE(s.ok());

  // External interaction verification
  EXPECT_EQ(g_last_env, &env);
  EXPECT_EQ(g_last_fname, fname);
  EXPECT_EQ(g_last_data, payload);
  EXPECT_TRUE(g_last_sync_flag);  // must force sync
}

// Error propagation: returns the exact error from the collaborator.
TEST_F(WriteStringToFileSyncTest_470, PropagatesErrorStatus_470) {
  DummyEnv env;
  const std::string fname = "out.dat";
  const std::string payload = "X";

  g_status_to_return = Status::IOError("disk full");

  Status s = WriteStringToFileSync(&env, Slice(payload), fname);

  EXPECT_FALSE(s.ok());
  // The exact string is implementation-defined; check it contains our message.
  EXPECT_NE(s.ToString().find("disk full"), std::string::npos);

  EXPECT_EQ(g_last_env, &env);
  EXPECT_EQ(g_last_fname, fname);
  EXPECT_EQ(g_last_data, payload);
  EXPECT_TRUE(g_last_sync_flag);
}

// Boundary: empty data slice should still delegate and sync.
TEST_F(WriteStringToFileSyncTest_470, HandlesEmptyData_470) {
  DummyEnv env;
  const std::string fname = "empty.bin";

  Status s = WriteStringToFileSync(&env, Slice(""), fname);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(g_last_env, &env);
  EXPECT_EQ(g_last_fname, fname);
  EXPECT_EQ(g_last_data, "");    // empty payload forwarded
  EXPECT_TRUE(g_last_sync_flag); // sync forced
}

// Boundary: long filename is forwarded unchanged.
TEST_F(WriteStringToFileSyncTest_470, ForwardsLongFilenameUnchanged_470) {
  DummyEnv env;
  const std::string long_name(1024, 'a'); // 1KB name
  const std::string payload = "data";

  Status s = WriteStringToFileSync(&env, Slice(payload), long_name);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(g_last_env, &env);
  EXPECT_EQ(g_last_fname, long_name);
  EXPECT_EQ(g_last_data, payload);
  EXPECT_TRUE(g_last_sync_flag);
}

}  // namespace
