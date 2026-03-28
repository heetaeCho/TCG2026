#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class BlockTest_412 : public ::testing::Test {
 protected:
  // Helper to build a block from key-value pairs
  BlockContents BuildBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                           int restart_interval = 16) {
    Options options;
    options.comparator = BytewiseComparator();
    BlockBuilder builder(&options);
    // Note: BlockBuilder uses options.block_restart_interval
    // We need to set it properly
    Options build_options;
    build_options.block_restart_interval = restart_interval;
    BlockBuilder bb(&build_options);
    
    for (const auto& kv : kvs) {
      bb.Add(kv.first, kv.second);
    }
    
    Slice raw = bb.Finish();
    // Make a copy since BlockBuilder's buffer may be reused
    char* data = new char[raw.size()];
    memcpy(data, raw.data(), raw.size());
    
    BlockContents contents;
    contents.data = Slice(data, raw.size());
    contents.cachable = false;
    contents.heap_allocated = true;
    return contents;
  }
};

// Test Prev from the last element traverses all elements in reverse
TEST_F(BlockTest_412, PrevFromLastTraversesAllReverse_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "val1"},
      {"key2", "val2"},
      {"key3", "val3"},
      {"key4", "val4"},
      {"key5", "val5"},
  };
  
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  // Collect keys in forward order
  std::vector<std::string> forward_keys;
  iter->SeekToFirst();
  while (iter->Valid()) {
    forward_keys.push_back(iter->key().ToString());
    iter->Next();
  }
  
  // Now traverse in reverse using Prev
  std::vector<std::string> reverse_keys;
  iter->SeekToLast();
  while (iter->Valid()) {
    reverse_keys.push_back(iter->key().ToString());
    iter->Prev();
  }
  
  // reverse_keys should be the reverse of forward_keys
  ASSERT_EQ(forward_keys.size(), reverse_keys.size());
  for (size_t i = 0; i < forward_keys.size(); i++) {
    EXPECT_EQ(forward_keys[i], reverse_keys[forward_keys.size() - 1 - i]);
  }
  
  delete iter;
}

// Test Prev on single element block
TEST_F(BlockTest_412, PrevOnSingleElement_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"only_key", "only_val"},
  };
  
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("only_key", iter->key().ToString());
  EXPECT_EQ("only_val", iter->value().ToString());
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Prev at the beginning makes iterator invalid
TEST_F(BlockTest_412, PrevAtBeginningMakesInvalid_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
  };
  
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Prev after Next returns to correct element
TEST_F(BlockTest_412, PrevAfterNextReturnsToPrevious_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "val1"},
      {"key2", "val2"},
      {"key3", "val3"},
  };
  
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->SeekToFirst();
  iter->Next(); // at key2
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key2", iter->key().ToString());
  
  iter->Prev(); // should go back to key1
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("key1", iter->key().ToString());
  EXPECT_EQ("val1", iter->value().ToString());
  
  delete iter;
}

// Test Prev with restart_interval = 1 (every entry is a restart point)
TEST_F(BlockTest_412, PrevWithSmallRestartInterval_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
      {"delta_nope", "4"}, // Note: keys must be sorted for block builder
  };
  
  // Sort for block builder
  std::sort(kvs.begin(), kvs.end());
  
  BlockContents contents = BuildBlock(kvs, 1); // restart every entry
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  // Collect in reverse
  std::vector<std::string> reverse_keys;
  iter->SeekToLast();
  while (iter->Valid()) {
    reverse_keys.push_back(iter->key().ToString());
    iter->Prev();
  }
  
  // Sort original to match what block builder expects
  std::sort(kvs.begin(), kvs.end());
  
  ASSERT_EQ(kvs.size(), reverse_keys.size());
  for (size_t i = 0; i < kvs.size(); i++) {
    EXPECT_EQ(kvs[kvs.size() - 1 - i], reverse_keys[i]);
  }
  
  delete iter;
}

// Test Prev with large restart interval (all entries share one restart point)
TEST_F(BlockTest_412, PrevWithLargeRestartInterval_412) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 20; i++) {
    char buf[32];
    snprintf(buf, sizeof(buf), "key%05d", i);
    kvs.push_back({std::string(buf), std::string("val") + std::to_string(i)});
  }
  
  BlockContents contents = BuildBlock(kvs, 100); // single restart point
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  std::vector<std::string> reverse_keys;
  iter->SeekToLast();
  while (iter->Valid()) {
    reverse_keys.push_back(iter->key().ToString());
    iter->Prev();
  }
  
  ASSERT_EQ(kvs.size(), reverse_keys.size());
  for (size_t i = 0; i < kvs.size(); i++) {
    EXPECT_EQ(kvs[kvs.size() - 1 - i], reverse_keys[i]);
  }
  
  delete iter;
}

