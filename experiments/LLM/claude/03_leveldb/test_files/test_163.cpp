#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/log_writer.h"
#include "db/filename.h"
#include "db/table_cache.h"
#include "db/dbformat.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/table.h"
#include "port/port.h"
#include "util/testutil.h"

#include <string>
#include <set>
#include <vector>

namespace leveldb {

class VersionSetTest_163 : public ::testing::Test {
 protected:
  std::string dbname_;
  Env* env_;
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
  port::Mutex mu_;

  VersionSetTest_163()
      : dbname_(testing::TempDir() + "version_set_test_163"),
        env_(Env::Default()),
        icmp_(BytewiseComparator()),
        table_cache_(nullptr),
        vset_(nullptr) {}

  void SetUp() override {
    options_.env = env_;
    options_.create_if_missing = true;
    // Create directory
    env_->CreateDir(dbname_);

    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);

    // Create a CURRENT file pointing to a manifest to allow Recover
    // We need to bootstrap the version set
    bool save_manifest = false;

    // Write CURRENT file manually or use Recover approach
    // First, create a manifest file
    std::string manifest = DescriptorFileName(dbname_, 1);
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(manifest, &file).ok());
    {
      log::Writer writer(file);
      // Write an initial snapshot-like record
      VersionEdit edit;
      edit.SetComparatorName(icmp_.user_comparator()->Name());
      edit.SetLogNumber(0);
      edit.SetNextFile(2);
      edit.SetLastSequence(0);
      std::string record;
      edit.EncodeTo(&record);
      ASSERT_TRUE(writer.AddRecord(record).ok());
    }
    delete file;

    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

    ASSERT_TRUE(vset_->Recover(&save_manifest).ok());
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    // Cleanup
    std::vector<std::string> files;
    env_->GetChildren(dbname_, &files);
    for (const auto& f : files) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }
};

// Test that LogAndApply succeeds with a basic empty edit
TEST_F(VersionSetTest_163, LogAndApplyBasicEdit_163) {
  VersionEdit edit;
  mu_.Lock();
  Status s = vset_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test that LogAndApply properly updates the log number when set
TEST_F(VersionSetTest_163, LogAndApplyWithLogNumber_163) {
  // First get a file number for the log
  uint64_t log_num = vset_->NewFileNumber();

  VersionEdit edit;
  edit.SetLogNumber(log_num);

  mu_.Lock();
  Status s = vset_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(vset_->LogNumber(), log_num);
}

// Test that LogAndApply sets default log number if not provided
TEST_F(VersionSetTest_163, LogAndApplyDefaultLogNumber_163) {
  uint64_t old_log = vset_->LogNumber();
  VersionEdit edit;

  mu_.Lock();
  Status s = vset_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(vset_->LogNumber(), old_log);
}

// Test that multiple LogAndApply calls succeed
TEST_F(VersionSetTest_163, MultipleLogAndApply_163) {
  for (int i = 0; i < 5; i++) {
    VersionEdit edit;
    mu_.Lock();
    Status s = vset_->LogAndApply(&edit, &mu_);
    mu_.Unlock();
    ASSERT_TRUE(s.ok()) << "Iteration " << i << ": " << s.ToString();
  }
}

// Test adding a file via LogAndApply and checking NumLevelFiles
TEST_F(VersionSetTest_163, LogAndApplyAddFile_163) {
  EXPECT_EQ(vset_->NumLevelFiles(0), 0);

  VersionEdit edit;
  uint64_t file_num = vset_->NewFileNumber();
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, file_num, 1000, smallest, largest);

  mu_.Lock();
  Status s = vset_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(vset_->NumLevelFiles(0), 1);
}

// Test removing a file via LogAndApply
TEST_F(VersionSetTest_163, LogAndApplyRemoveFile_163) {
  // First add a file
  uint64_t file_num = vset_->NewFileNumber();
  {
    VersionEdit edit;
    InternalKey smallest("a", 1, kTypeValue);
    InternalKey largest("z", 2, kTypeValue);
    edit.AddFile(0, file_num, 1000, smallest, largest);

    mu_.Lock();
    Status s = vset_->LogAndApply(&edit, &mu_);
    mu_.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
    EXPECT_EQ(vset_->NumLevelFiles(0), 1);
  }

  // Now remove it
  {
    VersionEdit edit;
    edit.RemoveFile(0, file_num);

    mu_.Lock();
    Status s = vset_->LogAndApply(&edit, &mu_);
    mu_.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
    EXPECT_EQ(vset_->NumLevelFiles(0), 0);
  }
}

