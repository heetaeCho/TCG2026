// File: version_update_stats_test_149.cc
#include <gtest/gtest.h>

#include "db/version_set.h"   // Declares leveldb::Version and GetStats
#include "db/version_edit.h"  // Declares leveldb::FileMetaData

namespace leveldb {

class VersionUpdateStatsTest_149 : public ::testing::Test {
protected:
  // Helper to build GetStats
  static Version::GetStats MakeStats(FileMetaData* f, int level) {
    Version::GetStats s;
    s.seek_file = f;
    s.seek_file_level = level;
    return s;
  }
};

// Normal operation: decrement when file is provided and still above zero.
TEST_F(VersionUpdateStatsTest_149, DecrementsAllowedSeeks_NoTrigger_149) {
  Version v(nullptr);               // Treat as black-box instance
  FileMetaData f;
  f.allowed_seeks = 2;

  auto stats = VersionUpdateStatsTest_149::MakeStats(&f, /*level=*/3);
  const bool triggered = v.UpdateStats(stats);

  EXPECT_EQ(1, f.allowed_seeks) << "Should decrement by exactly 1";
  EXPECT_FALSE(triggered) << "Should not trigger compaction while > 0";
}

// Boundary: exactly reaches zero => triggers (returns true) once.
TEST_F(VersionUpdateStatsTest_149, ReachesZero_TriggersOnce_149) {
  Version v(nullptr);
  FileMetaData f;
  f.allowed_seeks = 1;

  auto stats = VersionUpdateStatsTest_149::MakeStats(&f, /*level=*/0);
  const bool triggered = v.UpdateStats(stats);

  EXPECT_EQ(0, f.allowed_seeks) << "Should decrement to exactly 0";
  EXPECT_TRUE(triggered) << "Should trigger when allowed_seeks <= 0 and no prior file_to_compact";
}

// Boundary: already at zero before call (<= 0) => still decremented and triggers.
TEST_F(VersionUpdateStatsTest_149, AlreadyZeroBeforeCall_Triggers_149) {
  Version v(nullptr);
  FileMetaData f;
  f.allowed_seeks = 0;

  auto stats = VersionUpdateStatsTest_149::MakeStats(&f, /*level=*/2);
  const bool triggered = v.UpdateStats(stats);

  EXPECT_EQ(-1, f.allowed_seeks) << "Should still decrement from 0 to -1";
  EXPECT_TRUE(triggered) << "Should trigger because <= 0 and no prior file_to_compact";
}

// Exceptional/edge: nullptr seek_file => no decrement, no trigger.
TEST_F(VersionUpdateStatsTest_149, NullSeekFile_NoOpAndNoTrigger_149) {
  Version v(nullptr);

  auto stats = VersionUpdateStatsTest_149::MakeStats(/*f=*/nullptr, /*level=*/4);
  const bool triggered = v.UpdateStats(stats);

  EXPECT_FALSE(triggered) << "No file to update => cannot trigger compaction";
  // Nothing else to observe (no accessible internal state); just ensures no crash and false return.
}

// Interaction across calls: once compaction is selected, subsequent zero-crossings do not trigger again.
TEST_F(VersionUpdateStatsTest_149, TriggeredOnce_SubsequentZeroDoesNotTrigger_149) {
  Version v(nullptr);

  // First file reaches <= 0: should trigger.
  FileMetaData f1;
  f1.allowed_seeks = 1;
  auto s1 = VersionUpdateStatsTest_149::MakeStats(&f1, /*level=*/1);
  const bool first_trigger = v.UpdateStats(s1);
  EXPECT_TRUE(first_trigger);
  EXPECT_EQ(0, f1.allowed_seeks);

  // Second file also crosses <= 0: since a compaction target is already chosen internally,
  // UpdateStats should return false on subsequent attempts.
  FileMetaData f2;
  f2.allowed_seeks = 1;
  auto s2 = VersionUpdateStatsTest_149::MakeStats(&f2, /*level=*/5);
  const bool second_trigger = v.UpdateStats(s2);
  EXPECT_EQ(0, f2.allowed_seeks);
  EXPECT_FALSE(second_trigger) << "Should not select another compaction target after one is set";
}

// Sanity: Decrement from a larger number remains non-triggering until zero or below.
TEST_F(VersionUpdateStatsTest_149, LargeCount_NoTriggerUntilZeroOrBelow_149) {
  Version v(nullptr);
  FileMetaData f;
  f.allowed_seeks = 5;

  // One call: 5 -> 4
  EXPECT_FALSE(v.UpdateStats(VersionUpdateStatsTest_149::MakeStats(&f, 0)));
  EXPECT_EQ(4, f.allowed_seeks);

  // Another call: 4 -> 3
  EXPECT_FALSE(v.UpdateStats(VersionUpdateStatsTest_149::MakeStats(&f, 0)));
  EXPECT_EQ(3, f.allowed_seeks);
}

} // namespace leveldb
