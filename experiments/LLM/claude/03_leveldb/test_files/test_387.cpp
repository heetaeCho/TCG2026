#include "gtest/gtest.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "table/merger.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

// Forward declaration
Iterator* NewMergingIterator(const Comparator* comparator, Iterator** children, int n);

namespace {

// A simple in-memory iterator for testing purposes
class TestIterator : public Iterator {
 public:
  TestIterator(const std::vector<std::pair<std::string, std::string>>& data)
      : data_(data), index_(-1) {}

  ~TestIterator() override = default;

  bool Valid() const override {
    return index_ >= 0 && index_ < static_cast<int>(data_.size());
  }

  void SeekToFirst() override {
    index_ = data_.empty() ? -1 : 0;
  }

  void SeekToLast() override {
    index_ = data_.empty() ? -1 : static_cast<int>(data_.size()) - 1;
  }

  void Seek(const Slice& target) override {
    index_ = static_cast<int>(data_.size());  // invalid by default
    for (int i = 0; i < static_cast<int>(data_.size()); i++) {
      if (data_[i].first >= target.ToString()) {
        index_ = i;
        break;
      }
    }
  }

  void Next() override {
    assert(Valid());
    index_++;
  }

  void Prev() override {
    assert(Valid());
    index_--;
  }

  Slice key() const override {
    assert(Valid());
    return Slice(data_[index_].first);
  }

  Slice value() const override {
    assert(Valid());
    return Slice(data_[index_].second);
  }

  Status status() const override { return Status::OK(); }

 private:
  std::vector<std::pair<std::string, std::string>> data_;
  int index_;
};

// An iterator that returns a non-OK status
class ErrorIterator : public Iterator {
 public:
  ErrorIterator(Status s) : status_(s) {}
  ~ErrorIterator() override = default;

  bool Valid() const override { return false; }
  void SeekToFirst() override {}
  void SeekToLast() override {}
  void Seek(const Slice& target) override {}
  void Next() override {}
  void Prev() override {}
  Slice key() const override { return Slice(); }
  Slice value() const override { return Slice(); }
  Status status() const override { return status_; }

 private:
  Status status_;
};

class BytewiseComparatorImpl : public Comparator {
 public:
  const char* Name() const override { return "leveldb.BytewiseComparator"; }

  int Compare(const Slice& a, const Slice& b) const override {
    return a.compare(b);
  }

  void FindShortestSeparator(std::string* start,
                              const Slice& limit) const override {}
  void FindShortSuccessor(std::string* key) const override {}
};

}  // anonymous namespace

class MergingIteratorTest_387 : public ::testing::Test {
 protected:
  BytewiseComparatorImpl cmp_;
};

// Test that n=0 returns an empty iterator
TEST_F(MergingIteratorTest_387, ZeroChildrenReturnsEmptyIterator_387) {
  Iterator* iter = NewMergingIterator(&cmp_, nullptr, 0);
  ASSERT_TRUE(iter != nullptr);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test that n=1 returns the single child directly
TEST_F(MergingIteratorTest_387, SingleChildReturnsSameIterator_387) {
  std::vector<std::pair<std::string, std::string>> data = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  Iterator* child = new TestIterator(data);
  Iterator* iter = NewMergingIterator(&cmp_, &child, 1);
  // When n==1, the returned iterator should be the child itself
  EXPECT_EQ(iter, child);
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");
  EXPECT_EQ(iter->value().ToString(), "1");
  delete iter;
}

// Test merging two sorted iterators, forward iteration
TEST_F(MergingIteratorTest_387, TwoChildrenForwardIteration_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"c", "3"}, {"e", "5"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}, {"f", "6"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();

  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Next();
  }
  EXPECT_TRUE(iter->status().ok());
  ASSERT_EQ(keys.size(), 6u);
  EXPECT_EQ(keys[0], "a");
  EXPECT_EQ(keys[1], "b");
  EXPECT_EQ(keys[2], "c");
  EXPECT_EQ(keys[3], "d");
  EXPECT_EQ(keys[4], "e");
  EXPECT_EQ(keys[5], "f");

  delete iter;
}

// Test merging two sorted iterators, reverse iteration
TEST_F(MergingIteratorTest_387, TwoChildrenReverseIteration_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"c", "3"}, {"e", "5"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}, {"f", "6"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToLast();

  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Prev();
  }
  EXPECT_TRUE(iter->status().ok());
  ASSERT_EQ(keys.size(), 6u);
  EXPECT_EQ(keys[0], "f");
  EXPECT_EQ(keys[1], "e");
  EXPECT_EQ(keys[2], "d");
  EXPECT_EQ(keys[3], "c");
  EXPECT_EQ(keys[4], "b");
  EXPECT_EQ(keys[5], "a");

  delete iter;
}

