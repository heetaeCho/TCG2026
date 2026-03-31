#include "gtest/gtest.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
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

class BlockTest_411 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  std::string BuildBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                         int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // Override restart interval if needed - BlockBuilder uses Options
    // We'll use the default options which has block_restart_interval = 16
    for (const auto& kv : kvs) {
      builder.Add(Slice(kv.first), Slice(kv.second));
    }
    Slice raw = builder.Finish();
    return std::string(raw.data(), raw.size());
  }

  // Helper to build a block with a specific restart interval
  std::string BuildBlockWithRestartInterval(
      const std::vector<std::pair<std::string, std::string>>& kvs,
      int restart_interval) {
    Options options;
    options.comparator = BytewiseComparator();
    // BlockBuilder constructor takes Options* and uses block_restart_interval
    // We need to set it before constructing
    // Actually, Options has block_restart_interval field
    options.block_restart_interval = restart_interval;
    BlockBuilder builder(&options);
    for (const auto& kv : kvs) {
      builder.Add(Slice(kv.first), Slice(kv.second));
    }
    Slice raw = builder.Finish();
    return std::string(raw.data(), raw.size());
  }
};

// Test that an empty block produces an invalid iterator
TEST_F(BlockTest_411, EmptyBlock_411) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToFirst on an empty block
TEST_F(BlockTest_411, SeekToFirstEmptyBlock_411) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on an empty block
TEST_F(BlockTest_411, SeekToLastEmptyBlock_411) {
  std::string data = BuildBlock({});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block
TEST_F(BlockTest_411, SingleEntry_411) {
  std::string data = BuildBlock({{"key1", "value1"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test multiple entries with forward iteration
TEST_F(BlockTest_411, MultipleEntriesForwardIteration_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  for (size_t i = 0; i < kvs.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test backward iteration (Prev)
TEST_F(BlockTest_411, BackwardIteration_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  for (int i = kvs.size() - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    if (i > 0) iter->Prev();
  }

  delete iter;
}

// Test Seek to an existing key
TEST_F(BlockTest_411, SeekExistingKey_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  EXPECT_EQ(iter->value().ToString(), "val3");

  delete iter;
}

// Test Seek to a non-existing key (should land on next key)
TEST_F(BlockTest_411, SeekNonExistingKey_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"ccc", "val3"},
      {"eee", "val5"},
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
  EXPECT_EQ(iter->key().ToString(), "ccc");

  delete iter;
}

// Test Seek past the last key
TEST_F(BlockTest_411, SeekPastEnd_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
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

  delete iter;
}

// Test Seek before the first key
TEST_F(BlockTest_411, SeekBeforeFirst_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"bbb", "val2"},
      {"ccc", "val3"},
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
  EXPECT_EQ(iter->key().ToString(), "bbb");

  delete iter;
}

// Test SeekToLast on a single entry
TEST_F(BlockTest_411, SeekToLastSingleEntry_411) {
  std::string data = BuildBlock({{"only", "entry"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only");
  EXPECT_EQ(iter->value().ToString(), "entry");

  delete iter;
}

// Test Prev from SeekToLast goes through all entries
TEST_F(BlockTest_411, PrevFromLastToFirst_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  delete iter;
}

// Test status is OK for a valid block
TEST_F(BlockTest_411, StatusOkForValidBlock_411) {
  std::string data = BuildBlock({{"key", "val"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test with many entries (more than restart interval)
TEST_F(BlockTest_411, ManyEntries_411) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[16], val[16];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    kvs.push_back({std::string(key), std::string(val)});
  }
  std::string data = BuildBlockWithRestartInterval(kvs, 4);
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
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 100);

  delete iter;
}

// Test Seek with many entries across restart points
TEST_F(BlockTest_411, SeekAcrossRestartPoints_411) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 50; i++) {
    char key[16], val[16];
    snprintf(key, sizeof(key), "key%06d", i * 2);  // even numbers
    snprintf(val, sizeof(val), "val%06d", i * 2);
    kvs.push_back({std::string(key), std::string(val)});
  }
  std::string data = BuildBlockWithRestartInterval(kvs, 4);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Seek to a key that doesn't exist (odd number), should find next even
  char target[16];
  snprintf(target, sizeof(target), "key%06d", 25);
  iter->Seek(Slice(target));
  ASSERT_TRUE(iter->Valid());
  char expected[16];
  snprintf(expected, sizeof(expected), "key%06d", 26);
  EXPECT_EQ(iter->key().ToString(), std::string(expected));

  delete iter;
}

// Test block with restart interval of 1 (no prefix compression)
TEST_F(BlockTest_411, RestartIntervalOne_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
      {"delta_long_key", "4"},
  };
  // Sort kvs since block expects sorted keys
  std::sort(kvs.begin(), kvs.end());
  std::string data = BuildBlockWithRestartInterval(kvs, 1);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, static_cast<int>(kvs.size()));

  delete iter;
}

// Test Next then Prev alternation
TEST_F(BlockTest_411, NextThenPrev_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"},
      {"bbb", "2"},
      {"ccc", "3"},
      {"ddd", "4"},
      {"eee", "5"},
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
  EXPECT_EQ(iter->key().ToString(), "aaa");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "aaa");

  delete iter;
}

// Test Seek then continue forward
TEST_F(BlockTest_411, SeekThenContinueForward_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"},
      {"bbb", "2"},
      {"ccc", "3"},
      {"ddd", "4"},
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
  EXPECT_EQ(iter->key().ToString(), "bbb");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ddd");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test Seek then Prev
TEST_F(BlockTest_411, SeekThenPrev_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"},
      {"bbb", "2"},
      {"ccc", "3"},
      {"ddd", "4"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");

  delete iter;
}

// Test with empty key
TEST_F(BlockTest_411, EmptyKey_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"", "empty_key_value"},
      {"a", "val_a"},
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
  EXPECT_EQ(iter->key().ToString(), "");
  EXPECT_EQ(iter->value().ToString(), "empty_key_value");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  delete iter;
}

// Test with empty value
TEST_F(BlockTest_411, EmptyValue_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", ""},
      {"key2", "non_empty"},
      {"key3", ""},
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
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), "non_empty");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");
  EXPECT_EQ(iter->value().ToString(), "");

  delete iter;
}

// Test block size method
TEST_F(BlockTest_411, BlockSize_411) {
  std::string data = BuildBlock({{"key", "value"}});
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  EXPECT_EQ(block.size(), data.size());
}

// Test large values
TEST_F(BlockTest_411, LargeValues_411) {
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
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), large_val);

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), large_val);

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test keys with shared prefixes (exercises prefix compression)
TEST_F(BlockTest_411, SharedPrefixKeys_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"prefix_aaa", "1"},
      {"prefix_aab", "2"},
      {"prefix_aac", "3"},
      {"prefix_bbb", "4"},
      {"prefix_bbc", "5"},
  };
  std::string data = BuildBlockWithRestartInterval(kvs, 2);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Forward
  iter->SeekToFirst();
  for (size_t i = 0; i < kvs.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());

  // Backward
  iter->SeekToLast();
  for (int i = kvs.size() - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    if (i > 0) iter->Prev();
  }

  delete iter;
}

