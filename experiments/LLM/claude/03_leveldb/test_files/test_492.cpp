#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "table/block.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// Helper function to build a block with given key-value pairs
// Block format:
//   entries: shared_key_len | unshared_key_len | value_len | key_delta | value
//   restart points (array of uint32_t offsets)
//   num_restarts (uint32_t)
class BlockBuilderHelper {
 public:
  // Build a raw block from key-value pairs with a given restart_interval
  static std::string BuildBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                                 int restart_interval = 1) {
    std::string result;
    std::vector<uint32_t> restarts;
    std::string last_key;

    for (size_t i = 0; i < kvs.size(); i++) {
      const std::string& key = kvs[i].first;
      const std::string& value = kvs[i].second;

      uint32_t shared = 0;
      if (i % restart_interval == 0) {
        restarts.push_back(static_cast<uint32_t>(result.size()));
        shared = 0;
      } else {
        // Compute shared prefix length
        size_t min_len = std::min(last_key.size(), key.size());
        while (shared < min_len && last_key[shared] == key[shared]) {
          shared++;
        }
      }

      uint32_t non_shared = static_cast<uint32_t>(key.size()) - shared;
      uint32_t value_size = static_cast<uint32_t>(value.size());

      // Encode as varint32
      PutVarint32(&result, shared);
      PutVarint32(&result, non_shared);
      PutVarint32(&result, value_size);
      result.append(key.data() + shared, non_shared);
      result.append(value);

      last_key = key;
    }

    // If no entries, we still need at least one restart point
    if (restarts.empty()) {
      restarts.push_back(0);
    }

    // Append restart points
    for (uint32_t restart : restarts) {
      PutFixed32(&result, restart);
    }
    // Append number of restarts
    PutFixed32(&result, static_cast<uint32_t>(restarts.size()));

    return result;
  }
};

class BlockIterTest_492 : public ::testing::Test {
 protected:
  const Comparator* cmp_ = BytewiseComparator();

  // Create a Block from raw data. Block takes ownership via BlockContents.
  Block* MakeBlock(const std::string& data) {
    // Block expects BlockContents: data, cachable, heap_allocated
    // If heap_allocated is true, Block will delete[] the data
    char* buf = new char[data.size()];
    std::memcpy(buf, data.data(), data.size());
    BlockContents contents;
    contents.data = Slice(buf, data.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    return new Block(contents);
  }
};

// Test that an empty block (no entries but valid format) yields an invalid iterator
TEST_F(BlockIterTest_492, EmptyBlockIteratorIsInvalid_492) {
  std::string block_data = BlockBuilderHelper::BuildBlock({});
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  EXPECT_FALSE(iter->Valid());

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

// Test SeekToFirst with a single entry
TEST_F(BlockIterTest_492, SingleEntrySeeKToFirst_492) {
  std::string block_data = BlockBuilderHelper::BuildBlock({{"key1", "value1"}});
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");
  EXPECT_TRUE(iter->status().ok());

  delete iter;
  delete block;
}

// Test SeekToLast with a single entry
TEST_F(BlockIterTest_492, SingleEntrySeekToLast_492) {
  std::string block_data = BlockBuilderHelper::BuildBlock({{"key1", "value1"}});
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");

  delete iter;
  delete block;
}

// Test Next through multiple entries
TEST_F(BlockIterTest_492, MultipleEntriesForwardIteration_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToFirst();
  for (size_t i = 0; i < kvs.size(); i++) {
    ASSERT_TRUE(iter->Valid()) << "Entry " << i;
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    iter->Next();
  }
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

// Test Prev through multiple entries from the last
TEST_F(BlockIterTest_492, MultipleEntriesReverseIteration_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToLast();
  for (int i = static_cast<int>(kvs.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid()) << "Entry " << i;
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    if (i > 0) iter->Prev();
  }

  // Go one more Prev - should make it invalid
  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

// Test Seek to an exact key
TEST_F(BlockIterTest_492, SeekExactKey_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  EXPECT_EQ(iter->value().ToString(), "val3");

  delete iter;
  delete block;
}

// Test Seek to a key between entries (should land on next entry)
TEST_F(BlockIterTest_492, SeekBetweenKeys_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"ccc", "val2"},
      {"eee", "val3"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");

  iter->Seek("ddd");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "eee");

  delete iter;
  delete block;
}

// Test Seek past all keys
TEST_F(BlockIterTest_492, SeekPastEnd_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

// Test Seek to a key before all entries
TEST_F(BlockIterTest_492, SeekBeforeFirstKey_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"bbb", "val1"},
      {"ccc", "val2"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");

  delete iter;
  delete block;
}

// Test with shared prefix compression (restart_interval > 1)
TEST_F(BlockIterTest_492, SharedPrefixCompression_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"abcdef", "v1"},
      {"abcdgh", "v2"},
      {"abcdij", "v3"},
      {"abcdkl", "v4"},
  };
  // restart_interval = 2 means restart every 2 entries
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs, 2);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  // Forward iteration
  iter->SeekToFirst();
  for (size_t i = 0; i < kvs.size(); i++) {
    ASSERT_TRUE(iter->Valid()) << "Entry " << i;
    EXPECT_EQ(iter->key().ToString(), kvs[i].first);
    EXPECT_EQ(iter->value().ToString(), kvs[i].second);
    iter->Next();
  }
  EXPECT_FALSE(iter->Valid());

  // Seek test
  iter->Seek("abcdij");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "abcdij");
  EXPECT_EQ(iter->value().ToString(), "v3");

