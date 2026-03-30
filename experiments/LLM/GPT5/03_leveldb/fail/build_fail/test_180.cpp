#include <gtest/gtest.h>
#include "db/version_set.h"
#include "db/version_edit.h"

// Optional: include your project-specific helper if it exists.
// If you have a test utility that can construct/seed a Compaction, include it:
// #include "db/version_set_test_util.h"

// ===== Helper detection toggles =====
// Define HAS_COMPACTION_TEST_HELPERS=1 in your build if you have a factory
// that can create a Compaction and seed its inputs.
#ifndef HAS_COMPACTION_TEST_HELPERS
#define HAS_COMPACTION_TEST_HELPERS 0
#endif

namespace {

// --- Test utilities (black-box friendly) ---

// Extract the count of DeleteFile occurrences from VersionEdit::DebugString().
static int CountDeleteFileLines(const std::string& dbg) {
  int count = 0;
  // We only rely on the presence of "DeleteFile" as an observable string from DebugString().
  // This does not assume any private state or exact formatting beyond that token.
  std::string::size_type pos = 0;
  while ((pos = dbg.find("DeleteFile", pos)) != std::string::npos) {
    ++count;
    pos += 10; // advance past "DeleteFile"
  }
  return count;
}

// Try to detect a deletion of a specific (level, file_number) in DebugString().
// This is tolerant to formatting, requiring both tokens to appear nearby.
static ::testing::AssertionResult DebugStringContainsDelete(
    const std::string& dbg, int level, uint64_t file_no) {
  // We look for "DeleteFile" and both the level and the file number as decimal tokens.
  const std::string needle_level = std::to_string(level);
  const std::string needle_file  = std::to_string(file_no);

  std::string::size_type pos = 0;
  while ((pos = dbg.find("DeleteFile", pos)) != std::string::npos) {
    // Search a window after "DeleteFile" for tokens.
    auto window_end = dbg.find('\n', pos);
    std::string line = dbg.substr(pos, (window_end == std::string::npos) ? std::string::npos : window_end - pos);
    if (line.find(needle_level) != std::string::npos && line.find(needle_file) != std::string::npos) {
      return ::testing::AssertionSuccess();
    }
    if (window_end == std::string::npos) break;
    pos = window_end + 1;
  }
  return ::testing::AssertionFailure() << "No DeleteFile entry for (level=" << level
                                       << ", file=" << file_no << ") found in DebugString():\n"
                                       << dbg;
}

#if HAS_COMPACTION_TEST_HELPERS
// ---- If you have a helper, declare it here (adjust the signature to your helper) ----
// Example seam (adjust to your real helper if different):
// std::unique_ptr<leveldb::Compaction> MakeCompactionForTest(
//     int base_level,
//     const std::vector<leveldb::FileMetaData*>& level0_inputs,
//     const std::vector<leveldb::FileMetaData*>& level1_inputs);
#endif

// Convenient factory for FileMetaData objects using only public fields.
// (We do not rely on any internal behavior.)
static leveldb::FileMetaData* NewFileMeta(uint64_t number) {
  auto* f = new leveldb::FileMetaData();
  f->number = number;
  return f;
}

// Clean up allocated FileMetaData* vectors.
static void DeleteFiles(const std::vector<leveldb::FileMetaData*>& v) {
  for (auto* p : v) delete p;
}

}  // namespace

// =============================================
// Test Fixture
// =============================================
class CompactionAddInputDeletionsTest_180 : public ::testing::Test {
 protected:
  void TearDown() override {
    DeleteFiles(level0_);
    DeleteFiles(level1_);
  }

  // Test data (purely public-facing FileMetaData creation).
  std::vector<leveldb::FileMetaData*> level0_;
  std::vector<leveldb::FileMetaData*> level1_;
};

// ==========================================================
// Test 1: No inputs -> no deletions added to VersionEdit
// ==========================================================
TEST_F(CompactionAddInputDeletionsTest_180, NoInputs_NoDeletions_180) {
#if !HAS_COMPACTION_TEST_HELPERS
  GTEST_SKIP() << "No compaction construction/seed helper available. "
                  "Provide a factory to build/seed Compaction, then re-run.";
#else
  // Arrange
  // base_level can be any int the helper accepts; choose 2 for variety.
  const int base_level = 2;
  std::unique_ptr<leveldb::Compaction> c = MakeCompactionForTest(base_level, level0_, level1_);
  ASSERT_TRUE(c != nullptr);

  leveldb::VersionEdit ve_before;
  const std::string before_dbg = ve_before.DebugString();
  ASSERT_EQ(CountDeleteFileLines(before_dbg), 0);

  // Act
  c->AddInputDeletions(&ve_before);

  // Assert
  const std::string after_dbg = ve_before.DebugString();
  EXPECT_EQ(CountDeleteFileLines(after_dbg), 0) << "No inputs => no deletions expected.";
#endif
}

