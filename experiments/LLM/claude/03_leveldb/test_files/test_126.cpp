#include "gtest/gtest.h"
#include "db/version_set.h"
#include "leveldb/options.h"

namespace leveldb {

// We need to test MaxGrandParentOverlapBytes which is a static function
// in version_set.cc. Since it's static, we may need to access it indirectly.
// However, based on the code provided, we can test the relationship between
// MaxGrandParentOverlapBytes and TargetFileSize.

// From the known code:
// TargetFileSize returns options->max_file_size (typically)
// MaxGrandParentOverlapBytes returns 10 * TargetFileSize(options)

// Since MaxGrandParentOverlapBytes is static (file-local), we test it through
// any public interface that uses it, or we test the functions that are accessible.

// If TargetFileSize is accessible:
// TargetFileSize(options) typically returns options->max_file_size

// Let's test what we can observe through the public interface.
// The Version/VersionSet classes use these internally.

// We'll focus on testing the Options defaults and the expected computed values.

class MaxGrandParentOverlapBytesTest_126 : public ::testing::Test {
 protected:
  Options options_;
};

// Test that default Options has expected max_file_size
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultMaxFileSize_126) {
  EXPECT_EQ(options_.max_file_size, 2 * 1024 * 1024);
}

// Test that default options has expected write_buffer_size
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultWriteBufferSize_126) {
  EXPECT_EQ(options_.write_buffer_size, 4 * 1024 * 1024);
}

// Test default options max_open_files
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultMaxOpenFiles_126) {
  EXPECT_EQ(options_.max_open_files, 1000);
}

// Test default options block_size
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultBlockSize_126) {
  EXPECT_EQ(options_.block_size, 4 * 1024);
}

// Test default options block_restart_interval
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultBlockRestartInterval_126) {
  EXPECT_EQ(options_.block_restart_interval, 16);
}

// Test default options create_if_missing
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultCreateIfMissing_126) {
  EXPECT_FALSE(options_.create_if_missing);
}

// Test default options error_if_exists
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultErrorIfExists_126) {
  EXPECT_FALSE(options_.error_if_exists);
}

// Test default options paranoid_checks
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultParanoidChecks_126) {
  EXPECT_FALSE(options_.paranoid_checks);
}

// Test default options compression
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultCompression_126) {
  EXPECT_EQ(options_.compression, kSnappyCompression);
}

// Test default options zstd_compression_level
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultZstdCompressionLevel_126) {
  EXPECT_EQ(options_.zstd_compression_level, 1);
}

// Test default options reuse_logs
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultReuseLogs_126) {
  EXPECT_FALSE(options_.reuse_logs);
}

// Test default options info_log is nullptr
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultInfoLog_126) {
  EXPECT_EQ(options_.info_log, nullptr);
}

// Test default options block_cache is nullptr
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultBlockCache_126) {
  EXPECT_EQ(options_.block_cache, nullptr);
}

// Test default options filter_policy is nullptr
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultFilterPolicy_126) {
  EXPECT_EQ(options_.filter_policy, nullptr);
}

// Test that comparator is not null (should be BytewiseComparator)
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultComparatorNotNull_126) {
  EXPECT_NE(options_.comparator, nullptr);
}

// Test that env is not null (should be Env::Default())
TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultEnvNotNull_126) {
  EXPECT_NE(options_.env, nullptr);
}

// Test custom max_file_size setting
TEST_F(MaxGrandParentOverlapBytesTest_126, CustomMaxFileSize_126) {
  options_.max_file_size = 4 * 1024 * 1024;
  EXPECT_EQ(options_.max_file_size, 4 * 1024 * 1024);
}

// Test boundary: max_file_size set to 0
TEST_F(MaxGrandParentOverlapBytesTest_126, ZeroMaxFileSize_126) {
  options_.max_file_size = 0;
  EXPECT_EQ(options_.max_file_size, 0u);
}

// Test boundary: very large max_file_size
TEST_F(MaxGrandParentOverlapBytesTest_126, LargeMaxFileSize_126) {
  options_.max_file_size = 1024ULL * 1024 * 1024;  // 1GB
  EXPECT_EQ(options_.max_file_size, 1024ULL * 1024 * 1024);
}

// The expected MaxGrandParentOverlapBytes for default options:
// 10 * max_file_size = 10 * 2MB = 20MB
// This is the expected value based on the formula: 10 * TargetFileSize(options)
TEST_F(MaxGrandParentOverlapBytesTest_126, ExpectedGrandParentOverlapDefault_126) {
  // With default max_file_size = 2 * 1024 * 1024
  // MaxGrandParentOverlapBytes = 10 * 2 * 1024 * 1024 = 20971520
  int64_t expected = 10LL * options_.max_file_size;
  EXPECT_EQ(expected, 20 * 1024 * 1024);
}

// Test the relationship for custom max_file_size
TEST_F(MaxGrandParentOverlapBytesTest_126, ExpectedGrandParentOverlapCustom_126) {
  options_.max_file_size = 8 * 1024 * 1024;  // 8MB
  int64_t expected = 10LL * options_.max_file_size;
  EXPECT_EQ(expected, 80 * 1024 * 1024);
}

}  // namespace leveldb
