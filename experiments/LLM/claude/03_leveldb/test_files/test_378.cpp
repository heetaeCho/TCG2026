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

class IteratorWrapperTest_378 : public ::testing::Test {
 protected:
  std::vector<std::pair<std::string, std::string>> MakeSampleData() {
    return {{"a", "val_a"}, {"b", "val_b"}, {"c", "val_c"},
            {"d", "val_d"}, {"e", "val_e"}};
  }
};

TEST_F(IteratorWrapperTest_378, DefaultConstructor_Invalid_378) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_378, ConstructWithNullIterator_378) {
  IteratorWrapper wrapper(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_378, ConstructWithValidIterator_378) {
  auto data = MakeSampleData();
  Iterator* iter = new TestIterator(data);
  IteratorWrapper wrapper(iter);
  EXPECT_FALSE(wrapper.Valid());  // Not yet seeked
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_378, SetIterator_378) {
  auto data = MakeSampleData();
  Iterator* iter = new TestIterator(data);
  IteratorWrapper wrapper;
  wrapper.Set(iter);
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_378, SetNullIterator_378) {
  auto data = MakeSampleData();
  Iterator* iter = new TestIterator(data);
  IteratorWrapper wrapper(iter);
  wrapper.Set(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_378, SeekToFirst_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");
  EXPECT_EQ(wrapper.value().ToString(), "val_a");
}

TEST_F(IteratorWrapperTest_378, SeekToLast_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "e");
  EXPECT_EQ(wrapper.value().ToString(), "val_e");
}

TEST_F(IteratorWrapperTest_378, Next_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "b");
  EXPECT_EQ(wrapper.value().ToString(), "val_b");

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");
}

TEST_F(IteratorWrapperTest_378, Prev_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "e");

  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "d");
  EXPECT_EQ(wrapper.value().ToString(), "val_d");
}

TEST_F(IteratorWrapperTest_378, SeekExistingKey_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.Seek("c");
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");
  EXPECT_EQ(wrapper.value().ToString(), "val_c");
}

TEST_F(IteratorWrapperTest_378, SeekNonExistingKey_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  // Seek to a key that doesn't exist but falls between existing keys
  wrapper.Seek("bb");
  // Should land on "c" (first key >= "bb")
  if (wrapper.Valid()) {
    EXPECT_EQ(wrapper.key().ToString(), "c");
  }
}

TEST_F(IteratorWrapperTest_378, SeekPastEnd_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.Seek("z");
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_378, IterateAllForward_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();

  std::vector<std::string> keys;
  while (wrapper.Valid()) {
    keys.push_back(wrapper.key().ToString());
    wrapper.Next();
  }
  EXPECT_EQ(keys.size(), 5u);
  EXPECT_EQ(keys[0], "a");
  EXPECT_EQ(keys[1], "b");
  EXPECT_EQ(keys[2], "c");
  EXPECT_EQ(keys[3], "d");
  EXPECT_EQ(keys[4], "e");
}

TEST_F(IteratorWrapperTest_378, IterateAllBackward_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToLast();

  std::vector<std::string> keys;
  while (wrapper.Valid()) {
    keys.push_back(wrapper.key().ToString());
    wrapper.Prev();
  }
  EXPECT_EQ(keys.size(), 5u);
  EXPECT_EQ(keys[0], "e");
  EXPECT_EQ(keys[1], "d");
  EXPECT_EQ(keys[2], "c");
  EXPECT_EQ(keys[3], "b");
  EXPECT_EQ(keys[4], "a");
}

TEST_F(IteratorWrapperTest_378, StatusOk_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_378, EmptyIterator_SeekToFirst_378) {
  std::vector<std::pair<std::string, std::string>> empty_data;
  IteratorWrapper wrapper(new TestIterator(empty_data));
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_378, EmptyIterator_SeekToLast_378) {
  std::vector<std::pair<std::string, std::string>> empty_data;
  IteratorWrapper wrapper(new TestIterator(empty_data));
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_378, EmptyIterator_Seek_378) {
  std::vector<std::pair<std::string, std::string>> empty_data;
  IteratorWrapper wrapper(new TestIterator(empty_data));
  wrapper.Seek("anything");
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_378, SingleElement_378) {
  std::vector<std::pair<std::string, std::string>> single = {{"only", "one"}};
  IteratorWrapper wrapper(new TestIterator(single));

  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only");
  EXPECT_EQ(wrapper.value().ToString(), "one");

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_378, SingleElement_SeekToLast_378) {
  std::vector<std::pair<std::string, std::string>> single = {{"only", "one"}};
  IteratorWrapper wrapper(new TestIterator(single));

  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only");

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_378, SetReplacesIterator_378) {
  auto data1 = MakeSampleData();
  std::vector<std::pair<std::string, std::string>> data2 = {{"x", "val_x"}, {"y", "val_y"}};

  IteratorWrapper wrapper(new TestIterator(data1));
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  // Replace with a different iterator
  wrapper.Set(new TestIterator(data2));
  // After Set, the wrapper should reflect the new iterator's state
  // The new iterator hasn't been seeked yet, so it should be invalid
  EXPECT_FALSE(wrapper.Valid());

  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "x");
}

TEST_F(IteratorWrapperTest_378, KeyCaching_378) {
  // Test that repeated calls to key() return consistent results
  // (This tests the caching behavior observable through the interface)
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();

  Slice key1 = wrapper.key();
  Slice key2 = wrapper.key();
  EXPECT_EQ(key1.ToString(), key2.ToString());
  EXPECT_EQ(key1.ToString(), "a");
}

TEST_F(IteratorWrapperTest_378, NextThenPrev_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "a");

  wrapper.Next();
  EXPECT_EQ(wrapper.key().ToString(), "b");

  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");
}

TEST_F(IteratorWrapperTest_378, SeekToFirstThenValue_378) {
  auto data = MakeSampleData();
  IteratorWrapper wrapper(new TestIterator(data));
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.value().ToString(), "val_a");
}

TEST_F(IteratorWrapperTest_378, StatusAfterEmptySeek_378) {
  std::vector<std::pair<std::string, std::string>> empty_data;
  IteratorWrapper wrapper(new TestIterator(empty_data));
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.status().ok());
}

}  // namespace leveldb
