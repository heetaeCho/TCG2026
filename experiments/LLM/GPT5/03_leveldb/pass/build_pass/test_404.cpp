// File: table/new_error_iterator_test_404.cc

#include "leveldb/iterator.h"   // Iterator interface + NewErrorIterator declaration
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "gtest/gtest.h"

using leveldb::Iterator;
using leveldb::NewErrorIterator;
using leveldb::Slice;
using leveldb::Status;

class IteratorErrorTest_404 : public ::testing::Test {
protected:
  // Utility to create and own an iterator safely.
  static std::unique_ptr<Iterator> Make(Status s) {
    return std::unique_ptr<Iterator>(NewErrorIterator(s));
  }
};

// Verifies that NewErrorIterator returns an iterator that is invalid and
// surfaces the provided (non-OK) error via status().
TEST_F(IteratorErrorTest_404, ReturnsIteratorWithGivenStatus_404) {
  auto it = Make(Status::IOError("disk failed"));

  // Iterator should be constructed and immediately invalid.
  ASSERT_NE(it, nullptr);
  EXPECT_FALSE(it->Valid());

  // The error should be preserved and recognizable via Status predicates.
  Status st = it->status();
  EXPECT_FALSE(st.ok());
  EXPECT_TRUE(st.IsIOError());
}

// Verifies that seeking and movement operations do not make the iterator valid
// and that the error status remains observable afterwards.
TEST_F(IteratorErrorTest_404, OperationsDoNotBecomeValid_404) {
  auto it = Make(Status::Corruption("bad table"));

  // A sequence of navigation calls should not make it valid.
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().IsCorruption());

  it->SeekToLast();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().IsCorruption());

  it->Seek(Slice("key"));
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().IsCorruption());

  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().IsCorruption());

  it->Prev();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().IsCorruption());
}

// Boundary case: If an OK status is provided, the iterator should still be
// empty/invalid (since it's an "empty" iterator), and status() should report OK.
TEST_F(IteratorErrorTest_404, OkStatusYieldsEmptyButOkIterator_404) {
  auto it = Make(Status::OK());

  ASSERT_NE(it, nullptr);

  // Still represents an empty iterator: not valid at any time.
  EXPECT_FALSE(it->Valid());

  // But since we passed OK, status() should be OK.
  EXPECT_TRUE(it->status().ok());

  // Navigation shouldn't change either property.
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  it->Seek(Slice("anything"));
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}
