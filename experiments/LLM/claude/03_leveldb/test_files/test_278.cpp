#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

class LevelDBWriteOptionsTest_278 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that creating and destroying write options does not crash
TEST_F(LevelDBWriteOptionsTest_278, CreateAndDestroy_278) {
  leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
  ASSERT_NE(opt, nullptr);
  leveldb_writeoptions_destroy(opt);
}

// Test that destroying a freshly created write options object works correctly
TEST_F(LevelDBWriteOptionsTest_278, DestroyFreshlyCreated_278) {
  leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
  ASSERT_NE(opt, nullptr);
  // Should not crash or cause memory issues
  leveldb_writeoptions_destroy(opt);
}

// Test that multiple write options can be created and destroyed independently
TEST_F(LevelDBWriteOptionsTest_278, MultipleCreateAndDestroy_278) {
  leveldb_writeoptions_t* opt1 = leveldb_writeoptions_create();
  leveldb_writeoptions_t* opt2 = leveldb_writeoptions_create();
  leveldb_writeoptions_t* opt3 = leveldb_writeoptions_create();

  ASSERT_NE(opt1, nullptr);
  ASSERT_NE(opt2, nullptr);
  ASSERT_NE(opt3, nullptr);

  // Destroy in different order than creation
  leveldb_writeoptions_destroy(opt2);
  leveldb_writeoptions_destroy(opt1);
  leveldb_writeoptions_destroy(opt3);
}

// Test that setting sync before destroying does not cause issues
TEST_F(LevelDBWriteOptionsTest_278, SetSyncThenDestroy_278) {
  leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
  ASSERT_NE(opt, nullptr);
  leveldb_writeoptions_set_sync(opt, 1);
  leveldb_writeoptions_destroy(opt);
}

// Test that setting sync to false before destroying does not cause issues
TEST_F(LevelDBWriteOptionsTest_278, SetSyncFalseThenDestroy_278) {
  leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
  ASSERT_NE(opt, nullptr);
  leveldb_writeoptions_set_sync(opt, 0);
  leveldb_writeoptions_destroy(opt);
}

// Test create-modify-destroy cycle multiple times to check for leaks
TEST_F(LevelDBWriteOptionsTest_278, RepeatedCreateModifyDestroy_278) {
  for (int i = 0; i < 100; i++) {
    leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
    ASSERT_NE(opt, nullptr);
    leveldb_writeoptions_set_sync(opt, i % 2);
    leveldb_writeoptions_destroy(opt);
  }
}
