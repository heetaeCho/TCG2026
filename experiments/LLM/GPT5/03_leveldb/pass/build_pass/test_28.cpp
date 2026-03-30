// File: status_move_assignment_test_28.cc
#include "leveldb/status.h"
#include <gtest/gtest.h>
#include <utility>
#include <string>

using leveldb::Status;

class StatusMoveAssignTest_28 : public ::testing::Test {};

// Normal: move-assign from NotFound into OK transfers the "NotFound" state and message.
// Also verifies rhs now has the lhs's previous state (OK), per the provided swap-based implementation.
TEST_F(StatusMoveAssignTest_28, MoveFromNotFoundIntoOK_SwapsStates_28) {
  Status src = Status::NotFound("missing-key");
  Status dst = Status::OK();

  dst = std::move(src);

  EXPECT_TRUE(dst.IsNotFound());
  std::string moved_str = dst.ToString();
  EXPECT_NE(moved_str.find("missing-key"), std::string::npos);

  // rhs should now be OK because lhs was OK before the move (swap behavior).
  EXPECT_TRUE(src.ok());
}

// Boundary: self move-assignment should leave the object unchanged and valid.
TEST_F(StatusMoveAssignTest_28, SelfMoveAssignment_NoChange_28) {
  Status s = Status::NotSupported("feature-x");
  std::string before = s.ToString();

  s = std::move(s);

  EXPECT_TRUE(s.IsNotSupportedError());
  std::string after = s.ToString();
  EXPECT_EQ(before, after);
}

// Normal: move-assign from temporary rvalue updates the destination to the new status kind and message.
TEST_F(StatusMoveAssignTest_28, MoveFromTemporary_Rvalue_28) {
  Status s = Status::OK();

  s = Status::InvalidArgument("bad-arg");

  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_NE(s.ToString().find("bad-arg"), std::string::npos);
}

// Interaction: move-assign between two different non-OK statuses swaps their kinds and messages.
TEST_F(StatusMoveAssignTest_28, SwapBetweenDifferentErrorKinds_28) {
  Status a = Status::Corruption("c1");
  Status b = Status::IOError("io1");

  std::string a_before = a.ToString();
  std::string b_before = b.ToString();

  a = std::move(b);

  // 'a' should now reflect former 'b'
  EXPECT_TRUE(a.IsIOError());
  EXPECT_NE(a.ToString().find("io1"), std::string::npos);

  // 'b' should now reflect former 'a'
  EXPECT_TRUE(b.IsCorruption());
  EXPECT_NE(b.ToString().find("c1"), std::string::npos);

  // Sanity: strings actually changed sides
  EXPECT_NE(a.ToString(), a_before);
  EXPECT_NE(b.ToString(), b_before);
}

// Boundary: messages composed of (msg, msg2) are preserved when moved.
TEST_F(StatusMoveAssignTest_28, PreservesBothMessagesOnMove_28) {
  Status with_two_msgs = Status::NotFound("primary", "secondary");
  Status target = Status::OK();

  target = std::move(with_two_msgs);

  EXPECT_TRUE(target.IsNotFound());
  std::string s = target.ToString();
  EXPECT_NE(s.find("primary"), std::string::npos);
  EXPECT_NE(s.find("secondary"), std::string::npos);

  // Source becomes OK after swap with an originally-OK target.
  EXPECT_TRUE(with_two_msgs.ok());
}
