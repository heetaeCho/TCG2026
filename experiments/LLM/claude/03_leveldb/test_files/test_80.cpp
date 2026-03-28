#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test fixture for Compaction tests
class CompactionTest_80 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.max_file_size = 2 * 1024 * 1024;  // 2MB default
  }

  Options options_;
};

// Test that edit() returns a non-null pointer to VersionEdit
TEST_F(CompactionTest_80, EditReturnsNonNull_80) {
  Compaction compaction(&options_, 0);
  VersionEdit* edit = compaction.edit();
  ASSERT_NE(edit, nullptr);
}

// Test that edit() returns the same pointer on multiple calls (consistent reference)
TEST_F(CompactionTest_80, EditReturnsSamePointer_80) {
  Compaction compaction(&options_, 0);
  VersionEdit* edit1 = compaction.edit();
  VersionEdit* edit2 = compaction.edit();
  EXPECT_EQ(edit1, edit2);
}

// Test that level() returns the level passed to the constructor
TEST_F(CompactionTest_80, LevelReturnsConstructorValue_80) {
  Compaction compaction0(&options_, 0);
  EXPECT_EQ(compaction0.level(), 0);

  Compaction compaction1(&options_, 1);
  EXPECT_EQ(compaction1.level(), 1);

  Compaction compaction3(&options_, 3);
  EXPECT_EQ(compaction3.level(), 3);
}

// Test MaxOutputFileSize returns a reasonable value based on options
TEST_F(CompactionTest_80, MaxOutputFileSizeIsPositive_80) {
  Compaction compaction(&options_, 0);
  EXPECT_GT(compaction.MaxOutputFileSize(), 0u);
}

// Test num_input_files returns 0 for a freshly created compaction
TEST_F(CompactionTest_80, NumInputFilesInitiallyZero_80) {
  Compaction compaction(&options_, 0);
  EXPECT_EQ(compaction.num_input_files(0), 0);
  EXPECT_EQ(compaction.num_input_files(1), 0);
}

// Test IsTrivialMove on a fresh compaction with no inputs
TEST_F(CompactionTest_80, IsTrivialMoveNoInputs_80) {
  Compaction compaction(&options_, 0);
  // With no input files, behavior depends on implementation but should not crash
  // A compaction with 0 inputs in both levels - testing observable behavior
  bool result = compaction.IsTrivialMove();
  // We just verify it doesn't crash; the result depends on internal state
  (void)result;
}

// Test that ReleaseInputs doesn't crash on a fresh compaction
TEST_F(CompactionTest_80, ReleaseInputsNoVersion_80) {
  Compaction compaction(&options_, 0);
  // input_version_ is nullptr by default, ReleaseInputs should handle this gracefully
  compaction.ReleaseInputs();
}

// Test AddInputDeletions with a VersionEdit
TEST_F(CompactionTest_80, AddInputDeletionsDoesNotCrash_80) {
  Compaction compaction(&options_, 0);
  VersionEdit edit;
  // With no input files, AddInputDeletions should still work without crashing
  compaction.AddInputDeletions(&edit);
}

// Test different levels for MaxOutputFileSize potentially varying
TEST_F(CompactionTest_80, MaxOutputFileSizeDifferentLevels_80) {
  Compaction compaction0(&options_, 0);
  Compaction compaction1(&options_, 1);
  // Both should return positive values
  EXPECT_GT(compaction0.MaxOutputFileSize(), 0u);
  EXPECT_GT(compaction1.MaxOutputFileSize(), 0u);
}

// Test ShouldStopBefore on a fresh compaction
TEST_F(CompactionTest_80, ShouldStopBeforeFreshCompaction_80) {
  Compaction compaction(&options_, 0);
  Slice key("test_key");
  // On a fresh compaction with no grandparents, should return false
  bool result = compaction.ShouldStopBefore(key);
  EXPECT_FALSE(result);
}

// Test IsBaseLevelForKey on a fresh compaction with no input_version
// Note: This may require a valid input_version to work properly.
// We test that the interface is callable.
TEST_F(CompactionTest_80, LevelBoundaryValues_80) {
  // Test with level 0
  Compaction compaction_level0(&options_, 0);
  EXPECT_EQ(compaction_level0.level(), 0);

  // Test with level 6 (max typical level)
  Compaction compaction_level6(&options_, 6);
  EXPECT_EQ(compaction_level6.level(), 6);
}

// Test that destructor works properly (no double-free, etc.)
TEST_F(CompactionTest_80, DestructorSafe_80) {
  Compaction* compaction = new Compaction(&options_, 0);
  EXPECT_NE(compaction, nullptr);
  delete compaction;
  // If we get here without crash, destructor is safe
}

// Test edit can be modified through the returned pointer
TEST_F(CompactionTest_80, EditCanBeModified_80) {
  Compaction compaction(&options_, 0);
  VersionEdit* edit = compaction.edit();
  ASSERT_NE(edit, nullptr);
  // We can call methods on the returned edit without crashing
  edit->SetLogNumber(42);
  // The edit should retain the modification since it's the same object
  VersionEdit* edit_again = compaction.edit();
  EXPECT_EQ(edit, edit_again);
}

// Test with larger max_file_size option
TEST_F(CompactionTest_80, MaxOutputFileSizeWithLargeOption_80) {
  Options large_options;
  large_options.max_file_size = 64 * 1024 * 1024;  // 64MB
  Compaction compaction(&large_options, 0);
  EXPECT_GT(compaction.MaxOutputFileSize(), 0u);
}

// Test with small max_file_size option
TEST_F(CompactionTest_80, MaxOutputFileSizeWithSmallOption_80) {
  Options small_options;
  small_options.max_file_size = 1024;  // 1KB
  Compaction compaction(&small_options, 0);
  EXPECT_GT(compaction.MaxOutputFileSize(), 0u);
}

}  // namespace leveldb
