// status_ok_tests_21.cc
#include "gtest/gtest.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::Status;

// --- Basic OK semantics ---

TEST(StatusOkTest_21, DefaultConstructed_IsOk_21) {
  Status s;
  EXPECT_TRUE(s.ok());
}

TEST(StatusOkTest_21, StaticOK_IsOk_21) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// --- Error kinds must not be OK ---

TEST(StatusOkTest_21, NotFound_IsNotOk_21) {
  Status s = Status::NotFound(Slice("missing"));
  EXPECT_FALSE(s.ok());
}

TEST(StatusOkTest_21, Corruption_IsNotOk_21) {
  Status s = Status::Corruption(Slice("bad data"));
  EXPECT_FALSE(s.ok());
}

TEST(StatusOkTest_21, NotSupported_IsNotOk_21) {
  Status s = Status::NotSupported(Slice("op"));
  EXPECT_FALSE(s.ok());
}

TEST(StatusOkTest_21, InvalidArgument_IsNotOk_21) {
  Status s = Status::InvalidArgument(Slice("arg"));
  EXPECT_FALSE(s.ok());
}

TEST(StatusOkTest_21, IOError_IsNotOk_21) {
  Status s = Status::IOError(Slice("io"));
  EXPECT_FALSE(s.ok());
}

// --- Message parameters (including second message) do not flip OKness ---

TEST(StatusOkTest_21, ErrorWithTwoMessages_IsNotOk_21) {
  Status s = Status::IOError(Slice("io"), Slice("disk full"));
  EXPECT_FALSE(s.ok());
}

TEST(StatusOkTest_21, ErrorWithEmptyMessages_IsNotOk_21) {
  Status s = Status::InvalidArgument(Slice(), Slice());
  EXPECT_FALSE(s.ok());
}

// --- Copy semantics preserve OKness ---

TEST(StatusOkTest_21, CopyConstruct_OKRemainsOK_21) {
  Status a = Status::OK();
  Status b(a);
  EXPECT_TRUE(b.ok());
  EXPECT_TRUE(a.ok());
}

TEST(StatusOkTest_21, CopyConstruct_ErrorRemainsError_21) {
  Status a = Status::NotFound(Slice("k"));
  Status b(a);
  EXPECT_FALSE(b.ok());
  EXPECT_FALSE(a.ok());
}

TEST(StatusOkTest_21, CopyAssign_PreservesOKness_21) {
  Status src = Status::Corruption(Slice("x"));
  Status dst = Status::OK();
  dst = src;
  EXPECT_FALSE(dst.ok());
  EXPECT_FALSE(src.ok());

  Status src2 = Status::OK();
  dst = src2;
  EXPECT_TRUE(dst.ok());
  EXPECT_TRUE(src2.ok());
}

// --- Move semantics (destination OKness matches source before move) ---

TEST(StatusOkTest_21, MoveConstruct_DestinationMatchesSourceOKness_21) {
  // Error case
  Status err = Status::IOError(Slice("e"));
  bool before = err.ok();
  Status moved_err(std::move(err));
  EXPECT_EQ(moved_err.ok(), before);

  // OK case
  Status ok = Status::OK();
  before = ok.ok();
  Status moved_ok(std::move(ok));
  EXPECT_EQ(moved_ok.ok(), before);
}

TEST(StatusOkTest_21, MoveAssign_DestinationMatchesSourceOKness_21) {
  // Error -> OK
  Status dst = Status::OK();
  Status src = Status::NotFound(Slice("n"));
  bool before = src.ok();
  dst = std::move(src);
  EXPECT_EQ(dst.ok(), before);

  // OK -> Error
  Status dst2 = Status::IOError(Slice("io"));
  Status src2 = Status::OK();
  before = src2.ok();
  dst2 = std::move(src2);
  EXPECT_EQ(dst2.ok(), before);
}

// --- Self-assignment should leave OKness unchanged ---

TEST(StatusOkTest_21, SelfAssign_OKUnchanged_21) {
  Status s = Status::OK();
  s = s;
  EXPECT_TRUE(s.ok());
}

TEST(StatusOkTest_21, SelfAssign_ErrorUnchanged_21) {
  Status s = Status::Corruption(Slice("c"));
  s = s;
  EXPECT_FALSE(s.ok());
}
