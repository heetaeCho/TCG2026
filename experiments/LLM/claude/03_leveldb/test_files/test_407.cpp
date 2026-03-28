#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class BlockTest_407 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  BlockContents BuildBlock(const std::vector<std::pair<std::string, std::string>>& entries,
                           int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // Override restart interval if needed
    // BlockBuilder uses options.block_restart_interval which defaults to 16
    
    for (const auto& entry : entries) {
      builder.Add(entry.first, entry.second);
    }
    
    Slice raw = builder.Finish();
    
    // Copy data so it persists
    char* data = new char[raw.size()];
    memcpy(data, raw.data(), raw.size());
    
    BlockContents contents;
    contents.data = Slice(data, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    
    return contents;
  }
  
  // Build block with custom restart interval
  BlockContents BuildBlockWithRestartInterval(
      const std::vector<std::pair<std::string, std::string>>& entries,
      int restart_interval) {
    Options options;
    options.comparator = BytewiseComparator();
    options.block_restart_interval = restart_interval;
    BlockBuilder builder(&options);
    
    for (const auto& entry : entries) {
      builder.Add(entry.first, entry.second);
    }
    
    Slice raw = builder.Finish();
    
    char* data = new char[raw.size()];
    memcpy(data, raw.data(), raw.size());
    
    BlockContents contents;
    contents.data = Slice(data, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    
    return contents;
  }
};

