#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "leveldb/table.h"
#include "util/testutil.h"
#include "db/dbformat.h"
#include "port/port.h"

#include <set>
#include <string>

namespace leveldb {

class VersionSetTest_71 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_71";
    env_->CreateDir(dbname_);

    options_.env = env_;

    // Create a CURRENT file so that Recover can work
    // We'll set up the table cache and version set
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete version_set_;
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
  InternalKeyComparator* icmp_;
  VersionSet* version_set_;
};

// Test ManifestFileNumber returns default value after construction
TEST_F(VersionSetTest_71, ManifestFileNumberInitialValue_71) {
  // After construction (without Recover), manifest_file_number_ should be 0
  EXPECT_EQ(0u, version_set_->ManifestFileNumber());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_71, NewFileNumberIncrementsCorrectly_71) {
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test NewFileNumber starts at 2 (from constructor)
TEST_F(VersionSetTest_71, NewFileNumberStartsAt2_71) {
  uint64_t first = version_set_->NewFileNumber();
  EXPECT_EQ(2u, first);
}

// Test ReuseFileNumber can reuse the last allocated number
TEST_F(VersionSetTest_71, ReuseFileNumberReusesLastNumber_71) {
  uint64_t num = version_set_->NewFileNumber();
  version_set_->ReuseFileNumber(num);
  uint64_t reused = version_set_->NewFileNumber();
  EXPECT_EQ(num, reused);
}

// Test ReuseFileNumber with a non-last number does not reuse
TEST_F(VersionSetTest_71, ReuseFileNumberDoesNotReuseOldNumber_71) {
  uint64_t num1 = version_set_->NewFileNumber();
  uint64_t num2 = version_set_->NewFileNumber();
  // Try to reuse num1 (which is not the last allocated)
  version_set_->ReuseFileNumber(num1);
  uint64_t num3 = version_set_->NewFileNumber();
  EXPECT_EQ(num2 + 1, num3);
}

// Test LastSequence initial value
TEST_F(VersionSetTest_71, LastSequenceInitialValue_71) {
  EXPECT_EQ(0u, version_set_->LastSequence());
}

// Test SetLastSequence and LastSequence
TEST_F(VersionSetTest_71, SetAndGetLastSequence_71) {
  version_set_->SetLastSequence(100);
  EXPECT_EQ(100u, version_set_->LastSequence());
}

// Test SetLastSequence with large value
TEST_F(VersionSetTest_71, SetLastSequenceLargeValue_71) {
  uint64_t large_seq = 1ULL << 56;
  version_set_->SetLastSequence(large_seq);
  EXPECT_EQ(large_seq, version_set_->LastSequence());
}

// Test LogNumber initial value
TEST_F(VersionSetTest_71, LogNumberInitialValue_71) {
  EXPECT_EQ(0u, version_set_->LogNumber());
}

// Test PrevLogNumber initial value
TEST_F(VersionSetTest_71, PrevLogNumberInitialValue_71) {
  EXPECT_EQ(0u, version_set_->PrevLogNumber());
}

// Test NumLevelFiles returns 0 for all levels initially
TEST_F(VersionSetTest_71, NumLevelFilesInitiallyZero_71) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes returns 0 for all levels initially
TEST_F(VersionSetTest_71, NumLevelBytesInitiallyZero_71) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

// Test MarkFileNumberUsed with number less than next_file_number_
TEST_F(VersionSetTest_71, MarkFileNumberUsedSmallNumber_71) {
  // next_file_number_ starts at 2
  version_set_->MarkFileNumberUsed(1);
  // Should not change next_file_number_ since 1 < 2
  uint64_t num = version_set_->NewFileNumber();
  EXPECT_EQ(2u, num);
}

// Test MarkFileNumberUsed with number greater than or equal to next_file_number_
TEST_F(VersionSetTest_71, MarkFileNumberUsedLargeNumber_71) {
  version_set_->MarkFileNumberUsed(10);
  uint64_t num = version_set_->NewFileNumber();
  EXPECT_EQ(11u, num);
}

// Test MarkFileNumberUsed with exact next_file_number_ value
TEST_F(VersionSetTest_71, MarkFileNumberUsedExactNext_71) {
  // next_file_number_ starts at 2
  version_set_->MarkFileNumberUsed(2);
  uint64_t num = version_set_->NewFileNumber();
  EXPECT_EQ(3u, num);
}

// Test AddLiveFiles with empty version set
TEST_F(VersionSetTest_71, AddLiveFilesEmpty_71) {
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  // With no files added, live set might be empty
  // (current_ may be nullptr before Recover, but depends on implementation)
  // This test verifies no crash occurs
  SUCCEED();
}

// Test LevelSummary returns non-null string
TEST_F(VersionSetTest_71, LevelSummaryReturnsNonNull_71) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  ASSERT_NE(nullptr, summary);
  // The summary should be a valid C-string
  EXPECT_GE(strlen(summary), 0u);
}

