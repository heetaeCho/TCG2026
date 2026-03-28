// status_not_supported_test_18.cc
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using leveldb::Status;
using leveldb::Slice;
using ::testing::HasSubstr;

class StatusNotSupportedTest_18 : public ::testing::Test {};

// Verifies error classification flags and ok() for NotSupported.
TEST_F(StatusNotSupportedTest_18, SetsFlagAndNotOk_18) {
  Status s = Status::NotSupported(Slice("feature-x"));
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());

  // Also verify it's NOT any other error class we can observe via the interface.
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// ToString should include the primary message (observable via substring match).
TEST_F(StatusNotSupportedTest_18, ToStringContainsPrimaryMessage_18) {
  const std::string msg = "operation not available";
  Status s = Status::NotSupported(Slice(msg));
  const std::string str = s.ToString();

  EXPECT_FALSE(str.empty());
  EXPECT_THAT(str, HasSubstr(msg));
}

// When both messages are provided, both should be observable in ToString.
TEST_F(StatusNotSupportedTest_18, ToStringContainsBothMessages_18) {
  const std::string m1 = "compress";
  const std::string m2 = "lz4";
  Status s = Status::NotSupported(Slice(m1), Slice(m2));
  const std::string str = s.ToString();

  EXPECT_THAT(str, HasSubstr(m1));
  EXPECT_THAT(str, HasSubstr(m2));
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
}

// Boundary: empty messages are allowed; ToString should still describe the status.
TEST_F(StatusNotSupportedTest_18, EmptyMessagesStillDescribeStatus_18) {
  Status s = Status::NotSupported(Slice(), Slice());
  const std::string str = s.ToString();

  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(str.empty());           // observable description present
}

// Construction from different Slice sources should behave consistently.
TEST_F(StatusNotSupportedTest_18, AcceptsVariousSliceSources_18) {
  // From const char*
  Status a = Status::NotSupported("alpha");
  // From std::string
  std::string beta = "beta";
  Status b = Status::NotSupported(beta);
  // From (const char*, size_t)
  const char* gamma_c = "gamma-extra";
  Slice gamma{gamma_c, 5}; // "gamma"
  Status c = Status::NotSupported(gamma);

  EXPECT_TRUE(a.IsNotSupportedError());
  EXPECT_TRUE(b.IsNotSupportedError());
  EXPECT_TRUE(c.IsNotSupportedError());

  EXPECT_THAT(a.ToString(), HasSubstr("alpha"));
  EXPECT_THAT(b.ToString(), HasSubstr("beta"));
  EXPECT_THAT(c.ToString(), HasSubstr("gamma"));
}

// Copy and move semantics should preserve observable behavior of the status.
TEST_F(StatusNotSupportedTest_18, CopyAndMoveSemantics_18) {
  Status original = Status::NotSupported("copy-move");

  // Copy construct
  Status copied(original);
  EXPECT_TRUE(copied.IsNotSupportedError());
  EXPECT_EQ(copied.ToString(), original.ToString());

  // Copy assign
  Status copy_assigned = Status::OK();
  copy_assigned = original;
  EXPECT_TRUE(copy_assigned.IsNotSupportedError());
  EXPECT_EQ(copy_assigned.ToString(), original.ToString());

  // Move construct
  Status moved_constructed(std::move(original));
  EXPECT_TRUE(moved_constructed.IsNotSupportedError());
  // We do not assert anything about 'original' after move.

  // Move assign
  Status src = Status::NotSupported("move-assign");
  Status moved_assigned = Status::OK();
  moved_assigned = std::move(src);
  EXPECT_TRUE(moved_assigned.IsNotSupportedError());
  // We do not assert anything about 'src' after move.
}

// Large/long message should be observable without assuming formatting or truncation rules.
TEST_F(StatusNotSupportedTest_18, LongMessageContainsDistinctToken_18) {
  std::string long_msg(2048, 'x');
  long_msg.replace(100, 12, "LONG_TOKEN_18");
  Status s = Status::NotSupported(long_msg.c_str());

  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_THAT(s.ToString(), HasSubstr("LONG_TOKEN_18"));
}
