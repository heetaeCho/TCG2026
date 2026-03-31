#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "table/format.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class BlockTest_408 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  std::string BuildBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                         int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // BlockBuilder uses options.block_restart_interval which defaults to 16
    // We need to set it
    Options opts;
    opts.block_restart_interval = restart_interval;
    BlockBuilder b(&opts);
    for (const auto& kv : kvs) {
      b.Add(kv.first, kv.second);
    }
    return b.Finish().ToString();
  }

  Iterator* NewBlockIterator(const std::string& block_data) {
    BlockContents contents;
    contents.data = Slice(block_data);
    contents.cachable = false;
    contents.heap_allocated = false;
    Block block(contents);
    return block.NewIterator(BytewiseComparator());
  }
};

// Test that an empty block produces an iterator that is not valid
TEST_F(BlockTest_408, EmptyBlockIteratorNotValid_408) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test SeekToFirst on a block with one entry
TEST_F(BlockTest_408, SingleEntrySeekToFirst_408) {
  std::string data = BuildBlock({{"key1", "value1"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "value1");
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test SeekToLast on a block with one entry
TEST_F(BlockTest_408, SingleEntrySeekToLast_408) {
  std::string data = BuildBlock({{"key1", "value1"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "value1");
  delete iter;
}

// Test iterating forward through multiple entries
TEST_F(BlockTest_408, ForwardIteration_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
      {"ddd", "val_d"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    iter->Next();
    count++;
  }
  ASSERT_EQ(count, 4);
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test iterating backward through multiple entries
TEST_F(BlockTest_408, BackwardIteration_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
      {"ddd", "val_d"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  int count = static_cast<int>(kvs.size()) - 1;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    iter->Prev();
    count--;
  }
  ASSERT_EQ(count, -1);
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Seek to an exact key
TEST_F(BlockTest_408, SeekExactKey_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
      {"ddd", "val_d"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");
  ASSERT_EQ(iter->value().ToString(), "val_b");
  delete iter;
}

// Test Seek to a key between existing keys
TEST_F(BlockTest_408, SeekBetweenKeys_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"ccc", "val_c"},
      {"eee", "val_e"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val_c");
  delete iter;
}

// Test Seek past all keys
TEST_F(BlockTest_408, SeekPastAllKeys_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Seek before all keys
TEST_F(BlockTest_408, SeekBeforeAllKeys_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"bbb", "val_b"},
      {"ccc", "val_c"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");
  delete iter;
}

// Test Next past the end makes iterator invalid
TEST_F(BlockTest_408, NextPastEnd_408) {
  std::string data = BuildBlock({{"key1", "val1"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Prev before the beginning makes iterator invalid
TEST_F(BlockTest_408, PrevBeforeBeginning_408) {
  std::string data = BuildBlock({{"key1", "val1"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test with many entries spanning multiple restart points
TEST_F(BlockTest_408, ManyEntriesWithRestarts_408) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "value%06d", i);
    kvs.push_back({std::string(key), std::string(val)});
  }
  std::string data = BuildBlock(kvs, 4);  // restart every 4 entries
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Forward iteration
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    iter->Next();
    count++;
  }
  ASSERT_EQ(count, 100);

  // Backward iteration
  iter->SeekToLast();
  count = 99;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    iter->Prev();
    count--;
  }
  ASSERT_EQ(count, -1);

  delete iter;
}

// Test Seek in block with many entries
TEST_F(BlockTest_408, SeekInLargeBlock_408) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i * 2);  // even numbers only
    snprintf(val, sizeof(val), "value%06d", i * 2);
    kvs.push_back({std::string(key), std::string(val)});
  }
  std::string data = BuildBlock(kvs, 4);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Seek to an odd-numbered key, should land on the next even
  char target[32];
  snprintf(target, sizeof(target), "key%06d", 51);
  iter->Seek(target);
  ASSERT_TRUE(iter->Valid());
  char expected[32];
  snprintf(expected, sizeof(expected), "key%06d", 52);
  ASSERT_EQ(iter->key().ToString(), std::string(expected));

  delete iter;
}

// Test empty value
TEST_F(BlockTest_408, EmptyValue_408) {
  std::string data = BuildBlock({{"key1", ""}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "");
  delete iter;
}

// Test block size is reported
TEST_F(BlockTest_408, BlockSize_408) {
  std::string data = BuildBlock({{"key1", "value1"}, {"key2", "value2"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  ASSERT_GT(block.size(), 0u);
}

// Test status is ok after normal operations
TEST_F(BlockTest_408, StatusOkAfterOperations_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"}, {"bbb", "2"}, {"ccc", "3"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  iter->SeekToLast();
  ASSERT_TRUE(iter->status().ok());
  iter->Prev();
  ASSERT_TRUE(iter->status().ok());
  iter->Seek("bbb");
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

// Test forward then backward mixed iteration
TEST_F(BlockTest_408, MixedForwardBackward_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}, {"d", "4"}, {"e", "5"},
  };
  std::string data = BuildBlock(kvs, 2);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_EQ(iter->key().ToString(), "a");
  iter->Next();
  ASSERT_EQ(iter->key().ToString(), "b");
  iter->Next();
  ASSERT_EQ(iter->key().ToString(), "c");
  iter->Prev();
  ASSERT_EQ(iter->key().ToString(), "b");
  iter->Prev();
  ASSERT_EQ(iter->key().ToString(), "a");
  iter->Next();
  ASSERT_EQ(iter->key().ToString(), "b");

  delete iter;
}

// Test with restart interval of 1 (every key is a restart point)
TEST_F(BlockTest_408, RestartIntervalOne_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"}, {"beta", "2"}, {"gamma", "3"}, {"delta_long_key", "4"},
  };
  // Sort keys since block expects sorted input
  std::sort(kvs.begin(), kvs.end());
  std::string data = BuildBlock(kvs, 1);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    iter->Next();
    count++;
  }
  ASSERT_EQ(count, static_cast<int>(kvs.size()));

  delete iter;
}

// Test SeekToFirst on empty block
TEST_F(BlockTest_408, SeekToFirstOnEmptyBlock_408) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test SeekToLast on empty block
TEST_F(BlockTest_408, SeekToLastOnEmptyBlock_408) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Seek on empty block
TEST_F(BlockTest_408, SeekOnEmptyBlock_408) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("anything");
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test with keys sharing long common prefixes
TEST_F(BlockTest_408, SharedPrefixKeys_408) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"prefix_aaa", "1"},
      {"prefix_aab", "2"},
      {"prefix_aac", "3"},
      {"prefix_bbb", "4"},
      {"prefix_bbc", "5"},
  };
  std::string data = BuildBlock(kvs, 2);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("prefix_aab");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "prefix_aab");
  ASSERT_EQ(iter->value().ToString(), "2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "prefix_aac");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "prefix_aab");

  delete iter;
}

// Test with large values
TEST_F(BlockTest_408, LargeValues_408) {
  std::string large_val(10000, 'x');
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", large_val},
      {"key2", large_val},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), large_val);

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key2");
  ASSERT_EQ(iter->value().ToString(), large_val);

  delete iter;
}

}  // namespace leveldb
