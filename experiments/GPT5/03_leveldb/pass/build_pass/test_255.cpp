// File: db/options_set_create_if_missing_test_255.cc
#include <gtest/gtest.h>
#include <cstdint>

#include "leveldb/options.h"

// If the function and struct are not declared in a public header,
// include the proper header here. Otherwise, forward-declare exactly
// as provided by the interface (no reimplementation of logic).
extern "C" void leveldb_options_set_create_if_missing(struct leveldb_options_t* opt, uint8_t v);

// The struct layout is part of the provided interface snippet.
struct leveldb_options_t { leveldb::Options rep; };

// ---- Test Fixture ----
class LevelDBOptionsSetCreateIfMissingTest_255 : public ::testing::Test {
protected:
  leveldb_options_t opt_{};
};

// Default should be false according to leveldb::Options defaults.
TEST_F(LevelDBOptionsSetCreateIfMissingTest_255, DefaultIsFalse_255) {
  EXPECT_FALSE(opt_.rep.create_if_missing);
}

// Setting with 1 should enable create_if_missing.
TEST_F(LevelDBOptionsSetCreateIfMissingTest_255, SetTrueWithOne_255) {
  leveldb_options_set_create_if_missing(&opt_, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt_.rep.create_if_missing);
}

// Setting with 0 should disable create_if_missing.
TEST_F(LevelDBOptionsSetCreateIfMissingTest_255, SetFalseWithZero_255) {
  // First set to true to ensure we actually observe a change back to false.
  leveldb_options_set_create_if_missing(&opt_, static_cast<uint8_t>(1));
  ASSERT_TRUE(opt_.rep.create_if_missing);

  leveldb_options_set_create_if_missing(&opt_, static_cast<uint8_t>(0));
  EXPECT_FALSE(opt_.rep.create_if_missing);
}

// Any non-zero value should be treated as true (boundary: 255).
TEST_F(LevelDBOptionsSetCreateIfMissingTest_255, NonZeroByteYieldsTrue_255) {
  leveldb_options_set_create_if_missing(&opt_, static_cast<uint8_t>(255));
  EXPECT_TRUE(opt_.rep.create_if_missing);
}