  delete iter;
  delete block;
}

// Test that status() is ok for valid block
TEST_F(BlockIterTest_492, StatusOkForValidBlock_492) {
  std::string block_data = BlockBuilderHelper::BuildBlock({{"key", "val"}});
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  EXPECT_TRUE(iter->status().ok());

  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());

  delete iter;
  delete block;
}

// Test alternating Next and Prev
TEST_F(BlockIterTest_492, AlternatingNextPrev_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
      {"d", "4"},
      {"e", "5"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  delete iter;
  delete block;
}

// Test with empty key and value
TEST_F(BlockIterTest_492, EmptyKeyAndValue_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"", ""},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "");
  EXPECT_EQ(iter->value().ToString(), "");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

// Test with larger values
TEST_F(BlockIterTest_492, LargeValues_492) {
  std::string large_value(10000, 'x');
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", large_value},
      {"key2", large_value},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), large_value);

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), large_value);

  delete iter;
  delete block;
}

// Test Block::size() returns the size of the block data
TEST_F(BlockIterTest_492, BlockSize_492) {
  std::string block_data = BlockBuilderHelper::BuildBlock({{"k", "v"}});
  Block* block = MakeBlock(block_data);

  EXPECT_EQ(block->size(), block_data.size());

  delete block;
}

// Test corrupted block (invalid num_restarts)
TEST_F(BlockIterTest_492, CorruptedBlockTooSmall_492) {
  // A block that is too small to contain even the num_restarts field
  std::string tiny_data("ab");
  // Need at least sizeof(uint32_t) bytes. Let's create a block with size < sizeof(uint32_t)
  char* buf = new char[tiny_data.size()];
  std::memcpy(buf, tiny_data.data(), tiny_data.size());
  BlockContents contents;
  contents.data = Slice(buf, tiny_data.size());
  contents.cachable = false;
  contents.heap_allocated = true;
  Block block(contents);

  Iterator* iter = block.NewIterator(cmp_);
  // The iterator should report an error status for corrupted blocks
  EXPECT_FALSE(iter->Valid());
  // Status might or might not be ok depending on implementation
  // But the iterator should not crash
  delete iter;
}

// Test seeking to first key in the block
TEST_F(BlockIterTest_492, SeekToFirstKey_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->Seek("alpha");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "alpha");
  EXPECT_EQ(iter->value().ToString(), "1");

  delete iter;
  delete block;
}

// Test many entries with restart_interval of 16 (like default BlockBuilder)
TEST_F(BlockIterTest_492, ManyEntriesWithRestartInterval_492) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key_buf[32], val_buf[32];
    std::snprintf(key_buf, sizeof(key_buf), "key%06d", i);
    std::snprintf(val_buf, sizeof(val_buf), "val%06d", i);
    kvs.push_back({key_buf, val_buf});
  }
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs, 16);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  // Forward scan
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    ASSERT_LT(count, 100);
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 100);

  // Reverse scan
  iter->SeekToLast();
  count = 99;
  while (iter->Valid()) {
    ASSERT_GE(count, 0);
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count--;
    if (count >= 0) iter->Prev();
    else break;
  }
  EXPECT_EQ(count, -1);

  // Random seek
  iter->Seek("key000050");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key000050");

  delete iter;
  delete block;
}

// Test Next after SeekToLast goes invalid
TEST_F(BlockIterTest_492, NextAfterSeekToLast_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

// Test Prev after SeekToFirst goes invalid
TEST_F(BlockIterTest_492, PrevAfterSeekToFirst_492) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
  };
  std::string block_data = BlockBuilderHelper::BuildBlock(kvs);
  Block* block = MakeBlock(block_data);
  Iterator* iter = block->NewIterator(cmp_);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete block;
}

}  // namespace leveldb
