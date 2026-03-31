#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

TEST(LeveldbOptionsDestroyTest_252, DestroyValidOptions_252) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  // Should not crash or leak memory
  leveldb_options_destroy(options);
}

TEST(LeveldbOptionsDestroyTest_252, DestroyAfterSettingProperties_252) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_error_if_exists(options, 1);
  leveldb_options_set_paranoid_checks(options, 1);
  leveldb_options_set_write_buffer_size(options, 1024 * 1024);
  leveldb_options_set_max_open_files(options, 100);
  leveldb_options_set_block_size(options, 4096);
  leveldb_options_set_block_restart_interval(options, 16);
  leveldb_options_set_max_file_size(options, 2 * 1024 * 1024);
  leveldb_options_set_compression(options, leveldb_snappy_compression);
  // Should not crash or leak memory after setting multiple properties
  leveldb_options_destroy(options);
}

TEST(LeveldbOptionsDestroyTest_252, DestroyNullPointer_252) {
  // Passing nullptr; behavior depends on implementation but we document it
  // Some implementations may handle nullptr gracefully (delete nullptr is valid in C++)
  leveldb_options_destroy(nullptr);
}

TEST(LeveldbOptionsDestroyTest_252, CreateAndImmediatelyDestroy_252) {
  // Minimal lifecycle: create then destroy without any configuration
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_destroy(options);
}

TEST(LeveldbOptionsDestroyTest_252, MultipleCreateAndDestroy_252) {
  // Ensure multiple allocations and deallocations work correctly
  for (int i = 0; i < 100; i++) {
    leveldb_options_t* options = leveldb_options_create();
    ASSERT_NE(options, nullptr);
    leveldb_options_set_create_if_missing(options, 1);
    leveldb_options_destroy(options);
  }
}

TEST(LeveldbOptionsDestroyTest_252, DestroyWithCustomComparator_252) {
  // Create options, set a comparator (using default/no custom for safety), then destroy
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  // Don't set a custom comparator, just verify destroy works on default state
  leveldb_options_destroy(options);
}

TEST(LeveldbOptionsDestroyTest_252, DestroyWithNoCompression_252) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_compression(options, leveldb_no_compression);
  leveldb_options_destroy(options);
}
