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

// Helper function to build a block from key-value pairs
static std::string BuildBlock(const std::vector<std::pair<std::string, std::string>>& entries,
                               int restart_interval = 16) {
  Options options;
  options.comparator = BytewiseComparator();
  BlockBuilder builder(&options);
  // Note: BlockBuilder uses options.block_restart_interval which defaults to 16
  // We need to set it explicitly
  Options opts;
  opts.block_restart_interval = restart_interval;
  BlockBuilder bb(&opts);
  for (const auto& entry : entries) {
    bb.Add(Slice(entry.first), Slice(entry.second));
  }
  Slice raw = bb.Finish();
  return std::string(raw.data(), raw.size());
}

class BlockIterTest_415 : public ::testing::Test {
 protected:
  void SetUp() override {
    comparator_ = BytewiseComparator();
  }

  Iterator* NewBlockIterator(const std::string& block_data) {
    // Block takes ownership of BlockContents data
    // We need to create a proper Block
    BlockContents contents;
    contents.data = Slice(block_data);
    contents.cachable = false;
    contents.heap_allocated = false;
    block_.reset(new Block(contents));
    return block_->NewIterator(comparator_);
  }

  const Comparator* comparator_;
  std::unique_ptr<Block> block_;
};

// Test that an iterator over an empty block is not valid
TEST_F(BlockIterTest_415, EmptyBlockIteratorNotValid_415) {
  std::string data = BuildBlock({});
  Iterator* iter = NewBlockIterator(data);
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToFirst on empty block
TEST_F(BlockIterTest_415, SeekToFirstOnEmptyBlock_415) {
  std::string data = BuildBlock({});
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on empty block
TEST_F(BlockIterTest_415, SeekToLastOnEmptyBlock_415) {
  std::string data = BuildBlock({});
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test single entry block: SeekToFirst
TEST_F(BlockIterTest_415, SingleEntrySeekToFirst_415) {
  std::string data = BuildBlock({{"key1", "value1"}});
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ("value1", iter->value().ToString());
  delete iter;
}

// Test single entry block: SeekToLast
TEST_F(BlockIterTest_415, SingleEntrySeekToLast_415) {
  std::string data = BuildBlock({{"key1", "value1"}});
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ("value1", iter->value().ToString());
  delete iter;
}

// Test single entry: Next makes it invalid
TEST_F(BlockIterTest_415, SingleEntryNextInvalidates_415) {
  std::string data = BuildBlock({{"key1", "value1"}});
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries: forward iteration
TEST_F(BlockIterTest_415, MultipleEntriesForwardIteration_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries: backward iteration
TEST_F(BlockIterTest_415, MultipleEntriesBackwardIteration_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToLast();
  for (int i = static_cast<int>(entries.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Prev();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek: exact match
TEST_F(BlockIterTest_415, SeekExactMatch_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());
  EXPECT_EQ("val2", iter->value().ToString());
  delete iter;
}

// Test Seek: key between entries
TEST_F(BlockIterTest_415, SeekBetweenEntries_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"ccc", "val2"},
      {"eee", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());
  EXPECT_EQ("val2", iter->value().ToString());
  delete iter;
}

// Test Seek: key before all entries
TEST_F(BlockIterTest_415, SeekBeforeAllEntries_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"bbb", "val1"},
      {"ccc", "val2"},
      {"ddd", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());
  EXPECT_EQ("val1", iter->value().ToString());
  delete iter;
}

// Test Seek: key after all entries
TEST_F(BlockIterTest_415, SeekAfterAllEntries_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast then Prev
TEST_F(BlockIterTest_415, SeekToLastThenPrev_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test iteration with restart_interval = 1 (every entry is a restart point)
TEST_F(BlockIterTest_415, RestartIntervalOne_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  std::string data = BuildBlock(entries, 1);
  Iterator* iter = NewBlockIterator(data);

  // Forward
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());

  // Backward
  iter->SeekToLast();
  for (int i = static_cast<int>(entries.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Prev();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test iteration with restart_interval = 2
TEST_F(BlockIterTest_415, RestartIntervalTwo_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"aab", "val2"},
      {"bbb", "val3"},
      {"bbc", "val4"},
      {"ccc", "val5"},
  };
  std::string data = BuildBlock(entries, 2);
  Iterator* iter = NewBlockIterator(data);

  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast with many entries and restart_interval = 2
TEST_F(BlockIterTest_415, SeekToLastManyEntries_415) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    entries.push_back({std::string(key), std::string(val)});
  }
  std::string data = BuildBlock(entries, 2);
  Iterator* iter = NewBlockIterator(data);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(entries.back().first, iter->key().ToString());
  EXPECT_EQ(entries.back().second, iter->value().ToString());
  delete iter;
}

// Test Seek with many entries
TEST_F(BlockIterTest_415, SeekManyEntries_415) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[16];
    char val[16];
    snprintf(key, sizeof(key), "key%06d", i * 2);
    snprintf(val, sizeof(val), "val%06d", i * 2);
    entries.push_back({std::string(key), std::string(val)});
  }
  std::string data = BuildBlock(entries, 4);
  Iterator* iter = NewBlockIterator(data);

  // Seek to an existing key in the middle
  iter->Seek("key000050");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000050", iter->key().ToString());

  // Seek to a key that doesn't exist (odd number, should land on next even)
  iter->Seek("key000051");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key000052", iter->key().ToString());

  delete iter;
}

// Test status is OK during normal iteration
TEST_F(BlockIterTest_415, StatusOkDuringNormalIteration_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test forward then backward (mixed iteration)
TEST_F(BlockIterTest_415, MixedForwardBackward_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
      {"eee", "val5"},
  };
  std::string data = BuildBlock(entries, 2);
  Iterator* iter = NewBlockIterator(data);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());

  // Now go back
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());

  // Go forward again
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());

  delete iter;
}

// Test SeekToFirst then SeekToLast alternation
TEST_F(BlockIterTest_415, AlternateSeekToFirstAndLast_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"first", "val1"},
      {"middle", "val2"},
      {"last", "val3"},
  };
  // Note: keys must be sorted. "first" < "last" < "middle" lexicographically
  // Let's use properly sorted keys
  std::vector<std::pair<std::string, std::string>> sorted_entries = {
      {"aaa", "val1"},
      {"mmm", "val2"},
      {"zzz", "val3"},
  };
  std::string data = BuildBlock(sorted_entries);
  Iterator* iter = NewBlockIterator(data);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("zzz", iter->key().ToString());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());

  delete iter;
}

