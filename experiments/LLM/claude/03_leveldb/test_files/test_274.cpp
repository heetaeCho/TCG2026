#include "gtest/gtest.h"

#include <cstdint>

// Include necessary headers
#include "leveldb/options.h"

// Forward declare the C API structures and functions
extern "C" {

struct leveldb_readoptions_t {
  leveldb::ReadOptions rep;
};

void leveldb_readoptions_set_verify_checksums(leveldb_readoptions_t* opt, uint8_t v);

}

// Test fixture
class ReadOptionsVerifyChecksumsTest_274 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_readoptions_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_readoptions_t* opt_;
};

// Test that setting verify_checksums to 1 (true) works
TEST_F(ReadOptionsVerifyChecksumsTest_274, SetVerifyChecksumsTrue_274) {
  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_TRUE(opt_->rep.verify_checksums);
}

// Test that setting verify_checksums to 0 (false) works
TEST_F(ReadOptionsVerifyChecksumsTest_274, SetVerifyChecksumsFalse_274) {
  // First set to true, then back to false
  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_TRUE(opt_->rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(opt_, 0);
  EXPECT_FALSE(opt_->rep.verify_checksums);
}

// Test that the default value of verify_checksums is false
TEST_F(ReadOptionsVerifyChecksumsTest_274, DefaultValueIsFalse_274) {
  EXPECT_FALSE(opt_->rep.verify_checksums);
}

// Test that a non-zero value other than 1 is treated as true
TEST_F(ReadOptionsVerifyChecksumsTest_274, NonZeroValueIsTruthy_274) {
  leveldb_readoptions_set_verify_checksums(opt_, 42);
  EXPECT_TRUE(opt_->rep.verify_checksums);
}

// Test with maximum uint8_t value (255)
TEST_F(ReadOptionsVerifyChecksumsTest_274, MaxUint8Value_274) {
  leveldb_readoptions_set_verify_checksums(opt_, 255);
  EXPECT_TRUE(opt_->rep.verify_checksums);
}

// Test toggling verify_checksums multiple times
TEST_F(ReadOptionsVerifyChecksumsTest_274, ToggleMultipleTimes_274) {
  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_TRUE(opt_->rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(opt_, 0);
  EXPECT_FALSE(opt_->rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_TRUE(opt_->rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(opt_, 0);
  EXPECT_FALSE(opt_->rep.verify_checksums);
}

// Test that setting the same value twice doesn't cause issues
TEST_F(ReadOptionsVerifyChecksumsTest_274, SetSameValueTwice_274) {
  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_TRUE(opt_->rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_TRUE(opt_->rep.verify_checksums);
}

// Test that setting verify_checksums does not affect fill_cache
TEST_F(ReadOptionsVerifyChecksumsTest_274, DoesNotAffectFillCache_274) {
  bool original_fill_cache = opt_->rep.fill_cache;

  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_EQ(original_fill_cache, opt_->rep.fill_cache);

  leveldb_readoptions_set_verify_checksums(opt_, 0);
  EXPECT_EQ(original_fill_cache, opt_->rep.fill_cache);
}

// Test that setting verify_checksums does not affect snapshot
TEST_F(ReadOptionsVerifyChecksumsTest_274, DoesNotAffectSnapshot_274) {
  const leveldb::Snapshot* original_snapshot = opt_->rep.snapshot;

  leveldb_readoptions_set_verify_checksums(opt_, 1);
  EXPECT_EQ(original_snapshot, opt_->rep.snapshot);
}
