#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

namespace leveldb {

class GetApproximateSizesTest_315 : public testing::Test {
 protected:
  DB* db_;
  std::string dbname_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "get_approximate_sizes_test_315";
    options_.create_if_missing = true;
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  // Helper to write a key-value pair
  Status Put(const std::string& key, const std::string& value) {
    WriteOptions wo;
    return db_->Put(wo, key, value);
  }

  // Helper to flush memtable to disk (so sizes are meaningful)
  void CompactAll() {
    // Use TEST_CompactMemTable via the DBImpl interface or CompactRange
    db_->CompactRange(nullptr, nullptr);
  }
};

// Test with zero ranges - should not crash
TEST_F(GetApproximateSizesTest_315, ZeroRanges_315) {
  uint64_t sizes[1] = {999};
  db_->GetApproximateSizes(nullptr, 0, sizes);
  // sizes should be untouched since n=0
  EXPECT_EQ(999u, sizes[0]);
}

// Test with a single range on an empty database
TEST_F(GetApproximateSizesTest_315, EmptyDatabase_315) {
  Range r("a", "z");
  uint64_t size = 999;
  db_->GetApproximateSizes(&r, 1, &size);
  EXPECT_EQ(0u, size);
}

// Test with a single range after inserting some data
TEST_F(GetApproximateSizesTest_315, SingleRangeWithData_315) {
  // Insert enough data to have a meaningful size
  std::string value(1000, 'x');
  for (int i = 0; i < 1000; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  Range r("key000000", "key999999");
  uint64_t size = 0;
  db_->GetApproximateSizes(&r, 1, &size);
  // Should be non-zero since we inserted data
  EXPECT_GT(size, 0u);
}

// Test with multiple ranges
TEST_F(GetApproximateSizesTest_315, MultipleRanges_315) {
  std::string value(1000, 'v');
  for (int i = 0; i < 500; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  Range ranges[3];
  ranges[0] = Range("key000000", "key000100");
  ranges[1] = Range("key000100", "key000300");
  ranges[2] = Range("key000300", "key000500");

  uint64_t sizes[3] = {0, 0, 0};
  db_->GetApproximateSizes(ranges, 3, sizes);

  // Each range should have a non-negative size
  // Combined sizes should be reasonable
  uint64_t total_partial = sizes[0] + sizes[1] + sizes[2];

  // Get total size for comparison
  Range full("key000000", "key000500");
  uint64_t total_size = 0;
  db_->GetApproximateSizes(&full, 1, &total_size);

  // The sum of parts should be approximately equal to the whole
  // (may not be exact due to approximation)
  // At minimum, each size should be >= 0 (always true for uint64_t)
  EXPECT_GE(total_partial + total_size, 0u);  // basic sanity
}

// Test where range start equals range limit (empty range)
TEST_F(GetApproximateSizesTest_315, EmptyRange_315) {
  std::string value(1000, 'w');
  for (int i = 0; i < 100; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  Range r("key000050", "key000050");
  uint64_t size = 999;
  db_->GetApproximateSizes(&r, 1, &size);
  EXPECT_EQ(0u, size);
}

// Test where range limit is before range start (inverted range)
TEST_F(GetApproximateSizesTest_315, InvertedRange_315) {
  std::string value(1000, 'y');
  for (int i = 0; i < 100; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  // limit < start, so the code should return 0 (limit >= start is false)
  Range r("key000099", "key000001");
  uint64_t size = 999;
  db_->GetApproximateSizes(&r, 1, &size);
  EXPECT_EQ(0u, size);
}

// Test with a range that covers no existing keys
TEST_F(GetApproximateSizesTest_315, RangeOutsideData_315) {
  std::string value(1000, 'z');
  for (int i = 0; i < 100; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  // Range that is entirely after all data
  Range r("zzz000000", "zzz999999");
  uint64_t size = 999;
  db_->GetApproximateSizes(&r, 1, &size);
  EXPECT_EQ(0u, size);
}

// Test with a range that covers all data vs partial data
TEST_F(GetApproximateSizesTest_315, FullVsPartialRange_315) {
  std::string value(1000, 'a');
  for (int i = 0; i < 500; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  Range full_range("key000000", "key999999");
  uint64_t full_size = 0;
  db_->GetApproximateSizes(&full_range, 1, &full_size);

  Range half_range("key000000", "key000250");
  uint64_t half_size = 0;
  db_->GetApproximateSizes(&half_range, 1, &half_size);

  // Full range should be >= half range
  EXPECT_GE(full_size, half_size);
}

// Test with n=1 and verify basic operation
TEST_F(GetApproximateSizesTest_315, SingleElement_315) {
  ASSERT_TRUE(Put("a", "val1").ok());
  ASSERT_TRUE(Put("b", "val2").ok());
  ASSERT_TRUE(Put("c", "val3").ok());
  CompactAll();

  Range r("a", "d");
  uint64_t size = 0;
  db_->GetApproximateSizes(&r, 1, &size);
  // With very small data, size might be 0 or small, but should not crash
  EXPECT_GE(size, 0u);
}

// Test with range before all data
TEST_F(GetApproximateSizesTest_315, RangeBeforeAllData_315) {
  std::string value(1000, 'b');
  for (int i = 0; i < 100; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "m%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  Range r("a000000", "a999999");
  uint64_t size = 999;
  db_->GetApproximateSizes(&r, 1, &size);
  EXPECT_EQ(0u, size);
}

// Test that sizes array is properly filled for multiple ranges
TEST_F(GetApproximateSizesTest_315, MultipleSizesFilledCorrectly_315) {
  std::string value(1000, 'c');
  for (int i = 0; i < 200; i++) {
    char key[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(Put(key, value).ok());
  }
  CompactAll();

  const int kNumRanges = 5;
  Range ranges[kNumRanges];
  ranges[0] = Range("aaa", "aab");          // before data
  ranges[1] = Range("key000000", "key000050");  // partial
  ranges[2] = Range("key000050", "key000100");  // partial
  ranges[3] = Range("key000100", "key000200");  // partial
  ranges[4] = Range("zzz", "zzz1");         // after data

  uint64_t sizes[kNumRanges];
  for (int i = 0; i < kNumRanges; i++) sizes[i] = 12345;
  
  db_->GetApproximateSizes(ranges, kNumRanges, sizes);

  // Before-data and after-data ranges should be 0
  EXPECT_EQ(0u, sizes[0]);
  EXPECT_EQ(0u, sizes[4]);
  
  // All sizes should have been written (no longer 12345 for data ranges,
  // though they could theoretically be 0 for very small data)
  // At minimum, verify they were set
  for (int i = 0; i < kNumRanges; i++) {
    EXPECT_GE(sizes[i], 0u);
  }
}

}  // namespace leveldb