// Test Seek on a merged iterator
TEST_F(MergingIteratorTest_387, SeekOnMergedIterator_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"c", "3"}, {"e", "5"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}, {"f", "6"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->Seek("c");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "d");

  delete iter;
}

// Test Seek to a key that doesn't exist (lands on next key)
TEST_F(MergingIteratorTest_387, SeekToNonExistentKey_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"c", "3"}, {"e", "5"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}, {"f", "6"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->Seek("cc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "d");

  delete iter;
}

// Test Seek past all keys
TEST_F(MergingIteratorTest_387, SeekPastEnd_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"c", "3"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->Seek("z");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test merging with empty children
TEST_F(MergingIteratorTest_387, MergeWithEmptyChildren_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();

  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Next();
  }
  ASSERT_EQ(keys.size(), 2u);
  EXPECT_EQ(keys[0], "b");
  EXPECT_EQ(keys[1], "d");

  delete iter;
}

// Test merging all empty children
TEST_F(MergingIteratorTest_387, MergeAllEmptyChildren_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {};
  std::vector<std::pair<std::string, std::string>> data2 = {};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test merging with duplicate keys across children
TEST_F(MergingIteratorTest_387, DuplicateKeysAcrossChildren_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"b", "2"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"a", "10"}, {"b", "20"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();

  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Next();
  }
  // Should see all 4 entries (duplicates are not merged)
  ASSERT_EQ(keys.size(), 4u);
  EXPECT_EQ(keys[0], "a");
  EXPECT_EQ(keys[1], "a");
  EXPECT_EQ(keys[2], "b");
  EXPECT_EQ(keys[3], "b");

  delete iter;
}

// Test merging with three children
TEST_F(MergingIteratorTest_387, ThreeChildrenForwardIteration_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"d", "4"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"e", "5"}};
  std::vector<std::pair<std::string, std::string>> data3 = {
      {"c", "3"}, {"f", "6"}};

  Iterator* children[3];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);
  children[2] = new TestIterator(data3);

  Iterator* iter = NewMergingIterator(&cmp_, children, 3);
  iter->SeekToFirst();

  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Next();
  }
  ASSERT_EQ(keys.size(), 6u);
  EXPECT_EQ(keys[0], "a");
  EXPECT_EQ(keys[1], "b");
  EXPECT_EQ(keys[2], "c");
  EXPECT_EQ(keys[3], "d");
  EXPECT_EQ(keys[4], "e");
  EXPECT_EQ(keys[5], "f");

  delete iter;
}

// Test empty iterator from n=0 is not valid after SeekToLast
TEST_F(MergingIteratorTest_387, EmptyIteratorSeekToLast_387) {
  Iterator* iter = NewMergingIterator(&cmp_, nullptr, 0);
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test values are correctly returned through merged iterator
TEST_F(MergingIteratorTest_387, ValuesAreCorrect_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "val_a"}, {"c", "val_c"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "val_b"}, {"d", "val_d"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();

  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");
  EXPECT_EQ(iter->value().ToString(), "val_a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");
  EXPECT_EQ(iter->value().ToString(), "val_b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");
  EXPECT_EQ(iter->value().ToString(), "val_c");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "d");
  EXPECT_EQ(iter->value().ToString(), "val_d");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test forward then backward direction switching
TEST_F(MergingIteratorTest_387, DirectionSwitchForwardToReverse_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {
      {"a", "1"}, {"c", "3"}, {"e", "5"}};
  std::vector<std::pair<std::string, std::string>> data2 = {
      {"b", "2"}, {"d", "4"}, {"f", "6"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  // Now switch direction
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  delete iter;
}

// Test status is OK when all children are OK
TEST_F(MergingIteratorTest_387, StatusOKWhenAllChildrenOK_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {{"a", "1"}};
  std::vector<std::pair<std::string, std::string>> data2 = {{"b", "2"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());

  // Iterate through all
  while (iter->Valid()) {
    iter->Next();
  }
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test with one child having error status
TEST_F(MergingIteratorTest_387, ErrorStatusPropagated_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {{"a", "1"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new ErrorIterator(Status::Corruption("test error"));

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();

  // After iterating, the error status should be visible
  while (iter->Valid()) {
    iter->Next();
  }
  EXPECT_FALSE(iter->status().ok());

  delete iter;
}

// Test single entry per child
TEST_F(MergingIteratorTest_387, SingleEntryPerChild_387) {
  std::vector<std::pair<std::string, std::string>> data1 = {{"z", "26"}};
  std::vector<std::pair<std::string, std::string>> data2 = {{"a", "1"}};

  Iterator* children[2];
  children[0] = new TestIterator(data1);
  children[1] = new TestIterator(data2);

  Iterator* iter = NewMergingIterator(&cmp_, children, 2);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "z");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

}  // namespace leveldb
