// File: status_is_invalid_argument_test_26.cc
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>

using leveldb::Slice;
using leveldb::Status;

class StatusInvalidArgumentTest_26 : public ::testing::Test {};

// Normal operation: factory produces an InvalidArgument status that reports true.
TEST_F(StatusInvalidArgumentTest_26, ReturnsTrueForInvalidArgument_26) {
  Status s = Status::InvalidArgument(Slice("bad arg"), Slice("detail"));
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

// Negative checks: all other well-known statuses report false.
TEST_F(StatusInvalidArgumentTest_26, ReturnsFalseForOtherStatuses_26) {
  Status ok = Status::OK();
  Status nf = Status::NotFound(Slice("missing"), Slice());
  Status co = Status::Corruption(Slice("corr"), Slice("x"));
  Status ns = Status::NotSupported(Slice("noop"), Slice());
  Status io = Status::IOError(Slice("io"), Slice("disk"));

  EXPECT_FALSE(ok.IsInvalidArgument());
  EXPECT_FALSE(nf.IsInvalidArgument());
  EXPECT_FALSE(co.IsInvalidArgument());
  EXPECT_FALSE(ns.IsInvalidArgument());
  EXPECT_FALSE(io.IsInvalidArgument());
}

// Copy construction preserves the observable kind.
TEST_F(StatusInvalidArgumentTest_26, CopyConstructPreservesInvalidArgument_26) {
  Status original = Status::InvalidArgument(Slice("a"), Slice("b"));
  Status copy(original);
  EXPECT_TRUE(copy.IsInvalidArgument());
  EXPECT_FALSE(copy.ok());
}

// Move construction preserves the observable kind in the destination.
TEST_F(StatusInvalidArgumentTest_26, MoveConstructPreservesInvalidArgument_26) {
  Status tmp = Status::InvalidArgument(Slice("m1"), Slice("m2"));
  Status moved(std::move(tmp));
  EXPECT_TRUE(moved.IsInvalidArgument());
  EXPECT_FALSE(moved.ok());
  // No assertions about the moved-from object (contract unspecified).
}

// Copy assignment preserves the observable kind.
TEST_F(StatusInvalidArgumentTest_26, CopyAssignPreservesInvalidArgument_26) {
  Status src = Status::InvalidArgument(Slice("x"), Slice());
  Status dst = Status::OK();
  dst = src;
  EXPECT_TRUE(dst.IsInvalidArgument());
  EXPECT_FALSE(dst.ok());
}

// Move assignment preserves the observable kind in the destination.
TEST_F(StatusInvalidArgumentTest_26, MoveAssignPreservesInvalidArgument_26) {
  Status dst = Status::OK();
  Status src = Status::InvalidArgument(Slice("mv"), Slice("asgn"));
  dst = std::move(src);
  EXPECT_TRUE(dst.IsInvalidArgument());
  EXPECT_FALSE(dst.ok());
  // No assertions about moved-from src.
}

// Self-assignment does not change the observable kind.
TEST_F(StatusInvalidArgumentTest_26, SelfAssignmentSafe_26) {
  Status s = Status::InvalidArgument(Slice("self"), Slice("assign"));
  s = s;  // self-assign
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

// Chained assignment propagates the InvalidArgument kind.
TEST_F(StatusInvalidArgumentTest_26, ChainedAssignmentPropagatesKind_26) {
  Status a = Status::InvalidArgument(Slice("A"), Slice());
  Status b = Status::OK();
  Status c = Status::NotFound(Slice("C"), Slice());
  b = c = a;  // chain
  EXPECT_TRUE(b.IsInvalidArgument());
  EXPECT_TRUE(c.IsInvalidArgument());
  EXPECT_FALSE(b.ok());
  EXPECT_FALSE(c.ok());
}
