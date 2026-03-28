// EnvWrapper_NewWritableFile_test_108.cc
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace leveldb {

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;
using ::testing::SetArgPointee;

// Minimal mock of Env to observe external interaction.
// We only mock the collaborator method used by the SUT.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& fname, WritableFile** result), (override));
};

// A trivial concrete WritableFile we can hand out from the mock.
// We won't call into it; it's just an identifiable pointer.
class DummyWritableFile : public WritableFile {
  // No overrides needed; we don't call its methods in these tests.
};

class EnvWrapperTest_108 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
  EnvWrapper wrapper_{&mock_env_};
};

// Normal operation: forwards call, returns Status from target, and sets out param.
TEST_F(EnvWrapperTest_108, NewWritableFile_ForwardsCallAndResult_108) {
  const std::string kPath = "tmp/segment.log";
  DummyWritableFile dummy;
  WritableFile* out = nullptr;

  EXPECT_CALL(mock_env_, NewWritableFile(Eq(kPath), _))
      .WillOnce(testing::DoAll(SetArgPointee<1>(&dummy), Return(Status::OK())));

  Status s = wrapper_.NewWritableFile(kPath, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, &dummy);
}

// Error case: propagates non-OK Status and does not modify the out pointer.
TEST_F(EnvWrapperTest_108, NewWritableFile_PropagatesErrorStatus_108) {
  const std::string kPath = "tmp/fail.log";
  WritableFile* out = nullptr;  // Ensure untouched on failure.

  EXPECT_CALL(mock_env_, NewWritableFile(Eq(kPath), _))
      .WillOnce(Return(Status::IOError("disk full")));

  Status s = wrapper_.NewWritableFile(kPath, &out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(out, nullptr);
}

// Boundary: forwards a nullptr result parameter as-is to the target.
TEST_F(EnvWrapperTest_108, NewWritableFile_ForwardsNullOutputPointer_108) {
  const std::string kPath = "tmp/ignore_result.log";

  EXPECT_CALL(mock_env_, NewWritableFile(Eq(kPath), nullptr))
      .WillOnce(Return(Status::OK()));

  // We only verify delegation; we do not dereference the null out param.
  Status s = wrapper_.NewWritableFile(kPath, /*result=*/nullptr);

  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
