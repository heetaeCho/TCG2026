#include "gtest/gtest.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <map>

namespace leveldb {

// A simple test iterator that we can use to test IteratorWrapper
class TestIterator : public Iterator {
 public:
  TestIterator() : valid_(false), current_(0) {}

  void AddEntry(const std::string& key, const std::string& value) {
    entries_.push_back({key, value});
  }

  bool Valid() const override { return valid_; }

  void SeekToFirst() override {
    if (!entries_.empty()) {
      current_ = 0;
      valid_ = true;
    } else {
      valid_ = false;
    }
  }

  void SeekToLast() override {
    if (!entries_.empty()) {
      current_ = entries_.size() - 1;
      valid_ = true;
    } else {
      valid_ = false;
    }
  }

  void Seek(const Slice& target) override {
    for (size_t i = 0; i < entries_.size(); i++) {
      if (entries_[i].first >= target.ToString()) {
        current_ = i;
        valid_ = true;
        return;
      }
    }
    valid_ = false;
  }

  void Next() override {
    assert(valid_);
    current_++;
    if (current_ >= entries_.size()) {
      valid_ = false;
    }
  }

  void Prev() override {
    assert(valid_);
    if (current_ == 0) {
      valid_ = false;
    } else {
      current_--;
    }
  }

  Slice key() const override {
    assert(valid_);
    return Slice(entries_[current_].first);
  }

  Slice value() const override {
    assert(valid_);
    return Slice(entries_[current_].second);
  }

  Status status() const override { return status_; }

  void SetStatus(Status s) { status_ = s; }

 private:
  bool valid_;
  size_t current_;
  std::vector<std::pair<std::string, std::string>> entries_;
  Status status_;
};

class IteratorWrapperTest_375 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(IteratorWrapperTest_375, DefaultConstructorCreatesInvalidIterator_375) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_375, ConstructorWithIterator_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("key1", "value1");
  IteratorWrapper wrapper(iter);
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_375, SetReplacesIterator_375) {
  IteratorWrapper wrapper;
  TestIterator* iter = new TestIterator();
  iter->AddEntry("key1", "value1");
  wrapper.Set(iter);
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_375, SetDeletesPreviousIterator_375) {
  TestIterator* iter1 = new TestIterator();
  iter1->AddEntry("key1", "value1");
  TestIterator* iter2 = new TestIterator();
  iter2->AddEntry("key2", "value2");

  IteratorWrapper wrapper(iter1);
  wrapper.Set(iter2);
  EXPECT_EQ(wrapper.iter(), iter2);
}

TEST_F(IteratorWrapperTest_375, SetToNullptr_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("key1", "value1");
  IteratorWrapper wrapper(iter);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, SeekToFirstOnNonEmptyIterator_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("b", "vb");
  iter->AddEntry("c", "vc");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");
  EXPECT_EQ(wrapper.value().ToString(), "va");
}

TEST_F(IteratorWrapperTest_375, SeekToFirstOnEmptyIterator_375) {
  TestIterator* iter = new TestIterator();
  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, SeekToLastOnNonEmptyIterator_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("b", "vb");
  iter->AddEntry("c", "vc");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");
  EXPECT_EQ(wrapper.value().ToString(), "vc");
}

TEST_F(IteratorWrapperTest_375, SeekToLastOnEmptyIterator_375) {
  TestIterator* iter = new TestIterator();
  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, NextIteratesForward_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("b", "vb");
  iter->AddEntry("c", "vc");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();

  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "b");

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, PrevIteratesBackward_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("b", "vb");
  iter->AddEntry("c", "vc");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();

  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");

  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "b");

  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, SeekFindsCorrectEntry_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("c", "vc");
  iter->AddEntry("e", "ve");

  IteratorWrapper wrapper(iter);
  wrapper.Seek("c");
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");
  EXPECT_EQ(wrapper.value().ToString(), "vc");
}

