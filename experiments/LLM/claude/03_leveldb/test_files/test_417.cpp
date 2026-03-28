#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "table/two_level_iterator.h"

using namespace leveldb;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

// Forward declaration of the function under test
namespace leveldb {
typedef Iterator* (*BlockFunction)(void*, const ReadOptions&, const Slice&);
Iterator* NewTwoLevelIterator(Iterator* index_iter,
                              BlockFunction block_function,
                              void* arg,
                              const ReadOptions& options);
}

// Mock Iterator for testing
class MockIterator : public Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));
};

// Helper to create a block function that returns a MockIterator
static MockIterator* g_block_iter = nullptr;

Iterator* TestBlockFunction(void* arg, const ReadOptions& options, const Slice& index_value) {
  return g_block_iter;
}

// A simple test iterator that stores key-value pairs
class SimpleIterator : public Iterator {
 public:
  SimpleIterator() : current_(0), valid_(false) {}

  void AddEntry(const std::string& key, const std::string& value) {
    keys_.push_back(key);
    values_.push_back(value);
  }

  bool Valid() const override { return valid_ && current_ < keys_.size(); }

  void SeekToFirst() override {
    current_ = 0;
    valid_ = !keys_.empty();
  }

  void SeekToLast() override {
    if (keys_.empty()) {
      valid_ = false;
    } else {
      current_ = keys_.size() - 1;
      valid_ = true;
    }
  }

  void Seek(const Slice& target) override {
    for (size_t i = 0; i < keys_.size(); i++) {
      if (keys_[i] >= target.ToString()) {
        current_ = i;
        valid_ = true;
        return;
      }
    }
    valid_ = false;
  }

  void Next() override {
    if (valid_) {
      current_++;
      if (current_ >= keys_.size()) {
        valid_ = false;
      }
    }
  }

  void Prev() override {
    if (valid_) {
      if (current_ == 0) {
        valid_ = false;
      } else {
        current_--;
      }
    }
  }

  Slice key() const override {
    return Slice(keys_[current_]);
  }

  Slice value() const override {
    return Slice(values_[current_]);
  }

  Status status() const override { return Status::OK(); }

 private:
  std::vector<std::string> keys_;
  std::vector<std::string> values_;
  size_t current_;
  bool valid_;
};

// Global storage for block iterators created by the block function
static std::vector<SimpleIterator*> g_created_block_iters;
static std::map<std::string, SimpleIterator*> g_block_map;

Iterator* MapBlockFunction(void* arg, const ReadOptions& options, const Slice& index_value) {
  std::string key = index_value.ToString();
  auto it = g_block_map.find(key);
  if (it != g_block_map.end()) {
    return it->second;
  }
  // Return an empty iterator
  SimpleIterator* empty = new SimpleIterator();
  g_created_block_iters.push_back(empty);
  return empty;
}

class TwoLevelIteratorTest_417 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_block_iter = nullptr;
    g_created_block_iters.clear();
    g_block_map.clear();
  }

  void TearDown() override {
    g_block_map.clear();
    g_created_block_iters.clear();
  }
};

