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
extern "C" void leveldb_options_set_error_if_exists(leveldb_options_t* opt, uint8_t v);

class LevelDBOptionsErrorIfExistsTest_256 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that the default value of error_if_exists is false
TEST_F(LevelDBOptionsErrorIfExistsTest_256, DefaultValueIsFalse_256) {
  EXPECT_FALSE(opt_->rep.error_if_exists);
}

// Test setting error_if_exists to true (non-zero value 1)
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetToTrue_256) {
  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);
}

// Test setting error_if_exists to false (zero value)
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetToFalse_256) {
  // First set to true, then set back to false
  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);

  leveldb_options_set_error_if_exists(opt_, 0);
  EXPECT_FALSE(opt_->rep.error_if_exists);
}

// Test setting error_if_exists with a non-zero value other than 1
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetToNonZeroValue_256) {
  leveldb_options_set_error_if_exists(opt_, 42);
  EXPECT_TRUE(opt_->rep.error_if_exists);
}

// Test setting error_if_exists with the maximum uint8_t value (255)
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetToMaxUint8_256) {
  leveldb_options_set_error_if_exists(opt_, 255);
  EXPECT_TRUE(opt_->rep.error_if_exists);
}

// Test that setting the value multiple times works correctly
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetMultipleTimes_256) {
  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);

  leveldb_options_set_error_if_exists(opt_, 0);
  EXPECT_FALSE(opt_->rep.error_if_exists);

  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);

  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);
}

// Test setting to zero explicitly after default
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetToZeroFromDefault_256) {
  leveldb_options_set_error_if_exists(opt_, 0);
  EXPECT_FALSE(opt_->rep.error_if_exists);
}

// Test idempotency of setting to true
TEST_F(LevelDBOptionsErrorIfExistsTest_256, IdempotentSetTrue_256) {
  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);

  leveldb_options_set_error_if_exists(opt_, 1);
  EXPECT_TRUE(opt_->rep.error_if_exists);
}

// Test idempotency of setting to false
TEST_F(LevelDBOptionsErrorIfExistsTest_256, IdempotentSetFalse_256) {
  leveldb_options_set_error_if_exists(opt_, 0);
  EXPECT_FALSE(opt_->rep.error_if_exists);

  leveldb_options_set_error_if_exists(opt_, 0);
  EXPECT_FALSE(opt_->rep.error_if_exists);
}

// Test boundary value: uint8_t value of 2
TEST_F(LevelDBOptionsErrorIfExistsTest_256, SetToTwo_256) {
  leveldb_options_set_error_if_exists(opt_, 2);
  EXPECT_TRUE(opt_->rep.error_if_exists);
}
