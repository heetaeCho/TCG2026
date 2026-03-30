// File: envwrapper_unlockfile_test_118.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/env.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// ---- Test doubles ----
class MockEnvForUnlock : public Env {
 public:
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));
};

// A simple concrete FileLock to pass around (FileLock has a virtual dtor).
class TestFileLock : public FileLock {};

// ---- Test fixture ----
class EnvWrapperTest_118 : public ::testing::Test {
 protected:
  StrictMock<MockEnvForUnlock> mock_env_;
  EnvWrapper wrapper_{&mock_env_};
};

// Normal operation: forwarding and OK propagation
TEST_F(EnvWrapperTest_118, UnlockFile_ForwardsAndReturnsOk_118) {
  TestFileLock fl;
  FileLock* lock_ptr = &fl;

  EXPECT_CALL(mock_env_, UnlockFile(lock_ptr))
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.UnlockFile(lock_ptr);
  EXPECT_TRUE(s.ok());
}

// Boundary: nullptr lock pointer should still be forwarded exactly as-is
TEST_F(EnvWrapperTest_118, UnlockFile_AcceptsNullLockAndForwards_118) {
  FileLock* lock_ptr = nullptr;

  EXPECT_CALL(mock_env_, UnlockFile(lock_ptr))
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.UnlockFile(lock_ptr);
  EXPECT_TRUE(s.ok());
}

// Error propagation: non-OK from target must be returned unchanged
TEST_F(EnvWrapperTest_118, UnlockFile_PropagatesErrorStatus_118) {
  TestFileLock fl;
  FileLock* lock_ptr = &fl;

  // Use a concrete non-OK to ensure we can observe the error result.
  EXPECT_CALL(mock_env_, UnlockFile(lock_ptr))
      .WillOnce(Return(Status::IOError("unlock failed")));

  Status s = wrapper_.UnlockFile(lock_ptr);
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
