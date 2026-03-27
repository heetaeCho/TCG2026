// File: env_remove_dir_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/env.h"     // Declares leveldb::Env
#include "leveldb/status.h"  // Declares leveldb::Status

using ::testing::Return;
using ::testing::StrEq;

namespace leveldb {

// A mock that overrides only DeleteDir so we can observe calls.
// RemoveDir will use the real implementation defined in util/env.cc.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, DeleteDir, (const std::string& dirname), (override));
  // Ensure a virtual destructor since Env has one.
  ~MockEnv() override = default;
};

// ---------- Tests ----------

class EnvRemoveDirTest_463 : public ::testing::Test {};

// [Normal] Forwards argument and returns OK when DeleteDir returns OK.
TEST_F(EnvRemoveDirTest_463, ForwardsToDeleteDir_463) {
  MockEnv env;

  const std::string kDir = "path/to/dir";
  EXPECT_CALL(env, DeleteDir(StrEq(kDir)))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = env.RemoveDir(kDir);
  EXPECT_TRUE(s.ok());
}

// [Error propagation] Propagates non-OK status from DeleteDir.
TEST_F(EnvRemoveDirTest_463, PropagatesErrorStatus_463) {
  MockEnv env;

  const std::string kMissing = "missing/dir";
  EXPECT_CALL(env, DeleteDir(StrEq(kMissing)))
      .Times(1)
      .WillOnce(Return(Status::NotFound("dir not found")));

  Status s = env.RemoveDir(kMissing);
  EXPECT_FALSE(s.ok());
}

// [Boundary] Handles empty string directory name by forwarding as-is.
TEST_F(EnvRemoveDirTest_463, ForwardsEmptyDirname_463) {
  MockEnv env;

  const std::string kEmpty = "";
  EXPECT_CALL(env, DeleteDir(StrEq(kEmpty)))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = env.RemoveDir(kEmpty);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
