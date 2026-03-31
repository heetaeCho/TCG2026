#include "gtest/gtest.h"
#include "table/block.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "table/format.h"

#include <cstring>
#include <string>
#include <vector>

namespace leveldb {

// Helper to build a valid block with restart points
// A minimal valid block needs at least the num_restarts trailer (uint32_t)
// and the restart array itself.

class BlockTest_416 : public ::testing::Test {
 protected:
  // Build block contents from raw data
  BlockContents MakeBlockContents(const std::string& data, bool heap_allocated = false) {
    BlockContents contents;
    contents.data = Slice(data.data(), data.size());
    contents.cachable = false;
    contents.heap_allocated = heap_allocated;
    return contents;
  }

  // Build a minimal valid block with zero restarts
  // Format: [num_restarts = 0] (4 bytes little-endian)
  std::string MakeEmptyBlock() {
    std::string result;
    PutFixed32(&result, 0);  // num_restarts = 0
    return result;
  }

  // Build a block with some entries and restart points
  // This creates a proper block with one restart point at offset 0
  // and one key-value entry.
  std::string MakeBlockWithOneEntry(const std::string& key, const std::string& value) {
    std::string result;

    // Entry format: shared_bytes, unshared_bytes, value_length, key_delta, value
    // For first entry (restart point), shared = 0
    uint32_t restart_offset = 0;

    // Varint: shared=0, unshared=key.size(), value_length=value.size()
    PutVarint32(&result, 0);               // shared bytes
    PutVarint32(&result, key.size());      // unshared bytes
    PutVarint32(&result, value.size());    // value length
    result.append(key);
    result.append(value);

    // Remember restart offset (this entry starts at offset 0)
    uint32_t data_size = result.size();

    // Restart array
    PutFixed32(&result, 0);  // restart[0] = 0

    // num_restarts
    PutFixed32(&result, 1);  // 1 restart point

    return result;
  }

  std::string MakeBlockWithMultipleEntries(
      const std::vector<std::pair<std::string, std::string>>& entries) {
    std::string result;
    std::vector<uint32_t> restarts;
    std::string last_key;

    // Use restart interval of 1 for simplicity (every entry is a restart)
    for (size_t i = 0; i < entries.size(); i++) {
      restarts.push_back(result.size());
      const std::string& key = entries[i].first;
      const std::string& value = entries[i].second;

      // shared = 0 (each is a restart point)
      PutVarint32(&result, 0);
      PutVarint32(&result, key.size());
      PutVarint32(&result, value.size());
      result.append(key);
      result.append(value);
      last_key = key;
    }

    // Restart array
    for (uint32_t r : restarts) {
      PutFixed32(&result, r);
    }

    // num_restarts
    PutFixed32(&result, restarts.size());

    return result;
  }

  void PutFixed32(std::string* dst, uint32_t value) {
    char buf[sizeof(value)];
    buf[0] = value & 0xff;
    buf[1] = (value >> 8) & 0xff;
    buf[2] = (value >> 16) & 0xff;
    buf[3] = (value >> 24) & 0xff;
    dst->append(buf, sizeof(buf));
  }

  void PutVarint32(std::string* dst, uint32_t v) {
    char buf[5];
    int len = 0;
    while (v >= 128) {
      buf[len++] = (v & 127) | 128;
      v >>= 7;
    }
    buf[len++] = v;
    dst->append(buf, len);
  }
};

// Test that a block with size less than sizeof(uint32_t) returns an error iterator
TEST_F(BlockTest_416, TooSmallBlockReturnsErrorIterator_416) {
  // Block with less than 4 bytes
  std::string data = "ab";  // 2 bytes, less than sizeof(uint32_t)
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  ASSERT_TRUE(iter != nullptr);
  // The iterator should be an error iterator with corruption status
  ASSERT_FALSE(iter->Valid());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().IsCorruption());

  delete iter;
}

// Test that an empty block (0 bytes) returns an error iterator
TEST_F(BlockTest_416, EmptyDataReturnsErrorIterator_416) {
  std::string data = "";  // 0 bytes
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  ASSERT_TRUE(iter != nullptr);
  ASSERT_FALSE(iter->Valid());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().IsCorruption());

  delete iter;
}

// Test that a block with exactly 3 bytes returns an error iterator
TEST_F(BlockTest_416, ThreeBytesBlockReturnsErrorIterator_416) {
  std::string data = "abc";  // 3 bytes
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  ASSERT_TRUE(iter != nullptr);
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().IsCorruption());

  delete iter;
}

