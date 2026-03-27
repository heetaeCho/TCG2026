// File: env_remove_file_test_465.cc
#include "leveldb/env.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock that only mocks the collaborator we observe: DeleteFile.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, DeleteFile, (const std::string& fname), (override));
};

//
// TESTS
//

// Normal operation: RemoveFile should call DeleteFile with the same argument
// exactly once and propagate an OK status.
TEST(EnvRemoveFileTest_465, ForwardsAndReturnsOk_465) {
  StrictMock<MockEnv> env;
  const std::string path = "/tmp/file.dat";

  EXPECT_CALL(env, DeleteFile(path))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = env.RemoveFile(path);
  EXPECT_TRUE(s.ok());
}

// Error propagation: If DeleteFile returns a non-OK status (e.g., NotFound),
// RemoveFile should return the same status (observable via ToString / ok()).
TEST(EnvRemoveFileTest_465, PropagatesErrorStatus_465) {
  StrictMock<MockEnv> env;
  const std::string path = "/tmp/missing.dat";

  // Create a representative non-OK status. We only assert observable behavior.
  const Status expected = Status::NotFound("missing file", path);

  EXPECT_CALL(env, DeleteFile(path))
      .Times(1)
      .WillOnce(Return(expected));

  Status actual = env.RemoveFile(path);
  EXPECT_FALSE(actual.ok());
  // Compare the observable string representation to avoid relying on internals.
  EXPECT_EQ(expected.ToString(), actual.ToString());
}

}  // namespace leveldb
