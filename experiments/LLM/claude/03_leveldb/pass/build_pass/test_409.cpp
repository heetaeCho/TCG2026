#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "table/format.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class BlockTest_409 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  BlockContents BuildBlock(const std::vector<std::pair<std::string, std::string>>& entries,
                           int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // Note: BlockBuilder uses Options::block_restart_interval
    // We need to set it properly
    Options opts;
    opts.block_restart_interval = restart_interval;
    BlockBuilder bb(&opts);
    for (const auto& entry : entries) {
      bb.Add(entry.first, entry.second);
    }
    Slice raw = bb.Finish();
    // Make a copy of the data
    char* buf = new char[raw.size()];
    memcpy(buf, raw.data(), raw.size());
    BlockContents contents;
    contents.data = Slice(buf, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    return contents;
  }
};

// Test that an empty block produces an invalid iterator
TEST_F(BlockTest_409, EmptyBlockIteratorInvalid_409) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToFirst on empty block
TEST_F(BlockTest_409, EmptyBlockSeekToFirst_409) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on empty block
TEST_F(BlockTest_409, EmptyBlockSeekToLast_409) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block - SeekToFirst
TEST_F(BlockTest_409, SingleEntrySeekToFirst_409) {
  std::vector<std::pair<std::string, std::string>> entries = {{"key1", "value1"}};
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "value1");
  delete iter;
}

// Test single entry block - SeekToLast
TEST_F(BlockTest_409, SingleEntrySeekToLast_409) {
  std::vector<std::pair<std::string, std::string>> entries = {{"key1", "value1"}};
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "value1");
  delete iter;
}

// Test single entry - Next makes it invalid
TEST_F(BlockTest_409, SingleEntryNextInvalidates_409) {
  std::vector<std::pair<std::string, std::string>> entries = {{"key1", "value1"}};
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry - Prev from first makes it invalid
TEST_F(BlockTest_409, SingleEntryPrevInvalidates_409) {
  std::vector<std::pair<std::string, std::string>> entries = {{"key1", "value1"}};
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries - forward iteration
TEST_F(BlockTest_409, MultipleEntriesForwardIteration_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), entries[i].first);
    ASSERT_EQ(iter->value().ToString(), entries[i].second);
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries - backward iteration
TEST_F(BlockTest_409, MultipleEntriesBackwardIteration_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  for (int i = entries.size() - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), entries[i].first);
    ASSERT_EQ(iter->value().ToString(), entries[i].second);
    iter->Prev();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek - exact match
TEST_F(BlockTest_409, SeekExactMatch_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val3");
  delete iter;
}

// Test Seek - lands on next key when target is between entries
TEST_F(BlockTest_409, SeekBetweenEntries_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"ccc", "val2"},
      {"eee", "val3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val2");
  delete iter;
}

// Test Seek - target before all entries
TEST_F(BlockTest_409, SeekBeforeAllEntries_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"bbb", "val1"},
      {"ccc", "val2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");
  delete iter;
}

// Test Seek - target after all entries
TEST_F(BlockTest_409, SeekAfterAllEntries_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek to first key
TEST_F(BlockTest_409, SeekToFirstKey_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");
  ASSERT_EQ(iter->value().ToString(), "val1");
  delete iter;
}

// Test Seek to last key
TEST_F(BlockTest_409, SeekToLastKey_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val3");
  delete iter;
}

// Test status is OK during normal iteration
TEST_F(BlockTest_409, StatusOKDuringNormalIteration_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
      {"key2", "value2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test with many entries and small restart interval
TEST_F(BlockTest_409, ManyEntriesSmallRestartInterval_409) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    entries.push_back({key, val});
  }
  BlockContents contents = BuildBlock(entries, 2);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Forward iteration
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), entries[count].first);
    ASSERT_EQ(iter->value().ToString(), entries[count].second);
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, 100);

  // Backward iteration
  iter->SeekToLast();
  count = 99;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), entries[count].first);
    ASSERT_EQ(iter->value().ToString(), entries[count].second);
    count--;
    iter->Prev();
  }
  ASSERT_EQ(count, -1);
  delete iter;
}