TEST_F(IteratorWrapperTest_375, SeekFindsNextEntryWhenExactMissing_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("c", "vc");
  iter->AddEntry("e", "ve");

  IteratorWrapper wrapper(iter);
  wrapper.Seek("b");
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");
}

TEST_F(IteratorWrapperTest_375, SeekPastAllEntriesBecomesInvalid_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->AddEntry("b", "vb");

  IteratorWrapper wrapper(iter);
  wrapper.Seek("z");
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, StatusReturnsOk_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_375, StatusReturnsError_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "va");
  iter->SetStatus(Status::Corruption("test error"));

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

TEST_F(IteratorWrapperTest_375, KeyCachingBehavior_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("key1", "value1");
  iter->AddEntry("key2", "value2");
  iter->AddEntry("key3", "value3");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();

  // Access key multiple times — should return same result
  Slice k1 = wrapper.key();
  Slice k2 = wrapper.key();
  EXPECT_EQ(k1.ToString(), k2.ToString());
  EXPECT_EQ(k1.ToString(), "key1");
}

TEST_F(IteratorWrapperTest_375, ValueAccess_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("key1", "value1");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.value().ToString(), "value1");
}

TEST_F(IteratorWrapperTest_375, SingleEntryIterator_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("only", "single");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only");
  EXPECT_EQ(wrapper.value().ToString(), "single");

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, SingleEntrySeekToLast_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("only", "single");

  IteratorWrapper wrapper(iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only");

  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_375, IterReturnsUnderlyingIterator_375) {
  TestIterator* iter = new TestIterator();
  IteratorWrapper wrapper(iter);
  EXPECT_EQ(wrapper.iter(), iter);
}

TEST_F(IteratorWrapperTest_375, SetAfterIterating_375) {
  TestIterator* iter1 = new TestIterator();
  iter1->AddEntry("a", "va");
  iter1->AddEntry("b", "vb");

  IteratorWrapper wrapper(iter1);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  TestIterator* iter2 = new TestIterator();
  iter2->AddEntry("x", "vx");
  iter2->AddEntry("y", "vy");

  wrapper.Set(iter2);
  // After Set, the wrapper should reflect the new iterator's state
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "x");
}

TEST_F(IteratorWrapperTest_375, FullForwardIteration_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "1");
  iter->AddEntry("b", "2");
  iter->AddEntry("c", "3");
  iter->AddEntry("d", "4");
  iter->AddEntry("e", "5");

  IteratorWrapper wrapper(iter);
  std::vector<std::string> keys;
  for (wrapper.SeekToFirst(); wrapper.Valid(); wrapper.Next()) {
    keys.push_back(wrapper.key().ToString());
  }

  ASSERT_EQ(keys.size(), 5u);
  EXPECT_EQ(keys[0], "a");
  EXPECT_EQ(keys[1], "b");
  EXPECT_EQ(keys[2], "c");
  EXPECT_EQ(keys[3], "d");
  EXPECT_EQ(keys[4], "e");
}

TEST_F(IteratorWrapperTest_375, FullBackwardIteration_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("a", "1");
  iter->AddEntry("b", "2");
  iter->AddEntry("c", "3");

  IteratorWrapper wrapper(iter);
  std::vector<std::string> keys;
  for (wrapper.SeekToLast(); wrapper.Valid(); wrapper.Prev()) {
    keys.push_back(wrapper.key().ToString());
  }

  ASSERT_EQ(keys.size(), 3u);
  EXPECT_EQ(keys[0], "c");
  EXPECT_EQ(keys[1], "b");
  EXPECT_EQ(keys[2], "a");
}

TEST_F(IteratorWrapperTest_375, SeekToFirstThenValue_375) {
  TestIterator* iter = new TestIterator();
  iter->AddEntry("hello", "world");
  iter->AddEntry("foo", "bar");

  IteratorWrapper wrapper(iter);
  wrapper.Seek("foo");
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "foo");
  EXPECT_EQ(wrapper.value().ToString(), "bar");
}

}  // namespace leveldb
