// File: table/new_empty_iterator_test_403.cc

#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

#include <gtest/gtest.h>

namespace {

class EmptyIteratorTest_403 : public ::testing::Test {
protected:
  leveldb::Iterator* Make() {
    // System under test: must return a valid pointer to an Iterator
    return leveldb::NewEmptyIterator();
  }
};

// [Normal] The factory returns a non-null iterator.
TEST_F(EmptyIteratorTest_403, ReturnsNonNull_403) {
  std::unique_ptr<leveldb::Iterator> it(Make());
  ASSERT_NE(it.get(), nullptr);
}

// [Normal] status() is OK for a freshly created empty iterator.
TEST_F(EmptyIteratorTest_403, StatusIsOkByDefault_403) {
  std::unique_ptr<leveldb::Iterator> it(Make());
  ASSERT_TRUE(it->status().ok());
}

// [Boundary] An empty iterator is not valid and remains invalid after navigation.
TEST_F(EmptyIteratorTest_403, InvalidAndStaysInvalidOnNavigation_403) {
  std::unique_ptr<leveldb::Iterator> it(Make());
  // Initial state: not valid
  EXPECT_FALSE(it->Valid());

  // Navigations should not make it valid
  it->Next();
  EXPECT_FALSE(it->Valid());

  it->Prev();
  EXPECT_FALSE(it->Valid());

  // Seeking to first/last should still be invalid for an empty iterator
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());

  it->SeekToLast();
  EXPECT_FALSE(it->Valid());

  // Status should remain OK throughout (no errors reported)
  EXPECT_TRUE(it->status().ok());
}

// [Boundary] Seeking to any key on an empty iterator keeps it invalid and status OK.
TEST_F(EmptyIteratorTest_403, SeekKeepsIteratorInvalid_403) {
  std::unique_ptr<leveldb::Iterator> it(Make());

  it->Seek(leveldb::Slice("any-key"));
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  // Subsequent navigation still leaves it invalid
  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// [Normal] Multiple empty iterators can be created independently; operations on one do not affect the other.
TEST_F(EmptyIteratorTest_403, MultipleIteratorsIndependent_403) {
  std::unique_ptr<leveldb::Iterator> a(Make());
  std::unique_ptr<leveldb::Iterator> b(Make());

  ASSERT_FALSE(a->Valid());
  ASSERT_FALSE(b->Valid());
  ASSERT_TRUE(a->status().ok());
  ASSERT_TRUE(b->status().ok());

  a->SeekToFirst();
  a->Next();
  EXPECT_FALSE(a->Valid());
  EXPECT_FALSE(b->Valid());      // b remains unaffected
  EXPECT_TRUE(a->status().ok());
  EXPECT_TRUE(b->status().ok());
}

// [Exceptional/Robustness] Deleting an empty iterator should be safe (no leaks/crashes).
TEST_F(EmptyIteratorTest_403, DestroyIsSafe_403) {
  leveldb::Iterator* raw = Make();
  ASSERT_NE(raw, nullptr);
  // Intentionally not wrapping in unique_ptr to explicitly test deletion path.
  delete raw;
  SUCCEED(); // If we got here without crashing, destruction was safe.
}

} // namespace