// Test that SetLastSequence is reflected
TEST_F(VersionSetTest_163, SetLastSequence_163) {
  vset_->SetLastSequence(100);
  EXPECT_EQ(vset_->LastSequence(), 100);

  vset_->SetLastSequence(200);
  EXPECT_EQ(vset_->LastSequence(), 200);
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_163, NewFileNumberIncrements_163) {
  uint64_t n1 = vset_->NewFileNumber();
  uint64_t n2 = vset_->NewFileNumber();
  EXPECT_GT(n2, n1);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_163, ReuseFileNumber_163) {
  uint64_t n1 = vset_->NewFileNumber();
  vset_->ReuseFileNumber(n1);
  uint64_t n2 = vset_->NewFileNumber();
  EXPECT_EQ(n1, n2);
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_163, MarkFileNumberUsed_163) {
  vset_->MarkFileNumberUsed(1000);
  uint64_t n = vset_->NewFileNumber();
  EXPECT_GT(n, 1000);
}

// Test NumLevelFiles for all levels initially zero
TEST_F(VersionSetTest_163, InitialNumLevelFilesZero_163) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 0);
  }
}

// Test NumLevelBytes for all levels initially zero
TEST_F(VersionSetTest_163, InitialNumLevelBytesZero_163) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelBytes(level), 0);
  }
}

// Test current version is not null after construction
TEST_F(VersionSetTest_163, CurrentNotNull_163) {
  EXPECT_NE(vset_->current(), nullptr);
}

// Test ManifestFileNumber is valid
TEST_F(VersionSetTest_163, ManifestFileNumber_163) {
  EXPECT_GT(vset_->ManifestFileNumber(), 0u);
}

// Test AddLiveFiles with empty set
TEST_F(VersionSetTest_163, AddLiveFilesEmpty_163) {
  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test AddLiveFiles after adding files
TEST_F(VersionSetTest_163, AddLiveFilesAfterAdd_163) {
  uint64_t file_num = vset_->NewFileNumber();
  VersionEdit edit;
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, file_num, 1000, smallest, largest);

  mu_.Lock();
  Status s = vset_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  ASSERT_TRUE(s.ok());

  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.count(file_num) > 0);
}

// Test LevelSummary returns non-null
TEST_F(VersionSetTest_163, LevelSummary_163) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  EXPECT_NE(summary, nullptr);
  EXPECT_GT(strlen(summary), 0u);
}

// Test adding files to multiple levels
TEST_F(VersionSetTest_163, AddFilesToMultipleLevels_163) {
  for (int level = 0; level < config::kNumLevels; level++) {
    uint64_t file_num = vset_->NewFileNumber();
    VersionEdit edit;
    // For level 0, overlapping keys are ok. For others, need non-overlapping.
    char small_buf[16], large_buf[16];
    snprintf(small_buf, sizeof(small_buf), "k%d", level * 2);
    snprintf(large_buf, sizeof(large_buf), "k%d", level * 2 + 1);
    InternalKey smallest(small_buf, 1, kTypeValue);
    InternalKey largest(large_buf, 2, kTypeValue);
    edit.AddFile(level, file_num, 500, smallest, largest);

    mu_.Lock();
    Status s = vset_->LogAndApply(&edit, &mu_);
    mu_.Unlock();
    ASSERT_TRUE(s.ok()) << "Level " << level << ": " << s.ToString();
    EXPECT_EQ(vset_->NumLevelFiles(level), 1);
  }
}

// Test that NeedsCompaction returns a value (just call it, no crash)
TEST_F(VersionSetTest_163, NeedsCompactionNoFiles_163) {
  // With no files, should not need compaction
  bool needs = vset_->NeedsCompaction();
  // We don't assert the value, just that it doesn't crash
  (void)needs;
}

// Test MaxNextLevelOverlappingBytes with no files
TEST_F(VersionSetTest_163, MaxNextLevelOverlappingBytesEmpty_163) {
  int64_t bytes = vset_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(bytes, 0);
}

// Test Recover returns ok status
TEST_F(VersionSetTest_163, RecoverSucceeds_163) {
  // Re-create version set and recover
  delete vset_;
  vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test that LogAndApply with log_number set properly propagates
TEST_F(VersionSetTest_163, LogAndApplyPrevLogNumber_163) {
  uint64_t prev_log = vset_->PrevLogNumber();
  VersionEdit edit;
  // Don't set prev_log_number, let LogAndApply set it
  mu_.Lock();
  Status s = vset_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  ASSERT_TRUE(s.ok());
  // PrevLogNumber should remain the same since we didn't change it
  EXPECT_EQ(vset_->PrevLogNumber(), prev_log);
}

// Test PickCompaction with no files returns null
TEST_F(VersionSetTest_163, PickCompactionNoFiles_163) {
  Compaction* c = vset_->PickCompaction();
  // With no files and no compaction score, should be nullptr
  EXPECT_EQ(c, nullptr);
  delete c;
}

// Test CompactRange with no files in given level
TEST_F(VersionSetTest_163, CompactRangeNoFiles_163) {
  InternalKey begin("a", kMaxSequenceNumber, kValueTypeForSeek);
  InternalKey end("z", 0, static_cast<ValueType>(0));
  Compaction* c = vset_->CompactRange(0, &begin, &end);
  // May or may not be null depending on state, just ensure no crash
  delete c;
}

}  // namespace leveldb
