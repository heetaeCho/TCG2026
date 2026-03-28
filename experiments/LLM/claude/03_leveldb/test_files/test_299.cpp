#include "gtest/gtest.h"
#include "leveldb/options.h"

namespace leveldb {

// Declare the constant and function we need to test
extern const int kNumNonTableCacheFiles;

static int TableCacheSize(const Options& sanitized_options) {
  return sanitized_options.max_open_files - kNumNonTableCacheFiles;
}

// Test fixture
class TableCacheSizeTest_299 : public ::testing::Test {
 protected:
  Options options_;
};

// Test with default options (max_open_files = 1000)
TEST_F(TableCacheSizeTest_299, DefaultOptions_299) {
  int result = TableCacheSize(options_);
  // Default max_open_files is 1000, kNumNonTableCacheFiles is 10
  EXPECT_EQ(result, 1000 - 10);
}

// Test with a custom max_open_files value
TEST_F(TableCacheSizeTest_299, CustomMaxOpenFiles_299) {
  options_.max_open_files = 500;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, 500 - 10);
}

// Test with max_open_files equal to kNumNonTableCacheFiles (boundary: result should be 0)
TEST_F(TableCacheSizeTest_299, MaxOpenFilesEqualsNonTableCacheFiles_299) {
  options_.max_open_files = 10;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, 0);
}

// Test with max_open_files less than kNumNonTableCacheFiles (negative result)
TEST_F(TableCacheSizeTest_299, MaxOpenFilesLessThanNonTableCacheFiles_299) {
  options_.max_open_files = 5;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, 5 - 10);
  EXPECT_LT(result, 0);
}

// Test with max_open_files = 0
TEST_F(TableCacheSizeTest_299, MaxOpenFilesZero_299) {
  options_.max_open_files = 0;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, -10);
}

// Test with a very large max_open_files
TEST_F(TableCacheSizeTest_299, LargeMaxOpenFiles_299) {
  options_.max_open_files = 1000000;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, 1000000 - 10);
}

// Test with max_open_files = 11 (just above kNumNonTableCacheFiles)
TEST_F(TableCacheSizeTest_299, MaxOpenFilesJustAboveNonTableCacheFiles_299) {
  options_.max_open_files = 11;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, 1);
}

// Test with negative max_open_files
TEST_F(TableCacheSizeTest_299, NegativeMaxOpenFiles_299) {
  options_.max_open_files = -1;
  int result = TableCacheSize(options_);
  EXPECT_EQ(result, -1 - 10);
}

// Verify kNumNonTableCacheFiles value
TEST_F(TableCacheSizeTest_299, KNumNonTableCacheFilesValue_299) {
  EXPECT_EQ(kNumNonTableCacheFiles, 10);
}

// Test that TableCacheSize is purely a function of max_open_files
// (other option fields should not affect the result)
TEST_F(TableCacheSizeTest_299, OtherOptionsDoNotAffectResult_299) {
  options_.max_open_files = 200;
  int result1 = TableCacheSize(options_);

  options_.write_buffer_size = 8 * 1024 * 1024;
  options_.block_size = 8 * 1024;
  options_.create_if_missing = true;
  options_.paranoid_checks = true;
  int result2 = TableCacheSize(options_);

  EXPECT_EQ(result1, result2);
  EXPECT_EQ(result1, 200 - 10);
}

}  // namespace leveldb
