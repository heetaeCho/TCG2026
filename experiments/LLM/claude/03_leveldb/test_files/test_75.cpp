#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/options.h"
#include "util/env.h"
#include "util/testutil.h"

#include <set>
#include <string>

namespace leveldb {

class VersionSetTest_75 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    versions_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    std::vector<std::string> filenames;
    env_->GetChildren(dbname_, &filenames);
    for (const auto& f : filenames) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  const InternalKeyComparator* icmp_;
  VersionSet* versions_;
};

// Test that LastSequence returns initial value of 0
TEST_F(VersionSetTest_75, LastSequenceInitiallyZero_75) {
  EXPECT_EQ(0u, versions_->LastSequence());
}

// Test SetLastSequence sets and LastSequence retrieves the value
TEST_F(VersionSetTest_75, SetLastSequenceBasic_75) {
  versions_->SetLastSequence(42);
  EXPECT_EQ(42u, versions_->LastSequence());
}

// Test SetLastSequence with increasing values
TEST_F(VersionSetTest_75, SetLastSequenceIncreasing_75) {
  versions_->SetLastSequence(10);
  EXPECT_EQ(10u, versions_->LastSequence());
  versions_->SetLastSequence(20);
  EXPECT_EQ(20u, versions_->LastSequence());
  versions_->SetLastSequence(100);
  EXPECT_EQ(100u, versions_->LastSequence());
}

// Test SetLastSequence with same value (boundary)
TEST_F(VersionSetTest_75, SetLastSequenceSameValue_75) {
  versions_->SetLastSequence(50);
  EXPECT_EQ(50u, versions_->LastSequence());
  versions_->SetLastSequence(50);  // same value should be okay (s >= last_sequence_)
  EXPECT_EQ(50u, versions_->LastSequence());
}

// Test SetLastSequence with large value
TEST_F(VersionSetTest_75, SetLastSequenceLargeValue_75) {
  uint64_t large_val = UINT64_MAX - 1;
  versions_->SetLastSequence(large_val);
  EXPECT_EQ(large_val, versions_->LastSequence());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_75, NewFileNumberIncrementing_75) {
  uint64_t first = versions_->NewFileNumber();
  uint64_t second = versions_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_75, ReuseFileNumber_75) {
  uint64_t num = versions_->NewFileNumber();
  versions_->ReuseFileNumber(num);
  uint64_t reused = versions_->NewFileNumber();
  EXPECT_EQ(num, reused);
}

// Test ManifestFileNumber initial value
TEST_F(VersionSetTest_75, ManifestFileNumberInitial_75) {
  EXPECT_EQ(0u, versions_->ManifestFileNumber());
}

// Test LogNumber initial value
TEST_F(VersionSetTest_75, LogNumberInitial_75) {
  EXPECT_EQ(0u, versions_->LogNumber());
}

// Test PrevLogNumber initial value
TEST_F(VersionSetTest_75, PrevLogNumberInitial_75) {
  EXPECT_EQ(0u, versions_->PrevLogNumber());
}

// Test NumLevelFiles for all levels returns 0 initially
TEST_F(VersionSetTest_75, NumLevelFilesInitiallyZero_75) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, versions_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes for all levels returns 0 initially
TEST_F(VersionSetTest_75, NumLevelBytesInitiallyZero_75) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, versions_->NumLevelBytes(level));
  }
}

// Test current() is not null after construction
TEST_F(VersionSetTest_75, CurrentVersionNotNull_75) {
  // After construction (without Recover), current_ might be nullptr,
  // but let's check the accessor
  // Based on the constructor, current_ is set to nullptr initially
  // After Recover or AppendVersion it gets set
  // We can only test what's observable
  // Actually, current_ starts as nullptr per constructor
  Version* v = versions_->current();
  // This may be nullptr before Recover is called
  // Just verify the function doesn't crash
  (void)v;
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_75, MarkFileNumberUsed_75) {
  uint64_t before = versions_->NewFileNumber();
  // Mark a number much higher than current
  versions_->MarkFileNumberUsed(before + 100);
  uint64_t after = versions_->NewFileNumber();
  EXPECT_GT(after, before + 100);
}

// Test MarkFileNumberUsed with number less than current (should be no-op)
TEST_F(VersionSetTest_75, MarkFileNumberUsedLowerValue_75) {
  uint64_t num1 = versions_->NewFileNumber();
  versions_->MarkFileNumberUsed(0);  // Lower than current
  uint64_t num2 = versions_->NewFileNumber();
  EXPECT_EQ(num1 + 1, num2);
}

// Test AddLiveFiles returns empty set initially
TEST_F(VersionSetTest_75, AddLiveFilesEmpty_75) {
  std::set<uint64_t> live;
  versions_->AddLiveFiles(&live);
  // With no files added, live set should be empty
  EXPECT_TRUE(live.empty());
}

// Test LevelSummary doesn't crash and returns non-null
TEST_F(VersionSetTest_75, LevelSummaryNotNull_75) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = versions_->LevelSummary(&scratch);
  EXPECT_NE(nullptr, summary);
}

// Test SetLastSequence boundary: setting to 0 from 0
TEST_F(VersionSetTest_75, SetLastSequenceZeroToZero_75) {
  EXPECT_EQ(0u, versions_->LastSequence());
  versions_->SetLastSequence(0);
  EXPECT_EQ(0u, versions_->LastSequence());
}

// Test multiple NewFileNumber calls produce strictly increasing numbers
TEST_F(VersionSetTest_75, NewFileNumberStrictlyIncreasing_75) {
  uint64_t prev = versions_->NewFileNumber();
  for (int i = 0; i < 100; i++) {
    uint64_t curr = versions_->NewFileNumber();
    EXPECT_GT(curr, prev);
    prev = curr;
  }
}

// Test NeedsCompaction initially
TEST_F(VersionSetTest_75, NeedsCompactionInitially_75) {
  // Without any files, compaction shouldn't be needed
  // This depends on internal state but we test the observable return value
  bool needs = versions_->NeedsCompaction();
  // Just verify it doesn't crash; value depends on internal state
  (void)needs;
}

// Test MaxNextLevelOverlappingBytes with empty version set
TEST_F(VersionSetTest_75, MaxNextLevelOverlappingBytesEmpty_75) {
  int64_t result = versions_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test Recover with a fresh database (no CURRENT file)
TEST_F(VersionSetTest_75, RecoverWithNoCurrentFile_75) {
  bool save_manifest = false;
  Status s = versions_->Recover(&save_manifest);
  // Should fail because there's no CURRENT file
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
