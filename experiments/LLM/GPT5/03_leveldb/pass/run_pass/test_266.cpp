// File: db/c_options_set_compression_test.cc

#include <gtest/gtest.h>
#include <climits>

// Assume these public headers exist in the codebase.
#include "leveldb/options.h"   // for leveldb::Options and CompressionType
extern "C" {
  // Forward-declare the C wrapper types/APIs we’re testing.
  struct leveldb_options_t;  // defined in db/c.cc as { public Options rep; }
  void leveldb_options_set_compression(leveldb_options_t* opt, int t);
}

// Helper to access the public wrapper's rep (public per provided snippet).
// We do NOT re-implement internal logic—just observe public state.
struct leveldb_options_t {
 public:
  leveldb::Options rep;
};

// -------- Test Fixture --------
class COptionsSetCompressionTest_266 : public ::testing::Test {
 protected:
  leveldb_options_t opt_;  // default-constructed; options fields are public
};

// Normal operation: sets the compression to the exact integer value cast to enum.
TEST_F(COptionsSetCompressionTest_266, SetsExactEnumValue_266) {
  // Try a few representative integers (we don't rely on specific enum names).
  const int values[] = {0, 1, 2, 7, 42};
  for (int v : values) {
    leveldb_options_set_compression(&opt_, v);
    // Observable effect: the stored enum, when cast back to int, equals input.
    EXPECT_EQ(static_cast<int>(opt_.rep.compression), v) << "Failed for v=" << v;
  }
}

// Boundary condition: negative values should be stored as-is when cast to enum.
TEST_F(COptionsSetCompressionTest_266, AcceptsNegativeValues_266) {
  const int values[] = {-1, -7, INT_MIN};
  for (int v : values) {
    leveldb_options_set_compression(&opt_, v);
    EXPECT_EQ(static_cast<int>(opt_.rep.compression), v) << "Failed for v=" << v;
  }
}

// Boundary condition: very large values (including INT_MAX) are handled via cast.
TEST_F(COptionsSetCompressionTest_266, AcceptsLargeValues_266) {
  const int values[] = {INT_MAX, INT_MAX - 1};
  for (int v : values) {
    leveldb_options_set_compression(&opt_, v);
    EXPECT_EQ(static_cast<int>(opt_.rep.compression), v) << "Failed for v=" << v;
  }
}

// Idempotence across multiple calls: last call wins.
TEST_F(COptionsSetCompressionTest_266, MultipleCalls_LastValueWins_266) {
  leveldb_options_set_compression(&opt_, 1);
  leveldb_options_set_compression(&opt_, 5);
  leveldb_options_set_compression(&opt_, -3);
  EXPECT_EQ(static_cast<int>(opt_.rep.compression), -3);
}

// Non-regression: function must not alter unrelated public fields in Options.
TEST_F(COptionsSetCompressionTest_266, DoesNotModifyOtherFields_266) {
  // Snapshot a few representative, independent fields.
  const bool     create_if_missing_before = opt_.rep.create_if_missing;
  const bool     error_if_exists_before   = opt_.rep.error_if_exists;
  const size_t   write_buffer_before      = opt_.rep.write_buffer_size;
  const int      max_open_files_before    = opt_.rep.max_open_files;
  const size_t   block_size_before        = opt_.rep.block_size;
  const int      restart_interval_before  = opt_.rep.block_restart_interval;
  const size_t   max_file_size_before     = opt_.rep.max_file_size;
  const int      zstd_level_before        = opt_.rep.zstd_compression_level;
  auto* const    env_before               = opt_.rep.env;
  auto* const    log_before               = opt_.rep.info_log;
  auto* const    cache_before             = opt_.rep.block_cache;
  auto* const    comp_before              = opt_.rep.comparator;
  auto* const    filter_before            = opt_.rep.filter_policy;

  // Act
  leveldb_options_set_compression(&opt_, 7);

  // Assert unrelated fields unchanged.
  EXPECT_EQ(opt_.rep.create_if_missing, create_if_missing_before);
  EXPECT_EQ(opt_.rep.error_if_exists,   error_if_exists_before);
  EXPECT_EQ(opt_.rep.write_buffer_size, write_buffer_before);
  EXPECT_EQ(opt_.rep.max_open_files,    max_open_files_before);
  EXPECT_EQ(opt_.rep.block_size,        block_size_before);
  EXPECT_EQ(opt_.rep.block_restart_interval, restart_interval_before);
  EXPECT_EQ(opt_.rep.max_file_size,     max_file_size_before);
  EXPECT_EQ(opt_.rep.zstd_compression_level, zstd_level_before);
  EXPECT_EQ(opt_.rep.env,               env_before);
  EXPECT_EQ(opt_.rep.info_log,          log_before);
  EXPECT_EQ(opt_.rep.block_cache,       cache_before);
  EXPECT_EQ(opt_.rep.comparator,        comp_before);
  EXPECT_EQ(opt_.rep.filter_policy,     filter_before);

  // And, of course, compression reflects the argument.
  EXPECT_EQ(static_cast<int>(opt_.rep.compression), 7);
}