// ======================================================================
// Test 2: One file in each input vector -> both deletions are recorded
// ======================================================================
TEST_F(CompactionAddInputDeletionsTest_180, OneFileEachLevel_RemovesBoth_180) {
#if !HAS_COMPACTION_TEST_HELPERS
  GTEST_SKIP() << "No compaction construction/seed helper available. "
                  "Provide a factory to build/seed Compaction, then re-run.";
#else
  // Arrange
  const int base_level = 0;               // inputs_[0] deletions use (level_ + 0)
  const int next_level = base_level + 1;  // inputs_[1] deletions use (level_ + 1)

  level0_.push_back(NewFileMeta(/*number=*/101));
  level1_.push_back(NewFileMeta(/*number=*/202));

  std::unique_ptr<leveldb::Compaction> c = MakeCompactionForTest(base_level, level0_, level1_);
  ASSERT_TRUE(c != nullptr);

  leveldb::VersionEdit edit;
  // Act
  c->AddInputDeletions(&edit);

  // Assert
  const std::string dbg = edit.DebugString();
  EXPECT_EQ(CountDeleteFileLines(dbg), 2);
  EXPECT_TRUE(DebugStringContainsDelete(dbg, base_level,      /*file=*/101));
  EXPECT_TRUE(DebugStringContainsDelete(dbg, next_level,      /*file=*/202));
#endif
}

// ==================================================================================
// Test 3: Multiple files across inputs -> all are recorded with correct levels
// ==================================================================================
TEST_F(CompactionAddInputDeletionsTest_180, MultipleFiles_AllRecordedWithCorrectLevels_180) {
#if !HAS_COMPACTION_TEST_HELPERS
  GTEST_SKIP() << "No compaction construction/seed helper available. "
                  "Provide a factory to build/seed Compaction, then re-run.";
#else
  // Arrange
  const int base_level = 3;
  const int lvl0 = base_level;
  const int lvl1 = base_level + 1;

  level0_.push_back(NewFileMeta(7));
  level0_.push_back(NewFileMeta(8));
  level1_.push_back(NewFileMeta(42));
  level1_.push_back(NewFileMeta(43));
  level1_.push_back(NewFileMeta(44));

  std::unique_ptr<leveldb::Compaction> c = MakeCompactionForTest(base_level, level0_, level1_);
  ASSERT_TRUE(c != nullptr);

  leveldb::VersionEdit edit;

  // Act
  c->AddInputDeletions(&edit);

  // Assert
  const std::string dbg = edit.DebugString();
  EXPECT_EQ(CountDeleteFileLines(dbg), 5);
  EXPECT_TRUE(DebugStringContainsDelete(dbg, lvl0, 7));
  EXPECT_TRUE(DebugStringContainsDelete(dbg, lvl0, 8));
  EXPECT_TRUE(DebugStringContainsDelete(dbg, lvl1, 42));
  EXPECT_TRUE(DebugStringContainsDelete(dbg, lvl1, 43));
  EXPECT_TRUE(DebugStringContainsDelete(dbg, lvl1, 44));
#endif
}

// ==================================================================================
// Test 4: Empty inputs_[1] -> only level_ deletions are recorded
// ==================================================================================
TEST_F(CompactionAddInputDeletionsTest_180, OnlyFirstInput_RemovesOnlyBaseLevel_180) {
#if !HAS_COMPACTION_TEST_HELPERS
  GTEST_SKIP() << "No compaction construction/seed helper available. "
                  "Provide a factory to build/seed Compaction, then re-run.";
#else
  // Arrange
  const int base_level = 1;

  level0_.push_back(NewFileMeta(555));
  // level1_ remains empty

  std::unique_ptr<leveldb::Compaction> c = MakeCompactionForTest(base_level, level0_, level1_);
  ASSERT_TRUE(c != nullptr);

  leveldb::VersionEdit edit;

  // Act
  c->AddInputDeletions(&edit);

  // Assert
  const std::string dbg = edit.DebugString();
  EXPECT_EQ(CountDeleteFileLines(dbg), 1);
  EXPECT_TRUE(DebugStringContainsDelete(dbg, base_level, 555));
#endif
}

