// File: status_is_corruption_test_23.cc

#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>

using leveldb::Slice;
using leveldb::Status;

// Basic truthiness for a corruption status
TEST(StatusTest_23, IsCorruption_ReturnsTrueForCorruption_23) {
  Status s = Status::Corruption(Slice("bad"), Slice("data"));
  EXPECT_TRUE(s.IsCorruption());
}

// OK status should not be flagged as corruption
TEST(StatusTest_23, IsCorruption_ReturnsFalseForOK_23) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsCorruption());
}

// Default-constructed status should behave like OK (not corruption)
TEST(StatusTest_23, IsCorruption_FalseForDefaultConstructed_23) {
  Status s; // relies only on public default ctor behavior
  EXPECT_FALSE(s.IsCorruption());
}

// Other non-corruption error kinds should not be flagged as corruption
TEST(StatusTest_23, IsCorruption_FalseForOtherErrorCodes_23) {
  Status nf  = Status::NotFound(Slice("missing"));
  Status ns  = Status::NotSupported(Slice("op"));
  Status ia  = Status::InvalidArgument(Slice("arg"));
  Status io  = Status::IOError(Slice("io"));

  EXPECT_FALSE(nf.IsCorruption());
  EXPECT_FALSE(ns.IsCorruption());
  EXPECT_FALSE(ia.IsCorruption());
  EXPECT_FALSE(io.IsCorruption());
}

// Copying a corruption status preserves observable behavior
TEST(StatusTest_23, IsCorruption_PreservedAfterCopy_23) {
  Status original = Status::Corruption(Slice("bad"));
  Status copy = original;            // copy-construct
  EXPECT_TRUE(original.IsCorruption());
  EXPECT_TRUE(copy.IsCorruption());

  Status assigned = Status::OK();
  assigned = original;               // copy-assign
  EXPECT_TRUE(assigned.IsCorruption());
}

// Moving a corruption status preserves observable behavior of the target
TEST(StatusTest_23, IsCorruption_PreservedAfterMove_23) {
  Status src = Status::Corruption(Slice("bad"));
  Status moved = std::move(src);     // move-construct
  EXPECT_TRUE(moved.IsCorruption());

  Status dst = Status::OK();
  Status src2 = Status::Corruption(Slice("worse"));
  dst = std::move(src2);             // move-assign
  EXPECT_TRUE(dst.IsCorruption());
  // No assertions about moved-from objects' state (not part of the interface)
}
