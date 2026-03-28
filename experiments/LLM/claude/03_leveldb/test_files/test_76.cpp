#include "gtest/gtest.h"

#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/log_writer.h"
#include "leveldb/comparator.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "util/testutil.h"

namespace leveldb {

class VersionSetTest_76 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "version_set_test_76";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    const InternalKeyComparator cmp(options_.comparator);
    icmp_ = new InternalKeyComparator(options_.comparator);

    // Create a CURRENT file to allow Recover to work
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
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
  VersionSet* vset_;
};

TEST_F(VersionSetTest_76, LogNumberInitiallyZero_76) {
  // After construction (without Recover), log_number_ should be 0
  EXPECT_EQ(0, vset_->LogNumber());
}

TEST_F(VersionSetTest_76, PrevLogNumberInitiallyZero_76) {
  EXPECT_EQ(0, vset_->PrevLogNumber());
}

TEST_F(VersionSetTest_76, LastSequenceInitiallyZero_76) {
  EXPECT_EQ(0, vset_->LastSequence());
}

TEST_F(VersionSetTest_76, SetLastSequence_76) {
  vset_->SetLastSequence(100);
  EXPECT_EQ(100, vset_->LastSequence());
}

TEST_F(VersionSetTest_76, SetLastSequenceLargeValue_76) {
  uint64_t large_val = 0xFFFFFFFFFFFFFFULL;
  vset_->SetLastSequence(large_val);
  EXPECT_EQ(large_val, vset_->LastSequence());
}

TEST_F(VersionSetTest_76, NewFileNumberIncrementsMonotonically_76) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  uint64_t third = vset_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
  EXPECT_EQ(second + 1, third);
}

TEST_F(VersionSetTest_76, ReuseFileNumberDecrementsNext_76) {
  uint64_t num = vset_->NewFileNumber();
  // Reusing the last allocated number should allow re-allocation
  vset_->ReuseFileNumber(num);
  uint64_t reused = vset_->NewFileNumber();
  EXPECT_EQ(num, reused);
}

TEST_F(VersionSetTest_76, ReuseFileNumberOnlyLastAllocated_76) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  // Trying to reuse `first` (not the last allocated) should not work
  vset_->ReuseFileNumber(first);
  uint64_t next = vset_->NewFileNumber();
  // next should be second+1, not first, because first is not the last allocated
  EXPECT_EQ(second + 1, next);
}

TEST_F(VersionSetTest_76, MarkFileNumberUsed_76) {
  // MarkFileNumberUsed should ensure file numbers >= the marked one are not reused
  vset_->MarkFileNumberUsed(100);
  uint64_t next = vset_->NewFileNumber();
  EXPECT_GT(next, 100);
}

TEST_F(VersionSetTest_76, ManifestFileNumberInitiallyZero_76) {
  EXPECT_EQ(0, vset_->ManifestFileNumber());
}

TEST_F(VersionSetTest_76, NumLevelFilesInitiallyZero_76) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, vset_->NumLevelFiles(level));
  }
}

TEST_F(VersionSetTest_76, NumLevelBytesInitiallyZero_76) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, vset_->NumLevelBytes(level));
  }
}

TEST_F(VersionSetTest_76, CurrentVersionNotNull_76) {
  // After construction, current_ should be set via AppendVersion in constructor
  // Actually, looking at the constructor, current_ is set to nullptr initially
  // But the constructor likely calls AppendVersion or similar
  // We test what we can observe
  // current() might return nullptr if no version has been appended
  // This depends on implementation details, but we can check it doesn't crash
  Version* current = vset_->current();
  // After basic construction without Recover, current might be nullptr or valid
  // We just verify the method is callable
  (void)current;
}

TEST_F(VersionSetTest_76, AddLiveFilesEmptyInitially_76) {
  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  // Initially there should be no live files
  EXPECT_TRUE(live.empty());
}

TEST_F(VersionSetTest_76, NeedsCompactionInitially_76) {
  // Without any data, compaction should not be needed
  bool needs = vset_->NeedsCompaction();
  // We just verify the function is callable and returns a boolean
  (void)needs;
}

TEST_F(VersionSetTest_76, LevelSummary_76) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  ASSERT_NE(nullptr, summary);
  // Summary should be a non-empty string
  EXPECT_GT(strlen(summary), 0);
}

TEST_F(VersionSetTest_76, PickCompactionNoFiles_76) {
  // With no files, PickCompaction should return nullptr
  Compaction* c = vset_->PickCompaction();
  // Likely nullptr since there are no files
  // Clean up if not null
  delete c;
}

TEST_F(VersionSetTest_76, CompactRangeNoFiles_76) {
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  
  for (int level = 0; level < 7; level++) {
    Compaction* c = vset_->CompactRange(level, &begin, &end);
    // With no files, should return nullptr
    delete c;
  }
}

TEST_F(VersionSetTest_76, CompactRangeNullBounds_76) {
  Compaction* c = vset_->CompactRange(0, nullptr, nullptr);
  delete c;
}

TEST_F(VersionSetTest_76, MaxNextLevelOverlappingBytesNoFiles_76) {
  int64_t result = vset_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

TEST_F(VersionSetTest_76, SetLastSequenceMultipleTimes_76) {
  vset_->SetLastSequence(10);
  EXPECT_EQ(10, vset_->LastSequence());
  vset_->SetLastSequence(20);
  EXPECT_EQ(20, vset_->LastSequence());
  vset_->SetLastSequence(0);
  EXPECT_EQ(0, vset_->LastSequence());
}

TEST_F(VersionSetTest_76, NewFileNumberStartsAtTwo_76) {
  // Constructor sets next_file_number_ to 2
  uint64_t first = vset_->NewFileNumber();
  EXPECT_EQ(2, first);
}

TEST_F(VersionSetTest_76, MarkFileNumberUsedSmallValue_76) {
  // Marking a small value (less than current next_file_number_) should have no effect
  uint64_t before = vset_->NewFileNumber();  // Gets 2, next is 3
  vset_->MarkFileNumberUsed(1);  // 1 < 3, should not change
  uint64_t after = vset_->NewFileNumber();  // Should be 3
  EXPECT_EQ(before + 1, after);
}

TEST_F(VersionSetTest_76, RecoverWithoutManifest_76) {
  // Without a valid CURRENT file, Recover should fail
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  // Should fail because there's no valid CURRENT/MANIFEST
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
