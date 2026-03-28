#include "gtest/gtest.h"
#include "leveldb/options.h"

// We need to access the static function MaxBytesForLevel.
// Since it's defined as static in db/version_set.cc, we need to include it
// or redeclare it for testing purposes. We'll test it through a test helper.

// Forward declaration or inclusion of the function under test.
// Since MaxBytesForLevel is a static function in the .cc file, we need to
// either include the .cc file or use a workaround.
// For unit testing purposes, we include the source file.

namespace leveldb {

// Declare the function signature so we can test it.
// This assumes the function is accessible in the leveldb namespace.
static double MaxBytesForLevel(const Options* options, int level);

}  // namespace leveldb

// Include the actual implementation
#include "db/version_set.cc"

namespace leveldb {

class MaxBytesForLevelTest_128 : public ::testing::Test {
 protected:
  Options options_;
};

// Test level 1: The base case. Level 1 should return 10 * 1048576.0
// because the while loop condition (level > 1) is false when level == 1.
TEST_F(MaxBytesForLevelTest_128, Level1ReturnsBaseMB_128) {
  double result = MaxBytesForLevel(&options_, 1);
  double expected = 10.0 * 1048576.0;  // ~10 MB
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 2: result should be 10 * 1048576.0 * 10 = 100 MB
// The loop runs once (level=2 > 1, multiply by 10, level becomes 1, loop exits).
TEST_F(MaxBytesForLevelTest_128, Level2Returns100MB_128) {
  double result = MaxBytesForLevel(&options_, 2);
  double expected = 10.0 * 1048576.0 * 10.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 3: result should be 10 * 1048576.0 * 100 = 1000 MB
TEST_F(MaxBytesForLevelTest_128, Level3Returns1000MB_128) {
  double result = MaxBytesForLevel(&options_, 3);
  double expected = 10.0 * 1048576.0 * 100.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 4: result should be 10 * 1048576.0 * 1000 = 10000 MB
TEST_F(MaxBytesForLevelTest_128, Level4Returns10000MB_128) {
  double result = MaxBytesForLevel(&options_, 4);
  double expected = 10.0 * 1048576.0 * 1000.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 5
TEST_F(MaxBytesForLevelTest_128, Level5Returns100000MB_128) {
  double result = MaxBytesForLevel(&options_, 5);
  double expected = 10.0 * 1048576.0 * 10000.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 6
TEST_F(MaxBytesForLevelTest_128, Level6Returns1000000MB_128) {
  double result = MaxBytesForLevel(&options_, 6);
  double expected = 10.0 * 1048576.0 * 100000.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 7 (typically max level in LevelDB is 7)
TEST_F(MaxBytesForLevelTest_128, Level7ReturnsCorrectValue_128) {
  double result = MaxBytesForLevel(&options_, 7);
  double expected = 10.0 * 1048576.0 * 1000000.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test level 0: level <= 1, so the loop doesn't execute.
// result should be 10 * 1048576.0
TEST_F(MaxBytesForLevelTest_128, Level0ReturnsBaseMB_128) {
  double result = MaxBytesForLevel(&options_, 0);
  double expected = 10.0 * 1048576.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test negative level: The while loop condition (level > 1) is false,
// so the result should be the base value.
TEST_F(MaxBytesForLevelTest_128, NegativeLevelReturnsBaseMB_128) {
  double result = MaxBytesForLevel(&options_, -1);
  double expected = 10.0 * 1048576.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test that the function scales by 10x per level
TEST_F(MaxBytesForLevelTest_128, ScalesBy10xPerLevel_128) {
  for (int level = 2; level <= 7; ++level) {
    double current = MaxBytesForLevel(&options_, level);
    double previous = MaxBytesForLevel(&options_, level - 1);
    EXPECT_DOUBLE_EQ(current, previous * 10.0)
        << "Failed at level " << level;
  }
}

// Test that a nullptr options pointer doesn't affect the result
// (since the function doesn't seem to use options in the provided code)
TEST_F(MaxBytesForLevelTest_128, NullOptionsStillWorks_128) {
  double result = MaxBytesForLevel(nullptr, 1);
  double expected = 10.0 * 1048576.0;
  EXPECT_DOUBLE_EQ(expected, result);
}

// Test that result is always positive
TEST_F(MaxBytesForLevelTest_128, ResultAlwaysPositive_128) {
  for (int level = 0; level <= 10; ++level) {
    double result = MaxBytesForLevel(&options_, level);
    EXPECT_GT(result, 0.0) << "Failed at level " << level;
  }
}

// Test Options default construction
class OptionsTest_128 : public ::testing::Test {};

TEST_F(OptionsTest_128, DefaultOptionsValues_128) {
  Options options;
  EXPECT_NE(nullptr, options.comparator);
  EXPECT_EQ(false, options.create_if_missing);
  EXPECT_EQ(false, options.error_if_exists);
  EXPECT_EQ(false, options.paranoid_checks);
  EXPECT_NE(nullptr, options.env);
  EXPECT_EQ(nullptr, options.info_log);
  EXPECT_EQ(4u * 1024u * 1024u, options.write_buffer_size);
  EXPECT_EQ(1000, options.max_open_files);
  EXPECT_EQ(nullptr, options.block_cache);
  EXPECT_EQ(4u * 1024u, options.block_size);
  EXPECT_EQ(16, options.block_restart_interval);
  EXPECT_EQ(2u * 1024u * 1024u, options.max_file_size);
  EXPECT_EQ(kSnappyCompression, options.compression);
  EXPECT_EQ(1, options.zstd_compression_level);
  EXPECT_EQ(false, options.reuse_logs);
  EXPECT_EQ(nullptr, options.filter_policy);
}

}  // namespace leveldb