// Test interleaved Next and Prev
TEST_F(BlockTest_412, InterleavedNextAndPrev_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
      {"d", "4"},
      {"e", "5"},
  };
  
  BlockContents contents = BuildBlock(kvs, 2);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->SeekToFirst();
  EXPECT_EQ("a", iter->key().ToString());
  
  iter->Next();
  EXPECT_EQ("b", iter->key().ToString());
  
  iter->Next();
  EXPECT_EQ("c", iter->key().ToString());
  
  iter->Prev();
  EXPECT_EQ("b", iter->key().ToString());
  
  iter->Prev();
  EXPECT_EQ("a", iter->key().ToString());
  
  iter->Next();
  EXPECT_EQ("b", iter->key().ToString());
  
  delete iter;
}

// Test Prev after Seek
TEST_F(BlockTest_412, PrevAfterSeek_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"},
      {"bbb", "2"},
      {"ccc", "3"},
      {"ddd", "4"},
      {"eee", "5"},
  };
  
  BlockContents contents = BuildBlock(kvs, 2);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->Seek("ccc");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("ccc", iter->key().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("bbb", iter->key().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("aaa", iter->key().ToString());
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Prev after SeekToLast
TEST_F(BlockTest_412, PrevAfterSeekToLast_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"x", "10"},
      {"y", "20"},
      {"z", "30"},
  };
  
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("z", iter->key().ToString());
  EXPECT_EQ("30", iter->value().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("y", iter->key().ToString());
  EXPECT_EQ("20", iter->value().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("x", iter->key().ToString());
  EXPECT_EQ("10", iter->value().ToString());
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Prev with two elements
TEST_F(BlockTest_412, PrevWithTwoElements_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"},
      {"second", "2"},
  };
  
  BlockContents contents = BuildBlock(kvs);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("second", iter->key().ToString());
  
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("first", iter->key().ToString());
  
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

// Test Prev values are correct across restart boundaries
TEST_F(BlockTest_412, PrevValuesCorrectAcrossRestartBoundaries_412) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 10; i++) {
    char key_buf[32], val_buf[32];
    snprintf(key_buf, sizeof(key_buf), "key%03d", i);
    snprintf(val_buf, sizeof(val_buf), "value%03d", i);
    kvs.push_back({std::string(key_buf), std::string(val_buf)});
  }
  
  // Use restart_interval=3 so we have multiple restart points
  BlockContents contents = BuildBlock(kvs, 3);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  std::vector<std::pair<std::string, std::string>> reverse_kvs;
  iter->SeekToLast();
  while (iter->Valid()) {
    reverse_kvs.push_back({iter->key().ToString(), iter->value().ToString()});
    iter->Prev();
  }
  
  ASSERT_EQ(kvs.size(), reverse_kvs.size());
  for (size_t i = 0; i < kvs.size(); i++) {
    size_t ri = kvs.size() - 1 - i;
    EXPECT_EQ(kvs[i].first, reverse_kvs[ri].first);
    EXPECT_EQ(kvs[i].second, reverse_kvs[ri].second);
  }
  
  delete iter;
}

// Test that forward then full reverse gives consistent results
TEST_F(BlockTest_412, ForwardThenFullReverse_412) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"apple", "fruit"},
      {"carrot", "vegetable"},
      {"milk", "dairy"},
      {"steak", "meat"},
      {"water", "drink"},
  };
  
  BlockContents contents = BuildBlock(kvs, 2);
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  
  // Go forward to the end
  iter->SeekToFirst();
  while (iter->Valid()) {
    iter->Next();
  }
  
  // Now SeekToLast and go backward
  iter->SeekToLast();
  int idx = kvs.size() - 1;
  while (iter->Valid()) {
    ASSERT_GE(idx, 0);
    EXPECT_EQ(kvs[idx].first, iter->key().ToString());
    EXPECT_EQ(kvs[idx].second, iter->value().ToString());
    idx--;
    iter->Prev();
  }
  EXPECT_EQ(-1, idx);
  
  delete iter;
}

}  // namespace leveldb