// Test Seek with many entries
TEST_F(BlockTest_409, SeekManyEntries_409) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%06d", i * 2);  // Even numbered keys
    snprintf(val, sizeof(val), "val%06d", i * 2);
    entries.push_back({key, val});
  }
  BlockContents contents = BuildBlock(entries, 4);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Seek to an odd-numbered key should land on next even
  char target[32];
  snprintf(target, sizeof(target), "key%06d", 51);  // odd, between key000050 and key000052
  iter->Seek(target);
  ASSERT_TRUE(iter->Valid());
  char expected[32];
  snprintf(expected, sizeof(expected), "key%06d", 52);
  ASSERT_EQ(iter->key().ToString(), expected);
  delete iter;
}

// Test block size
TEST_F(BlockTest_409, BlockSize_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  ASSERT_GT(block.size(), 0u);
  delete block.NewIterator(BytewiseComparator());
}

// Test forward then backward
TEST_F(BlockTest_409, ForwardThenBackward_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
      {"d", "4"},
      {"e", "5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Go forward to "c"
  iter->SeekToFirst();
  iter->Next();
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");

  // Now go backward
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test backward then forward
TEST_F(BlockTest_409, BackwardThenForward_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
      {"d", "4"},
      {"e", "5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  iter->Prev();
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "d");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "e");

  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test restart interval of 1 (every key is a restart point)
TEST_F(BlockTest_409, RestartIntervalOne_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  BlockContents contents = BuildBlock(entries, 1);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_EQ(iter->key().ToString(), entries[count].first);
    ASSERT_EQ(iter->value().ToString(), entries[count].second);
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, 4);

  // Also test Prev
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ddd");
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  delete iter;
}

// Test with empty key and value
TEST_F(BlockTest_409, EmptyKeyAndValue_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"", ""},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "");
  ASSERT_EQ(iter->value().ToString(), "");
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test with empty values
TEST_F(BlockTest_409, EmptyValues_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", ""},
      {"key2", ""},
      {"key3", ""},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), entries[i].first);
    ASSERT_EQ(iter->value().ToString(), "");
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test with long keys and values
TEST_F(BlockTest_409, LongKeysAndValues_409) {
  std::string longkey(1000, 'k');
  std::string longval(2000, 'v');
  std::vector<std::pair<std::string, std::string>> entries = {
      {longkey + "1", longval + "1"},
      {longkey + "2", longval + "2"},
      {longkey + "3", longval + "3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    ASSERT_EQ(iter->key().ToString(), entries[i].first);
    ASSERT_EQ(iter->value().ToString(), entries[i].second);
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek on empty block
TEST_F(BlockTest_409, SeekOnEmptyBlock_409) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("anything");
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test keys with common prefix (to exercise prefix compression)
TEST_F(BlockTest_409, CommonPrefixKeys_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"prefix_aaa", "val1"},
      {"prefix_aab", "val2"},
      {"prefix_aac", "val3"},
      {"prefix_bbb", "val4"},
      {"prefix_bbc", "val5"},
  };
  BlockContents contents = BuildBlock(entries, 2);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Seek to middle
  iter->Seek("prefix_aab");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "prefix_aab");
  ASSERT_EQ(iter->value().ToString(), "val2");

  // Try backward
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "prefix_aaa");
  ASSERT_EQ(iter->value().ToString(), "val1");

  delete iter;
}

// Test that corrupted block data is handled
TEST_F(BlockTest_409, CorruptedBlockData_409) {
  // Build a valid block first, then corrupt it
  // Create minimal corrupt data: just put a restart count of 0
  // This might result in an error state or empty iteration
  char data[sizeof(uint32_t)];
  EncodeFixed32(data, 0);  // num_restarts = 0
  BlockContents contents;
  contents.data = Slice(data, sizeof(data));
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  // With 0 restart points, iterator should not be valid
  // (the exact behavior depends on implementation, but shouldn't crash)
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple seeks
TEST_F(BlockTest_409, MultipleSeeks_409) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "1"},
      {"c", "2"},
      {"e", "3"},
      {"g", "4"},
      {"i", "5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("e");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "e");

  iter->Seek("a");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->Seek("i");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "i");

  iter->Seek("d");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "e");

  delete iter;
}

}  // namespace leveldb
