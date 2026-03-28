// EnvWrapper_NewSequentialFile_test_106.cc
#include "leveldb/env.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::IsNull;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrEq;

namespace leveldb {

// Minimal mock for Env focusing only on the method under test.
// We do NOT simulate internal EnvWrapper behavior; we just observe interactions.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile,
              (const std::string& fname, SequentialFile** result), (override));
  // Other virtuals are not overridden since they are not used in these tests.
};

class EnvWrapperTest_106 : public ::testing::Test {
 protected:
  MockEnv mock_;
  EnvWrapper wrapper_{&mock_};
};

TEST_F(EnvWrapperTest_106, ForwardsCallAndResult_106) {
  // Arrange: The underlying Env returns OK and sets *result to a sentinel.
  SequentialFile* expected_ptr =
      reinterpret_cast<SequentialFile*>(0xDEADBEEF);
  EXPECT_CALL(mock_, NewSequentialFile(StrEq("path/to/file"), _))
      .WillOnce(DoAll(SetArgPointee<1>(expected_ptr), Return(Status::OK())));

  // Act
  SequentialFile* out = nullptr;
  Status s = wrapper_.NewSequentialFile("path/to/file", &out);

  // Assert: Status and out-parameter are passed through unchanged.
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, expected_ptr);
}

TEST_F(EnvWrapperTest_106, ForwardsErrorStatus_106) {
  // Arrange: Underlying Env reports an error and does not set *result.
  EXPECT_CALL(mock_, NewSequentialFile(StrEq("bad/file"), _))
      .WillOnce(Return(Status::IOError("cannot open")));

  // Act
  SequentialFile* out = reinterpret_cast<SequentialFile*>(0x1);  // pre-set
  Status s = wrapper_.NewSequentialFile("bad/file", &out);

  // Assert: Error status is propagated; out should remain untouched (black box),
  // so we only assert that status is non-OK. We do NOT infer internal behavior
  // like clearing the pointer.
  EXPECT_FALSE(s.ok());
}

TEST_F(EnvWrapperTest_106, AllowsNullOutParam_106) {
  // Arrange: Ensure filename is forwarded even when result pointer is null.
  EXPECT_CALL(mock_, NewSequentialFile(StrEq("any/file"), IsNull()))
      .WillOnce(Return(Status::OK()));

  // Act & Assert: Call should succeed and simply forward to target.
  Status s = wrapper_.NewSequentialFile("any/file", /*result=*/nullptr);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
