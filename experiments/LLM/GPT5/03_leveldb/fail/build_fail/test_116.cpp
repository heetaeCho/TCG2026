// EnvWrapper_RenameFile_test_116.cc
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock of Env focusing only on the collaborator method we exercise.
class MockEnv_116 : public Env {
 public:
  MOCK_METHOD(Status, RenameFile, (const std::string& src, const std::string& dst), (override));
};

class EnvWrapperTest_116 : public ::testing::Test {
 protected:
  EnvWrapperTest_116() : mock_(new StrictMock<MockEnv_116>()), wrapper_(mock_) {}
  ~EnvWrapperTest_116() override = default;

  StrictMock<MockEnv_116>* mock_;  // Owned by the test fixture
  EnvWrapper wrapper_;
};

// Normal operation: forwards parameters and returns OK from target.
TEST_F(EnvWrapperTest_116, RenameFile_ForwardsParamsAndReturnsOK_116) {
  const std::string src = "from.dat";
  const std::string dst = "to.dat";
  Status ok;  // default-constructed Status in LevelDB is OK

  EXPECT_CALL(*mock_, RenameFile(src, dst))
      .Times(1)
      .WillOnce(Return(ok));

  Status s = wrapper_.RenameFile(src, dst);
  EXPECT_TRUE(s.ok());
}

// Error propagation: wrapper should return exactly what target returns.
TEST_F(EnvWrapperTest_116, RenameFile_PropagatesErrorStatus_116) {
  const std::string src = "missing.file";
  const std::string dst = "irrelevant.target";
  Status not_found = Status::NotFound("rename", "src not found");

  EXPECT_CALL(*mock_, RenameFile(src, dst))
      .Times(1)
      .WillOnce(Return(not_found));

  Status s = wrapper_.RenameFile(src, dst);
  EXPECT_EQ(s.code(), not_found.code());   // observable via Status API
  EXPECT_FALSE(s.ok());
}

// Boundary: empty strings should still be forwarded exactly as-is.
TEST_F(EnvWrapperTest_116, RenameFile_EmptyPaths_116) {
  const std::string src;
  const std::string dst;
  Status ioerr = Status::IOError("empty paths");

  EXPECT_CALL(*mock_, RenameFile(src, dst))
      .Times(1)
      .WillOnce(Return(ioerr));

  Status s = wrapper_.RenameFile(src, dst);
  EXPECT_EQ(s.code(), ioerr.code());
  EXPECT_FALSE(s.ok());
}

// Boundary: very long path strings are forwarded unchanged.
TEST_F(EnvWrapperTest_116, RenameFile_VeryLongPaths_116) {
  std::string src(4096, 'a');
  std::string dst(4096, 'b');
  Status ok;  // OK

  EXPECT_CALL(*mock_, RenameFile(src, dst))
      .Times(1)
      .WillOnce(Return(ok));

  Status s = wrapper_.RenameFile(src, dst);
  EXPECT_TRUE(s.ok());
}

// Edge case: src == dst; still must forward as-is and return target's status.
TEST_F(EnvWrapperTest_116, RenameFile_SourceEqualsTarget_116) {
  const std::string path = "same.file";
  Status invalid = Status::InvalidArgument("source equals target");

  EXPECT_CALL(*mock_, RenameFile(path, path))
      .Times(1)
      .WillOnce(Return(invalid));

  Status s = wrapper_.RenameFile(path, path);
  EXPECT_EQ(s.code(), invalid.code());
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
