#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

#include "leveldb/options.h"

// Access the internal struct definition
struct leveldb_options_t {
  leveldb::Options rep;
};

// Declaration of the function under test
extern "C" void leveldb_options_set_write_buffer_size(leveldb_options_t* opt, size_t s);

class LevelDBOptionsWriteBufferSizeTest_260 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that the default write_buffer_size is 4MB before any modification
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, DefaultWriteBufferSize_260) {
  EXPECT_EQ(opt_->rep.write_buffer_size, 4 * 1024 * 1024);
}

// Test setting a normal write buffer size value
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetNormalSize_260) {
  size_t new_size = 8 * 1024 * 1024;  // 8MB
  leveldb_options_set_write_buffer_size(opt_, new_size);
  EXPECT_EQ(opt_->rep.write_buffer_size, new_size);
}

// Test setting write buffer size to zero
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetZeroSize_260) {
  leveldb_options_set_write_buffer_size(opt_, 0);
  EXPECT_EQ(opt_->rep.write_buffer_size, 0);
}

// Test setting write buffer size to 1 (minimum non-zero)
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetMinimumSize_260) {
  leveldb_options_set_write_buffer_size(opt_, 1);
  EXPECT_EQ(opt_->rep.write_buffer_size, 1);
}

// Test setting write buffer size to maximum size_t value
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetMaxSize_260) {
  size_t max_size = static_cast<size_t>(-1);  // SIZE_MAX
  leveldb_options_set_write_buffer_size(opt_, max_size);
  EXPECT_EQ(opt_->rep.write_buffer_size, max_size);
}

// Test setting write buffer size to a small value (e.g., 1024 bytes)
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetSmallSize_260) {
  leveldb_options_set_write_buffer_size(opt_, 1024);
  EXPECT_EQ(opt_->rep.write_buffer_size, 1024);
}

// Test setting write buffer size to a large value (e.g., 1GB)
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetLargeSize_260) {
  size_t one_gb = 1024ULL * 1024 * 1024;
  leveldb_options_set_write_buffer_size(opt_, one_gb);
  EXPECT_EQ(opt_->rep.write_buffer_size, one_gb);
}

// Test setting write buffer size multiple times (last value wins)
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetMultipleTimes_260) {
  leveldb_options_set_write_buffer_size(opt_, 1024);
  EXPECT_EQ(opt_->rep.write_buffer_size, 1024);

  leveldb_options_set_write_buffer_size(opt_, 2048);
  EXPECT_EQ(opt_->rep.write_buffer_size, 2048);

  leveldb_options_set_write_buffer_size(opt_, 512);
  EXPECT_EQ(opt_->rep.write_buffer_size, 512);
}

// Test that setting write_buffer_size does not affect other fields
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, DoesNotAffectOtherFields_260) {
  int original_max_open_files = opt_->rep.max_open_files;
  size_t original_block_size = opt_->rep.block_size;
  int original_block_restart_interval = opt_->rep.block_restart_interval;
  bool original_create_if_missing = opt_->rep.create_if_missing;

  leveldb_options_set_write_buffer_size(opt_, 16 * 1024 * 1024);

  EXPECT_EQ(opt_->rep.max_open_files, original_max_open_files);
  EXPECT_EQ(opt_->rep.block_size, original_block_size);
  EXPECT_EQ(opt_->rep.block_restart_interval, original_block_restart_interval);
  EXPECT_EQ(opt_->rep.create_if_missing, original_create_if_missing);
}

// Test setting to same value as default (should still work)
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetToDefaultValue_260) {
  size_t default_size = 4 * 1024 * 1024;
  leveldb_options_set_write_buffer_size(opt_, default_size);
  EXPECT_EQ(opt_->rep.write_buffer_size, default_size);
}

// Test with a power-of-two boundary value
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetPowerOfTwoBoundary_260) {
  size_t pow2 = 1ULL << 20;  // 1MB
  leveldb_options_set_write_buffer_size(opt_, pow2);
  EXPECT_EQ(opt_->rep.write_buffer_size, pow2);
}

// Test with a non-power-of-two value
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetNonPowerOfTwo_260) {
  size_t odd_size = 3 * 1024 * 1024 + 7;
  leveldb_options_set_write_buffer_size(opt_, odd_size);
  EXPECT_EQ(opt_->rep.write_buffer_size, odd_size);
}
