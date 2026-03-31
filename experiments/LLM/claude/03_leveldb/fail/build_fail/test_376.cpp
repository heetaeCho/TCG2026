#include "gtest/gtest.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/testutil.h"

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
      index_ = -1;  // not found
    }
  }

  void Next() override {
    assert(Valid());
    index_++;
    if (index_ >= static_cast<int>(data_.size())) {
      index_ = -1;
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

// An iterator that returns an error status
class ErrorIterator : public Iterator {
 public:
  explicit ErrorIterator(const Status& s) : status_(s) {}
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

class IteratorWrapperTest_376 : public ::testing::Test {
 protected:
  std::vector<std::pair<std::string, std::string>> MakeSampleData() {
    return {{"a", "val_a"}, {"b", "val_b"}, {"c", "val_c"},
            {"d", "val_d"}, {"e", "val_e"}};
  }
};

TEST_F(IteratorWrapperTest_376, DefaultConstructor_NullIter_376) {
  IteratorWrapper wrapper;
  EXPECT_EQ(nullptr, wrapper.iter());
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, ConstructorWithIterator_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  EXPECT_EQ(iter, wrapper.iter());
}

TEST_F(IteratorWrapperTest_376, SetIterator_376) {
  IteratorWrapper wrapper;
  EXPECT_EQ(nullptr, wrapper.iter());

  auto* iter = new TestIterator(MakeSampleData());
  wrapper.Set(iter);
  EXPECT_EQ(iter, wrapper.iter());
}

TEST_F(IteratorWrapperTest_376, SetReplacesOldIterator_376) {
  auto* iter1 = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter1);
  EXPECT_EQ(iter1, wrapper.iter());

  auto* iter2 = new TestIterator({{"x", "val_x"}});
  wrapper.Set(iter2);
  EXPECT_EQ(iter2, wrapper.iter());
}

TEST_F(IteratorWrapperTest_376, SetNull_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Set(nullptr);
  EXPECT_EQ(nullptr, wrapper.iter());
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, SeekToFirst_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("a", wrapper.key().ToString());
  EXPECT_EQ("val_a", wrapper.value().ToString());
}

TEST_F(IteratorWrapperTest_376, SeekToLast_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("e", wrapper.key().ToString());
  EXPECT_EQ("val_e", wrapper.value().ToString());
}

TEST_F(IteratorWrapperTest_376, Next_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("a", wrapper.key().ToString());

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("b", wrapper.key().ToString());
  EXPECT_EQ("val_b", wrapper.value().ToString());

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("c", wrapper.key().ToString());
}

TEST_F(IteratorWrapperTest_376, Prev_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("e", wrapper.key().ToString());

  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("d", wrapper.key().ToString());
  EXPECT_EQ("val_d", wrapper.value().ToString());
}

TEST_F(IteratorWrapperTest_376, Seek_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("c");
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("c", wrapper.key().ToString());
  EXPECT_EQ("val_c", wrapper.value().ToString());
}

TEST_F(IteratorWrapperTest_376, SeekNonExistentKey_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  // "z" is beyond all keys, so Seek should result in invalid
  wrapper.Seek("z");
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, IterateAll_376) {
  auto data = MakeSampleData();
  auto* iter = new TestIterator(data);
  IteratorWrapper wrapper(iter);

  int count = 0;
  for (wrapper.SeekToFirst(); wrapper.Valid(); wrapper.Next()) {
    EXPECT_EQ(data[count].first, wrapper.key().ToString());
    EXPECT_EQ(data[count].second, wrapper.value().ToString());
    count++;
  }
  EXPECT_EQ(static_cast<int>(data.size()), count);
}

TEST_F(IteratorWrapperTest_376, IterateReverseAll_376) {
  auto data = MakeSampleData();
  auto* iter = new TestIterator(data);
  IteratorWrapper wrapper(iter);

  int count = static_cast<int>(data.size()) - 1;
  for (wrapper.SeekToLast(); wrapper.Valid(); wrapper.Prev()) {
    EXPECT_EQ(data[count].first, wrapper.key().ToString());
    EXPECT_EQ(data[count].second, wrapper.value().ToString());
    count--;
  }
  EXPECT_EQ(-1, count);
}

TEST_F(IteratorWrapperTest_376, EmptyIterator_376) {
  auto* iter = new TestIterator({});
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, StatusOK_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_376, StatusError_376) {
  auto* iter = new ErrorIterator(Status::Corruption("test error"));
  IteratorWrapper wrapper(iter);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

TEST_F(IteratorWrapperTest_376, SingleElementIterator_376) {
  auto* iter = new TestIterator({{"only", "one"}});
  IteratorWrapper wrapper(iter);

  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("only", wrapper.key().ToString());
  EXPECT_EQ("one", wrapper.value().ToString());

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, SingleElementSeekToLast_376) {
  auto* iter = new TestIterator({{"only", "one"}});
  IteratorWrapper wrapper(iter);

  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("only", wrapper.key().ToString());
  EXPECT_EQ("one", wrapper.value().ToString());

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, SeekToFirstOfExistingKey_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.Seek("a");
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ("a", wrapper.key().ToString());
}

TEST_F(IteratorWrapperTest_376, ValidAfterSetNewIterator_376) {
  auto* iter1 = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter1);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());

  // Replace with a new iterator; state should reset
  auto* iter2 = new TestIterator({{"x", "val_x"}});
  wrapper.Set(iter2);
  // After Set, the wrapper should reflect the new iterator's initial state
  // The new iterator hasn't been positioned, so Valid should be false
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, KeyCachingConsistency_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);

  wrapper.SeekToFirst();
  Slice key1 = wrapper.key();
  // Calling key() again should return the same value
  Slice key2 = wrapper.key();
  EXPECT_EQ(key1.ToString(), key2.ToString());

  wrapper.Next();
  Slice key3 = wrapper.key();
  EXPECT_NE(key1.ToString(), key3.ToString());
  EXPECT_EQ("b", key3.ToString());
}

TEST_F(IteratorWrapperTest_376, DestructorDeletesIterator_376) {
  // We just ensure no crash/leak when wrapper is destroyed with an iterator
  auto* iter = new TestIterator(MakeSampleData());
  {
    IteratorWrapper wrapper(iter);
    wrapper.SeekToFirst();
    EXPECT_TRUE(wrapper.Valid());
  }
  // If the wrapper properly deletes the iterator, this should not leak
}

TEST_F(IteratorWrapperTest_376, NextPastEnd_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();

  // Advance past all elements
  while (wrapper.Valid()) {
    wrapper.Next();
  }
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_376, PrevBeforeBeginning_376) {
  auto* iter = new TestIterator(MakeSampleData());
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

}  // namespace leveldb
