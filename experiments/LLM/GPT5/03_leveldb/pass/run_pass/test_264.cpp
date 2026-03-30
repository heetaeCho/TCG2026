// File: db/c_options_set_block_restart_interval_test_264.cc

#include <gtest/gtest.h>
#include <climits>

// Public interface pieces from the prompt
// (kept minimal and matching the provided snippets)
namespace leveldb {
struct Options {
  // Only the fields we need for observable checks
  // Defaults per provided snippet
  const void* comparator = nullptr;   // not used, but present in interface
  bool create_if_missing = false;
  bool error_if_exists = false;
  bool paranoid_checks = false;
  void* env = nullptr;
  void* info_log = nullptr;
  size_t write_buffer_size = 4 * 1024 * 1024;
  int max_open_files = 1000;
  void* block_cache = nullptr;
  size_t block_size = 4 * 1024;
  int block_restart_interval = 16; // default from the snippet
  size_t max_file_size = 2 * 1024 * 1024;
  int compression = 0; // placeholder
  int zstd_compression_level = 1;
  bool reuse_logs = false;
  const void* filter_policy = nullptr;

  Options() = default;
};
}  // namespace leveldb

// Wrapper from the prompt
struct leveldb_options_t {
  leveldb::Options rep;
};

// C API function under test (provided)
extern "C" {
void leveldb_options_set_block_restart_interval(leveldb_options_t* opt, int n);
}

// Test fixture kept simple for clarity
class LeveldbOptionsSetBlockRestartIntervalTest_264 : public ::testing::Test {
protected:
  leveldb_options_t opt_;  // default-constructed with block_restart_interval = 16
};

// Normal operation: sets to a typical positive value
TEST_F(LeveldbOptionsSetBlockRestartIntervalTest_264, SetsValue_Normal_264) {
  ASSERT_EQ(16, opt_.rep.block_restart_interval) << "Precondition: default should be 16";
  leveldb_options_set_block_restart_interval(&opt_, 8);
  EXPECT_EQ(8, opt_.rep.block_restart_interval);
}

// Boundary: zero (verify it accepts and stores zero without adjustment)
TEST_F(LeveldbOptionsSetBlockRestartIntervalTest_264, SetsZeroAllowed_264) {
  leveldb_options_set_block_restart_interval(&opt_, 0);
  EXPECT_EQ(0, opt_.rep.block_restart_interval);
}

// Boundary: negative (no clamping implied by interface; verify direct storage)
TEST_F(LeveldbOptionsSetBlockRestartIntervalTest_264, SetsNegativePreserved_264) {
  leveldb_options_set_block_restart_interval(&opt_, -5);
  EXPECT_EQ(-5, opt_.rep.block_restart_interval);
}

// Boundary: very large positive value (e.g., INT_MAX)
TEST_F(LeveldbOptionsSetBlockRestartIntervalTest_264, SetsLargeValue_264) {
  leveldb_options_set_block_restart_interval(&opt_, INT_MAX);
  EXPECT_EQ(INT_MAX, opt_.rep.block_restart_interval);
}

// Idempotence/overwrite behavior: subsequent calls overwrite prior value
TEST_F(LeveldbOptionsSetBlockRestartIntervalTest_264, SubsequentCallOverwrites_264) {
  leveldb_options_set_block_restart_interval(&opt_, 4);
  ASSERT_EQ(4, opt_.rep.block_restart_interval);
  leveldb_options_set_block_restart_interval(&opt_, 32);
  EXPECT_EQ(32, opt_.rep.block_restart_interval);
}
