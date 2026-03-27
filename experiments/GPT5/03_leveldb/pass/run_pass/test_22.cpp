// status_is_not_found_test_22.cc
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>

using leveldb::Slice;
using leveldb::Status;

namespace {

TEST(StatusTest_22, NotFoundReturnsTrue_22) {
  Status s = Status::NotFound(Slice("missing"));
  EXPECT_TRUE(s.IsNotFound());
}

TEST(StatusTest_22, OkReturnsFalse_22) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_22, OtherErrorCodesReturnFalse_22) {
  Status c = Status::Corruption(Slice("corr"));
  Status ns = Status::NotSupported(Slice("nsp"));
  Status ia = Status::InvalidArgument(Slice("inv"));
  Status io = Status::IOError(Slice("io"));

  EXPECT_FALSE(c.IsNotFound());
  EXPECT_FALSE(ns.IsNotFound());
  EXPECT_FALSE(ia.IsNotFound());
  EXPECT_FALSE(io.IsNotFound());
}

TEST(StatusTest_22, NotFoundWithTwoMessagesStillIsNotFound_22) {
  Status s = Status::NotFound(Slice("primary"), Slice("secondary"));
  EXPECT_TRUE(s.IsNotFound());
}

TEST(StatusTest_22, CopyPreservesNotFound_22) {
  Status original = Status::NotFound(Slice("x"));
  Status copy = original;  // copy-ctor
  EXPECT_TRUE(copy.IsNotFound());
  // Copy should not change the source’s observable state.
  EXPECT_TRUE(original.IsNotFound());
}

TEST(StatusTest_22, MovePreservesNotFoundInDestination_22) {
  Status original = Status::NotFound(Slice("x"));
  Status moved = std::move(original);  // move-ctor
  EXPECT_TRUE(moved.IsNotFound());
  // Do not assert on 'original' after move; its state is unspecified but valid.
}

TEST(StatusTest_22, DefaultConstructedIsNotNotFound_22) {
  Status s;  // default-constructed
  // We only assert the observable: it should not report NotFound unless created as such.
  EXPECT_FALSE(s.IsNotFound());
}

}  // namespace
