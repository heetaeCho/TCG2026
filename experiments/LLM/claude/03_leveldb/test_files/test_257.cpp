#include "gtest/gtest.h"

#include <cstdint>

// Include necessary headers
#include "leveldb/c.h"
#include "leveldb/options.h"

// We need access to the internal struct to verify behavior
// Since c.cc defines these structs, we need to either include or redeclare them
struct leveldb_options_t {
  leveldb::Options rep;
};

// Declare the function under test (from c.cc)
extern "C" {
void leveldb_options_set_paranoid_checks(leveldb_options_t* opt, uint8_t v);
}

class LeveldbOptionsParanoidChecksTest_257 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that paranoid_checks defaults to false
TEST_F(LeveldbOptionsParanoidChecksTest_257, DefaultParanoidChecksIsFalse_257) {
  EXPECT_FALSE(opt_->rep.paranoid_checks);
}

// Test setting paranoid_checks to true (non-zero value 1)
TEST_F(LeveldbOptionsParanoidChecksTest_257, SetParanoidChecksToOne_257) {
  leveldb_options_set_paranoid_checks(opt_, 1);
  EXPECT_TRUE(opt_->rep.paranoid_checks);
}

// Test setting paranoid_checks to false (zero value)
TEST_F(LeveldbOptionsParanoidChecksTest_257, SetParanoidChecksToZero_257) {
  // First set it to true, then back to false
  leveldb_options_set_paranoid_checks(opt_, 1);
  EXPECT_TRUE(opt_->rep.paranoid_checks);

  leveldb_options_set_paranoid_checks(opt_, 0);
  EXPECT_FALSE(opt_->rep.paranoid_checks);
}

// Test setting paranoid_checks with a non-zero value other than 1
TEST_F(LeveldbOptionsParanoidChecksTest_257, SetParanoidChecksToNonZeroValue_257) {
  leveldb_options_set_paranoid_checks(opt_, 42);
  EXPECT_TRUE(opt_->rep.paranoid_checks);
}

// Test setting paranoid_checks with max uint8_t value (255)
TEST_F(LeveldbOptionsParanoidChecksTest_257, SetParanoidChecksToMaxUint8_257) {
  leveldb_options_set_paranoid_checks(opt_, 255);
  EXPECT_TRUE(opt_->rep.paranoid_checks);
}

// Test toggling paranoid_checks multiple times
TEST_F(LeveldbOptionsParanoidChecksTest_257, ToggleParanoidChecksMultipleTimes_257) {
  leveldb_options_set_paranoid_checks(opt_, 1);
  EXPECT_TRUE(opt_->rep.paranoid_checks);

  leveldb_options_set_paranoid_checks(opt_, 0);
  EXPECT_FALSE(opt_->rep.paranoid_checks);

  leveldb_options_set_paranoid_checks(opt_, 1);
  EXPECT_TRUE(opt_->rep.paranoid_checks);

  leveldb_options_set_paranoid_checks(opt_, 0);
  EXPECT_FALSE(opt_->rep.paranoid_checks);
}

// Test setting paranoid_checks to zero when already false (idempotent)
TEST_F(LeveldbOptionsParanoidChecksTest_257, SetParanoidChecksToZeroWhenAlreadyFalse_257) {
  EXPECT_FALSE(opt_->rep.paranoid_checks);
  leveldb_options_set_paranoid_checks(opt_, 0);
  EXPECT_FALSE(opt_->rep.paranoid_checks);
}

// Test setting paranoid_checks to true when already true (idempotent)
TEST_F(LeveldbOptionsParanoidChecksTest_257, SetParanoidChecksToTrueWhenAlreadyTrue_257) {
  leveldb_options_set_paranoid_checks(opt_, 1);
  EXPECT_TRUE(opt_->rep.paranoid_checks);

  leveldb_options_set_paranoid_checks(opt_, 1);
  EXPECT_TRUE(opt_->rep.paranoid_checks);
}

// Test that setting paranoid_checks does not affect other options
TEST_F(LeveldbOptionsParanoidChecksTest_257, DoesNotAffectOtherOptions_257) {
  // Record defaults before
  bool create_if_missing_before = opt_->rep.create_if_missing;
  bool error_if_exists_before = opt_->rep.error_if_exists;
  size_t write_buffer_size_before = opt_->rep.write_buffer_size;
  int max_open_files_before = opt_->rep.max_open_files;

  leveldb_options_set_paranoid_checks(opt_, 1);

  EXPECT_EQ(create_if_missing_before, opt_->rep.create_if_missing);
  EXPECT_EQ(error_if_exists_before, opt_->rep.error_if_exists);
  EXPECT_EQ(write_buffer_size_before, opt_->rep.write_buffer_size);
  EXPECT_EQ(max_open_files_before, opt_->rep.max_open_files);
}
