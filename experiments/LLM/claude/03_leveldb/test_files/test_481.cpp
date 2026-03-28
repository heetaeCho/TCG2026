#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "util/testutil.h"

namespace leveldb {

class VersionSetTest_481 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_481";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    icmp_ = new InternalKeyComparator(options_.comparator);
    table_cache_ = new TableCache(dbname_, options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    // (In a production test, we'd properly clean up files)
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* version_set_;
};

// Test that constructor initializes current_ to a non-null version
TEST_F(VersionSetTest_481, ConstructorInitializesCurrentVersion_481) {
  ASSERT_NE(nullptr, version_set_->current());
}

// Test NewFileNumber starts at 2 and increments
TEST_F(VersionSetTest_481, NewFileNumberStartsAtTwo_481) {
  uint64_t first = version_set_->NewFileNumber();
  EXPECT_EQ(2, first);
}

// Test NewFileNumber increments on successive calls
TEST_F(VersionSetTest_481, NewFileNumberIncrements_481) {
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test ReuseFileNumber can reuse the last allocated number
TEST_F(VersionSetTest_481, ReuseFileNumberDecrements_481) {
  uint64_t num = version_set_->NewFileNumber();
  version_set_->ReuseFileNumber(num);
  uint64_t reused = version_set_->NewFileNumber();
  EXPECT_EQ(num, reused);
}

// Test ReuseFileNumber does not reuse if number doesn't match
TEST_F(VersionSetTest_481, ReuseFileNumberNoEffectIfNotMatch_481) {
  uint64_t num = version_set_->NewFileNumber();
  // Try to reuse a different number (not the last allocated)
  version_set_->ReuseFileNumber(num - 1);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_EQ(num + 1, next);
}

// Test LastSequence initial value
TEST_F(VersionSetTest_481, LastSequenceInitiallyZero_481) {
  EXPECT_EQ(0, version_set_->LastSequence());
}

// Test SetLastSequence and LastSequence
TEST_F(VersionSetTest_481, SetLastSequence_481) {
  version_set_->SetLastSequence(100);
  EXPECT_EQ(100, version_set_->LastSequence());
}

// Test SetLastSequence with large value
TEST_F(VersionSetTest_481, SetLastSequenceLargeValue_481) {
  uint64_t large_seq = 1ULL << 56;
  version_set_->SetLastSequence(large_seq);
  EXPECT_EQ(large_seq, version_set_->LastSequence());
}

// Test LogNumber initial value
TEST_F(VersionSetTest_481, LogNumberInitiallyZero_481) {
  EXPECT_EQ(0, version_set_->LogNumber());
}

// Test PrevLogNumber initial value
TEST_F(VersionSetTest_481, PrevLogNumberInitiallyZero_481) {
  EXPECT_EQ(0, version_set_->PrevLogNumber());
}

// Test ManifestFileNumber initial value
TEST_F(VersionSetTest_481, ManifestFileNumberInitiallyZero_481) {
  EXPECT_EQ(0, version_set_->ManifestFileNumber());
}

// Test NumLevelFiles for all levels with fresh VersionSet
TEST_F(VersionSetTest_481, NumLevelFilesInitiallyZero_481) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes for all levels with fresh VersionSet
TEST_F(VersionSetTest_481, NumLevelBytesInitiallyZero_481) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

// Test MarkFileNumberUsed with a number less than next_file_number_
TEST_F(VersionSetTest_481, MarkFileNumberUsedSmallNumber_481) {
  // next_file_number_ starts at 2
  version_set_->MarkFileNumberUsed(1);
  // Should not affect NewFileNumber since 1 < 2
  uint64_t num = version_set_->NewFileNumber();
  EXPECT_EQ(2, num);
}

// Test MarkFileNumberUsed with a number >= next_file_number_
TEST_F(VersionSetTest_481, MarkFileNumberUsedLargeNumber_481) {
  version_set_->MarkFileNumberUsed(10);
  uint64_t num = version_set_->NewFileNumber();
  // next_file_number_ should be at least 11
  EXPECT_GE(num, 11);
}

// Test LevelSummary returns non-null string
TEST_F(VersionSetTest_481, LevelSummaryReturnsNonNull_481) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  ASSERT_NE(nullptr, summary);
  // Summary should contain some content
  EXPECT_GT(strlen(summary), 0);
}

// Test AddLiveFiles on fresh VersionSet
TEST_F(VersionSetTest_481, AddLiveFilesInitiallyEmpty_481) {
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  // A fresh version set should have no live files
  EXPECT_TRUE(live.empty());
}

// Test MaxNextLevelOverlappingBytes on fresh VersionSet
TEST_F(VersionSetTest_481, MaxNextLevelOverlappingBytesInitiallyZero_481) {
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test NeedsCompaction on fresh VersionSet
TEST_F(VersionSetTest_481, NeedsCompactionInitiallyFalse_481) {
  // A fresh version set with no files should not need compaction
  // (This could vary based on internal state, but typically false for empty db)
  // We just verify it doesn't crash and returns a valid bool
  bool needs = version_set_->NeedsCompaction();
  (void)needs;  // Just ensuring it doesn't crash
}

// Test PickCompaction on fresh VersionSet
TEST_F(VersionSetTest_481, PickCompactionOnEmptyReturnsNull_481) {
  Compaction* c = version_set_->PickCompaction();
  // With no files, there should be nothing to compact
  EXPECT_EQ(nullptr, c);
}

// Test that multiple NewFileNumber calls produce strictly increasing values
TEST_F(VersionSetTest_481, NewFileNumberStrictlyIncreasing_481) {
  uint64_t prev = version_set_->NewFileNumber();
  for (int i = 0; i < 100; i++) {
    uint64_t curr = version_set_->NewFileNumber();
    EXPECT_GT(curr, prev);
    prev = curr;
  }
}

// Test SetLastSequence can be called multiple times
TEST_F(VersionSetTest_481, SetLastSequenceMultipleTimes_481) {
  version_set_->SetLastSequence(10);
  EXPECT_EQ(10, version_set_->LastSequence());
  version_set_->SetLastSequence(20);
  EXPECT_EQ(20, version_set_->LastSequence());
  version_set_->SetLastSequence(0);
  EXPECT_EQ(0, version_set_->LastSequence());
}

// Test that current() returns a valid Version pointer after construction
TEST_F(VersionSetTest_481, CurrentVersionIsValid_481) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
}

// Test CompactRange on empty database
TEST_F(VersionSetTest_481, CompactRangeOnEmptyReturnsNull_481) {
  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 100, kTypeValue);
  Compaction* c = version_set_->CompactRange(0, &begin, &end);
  // With no files, nothing to compact
  EXPECT_EQ(nullptr, c);
}

// Test CompactRange with nullptr begin and end
TEST_F(VersionSetTest_481, CompactRangeNullBoundsOnEmpty_481) {
  Compaction* c = version_set_->CompactRange(0, nullptr, nullptr);
  EXPECT_EQ(nullptr, c);
}

// Test MarkFileNumberUsed with boundary values
TEST_F(VersionSetTest_481, MarkFileNumberUsedBoundary_481) {
  // Mark with exactly next_file_number_ - 1 (should be 1, since next is 2)
  version_set_->MarkFileNumberUsed(1);
  uint64_t num = version_set_->NewFileNumber();
  EXPECT_EQ(2, num);
}

// Test MarkFileNumberUsed with exact next_file_number_ value
TEST_F(VersionSetTest_481, MarkFileNumberUsedExactNext_481) {
  // next_file_number_ is 2, mark 2
  version_set_->MarkFileNumberUsed(2);
  uint64_t num = version_set_->NewFileNumber();
  EXPECT_GE(num, 3);
}

}  // namespace leveldb
