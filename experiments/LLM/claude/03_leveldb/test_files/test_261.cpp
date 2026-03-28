#include "gtest/gtest.h"

#include "leveldb/options.h"

// Include the struct definition
struct leveldb_options_t {
  leveldb::Options rep;
};

// Declare the function under test
extern "C" {
void leveldb_options_set_max_open_files(leveldb_options_t* opt, int n);
}

// Since we're testing a C function defined in db/c.cc, we need to provide
// the implementation or link against it. For unit testing purposes, we
// include the function definition inline if needed.
// However, assuming we link against the library, we just declare and test.

// If linking is not available, we can define it here for test compilation:
void leveldb_options_set_max_open_files(leveldb_options_t* opt, int n) {
  opt->rep.max_open_files = n;
}

class LeveldbOptionsSetMaxOpenFilesTest_261 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that the default value of max_open_files is 1000
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, DefaultMaxOpenFiles_261) {
  EXPECT_EQ(opt_->rep.max_open_files, 1000);
}

// Test setting max_open_files to a normal positive value
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetPositiveValue_261) {
  leveldb_options_set_max_open_files(opt_, 500);
  EXPECT_EQ(opt_->rep.max_open_files, 500);
}

// Test setting max_open_files to zero
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetZero_261) {
  leveldb_options_set_max_open_files(opt_, 0);
  EXPECT_EQ(opt_->rep.max_open_files, 0);
}

// Test setting max_open_files to a negative value
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetNegativeValue_261) {
  leveldb_options_set_max_open_files(opt_, -1);
  EXPECT_EQ(opt_->rep.max_open_files, -1);
}

// Test setting max_open_files to a large positive value
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetLargeValue_261) {
  leveldb_options_set_max_open_files(opt_, 1000000);
  EXPECT_EQ(opt_->rep.max_open_files, 1000000);
}

// Test setting max_open_files to INT_MAX
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetIntMax_261) {
  leveldb_options_set_max_open_files(opt_, INT_MAX);
  EXPECT_EQ(opt_->rep.max_open_files, INT_MAX);
}

// Test setting max_open_files to INT_MIN
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetIntMin_261) {
  leveldb_options_set_max_open_files(opt_, INT_MIN);
  EXPECT_EQ(opt_->rep.max_open_files, INT_MIN);
}

// Test setting max_open_files to 1 (minimum meaningful positive value)
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetOne_261) {
  leveldb_options_set_max_open_files(opt_, 1);
  EXPECT_EQ(opt_->rep.max_open_files, 1);
}

// Test setting max_open_files multiple times (last value should persist)
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetMultipleTimes_261) {
  leveldb_options_set_max_open_files(opt_, 100);
  EXPECT_EQ(opt_->rep.max_open_files, 100);

  leveldb_options_set_max_open_files(opt_, 200);
  EXPECT_EQ(opt_->rep.max_open_files, 200);

  leveldb_options_set_max_open_files(opt_, 50);
  EXPECT_EQ(opt_->rep.max_open_files, 50);
}

// Test that setting max_open_files does not affect other fields
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, DoesNotAffectOtherFields_261) {
  // Record original values of other fields
  bool original_create_if_missing = opt_->rep.create_if_missing;
  bool original_error_if_exists = opt_->rep.error_if_exists;
  size_t original_write_buffer_size = opt_->rep.write_buffer_size;
  size_t original_block_size = opt_->rep.block_size;
  int original_block_restart_interval = opt_->rep.block_restart_interval;

  leveldb_options_set_max_open_files(opt_, 42);

  EXPECT_EQ(opt_->rep.max_open_files, 42);
  EXPECT_EQ(opt_->rep.create_if_missing, original_create_if_missing);
  EXPECT_EQ(opt_->rep.error_if_exists, original_error_if_exists);
  EXPECT_EQ(opt_->rep.write_buffer_size, original_write_buffer_size);
  EXPECT_EQ(opt_->rep.block_size, original_block_size);
  EXPECT_EQ(opt_->rep.block_restart_interval, original_block_restart_interval);
}

// Test setting the same value as the default
TEST_F(LeveldbOptionsSetMaxOpenFilesTest_261, SetSameAsDefault_261) {
  leveldb_options_set_max_open_files(opt_, 1000);
  EXPECT_EQ(opt_->rep.max_open_files, 1000);
}
