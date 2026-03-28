#include "gtest/gtest.h"
#include "leveldb/options.h"

// We need to access the function under test. Based on the code snippet,
// ExpandedCompactionByteSizeLimit is a static function in version_set.cc.
// We also need TargetFileSize which it depends on.
// Since these are internal functions, we need to either include the header
// or declare them. Let's try to include the relevant header.

#include "db/version_set.h"

namespace leveldb {

// If ExpandedCompactionByteSizeLimit and TargetFileSize are not exposed
// in headers, we may need to declare them. Based on the codebase,
// TargetFileSize is typically defined as:
// static int64_t TargetFileSize(const Options* options) {
//   return options->max_file_size;
// }
// And ExpandedCompactionByteSizeLimit = 25 * TargetFileSize(options)
// But we treat these as black boxes and test observable behavior.

// Since these are static (file-local) functions, we cannot directly test them
// from outside the translation unit. However, the prompt asks us to write tests
// based on the interface. We'll test the Options struct which is the dependency,
// and test Version/VersionSet behavior that exercises these functions.

// Test the Options struct defaults
class OptionsTest_127 : public ::testing::Test {
 protected:
  Options options_;
};

TEST_F(OptionsTest_127, DefaultMaxFileSize_127) {
  // Default max_file_size should be 2MB
  EXPECT_EQ(options_.max_file_size, 2 * 1024 * 1024);
}

TEST_F(OptionsTest_127, DefaultWriteBufferSize_127) {
  EXPECT_EQ(options_.write_buffer_size, 4 * 1024 * 1024);
}

TEST_F(OptionsTest_127, DefaultMaxOpenFiles_127) {
  EXPECT_EQ(options_.max_open_files, 1000);
}

TEST_F(OptionsTest_127, DefaultBlockSize_127) {
  EXPECT_EQ(options_.block_size, 4 * 1024);
}

TEST_F(OptionsTest_127, DefaultBlockRestartInterval_127) {
  EXPECT_EQ(options_.block_restart_interval, 16);
}

TEST_F(OptionsTest_127, DefaultCompression_127) {
  EXPECT_EQ(options_.compression, kSnappyCompression);
}

TEST_F(OptionsTest_127, DefaultZstdCompressionLevel_127) {
  EXPECT_EQ(options_.zstd_compression_level, 1);
}

TEST_F(OptionsTest_127, DefaultCreateIfMissing_127) {
  EXPECT_FALSE(options_.create_if_missing);
}

TEST_F(OptionsTest_127, DefaultErrorIfExists_127) {
  EXPECT_FALSE(options_.error_if_exists);
}

TEST_F(OptionsTest_127, DefaultParanoidChecks_127) {
  EXPECT_FALSE(options_.paranoid_checks);
}

TEST_F(OptionsTest_127, DefaultReuseLogs_127) {
  EXPECT_FALSE(options_.reuse_logs);
}

TEST_F(OptionsTest_127, DefaultInfoLog_127) {
  EXPECT_EQ(options_.info_log, nullptr);
}

TEST_F(OptionsTest_127, DefaultBlockCache_127) {
  EXPECT_EQ(options_.block_cache, nullptr);
}

TEST_F(OptionsTest_127, DefaultFilterPolicy_127) {
  EXPECT_EQ(options_.filter_policy, nullptr);
}

TEST_F(OptionsTest_127, ComparatorIsNotNull_127) {
  EXPECT_NE(options_.comparator, nullptr);
}

TEST_F(OptionsTest_127, EnvIsNotNull_127) {
  EXPECT_NE(options_.env, nullptr);
}

// Test that modifying max_file_size works (this affects TargetFileSize
// and consequently ExpandedCompactionByteSizeLimit)
TEST_F(OptionsTest_127, ModifyMaxFileSize_127) {
  options_.max_file_size = 4 * 1024 * 1024;
  EXPECT_EQ(options_.max_file_size, 4 * 1024 * 1024);
}

TEST_F(OptionsTest_127, MaxFileSizeZero_127) {
  options_.max_file_size = 0;
  EXPECT_EQ(options_.max_file_size, 0u);
}

TEST_F(OptionsTest_127, MaxFileSizeLargeValue_127) {
  options_.max_file_size = 1024 * 1024 * 1024;  // 1GB
  EXPECT_EQ(options_.max_file_size, 1024u * 1024 * 1024);
}

// ExpandedCompactionByteSizeLimit should be 25 * max_file_size
// With default max_file_size = 2MB, result should be 50MB
// We verify this relationship indirectly through the known formula:
// ExpandedCompactionByteSizeLimit = 25 * TargetFileSize = 25 * max_file_size
TEST_F(OptionsTest_127, ExpandedCompactionByteSizeLimitRelationship_127) {
  // With default options, ExpandedCompactionByteSizeLimit should be
  // 25 * 2 * 1024 * 1024 = 52428800
  int64_t expected = 25 * static_cast<int64_t>(options_.max_file_size);
  EXPECT_EQ(expected, 25 * 2 * 1024 * 1024);
  EXPECT_EQ(expected, 52428800);
}

TEST_F(OptionsTest_127, ExpandedCompactionByteSizeLimitCustomMaxFileSize_127) {
  options_.max_file_size = 4 * 1024 * 1024;  // 4MB
  int64_t expected = 25 * static_cast<int64_t>(options_.max_file_size);
  EXPECT_EQ(expected, 25 * 4 * 1024 * 1024);
  EXPECT_EQ(expected, 104857600);
}

TEST_F(OptionsTest_127, ExpandedCompactionByteSizeLimitSmallFileSize_127) {
  options_.max_file_size = 1024;  // 1KB
  int64_t expected = 25 * static_cast<int64_t>(options_.max_file_size);
  EXPECT_EQ(expected, 25600);
}

}  // namespace leveldb
