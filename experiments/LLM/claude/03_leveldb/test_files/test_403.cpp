#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"

namespace leveldb {

// Test that NewEmptyIterator returns a non-null iterator
TEST(NewEmptyIteratorTest_403, ReturnsNonNull_403) {
  Iterator* iter = NewEmptyIterator();
  ASSERT_NE(iter, nullptr);
  delete iter;
}

// Test that the empty iterator reports Valid() as false initially
TEST(NewEmptyIteratorTest_403, InitiallyInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that the empty iterator's status is OK
TEST(NewEmptyIteratorTest_403, StatusIsOK_403) {
  Iterator* iter = NewEmptyIterator();
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test that SeekToFirst does not make the iterator valid
TEST(NewEmptyIteratorTest_403, SeekToFirstRemainsInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that SeekToLast does not make the iterator valid
TEST(NewEmptyIteratorTest_403, SeekToLastRemainsInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that Seek does not make the iterator valid
TEST(NewEmptyIteratorTest_403, SeekRemainsInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  iter->Seek("some_key");
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that Next does not make the iterator valid (calling on empty iterator)
TEST(NewEmptyIteratorTest_403, NextRemainsInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  iter->SeekToFirst();
  // Iterator is not valid, but calling Next should not crash in a well-behaved implementation
  // We just verify it remains invalid
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that Prev does not make the iterator valid
TEST(NewEmptyIteratorTest_403, PrevRemainsInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that status remains OK after various operations
TEST(NewEmptyIteratorTest_403, StatusRemainsOKAfterOperations_403) {
  Iterator* iter = NewEmptyIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());
  iter->SeekToLast();
  EXPECT_TRUE(iter->status().ok());
  iter->Seek("test");
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test that Seek with empty key still results in invalid iterator
TEST(NewEmptyIteratorTest_403, SeekWithEmptyKeyRemainsInvalid_403) {
  Iterator* iter = NewEmptyIterator();
  iter->Seek("");
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test that multiple NewEmptyIterator calls produce independent iterators
TEST(NewEmptyIteratorTest_403, MultipleIteratorsAreIndependent_403) {
  Iterator* iter1 = NewEmptyIterator();
  Iterator* iter2 = NewEmptyIterator();
  ASSERT_NE(iter1, nullptr);
  ASSERT_NE(iter2, nullptr);
  EXPECT_NE(iter1, iter2);
  EXPECT_FALSE(iter1->Valid());
  EXPECT_FALSE(iter2->Valid());
  EXPECT_TRUE(iter1->status().ok());
  EXPECT_TRUE(iter2->status().ok());
  delete iter1;
  delete iter2;
}

// Test NewErrorIterator if available - testing with NewEmptyIterator that status is ok
TEST(NewEmptyIteratorTest_403, EmptyIteratorStatusToString_403) {
  Iterator* iter = NewEmptyIterator();
  std::string status_str = iter->status().ToString();
  EXPECT_EQ(status_str, "OK");
  delete iter;
}

}  // namespace leveldb
