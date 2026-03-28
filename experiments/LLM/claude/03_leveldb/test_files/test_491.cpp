#include "gtest/gtest.h"
#include "table/block.h"
#include "table/format.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"

#include <cstring>
#include <string>
#include <vector>

namespace leveldb {

// Helper to encode a uint32_t in little-endian format
static void PutFixed32(std::string* dst, uint32_t value) {
  char buf[sizeof(value)];
  buf[0] = value & 0xff;
  buf[1] = (value >> 8) & 0xff;
  buf[2] = (value >> 16) & 0xff;
  buf[3] = (value >> 24) & 0xff;
  dst->append(buf, sizeof(buf));
}

// Helper to build a minimal valid block with no entries and one restart point at offset 0
// Block format: [entries...] [restart_point_0] ... [restart_point_n-1] [num_restarts]
static std::string BuildEmptyBlock() {
  std::string data;
  // One restart point at offset 0
  PutFixed32(&data, 0);
  // num_restarts = 1
  PutFixed32(&data, 1);
  return data;
}

// Build a block with entries. This builds a simple block with one key-value pair.
// Block entry format: shared(varint32) | non_shared(varint32) | value_length(varint32) | key_delta | value
// For simplicity, shared=0, so key_delta is the full key.
static void PutVarint32(std::string* dst, uint32_t v) {
  char buf[5];
  int len = 0;
  while (v >= 128) {
    buf[len++] = (v & 0x7f) | 0x80;
    v >>= 7;
  }
  buf[len++] = v;
  dst->append(buf, len);
}

static std::string BuildBlockWithEntries(
    const std::vector<std::pair<std::string, std::string>>& entries,
    int restart_interval = 16) {
  std::string data;
  std::vector<uint32_t> restarts;
  
  for (size_t i = 0; i < entries.size(); i++) {
    if (i % restart_interval == 0) {
      restarts.push_back(static_cast<uint32_t>(data.size()));
    }
    const std::string& key = entries[i].first;
    const std::string& value = entries[i].second;
    
    // shared = 0, non_shared = key.size(), value_length = value.size()
    PutVarint32(&data, 0);
    PutVarint32(&data, static_cast<uint32_t>(key.size()));
    PutVarint32(&data, static_cast<uint32_t>(value.size()));
    data.append(key);
    data.append(value);
  }
  
  if (restarts.empty()) {
    restarts.push_back(0);
  }
  
  for (uint32_t r : restarts) {
    PutFixed32(&data, r);
  }
  PutFixed32(&data, static_cast<uint32_t>(restarts.size()));
  
  return data;
}

class BlockTest_491 : public ::testing::Test {
 protected:
  BlockContents MakeContents(const std::string& data, bool heap_allocated = false) {
    BlockContents contents;
    contents.data = Slice(data.data(), data.size());
    contents.cachable = false;
    contents.heap_allocated = heap_allocated;
    return contents;
  }
};

// Test that a block with size less than sizeof(uint32_t) is treated as an error (size becomes 0)
TEST_F(BlockTest_491, TooSmallBlockSetsZeroSize_491) {
  std::string tiny_data = "ab";  // less than 4 bytes
  BlockContents contents = MakeContents(tiny_data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test empty data (0 bytes)
TEST_F(BlockTest_491, EmptyDataSetsZeroSize_491) {
  std::string empty;
  BlockContents contents = MakeContents(empty);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test block with exactly 4 bytes but num_restarts is too large
TEST_F(BlockTest_491, FourBytesWithLargeNumRestarts_491) {
  std::string data;
  // num_restarts = 100, but max_restarts_allowed = (4 - 4)/4 = 0
  PutFixed32(&data, 100);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test block with exactly 4 bytes and num_restarts = 0
TEST_F(BlockTest_491, FourBytesZeroRestarts_491) {
  std::string data;
  PutFixed32(&data, 0);  // num_restarts = 0
  BlockContents contents = MakeContents(data);
  Block block(contents);
  // max_restarts_allowed = (4-4)/4 = 0, NumRestarts()=0, 0 <= 0 is ok
  EXPECT_EQ(block.size(), 4u);
}

// Test a valid empty block (no entries, one restart)
TEST_F(BlockTest_491, ValidEmptyBlock_491) {
  std::string data = BuildEmptyBlock();
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), data.size());
}

// Test that NewIterator returns a valid iterator for an empty block
TEST_F(BlockTest_491, EmptyBlockIterator_491) {
  std::string data = BuildEmptyBlock();
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test that NewIterator works for a block with one entry
TEST_F(BlockTest_491, SingleEntryBlock_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", "value1"}
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_GT(block.size(), 0u);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");
  
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test multiple entries with SeekToFirst and iteration
TEST_F(BlockTest_491, MultipleEntriesIteration_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
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

// Test SeekToLast with multiple entries
TEST_F(BlockTest_491, SeekToLast_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  EXPECT_EQ(iter->value().ToString(), "val3");
  
  delete iter;
}

// Test Seek to a specific key
TEST_F(BlockTest_491, SeekToExistingKey_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  EXPECT_EQ(iter->value().ToString(), "val2");
  
  delete iter;
}

// Test Seek to a key between existing keys
TEST_F(BlockTest_491, SeekBetweenKeys_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"ccc", "val3"},
    {"eee", "val5"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  
  delete iter;
}

// Test Seek to a key past all entries
TEST_F(BlockTest_491, SeekPastEnd_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Prev navigation
TEST_F(BlockTest_491, PrevNavigation_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "aaa");
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test that a corrupted block (num_restarts too large) results in size 0
TEST_F(BlockTest_491, CorruptedNumRestarts_491) {
  std::string data;
  // Add 8 bytes of data, then set num_restarts to a huge number
  PutFixed32(&data, 0);       // some data / fake restart
  PutFixed32(&data, 999999);  // num_restarts = 999999
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test block with num_restarts equal to exactly max allowed
TEST_F(BlockTest_491, NumRestartsAtMax_491) {
  std::string data;
  // Build data with exactly 2 restart points and num_restarts = 2
  // Total: 2 restart offsets (8 bytes) + num_restarts (4 bytes) = 12 bytes
  // max_restarts_allowed = (12 - 4) / 4 = 2
  PutFixed32(&data, 0);  // restart[0]
  PutFixed32(&data, 0);  // restart[1]
  PutFixed32(&data, 2);  // num_restarts = 2
  
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 12u);
}

// Test block with num_restarts = max_allowed + 1 (should be invalid)
TEST_F(BlockTest_491, NumRestartsExceedsMax_491) {
  std::string data;
  // 12 bytes total, max_restarts_allowed = (12-4)/4 = 2, but num_restarts=3
  PutFixed32(&data, 0);
  PutFixed32(&data, 0);
  PutFixed32(&data, 3);  // num_restarts = 3
  
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test that creating an iterator on a zero-size (error) block still works safely
TEST_F(BlockTest_491, IteratorOnErrorBlock_491) {
  std::string tiny = "ab";
  BlockContents contents = MakeContents(tiny);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test with exactly sizeof(uint32_t) bytes = 4 and valid num_restarts
TEST_F(BlockTest_491, ExactlyFourBytesOneRestart_491) {
  std::string data;
  // num_restarts = 1, max_restarts_allowed = (4-4)/4 = 0
  // 1 > 0 so this should be invalid
  PutFixed32(&data, 1);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test with 3 bytes (less than uint32_t)
TEST_F(BlockTest_491, ThreeBytesSetsZeroSize_491) {
  std::string data = "abc";
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test with 1 byte
TEST_F(BlockTest_491, OneByteBlock_491) {
  std::string data = "x";
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), 0u);
}

// Test multiple entries with restart interval = 1 (every entry is a restart point)
TEST_F(BlockTest_491, MultipleRestartsIteration_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "v1"},
    {"bbb", "v2"},
    {"ccc", "v3"},
    {"ddd", "v4"},
    {"eee", "v5"},
  };
  std::string data = BuildBlockWithEntries(entries, 1);  // restart_interval=1
  BlockContents contents = MakeContents(data);
  Block block(contents);
  EXPECT_GT(block.size(), 0u);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 5);
  
  delete iter;
}

// Test Seek to a key before the first entry
TEST_F(BlockTest_491, SeekBeforeFirstKey_491) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"bbb", "val2"},
    {"ccc", "val3"},
  };
  std::string data = BuildBlockWithEntries(entries);
  BlockContents contents = MakeContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  
  delete iter;
}

// Test heap_allocated flag doesn't affect block construction logic
TEST_F(BlockTest_491, HeapAllocatedFlag_491) {
  std::string data = BuildEmptyBlock();
  
  // Create with heap_allocated = false
  BlockContents contents1;
  contents1.data = Slice(data.data(), data.size());
  contents1.cachable = false;
  contents1.heap_allocated = false;
  
  Block block1(contents1);
  EXPECT_EQ(block1.size(), data.size());
}

}  // namespace leveldb
