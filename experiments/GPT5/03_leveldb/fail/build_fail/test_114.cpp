// File: envwrapper_remove_dir_test_114.cc
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;
using leveldb::Env;
using leveldb::EnvWrapper;
using leveldb::Status;

namespace {

// Minimal mock of Env focusing only on the collaborator method we verify.
// We rely on Env providing default implementations for other virtual methods.
class MockEnv : public Env {
public:
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
};

}  // namespace

// Verifies that EnvWrapper forwards the exact path to the target Env and
// returns the exact Status propagated from the target.
TEST(EnvWrapper_RemoveDirTest_114, ForwardsAndPropagatesStatus_114) {
  StrictMock<MockEnv> mock_env;
  EnvWrapper wrapper(&mock_env);

  const std::string kPath = "some/dir";
  const Status kWant = Status::NotFound("no such dir");

  EXPECT_CALL(mock_env, RemoveDir(kPath))
      .WillOnce(Return(kWant));

  Status got = wrapper.RemoveDir(kPath);
  // Compare via ToString() (portable across Status variants) without
  // assuming operator== semantics.
  EXPECT_EQ(kWant.ToString(), got.ToString());
}

// Verifies boundary behavior with an empty path: still forwards exactly and
// returns what the target provides (no assumptions about internal checks).
TEST(EnvWrapper_RemoveDirTest_114, EmptyPathIsForwarded_114) {
  StrictMock<MockEnv> mock_env;
  EnvWrapper wrapper(&mock_env);

  const std::string kEmptyPath;
  const Status kWant = Status::InvalidArgument("empty dirname");

  EXPECT_CALL(mock_env, RemoveDir(kEmptyPath))
      .WillOnce(Return(kWant));

  Status got = wrapper.RemoveDir(kEmptyPath);
  EXPECT_EQ(kWant.ToString(), got.ToString());
}

// Verifies that unusual characters are passed through unchanged and the
// returned Status is propagated as-is.
TEST(EnvWrapper_RemoveDirTest_114, SpecialCharactersPathIsForwarded_114) {
  StrictMock<MockEnv> mock_env;
  EnvWrapper wrapper(&mock_env);

  const std::string kWeirdPath = "/tmp/한글 spaces/../.#$%^&()!";
  const Status kWant = Status::OK();

  EXPECT_CALL(mock_env, RemoveDir(kWeirdPath))
      .WillOnce(Return(kWant));

  Status got = wrapper.RemoveDir(kWeirdPath);
  EXPECT_EQ(kWant.ToString(), got.ToString());
}

// Verifies that exactly one collaborator interaction occurs for one call,
// with no extra calls to RemoveDir (StrictMock enforces this).
TEST(EnvWrapper_RemoveDirTest_114, SingleCall_NoExtraInteractions_114) {
  StrictMock<MockEnv> mock_env;
  EnvWrapper wrapper(&mock_env);

  const std::string kPath = "only/once";
  const Status kWant = Status::IOError("fs error");

  EXPECT_CALL(mock_env, RemoveDir(kPath))
      .WillOnce(Return(kWant));

  Status got = wrapper.RemoveDir(kPath);
  EXPECT_EQ(kWant.ToString(), got.ToString());
}

