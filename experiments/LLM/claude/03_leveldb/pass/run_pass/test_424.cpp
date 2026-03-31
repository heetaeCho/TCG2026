#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "leveldb/table.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/table_builder.h"
#include "leveldb/iterator.h"
#include "table/format.h"

namespace leveldb {

// Helper to build a table in a file and open it
class TableTest_424 : public ::testing::Test {
 protected:
  Env* env_;
  std::string fname_;
  Options options_;
  
  void SetUp() override {
    env_ = Env::Default();
    fname_ = testing::TempDir() + "/table_test_424.ldb";
    options_ = Options();
  }

  void TearDown() override {
    env_->RemoveFile(fname_);
  }

  // Build a table with the given key-value pairs
  Status BuildTable(const std::vector<std::pair<std::string, std::string>>& kvs) {
    WritableFile* wfile;
    Status s = env_->NewWritableFile(fname_, &wfile);
    if (!s.ok()) return s;

    TableBuilder builder(options_, wfile);
    for (const auto& kv : kvs) {
      builder.Add(kv.first, kv.second);
    }
    s = builder.Finish();
    if (s.ok()) {
      s = wfile->Close();
    }
    delete wfile;
    return s;
  }

  // Open the table for reading
  Status OpenTable(Table** table) {
    RandomAccessFile* rfile;
    Status s = env_->NewRandomAccessFile(fname_, &rfile);
    if (!s.ok()) return s;

    uint64_t file_size;
    s = env_->GetFileSize(fname_, &file_size);
    if (!s.ok()) {
      delete rfile;
      return s;
    }

    s = Table::Open(options_, rfile, file_size, table);
    if (!s.ok()) {
      delete rfile;
    }
    return s;
  }
};

// Test ApproximateOffsetOf with an empty table
TEST_F(TableTest_424, ApproximateOffsetOfEmptyTable_424) {
  std::vector<std::pair<std::string, std::string>> kvs;
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  // With no entries, any key should return metaindex offset
  uint64_t offset = table->ApproximateOffsetOf("anything");
  // The result should be some valid offset (the metaindex handle offset)
  // We just verify it doesn't crash and returns a value
  EXPECT_GE(offset, 0u);

  delete table;
}

// Test ApproximateOffsetOf with a single entry
TEST_F(TableTest_424, ApproximateOffsetOfSingleEntry_424) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"}
  };
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  // Key before the only entry
  uint64_t offset_before = table->ApproximateOffsetOf("aaa");
  // Key equal to the entry
  uint64_t offset_at = table->ApproximateOffsetOf("key1");
  // Key after the entry
  uint64_t offset_after = table->ApproximateOffsetOf("zzz");

  // offset_before should be <= offset_at since "aaa" < "key1"
  EXPECT_LE(offset_before, offset_at);
  // offset_after should be >= offset_at
  EXPECT_GE(offset_after, offset_at);

  delete table;
}

// Test ApproximateOffsetOf with multiple entries - offsets should be non-decreasing
TEST_F(TableTest_424, ApproximateOffsetOfMultipleEntriesNonDecreasing_424) {
  std::vector<std::pair<std::string, std::string>> kvs;
  // Create enough entries to span multiple blocks
  for (int i = 0; i < 1000; i++) {
    char key[100];
    char val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "value%06d_padding_to_make_it_larger_xxxxxxxxxx", i);
    kvs.push_back({std::string(key), std::string(val)});
  }
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  uint64_t prev_offset = 0;
  for (int i = 0; i < 1000; i += 100) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    uint64_t offset = table->ApproximateOffsetOf(Slice(key));
    EXPECT_GE(offset, prev_offset) << "Offsets should be non-decreasing for key " << key;
    prev_offset = offset;
  }

  delete table;
}

// Test that key before all entries returns offset 0 or the first block offset
TEST_F(TableTest_424, ApproximateOffsetOfKeyBeforeAll_424) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[100];
    char val[1000];
    snprintf(key, sizeof(key), "m_key%06d", i);
    memset(val, 'x', sizeof(val) - 1);
    val[sizeof(val) - 1] = '\0';
    kvs.push_back({std::string(key), std::string(val)});
  }
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  // A key that's before all entries should have a small offset (likely 0)
  uint64_t offset = table->ApproximateOffsetOf("a");
  // It should seek to the first index entry, which points to offset 0 or near 0
  EXPECT_EQ(offset, 0u);

  delete table;
}

