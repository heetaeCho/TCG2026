// File: compaction_level_test_79.cc
#include "db/version_set.h"
#include <memory>
#include "gtest/gtest.h"

namespace leveldb {
// Forward declarations to avoid depending on internal headers.
class Options;
// Test-only factory expected to be provided by the codebase (e.g., in a test helper TU).
std::unique_ptr<Compaction> MakeCompactionForTest(const Options* options, int level);
}  // namespace leveldb

using leveldb::Compaction;
using leveldb::MakeCompactionForTest;
using leveldb::Options;

class CompactionTest_79 : public ::testing::Test {
protected:
  // Utility: constructs a Compaction via the public test factory.
  std::unique_ptr<Compaction> MakeAtLevel(int level) {
    // The factory is responsible for supplying a valid Options instance as needed.
    // Tests remain black-box and do not assume anything about Options.
    return MakeCompactionForTest(/*options=*/nullptr, level);
  }
};

// Normal operation: level() reflects the level used at construction.
TEST_F(CompactionTest_79, LevelReflectsConstruction_Level0_79) {
  auto c = MakeAtLevel(0);
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(0, c->level());
}

TEST_F(CompactionTest_79, LevelReflectsConstruction_Level6_79) {
  auto c = MakeAtLevel(6);
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(6, c->level());
}

// Idempotence: multiple calls to level() are stable and consistent.
TEST_F(CompactionTest_79, LevelGetterIsStable_79) {
  auto c = MakeAtLevel(3);
  ASSERT_NE(c, nullptr);
  const int first = c->level();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(first, c->level()) << "level() changed between calls";
  }
}

// Boundary condition within typical [0,6] tiered levels observed in LSM designs.
// (We DO NOT assert validity beyond observing the returned value.)
TEST_F(CompactionTest_79, LevelBoundaryUpperTypical_79) {
  auto c = MakeAtLevel(6);
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(6, c->level());
}

// Defensive check: constructing different levels yields different observed values.
// (Black-box distinctness, not relying on internal state.)
TEST_F(CompactionTest_79, DifferentConstructionsYieldDifferentObservedLevels_79) {
  auto c1 = MakeAtLevel(1);
  auto c2 = MakeAtLevel(2);
  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  EXPECT_EQ(1, c1->level());
  EXPECT_EQ(2, c2->level());
  EXPECT_NE(c1->level(), c2->level());
}
