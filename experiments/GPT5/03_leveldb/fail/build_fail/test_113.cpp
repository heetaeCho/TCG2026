// EnvWrapper_CreateDir_test_113.cc
#include "leveldb/env.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::StrictMock;
using ::testing::StrEq;

namespace leveldb {

// Minimal mock of Env that overrides only what we exercise.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
};

class EnvWrapperTest_113 : public ::testing::Test {
 protected:
  StrictMock<MockEnv> mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: forwards the exact path and returns success from target.
TEST_F(EnvWrapperTest_113, ForwardsCreateDirAndReturnsOk_113) {
  const std::string kPath = "a/b/c";
  EXPECT_CALL(mock_, CreateDir(StrEq(kPath)))
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.CreateDir(kPath);
  EXPECT_TRUE(s.ok());
}

// Error propagation: wrapper must propagate a non-OK status from target.
TEST_F(EnvWrapperTest_113, PropagatesErrorFromTarget_113) {
  const std::string kPath = "/root/protected";
  // Use a clear non-OK status (interface-observable).
  Status expected = Status::IOError("permission denied");
  EXPECT_CALL(mock_, CreateDir(StrEq(kPath)))
      .WillOnce(Return(expected));

  Status s = wrapper_.CreateDir(kPath);
  EXPECT_FALSE(s.ok());
}

// Boundary condition: empty directory name should still be forwarded as-is.
TEST_F(EnvWrapperTest_113, ForwardsEmptyDirectoryName_113) {
  const std::string kEmpty;
  EXPECT_CALL(mock_, CreateDir(StrEq(kEmpty)))
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.CreateDir(kEmpty);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
