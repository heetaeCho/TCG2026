// File: db/c_options_paranoid_checks_test.cc

#include <cstdint>
#include "gtest/gtest.h"

// Public interface from the prompt / known deps.
#include "leveldb/options.h"

// Forward declarations to avoid depending on private/internal files.
// These match the provided interface snippets.
struct leveldb_options_t { leveldb::Options rep; };
void leveldb_options_set_paranoid_checks(leveldb_options_t* opt, uint8_t v);

class OptionsParanoidChecksTest_257 : public ::testing::Test {
protected:
  leveldb_options_t opt{};
};

// Normal operation: setting to 0 results in false
TEST_F(OptionsParanoidChecksTest_257, SetsFalseWhenZero_257) {
  // Precondition: flip to true to ensure the call actually changes it to false.
  opt.rep.paranoid_checks = true;

  leveldb_options_set_paranoid_checks(&opt, /*v=*/0);

  EXPECT_FALSE(opt.rep.paranoid_checks)
      << "paranoid_checks should become false when v == 0";
}

// Normal operation: setting to 1 results in true
TEST_F(OptionsParanoidChecksTest_257, SetsTrueWhenOne_257) {
  opt.rep.paranoid_checks = false;

  leveldb_options_set_paranoid_checks(&opt, /*v=*/1);

  EXPECT_TRUE(opt.rep.paranoid_checks)
      << "paranoid_checks should become true when v == 1";
}

// Boundary-ish / robustness: any non-zero (e.g., 0xFF) should be treated as true
TEST_F(OptionsParanoidChecksTest_257, SetsTrueWhenNonZero255_257) {
  opt.rep.paranoid_checks = false;

  leveldb_options_set_paranoid_checks(&opt, /*v=*/0xFF);

  EXPECT_TRUE(opt.rep.paranoid_checks)
      << "paranoid_checks should become true when v != 0";
}

// Toggle behavior: true -> false via 0, then false -> true via 1
TEST_F(OptionsParanoidChecksTest_257, ToggleTrueThenFalse_257) {
  opt.rep.paranoid_checks = false;

  leveldb_options_set_paranoid_checks(&opt, /*v=*/1);
  ASSERT_TRUE(opt.rep.paranoid_checks) << "Expected set to true first";

  leveldb_options_set_paranoid_checks(&opt, /*v=*/0);
  EXPECT_FALSE(opt.rep.paranoid_checks) << "Expected set back to false";
}

// No unintended side effects: other option fields remain unchanged
TEST_F(OptionsParanoidChecksTest_257, NoSideEffectsOnOtherFields_257) {
  // Snapshot a few representative fields that should not change.
  auto before_write_buffer_size = opt.rep.write_buffer_size;
  auto before_max_open_files    = opt.rep.max_open_files;
  auto before_block_size        = opt.rep.block_size;
  auto before_restart_interval  = opt.rep.block_restart_interval;
  auto before_max_file_size     = opt.rep.max_file_size;
  auto before_compression       = opt.rep.compression;
  auto before_zstd_level        = opt.rep.zstd_compression_level;
  auto before_reuse_logs        = opt.rep.reuse_logs;
  auto before_comparator        = opt.rep.comparator;
  auto before_env               = opt.rep.env;
  auto before_info_log          = opt.rep.info_log;
  auto before_block_cache       = opt.rep.block_cache;
  auto before_filter_policy     = opt.rep.filter_policy;
  auto before_create_if_missing = opt.rep.create_if_missing;
  auto before_error_if_exists   = opt.rep.error_if_exists;

  // Perform the operation under test with two different values.
  leveldb_options_set_paranoid_checks(&opt, /*v=*/1);
  leveldb_options_set_paranoid_checks(&opt, /*v=*/0);

  // Verify no other fields were mutated.
  EXPECT_EQ(before_write_buffer_size, opt.rep.write_buffer_size);
  EXPECT_EQ(before_max_open_files,    opt.rep.max_open_files);
  EXPECT_EQ(before_block_size,        opt.rep.block_size);
  EXPECT_EQ(before_restart_interval,  opt.rep.block_restart_interval);
  EXPECT_EQ(before_max_file_size,     opt.rep.max_file_size);
  EXPECT_EQ(before_compression,       opt.rep.compression);
  EXPECT_EQ(before_zstd_level,        opt.rep.zstd_compression_level);
  EXPECT_EQ(before_reuse_logs,        opt.rep.reuse_logs);
  EXPECT_EQ(before_comparator,        opt.rep.comparator);
  EXPECT_EQ(before_env,               opt.rep.env);
  EXPECT_EQ(before_info_log,          opt.rep.info_log);
  EXPECT_EQ(before_block_cache,       opt.rep.block_cache);
  EXPECT_EQ(before_filter_policy,     opt.rep.filter_policy);
  EXPECT_EQ(before_create_if_missing, opt.rep.create_if_missing);
  EXPECT_EQ(before_error_if_exists,   opt.rep.error_if_exists);

  // And, of course, the targeted field reflects the last call.
  EXPECT_FALSE(opt.rep.paranoid_checks);
}
