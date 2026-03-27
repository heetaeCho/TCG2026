// status_is_not_supported_error_test.cc
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>

using leveldb::Slice;
using leveldb::Status;

//
// Normal operation
//

// Returns true only for a NotSupported status (single message).
TEST(Status_IsNotSupportedError_25, ReturnsTrueForNotSupportedSingleMsg_25) {
  Status s = Status::NotSupported(Slice("feature X not supported"));
  EXPECT_TRUE(s.IsNotSupportedError());
}

// Returns true for a NotSupported status constructed with two messages.
TEST(Status_IsNotSupportedError_25, ReturnsTrueForNotSupportedTwoMsgs_25) {
  Status s = Status::NotSupported(Slice("opY"), Slice("requires Z"));
  EXPECT_TRUE(s.IsNotSupportedError());
}

// Returns false for OK.
TEST(Status_IsNotSupportedError_25, ReturnsFalseForOK_25) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotSupportedError());
}

// Returns false for other error types.
TEST(Status_IsNotSupportedError_25, ReturnsFalseForOtherErrors_25) {
  Status nf = Status::NotFound(Slice("k"), Slice("v"));
  Status cor = Status::Corruption(Slice("bad"), Slice("format"));
  Status ia = Status::InvalidArgument(Slice("arg"), Slice("invalid"));
  Status io = Status::IOError(Slice("path"), Slice("perm"));

  EXPECT_FALSE(nf.IsNotSupportedError());
  EXPECT_FALSE(cor.IsNotSupportedError());
  EXPECT_FALSE(ia.IsNotSupportedError());
  EXPECT_FALSE(io.IsNotSupportedError());
}

//
// Boundary conditions
//

// Default-constructed Status should not report NotSupported.
TEST(Status_IsNotSupportedError_25, DefaultConstructedIsNotNotSupported_25) {
  Status s;  // Treat as black box; only check observable behavior.
  EXPECT_FALSE(s.IsNotSupportedError());
}

// NotSupported created with empty messages is still NotSupported.
TEST(Status_IsNotSupportedError_25, EmptyMessagesStillNotSupported_25) {
  Status s = Status::NotSupported(Slice(), Slice());
  EXPECT_TRUE(s.IsNotSupportedError());
}

//
// Copy/Move semantics (external interactions)
//

// Copying a NotSupported status preserves IsNotSupportedError.
TEST(Status_IsNotSupportedError_25, CopyPreservesNotSupported_25) {
  Status original = Status::NotSupported(Slice("copy me"));
  Status copy = original;  // Uses copy constructor
  EXPECT_TRUE(original.IsNotSupportedError());
  EXPECT_TRUE(copy.IsNotSupportedError());
}

// Moving a NotSupported status preserves IsNotSupportedError on the destination.
// The source's exact state is not specified/relied on; only check destination.
TEST(Status_IsNotSupportedError_25, MovePreservesNotSupportedOnDest_25) {
  Status src = Status::NotSupported(Slice("move me"));
  Status dest = std::move(src);  // Uses move constructor
  EXPECT_TRUE(dest.IsNotSupportedError());
}

// Assigning (copy) preserves NotSupported on the target.
TEST(Status_IsNotSupportedError_25, CopyAssignmentPreservesNotSupported_25) {
  Status a = Status::OK();
  Status b = Status::NotSupported(Slice("assign"));
  a = b;  // copy assignment
  EXPECT_TRUE(a.IsNotSupportedError());
  EXPECT_TRUE(b.IsNotSupportedError());
}

// Assigning (move) preserves NotSupported on the target.
TEST(Status_IsNotSupportedError_25, MoveAssignmentPreservesNotSupported_25) {
  Status a = Status::OK();
  Status b = Status::NotSupported(Slice("move-assign"));
  a = std::move(b);  // move assignment
  EXPECT_TRUE(a.IsNotSupportedError());
  // We do not assert anything about 'b' after move (black-box behavior).
}
