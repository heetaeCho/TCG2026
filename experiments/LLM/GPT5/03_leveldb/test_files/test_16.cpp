// status_notfound_test_16.cc
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>

using leveldb::Slice;
using leveldb::Status;

class StatusTest_16 : public ::testing::Test {};

// Verifies that Status::NotFound produces a non-OK status flagged as "not found".
TEST_F(StatusTest_16, NotFound_SetsIsNotFoundAndNotOk_16) {
  Status s = Status::NotFound(Slice("missing"));
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Verifies ToString() includes the category indicator and both messages (when provided).
TEST_F(StatusTest_16, NotFound_ToStringContainsMessages_OneAndTwo_16) {
  Status s1 = Status::NotFound(Slice("user.db"), Slice("key=42"));
  std::string str1 = s1.ToString();

  // Don't assert exact formatting; only observable substrings.
  EXPECT_NE(std::string::npos, str1.find("NotFound")) << str1;
  EXPECT_NE(std::string::npos, str1.find("user.db")) << str1;
  EXPECT_NE(std::string::npos, str1.find("key=42")) << str1;

  Status s2 = Status::NotFound(Slice("only-one"));
  std::string str2 = s2.ToString();

  EXPECT_NE(std::string::npos, str2.find("NotFound")) << str2;
  EXPECT_NE(std::string::npos, str2.find("only-one")) << str2;
}

// Boundary: empty messages still yield a NotFound status; formatting is not assumed.
TEST_F(StatusTest_16, NotFound_EmptyMessages_StillNotFound_16) {
  Status s = Status::NotFound(Slice(""), Slice(""));
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());

  std::string str = s.ToString();
  // At minimum, the category should be present.
  EXPECT_NE(std::string::npos, str.find("NotFound")) << str;
}

// Copy & move should preserve the observable state (category and messages presence).
TEST_F(StatusTest_16, NotFound_CopyAndMove_PreserveState_16) {
  Status original = Status::NotFound(Slice("file.txt"), Slice("id=7"));
  ASSERT_TRUE(original.IsNotFound());
  const std::string orig_str = original.ToString();

  // Copy construction
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_EQ(orig_str, copy.ToString());

  // Copy assignment
  Status copy_asg;
  copy_asg = original;
  EXPECT_TRUE(copy_asg.IsNotFound());
  EXPECT_EQ(orig_str, copy_asg.ToString());

  // Move construction
  Status move_constructed(std::move(copy));
  EXPECT_TRUE(move_constructed.IsNotFound());
  EXPECT_EQ(orig_str, move_constructed.ToString());

  // Move assignment
  Status move_assigned;
  move_assigned = Status::NotFound(Slice("tmp"), Slice("x"));
  move_assigned = std::move(copy_asg);
  EXPECT_TRUE(move_assigned.IsNotFound());
  EXPECT_EQ(orig_str, move_assigned.ToString());
}

// Defaulted second argument should behave like explicitly passing an empty Slice.
TEST_F(StatusTest_16, NotFound_DefaultSecondArgEquivalentToExplicitEmpty_16) {
  Status a = Status::NotFound(Slice("alpha"));
  Status b = Status::NotFound(Slice("alpha"), Slice());

  EXPECT_TRUE(a.IsNotFound());
  EXPECT_TRUE(b.IsNotFound());
  EXPECT_EQ(a.ToString(), b.ToString());
}

// Sanity: NotFound does not alter independently-created OK status.
TEST_F(StatusTest_16, NotFound_DoesNotAffectOtherStatuses_16) {
  Status ok = Status::OK();
  EXPECT_TRUE(ok.ok());
  EXPECT_FALSE(ok.IsNotFound());

  Status nf = Status::NotFound(Slice("x"));
  EXPECT_TRUE(nf.IsNotFound());
  EXPECT_FALSE(nf.ok());

  // Ensure the OK status remains OK after creating another status.
  EXPECT_TRUE(ok.ok());
  EXPECT_FALSE(ok.IsNotFound());
}