// Test that an iterator over an empty block is not valid initially
TEST_F(BlockTest_407, EmptyBlockIteratorNotValid_407) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  EXPECT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test that SeekToFirst on empty block leaves iterator invalid
TEST_F(BlockTest_407, EmptyBlockSeekToFirst_407) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that SeekToLast on empty block leaves iterator invalid
TEST_F(BlockTest_407, EmptyBlockSeekToLast_407) {
  std::vector<std::pair<std::string, std::string>> entries;
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block - SeekToFirst
TEST_F(BlockTest_407, SingleEntrySeekToFirst_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", "value1"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ("value1", iter->value().ToString());
  
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block - SeekToLast
TEST_F(BlockTest_407, SingleEntrySeekToLast_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", "value1"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ("value1", iter->value().ToString());
  delete iter;
}

// Test multiple entries - forward iteration
TEST_F(BlockTest_407, MultipleEntriesForwardIteration_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"},
    {"eee", "val5"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Next();
  }
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries - backward iteration
TEST_F(BlockTest_407, MultipleEntriesBackwardIteration_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"},
    {"eee", "val5"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  
  for (int i = entries.size() - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Prev();
  }
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek to existing key
TEST_F(BlockTest_407, SeekToExistingKey_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"},
    {"eee", "val5"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());
  EXPECT_EQ("val3", iter->value().ToString());
  delete iter;
}

// Test Seek to non-existing key (should land on next key)
TEST_F(BlockTest_407, SeekToNonExistingKey_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"ccc", "val3"},
    {"eee", "val5"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());
  EXPECT_EQ("val3", iter->value().ToString());
  delete iter;
}

// Test Seek past all keys
TEST_F(BlockTest_407, SeekPastAllKeys_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek to key before all entries
TEST_F(BlockTest_407, SeekBeforeAllKeys_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"}
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());
  EXPECT_EQ("val2", iter->value().ToString());
  delete iter;
}

// Test Prev after SeekToFirst makes iterator invalid
TEST_F(BlockTest_407, PrevAtBeginning_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test Next after SeekToLast makes iterator invalid
TEST_F(BlockTest_407, NextAtEnd_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test with restart interval of 1 (no prefix compression)
TEST_F(BlockTest_407, RestartIntervalOne_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"abc", "v1"},
    {"abd", "v2"},
    {"abe", "v3"},
    {"abf", "v4"},
  };
  BlockContents contents = BuildBlockWithRestartInterval(entries, 1);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Next();
  }
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test with restart interval of 2
TEST_F(BlockTest_407, RestartIntervalTwo_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"abc", "v1"},
    {"abd", "v2"},
    {"abe", "v3"},
    {"abf", "v4"},
    {"abg", "v5"},
  };
  BlockContents contents = BuildBlockWithRestartInterval(entries, 2);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  // Test forward iteration
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    iter->Next();
  }
  EXPECT_FALSE(iter->Valid());
  
  // Test backward iteration
  iter->SeekToLast();
  for (int i = entries.size() - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    iter->Prev();
  }
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Seek with many entries spanning multiple restart points
TEST_F(BlockTest_407, SeekWithManyEntries_407) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%06d", i * 2);  // even numbers
    snprintf(val, sizeof(val), "val%06d", i * 2);
    entries.push_back({key, val});
  }
  BlockContents contents = BuildBlockWithRestartInterval(entries, 4);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  // Seek to an existing key in the middle
  iter->Seek("key000050");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000050", iter->key().ToString());
  
  // Seek to a non-existing key (odd number between entries)
  iter->Seek("key000051");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000052", iter->key().ToString());
  
  // Seek to first key
  iter->Seek("key000000");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000000", iter->key().ToString());
  
  // Seek past last key
  iter->Seek("key999999");
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test iterator status is ok during normal operation
TEST_F(BlockTest_407, StatusOkDuringNormalOperation_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", "val1"},
    {"key2", "val2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  EXPECT_TRUE(iter->status().ok());
  
  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());
  
  iter->Next();
  EXPECT_TRUE(iter->status().ok());
  
  iter->SeekToLast();
  EXPECT_TRUE(iter->status().ok());
  
  iter->Prev();
  EXPECT_TRUE(iter->status().ok());
  
  delete iter;
}

// Test that newly created iterator (before any seek) is not valid
TEST_F(BlockTest_407, NewIteratorNotValid_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", "val1"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test forward then backward iteration (mixed direction)
TEST_F(BlockTest_407, MixedDirectionIteration_407) {
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
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  
  // Now go backward
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  
  // Forward again
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());
  
  delete iter;
}

// Test Seek to the first key exactly
TEST_F(BlockTest_407, SeekToFirstKeyExact_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"alpha", "v1"},
    {"beta", "v2"},
    {"gamma", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("alpha");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("alpha", iter->key().ToString());
  EXPECT_EQ("v1", iter->value().ToString());
  delete iter;
}

// Test Seek to the last key exactly
TEST_F(BlockTest_407, SeekToLastKeyExact_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"alpha", "v1"},
    {"beta", "v2"},
    {"gamma", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->Seek("gamma");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("gamma", iter->key().ToString());
  EXPECT_EQ("v3", iter->value().ToString());
  delete iter;
}

// Test with empty values
TEST_F(BlockTest_407, EmptyValues_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", ""},
    {"key2", ""},
    {"key3", ""},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ("", iter->value().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key2", iter->key().ToString());
  EXPECT_EQ("", iter->value().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key3", iter->key().ToString());
  EXPECT_EQ("", iter->value().ToString());
  
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test with large values
TEST_F(BlockTest_407, LargeValues_407) {
  std::string large_val(10000, 'x');
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", large_val},
    {"key2", large_val},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ(large_val, iter->value().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key2", iter->key().ToString());
  EXPECT_EQ(large_val, iter->value().ToString());
  
  delete iter;
}

// Test with keys sharing long common prefixes
TEST_F(BlockTest_407, SharedPrefixKeys_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"abcdefghijklmnop_1", "v1"},
    {"abcdefghijklmnop_2", "v2"},
    {"abcdefghijklmnop_3", "v3"},
    {"abcdefghijklmnop_4", "v4"},
  };
  BlockContents contents = BuildBlockWithRestartInterval(entries, 2);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->Seek("abcdefghijklmnop_3");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("abcdefghijklmnop_3", iter->key().ToString());
  EXPECT_EQ("v3", iter->value().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("abcdefghijklmnop_2", iter->key().ToString());
  
  delete iter;
}

// Test block size
TEST_F(BlockTest_407, BlockSize_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", "val1"},
    {"key2", "val2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  // Block should report a positive size
  EXPECT_GT(block.size(), 0u);
}

// Test iteration count matches number of entries
TEST_F(BlockTest_407, IterationCountMatchesEntries_407) {
  const int num_entries = 50;
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < num_entries; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "key%04d", i);
    snprintf(val, sizeof(val), "val%04d", i);
    entries.push_back({key, val});
  }
  
  BlockContents contents = BuildBlockWithRestartInterval(entries, 8);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(num_entries, count);
  EXPECT_TRUE(iter->status().ok());
  
  // Also count backward
  count = 0;
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    count++;
  }
  EXPECT_EQ(num_entries, count);
  EXPECT_TRUE(iter->status().ok());
  
  delete iter;
}

// Test Seek then Next produces correct sequence
TEST_F(BlockTest_407, SeekThenNext_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"a", "1"},
    {"c", "3"},
    {"e", "5"},
    {"g", "7"},
    {"i", "9"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  // Seek to "d" which doesn't exist, should land on "e"
  iter->Seek("d");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("e", iter->key().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("g", iter->key().ToString());
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("i", iter->key().ToString());
  
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Seek then Prev
TEST_F(BlockTest_407, SeekThenPrev_407) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"a", "1"},
    {"c", "3"},
    {"e", "5"},
    {"g", "7"},
    {"i", "9"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->Seek("e");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("e", iter->key().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

}  // namespace leveldb
