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

// Helper function to build a block with given key-value pairs
static std::string BuildBlockData(const std::vector<std::pair<std::string, std::string>>& entries, int restart_interval = 16) {
  Options options;
  options.block_restart_interval = restart_interval;
  BlockBuilder builder(&options);
  for (const auto& entry : entries) {
    builder.Add(Slice(entry.first), Slice(entry.second));
  }
  Slice raw = builder.Finish();
  return std::string(raw.data(), raw.size());
}

// Helper to create BlockContents from a string (not heap allocated)
static BlockContents MakeBlockContents(const std::string& data, bool heap_allocated = false) {
  BlockContents contents;
  contents.data = Slice(data.data(), data.size());
  contents.cachable = false;
  contents.heap_allocated = heap_allocated;
  return contents;
}

// Test fixture
class BlockTest_405 : public ::testing::Test {
 protected:
  const Comparator* cmp_ = BytewiseComparator();
};

// Test creating a block with no entries and iterating yields nothing
TEST_F(BlockTest_405, EmptyBlock_405) {
  std::string data = BuildBlockData({});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  ASSERT_TRUE(iter != nullptr);
  
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test block size returns correct size
TEST_F(BlockTest_405, SizeReturnsCorrectValue_405) {
  std::string data = BuildBlockData({{"key1", "value1"}});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  EXPECT_EQ(block.size(), data.size());
}

// Test single entry block
TEST_F(BlockTest_405, SingleEntry_405) {
  std::string data = BuildBlockData({{"hello", "world"}});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "hello");
  EXPECT_EQ(iter->value().ToString(), "world");
  
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test multiple entries with SeekToFirst and iteration
TEST_F(BlockTest_405, MultipleEntriesForwardIteration_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->SeekToFirst();
  
  for (size_t i = 0; i < entries.size(); i++) {
    ASSERT_TRUE(iter->Valid()) << "Expected valid at index " << i;
    EXPECT_EQ(iter->key().ToString(), entries[i].first);
    EXPECT_EQ(iter->value().ToString(), entries[i].second);
    iter->Next();
  }
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test SeekToLast and backward iteration
TEST_F(BlockTest_405, BackwardIteration_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->SeekToLast();
  
  for (int i = static_cast<int>(entries.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter->Valid()) << "Expected valid at index " << i;
    EXPECT_EQ(iter->key().ToString(), entries[i].first);
    EXPECT_EQ(iter->value().ToString(), entries[i].second);
    iter->Prev();
  }
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Seek to existing key
TEST_F(BlockTest_405, SeekExistingKey_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
    {"ccc", "val3"},
    {"ddd", "val4"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  EXPECT_EQ(iter->value().ToString(), "val2");
  
  delete iter;
}

// Test Seek to non-existing key (should find next key)
TEST_F(BlockTest_405, SeekNonExistingKey_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"ccc", "val3"},
    {"eee", "val5"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");
  EXPECT_EQ(iter->value().ToString(), "val3");
  
  delete iter;
}

// Test Seek past all keys
TEST_F(BlockTest_405, SeekPastAllKeys_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"aaa", "val1"},
    {"bbb", "val2"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Seek before all keys
TEST_F(BlockTest_405, SeekBeforeAllKeys_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"bbb", "val2"},
    {"ccc", "val3"},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  
  delete iter;
}

// Test block with heap-allocated data (owned_=true, destructor should free)
TEST_F(BlockTest_405, HeapAllocatedBlock_405) {
  std::string raw = BuildBlockData({{"key", "value"}});
  
  // Allocate data on heap
  char* heap_data = new char[raw.size()];
  std::memcpy(heap_data, raw.data(), raw.size());
  
  BlockContents contents;
  contents.data = Slice(heap_data, raw.size());
  contents.cachable = false;
  contents.heap_allocated = true;
  
  // Block takes ownership; destructor should delete[] heap_data
  Block* block = new Block(contents);
  Iterator* iter = block->NewIterator(cmp_);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key");
  EXPECT_EQ(iter->value().ToString(), "value");
  
  delete iter;
  delete block;  // Should not crash; it owns the data
}

// Test with many entries spanning multiple restart points
TEST_F(BlockTest_405, ManyEntriesWithRestarts_405) {
  std::vector<std::pair<std::string, std::string>> entries;
  for (int i = 0; i < 100; i++) {
    char key[16], val[16];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    entries.push_back({std::string(key), std::string(val)});
  }
  
  // Use restart interval of 4 to have many restart points
  std::string data = BuildBlockData(entries, 4);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  
  // Forward iteration
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    EXPECT_EQ(iter->key().ToString(), entries[count].first);
    EXPECT_EQ(iter->value().ToString(), entries[count].second);
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 100);
  
  // Seek to middle
  iter->Seek("key000050");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key000050");
  EXPECT_EQ(iter->value().ToString(), "val000050");
  
  delete iter;
}

// Test iterator status is ok for a valid block
TEST_F(BlockTest_405, IteratorStatusOk_405) {
  std::string data = BuildBlockData({{"key", "val"}});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  EXPECT_TRUE(iter->status().ok());
  
  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());
  
  delete iter;
}

// Test block with large values
TEST_F(BlockTest_405, LargeValues_405) {
  std::string large_val(10000, 'x');
  std::vector<std::pair<std::string, std::string>> entries = {
    {"key1", large_val},
    {"key2", std::string(5000, 'y')},
  };
  std::string data = BuildBlockData(entries);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), large_val);
  
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().size(), 5000u);
  
  delete iter;
}

// Test empty block size
TEST_F(BlockTest_405, EmptyBlockSize_405) {
  std::string data = BuildBlockData({});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  // Empty block still has restart array (at minimum the count)
  EXPECT_GT(block.size(), 0u);
}

// Test Prev from SeekToFirst makes iterator invalid
TEST_F(BlockTest_405, PrevFromFirstIsInvalid_405) {
  std::string data = BuildBlockData({{"aaa", "111"}, {"bbb", "222"}});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Next from SeekToLast makes iterator invalid
TEST_F(BlockTest_405, NextFromLastIsInvalid_405) {
  std::string data = BuildBlockData({{"aaa", "111"}, {"bbb", "222"}});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test restart_interval = 1 (every entry is a restart point)
TEST_F(BlockTest_405, RestartIntervalOne_405) {
  std::vector<std::pair<std::string, std::string>> entries = {
    {"abc", "1"},
    {"abd", "2"},
    {"abe", "3"},
    {"abf", "4"},
  };
  std::string data = BuildBlockData(entries, 1);
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  
  // Test seeking to each key
  for (const auto& entry : entries) {
    iter->Seek(entry.first);
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), entry.first);
    EXPECT_EQ(iter->value().ToString(), entry.second);
  }
  
  delete iter;
}

// Test that NewIterator returns a non-null iterator even for empty blocks
TEST_F(BlockTest_405, NewIteratorNonNull_405) {
  std::string data = BuildBlockData({});
  BlockContents contents = MakeBlockContents(data);
  Block block(contents);
  
  Iterator* iter = block.NewIterator(cmp_);
  ASSERT_NE(iter, nullptr);
  delete iter;
}

}  // namespace leveldb
