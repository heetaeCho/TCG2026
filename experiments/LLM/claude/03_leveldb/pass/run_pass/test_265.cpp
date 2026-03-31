#include "gtest/gtest.h"

// Include necessary headers
#include "leveldb/c.h"
#include "leveldb/options.h"

// We need access to the internal struct to verify behavior
// Since c.cc defines these structs, we need to replicate or include them
extern "C" {
struct leveldb_options_t {
  leveldb::Options rep;
};
}

class LeveldbOptionsSetMaxFileSizeTest_265 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that the default max_file_size is 2MB before any modification
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, DefaultMaxFileSize_265) {
  EXPECT_EQ(opt_->rep.max_file_size, 2 * 1024 * 1024);
}

// Test setting max_file_size to a normal value
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetNormalValue_265) {
  size_t new_size = 4 * 1024 * 1024;  // 4MB
  leveldb_options_set_max_file_size(opt_, new_size);
  EXPECT_EQ(opt_->rep.max_file_size, new_size);
}

// Test setting max_file_size to zero (boundary condition)
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetToZero_265) {
  leveldb_options_set_max_file_size(opt_, 0);
  EXPECT_EQ(opt_->rep.max_file_size, 0);
}

// Test setting max_file_size to 1 (boundary condition - minimum non-zero)
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetToOne_265) {
  leveldb_options_set_max_file_size(opt_, 1);
  EXPECT_EQ(opt_->rep.max_file_size, 1);
}

// Test setting max_file_size to the maximum possible size_t value
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetToMaxSizeT_265) {
  size_t max_val = std::numeric_limits<size_t>::max();
  leveldb_options_set_max_file_size(opt_, max_val);
  EXPECT_EQ(opt_->rep.max_file_size, max_val);
}

// Test setting max_file_size to a large value (1GB)
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetToLargeValue_265) {
  size_t large_size = 1ULL * 1024 * 1024 * 1024;  // 1GB
  leveldb_options_set_max_file_size(opt_, large_size);
  EXPECT_EQ(opt_->rep.max_file_size, large_size);
}

// Test setting max_file_size to a small value (1 byte)
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetToSmallValue_265) {
  leveldb_options_set_max_file_size(opt_, 512);
  EXPECT_EQ(opt_->rep.max_file_size, 512);
}

// Test setting max_file_size multiple times - last value should stick
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetMultipleTimes_265) {
  leveldb_options_set_max_file_size(opt_, 1024);
  EXPECT_EQ(opt_->rep.max_file_size, 1024);

  leveldb_options_set_max_file_size(opt_, 2048);
  EXPECT_EQ(opt_->rep.max_file_size, 2048);

  leveldb_options_set_max_file_size(opt_, 4096);
  EXPECT_EQ(opt_->rep.max_file_size, 4096);
}

// Test that setting max_file_size does not affect other options fields
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, DoesNotAffectOtherFields_265) {
  size_t original_write_buffer_size = opt_->rep.write_buffer_size;
  size_t original_block_size = opt_->rep.block_size;
  int original_max_open_files = opt_->rep.max_open_files;
  int original_block_restart_interval = opt_->rep.block_restart_interval;
  bool original_create_if_missing = opt_->rep.create_if_missing;

  leveldb_options_set_max_file_size(opt_, 8 * 1024 * 1024);

  EXPECT_EQ(opt_->rep.write_buffer_size, original_write_buffer_size);
  EXPECT_EQ(opt_->rep.block_size, original_block_size);
  EXPECT_EQ(opt_->rep.max_open_files, original_max_open_files);
  EXPECT_EQ(opt_->rep.block_restart_interval, original_block_restart_interval);
  EXPECT_EQ(opt_->rep.create_if_missing, original_create_if_missing);
}

// Test setting back to default value after changing
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetBackToDefault_265) {
  size_t default_size = 2 * 1024 * 1024;
  leveldb_options_set_max_file_size(opt_, 10 * 1024 * 1024);
  EXPECT_EQ(opt_->rep.max_file_size, 10 * 1024 * 1024);

  leveldb_options_set_max_file_size(opt_, default_size);
  EXPECT_EQ(opt_->rep.max_file_size, default_size);
}

// Test with a power-of-two boundary value
TEST_F(LeveldbOptionsSetMaxFileSizeTest_265, SetPowerOfTwo_265) {
  size_t pow2 = 1ULL << 20;  // 1MB
  leveldb_options_set_max_file_size(opt_, pow2);
  EXPECT_EQ(opt_->rep.max_file_size, pow2);
}
