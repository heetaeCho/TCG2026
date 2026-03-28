// status_is_io_error_test_24.cc
#include "leveldb/status.h"
#include <gtest/gtest.h>

using leveldb::Status;

// Suite focuses solely on observable behavior of IsIOError().
class StatusIsIOErrorTest_24 : public ::testing::Test {};

// Normal operation: factory creates an IOError status that reports true.
TEST_F(StatusIsIOErrorTest_24, ReturnsTrueForIOError_24) {
  Status s = Status::IOError("disk", "full");
  EXPECT_TRUE(s.IsIOError());
}

// Normal operation: non-IOError statuses report false.
TEST_F(StatusIsIOErrorTest_24, ReturnsFalseForOK_24) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusIsIOErrorTest_24, ReturnsFalseForNotFound_24) {
  Status s = Status::NotFound("missing", "file");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusIsIOErrorTest_24, ReturnsFalseForCorruption_24) {
  Status s = Status::Corruption("bad", "checksum");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusIsIOErrorTest_24, ReturnsFalseForNotSupported_24) {
  Status s = Status::NotSupported("feature");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusIsIOErrorTest_24, ReturnsFalseForInvalidArgument_24) {
  Status s = Status::InvalidArgument("arg");
  EXPECT_FALSE(s.IsIOError());
}

// Boundary/copy semantics: copying preserves the observable IsIOError state.
TEST_F(StatusIsIOErrorTest_24, CopyConstructorPreservesIOError_24) {
  Status original = Status::IOError("io", "err");
  Status copy(original);
  EXPECT_TRUE(copy.IsIOError());
}

// Boundary/move semantics: moving preserves the observable IsIOError state
// of the destination (no assertions on moved-from object).
TEST_F(StatusIsIOErrorTest_24, MoveConstructorPreservesIOError_24) {
  Status original = Status::IOError("moving");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
}

// Assignment preserves/updates the observable IsIOError state.
TEST_F(StatusIsIOErrorTest_24, CopyAssignmentPreservesIOError_24) {
  Status src = Status::IOError("net");
  Status dst = Status::OK();
  dst = src;
  EXPECT_TRUE(dst.IsIOError());
}

TEST_F(StatusIsIOErrorTest_24, MoveAssignmentPreservesIOError_24) {
  Status dst = Status::OK();
  Status tmp = Status::IOError("tmp");
  dst = std::move(tmp);
  EXPECT_TRUE(dst.IsIOError());
}

// State transition: assigning a non-IOError status makes IsIOError() false.
TEST_F(StatusIsIOErrorTest_24, ReassignFromIOErrorToOK_UpdatesToFalse_24) {
  Status s = Status::IOError("before");
  s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}
