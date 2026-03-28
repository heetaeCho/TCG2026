#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "util/testutil.h"
#include "db/db_impl.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class CompactRangeTest_301 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "compact_range_test_301";
    options_.create_if_missing = true;
    // Use a small write buffer to trigger compactions more easily
    options_.write_buffer_size = 1024;
    ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  // Helper to put multiple key-value pairs
  void FillDB(int num_entries, const std::string& key_prefix = "key",
              const std::string& value_prefix = "value") {
    WriteOptions write_options;
    for (int i = 0; i < num_entries; i++) {
      std::string key = key_prefix + std::to_string(i);
      std::string value = value_prefix + std::to_string(i);
      ASSERT_TRUE(db_->Put(write_options, key, value).ok());
    }
  }

  std::string Get(const std::string& key) {
    ReadOptions read_options;
    std::string value;
    Status s = db_->Get(read_options, key, &value);
    if (s.IsNotFound()) {
      return "NOT_FOUND";
    }
    EXPECT_TRUE(s.ok());
    return value;
  }
};

// Test CompactRange with nullptr for both begin and end (compact entire DB)
TEST_F(CompactRangeTest_301, CompactEntireRange_301) {
  FillDB(100);
  // Compact the entire range
  db_->CompactRange(nullptr, nullptr);
  // Verify data is still accessible
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange with specific begin and end
TEST_F(CompactRangeTest_301, CompactSpecificRange_301) {
  FillDB(100);

  Slice begin("key10");
  Slice end("key50");
  db_->CompactRange(&begin, &end);

  // Verify all data is still accessible
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange with only begin specified
TEST_F(CompactRangeTest_301, CompactFromBeginToEnd_301) {
  FillDB(50);

  Slice begin("key10");
  db_->CompactRange(&begin, nullptr);

  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange with only end specified
TEST_F(CompactRangeTest_301, CompactFromStartToEnd_301) {
  FillDB(50);

  Slice end("key30");
  db_->CompactRange(nullptr, &end);

  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange on an empty database
TEST_F(CompactRangeTest_301, CompactEmptyDB_301) {
  db_->CompactRange(nullptr, nullptr);
  // Should not crash; verify the DB is still functional
  ASSERT_TRUE(db_->Put(WriteOptions(), "after_compact", "value").ok());
  EXPECT_EQ("value", Get("after_compact"));
}

// Test CompactRange with a range that covers no existing keys
TEST_F(CompactRangeTest_301, CompactNonOverlappingRange_301) {
  FillDB(50);

  Slice begin("zzz_start");
  Slice end("zzz_end_after");
  db_->CompactRange(&begin, &end);

  // All original data should still be accessible
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange after deletes
TEST_F(CompactRangeTest_301, CompactAfterDeletes_301) {
  FillDB(100);

  WriteOptions write_options;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Delete(write_options, key).ok());
  }

  db_->CompactRange(nullptr, nullptr);

  // Deleted keys should not be found
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    EXPECT_EQ("NOT_FOUND", Get(key));
  }
  // Remaining keys should still be accessible
  for (int i = 50; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange with same begin and end (single key range)
TEST_F(CompactRangeTest_301, CompactSingleKeyRange_301) {
  FillDB(50);

  Slice point("key25");
  db_->CompactRange(&point, &point);

  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test multiple consecutive CompactRange calls
TEST_F(CompactRangeTest_301, MultipleCompactions_301) {
  FillDB(200);

  db_->CompactRange(nullptr, nullptr);
  db_->CompactRange(nullptr, nullptr);

  for (int i = 0; i < 200; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange with large amount of data to trigger multi-level compaction
TEST_F(CompactRangeTest_301, CompactLargeDataset_301) {
  // Write enough data to span multiple levels
  WriteOptions write_options;
  for (int i = 0; i < 1000; i++) {
    char key[100];
    char value[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(value, sizeof(value), "value%06d", i);
    ASSERT_TRUE(db_->Put(write_options, key, value).ok());
  }

  db_->CompactRange(nullptr, nullptr);

  // Verify all data
  for (int i = 0; i < 1000; i++) {
    char key[100];
    char expected_value[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(expected_value, sizeof(expected_value), "value%06d", i);
    ReadOptions read_options;
    std::string actual_value;
    ASSERT_TRUE(db_->Get(read_options, key, &actual_value).ok());
    EXPECT_EQ(std::string(expected_value), actual_value);
  }
}

// Test CompactRange preserves data written after compaction starts
TEST_F(CompactRangeTest_301, WriteAfterCompact_301) {
  FillDB(50);
  db_->CompactRange(nullptr, nullptr);

  // Write more data after compaction
  WriteOptions write_options;
  for (int i = 50; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, value).ok());
  }

  // Verify both old and new data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test CompactRange with overwrites
TEST_F(CompactRangeTest_301, CompactWithOverwrites_301) {
  FillDB(50);

  // Overwrite some keys
  WriteOptions write_options;
  for (int i = 0; i < 25; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "newvalue" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, value).ok());
  }

  db_->CompactRange(nullptr, nullptr);

  // Verify overwritten values
  for (int i = 0; i < 25; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "newvalue" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
  // Verify non-overwritten values
  for (int i = 25; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    EXPECT_EQ(expected_value, Get(key));
  }
}

// Test that iterator works correctly after CompactRange
TEST_F(CompactRangeTest_301, IteratorAfterCompact_301) {
  WriteOptions write_options;
  for (int i = 0; i < 50; i++) {
    char key[100];
    char value[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(value, sizeof(value), "value%06d", i);
    ASSERT_TRUE(db_->Put(write_options, key, value).ok());
  }

  db_->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  Iterator* iter = db_->NewIterator(read_options);
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(50, count);
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

}  // namespace leveldb
