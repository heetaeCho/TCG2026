// status_io_error_test_20.cc
#include <gtest/gtest.h>
#include "leveldb/status.h"
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::Status;

class StatusIOErrorTest_20 : public ::testing::Test {};

// 1) Normal operation: creating an IOError returns a non-OK status reporting IO error.
TEST_F(StatusIOErrorTest_20, IOError_BasicProperties_20) {
  Status s = Status::IOError(Slice("disk full"));
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());

  // ToString should be a non-empty description for an error.
  std::string msg = s.ToString();
  EXPECT_FALSE(msg.empty());
  // The message should include the provided text (observable via ToString()).
  EXPECT_NE(msg.find("disk full"), std::string::npos);
}

// 2) Normal operation: second message is incorporated (observable via ToString()).
TEST_F(StatusIOErrorTest_20, IOError_WithTwoMessages_ToStringContainsBoth_20) {
  Status s = Status::IOError(Slice("open"), Slice("permission denied"));
  std::string msg = s.ToString();
  EXPECT_FALSE(msg.empty());
  EXPECT_NE(msg.find("open"), std::string::npos);
  EXPECT_NE(msg.find("permission denied"), std::string::npos);
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

// 3) Copy semantics: copying preserves the observable error category and message.
TEST_F(StatusIOErrorTest_20, IOError_CopyCtorAndAssign_PreservesCodeAndMessage_20) {
  Status original = Status::IOError(Slice("read"), Slice("I/O timeout"));
  std::string original_str = original.ToString();

  // Copy constructor
  Status copy_constructed(original);
  EXPECT_TRUE(copy_constructed.IsIOError());
  EXPECT_FALSE(copy_constructed.ok());
  EXPECT_EQ(copy_constructed.ToString(), original_str);

  // Copy assignment
  Status copy_assigned;
  copy_assigned = original;
  EXPECT_TRUE(copy_assigned.IsIOError());
  EXPECT_FALSE(copy_assigned.ok());
  EXPECT_EQ(copy_assigned.ToString(), original_str);
}

// 4) Move semantics: moving preserves the observable error category in the destination.
TEST_F(StatusIOErrorTest_20, IOError_MoveCtorAndAssign_PreservesCategory_20) {
  Status src1 = Status::IOError(Slice("flush"), Slice("device busy"));
  Status moved_ctor(std::move(src1));
  EXPECT_TRUE(moved_ctor.IsIOError());
  EXPECT_FALSE(moved_ctor.ok());
  // (No assumptions about moved-from state.)

  Status src2 = Status::IOError(Slice("sync"), Slice("broken pipe"));
  Status moved_assign;
  moved_assign = std::move(src2);
  EXPECT_TRUE(moved_assign.IsIOError());
  EXPECT_FALSE(moved_assign.ok());
  // (No assumptions about moved-from state.)
}

// 5) Error typing: IOError should not report any other error types.
TEST_F(StatusIOErrorTest_20, IOError_DoesNotReportOtherErrorTypes_20) {
  Status s = Status::IOError(Slice("x"));
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}
