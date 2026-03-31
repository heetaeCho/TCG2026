#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

// Since we need access to the internal struct for verification,
// we include the necessary headers
#include "leveldb/options.h"

// Forward declaration of the internal struct
struct leveldb_options_t {
  leveldb::Options rep;
};

// We need the C API function declaration
extern "C" {
void leveldb_options_set_block_size(leveldb_options_t* opt, size_t s);
}

class LevelDBOptionsBlockSizeTest_263 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that setting block size to a normal value works correctly
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeNormalValue_263) {
  size_t block_size = 8192;
  leveldb_options_set_block_size(opt_, block_size);
  EXPECT_EQ(opt_->rep.block_size, block_size);
}

// Test that the default block size is 4096 (4 * 1024) before modification
TEST_F(LevelDBOptionsBlockSizeTest_263, DefaultBlockSize_263) {
  EXPECT_EQ(opt_->rep.block_size, 4 * 1024);
}

// Test setting block size to zero (boundary condition)
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeZero_263) {
  leveldb_options_set_block_size(opt_, 0);
  EXPECT_EQ(opt_->rep.block_size, 0);
}

// Test setting block size to 1 (minimum non-zero boundary)
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeOne_263) {
  leveldb_options_set_block_size(opt_, 1);
  EXPECT_EQ(opt_->rep.block_size, 1);
}

// Test setting block size to a very large value
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeLargeValue_263) {
  size_t large_size = static_cast<size_t>(1) << 30;  // 1 GB
  leveldb_options_set_block_size(opt_, large_size);
  EXPECT_EQ(opt_->rep.block_size, large_size);
}

// Test setting block size to maximum size_t value (boundary condition)
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeMaxSizeT_263) {
  size_t max_size = std::numeric_limits<size_t>::max();
  leveldb_options_set_block_size(opt_, max_size);
  EXPECT_EQ(opt_->rep.block_size, max_size);
}

// Test that setting block size multiple times overwrites the previous value
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeMultipleTimes_263) {
  leveldb_options_set_block_size(opt_, 1024);
  EXPECT_EQ(opt_->rep.block_size, 1024);

  leveldb_options_set_block_size(opt_, 2048);
  EXPECT_EQ(opt_->rep.block_size, 2048);

  leveldb_options_set_block_size(opt_, 512);
  EXPECT_EQ(opt_->rep.block_size, 512);
}

// Test setting block size to a power of two
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizePowerOfTwo_263) {
  size_t block_size = 16384;  // 16 KB
  leveldb_options_set_block_size(opt_, block_size);
  EXPECT_EQ(opt_->rep.block_size, block_size);
}

// Test setting block size to a non-power-of-two value
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeNonPowerOfTwo_263) {
  size_t block_size = 5000;
  leveldb_options_set_block_size(opt_, block_size);
  EXPECT_EQ(opt_->rep.block_size, block_size);
}

// Test that setting block size does not affect other options
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeDoesNotAffectOtherOptions_263) {
  size_t original_write_buffer_size = opt_->rep.write_buffer_size;
  int original_max_open_files = opt_->rep.max_open_files;
  int original_block_restart_interval = opt_->rep.block_restart_interval;
  size_t original_max_file_size = opt_->rep.max_file_size;
  bool original_create_if_missing = opt_->rep.create_if_missing;

  leveldb_options_set_block_size(opt_, 16384);

  EXPECT_EQ(opt_->rep.write_buffer_size, original_write_buffer_size);
  EXPECT_EQ(opt_->rep.max_open_files, original_max_open_files);
  EXPECT_EQ(opt_->rep.block_restart_interval, original_block_restart_interval);
  EXPECT_EQ(opt_->rep.max_file_size, original_max_file_size);
  EXPECT_EQ(opt_->rep.create_if_missing, original_create_if_missing);
}

// Test setting block size back to default after changing it
TEST_F(LevelDBOptionsBlockSizeTest_263, SetBlockSizeBackToDefault_263) {
  leveldb_options_set_block_size(opt_, 8192);
  EXPECT_EQ(opt_->rep.block_size, 8192);

  leveldb_options_set_block_size(opt_, 4 * 1024);
  EXPECT_EQ(opt_->rep.block_size, 4 * 1024);
}
