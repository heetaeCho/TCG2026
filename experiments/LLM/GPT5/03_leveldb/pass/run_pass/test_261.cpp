// File: db/c_options_set_max_open_files_test.cc

#include <gtest/gtest.h>
#include <climits>

// Minimal includes/declarations based strictly on the provided interface.
#include "leveldb/options.h"

// Mirror of the provided C-API wrapper type (public, from prompt).
// We rely only on its public layout: a publicly accessible `rep` Options.
struct leveldb_options_t { leveldb::Options rep; };

// C-API function under test (from prompt).
extern "C" {
void leveldb_options_set_max_open_files(leveldb_options_t* opt, int n);
}

class LevelDBOptionsCAPI_261 : public ::testing::Test {
protected:
  leveldb_options_t opt_;
};

// Normal operation: sets a positive value exactly.
TEST_F(LevelDBOptionsCAPI_261, SetsPositiveValueExactly_261) {
  const int kValue = 2048;
  leveldb_options_set_max_open_files(&opt_, kValue);
  EXPECT_EQ(opt_.rep.max_open_files, kValue);
}

// Boundary: zero should be accepted and set exactly (no validation implied by interface).
TEST_F(LevelDBOptionsCAPI_261, AcceptsZero_261) {
  leveldb_options_set_max_open_files(&opt_, 0);
  EXPECT_EQ(opt_.rep.max_open_files, 0);
}

// Boundary/Exceptional (observable): negative value should be stored as-is
// since no validation is observable through the interface.
TEST_F(LevelDBOptionsCAPI_261, AcceptsNegativeValue_261) {
  leveldb_options_set_max_open_files(&opt_, -1);
  EXPECT_EQ(opt_.rep.max_open_files, -1);
}

// Boundary: very large value within int range.
TEST_F(LevelDBOptionsCAPI_261, AcceptsIntMax_261) {
  leveldb_options_set_max_open_files(&opt_, INT_MAX);
  EXPECT_EQ(opt_.rep.max_open_files, INT_MAX);
}

// Idempotence/overwrite behavior: multiple calls — last call wins.
TEST_F(LevelDBOptionsCAPI_261, MultipleCalls_LastValueWins_261) {
  leveldb_options_set_max_open_files(&opt_, 10);
  leveldb_options_set_max_open_files(&opt_, 20);
  EXPECT_EQ(opt_.rep.max_open_files, 20);
}

// Non-interference: setting max_open_files does not change other Option fields
// (validate via other public members as observable state).
TEST_F(LevelDBOptionsCAPI_261, DoesNotAffectOtherFields_261) {
  const size_t original_write_buffer_size = opt_.rep.write_buffer_size;
  const size_t original_block_size = opt_.rep.block_size;
  const int original_block_restart_interval = opt_.rep.block_restart_interval;
  const size_t original_max_file_size = opt_.rep.max_file_size;
  const auto original_compression = opt_.rep.compression;

  leveldb_options_set_max_open_files(&opt_, 123);

  EXPECT_EQ(opt_.rep.write_buffer_size, original_write_buffer_size);
  EXPECT_EQ(opt_.rep.block_size, original_block_size);
  EXPECT_EQ(opt_.rep.block_restart_interval, original_block_restart_interval);
  EXPECT_EQ(opt_.rep.max_file_size, original_max_file_size);
  EXPECT_EQ(opt_.rep.compression, original_compression);
}
