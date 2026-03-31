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

class BlockTest_414 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  BlockContents BuildBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                           int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // BlockBuilder uses options.block_restart_interval internally
    // We'll use a custom options to control restart interval
    Options custom_options;
    custom_options.block_restart_interval = restart_interval;
    BlockBuilder custom_builder(&custom_options);

    for (const auto& kv : kvs) {
      custom_builder.Add(kv.first, kv.second);
    }
    Slice raw = custom_builder.Finish();

    // Make a copy of the data since BlockBuilder's buffer may go away
    char* data = new char[raw.size()];
    memcpy(data, raw.data(), raw.size());

    BlockContents contents;
    contents.data = Slice(data, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    return contents;
  }
};

// Test that an empty block produces an invalid iterator
TEST_F(BlockTest_414, EmptyBlockIteratorInvalid_414) {
  std::vector<std::pair<std::string, std::string>> kvs;
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToFirst on an empty block
TEST_F(BlockTest_414, EmptyBlockSeekToFirst_414) {
  std::vector<std::pair<std::string, std::string>> kvs;
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on an empty block
TEST_F(BlockTest_414, EmptyBlockSeekToLast_414) {
  std::vector<std::pair<std::string, std::string>> kvs;
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block
TEST_F(BlockTest_414, SingleEntry_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {{"key1", "value1"}};
  BlockContents contents = BuildBlock(kvs);
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

// Test SeekToFirst returns first entry
TEST_F(BlockTest_414, SeekToFirstReturnsFirstEntry_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "v1"}, {"bbb", "v2"}, {"ccc", "v3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");
  ASSERT_EQ(iter->value().ToString(), "v1");
  delete iter;
}

// Test SeekToLast returns last entry
TEST_F(BlockTest_414, SeekToLastReturnsLastEntry_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "v1"}, {"bbb", "v2"}, {"ccc", "v3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "v3");
  delete iter;
}

// Test forward iteration through all entries
TEST_F(BlockTest_414, ForwardIteration_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}, {"d", "4"}, {"e", "5"}};
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

// Test backward iteration through all entries
TEST_F(BlockTest_414, BackwardIteration_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}, {"d", "4"}, {"e", "5"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  for (int i = static_cast<int>(kvs.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), kvs[i].first);
    ASSERT_EQ(iter->value().ToString(), kvs[i].second);
    iter->Prev();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek to existing key
TEST_F(BlockTest_414, SeekExistingKey_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"apple", "v1"}, {"banana", "v2"}, {"cherry", "v3"}, {"date", "v4"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "banana");
  ASSERT_EQ(iter->value().ToString(), "v2");
  delete iter;
}

// Test Seek to non-existing key (should land on first key >= target)
TEST_F(BlockTest_414, SeekNonExistingKey_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"apple", "v1"}, {"cherry", "v3"}, {"date", "v4"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "cherry");
  ASSERT_EQ(iter->value().ToString(), "v3");
  delete iter;
}

// Test Seek past all keys
TEST_F(BlockTest_414, SeekPastAllKeys_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("z");
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek before all keys
TEST_F(BlockTest_414, SeekBeforeAllKeys_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"b", "1"}, {"c", "2"}, {"d", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("a");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "b");
  ASSERT_EQ(iter->value().ToString(), "1");
  delete iter;
}

// Test Prev from first element makes iterator invalid
TEST_F(BlockTest_414, PrevFromFirstElement_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Next from last element makes iterator invalid
TEST_F(BlockTest_414, NextFromLastElement_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test with many entries (multiple restart points)
TEST_F(BlockTest_414, ManyEntriesMultipleRestarts_414) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "value%06d", i);
    kvs.push_back({key, val});
  }
  // Use a small restart interval to create multiple restart points
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

  // Backward iteration
  iter->SeekToLast();
  count = 99;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), kvs[count].first);
    ASSERT_EQ(iter->value().ToString(), kvs[count].second);
    count--;
    iter->Prev();
  }
  ASSERT_EQ(count, -1);

  delete iter;
}

