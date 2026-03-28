#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

// We need access to the internal struct to verify behavior through the interface
// Since c.cc exposes these structs, we include the necessary headers
#include "leveldb/options.h"

// Forward declare the struct as defined in db/c.cc
struct leveldb_readoptions_t {
  leveldb::ReadOptions rep;
};

// Declare the function under test
extern "C" void leveldb_readoptions_set_fill_cache(leveldb_readoptions_t* opt, uint8_t v);

class LevelDBReadOptionsSetFillCacheTest_275 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_readoptions_t();
    // Default value of fill_cache should be true according to ReadOptions
    opt_->rep.fill_cache = true;
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_readoptions_t* opt_;
};

// Test that setting fill_cache to 0 (false) works correctly
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, SetFillCacheToFalse_275) {
  leveldb_readoptions_set_fill_cache(opt_, 0);
  EXPECT_FALSE(opt_->rep.fill_cache);
}

// Test that setting fill_cache to 1 (true) works correctly
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, SetFillCacheToTrue_275) {
  // First set to false, then set to true
  opt_->rep.fill_cache = false;
  leveldb_readoptions_set_fill_cache(opt_, 1);
  EXPECT_TRUE(opt_->rep.fill_cache);
}

// Test that setting fill_cache with a non-zero value results in true
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, SetFillCacheToNonZeroValue_275) {
  opt_->rep.fill_cache = false;
  leveldb_readoptions_set_fill_cache(opt_, 255);
  EXPECT_TRUE(opt_->rep.fill_cache);
}

// Test that the default value is true and setting to 0 changes it
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, DefaultValueIsTrueThenSetToFalse_275) {
  EXPECT_TRUE(opt_->rep.fill_cache);
  leveldb_readoptions_set_fill_cache(opt_, 0);
  EXPECT_FALSE(opt_->rep.fill_cache);
}

// Test toggling fill_cache from false to true
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, ToggleFillCache_275) {
  leveldb_readoptions_set_fill_cache(opt_, 0);
  EXPECT_FALSE(opt_->rep.fill_cache);

  leveldb_readoptions_set_fill_cache(opt_, 1);
  EXPECT_TRUE(opt_->rep.fill_cache);

  leveldb_readoptions_set_fill_cache(opt_, 0);
  EXPECT_FALSE(opt_->rep.fill_cache);
}

// Test setting fill_cache to various uint8_t boundary values
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, BoundaryValueMax_275) {
  opt_->rep.fill_cache = false;
  leveldb_readoptions_set_fill_cache(opt_, UINT8_MAX);
  EXPECT_TRUE(opt_->rep.fill_cache);
}

// Test setting fill_cache to 2 (another non-zero, non-one value)
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, SetFillCacheToTwo_275) {
  opt_->rep.fill_cache = false;
  leveldb_readoptions_set_fill_cache(opt_, 2);
  EXPECT_TRUE(opt_->rep.fill_cache);
}

// Test that setting fill_cache does not affect other fields
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, DoesNotAffectOtherFields_275) {
  opt_->rep.verify_checksums = true;
  opt_->rep.snapshot = nullptr;

  leveldb_readoptions_set_fill_cache(opt_, 0);

  EXPECT_TRUE(opt_->rep.verify_checksums);
  EXPECT_EQ(nullptr, opt_->rep.snapshot);
}

// Test repeated calls with same value
TEST_F(LevelDBReadOptionsSetFillCacheTest_275, RepeatedCallsWithSameValue_275) {
  leveldb_readoptions_set_fill_cache(opt_, 1);
  EXPECT_TRUE(opt_->rep.fill_cache);
  leveldb_readoptions_set_fill_cache(opt_, 1);
  EXPECT_TRUE(opt_->rep.fill_cache);

  leveldb_readoptions_set_fill_cache(opt_, 0);
  EXPECT_FALSE(opt_->rep.fill_cache);
  leveldb_readoptions_set_fill_cache(opt_, 0);
  EXPECT_FALSE(opt_->rep.fill_cache);
}
