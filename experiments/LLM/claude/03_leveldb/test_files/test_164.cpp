#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "db/log_writer.h"
#include "db/filename.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "leveldb/status.h"
#include "leveldb/table_cache.h"
#include "util/testutil.h"

#include <string>
#include <cstdio>

namespace leveldb {

class VersionSetRecoverTest_164 : public ::testing::Test {
 protected:
  std::string dbname_;
  Env* env_;
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_;
  VersionSet* version_set_;

  VersionSetRecoverTest_164()
      : dbname_(testing::TempDir() + "version_set_recover_test_164"),
        env_(Env::Default()),
        icmp_(BytewiseComparator()),
        table_cache_(nullptr),
        version_set_(nullptr) {}

  void SetUp() override {
    // Clean up any previous test artifacts
    CleanupDB();
    env_->CreateDir(dbname_);
    options_.env = env_;
    options_.comparator = BytewiseComparator();
    table_cache_ = new TableCache(dbname_, &options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    CleanupDB();
  }

  void CleanupDB() {
    std::vector<std::string> files;
    env_->GetChildren(dbname_, &files);
    for (const auto& f : files) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  // Helper: write a valid CURRENT file pointing to a manifest
  Status WriteCurrentFile(const std::string& manifest_name) {
    std::string current_path = CurrentFileName(dbname_);
    WritableFile* file;
    Status s = env_->NewWritableFile(current_path, &file);
    if (!s.ok()) return s;
    s = file->Append(manifest_name + "\n");
    if (s.ok()) s = file->Close();
    delete file;
    return s;
  }

  // Helper: create a valid manifest file with a single VersionEdit
  Status WriteManifest(const std::string& manifest_name, VersionEdit* edit) {
    std::string manifest_path = dbname_ + "/" + manifest_name;
    WritableFile* file;
    Status s = env_->NewWritableFile(manifest_path, &file);
    if (!s.ok()) return s;
    log::Writer writer(file);
    std::string record;
    edit->EncodeTo(&record);
    s = writer.AddRecord(record);
    if (s.ok()) s = file->Close();
    delete file;
    return s;
  }

  // Helper: create a complete valid setup for Recover
  Status SetupValidManifest() {
    std::string manifest_name = "MANIFEST-000001";
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);

    Status s = WriteManifest(manifest_name, &edit);
    if (!s.ok()) return s;
    return WriteCurrentFile(manifest_name);
  }
};

// Test: Recover fails when no CURRENT file exists
TEST_F(VersionSetRecoverTest_164, RecoverFailsWhenNoCurrent_164) {
  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

// Test: Recover fails when CURRENT file is empty
TEST_F(VersionSetRecoverTest_164, RecoverFailsWhenCurrentEmpty_164) {
  std::string current_path = CurrentFileName(dbname_);
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_path, &file).ok());
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Recover fails when CURRENT file does not end with newline
TEST_F(VersionSetRecoverTest_164, RecoverFailsWhenCurrentNoNewline_164) {
  std::string current_path = CurrentFileName(dbname_);
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_path, &file).ok());
  file->Append("MANIFEST-000001");  // no newline
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Recover fails when CURRENT points to non-existent manifest
TEST_F(VersionSetRecoverTest_164, RecoverFailsWhenManifestMissing_164) {
  ASSERT_TRUE(WriteCurrentFile("MANIFEST-000001").ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Recover fails when manifest has no next file entry
TEST_F(VersionSetRecoverTest_164, RecoverFailsNoNextFile_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(0);
  // No SetNextFile
  edit.SetLastSequence(0);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Recover fails when manifest has no log number entry
TEST_F(VersionSetRecoverTest_164, RecoverFailsNoLogNumber_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  // No SetLogNumber
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Recover fails when manifest has no last sequence entry
TEST_F(VersionSetRecoverTest_164, RecoverFailsNoLastSequence_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  // No SetLastSequence

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Recover succeeds with valid manifest
TEST_F(VersionSetRecoverTest_164, RecoverSucceedsWithValidManifest_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test: After successful recover, current version is not null
TEST_F(VersionSetRecoverTest_164, RecoverSetsCurrentVersion_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_NE(nullptr, version_set_->current());
}

// Test: After recovery, sequence numbers are set properly
TEST_F(VersionSetRecoverTest_164, RecoverSetsSequenceNumber_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(5);
  edit.SetNextFile(10);
  edit.SetLastSequence(42);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(42u, version_set_->LastSequence());
  EXPECT_EQ(5u, version_set_->LogNumber());
}

// Test: After recovery, manifest file number is set
TEST_F(VersionSetRecoverTest_164, RecoverSetsManifestFileNumber_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(10);
  edit.SetLastSequence(0);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(10u, version_set_->ManifestFileNumber());
}

// Test: Recover fails with mismatched comparator
TEST_F(VersionSetRecoverTest_164, RecoverFailsComparatorMismatch_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName("some.other.comparator");
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test: Recover with prev_log_number set
TEST_F(VersionSetRecoverTest_164, RecoverWithPrevLogNumber_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(5);
  edit.SetPrevLogNumber(3);
  edit.SetNextFile(10);
  edit.SetLastSequence(100);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(3u, version_set_->PrevLogNumber());
  EXPECT_EQ(5u, version_set_->LogNumber());
  EXPECT_EQ(100u, version_set_->LastSequence());
}

// Test: Recover with corrupted manifest data
TEST_F(VersionSetRecoverTest_164, RecoverFailsWithCorruptedManifest_164) {
  std::string manifest_name = "MANIFEST-000001";
  std::string manifest_path = dbname_ + "/" + manifest_name;

  // Write garbage to manifest
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());
  file->Append("this is not a valid log record");
  file->Close();
  delete file;

  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  // With no valid records, we expect missing meta entries corruption
  EXPECT_FALSE(s.ok());
}

// Test: Recover with multiple edits in manifest
TEST_F(VersionSetRecoverTest_164, RecoverWithMultipleEdits_164) {
  std::string manifest_name = "MANIFEST-000001";
  std::string manifest_path = dbname_ + "/" + manifest_name;

  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());
  log::Writer writer(file);

  // First edit: set comparator and log number
  {
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(1);
    edit.SetNextFile(5);
    edit.SetLastSequence(10);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }

  // Second edit: update sequence and log number
  {
    VersionEdit edit;
    edit.SetLogNumber(3);
    edit.SetNextFile(8);
    edit.SetLastSequence(50);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }

  file->Close();
  delete file;

  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // The last edit's values should take effect
  EXPECT_EQ(50u, version_set_->LastSequence());
  EXPECT_EQ(3u, version_set_->LogNumber());
  EXPECT_EQ(8u, version_set_->ManifestFileNumber());
}

// Test: NumLevelFiles returns 0 for all levels after empty recover
TEST_F(VersionSetRecoverTest_164, NumLevelFilesAfterRecoverEmpty_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

// Test: NumLevelBytes returns 0 after empty recovery
TEST_F(VersionSetRecoverTest_164, NumLevelBytesAfterRecoverEmpty_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

// Test: NewFileNumber returns incrementing numbers
TEST_F(VersionSetRecoverTest_164, NewFileNumberIncrementing_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test: SetLastSequence and LastSequence
TEST_F(VersionSetRecoverTest_164, SetAndGetLastSequence_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  version_set_->SetLastSequence(999);
  EXPECT_EQ(999u, version_set_->LastSequence());
}

// Test: PrevLogNumber defaults to 0 when not set in manifest
TEST_F(VersionSetRecoverTest_164, PrevLogNumberDefaultsToZero_164) {
  std::string manifest_name = "MANIFEST-000001";
  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(1);
  // No SetPrevLogNumber
  edit.SetNextFile(5);
  edit.SetLastSequence(10);

  ASSERT_TRUE(WriteManifest(manifest_name, &edit).ok());
  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(0u, version_set_->PrevLogNumber());
}

// Test: AddLiveFiles on empty version set returns empty set
TEST_F(VersionSetRecoverTest_164, AddLiveFilesEmpty_164) {
  ASSERT_TRUE(SetupValidManifest().ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test: Recover with a file added in the manifest
TEST_F(VersionSetRecoverTest_164, RecoverWithAddedFile_164) {
  std::string manifest_name = "MANIFEST-000001";
  std::string manifest_path = dbname_ + "/" + manifest_name;

  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());
  log::Writer writer(file);

  VersionEdit edit;
  edit.SetComparatorName(icmp_.user_comparator()->Name());
  edit.SetLogNumber(1);
  edit.SetNextFile(10);
  edit.SetLastSequence(5);

  InternalKey smallest, largest;
  smallest.DecodeFrom(
      Slice(std::string("a\x01\x00\x00\x00\x00\x00\x00\x01", 9)));
  // Use a proper internal key encoding
  smallest = InternalKey("a", 1, kTypeValue);
  largest = InternalKey("z", 2, kTypeValue);
  edit.AddFile(0, 3, 1000, smallest, largest);

  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());

  file->Close();
  delete file;

  ASSERT_TRUE(WriteCurrentFile(manifest_name).ok());

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(1, version_set_->NumLevelFiles(0));

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_TRUE(live.count(3) > 0);
}

}  // namespace leveldb
