#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/options.h"
#include "util/env.h"
#include "util/testutil.h"

#include <string>
#include <memory>

namespace leveldb {

class VersionSetTest_166 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_166";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(options_.comparator);
    versions_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* versions_;
};

// Test that NumLevelFiles returns 0 for all levels on a fresh VersionSet
// (before any files are added via Recover or LogAndApply)
TEST_F(VersionSetTest_166, NumLevelFilesReturnsZeroForEmptyLevels_166) {
  // After constructing a VersionSet and recovering, all levels should
  // initially have 0 files. We need to recover first to set current_.
  // Create a CURRENT file pointing to a manifest
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  // Write an empty version edit as a snapshot
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;

  // Write CURRENT file
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  Status s = versions_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, versions_->NumLevelFiles(level))
        << "Level " << level << " should have 0 files";
  }
}

// Test NumLevelFiles for each valid level index
TEST_F(VersionSetTest_166, NumLevelFilesValidLevels_166) {
  // Set up a valid manifest
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  // All levels from 0 to kNumLevels-1 should be queryable
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_GE(versions_->NumLevelFiles(level), 0);
  }
}

// Test NumLevelFiles after adding a file via LogAndApply
TEST_F(VersionSetTest_166, NumLevelFilesAfterAddingFile_166) {
  // Set up manifest
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(100);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  // Initially level 0 should have 0 files
  EXPECT_EQ(0, versions_->NumLevelFiles(0));

  // Add a file to level 0
  VersionEdit edit;
  edit.SetLogNumber(0);
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, versions_->NewFileNumber(), 100, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = versions_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Now level 0 should have 1 file
  EXPECT_EQ(1, versions_->NumLevelFiles(0));

  // Other levels should still have 0 files
  for (int level = 1; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, versions_->NumLevelFiles(level));
  }
}

// Test NumLevelFiles after adding files to multiple levels
TEST_F(VersionSetTest_166, NumLevelFilesMultipleLevels_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(100);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  // Add files to multiple levels in one edit
  VersionEdit edit;
  edit.SetLogNumber(0);

  // Add 3 files to level 0
  for (int i = 0; i < 3; i++) {
    std::string s_key = std::string(1, 'a' + i * 2);
    std::string l_key = std::string(1, 'a' + i * 2 + 1);
    InternalKey smallest(s_key, i * 2 + 1, kTypeValue);
    InternalKey largest(l_key, i * 2 + 2, kTypeValue);
    edit.AddFile(0, versions_->NewFileNumber(), 100, smallest, largest);
  }

  // Add 2 files to level 1
  {
    InternalKey smallest1("a", 100, kTypeValue);
    InternalKey largest1("m", 101, kTypeValue);
    edit.AddFile(1, versions_->NewFileNumber(), 200, smallest1, largest1);

    InternalKey smallest2("n", 102, kTypeValue);
    InternalKey largest2("z", 103, kTypeValue);
    edit.AddFile(1, versions_->NewFileNumber(), 200, smallest2, largest2);
  }

  port::Mutex mu;
  mu.Lock();
  Status s = versions_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(3, versions_->NumLevelFiles(0));
  EXPECT_EQ(2, versions_->NumLevelFiles(1));
  for (int level = 2; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, versions_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes returns 0 for all levels on fresh VersionSet
TEST_F(VersionSetTest_166, NumLevelBytesReturnsZeroForEmptyLevels_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, versions_->NumLevelBytes(level));
  }
}

// Test LastSequence and SetLastSequence
TEST_F(VersionSetTest_166, LastSequenceSetAndGet_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  EXPECT_EQ(0u, versions_->LastSequence());
  versions_->SetLastSequence(42);
  EXPECT_EQ(42u, versions_->LastSequence());
  versions_->SetLastSequence(100);
  EXPECT_EQ(100u, versions_->LastSequence());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_166, NewFileNumberIncrements_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  uint64_t first = versions_->NewFileNumber();
  uint64_t second = versions_->NewFileNumber();
  EXPECT_EQ(first + 1, second);

  uint64_t third = versions_->NewFileNumber();
  EXPECT_EQ(second + 1, third);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_166, ReuseFileNumber_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  uint64_t num = versions_->NewFileNumber();
  // Reuse the number we just got
  versions_->ReuseFileNumber(num);
  // Next call should give back the same number
  uint64_t reused = versions_->NewFileNumber();
  EXPECT_EQ(num, reused);
}

// Test current() returns non-null after Recover
TEST_F(VersionSetTest_166, CurrentVersionNotNull_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  EXPECT_NE(nullptr, versions_->current());
}

// Test LevelSummary returns a non-null string
TEST_F(VersionSetTest_166, LevelSummaryReturnsNonNull_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  VersionSet::LevelSummaryStorage scratch;
  const char* summary = versions_->LevelSummary(&scratch);
  EXPECT_NE(nullptr, summary);
  EXPECT_GT(strlen(summary), 0u);
}

// Test AddLiveFiles on empty version set
TEST_F(VersionSetTest_166, AddLiveFilesEmpty_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  std::set<uint64_t> live;
  versions_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test Recover with missing CURRENT file
TEST_F(VersionSetTest_166, RecoverFailsWithoutCurrent_166) {
  bool save_manifest = false;
  Status s = versions_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

// Test MarkFileNumberUsed ensures file numbers are advanced
TEST_F(VersionSetTest_166, MarkFileNumberUsed_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  // Mark a high file number as used
  versions_->MarkFileNumberUsed(1000);
  uint64_t next = versions_->NewFileNumber();
  EXPECT_GT(next, 1000u);
}

// Test Version::NumFiles matches VersionSet::NumLevelFiles
TEST_F(VersionSetTest_166, VersionNumFilesConsistency_166) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(100);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

  bool save_manifest = false;
  ASSERT_TRUE(versions_->Recover(&save_manifest).ok());

  Version* current = versions_->current();
  ASSERT_NE(nullptr, current);

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(versions_->NumLevelFiles(level), current->NumFiles(level));
  }
}

}  // namespace leveldb
