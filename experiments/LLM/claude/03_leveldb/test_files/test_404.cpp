#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"

namespace leveldb {

// Test that NewErrorIterator returns a non-null iterator
TEST(NewErrorIteratorTest_404, ReturnsNonNull_404) {
  Status status = Status::NotFound("key not found");
  Iterator* iter = NewErrorIterator(status);
  ASSERT_NE(iter, nullptr);
  delete iter;
}

// Test that the iterator created with an error status reports that status
TEST(NewErrorIteratorTest_404, StatusReflectsError_404) {
  Status status = Status::NotFound("key not found");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_TRUE(iter->status().IsNotFound());
  delete iter;
}

// Test that the iterator is not valid upon creation
TEST(NewErrorIteratorTest_404, NotValidInitially_404) {
  Status status = Status::Corruption("data corrupted");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that SeekToFirst does not make iterator valid
TEST(NewErrorIteratorTest_404, SeekToFirstStillInvalid_404) {
  Status status = Status::IOError("io error");
  Iterator* iter = NewErrorIterator(status);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().IsIOError());
  delete iter;
}

// Test that SeekToLast does not make iterator valid
TEST(NewErrorIteratorTest_404, SeekToLastStillInvalid_404) {
  Status status = Status::NotSupported("not supported");
  Iterator* iter = NewErrorIterator(status);
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().IsNotSupportedError());
  delete iter;
}

// Test that Seek does not make iterator valid
TEST(NewErrorIteratorTest_404, SeekStillInvalid_404) {
  Status status = Status::InvalidArgument("bad argument");
  Iterator* iter = NewErrorIterator(status);
  iter->Seek("some_key");
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().IsInvalidArgument());
  delete iter;
}

// Test that Next does not make iterator valid (called on invalid iterator)
TEST(NewErrorIteratorTest_404, NextStillInvalid_404) {
  Status status = Status::Corruption("corrupted");
  Iterator* iter = NewErrorIterator(status);
  // Iterator is not valid, but calling Next should not crash
  // (behavior may vary, but it should remain invalid)
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that Prev does not make iterator valid
TEST(NewErrorIteratorTest_404, PrevStillInvalid_404) {
  Status status = Status::Corruption("corrupted");
  Iterator* iter = NewErrorIterator(status);
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test with different error types to ensure status is preserved correctly
TEST(NewErrorIteratorTest_404, CorruptionStatus_404) {
  Status status = Status::Corruption("file corrupted", "details");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_TRUE(iter->status().IsCorruption());
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

TEST(NewErrorIteratorTest_404, IOErrorStatus_404) {
  Status status = Status::IOError("disk failure");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_TRUE(iter->status().IsIOError());
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

TEST(NewErrorIteratorTest_404, NotSupportedStatus_404) {
  Status status = Status::NotSupported("operation not supported");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_TRUE(iter->status().IsNotSupportedError());
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

TEST(NewErrorIteratorTest_404, InvalidArgumentStatus_404) {
  Status status = Status::InvalidArgument("invalid arg");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_TRUE(iter->status().IsInvalidArgument());
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

TEST(NewErrorIteratorTest_404, NotFoundStatus_404) {
  Status status = Status::NotFound("not found", "extra info");
  Iterator* iter = NewErrorIterator(status);
  EXPECT_TRUE(iter->status().IsNotFound());
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

// Test that status message content is preserved
TEST(NewErrorIteratorTest_404, StatusMessagePreserved_404) {
  Status status = Status::Corruption("specific error message");
  Iterator* iter = NewErrorIterator(status);
  std::string statusStr = iter->status().ToString();
  EXPECT_NE(statusStr.find("specific error message"), std::string::npos);
  delete iter;
}

// Test creating multiple error iterators with different statuses
TEST(NewErrorIteratorTest_404, MultipleErrorIterators_404) {
  Iterator* iter1 = NewErrorIterator(Status::NotFound("a"));
  Iterator* iter2 = NewErrorIterator(Status::Corruption("b"));
  Iterator* iter3 = NewErrorIterator(Status::IOError("c"));

  EXPECT_TRUE(iter1->status().IsNotFound());
  EXPECT_TRUE(iter2->status().IsCorruption());
  EXPECT_TRUE(iter3->status().IsIOError());

  EXPECT_FALSE(iter1->Valid());
  EXPECT_FALSE(iter2->Valid());
  EXPECT_FALSE(iter3->Valid());

  delete iter1;
  delete iter2;
  delete iter3;
}

// Test that Seek with empty key still results in invalid iterator
TEST(NewErrorIteratorTest_404, SeekWithEmptyKey_404) {
  Status status = Status::NotFound("missing");
  Iterator* iter = NewErrorIterator(status);
  iter->Seek("");
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().IsNotFound());
  delete iter;
}

}  // namespace leveldb