// Test that a block with num_restarts = 0 returns an empty iterator
TEST_F(BlockTest_416, ZeroRestartsReturnsEmptyIterator_416) {
  std::string data = MakeEmptyBlock();
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  ASSERT_TRUE(iter != nullptr);
  ASSERT_FALSE(iter->Valid());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

// Test that a block with one entry can be iterated
TEST_F(BlockTest_416, SingleEntryBlockSeekToFirst_416) {
  std::string data = MakeBlockWithOneEntry("hello", "world");
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  ASSERT_TRUE(iter != nullptr);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "hello");
  ASSERT_EQ(iter->value().ToString(), "world");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test SeekToLast on a single entry block
TEST_F(BlockTest_416, SingleEntryBlockSeekToLast_416) {
  std::string data = MakeBlockWithOneEntry("key1", "val1");
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "val1");

  delete iter;
}

// Test Seek on a single entry block
TEST_F(BlockTest_416, SingleEntryBlockSeek_416) {
  std::string data = MakeBlockWithOneEntry("key1", "val1");
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  // Seek to exact key
  iter->Seek("key1");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");

  // Seek to key before
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");

  // Seek to key after
  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test multiple entries
TEST_F(BlockTest_416, MultipleEntriesIteration_416) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
  };
  std::string data = MakeBlockWithMultipleEntries(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  // Forward iteration
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");
  ASSERT_EQ(iter->value().ToString(), "val_a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");
  ASSERT_EQ(iter->value().ToString(), "val_b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");
  ASSERT_EQ(iter->value().ToString(), "val_c");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test reverse iteration
TEST_F(BlockTest_416, MultipleEntriesReverseIteration_416) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
  };
  std::string data = MakeBlockWithMultipleEntries(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test Seek in multiple entries
TEST_F(BlockTest_416, MultipleEntriesSeek_416) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val_a"},
      {"ccc", "val_c"},
      {"eee", "val_e"},
  };
  std::string data = MakeBlockWithMultipleEntries(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  // Seek to middle key that doesn't exist - should land on next key
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");

  // Seek to existing key
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");

  // Seek past all keys
  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());

  // Seek to before all keys
  iter->Seek("");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");

  delete iter;
}

// Test exactly 4 bytes (sizeof(uint32_t)) block - should not be corruption
// With 4 bytes, the block has a num_restarts field that can be read
TEST_F(BlockTest_416, ExactlyFourBytesBlock_416) {
  std::string data;
  PutFixed32(&data, 0);  // num_restarts = 0
  ASSERT_EQ(data.size(), 4u);

  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  const Comparator* cmp = BytewiseComparator();
  Iterator* iter = block.NewIterator(cmp);

  ASSERT_TRUE(iter != nullptr);
  // With num_restarts = 0, should get empty iterator
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

// Test block size() method
TEST_F(BlockTest_416, BlockSizeMethod_416) {
  std::string data = MakeBlockWithOneEntry("key", "value");
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  ASSERT_EQ(block.size(), data.size());
}

// Test block size for empty block
TEST_F(BlockTest_416, EmptyBlockSize_416) {
  std::string data = MakeEmptyBlock();
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  ASSERT_EQ(block.size(), data.size());
}

// Test that NewIterator returns a non-null iterator even for error cases
TEST_F(BlockTest_416, NewIteratorNeverReturnsNull_416) {
  // Too small
  {
    std::string data = "x";
    BlockContents contents = MakeBlockContents(data);
    Block block(contents);
    Iterator* iter = block.NewIterator(BytewiseComparator());
    ASSERT_TRUE(iter != nullptr);
    delete iter;
  }

  // Zero restarts
  {
    std::string data = MakeEmptyBlock();
    BlockContents contents = MakeBlockContents(data);
    Block block(contents);
    Iterator* iter = block.NewIterator(BytewiseComparator());
    ASSERT_TRUE(iter != nullptr);
    delete iter;
  }

  // Normal block
  {
    std::string data = MakeBlockWithOneEntry("k", "v");
    BlockContents contents = MakeBlockContents(data);
    Block block(contents);
    Iterator* iter = block.NewIterator(BytewiseComparator());
    ASSERT_TRUE(iter != nullptr);
    delete iter;
  }
}

// Test with single byte data (boundary: size 1 < sizeof(uint32_t))
TEST_F(BlockTest_416, SingleByteBlock_416) {
  std::string data(1, '\0');
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);

  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().IsCorruption());

  delete iter;
}

}  // namespace leveldb
