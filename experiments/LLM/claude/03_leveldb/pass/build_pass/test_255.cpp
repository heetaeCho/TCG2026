#include "gtest/gtest.h"

#include "leveldb/options.h"

// Include the struct definition from db/c.cc
struct leveldb_options_t {
  leveldb::Options rep;
};

// Declaration of the function under test
extern "C" {
void leveldb_options_set_create_if_missing(leveldb_options_t* opt, uint8_t v);
}

// Since we're testing a C API function defined in db/c.cc, we need to include or link it.
// For the purpose of these tests, we rely on the linker to resolve the symbol.
// If that's not possible, we replicate the function behavior note: but per constraints we treat as black box.

class LeveldbOptionsSetCreateIfMissingTest_255 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t;
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that the default value of create_if_missing is false
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, DefaultIsFalse_255) {
  EXPECT_FALSE(opt_->rep.create_if_missing);
}

// Test setting create_if_missing to true (non-zero value 1)
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, SetToTrue_255) {
  leveldb_options_set_create_if_missing(opt_, 1);
  EXPECT_TRUE(opt_->rep.create_if_missing);
}

// Test setting create_if_missing to false (value 0)
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, SetToFalse_255) {
  // First set to true, then set back to false
  leveldb_options_set_create_if_missing(opt_, 1);
  EXPECT_TRUE(opt_->rep.create_if_missing);

  leveldb_options_set_create_if_missing(opt_, 0);
  EXPECT_FALSE(opt_->rep.create_if_missing);
}

// Test setting create_if_missing with a non-zero value other than 1
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, SetToNonZeroNonOne_255) {
  leveldb_options_set_create_if_missing(opt_, 42);
  EXPECT_TRUE(opt_->rep.create_if_missing);
}

// Test setting with maximum uint8_t value (255)
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, SetToMaxUint8_255) {
  leveldb_options_set_create_if_missing(opt_, 255);
  EXPECT_TRUE(opt_->rep.create_if_missing);
}

// Test toggling the value multiple times
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, ToggleMultipleTimes_255) {
  leveldb_options_set_create_if_missing(opt_, 1);
  EXPECT_TRUE(opt_->rep.create_if_missing);

  leveldb_options_set_create_if_missing(opt_, 0);
  EXPECT_FALSE(opt_->rep.create_if_missing);

  leveldb_options_set_create_if_missing(opt_, 1);
  EXPECT_TRUE(opt_->rep.create_if_missing);

  leveldb_options_set_create_if_missing(opt_, 0);
  EXPECT_FALSE(opt_->rep.create_if_missing);
}

// Test that setting create_if_missing does not affect other options
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, DoesNotAffectOtherOptions_255) {
  // Record initial values of other options
  bool initial_error_if_exists = opt_->rep.error_if_exists;
  bool initial_paranoid_checks = opt_->rep.paranoid_checks;
  size_t initial_write_buffer_size = opt_->rep.write_buffer_size;
  int initial_max_open_files = opt_->rep.max_open_files;
  size_t initial_block_size = opt_->rep.block_size;
  int initial_block_restart_interval = opt_->rep.block_restart_interval;

  leveldb_options_set_create_if_missing(opt_, 1);

  EXPECT_EQ(initial_error_if_exists, opt_->rep.error_if_exists);
  EXPECT_EQ(initial_paranoid_checks, opt_->rep.paranoid_checks);
  EXPECT_EQ(initial_write_buffer_size, opt_->rep.write_buffer_size);
  EXPECT_EQ(initial_max_open_files, opt_->rep.max_open_files);
  EXPECT_EQ(initial_block_size, opt_->rep.block_size);
  EXPECT_EQ(initial_block_restart_interval, opt_->rep.block_restart_interval);
}

// Test setting with value 0 when already false (no-op scenario)
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, SetFalseWhenAlreadyFalse_255) {
  EXPECT_FALSE(opt_->rep.create_if_missing);
  leveldb_options_set_create_if_missing(opt_, 0);
  EXPECT_FALSE(opt_->rep.create_if_missing);
}

// Test setting with value 1 when already true (idempotent scenario)
TEST_F(LeveldbOptionsSetCreateIfMissingTest_255, SetTrueWhenAlreadyTrue_255) {
  leveldb_options_set_create_if_missing(opt_, 1);
  EXPECT_TRUE(opt_->rep.create_if_missing);
  leveldb_options_set_create_if_missing(opt_, 1);
  EXPECT_TRUE(opt_->rep.create_if_missing);
}
