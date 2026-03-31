#include "gtest/gtest.h"

#include <cstdint>

// Include necessary headers
#include "leveldb/options.h"

// Forward declare / include the C API structures and functions
extern "C" {

struct leveldb_writeoptions_t {
  leveldb::WriteOptions rep;
};

void leveldb_writeoptions_set_sync(leveldb_writeoptions_t* opt, uint8_t v);

}

class LevelDBWriteOptionsTest_279 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_writeoptions_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_writeoptions_t* opt_;
};

// Test that the default sync value is false
TEST_F(LevelDBWriteOptionsTest_279, DefaultSyncIsFalse_279) {
  EXPECT_FALSE(opt_->rep.sync);
}

// Test setting sync to 1 (true)
TEST_F(LevelDBWriteOptionsTest_279, SetSyncToTrue_279) {
  leveldb_writeoptions_set_sync(opt_, 1);
  EXPECT_TRUE(opt_->rep.sync);
}

// Test setting sync to 0 (false)
TEST_F(LevelDBWriteOptionsTest_279, SetSyncToFalse_279) {
  leveldb_writeoptions_set_sync(opt_, 0);
  EXPECT_FALSE(opt_->rep.sync);
}

// Test setting sync to true then back to false
TEST_F(LevelDBWriteOptionsTest_279, SetSyncTrueThenFalse_279) {
  leveldb_writeoptions_set_sync(opt_, 1);
  EXPECT_TRUE(opt_->rep.sync);
  leveldb_writeoptions_set_sync(opt_, 0);
  EXPECT_FALSE(opt_->rep.sync);
}

// Test setting sync with a non-zero value other than 1
TEST_F(LevelDBWriteOptionsTest_279, SetSyncNonZeroValue_279) {
  leveldb_writeoptions_set_sync(opt_, 255);
  // Any non-zero value should be treated as true
  EXPECT_TRUE(opt_->rep.sync);
}

// Test setting sync with value 2
TEST_F(LevelDBWriteOptionsTest_279, SetSyncValueTwo_279) {
  leveldb_writeoptions_set_sync(opt_, 2);
  EXPECT_TRUE(opt_->rep.sync);
}

// Test setting sync multiple times to the same value
TEST_F(LevelDBWriteOptionsTest_279, SetSyncMultipleTimesToTrue_279) {
  leveldb_writeoptions_set_sync(opt_, 1);
  leveldb_writeoptions_set_sync(opt_, 1);
  EXPECT_TRUE(opt_->rep.sync);
}

// Test setting sync multiple times to false
TEST_F(LevelDBWriteOptionsTest_279, SetSyncMultipleTimesToFalse_279) {
  leveldb_writeoptions_set_sync(opt_, 0);
  leveldb_writeoptions_set_sync(opt_, 0);
  EXPECT_FALSE(opt_->rep.sync);
}

// Test boundary: maximum uint8_t value
TEST_F(LevelDBWriteOptionsTest_279, SetSyncMaxUint8_279) {
  leveldb_writeoptions_set_sync(opt_, UINT8_MAX);
  EXPECT_TRUE(opt_->rep.sync);
}

// Test boundary: minimum uint8_t value (0)
TEST_F(LevelDBWriteOptionsTest_279, SetSyncMinUint8_279) {
  leveldb_writeoptions_set_sync(opt_, 0);
  EXPECT_FALSE(opt_->rep.sync);
}