// Test corrupted block data (too small to be valid)
TEST_F(BlockTest_411, CorruptedBlockTooSmall_411) {
  // A valid block needs at least a trailer with num_restarts
  // A block with less than sizeof(uint32_t) bytes is invalid
  std::string data = "x";
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  // Should not be valid or should report error
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test Seek to first key exactly
TEST_F(BlockTest_411, SeekToExactFirstKey_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"},
      {"second", "2"},
      {"third", "3"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("first");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "first");
  EXPECT_EQ(iter->value().ToString(), "1");

  delete iter;
}

// Test Seek to last key exactly
TEST_F(BlockTest_411, SeekToExactLastKey_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"},
      {"second", "2"},
      {"third", "3"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("third");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "third");
  EXPECT_EQ(iter->value().ToString(), "3");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test repeated SeekToFirst
TEST_F(BlockTest_411, RepeatedSeekToFirst_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  for (int i = 0; i < 3; i++) {
    iter->SeekToFirst();
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), "a");
    EXPECT_EQ(iter->value().ToString(), "1");
  }

  delete iter;
}

// Test repeated SeekToLast
TEST_F(BlockTest_411, RepeatedSeekToLast_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
  };
  std::string data = BuildBlock(kvs);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  for (int i = 0; i < 3; i++) {
    iter->SeekToLast();
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), "b");
    EXPECT_EQ(iter->value().ToString(), "2");
  }

  delete iter;
}

// Test full backward then forward iteration
TEST_F(BlockTest_411, FullBackwardThenForward_411) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
      {"d", "4"},
      {"e", "5"},
  };
  std::string data = BuildBlockWithRestartInterval(kvs, 2);
  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Backward
  iter->SeekToLast();
  int count = kvs.size() - 1;
  while (iter->Valid() && count > 0) {
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    count--;
    iter->Prev();
  }
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), kvs[0].first);

  // Now forward from beginning
  iter->SeekToFirst();
  for (size_t i = 0; i < kvs.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

}  // namespace leveldb
