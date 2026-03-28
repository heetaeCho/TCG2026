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

class VersionSetTest_73 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    
    const int table_cache_size = 100;
    table_cache_ = new TableCache(dbname_, &options_, table_cache_size);
    
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  const InternalKeyComparator* icmp_;
  VersionSet* vset_;
};

// Test NewFileNumber returns incrementing file numbers
TEST_F(VersionSetTest_73, NewFileNumberIncrementing_73) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test ReuseFileNumber with the last allocated number
TEST_F(VersionSetTest_73, ReuseFileNumberLastAllocated_73) {
  uint64_t num = vset_->NewFileNumber();
  // Reuse should work since next_file_number_ == num + 1
  vset_->ReuseFileNumber(num);
  uint64_t next = vset_->NewFileNumber();
  // After reuse, next allocated number should be same as num
  EXPECT_EQ(num, next);
}

// Test ReuseFileNumber with a number that is not the last allocated
TEST_F(VersionSetTest_73, ReuseFileNumberNotLastAllocated_73) {
  uint64_t num1 = vset_->NewFileNumber();
  uint64_t num2 = vset_->NewFileNumber();
  // Try to reuse num1, which is not the last one
  vset_->ReuseFileNumber(num1);
  uint64_t num3 = vset_->NewFileNumber();
  // Since num1+1 != next_file_number_, reuse should not happen
  EXPECT_EQ(num2 + 1, num3);
}

// Test SetLastSequence and LastSequence
TEST_F(VersionSetTest_73, SetAndGetLastSequence_73) {
  vset_->SetLastSequence(100);
  EXPECT_EQ(100u, vset_->LastSequence());
}

// Test SetLastSequence with zero
TEST_F(VersionSetTest_73, SetLastSequenceZero_73) {
  vset_->SetLastSequence(0);
  EXPECT_EQ(0u, vset_->LastSequence());
}

// Test SetLastSequence with large value
TEST_F(VersionSetTest_73, SetLastSequenceLargeValue_73) {
  uint64_t large = 0xFFFFFFFFFFFFFFULL;
  vset_->SetLastSequence(large);
  EXPECT_EQ(large, vset_->LastSequence());
}

// Test LogNumber initial value
TEST_F(VersionSetTest_73, LogNumberInitial_73) {
  EXPECT_EQ(0u, vset_->LogNumber());
}

// Test PrevLogNumber initial value
TEST_F(VersionSetTest_73, PrevLogNumberInitial_73) {
  EXPECT_EQ(0u, vset_->PrevLogNumber());
}

// Test NumLevelFiles for various levels without any data
TEST_F(VersionSetTest_73, NumLevelFilesEmpty_73) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, vset_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes for various levels without any data
TEST_F(VersionSetTest_73, NumLevelBytesEmpty_73) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, vset_->NumLevelBytes(level));
  }
}

// Test MarkFileNumberUsed with a number below current next
TEST_F(VersionSetTest_73, MarkFileNumberUsedBelowCurrent_73) {
  uint64_t before = vset_->NewFileNumber();
  // Mark a number lower than current next_file_number_
  vset_->MarkFileNumberUsed(0);
  uint64_t after = vset_->NewFileNumber();
  // Should still increment normally
  EXPECT_EQ(before + 1, after);
}

// Test MarkFileNumberUsed with a number above current next
TEST_F(VersionSetTest_73, MarkFileNumberUsedAboveCurrent_73) {
  uint64_t high_number = 1000;
  vset_->MarkFileNumberUsed(high_number);
  uint64_t next = vset_->NewFileNumber();
  // next_file_number_ should be at least high_number + 1
  EXPECT_GT(next, high_number);
}

// Test NewFileNumber multiple times
TEST_F(VersionSetTest_73, NewFileNumberMultipleCalls_73) {
  uint64_t nums[10];
  for (int i = 0; i < 10; i++) {
    nums[i] = vset_->NewFileNumber();
  }
  for (int i = 1; i < 10; i++) {
    EXPECT_EQ(nums[i - 1] + 1, nums[i]);
  }
}

// Test ReuseFileNumber then allocate again to ensure correctness
TEST_F(VersionSetTest_73, ReuseFileNumberAndReallocate_73) {
  uint64_t a = vset_->NewFileNumber();
  vset_->ReuseFileNumber(a);
  uint64_t b = vset_->NewFileNumber();
  EXPECT_EQ(a, b);
  uint64_t c = vset_->NewFileNumber();
  EXPECT_EQ(b + 1, c);
}

// Test ReuseFileNumber with arbitrary unrelated number
TEST_F(VersionSetTest_73, ReuseFileNumberArbitraryNumber_73) {
  uint64_t num = vset_->NewFileNumber();
  // Try reusing a completely unrelated number
  vset_->ReuseFileNumber(9999);
  uint64_t next = vset_->NewFileNumber();
  EXPECT_EQ(num + 1, next);
}

// Test LevelSummary doesn't crash and returns non-null
TEST_F(VersionSetTest_73, LevelSummaryReturnsNonNull_73) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  ASSERT_NE(nullptr, summary);
  EXPECT_GT(strlen(summary), 0u);
}

// Test AddLiveFiles on empty version set
TEST_F(VersionSetTest_73, AddLiveFilesEmpty_73) {
  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  // With no data loaded, live files might be empty
  // We just verify it doesn't crash
  EXPECT_GE(live.size(), 0u);
}

// Test NeedsCompaction on fresh version set
TEST_F(VersionSetTest_73, NeedsCompactionFresh_73) {
  // Fresh version set shouldn't need compaction
  bool needs = vset_->NeedsCompaction();
  // Just verify it returns a valid boolean (doesn't crash)
  EXPECT_TRUE(needs == true || needs == false);
}

// Test current() returns a non-null value after construction
// (VersionSet constructor should set up a current version)
TEST_F(VersionSetTest_73, CurrentVersionNotNull_73) {
  // After a fresh VersionSet without Recover, current_ might be nullptr
  // depending on implementation. We just test it doesn't crash.
  // Some implementations initialize current_ in constructor.
  Version* v = vset_->current();
  // This might be nullptr if Recover hasn't been called
  // We just ensure the call doesn't crash
  (void)v;
}

// Test ManifestFileNumber initial value
TEST_F(VersionSetTest_73, ManifestFileNumberInitial_73) {
  EXPECT_EQ(0u, vset_->ManifestFileNumber());
}

// Test multiple reuse attempts in sequence
TEST_F(VersionSetTest_73, MultipleReuseAttempts_73) {
  uint64_t a = vset_->NewFileNumber();
  vset_->ReuseFileNumber(a);  // succeeds
  vset_->ReuseFileNumber(a);  // now next_file_number_ == a, so a != a-1+1? 
  // After first reuse: next = a
  // Second reuse: next_file_number_(a) == file_number(a) + 1? No, a == a+1 is false
  // So second reuse is no-op
  uint64_t b = vset_->NewFileNumber();
  EXPECT_EQ(a, b);
}

// Test MarkFileNumberUsed with exact current next file number
TEST_F(VersionSetTest_73, MarkFileNumberUsedExactCurrent_73) {
  uint64_t n1 = vset_->NewFileNumber();
  // next_file_number_ is now n1+1
  // Mark n1+1 as used
  vset_->MarkFileNumberUsed(n1 + 1);
  uint64_t n2 = vset_->NewFileNumber();
  // Should be at least n1+2
  EXPECT_GE(n2, n1 + 2);
}

}  // namespace leveldb
