#include "gtest/gtest.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

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
    if (index_ >= static_cast<int>(data_.size())) {
      index_ = -1;  // mark invalid
    }
  }

  void Next() override {
    assert(Valid());
    index_++;
    if (index_ >= static_cast<int>(data_.size())) {
      index_ = -1;  // mark invalid
    }
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

  Status status() const override { return status_; }

  void SetStatus(const Status& s) { status_ = s; }

 private:
  std::vector<std::pair<std::string, std::string>> data_;
  int index_;
  Status status_;
};

class IteratorWrapperTest_379 : public ::testing::Test {
 protected:
  std::vector<std::pair<std::string, std::string>> MakeSampleData() {
    return {{"apple", "red"}, {"banana", "yellow"}, {"cherry", "dark_red"},
            {"date", "brown"}, {"elderberry", "purple"}};
  }
};

TEST_F(IteratorWrapperTest_379, DefaultConstructorIsInvalid_379) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_379, ConstructorWithNullIterator_379) {
  IteratorWrapper wrapper(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_379, ConstructorWithValidIterator_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  EXPECT_EQ(wrapper.iter(), iter);
  // Initially not seeked, should not be valid
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, SetIterator_379) {
  IteratorWrapper wrapper;
  auto* iter = new TestIterator(MakeSampleData());
  wrapper.Set(iter);
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_379, SetNullIterator_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, SeekToFirst_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "apple");
  EXPECT_EQ(wrapper.value().ToString(), "red");
}

TEST_F(IteratorWrapperTest_379, SeekToLast_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "elderberry");
  EXPECT_EQ(wrapper.value().ToString(), "purple");
}

TEST_F(IteratorWrapperTest_379, NextIteration_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "apple");

  wrapper.Next();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "banana");

  wrapper.Next();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "cherry");

  wrapper.Next();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "date");

  wrapper.Next();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "elderberry");

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, PrevIteration_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "elderberry");

  wrapper.Prev();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "date");

  wrapper.Prev();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "cherry");

  wrapper.Prev();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "banana");

  wrapper.Prev();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "apple");

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, SeekToExistingKey_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("cherry");
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "cherry");
  EXPECT_EQ(wrapper.value().ToString(), "dark_red");
}

TEST_F(IteratorWrapperTest_379, SeekToNonExistingKeyFindsNext_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("cat");  // between "banana" and "cherry"
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "cherry");
}

TEST_F(IteratorWrapperTest_379, SeekPastAllKeys_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("zzz");  // past all keys
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, SeekToFirstKey_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("apple");
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "apple");
}

TEST_F(IteratorWrapperTest_379, SeekBeforeFirstKey_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("aaa");  // before "apple"
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "apple");
}

TEST_F(IteratorWrapperTest_379, EmptyIterator_379) {
  auto* iter = new TestIterator({});
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, EmptyIteratorSeekToLast_379) {
  auto* iter = new TestIterator({});
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, EmptyIteratorSeek_379) {
  auto* iter = new TestIterator({});
  IteratorWrapper wrapper(iter);
  wrapper.Seek("anything");
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, StatusOk_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_379, SingleElementIterator_379) {
  auto* iter = new TestIterator({{"only", "one"}});
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only");
  EXPECT_EQ(wrapper.value().ToString(), "one");

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, SingleElementSeekToLast_379) {
  auto* iter = new TestIterator({{"only", "one"}});
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only");

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_379, SetReplacesOldIterator_379) {
  auto* iter1 = new TestIterator({{"a", "1"}, {"b", "2"}});
  auto* iter2 = new TestIterator({{"x", "10"}, {"y", "20"}});
  IteratorWrapper wrapper(iter1);
  wrapper.SeekToFirst();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  // Set replaces the iterator (should delete old one)
  wrapper.Set(iter2);
  wrapper.SeekToFirst();
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "x");
}

TEST_F(IteratorWrapperTest_379, ValueAfterSeek_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("banana");
  ASSERT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.value().ToString(), "yellow");
}

TEST_F(IteratorWrapperTest_379, IterReturnsUnderlyingIterator_379) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_379, FullForwardTraversal_379) {
  auto data = MakeSampleData();
  auto* iter = new TestIterator(data);
  IteratorWrapper wrapper(iter);

  int count = 0;
  for (wrapper.SeekToFirst(); wrapper.Valid(); wrapper.Next()) {
    EXPECT_EQ(wrapper.key().ToString(), data[count].first);
    EXPECT_EQ(wrapper.value().ToString(), data[count].second);
    count++;
  }
  EXPECT_EQ(count, static_cast<int>(data.size()));
}

TEST_F(IteratorWrapperTest_379, FullReverseTraversal_379) {
  auto data = MakeSampleData();
  auto* iter = new TestIterator(data);
  IteratorWrapper wrapper(iter);

  int count = static_cast<int>(data.size()) - 1;
  for (wrapper.SeekToLast(); wrapper.Valid(); wrapper.Prev()) {
    EXPECT_EQ(wrapper.key().ToString(), data[count].first);
    EXPECT_EQ(wrapper.value().ToString(), data[count].second);
    count--;
  }
  EXPECT_EQ(count, -1);
}

TEST_F(IteratorWrapperTest_379, KeyCachingConsistency_379) {
  // Verify that the key returned by wrapper matches underlying iterator's key
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  ASSERT_TRUE(wrapper.Valid());

  // The wrapper caches the key - verify it returns correct key through iteration
  Slice firstKey = wrapper.key();
  EXPECT_EQ(firstKey.ToString(), "apple");

  wrapper.Next();
  Slice secondKey = wrapper.key();
  EXPECT_EQ(secondKey.ToString(), "banana");
  // First key should still be "apple" conceptually but the underlying data may
  // have changed. We only verify current key is correct.
}

}  // namespace leveldb
