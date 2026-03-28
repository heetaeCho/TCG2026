// File: envwrapper_gettestdirectory_test_121.cc

#include "leveldb/env.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::DoAll;
using ::testing::IsNull;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

// Minimal mock for Env's GetTestDirectory used by EnvWrapper.
class MockEnvForGetTestDirectory : public Env {
 public:
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));

  // Silence other pure virtuals for this specific test file by forwarding to default Env if needed.
  // If your build requires more overrides, you can inherit from EnvWrapper around Env::Default().
};

class EnvWrapperTest_121 : public ::testing::Test {
 protected:
  MockEnvForGetTestDirectory mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: forwards call, target sets path, and Status is propagated.
TEST_F(EnvWrapperTest_121, ForwardsCallAndUpdatesPath_121) {
  std::string out;
  const std::string kDir = "/tmp/leveldb-test-dir";

  EXPECT_CALL(mock_, GetTestDirectory(_))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<0>(kDir), Return(Status::OK())));

  Status s = wrapper_.GetTestDirectory(&out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, kDir);
}

// Error propagation: target returns a non-OK Status; wrapper returns the same Status.
// Also verifies that wrapper does not alter *path beyond what the target does (here: target does nothing).
TEST_F(EnvWrapperTest_121, PropagatesErrorStatus_121) {
  std::string out = "unchanged";

  Status not_found = Status::NotFound("no test dir");
  EXPECT_CALL(mock_, GetTestDirectory(_))
      .Times(1)
      .WillOnce(Return(not_found));

  Status s = wrapper_.GetTestDirectory(&out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.ToString(), not_found.ToString());
  EXPECT_EQ(out, "unchanged");  // remains as-is because the mock didn't modify it
}

// Boundary: path == nullptr. Verifies the pointer is forwarded as nullptr and status is returned.
TEST_F(EnvWrapperTest_121, ForwardsNullptrPath_121) {
  EXPECT_CALL(mock_, GetTestDirectory(IsNull()))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  // Call with nullptr; this is about verifying delegation behavior only.
  Status s = wrapper_.GetTestDirectory(nullptr);

  EXPECT_TRUE(s.ok());
}

// Interaction verification: exactly one delegation and no extra calls/side-effects.
TEST_F(EnvWrapperTest_121, SingleDelegationCall_121) {
  std::string out;

  EXPECT_CALL(mock_, GetTestDirectory(&out))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.GetTestDirectory(&out);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
