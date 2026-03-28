// File: version_set_max_file_size_for_level_test.cc

#include <gtest/gtest.h>
#include "leveldb/options.h"

// Forward declare the function under test (public interface used by production code).
namespace leveldb {
  // Implemented in db/version_set.cc
  uint64_t MaxFileSizeForLevel(const Options* options, int level);
}

namespace {

using namespace leveldb;

class VersionSet_MaxFileSizeForLevelTest_129 : public ::testing::Test {
protected:
  Options opts_;
};

// Verifies: With default Options, the result is positive and does not depend on level.
TEST_F(VersionSet_MaxFileSizeForLevelTest_129, DefaultOptions_LevelIndependence_129) {
  // Choose a variety of level values, including boundary-like cases
  const int levels[] = {0, 1, 2, 6, 100, std::numeric_limits<int>::max()};

  const uint64_t v0 = MaxFileSizeForLevel(&opts_, levels[0]);
  ASSERT_GT(v0, 0u) << "Expected a positive max file size for default options";

  for (int lvl : levels) {
    EXPECT_EQ(v0, MaxFileSizeForLevel(&opts_, lvl))
        << "Expected level " << lvl << " to yield the same value as level 0";
  }
}

// Verifies: Changing Options::max_file_size affects the observed return value (black-box).
TEST_F(VersionSet_MaxFileSizeForLevelTest_129, HonorsChangedMaxFileSize_129) {
  // Baseline with default options
  const uint64_t baseline = MaxFileSizeForLevel(&opts_, /*level=*/0);
  ASSERT_GT(baseline, 0u);

  // Change option and observe different outcome
  const size_t kNewMax = 64 * 1024; // 64 KiB (arbitrary non-default)
  opts_.max_file_size = kNewMax;

  const uint64_t changed = MaxFileSizeForLevel(&opts_, /*level=*/3);
  EXPECT_EQ(static_cast<uint64_t>(kNewMax), changed)
      << "Expected the function to reflect the configured max_file_size";
  // Also ensure it still ignores level differences
  EXPECT_EQ(changed, MaxFileSizeForLevel(&opts_, /*level=*/0));
  EXPECT_EQ(changed, MaxFileSizeForLevel(&opts_, /*level=*/100));
}

// Verifies: Very large configured sizes are returned intact (no truncation/overflow at the interface).
TEST_F(VersionSet_MaxFileSizeForLevelTest_129, LargeConfiguredSizePropagates_129) {
  // Use a large value that comfortably fits in uint64_t
  const uint64_t kLarge = (1ull << 33); // 8 GiB
  opts_.max_file_size = static_cast<size_t>(kLarge);

  const uint64_t observed = MaxFileSizeForLevel(&opts_, /*level=*/5);
  EXPECT_EQ(kLarge, observed);
}

// Verifies: Negative/odd level values do not change the outcome (treated as black-box).
TEST_F(VersionSet_MaxFileSizeForLevelTest_129, RobustToOddLevelValues_129) {
  // Set a distinct value to make equality checks obvious
  opts_.max_file_size = 257 * 1024; // 257 KiB
  const uint64_t expected = MaxFileSizeForLevel(&opts_, /*level=*/0);

  // Although negative levels may not be meaningful, the function under test is observed to
  // be independent of level in the provided interface, so results should match.
  const int odd_levels[] = {-1, -100, std::numeric_limits<int>::min() + 1};
  for (int lvl : odd_levels) {
    EXPECT_EQ(expected, MaxFileSizeForLevel(&opts_, lvl))
        << "Expected odd/negative level " << lvl << " to yield the same value";
  }
}

}  // namespace