// Test that key after all entries returns the metaindex offset
TEST_F(TableTest_424, ApproximateOffsetOfKeyAfterAll_424) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 100; i++) {
    char key[100];
    char val[1000];
    snprintf(key, sizeof(key), "key%06d", i);
    memset(val, 'x', sizeof(val) - 1);
    val[sizeof(val) - 1] = '\0';
    kvs.push_back({std::string(key), std::string(val)});
  }
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  // Key after all entries; index_iter->Valid() should be false
  // Result should be metaindex_handle.offset(), which is near the end of data
  uint64_t offset_after = table->ApproximateOffsetOf("zzzzzzzzz");
  
  // The offset should be greater than 0 for a non-trivial table
  EXPECT_GT(offset_after, 0u);

  // Also, it should be larger than offset for first key
  uint64_t offset_first = table->ApproximateOffsetOf("key000000");
  EXPECT_GE(offset_after, offset_first);

  delete table;
}

// Test with large values that force multiple data blocks
TEST_F(TableTest_424, ApproximateOffsetOfLargeValues_424) {
  options_.block_size = 1024;  // Small block size to force many blocks
  
  std::vector<std::pair<std::string, std::string>> kvs;
  std::string large_val(10000, 'v');
  for (int i = 0; i < 10; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%02d", i);
    kvs.push_back({std::string(key), large_val});
  }
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  uint64_t offset_start = table->ApproximateOffsetOf("key00");
  uint64_t offset_mid = table->ApproximateOffsetOf("key05");
  uint64_t offset_end = table->ApproximateOffsetOf("key09");
  uint64_t offset_past = table->ApproximateOffsetOf("key99");

  // With large values, there should be noticeable differences
  EXPECT_LE(offset_start, offset_mid);
  EXPECT_LE(offset_mid, offset_end);
  EXPECT_LE(offset_end, offset_past);

  // The mid offset should be significantly greater than start for large blocks
  EXPECT_GT(offset_mid, offset_start);

  delete table;
}

// Test with empty key
TEST_F(TableTest_424, ApproximateOffsetOfEmptyKey_424) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val1"},
      {"bbb", "val2"},
      {"ccc", "val3"},
  };
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  // Empty key should be before all entries in bytewise comparison
  uint64_t offset = table->ApproximateOffsetOf(Slice(""));
  EXPECT_EQ(offset, 0u);

  delete table;
}

// Test consistency - calling with same key returns same result
TEST_F(TableTest_424, ApproximateOffsetOfConsistency_424) {
  std::vector<std::pair<std::string, std::string>> kvs;
  std::string val(5000, 'x');
  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%04d", i);
    kvs.push_back({std::string(key), val});
  }
  options_.block_size = 1024;
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  // Same key should always return the same offset
  uint64_t offset1 = table->ApproximateOffsetOf("key0025");
  uint64_t offset2 = table->ApproximateOffsetOf("key0025");
  EXPECT_EQ(offset1, offset2);

  delete table;
}

// Test that ApproximateOffsetOf with a key between entries gives reasonable results
TEST_F(TableTest_424, ApproximateOffsetOfBetweenKeys_424) {
  options_.block_size = 512;  // Small blocks
  
  std::vector<std::pair<std::string, std::string>> kvs;
  std::string val(2000, 'y');
  kvs.push_back({"aaaa", val});
  kvs.push_back({"bbbb", val});
  kvs.push_back({"cccc", val});
  kvs.push_back({"dddd", val});
  kvs.push_back({"eeee", val});
  ASSERT_TRUE(BuildTable(kvs).ok());

  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(&table).ok());

  uint64_t offset_a = table->ApproximateOffsetOf("aaaa");
  uint64_t offset_ab = table->ApproximateOffsetOf("abbb");  // between aaaa and bbbb
  uint64_t offset_b = table->ApproximateOffsetOf("bbbb");

  // The offset for a key between two entries should be between their offsets
  // or equal to the next entry's offset
  EXPECT_GE(offset_ab, offset_a);
  EXPECT_LE(offset_ab, offset_b);

  delete table;
}

}  // namespace leveldb