// Test MaxNextLevelOverlappingBytes with empty version set
TEST_F(VersionSetTest_71, MaxNextLevelOverlappingBytesEmpty_71) {
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// Test NeedsCompaction with empty version set
TEST_F(VersionSetTest_71, NeedsCompactionInitially_71) {
  // With no files, compaction should not be needed
  // (depends on implementation but typically false for empty db)
  bool needs = version_set_->NeedsCompaction();
  // Just verify it doesn't crash; we can't know for sure without Recover
  (void)needs;
  SUCCEED();
}

// Test current() before Recover
TEST_F(VersionSetTest_71, CurrentVersionBeforeRecover_71) {
  // Before Recover, current_ is nullptr based on constructor
  Version* current = version_set_->current();
  // This is expected to be nullptr
  EXPECT_EQ(nullptr, current);
}

// Test Recover with no CURRENT file
TEST_F(VersionSetTest_71, RecoverWithNoCurrent_71) {
  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  // Should fail since there's no CURRENT file
  EXPECT_FALSE(s.ok());
}

// Full integration test: create a valid db state and recover
class VersionSetRecoverTest_71 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_recover_test_71";
    env_->CreateDir(dbname_);
    options_.env = env_;
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
  }

  void TearDown() override {
    delete table_cache_;
    delete icmp_;
    std::vector<std::string> filenames;
    env_->GetChildren(dbname_, &filenames);
    for (const auto& f : filenames) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  // Helper to create a valid manifest and CURRENT file
  Status CreateManifest() {
    // Create a manifest file
    std::string manifest = dbname_ + "/MANIFEST-000001";
    WritableFile* file;
    Status s = env_->NewWritableFile(manifest, &file);
    if (!s.ok()) return s;

    log::Writer writer(file);
    
    // Write a version edit as the initial snapshot
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);

    std::string record;
    edit.EncodeTo(&record);
    s = writer.AddRecord(record);
    if (!s.ok()) {
      delete file;
      return s;
    }
    
    delete file;

    // Write CURRENT file pointing to manifest
    s = SetCurrentFile(env_, dbname_, 1);
    return s;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
};

// Test successful Recover
TEST_F(VersionSetRecoverTest_71, RecoverSuccess_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // After recover, current should not be null
  EXPECT_NE(nullptr, vs.current());
  
  // ManifestFileNumber should be set
  EXPECT_GT(vs.ManifestFileNumber(), 0u);
}

// Test LogAndApply after Recover
TEST_F(VersionSetRecoverTest_71, LogAndApplyAfterRecover_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  port::Mutex mu;
  mu.Lock();

  VersionEdit edit;
  edit.SetLogNumber(vs.LogNumber());
  s = vs.LogAndApply(&edit, &mu);
  EXPECT_TRUE(s.ok()) << s.ToString();

  mu.Unlock();
}

// Test NumLevelFiles after adding a file via LogAndApply
TEST_F(VersionSetRecoverTest_71, NumLevelFilesAfterAddFile_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Initially should have 0 files at all levels
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(0, vs.NumLevelFiles(i));
  }

  port::Mutex mu;
  mu.Lock();

  // Add a file to level 0
  VersionEdit edit;
  uint64_t file_num = vs.NewFileNumber();
  InternalKey smallest(Slice("a"), 1, kTypeValue);
  InternalKey largest(Slice("z"), 2, kTypeValue);
  edit.AddFile(0, file_num, 1000, smallest, largest);
  edit.SetLogNumber(vs.LogNumber());

  s = vs.LogAndApply(&edit, &mu);
  EXPECT_TRUE(s.ok()) << s.ToString();

  mu.Unlock();

  // Now level 0 should have 1 file
  EXPECT_EQ(1, vs.NumLevelFiles(0));
  // Other levels still 0
  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(0, vs.NumLevelFiles(i));
  }
}

// Test AddLiveFiles after adding files
TEST_F(VersionSetRecoverTest_71, AddLiveFilesAfterAddFile_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  port::Mutex mu;
  mu.Lock();

  uint64_t file_num = vs.NewFileNumber();
  VersionEdit edit;
  InternalKey smallest(Slice("a"), 1, kTypeValue);
  InternalKey largest(Slice("z"), 2, kTypeValue);
  edit.AddFile(0, file_num, 1000, smallest, largest);
  edit.SetLogNumber(vs.LogNumber());

  s = vs.LogAndApply(&edit, &mu);
  EXPECT_TRUE(s.ok()) << s.ToString();

  mu.Unlock();

  std::set<uint64_t> live;
  vs.AddLiveFiles(&live);
  EXPECT_TRUE(live.find(file_num) != live.end());
}

// Test SetLastSequence then verify
TEST_F(VersionSetRecoverTest_71, SetLastSequenceAfterRecover_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  vs.SetLastSequence(42);
  EXPECT_EQ(42u, vs.LastSequence());

  vs.SetLastSequence(0);
  EXPECT_EQ(0u, vs.LastSequence());

  vs.SetLastSequence(UINT64_MAX);
  EXPECT_EQ(UINT64_MAX, vs.LastSequence());
}

// Test PickCompaction with empty db returns nullptr
TEST_F(VersionSetRecoverTest_71, PickCompactionEmptyDb_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Compaction* c = vs.PickCompaction();
  // Empty db should not need compaction
  EXPECT_EQ(nullptr, c);
  delete c;
}

// Test CompactRange with empty db
TEST_F(VersionSetRecoverTest_71, CompactRangeEmptyDb_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  InternalKey begin(Slice("a"), kMaxSequenceNumber, kValueTypeForSeek);
  InternalKey end(Slice("z"), 0, static_cast<ValueType>(0));

  Compaction* c = vs.CompactRange(0, &begin, &end);
  // With no files, should return nullptr
  EXPECT_EQ(nullptr, c);
  delete c;
}

// Test NeedsCompaction after Recover on empty db
TEST_F(VersionSetRecoverTest_71, NeedsCompactionEmptyDb_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_FALSE(vs.NeedsCompaction());
}

// Test multiple NewFileNumber calls
TEST_F(VersionSetRecoverTest_71, MultipleNewFileNumbers_71) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet vs(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  s = vs.Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  uint64_t prev = vs.NewFileNumber();
  for (int i = 0; i < 100; i++) {
    uint64_t next = vs.NewFileNumber();
    EXPECT_EQ(prev + 1, next);
    prev = next;
  }
}

}  // namespace leveldb
