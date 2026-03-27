// EnvWrapper_RemoveFile_test_112.cc
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock for the external collaborator (Env).
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
};

// Test fixture
class EnvWrapperTest_112 : public ::testing::Test {
 protected:
  StrictMock<MockEnv> mock_env_;
  EnvWrapper wrapper_{&mock_env_};
};

// 1) Normal operation: forwards the call and returns the same Status (OK)
TEST_F(EnvWrapperTest_112, RemoveFile_DelegatesAndReturnsOk_112) {
  const std::string kPath = "a/b/c.dat";
  EXPECT_CALL(mock_env_, RemoveFile(kPath))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.RemoveFile(kPath);
  EXPECT_TRUE(s.ok());
}

// 2) Error propagation: non-OK from target is surfaced unchanged by wrapper
TEST_F(EnvWrapperTest_112, RemoveFile_PropagatesErrorStatus_112) {
  const std::string kPath = "missing.file";

  // Return a non-OK Status from the target; wrapper should propagate it.
  // Using IOError() as an observable non-OK status.
  EXPECT_CALL(mock_env_, RemoveFile(kPath))
      .Times(1)
      .WillOnce(Return(Status::IOError("remove failed")));

  Status s = wrapper_.RemoveFile(kPath);
  EXPECT_FALSE(s.ok());
}

// 3) Boundary condition: empty filename should still be forwarded verbatim
TEST_F(EnvWrapperTest_112, RemoveFile_EmptyPathForwarded_112) {
  const std::string kEmptyPath = "";

  EXPECT_CALL(mock_env_, RemoveFile(kEmptyPath))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.RemoveFile(kEmptyPath);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