// Test Seek to first key
TEST_F(BlockIterTest_415, SeekToFirstKey_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());
  EXPECT_EQ("val1", iter->value().ToString());
  delete iter;
}

// Test Seek to last key
TEST_F(BlockIterTest_415, SeekToLastKey_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());
  EXPECT_EQ("val3", iter->value().ToString());
  delete iter;
}

// Test with large values
TEST_F(BlockIterTest_415, LargeValues_415) {
  std::string large_val(10000, 'x');
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", large_val},
      {"key2", large_val},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
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

// Test with keys sharing common prefixes (prefix compression exercised)
TEST_F(BlockIterTest_415, SharedPrefixKeys_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"prefix_aaa", "val1"},
      {"prefix_aab", "val2"},
      {"prefix_aac", "val3"},
      {"prefix_bbb", "val4"},
      {"prefix_bbc", "val5"},
  };
  std::string data = BuildBlock(entries, 16);
  Iterator* iter = NewBlockIterator(data);

  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ(entries[i].second, iter->value().ToString());
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());

  // Also test backward
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("prefix_bbc", iter->key().ToString());

  delete iter;
}

// Test two entries: Prev from second to first
TEST_F(BlockIterTest_415, TwoEntriesPrev_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test empty values
TEST_F(BlockIterTest_415, EmptyValues_415) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", ""},
      {"key2", ""},
      {"key3", ""},
  };
  std::string data = BuildBlock(entries);
  Iterator* iter = NewBlockIterator(data);
  iter->SeekToFirst();
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(entries[i].first, iter->key().ToString());
    EXPECT_EQ("", iter->value().ToString());
    iter->Next();
  }
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

}  // namespace leveldb
