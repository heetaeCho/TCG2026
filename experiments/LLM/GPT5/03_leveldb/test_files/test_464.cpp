// Env_DeleteDir_test.cc
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::StrEq;

namespace leveldb {

class MockEnvForDeleteDir : public Env {
 public:
  // Only mock the collaborator we observe: RemoveDir.
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  // Inherit the real base implementation of DeleteDir that calls RemoveDir.
  // (No override for DeleteDir here.)
};

class EnvDeleteDirTest_464 : public ::testing::Test {
 protected:
  MockEnvForDeleteDir env_;
};

// Normal operation: DeleteDir forwards the same path to RemoveDir and
// returns OK when RemoveDir returns OK.
TEST_F(EnvDeleteDirTest_464, ForwardsToRemoveDirAndReturnsOk_464) {
  const std::string kPath = "/tmp/some_dir";
  EXPECT_CALL(env_, RemoveDir(StrEq(kPath)))
      .WillOnce(Return(Status::OK()));

  Status s = env_.DeleteDir(kPath);
  EXPECT_TRUE(s.ok());
}

// Error propagation: if RemoveDir fails, DeleteDir returns the same failure.
TEST_F(EnvDeleteDirTest_464, PropagatesErrorFromRemoveDir_464) {
  const std::string kPath = "/tmp/missing_dir";
  EXPECT_CALL(env_, RemoveDir(StrEq(kPath)))
      .WillOnce(Return(Status::NotFound("dir not found", kPath)));

  Status s = env_.DeleteDir(kPath);
  EXPECT_FALSE(s.ok());
}

// Boundary condition: empty dirname should still be forwarded exactly,
// and the result should be whatever RemoveDir returns.
TEST_F(EnvDeleteDirTest_464, EmptyDirnameIsForwarded_464) {
  const std::string kEmpty;
  EXPECT_CALL(env_, RemoveDir(StrEq(kEmpty)))
      .WillOnce(Return(Status::OK()));

  Status s = env_.DeleteDir(kEmpty);
  EXPECT_TRUE(s.ok());
}

// Boundary/special characters: unusual paths are forwarded verbatim.
TEST_F(EnvDeleteDirTest_464, SpecialCharactersInPathAreForwarded_464) {
  const std::string kWeird = "///..//weird path/한글/🚀";
  EXPECT_CALL(env_, RemoveDir(StrEq(kWeird)))
      .WillOnce(Return(Status::OK()));

  Status s = env_.DeleteDir(kWeird);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
