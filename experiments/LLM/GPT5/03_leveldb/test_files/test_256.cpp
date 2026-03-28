// File: db/c_options_set_error_if_exists_test.cc

#include <gtest/gtest.h>
#include <cstdint>

// Minimal includes / forward declarations based on the provided interface.
#include "leveldb/options.h"

// Forward-declare the wrapper struct and the C-API function under test,
// as shown in the provided partial code.
struct leveldb_options_t { leveldb::Options rep; };

// Function under test (from db/c.cc)
void leveldb_options_set_error_if_exists(leveldb_options_t* opt, uint8_t v);

class OptionsSetErrorIfExistsTest_256 : public ::testing::Test {
protected:
  leveldb_options_t opt{};

  void SetUp() override {
    // Start from a known default state.
    opt.rep = leveldb::Options();  // default-constructed Options
  }
};

// Normal operation: setting 1 should make the bool true.
TEST_F(OptionsSetErrorIfExistsTest_256, SetsTrueWhenValueIs1_256) {
  ASSERT_FALSE(opt.rep.error_if_exists) << "Precondition: default should be false (per interface defaults).";
  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt.rep.error_if_exists);
}

// Boundary: setting 0 should make the bool false.
TEST_F(OptionsSetErrorIfExistsTest_256, SetsFalseWhenValueIs0_256) {
  // First flip it to true to ensure the call can turn it off.
  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(1));
  ASSERT_TRUE(opt.rep.error_if_exists);

  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(0));
  EXPECT_FALSE(opt.rep.error_if_exists);
}

// Non-zero boundary: any non-zero (e.g., 255) should be treated as true.
TEST_F(OptionsSetErrorIfExistsTest_256, SetsTrueWhenValueIsNonZero_256) {
  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(255));
  EXPECT_TRUE(opt.rep.error_if_exists);
}

// Idempotence / Multiple calls: last call’s value wins.
TEST_F(OptionsSetErrorIfExistsTest_256, MultipleCalls_LastValueWins_256) {
  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt.rep.error_if_exists);

  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(0));
  EXPECT_FALSE(opt.rep.error_if_exists);

  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(2));
  EXPECT_TRUE(opt.rep.error_if_exists);
}

// Regression guard: other option fields remain unchanged by this setter.
TEST_F(OptionsSetErrorIfExistsTest_256, DoesNotAffectOtherFields_256) {
  const auto initial_write_buffer_size = opt.rep.write_buffer_size;
  const auto initial_block_size = opt.rep.block_size;
  const auto initial_restart_interval = opt.rep.block_restart_interval;
  const auto initial_max_open_files = opt.rep.max_open_files;

  leveldb_options_set_error_if_exists(&opt, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt.rep.error_if_exists);

  // Check a few representative, unrelated fields.
  EXPECT_EQ(opt.rep.write_buffer_size, initial_write_buffer_size);
  EXPECT_EQ(opt.rep.block_size, initial_block_size);
  EXPECT_EQ(opt.rep.block_restart_interval, initial_restart_interval);
  EXPECT_EQ(opt.rep.max_open_files, initial_max_open_files);
}
