#include "gtest/gtest.h"
#include "table/block.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/table_builder.h"
#include "table/block_builder.h"
#include "table/format.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// Helper function to build a block from key-value pairs
static std::string BuildBlockData(const std::vector<std::pair<std::string, std::string>>& entries) {
  Options options;
  BlockBuilder builder(&options);
  for (const auto& entry : entries) {
    builder.Add(entry.first, entry.second);
  }
  Slice raw = builder.Finish();
  return std::string(raw.data(), raw.size());
}

// Helper to create BlockContents from a string (not heap allocated)
static BlockContents MakeBlockContents(const std::string& data) {
  BlockContents contents;
  contents.data = Slice(data.data(), data.size());
  contents.cachable = false;
  contents.heap_allocated = false;
  return contents;
}

// Helper to create BlockContents with heap-allocated data
static BlockContents MakeHeapBlockContents(const std::string& data) {
  char* buf = new char[data.size()];
  std::memcpy(buf, data.data(), data.size());
  BlockContents contents;
  contents.data = Slice(buf, data.size());
  contents.cachable = false;
  contents.heap_allocated = true;
  return contents;
}

class BlockTest_295 : public ::testing::Test {
 protected:
};

TEST_F(BlockTest_295, EmptyBlockSize_295) {
  std::string data = BuildBlockData({});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), data.size());
}

TEST_F(BlockTest_295, SingleEntryBlockSize_295) {
  std::string data = BuildBlockData({{"key1", "value1"}});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), data.size());
}

TEST_F(BlockTest_295, MultipleEntriesBlockSize_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
      {"ddd", "val4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), data.size());
}

TEST_F(BlockTest_295, NewIteratorOnEmptyBlock_295) {
  std::string data = BuildBlockData({});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  EXPECT_TRUE(iter->status().ok());
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorSeekToFirst_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorSeekToLast_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");
  EXPECT_EQ(iter->value().ToString(), "value3");
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorForwardIteration_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "v1"},
      {"bbb", "v2"},
      {"ccc", "v3"},
      {"ddd", "v4"},
      {"eee", "v5"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    EXPECT_EQ(iter->key().ToString(), entries[count].first);
    EXPECT_EQ(iter->value().ToString(), entries[count].second);
    count++;
  }
  EXPECT_EQ(count, static_cast<int>(entries.size()));
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorReverseIteration_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "v1"},
      {"bbb", "v2"},
      {"ccc", "v3"},
      {"ddd", "v4"},
      {"eee", "v5"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);

  int count = static_cast<int>(entries.size()) - 1;
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    EXPECT_EQ(iter->key().ToString(), entries[count].first);
    EXPECT_EQ(iter->value().ToString(), entries[count].second);
    count--;
  }
  EXPECT_EQ(count, -1);
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorSeekExactKey_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "1"},
      {"banana", "2"},
      {"cherry", "3"},
      {"date", "4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);

  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "banana");
  EXPECT_EQ(iter->value().ToString(), "2");

  iter->Seek("cherry");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "cherry");
  EXPECT_EQ(iter->value().ToString(), "3");
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorSeekNonExistentKey_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"apple", "1"},
      {"cherry", "3"},
      {"date", "4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);

  // Seek to "banana" which doesn't exist; should land on "cherry"
  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "cherry");
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorSeekPastEnd_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"aaa", "1"},
      {"bbb", "2"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);

  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(BlockTest_295, NewIteratorSeekBeforeBeginning_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"bbb", "1"},
      {"ccc", "2"},
      {"ddd", "3"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  ASSERT_NE(iter, nullptr);

  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  delete iter;
}

TEST_F(BlockTest_295, HeapAllocatedBlockContents_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
      {"key2", "value2"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeHeapBlockContents(data);
  Block* block = new Block(contents);
  EXPECT_EQ(block->size(), data.size());

  Iterator* iter = block->NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  delete iter;
  // Block destructor should handle freeing heap-allocated data
  delete block;
}

TEST_F(BlockTest_295, SingleEntryIteration_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"only_key", "only_value"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only_key");
  EXPECT_EQ(iter->value().ToString(), "only_value");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only_key");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(BlockTest_295, LargeNumberOfEntries_295) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 1000; i++) {
    char key_buf[32], val_buf[32];
    snprintf(key_buf, sizeof(key_buf), "key%06d", i);
    snprintf(val_buf, sizeof(val_buf), "val%06d", i);
    entries.push_back({key_buf, val_buf});
  }
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  EXPECT_EQ(block.size(), data.size());

  Iterator* iter = block.NewIterator(BytewiseComparator());

  // Forward iteration count
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 1000);

  // Seek to middle entry
  iter->Seek("key000500");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key000500");
  EXPECT_EQ(iter->value().ToString(), "val000500");

  delete iter;
}

TEST_F(BlockTest_295, EmptyKeyAndValue_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"", ""},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "");
  EXPECT_EQ(iter->value().ToString(), "");

  delete iter;
}

TEST_F(BlockTest_295, LargeValues_295) {
  std::string large_value(10000, 'x');
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", large_value},
      {"key2", large_value},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->value().size(), 10000u);
  EXPECT_EQ(iter->value().ToString(), large_value);

  delete iter;
}

TEST_F(BlockTest_295, NextThenPrev_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
      {"d", "4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());

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

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(BlockTest_295, SizeNonZeroForNonEmptyBlock_295) {
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key", "value"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  EXPECT_GT(block.size(), 0u);
}

}  // namespace leveldb
