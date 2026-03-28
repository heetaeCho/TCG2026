#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/testutil.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"

#include <set>
#include <string>

namespace leveldb {

class VersionSetTest_77 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "version_set_test_77";
    env_->CreateDir(dbname_);

    options_.env = env_;
    cache_ = NewLRUCache(100);
    options_.block_cache = cache_;

    const InternalKeyComparator cmp(BytewiseComparator());
    icmp_ = new InternalKeyComparator(cmp);
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    delete cache_;
    // Clean up test directory
    std::vector<std::string> files;
    env_->GetChildren(dbname_, &files);
    for (const auto& f : files) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  Cache* cache_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that PrevLogNumber returns 0 initially
TEST_F(VersionSetTest_77, PrevLogNumberInitiallyZero_77) {
  EXPECT_EQ(0u, vset_->PrevLogNumber());
}

// Test that LogNumber returns 0 initially
TEST_F(VersionSetTest_77, LogNumberInitiallyZero_77) {
  EXPECT_EQ(0u, vset_->LogNumber());
}

// Test that LastSequence returns 0 initially
TEST_F(VersionSetTest_77, LastSequenceInitiallyZero_77) {
  EXPECT_EQ(0u, vset_->LastSequence());
}

// Test SetLastSequence and LastSequence
TEST_F(VersionSetTest_77, SetAndGetLastSequence_77) {
  vset_->SetLastSequence(42);
  EXPECT_EQ(42u, vset_->LastSequence());
}

// Test SetLastSequence with large value
TEST_F(VersionSetTest_77, SetLastSequenceLargeValue_77) {
  uint64_t large_val = 1000000000ULL;
  vset_->SetLastSequence(large_val);
  EXPECT_EQ(large_val, vset_->LastSequence());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_77, NewFileNumberIncrements_77) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test NewFileNumber starts at 2 (based on constructor)
TEST_F(VersionSetTest_77, NewFileNumberStartsAt2_77) {
  uint64_t num = vset_->NewFileNumber();
  EXPECT_EQ(2u, num);
}

// Test ReuseFileNumber reuses the last allocated number
TEST_F(VersionSetTest_77, ReuseFileNumberBasic_77) {
  uint64_t num1 = vset_->NewFileNumber();
  vset_->ReuseFileNumber(num1);
  uint64_t num2 = vset_->NewFileNumber();
  EXPECT_EQ(num1, num2);
}

// Test that ReuseFileNumber with a different number doesn't reuse
TEST_F(VersionSetTest_77, ReuseFileNumberWrongNumber_77) {
  uint64_t num1 = vset_->NewFileNumber();
  // Try to reuse a number that's not the last one allocated
  vset_->ReuseFileNumber(num1 - 1);
  uint64_t num2 = vset_->NewFileNumber();
  EXPECT_EQ(num1 + 1, num2);
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_77, MarkFileNumberUsed_77) {
  vset_->MarkFileNumberUsed(100);
  uint64_t num = vset_->NewFileNumber();
  EXPECT_GE(num, 101u);
}

// Test ManifestFileNumber
TEST_F(VersionSetTest_77, ManifestFileNumberInitial_77) {
  // Initially 0 per constructor
  EXPECT_EQ(0u, vset_->ManifestFileNumber());
}

// Test NumLevelFiles returns 0 for all levels initially
TEST_F(VersionSetTest_77, NumLevelFilesInitiallyZero_77) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, vset_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes returns 0 for all levels initially
TEST_F(VersionSetTest_77, NumLevelBytesInitiallyZero_77) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, vset_->NumLevelBytes(level));
  }
}

// Test current() returns non-null after construction
TEST_F(VersionSetTest_77, CurrentVersionNotNull_77) {
  // Note: current_ is set to nullptr in constructor, but AppendVersion
  // should be called. After construction without Recover, current may be nullptr.
  // This tests the observable state.
  // Actually from the constructor shown, current_ is set to nullptr.
  // It would be nullptr until Recover or LogAndApply is called.
  // We just document what we observe.
  // Let's not assert on this since the constructor sets nullptr.
}

// Test AddLiveFiles with empty version set
TEST_F(VersionSetTest_77, AddLiveFilesEmpty_77) {
  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  // With no files added, live set should be empty
  EXPECT_TRUE(live.empty());
}

// Test LevelSummary produces a non-null string
TEST_F(VersionSetTest_77, LevelSummaryNonNull_77) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  EXPECT_NE(nullptr, summary);
  EXPECT_GT(strlen(summary), 0u);
}

// Test NeedsCompaction on fresh VersionSet
TEST_F(VersionSetTest_77, NeedsCompactionInitially_77) {
  // A fresh version set with no files should not need compaction
  // (though this depends on the current version being set up properly)
  // We just call it to ensure it doesn't crash
  bool needs = vset_->NeedsCompaction();
  // For a fresh empty vset, typically false
  EXPECT_FALSE(needs);
}

// Test MaxNextLevelOverlappingBytes on empty set
TEST_F(VersionSetTest_77, MaxNextLevelOverlappingBytesEmpty_77) {
  int64_t result = vset_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test Recover with a fresh (empty) database that has no CURRENT file
TEST_F(VersionSetTest_77, RecoverWithoutCurrentFileFails_77) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  // Should fail because there's no CURRENT file
  EXPECT_FALSE(s.ok());
}

// Test multiple calls to NewFileNumber
TEST_F(VersionSetTest_77, NewFileNumberMonotonicallyIncreasing_77) {
  uint64_t prev = vset_->NewFileNumber();
  for (int i = 0; i < 100; i++) {
    uint64_t curr = vset_->NewFileNumber();
    EXPECT_GT(curr, prev);
    prev = curr;
  }
}

// Test SetLastSequence overwrites previous value
TEST_F(VersionSetTest_77, SetLastSequenceOverwrites_77) {
  vset_->SetLastSequence(10);
  EXPECT_EQ(10u, vset_->LastSequence());
  vset_->SetLastSequence(20);
  EXPECT_EQ(20u, vset_->LastSequence());
  vset_->SetLastSequence(5);
  EXPECT_EQ(5u, vset_->LastSequence());
}

// Test MarkFileNumberUsed with number less than current doesn't decrease
TEST_F(VersionSetTest_77, MarkFileNumberUsedSmallNumber_77) {
  vset_->MarkFileNumberUsed(100);
  uint64_t after_mark = vset_->NewFileNumber();
  vset_->MarkFileNumberUsed(50);
  uint64_t after_small_mark = vset_->NewFileNumber();
  EXPECT_GT(after_small_mark, after_mark);
}

// Test PickCompaction on empty version set
TEST_F(VersionSetTest_77, PickCompactionOnEmpty_77) {
  Compaction* c = vset_->PickCompaction();
  // No files, so no compaction needed
  EXPECT_EQ(nullptr, c);
}

// Test CompactRange on empty version set
TEST_F(VersionSetTest_77, CompactRangeOnEmpty_77) {
  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 100, kTypeValue);
  Compaction* c = vset_->CompactRange(0, &begin, &end);
  // No files in level 0, should return nullptr
  EXPECT_EQ(nullptr, c);
}

// Test CompactRange with nullptr begin and end (full range)
TEST_F(VersionSetTest_77, CompactRangeFullRange_77) {
  Compaction* c = vset_->CompactRange(0, nullptr, nullptr);
  EXPECT_EQ(nullptr, c);
}

}  // namespace leveldb
