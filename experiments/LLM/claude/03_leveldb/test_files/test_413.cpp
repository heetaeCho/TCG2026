#include "gtest/gtest.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class BlockTest_413 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  BlockContents BuildBlock(const std::vector<std::pair<std::string, std::string>>& entries,
                           int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // Override restart interval if needed
    // BlockBuilder uses options.block_restart_interval
    Options opts;
    opts.block_restart_interval = restart_interval;
    BlockBuilder bb(&opts);
    for (const auto& entry : entries) {
      bb.Add(entry.first, entry.second);
    }
    Slice raw = bb.Finish();
    // Copy data so it persists
    char* data = new char[raw.size()];
    memcpy(data, raw.data(), raw.size());
    BlockContents contents;
    contents.data = Slice(data, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    return contents;
  }

  Iterator* NewBlockIterator(Block* block) {
    return block->NewIterator(BytewiseComparator());
  }
};

// Test seeking to an existing key
TEST_F(BlockTest_413, SeekExistingKey_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "v1"},
      {"banana", "v2"},
      {"cherry", "v3"},
      {"date", "v4"},
      {"elderberry", "v5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("cherry");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("cherry", iter->key().ToString());
  EXPECT_EQ("v3", iter->value().ToString());

  delete iter;
}

// Test seeking to a key that doesn't exist - should land on next key
TEST_F(BlockTest_413, SeekNonExistingKey_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "v1"},
      {"banana", "v2"},
      {"cherry", "v3"},
      {"date", "v4"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("blueberry");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("cherry", iter->key().ToString());

  delete iter;
}

// Test seeking to first key
TEST_F(BlockTest_413, SeekToFirstKey_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "v1"},
      {"banana", "v2"},
      {"cherry", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("apple");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("apple", iter->key().ToString());
  EXPECT_EQ("v1", iter->value().ToString());

  delete iter;
}

// Test seeking to last key
TEST_F(BlockTest_413, SeekToLastKey_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "v1"},
      {"banana", "v2"},
      {"cherry", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("cherry");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("cherry", iter->key().ToString());
  EXPECT_EQ("v3", iter->value().ToString());

  delete iter;
}

// Test seeking past all keys
TEST_F(BlockTest_413, SeekPastAllKeys_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "v1"},
      {"banana", "v2"},
      {"cherry", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("zebra");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test seeking before all keys
TEST_F(BlockTest_413, SeekBeforeAllKeys_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"banana", "v1"},
      {"cherry", "v2"},
      {"date", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("banana", iter->key().ToString());
  EXPECT_EQ("v1", iter->value().ToString());

  delete iter;
}

// Test seeking with single entry block
TEST_F(BlockTest_413, SeekSingleEntry_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"only", "v1"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("only");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("only", iter->key().ToString());
  EXPECT_EQ("v1", iter->value().ToString());

  delete iter;
}

// Test seeking past single entry
TEST_F(BlockTest_413, SeekPastSingleEntry_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"only", "v1"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("zoo");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test seeking before single entry
TEST_F(BlockTest_413, SeekBeforeSingleEntry_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"only", "v1"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("only", iter->key().ToString());

  delete iter;
}

// Test multiple seeks on same iterator
TEST_F(BlockTest_413, MultipleSeeks_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
      {"d", "v4"},
      {"e", "v5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("c");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Seek("a");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  iter->Seek("e");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("e", iter->key().ToString());

  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  delete iter;
}

// Test seek then Next
TEST_F(BlockTest_413, SeekThenNext_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
      {"d", "v4"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("d", iter->key().ToString());

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test seek then Prev
TEST_F(BlockTest_413, SeekThenPrev_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
      {"d", "v4"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("c");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  delete iter;
}

// Test SeekToFirst
TEST_F(BlockTest_413, SeekToFirst_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  EXPECT_EQ("v1", iter->value().ToString());

  delete iter;
}

// Test SeekToLast
TEST_F(BlockTest_413, SeekToLast_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  EXPECT_EQ("v3", iter->value().ToString());

  delete iter;
}

// Test with many entries to exercise multiple restart points
TEST_F(BlockTest_413, SeekWithManyEntries_413) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    entries.push_back({key, val});
  }
  // Use small restart interval to create many restart points
  BlockContents contents = BuildBlock(entries, 4);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  // Seek to middle
  iter->Seek("key000050");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000050", iter->key().ToString());
  EXPECT_EQ("val000050", iter->value().ToString());

  // Seek to something between entries
  iter->Seek("key000050x");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000051", iter->key().ToString());

  // Seek to first
  iter->Seek("key000000");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000000", iter->key().ToString());

  // Seek to last
  iter->Seek("key000099");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000099", iter->key().ToString());

  // Seek past end
  iter->Seek("key000100");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test seek forward from current position (left = restart_index_ case)
TEST_F(BlockTest_413, SeekForwardFromCurrentPosition_413) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 50; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%04d", i);
    snprintf(val, sizeof(val), "val%04d", i);
    entries.push_back({key, val});
  }
  BlockContents contents = BuildBlock(entries, 4);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  // Position at key0010
  iter->Seek("key0010");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0010", iter->key().ToString());

  // Seek forward
  iter->Seek("key0020");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0020", iter->key().ToString());

  delete iter;
}

// Test seek backward from current position (right = restart_index_ case)
TEST_F(BlockTest_413, SeekBackwardFromCurrentPosition_413) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 50; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%04d", i);
    snprintf(val, sizeof(val), "val%04d", i);
    entries.push_back({key, val});
  }
  BlockContents contents = BuildBlock(entries, 4);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  // Position at key0040
  iter->Seek("key0040");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0040", iter->key().ToString());

  // Seek backward
  iter->Seek("key0010");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0010", iter->key().ToString());

  delete iter;
}

// Test seek to same key (early return path)
TEST_F(BlockTest_413, SeekToSameKey_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  // Seek to same key again
  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());
  EXPECT_EQ("v2", iter->value().ToString());

  delete iter;
}

