#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

// Test that creating and destroying read options does not crash
TEST(LevelDBReadOptionsDestroyTest_273, CreateAndDestroy_273) {
  leveldb_readoptions_t* opt = leveldb_readoptions_create();
  ASSERT_NE(opt, nullptr);
  leveldb_readoptions_destroy(opt);
  // If we reach here without crash, the test passes
}

// Test that destroying a nullptr does not crash (boundary condition)
// Note: This depends on implementation behavior with nullptr delete,
// which in C++ is well-defined (no-op). Testing observable behavior.
TEST(LevelDBReadOptionsDestroyTest_273, DestroyNullptr_273) {
  leveldb_readoptions_destroy(nullptr);
  // delete nullptr is a no-op in C++, should not crash
}

// Test creating multiple read options and destroying them
TEST(LevelDBReadOptionsDestroyTest_273, CreateMultipleAndDestroy_273) {
  leveldb_readoptions_t* opt1 = leveldb_readoptions_create();
  leveldb_readoptions_t* opt2 = leveldb_readoptions_create();
  leveldb_readoptions_t* opt3 = leveldb_readoptions_create();

  ASSERT_NE(opt1, nullptr);
  ASSERT_NE(opt2, nullptr);
  ASSERT_NE(opt3, nullptr);

  leveldb_readoptions_destroy(opt1);
  leveldb_readoptions_destroy(opt2);
  leveldb_readoptions_destroy(opt3);
}

// Test that options can be modified before destruction without issues
TEST(LevelDBReadOptionsDestroyTest_273, ModifyThenDestroy_273) {
  leveldb_readoptions_t* opt = leveldb_readoptions_create();
  ASSERT_NE(opt, nullptr);

  leveldb_readoptions_set_verify_checksums(opt, 1);
  leveldb_readoptions_set_fill_cache(opt, 0);

  leveldb_readoptions_destroy(opt);
  // Should not crash after modifying options
}

// Test creating, setting snapshot to null, then destroying
TEST(LevelDBReadOptionsDestroyTest_273, SetSnapshotNullThenDestroy_273) {
  leveldb_readoptions_t* opt = leveldb_readoptions_create();
  ASSERT_NE(opt, nullptr);

  leveldb_readoptions_set_snapshot(opt, nullptr);

  leveldb_readoptions_destroy(opt);
}
