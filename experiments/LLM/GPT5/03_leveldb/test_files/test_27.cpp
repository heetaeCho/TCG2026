// File: status_copy_assignment_test_27.cc
#include <gtest/gtest.h>
#include "leveldb/status.h"

using leveldb::Status;

class StatusAssignmentTest_27 : public ::testing::Test {};

// Normal: assign error -> OK
TEST_F(StatusAssignmentTest_27, CopyAssign_FromErrorToOK_27) {
  Status lhs = Status::OK();
  Status rhs = Status::NotFound("missing");

  lhs = rhs;

  EXPECT_TRUE(lhs.IsNotFound());
  EXPECT_FALSE(lhs.ok());
  EXPECT_EQ(lhs.ToString(), rhs.ToString());

  // Deep copy check: changing rhs afterwards doesn't affect lhs
  rhs = Status::Corruption("other");
  EXPECT_TRUE(lhs.IsNotFound());
  EXPECT_NE(lhs.ToString(), rhs.ToString());
}

// Normal: assign OK -> error (should become OK)
TEST_F(StatusAssignmentTest_27, CopyAssign_FromOKToError_27) {
  Status lhs = Status::NotFound("x");
  Status rhs = Status::OK();

  lhs = rhs;

  EXPECT_TRUE(lhs.ok());
  EXPECT_FALSE(lhs.IsNotFound());
  EXPECT_EQ(lhs.ToString(), rhs.ToString());
}

// Boundary: self-assignment when OK
TEST_F(StatusAssignmentTest_27, CopyAssign_SelfAssignment_OK_27) {
  Status s = Status::OK();
  std::string before = s.ToString();

  s = s;  // self-assign should be safe and no-op (observable)

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(s.ToString(), before);
}

// Boundary: self-assignment when error
TEST_F(StatusAssignmentTest_27, CopyAssign_SelfAssignment_Error_27) {
  Status s = Status::InvalidArgument("bad arg");
  std::string before = s.ToString();

  s = s;  // self-assign

  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_EQ(s.ToString(), before);
}

// Overwrite with a different error kind
TEST_F(StatusAssignmentTest_27, CopyAssign_OverwriteDifferentError_27) {
  Status lhs = Status::Corruption("a");
  Status rhs = Status::IOError("b");

  lhs = rhs;

  EXPECT_TRUE(lhs.IsIOError());
  EXPECT_FALSE(lhs.IsCorruption());
  EXPECT_EQ(lhs.ToString(), rhs.ToString());
}

// Chained assignment should make left operands equal to the right-most value
TEST_F(StatusAssignmentTest_27, CopyAssign_ChainedAssignment_27) {
  Status a = Status::OK();
  Status b = Status::NotSupported("ns");
  Status c = Status::InvalidArgument("iv");

  a = b = c;  // right-to-left: b=c; a=b;

  EXPECT_TRUE(a.IsInvalidArgument());
  EXPECT_TRUE(b.IsInvalidArgument());
  EXPECT_TRUE(c.IsInvalidArgument());
  EXPECT_EQ(a.ToString(), b.ToString());
  EXPECT_EQ(b.ToString(), c.ToString());
}

// OK -> OK (null-to-null) remains OK
TEST_F(StatusAssignmentTest_27, CopyAssign_OKToOK_27) {
  Status lhs = Status::OK();
  Status rhs = Status::OK();

  lhs = rhs;

  EXPECT_TRUE(lhs.ok());
  EXPECT_EQ(lhs.ToString(), rhs.ToString());
}
