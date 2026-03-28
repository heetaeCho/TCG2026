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

class BlockTest_410 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  BlockContents BuildBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                           int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // Override restart interval if needed
    // BlockBuilder uses options.block_restart_interval but we set it through options
    Options opts;
    opts.block_restart_interval = restart_interval;
    BlockBuilder bb(&opts);
    for (const auto& kv : kvs) {
      bb.Add(kv.first, kv.second);
    }
    Slice raw = bb.Finish();
    // We need to copy the data since bb will be destroyed
    char* data = new char[raw.size()];
    memcpy(data, raw.data(), raw.size());
    BlockContents contents;
    contents.data = Slice(data, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    return contents;
  }
};

// Test that an iterator over an empty block is not valid
TEST_F(BlockTest_410, EmptyBlockIteratorNotValid_410) {
  BlockContents contents = BuildBlock({});
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test SeekToFirst on an empty block
TEST_F(BlockTest_410, EmptyBlockSeekToFirst_410) {
  BlockContents contents = BuildBlock({});
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on an empty block
TEST_F(BlockTest_410, EmptyBlockSeekToLast_410) {
  BlockContents contents = BuildBlock({});
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block
TEST_F(BlockTest_410, SingleEntry_410) {
  BlockContents contents = BuildBlock({{"key1", "value1"}});
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "value1");
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries with SeekToFirst and iteration
TEST_F(BlockTest_410, MultipleEntriesForwardIteration_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  for (size_t i = 0; i < kvs.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), kvs[i].first);
    ASSERT_EQ(iter->value().ToString(), kvs[i].second);
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test backward iteration with SeekToLast and Prev
TEST_F(BlockTest_410, MultipleEntriesBackwardIteration_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  for (int i = static_cast<int>(kvs.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), kvs[i].first);
    ASSERT_EQ(iter->value().ToString(), kvs[i].second);
    if (i > 0) iter->Prev();
  }
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek to an existing key
TEST_F(BlockTest_410, SeekExactKey_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val3");
  delete iter;
}

// Test Seek to a key between existing keys
TEST_F(BlockTest_410, SeekBetweenKeys_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"ccc", "val2"},
      {"eee", "val3"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val2");
  delete iter;
}

// Test Seek past all keys
TEST_F(BlockTest_410, SeekPastAllKeys_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek to key before all keys
TEST_F(BlockTest_410, SeekBeforeAllKeys_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"bbb", "val1"},
      {"ccc", "val2"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");
  delete iter;
}

// Test single entry SeekToLast
TEST_F(BlockTest_410, SingleEntrySeekToLast_410) {
  BlockContents contents = BuildBlock({{"only_key", "only_value"}});
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "only_key");
  ASSERT_EQ(iter->value().ToString(), "only_value");
  delete iter;
}

// Test status is ok after normal operations
TEST_F(BlockTest_410, StatusOkAfterNormalOps_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"},
  };
  BlockContents contents = BuildBlock(kvs);
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
  delete iter;
}

// Test with restart interval of 1 (every key is a restart point)
TEST_F(BlockTest_410, RestartIntervalOne_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
      {"delta_long_key", "4"},
  };
  // Sort keys since block builder expects sorted input
  std::sort(kvs.begin(), kvs.end());
  BlockContents contents = BuildBlock(kvs, 1);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Forward
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, static_cast<int>(kvs.size()));

  // Backward
  iter->SeekToLast();
  count = static_cast<int>(kvs.size()) - 1;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    count--;
    if (count >= 0) iter->Prev();
    else break;
  }
  delete iter;
}

// Test with many entries to test across multiple restart points
TEST_F(BlockTest_410, ManyEntries_410) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key_%06d", i);
    snprintf(val, sizeof(val), "val_%06d", i);
    kvs.push_back({key, val});
  }
  BlockContents contents = BuildBlock(kvs, 4);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Forward iteration
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, 100);

  // Seek in the middle
  iter->Seek("key_000050");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key_000050");
  ASSERT_EQ(iter->value().ToString(), "val_000050");

  // Seek between entries
  iter->Seek("key_000050a");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key_000051");

  delete iter;
}

// Test Next then Prev (mixed direction)
TEST_F(BlockTest_410, MixedDirectionIteration_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}, {"d", "4"}, {"e", "5"},
  };
  BlockContents contents = BuildBlock(kvs);
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
  iter->Next();
  ASSERT_EQ(iter->key().ToString(), "c");
  iter->Next();
  ASSERT_EQ(iter->key().ToString(), "d");
  delete iter;
}

// Test value with empty values
TEST_F(BlockTest_410, EmptyValues_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", ""},
      {"key2", ""},
      {"key3", "non_empty"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key2");
  ASSERT_EQ(iter->value().ToString(), "");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key3");
  ASSERT_EQ(iter->value().ToString(), "non_empty");

  delete iter;
}

// Test block size
TEST_F(BlockTest_410, BlockSize_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"k1", "v1"}, {"k2", "v2"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  ASSERT_GT(block.size(), 0u);
}

// Test Seek to the first key exactly
TEST_F(BlockTest_410, SeekToFirstKeyExact_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"}, {"second", "2"}, {"third", "3"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("first");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "first");
  ASSERT_EQ(iter->value().ToString(), "1");
  delete iter;
}

// Test Seek to the last key exactly
TEST_F(BlockTest_410, SeekToLastKeyExact_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"}, {"second", "2"}, {"third", "3"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("third");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "third");
  ASSERT_EQ(iter->value().ToString(), "3");
  delete iter;
}

// Test large values
TEST_F(BlockTest_410, LargeValues_410) {
  std::string large_val(10000, 'x');
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", large_val},
      {"key2", "small"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), large_val);
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key2");
  ASSERT_EQ(iter->value().ToString(), "small");
  delete iter;
}

// Test Prev from first entry makes iterator invalid
TEST_F(BlockTest_410, PrevFromFirstEntry_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Next past last entry makes iterator invalid
TEST_F(BlockTest_410, NextPastLastEntry_410) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"},
  };
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

}  // namespace leveldb
