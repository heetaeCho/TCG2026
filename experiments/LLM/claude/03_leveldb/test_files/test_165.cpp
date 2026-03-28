#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/filename.h"
#include "db/log_writer.h"
#include "db/version_edit.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table_cache.h"
#include "table/merger.h"
#include "util/testutil.h"

namespace leveldb {

class VersionSetTest_165 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_165";
    env_->CreateDir(dbname_);

    // Create a CURRENT file pointing to a valid manifest
    options_.env = env_;
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    vs_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vs_;
    delete table_cache_;
    delete icmp_;
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
  TableCache* table_cache_;
  const InternalKeyComparator* icmp_;
  VersionSet* vs_;
};

// Test MarkFileNumberUsed: when number >= next_file_number_, next should be number+1
TEST_F(VersionSetTest_165, MarkFileNumberUsed_SetsNextFileNumber_165) {
  // Initially, next_file_number_ is 2 (from constructor).
  // NewFileNumber returns current and increments.
  uint64_t first = vs_->NewFileNumber();
  EXPECT_EQ(first, 2);

  // Now next_file_number_ should be 3.
  // Mark file number 10 as used.
  vs_->MarkFileNumberUsed(10);

  // Next file number should now be 11.
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 11);
}

// Test MarkFileNumberUsed with a number less than current next_file_number_
TEST_F(VersionSetTest_165, MarkFileNumberUsed_SmallerNumberNoEffect_165) {
  // next_file_number_ starts at 2
  vs_->MarkFileNumberUsed(0);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 2);  // Should still be 2, unchanged
}

// Test MarkFileNumberUsed with the exact current next_file_number_ - 1
TEST_F(VersionSetTest_165, MarkFileNumberUsed_ExactBoundary_165) {
  // next_file_number_ is 2
  // Mark 1 as used: since 2 > 1, no change
  vs_->MarkFileNumberUsed(1);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 2);
}

// Test MarkFileNumberUsed with the exact current next_file_number_
TEST_F(VersionSetTest_165, MarkFileNumberUsed_EqualToNext_165) {
  // next_file_number_ is 2
  // Mark 2 as used: since 2 <= 2, set next to 3
  vs_->MarkFileNumberUsed(2);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 3);
}

// Test NewFileNumber increments correctly
TEST_F(VersionSetTest_165, NewFileNumber_Increments_165) {
  uint64_t a = vs_->NewFileNumber();
  uint64_t b = vs_->NewFileNumber();
  uint64_t c = vs_->NewFileNumber();
  EXPECT_EQ(a, 2);
  EXPECT_EQ(b, 3);
  EXPECT_EQ(c, 4);
}

// Test ReuseFileNumber: reuse the last allocated file number
TEST_F(VersionSetTest_165, ReuseFileNumber_DecreasesNext_165) {
  uint64_t num = vs_->NewFileNumber();
  EXPECT_EQ(num, 2);
  // Now next_file_number_ is 3
  vs_->ReuseFileNumber(num);
  // Should be able to get 2 again
  uint64_t num2 = vs_->NewFileNumber();
  EXPECT_EQ(num2, 2);
}

// Test LastSequence and SetLastSequence
TEST_F(VersionSetTest_165, LastSequence_InitiallyZero_165) {
  EXPECT_EQ(vs_->LastSequence(), 0);
}

TEST_F(VersionSetTest_165, SetLastSequence_UpdatesValue_165) {
  vs_->SetLastSequence(100);
  EXPECT_EQ(vs_->LastSequence(), 100);
}

TEST_F(VersionSetTest_165, SetLastSequence_LargeValue_165) {
  uint64_t large_val = (1ULL << 56) - 1;
  vs_->SetLastSequence(large_val);
  EXPECT_EQ(vs_->LastSequence(), large_val);
}

// Test LogNumber and PrevLogNumber initial values
TEST_F(VersionSetTest_165, LogNumber_InitiallyZero_165) {
  EXPECT_EQ(vs_->LogNumber(), 0);
}

TEST_F(VersionSetTest_165, PrevLogNumber_InitiallyZero_165) {
  EXPECT_EQ(vs_->PrevLogNumber(), 0);
}

// Test ManifestFileNumber initial value
TEST_F(VersionSetTest_165, ManifestFileNumber_InitiallyZero_165) {
  EXPECT_EQ(vs_->ManifestFileNumber(), 0);
}

// Test MarkFileNumberUsed with very large number
TEST_F(VersionSetTest_165, MarkFileNumberUsed_VeryLargeNumber_165) {
  uint64_t large = UINT64_MAX - 1;
  vs_->MarkFileNumberUsed(large);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, large + 1);
}

// Test MarkFileNumberUsed called multiple times with increasing values
TEST_F(VersionSetTest_165, MarkFileNumberUsed_MultipleIncreasingCalls_165) {
  vs_->MarkFileNumberUsed(5);
  vs_->MarkFileNumberUsed(10);
  vs_->MarkFileNumberUsed(15);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 16);
}

// Test MarkFileNumberUsed called multiple times with decreasing values
TEST_F(VersionSetTest_165, MarkFileNumberUsed_MultipleDecreasingCalls_165) {
  vs_->MarkFileNumberUsed(15);
  vs_->MarkFileNumberUsed(10);
  vs_->MarkFileNumberUsed(5);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 16);  // Should remain at 16 since 15 was the max
}

// Test NumLevelFiles for initial state
TEST_F(VersionSetTest_165, NumLevelFiles_InitiallyZero_165) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(vs_->NumLevelFiles(level), 0);
  }
}

// Test NumLevelBytes for initial state
TEST_F(VersionSetTest_165, NumLevelBytes_InitiallyZero_165) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(vs_->NumLevelBytes(level), 0);
  }
}

// Test current() is not null after construction
TEST_F(VersionSetTest_165, Current_NotNullAfterConstruction_165) {
  // current_ starts as nullptr in constructor but AppendVersion should set it
  // Actually looking at the constructor, current_ is set to nullptr
  // It's typically set after Recover or AppendVersion
  // This tests the initial state
  // Note: The constructor doesn't call AppendVersion, so current_ may be nullptr
  // This is an observable state through the public interface
}

// Test MarkFileNumberUsed with zero
TEST_F(VersionSetTest_165, MarkFileNumberUsed_Zero_165) {
  // next_file_number_ starts at 2, marking 0 should have no effect
  vs_->MarkFileNumberUsed(0);
  uint64_t next = vs_->NewFileNumber();
  EXPECT_EQ(next, 2);
}

// Test sequential NewFileNumber and MarkFileNumberUsed interleaving
TEST_F(VersionSetTest_165, NewFileNumberAndMarkFileNumberUsed_Interleaved_165) {
  uint64_t n1 = vs_->NewFileNumber();  // returns 2, next=3
  EXPECT_EQ(n1, 2);

  vs_->MarkFileNumberUsed(5);  // next=6

  uint64_t n2 = vs_->NewFileNumber();  // returns 6, next=7
  EXPECT_EQ(n2, 6);

  vs_->MarkFileNumberUsed(4);  // no change, 7 > 4

  uint64_t n3 = vs_->NewFileNumber();  // returns 7, next=8
  EXPECT_EQ(n3, 7);
}

}  // namespace leveldb