// Test iterator status is ok on normal operation
TEST_F(BlockTest_413, StatusOkOnNormalOperation_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("a");
  ASSERT_TRUE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test empty string key seek
TEST_F(BlockTest_413, SeekEmptyStringKey_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"", "empty_key_value"},
      {"a", "v1"},
      {"b", "v2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("", iter->key().ToString());
  EXPECT_EQ("empty_key_value", iter->value().ToString());

  delete iter;
}

// Test full iteration after seek
TEST_F(BlockTest_413, FullIterationAfterSeek_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
      {"d", "v4"},
      {"e", "v5"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("c");
  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Next();
  }
  ASSERT_EQ(3u, keys.size());
  EXPECT_EQ("c", keys[0]);
  EXPECT_EQ("d", keys[1]);
  EXPECT_EQ("e", keys[2]);

  delete iter;
}

// Test with restart interval of 1 (every key is a restart point)
TEST_F(BlockTest_413, SeekWithRestartIntervalOne_413) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 20; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%04d", i);
    snprintf(val, sizeof(val), "val%04d", i);
    entries.push_back({key, val});
  }
  BlockContents contents = BuildBlock(entries, 1);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("key0010");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0010", iter->key().ToString());

  iter->Seek("key0005");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0005", iter->key().ToString());

  delete iter;
}

// Test with large values
TEST_F(BlockTest_413, SeekWithLargeValues_413) {
  std::vector<std::pair<std::string, std::string>> entries;
  std::string large_value(1000, 'x');
  for (int i = 0; i < 10; i++) {
    char key[16];
    snprintf(key, sizeof(key), "key%04d", i);
    entries.push_back({key, large_value});
  }
  BlockContents contents = BuildBlock(entries, 2);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  iter->Seek("key0005");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key0005", iter->key().ToString());
  EXPECT_EQ(large_value, iter->value().ToString());

  delete iter;
}

// Test iterator initially not valid
TEST_F(BlockTest_413, IteratorInitiallyNotValid_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test SeekToFirst then iterate all
TEST_F(BlockTest_413, SeekToFirstIterateAll_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(3, count);

  delete iter;
}

// Test SeekToLast then iterate backward
TEST_F(BlockTest_413, SeekToLastIterateBackward_413) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
  };
  BlockContents contents = BuildBlock(entries);
  Block block(contents);
  Iterator* iter = NewBlockIterator(&block);

  int count = 0;
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    count++;
  }
  EXPECT_EQ(3, count);

  delete iter;
}

}  // namespace leveldb