// Test Seek with multiple restart points
TEST_F(BlockTest_414, SeekWithMultipleRestartPoints_414) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 50; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i * 2);  // Even numbered keys
    snprintf(val, sizeof(val), "value%06d", i * 2);
    kvs.push_back({key, val});
  }
  BlockContents contents = BuildBlock(kvs, 2);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Seek to an odd-numbered key (doesn't exist), should land on next even
  char target[32];
  snprintf(target, sizeof(target), "key%06d", 25);
  iter->Seek(target);
  ASSERT_TRUE(iter->Valid());
  char expected_key[32];
  snprintf(expected_key, sizeof(expected_key), "key%06d", 26);
  ASSERT_EQ(iter->key().ToString(), expected_key);

  delete iter;
}

// Test status is OK for well-formed block
TEST_F(BlockTest_414, StatusOkForWellFormedBlock_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  while (iter->Valid()) {
    ASSERT_TRUE(iter->status().ok());
    iter->Next();
  }
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test single entry SeekToLast
TEST_F(BlockTest_414, SingleEntrySeekToLast_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {{"only", "one"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "only");
  ASSERT_EQ(iter->value().ToString(), "one");

  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry backward
TEST_F(BlockTest_414, SingleEntryPrev_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {{"only", "one"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test forward then backward (mixed iteration)
TEST_F(BlockTest_414, MixedForwardBackward_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}, {"d", "4"}, {"e", "5"}};
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

  iter->Prev();
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_EQ(iter->key().ToString(), "b");

  delete iter;
}

// Test Seek to exact first key
TEST_F(BlockTest_414, SeekToFirstKey_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "v1"}, {"bbb", "v2"}, {"ccc", "v3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");
  ASSERT_EQ(iter->value().ToString(), "v1");
  delete iter;
}

// Test Seek to exact last key
TEST_F(BlockTest_414, SeekToLastKey_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "v1"}, {"bbb", "v2"}, {"ccc", "v3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "v3");
  delete iter;
}

// Test with empty values
TEST_F(BlockTest_414, EmptyValues_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", ""}, {"b", ""}, {"c", ""}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");
  ASSERT_EQ(iter->value().ToString(), "");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "b");
  ASSERT_EQ(iter->value().ToString(), "");

  delete iter;
}

// Test with long keys and values
TEST_F(BlockTest_414, LongKeysAndValues_414) {
  std::string long_key(1000, 'k');
  std::string long_val(5000, 'v');
  std::vector<std::pair<std::string, std::string>> kvs = {
      {long_key + "1", long_val + "1"},
      {long_key + "2", long_val + "2"},
      {long_key + "3", long_val + "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), long_key + "1");
  ASSERT_EQ(iter->value().ToString(), long_val + "1");

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), long_key + "3");
  ASSERT_EQ(iter->value().ToString(), long_val + "3");

  delete iter;
}

// Test block size
TEST_F(BlockTest_414, BlockSize_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);

  // Block should have a non-zero size
  ASSERT_GT(block.size(), 0u);
}

// Test restart_interval = 1 (every key is a restart point)
TEST_F(BlockTest_414, RestartIntervalOne_414) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 20; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    kvs.push_back({key, val});
  }
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
  ASSERT_EQ(count, 20);

  // Seek in the middle
  iter->Seek("key000010");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key000010");

  // Backward from seek point
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key000009");

  delete iter;
}

// Test SeekToFirst followed by SeekToLast
TEST_F(BlockTest_414, SeekToFirstThenSeekToLast_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  delete iter;
}

// Test two entries
TEST_F(BlockTest_414, TwoEntries_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"}, {"second", "2"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "first");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "second");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "first");

  delete iter;
}

// Test Seek on empty key string
TEST_F(BlockTest_414, SeekEmptyString_414) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"}, {"b", "2"}, {"c", "3"}};
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("");
  ASSERT_TRUE(iter->Valid());
  // Empty string is before "a" in bytewise comparison
  ASSERT_EQ(iter->key().ToString(), "a");

  delete iter;
}

}  // namespace leveldb
