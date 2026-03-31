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
extern "C" void leveldb_options_set_block_restart_interval(leveldb_options_t* opt, int n);

class LevelDBOptionsBlockRestartIntervalTest_264 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that the default block_restart_interval is 16
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, DefaultValue_264) {
  EXPECT_EQ(opt_->rep.block_restart_interval, 16);
}

// Test setting block_restart_interval to a normal value
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetNormalValue_264) {
  leveldb_options_set_block_restart_interval(opt_, 8);
  EXPECT_EQ(opt_->rep.block_restart_interval, 8);
}

// Test setting block_restart_interval to 1
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToOne_264) {
  leveldb_options_set_block_restart_interval(opt_, 1);
  EXPECT_EQ(opt_->rep.block_restart_interval, 1);
}

// Test setting block_restart_interval to 0
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToZero_264) {
  leveldb_options_set_block_restart_interval(opt_, 0);
  EXPECT_EQ(opt_->rep.block_restart_interval, 0);
}

// Test setting block_restart_interval to a negative value
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToNegative_264) {
  leveldb_options_set_block_restart_interval(opt_, -1);
  EXPECT_EQ(opt_->rep.block_restart_interval, -1);
}

// Test setting block_restart_interval to a large value
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToLargeValue_264) {
  leveldb_options_set_block_restart_interval(opt_, 1000000);
  EXPECT_EQ(opt_->rep.block_restart_interval, 1000000);
}

// Test setting block_restart_interval to INT_MAX
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToIntMax_264) {
  leveldb_options_set_block_restart_interval(opt_, INT_MAX);
  EXPECT_EQ(opt_->rep.block_restart_interval, INT_MAX);
}

// Test setting block_restart_interval to INT_MIN
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToIntMin_264) {
  leveldb_options_set_block_restart_interval(opt_, INT_MIN);
  EXPECT_EQ(opt_->rep.block_restart_interval, INT_MIN);
}

// Test setting block_restart_interval multiple times (last write wins)
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetMultipleTimes_264) {
  leveldb_options_set_block_restart_interval(opt_, 4);
  EXPECT_EQ(opt_->rep.block_restart_interval, 4);

  leveldb_options_set_block_restart_interval(opt_, 32);
  EXPECT_EQ(opt_->rep.block_restart_interval, 32);

  leveldb_options_set_block_restart_interval(opt_, 2);
  EXPECT_EQ(opt_->rep.block_restart_interval, 2);
}

// Test that setting block_restart_interval does not affect other options
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, DoesNotAffectOtherOptions_264) {
  size_t original_write_buffer_size = opt_->rep.write_buffer_size;
  int original_max_open_files = opt_->rep.max_open_files;
  size_t original_block_size = opt_->rep.block_size;
  bool original_create_if_missing = opt_->rep.create_if_missing;

  leveldb_options_set_block_restart_interval(opt_, 42);

  EXPECT_EQ(opt_->rep.block_restart_interval, 42);
  EXPECT_EQ(opt_->rep.write_buffer_size, original_write_buffer_size);
  EXPECT_EQ(opt_->rep.max_open_files, original_max_open_files);
  EXPECT_EQ(opt_->rep.block_size, original_block_size);
  EXPECT_EQ(opt_->rep.create_if_missing, original_create_if_missing);
}

// Test setting the same value as the default
TEST_F(LevelDBOptionsBlockRestartIntervalTest_264, SetToDefaultValue_264) {
  leveldb_options_set_block_restart_interval(opt_, 16);
  EXPECT_EQ(opt_->rep.block_restart_interval, 16);
}
