// status_invalid_argument_test_19.cc
#include <gtest/gtest.h>
#include "leveldb/status.h"
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::Status;

class StatusInvalidArgumentTest_19 : public ::testing::Test {};

// Normal operation: single message
TEST_F(StatusInvalidArgumentTest_19, SetsCodeAndNotOk_19) {
  Status s = Status::InvalidArgument(Slice("bad input"));
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

// Normal operation: two messages should appear in ToString (observable text)
TEST_F(StatusInvalidArgumentTest_19, ToStringContainsBothMessages_19) {
  const char* m1 = "arg1";
  const char* m2 = "is invalid";
  Status s = Status::InvalidArgument(Slice(m1), Slice(m2));
  std::string str = s.ToString();
  // We don't assert exact formatting—only presence of provided messages.
  EXPECT_NE(std::string::npos, str.find(m1));
  EXPECT_NE(std::string::npos, str.find(m2));
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

// Boundary: empty messages should still produce a non-OK InvalidArgument status
TEST_F(StatusInvalidArgumentTest_19, EmptyMessagesStillInvalidArgument_19) {
  Status s = Status::InvalidArgument(Slice(), Slice());
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
  // ToString should be non-empty to be informative (observable behavior).
  EXPECT_FALSE(s.ToString().empty());
}

// Copy construction preserves observable behavior
TEST_F(StatusInvalidArgumentTest_19, CopyConstructorPreservesState_19) {
  Status original = Status::InvalidArgument(Slice("copy-me"));
  Status copy(original);
  EXPECT_TRUE(copy.IsInvalidArgument());
  EXPECT_FALSE(copy.ok());
  std::string str = copy.ToString();
  EXPECT_NE(std::string::npos, str.find("copy-me"));
}

// Move construction preserves observable behavior of the moved-to object
TEST_F(StatusInvalidArgumentTest_19, MoveConstructorPreservesState_19) {
  Status original = Status::InvalidArgument(Slice("move-me"));
  Status moved_to(std::move(original));
  EXPECT_TRUE(moved_to.IsInvalidArgument());
  EXPECT_FALSE(moved_to.ok());
  EXPECT_NE(std::string::npos, moved_to.ToString().find("move-me"));
  // No assumptions about moved-from object's internal state.
}

// Copy assignment preserves observable behavior
TEST_F(StatusInvalidArgumentTest_19, CopyAssignmentPreservesState_19) {
  Status src = Status::InvalidArgument(Slice("assign-copy"));
  Status dst = Status::OK();
  dst = src;
  EXPECT_TRUE(dst.IsInvalidArgument());
  EXPECT_FALSE(dst.ok());
  EXPECT_NE(std::string::npos, dst.ToString().find("assign-copy"));
}

// Move assignment preserves observable behavior of the target
TEST_F(StatusInvalidArgumentTest_19, MoveAssignmentPreservesState_19) {
  Status src = Status::InvalidArgument(Slice("assign-move"));
  Status dst = Status::OK();
  dst = std::move(src);
  EXPECT_TRUE(dst.IsInvalidArgument());
  EXPECT_FALSE(dst.ok());
  EXPECT_NE(std::string::npos, dst.ToString().find("assign-move"));
  // No assertions about src after move.
}

// Cross-check against another error kind to verify predicate isolation
TEST_F(StatusInvalidArgumentTest_19, PredicatesAreIsolatedFromOtherErrors_19) {
  Status invalid = Status::InvalidArgument(Slice("x"));
  EXPECT_TRUE(invalid.IsInvalidArgument());
  EXPECT_FALSE(invalid.IsNotFound());
  EXPECT_FALSE(invalid.IsCorruption());
  EXPECT_FALSE(invalid.IsIOError());
  EXPECT_FALSE(invalid.IsNotSupportedError());
}
