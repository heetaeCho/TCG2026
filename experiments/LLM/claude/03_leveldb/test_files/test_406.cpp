#include "gtest/gtest.h"
#include "table/block.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// We need to test DecodeEntry which is a static inline function in block.cc.
// Since it's static inline in block.cc, we can't directly call it from here.
// However, we can test it through the Block and Block::Iter public interface.
// 
// The Block class reads a block of data and provides an iterator.
// We'll construct valid block data and test the Block's iterator behavior,
// which internally uses DecodeEntry.

// Helper to build a block with given key-value pairs
static std::string BuildBlock(const std::vector<std::pair<std::string, std::string>>& entries,
                               int restart_interval = 1) {
  // Block format:
  //   entries...
  //   restarts[0], restarts[1], ...
  //   num_restarts (4 bytes)
  //
  // Each entry:
  //   shared_bytes (varint32)
  //   unshared_bytes (varint32)
  //   value_length (varint32)
  //   key_delta (unshared_bytes)
  //   value (value_length)

  std::string result;
  std::vector<uint32_t> restarts;
  std::string last_key;
  int counter = 0;

  for (size_t i = 0; i < entries.size(); i++) {
    const std::string& key = entries[i].first;
    const std::string& value = entries[i].second;

    uint32_t shared = 0;
    if (counter < restart_interval) {
      // Compute shared prefix with last_key
      size_t min_len = std::min(last_key.size(), key.size());
      while (shared < min_len && last_key[shared] == key[shared]) {
        shared++;
      }
    } else {
      counter = 0;
    }

    if (counter == 0) {
      restarts.push_back(static_cast<uint32_t>(result.size()));
      shared = 0;
    }

    uint32_t non_shared = static_cast<uint32_t>(key.size()) - shared;
    uint32_t value_length = static_cast<uint32_t>(value.size());

    PutVarint32(&result, shared);
    PutVarint32(&result, non_shared);
    PutVarint32(&result, value_length);
    result.append(key.data() + shared, non_shared);
    result.append(value);

    last_key = key;
    counter++;
  }

  // Write restart array
  for (size_t i = 0; i < restarts.size(); i++) {
    PutFixed32(&result, restarts[i]);
  }
  PutFixed32(&result, static_cast<uint32_t>(restarts.size()));

  return result;
}

class BlockTest_406 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Empty block with no entries, just the restart array
TEST_F(BlockTest_406, EmptyBlock_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Single entry block
TEST_F(BlockTest_406, SingleEntry_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"key1", "value1"});
  std::string data = BuildBlock(entries);

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
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Multiple entries - iterate forward
TEST_F(BlockTest_406, MultipleEntriesForward_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"bbb", "val2"});
  entries.push_back({"ccc", "val3"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "aaa");
  EXPECT_EQ(iter->value().ToString(), "val1");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  EXPECT_EQ(iter->value().ToString(), "val2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  EXPECT_EQ(iter->value().ToString(), "val3");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Multiple entries - iterate backward
TEST_F(BlockTest_406, MultipleEntriesBackward_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"bbb", "val2"});
  entries.push_back({"ccc", "val3"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  EXPECT_EQ(iter->value().ToString(), "val3");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  EXPECT_EQ(iter->value().ToString(), "val2");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "aaa");
  EXPECT_EQ(iter->value().ToString(), "val1");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Seek to specific key
TEST_F(BlockTest_406, SeekToExistingKey_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"bbb", "val2"});
  entries.push_back({"ccc", "val3"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  EXPECT_EQ(iter->value().ToString(), "val2");

  delete iter;
}

// Test: Seek to non-existing key (between entries)
TEST_F(BlockTest_406, SeekToNonExistingKey_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"ccc", "val3"});
  entries.push_back({"eee", "val5"});
  std::string data = BuildBlock(entries);

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

// Test: Seek past all keys
TEST_F(BlockTest_406, SeekPastAllKeys_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"bbb", "val2"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Seek before all keys
TEST_F(BlockTest_406, SeekBeforeAllKeys_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"bbb", "val2"});
  entries.push_back({"ccc", "val3"});
  std::string data = BuildBlock(entries);

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

// Test: Block with shared prefix compression (restart_interval > 1)
TEST_F(BlockTest_406, SharedPrefixCompression_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"abc1", "v1"});
  entries.push_back({"abc2", "v2"});
  entries.push_back({"abc3", "v3"});
  entries.push_back({"abc4", "v4"});
  std::string data = BuildBlock(entries, 4);  // restart every 4 entries

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 4);

  // Verify we can seek properly with shared prefixes
  iter->Seek("abc3");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "abc3");
  EXPECT_EQ(iter->value().ToString(), "v3");

  delete iter;
}

// Test: Empty key and value
TEST_F(BlockTest_406, EmptyKeyAndValue_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"", ""});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "");
  EXPECT_EQ(iter->value().ToString(), "");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Large values
TEST_F(BlockTest_406, LargeValues_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  std::string large_value(10000, 'x');
  entries.push_back({"key1", large_value});
  entries.push_back({"key2", large_value});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().size(), 10000u);

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().size(), 10000u);

  delete iter;
}

// Test: Corrupted block data - too small
TEST_F(BlockTest_406, CorruptedBlockTooSmall_406) {
  // A valid block needs at least the num_restarts field (4 bytes)
  // A block with data smaller than sizeof(uint32_t) should handle gracefully
  std::string data("ab");  // too small

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  // Should be invalid or report error for corrupted block
  EXPECT_TRUE(!iter->Valid() || !iter->status().ok());

  delete iter;
}

// Test: Block size method
TEST_F(BlockTest_406, BlockSize_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"key1", "value1"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  EXPECT_EQ(block.size(), data.size());
}

// Test: Multiple restarts with many entries
TEST_F(BlockTest_406, MultipleRestarts_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[32];
    char val[32];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    entries.push_back({key, val});
  }
  // restart_interval=16 means a new restart every 16 entries
  std::string data = BuildBlock(entries, 16);

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
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 100);

  // Seek to middle
  iter->Seek("key000050");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key000050");
  EXPECT_EQ(iter->value().ToString(), "val000050");

  // SeekToLast and backward
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key000099");

  delete iter;
}

// Test: SeekToFirst then Prev should be invalid
TEST_F(BlockTest_406, SeekToFirstThenPrev_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"bbb", "val2"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: SeekToLast then Next should be invalid
TEST_F(BlockTest_406, SeekToLastThenNext_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"aaa", "val1"});
  entries.push_back({"bbb", "val2"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Keys with values >= 128 bytes trigger varint encoding path
TEST_F(BlockTest_406, LargeFieldsVarintEncoding_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  // Value length >= 128 to exercise the varint path in DecodeEntry
  std::string large_val(200, 'v');
  entries.push_back({"key1", large_val});
  entries.push_back({"key2", large_val});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().size(), 200u);

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().size(), 200u);

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Key with length >= 128 to trigger varint for non_shared
TEST_F(BlockTest_406, LargeKeyVarintEncoding_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  std::string long_key(200, 'k');
  entries.push_back({long_key, "val"});
  std::string data = BuildBlock(entries);

  BlockContents contents;
  contents.data = Slice(data);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), long_key);
  EXPECT_EQ(iter->value().ToString(), "val");

  delete iter;
}

// Test: Iterator status is ok for valid block
TEST_F(BlockTest_406, IteratorStatusOk_406) {
  std::vector<std::pair<std::string, std::string>> entries;
  entries.push_back({"key1", "val1"});
  std::string data = BuildBlock(entries);

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

}  // namespace leveldb