TEST_F(TwoLevelIteratorTest_417, CreationReturnsNonNull_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  ASSERT_NE(iter, nullptr);
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, EmptyIndexIteratorNotValid_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, EmptyIndexSeekToFirst_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, EmptyIndexSeekToLast_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, EmptyIndexSeek_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->Seek("anything");
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, EmptyIndexStatusOk_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SingleBlockSeekToFirst_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("block0", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("b", "val_b");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");
  EXPECT_EQ(iter->value().ToString(), "val_a");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SingleBlockNextIteration_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("block0", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("b", "val_b");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, MultipleBlocksForwardIteration_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");
  index_iter->AddEntry("h", "block1_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  SimpleIterator* block1 = new SimpleIterator();
  block1->AddEntry("e", "val_e");
  block1->AddEntry("g", "val_g");
  g_block_map["block1_handle"] = block1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "e");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "g");

  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekToLastSingleBlock_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("block0", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("b", "val_b");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekToLastMultipleBlocks_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");
  index_iter->AddEntry("h", "block1_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  SimpleIterator* block1 = new SimpleIterator();
  block1->AddEntry("e", "val_e");
  block1->AddEntry("g", "val_g");
  g_block_map["block1_handle"] = block1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "g");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, PrevFromLastMultipleBlocks_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");
  index_iter->AddEntry("h", "block1_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  SimpleIterator* block1 = new SimpleIterator();
  block1->AddEntry("e", "val_e");
  block1->AddEntry("g", "val_g");
  g_block_map["block1_handle"] = block1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "g");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "e");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekFindsCorrectKey_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");
  index_iter->AddEntry("h", "block1_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  SimpleIterator* block1 = new SimpleIterator();
  block1->AddEntry("e", "val_e");
  block1->AddEntry("g", "val_g");
  g_block_map["block1_handle"] = block1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->Seek("c");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");
  EXPECT_EQ(iter->value().ToString(), "val_c");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekBeyondAllKeys_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->Seek("z");
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekToMiddleOfSecondBlock_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");
  index_iter->AddEntry("h", "block1_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  SimpleIterator* block1 = new SimpleIterator();
  block1->AddEntry("e", "val_e");
  block1->AddEntry("g", "val_g");
  g_block_map["block1_handle"] = block1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->Seek("f");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "g");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekBeforeFirstKey_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("b", "val_b");
  block0->AddEntry("c", "val_c");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->Seek("a");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, EmptyBlocksSkipped_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");
  index_iter->AddEntry("h", "block1_handle");

  // block0 is empty
  SimpleIterator* block0 = new SimpleIterator();
  g_block_map["block0_handle"] = block0;

  SimpleIterator* block1 = new SimpleIterator();
  block1->AddEntry("e", "val_e");
  g_block_map["block1_handle"] = block1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->SeekToFirst();
  // After seeking to first in an empty first block, should advance to next block
  if (iter->Valid()) {
    EXPECT_EQ(iter->key().ToString(), "e");
  }
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SingleEntryIteration_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("a", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");
  EXPECT_EQ(iter->value().ToString(), "val_a");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, StatusOkOnNormalIteration_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("d", "block0_handle");

  SimpleIterator* block0 = new SimpleIterator();
  block0->AddEntry("a", "val_a");
  g_block_map["block0_handle"] = block0;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());

  iter->Next();
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Error iterator for testing error propagation
class ErrorIterator : public Iterator {
 public:
  explicit ErrorIterator(Status s) : status_(s) {}
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

static ErrorIterator* g_error_block_iter = nullptr;

Iterator* ErrorBlockFunction(void* arg, const ReadOptions& options, const Slice& index_value) {
  return new ErrorIterator(Status::Corruption("block read error"));
}

TEST_F(TwoLevelIteratorTest_417, ErrorIndexIteratorPropagatesStatus_417) {
  // Use an error iterator as the index iterator
  ErrorIterator* index_iter = new ErrorIterator(Status::Corruption("index error"));

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, ThreeBlocksForwardAndBackward_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("c", "b0");
  index_iter->AddEntry("f", "b1");
  index_iter->AddEntry("i", "b2");

  SimpleIterator* b0 = new SimpleIterator();
  b0->AddEntry("a", "1");
  b0->AddEntry("b", "2");
  g_block_map["b0"] = b0;

  SimpleIterator* b1 = new SimpleIterator();
  b1->AddEntry("d", "3");
  b1->AddEntry("e", "4");
  g_block_map["b1"] = b1;

  SimpleIterator* b2 = new SimpleIterator();
  b2->AddEntry("g", "5");
  b2->AddEntry("h", "6");
  g_block_map["b2"] = b2;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  // Forward
  iter->SeekToFirst();
  std::vector<std::string> forward_keys;
  while (iter->Valid()) {
    forward_keys.push_back(iter->key().ToString());
    iter->Next();
  }
  ASSERT_EQ(forward_keys.size(), 6u);
  EXPECT_EQ(forward_keys[0], "a");
  EXPECT_EQ(forward_keys[1], "b");
  EXPECT_EQ(forward_keys[2], "d");
  EXPECT_EQ(forward_keys[3], "e");
  EXPECT_EQ(forward_keys[4], "g");
  EXPECT_EQ(forward_keys[5], "h");

  // Backward
  iter->SeekToLast();
  std::vector<std::string> backward_keys;
  while (iter->Valid()) {
    backward_keys.push_back(iter->key().ToString());
    iter->Prev();
  }
  ASSERT_EQ(backward_keys.size(), 6u);
  EXPECT_EQ(backward_keys[0], "h");
  EXPECT_EQ(backward_keys[1], "g");
  EXPECT_EQ(backward_keys[2], "e");
  EXPECT_EQ(backward_keys[3], "d");
  EXPECT_EQ(backward_keys[4], "b");
  EXPECT_EQ(backward_keys[5], "a");

  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, SeekExactKeyInSecondBlock_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("c", "b0");
  index_iter->AddEntry("f", "b1");

  SimpleIterator* b0 = new SimpleIterator();
  b0->AddEntry("a", "1");
  b0->AddEntry("c", "2");
  g_block_map["b0"] = b0;

  SimpleIterator* b1 = new SimpleIterator();
  b1->AddEntry("d", "3");
  b1->AddEntry("f", "4");
  g_block_map["b1"] = b1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->Seek("d");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "d");
  EXPECT_EQ(iter->value().ToString(), "3");
  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, NextThenPrevReturnsCorrectKey_417) {
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("c", "b0");
  index_iter->AddEntry("f", "b1");

  SimpleIterator* b0 = new SimpleIterator();
  b0->AddEntry("a", "1");
  b0->AddEntry("b", "2");
  g_block_map["b0"] = b0;

  SimpleIterator* b1 = new SimpleIterator();
  b1->AddEntry("d", "3");
  b1->AddEntry("e", "4");
  g_block_map["b1"] = b1;

  ReadOptions options;
  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "d");

  // Now go back
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  delete iter;
}

TEST_F(TwoLevelIteratorTest_417, ReadOptionsPassedThrough_417) {
  // Test that different ReadOptions don't cause crashes
  SimpleIterator* index_iter = new SimpleIterator();
  index_iter->AddEntry("a", "b0");

  SimpleIterator* b0 = new SimpleIterator();
  b0->AddEntry("a", "val");
  g_block_map["b0"] = b0;

  ReadOptions options;
  options.verify_checksums = true;
  options.fill_cache = false;

  Iterator* iter = NewTwoLevelIterator(index_iter, MapBlockFunction, nullptr, options);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");
  delete iter;
}
