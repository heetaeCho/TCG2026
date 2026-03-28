// File: version_set_numlevelfiles_test.cc

#include "db/version_set.h"
#include "db/dbformat.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// LevelDB deps typically available in the codebase:
#include "util/logging.h"
#include "util/testutil.h"
#include "util/env.h"
#include "db/filename.h"

using namespace leveldb;

class VersionSet_NumLevelFilesTest_166 : public ::testing::Test {
protected:
  // Minimal fixture that constructs a VersionSet using real types.
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_;  // Not used by NumLevelFiles path
  std::unique_ptr<VersionSet> vset_;

  VersionSet_NumLevelFilesTest_166()
      : options_(),
        icmp_(BytewiseComparator()),
        table_cache_(nullptr) {
    options_.env = Env::Default();
  }

  void SetUp() override {
    // A simple db name; no files are needed for NumLevelFiles tests.
    vset_.reset(new VersionSet("NumLevelFilesTestDB", &options_, table_cache_, &icmp_));
  }
};

// Normal operation: for a freshly constructed VersionSet,
// each level should report 0 files (observable via the public API).
TEST_F(VersionSet_NumLevelFilesTest_166, FreshSet_AllLevelsStartEmpty_166) {
  for (int level = 0; level < config::kNumLevels; ++level) {
    EXPECT_EQ(0, vset_->NumLevelFiles(level)) << "Level " << level << " should start empty";
  }
}

// Boundary: negative level should trigger an assertion/death.
TEST_F(VersionSet_NumLevelFilesTest_166, NegativeLevel_TriggersDeath_166) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH({ vset_->NumLevelFiles(-1); }, "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// Boundary: level == kNumLevels (one past the last valid index) should trigger death.
TEST_F(VersionSet_NumLevelFilesTest_166, EqualToKNumLevels_TriggersDeath_166) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH({ vset_->NumLevelFiles(config::kNumLevels); }, "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// Boundary: a very large out-of-range level should also trigger death.
TEST_F(VersionSet_NumLevelFilesTest_166, FarOutOfRangeLevel_TriggersDeath_166) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH({ vset_->NumLevelFiles(1000); }, "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// Sanity: the highest valid level should be callable and return a non-negative count (0 for fresh set).
TEST_F(VersionSet_NumLevelFilesTest_166, HighestValidLevel_ReturnsCount_166) {
  const int last = config::kNumLevels - 1;
  // Should not crash and should return 0 for a fresh set.
  EXPECT_EQ(0, vset_->NumLevelFiles(last));
}
