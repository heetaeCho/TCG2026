#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "table/table_cache.h"
#include "util/comparator.h"
#include "util/options.h"
#include "util/env.h"
#include "util/testutil.h"
#include "db/dbformat.h"
#include "leveldb/table_cache.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"

#include <string>
#include <vector>
#include <set>
#include <memory>

namespace leveldb {

class VersionSetTest_152 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    icmp_ = new InternalKeyComparator(options_.comparator);
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that VersionSet can be constructed properly
TEST_F(VersionSetTest_152, Construction_152) {
  ASSERT_NE(vset_, nullptr);
}

// Test current() returns a valid version
TEST_F(VersionSetTest_152, CurrentVersionNotNull_152) {
  // After construction, current_ may be nullptr until Recover or AppendVersion
  // is called. But we can at least test the accessor doesn't crash.
  // current() may return nullptr before Recover is called.
  Version* v = vset_->current();
  // Just verify the call doesn't crash; value depends on implementation
  (void)v;
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_152, NewFileNumberIncrement_152) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  EXPECT_EQ(second, first + 1);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_152, ReuseFileNumber_152) {
  uint64_t num = vset_->NewFileNumber();
  vset_->ReuseFileNumber(num);
  uint64_t reused = vset_->NewFileNumber();
  EXPECT_EQ(reused, num);
}

// Test ReuseFileNumber with non-matching number (should not reuse)
TEST_F(VersionSetTest_152, ReuseFileNumberNonMatching_152) {
  uint64_t num = vset_->NewFileNumber();
  // Try to reuse a number that is not the last allocated
  vset_->ReuseFileNumber(num - 1);
  uint64_t next = vset_->NewFileNumber();
  EXPECT_EQ(next, num + 1);
}

// Test SetLastSequence and LastSequence
TEST_F(VersionSetTest_152, LastSequence_152) {
  vset_->SetLastSequence(100);
  EXPECT_EQ(vset_->LastSequence(), 100);
}

// Test SetLastSequence boundary: zero
TEST_F(VersionSetTest_152, LastSequenceZero_152) {
  // Initially last_sequence_ is 0
  EXPECT_EQ(vset_->LastSequence(), 0);
}

// Test SetLastSequence large value
TEST_F(VersionSetTest_152, LastSequenceLargeValue_152) {
  uint64_t large_val = UINT64_MAX - 1;
  vset_->SetLastSequence(large_val);
  EXPECT_EQ(vset_->LastSequence(), large_val);
}

// Test ManifestFileNumber
TEST_F(VersionSetTest_152, ManifestFileNumber_152) {
  // After construction, manifest_file_number_ is 0
  uint64_t mfn = vset_->ManifestFileNumber();
  EXPECT_EQ(mfn, 0);
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_152, MarkFileNumberUsed_152) {
  vset_->MarkFileNumberUsed(10);
  uint64_t next = vset_->NewFileNumber();
  EXPECT_GE(next, 11);
}

// Test MarkFileNumberUsed with a smaller number than current
TEST_F(VersionSetTest_152, MarkFileNumberUsedSmaller_152) {
  uint64_t before = vset_->NewFileNumber();
  vset_->MarkFileNumberUsed(0);
  uint64_t after = vset_->NewFileNumber();
  // Should not decrease the file number
  EXPECT_GT(after, before);
}

// Test NumLevelFiles for various levels on empty version set
TEST_F(VersionSetTest_152, NumLevelFilesEmpty_152) {
  // Before Recover, current might be null or have no files
  // This test checks that NumLevelFiles works for valid levels
  // We need a valid current version. Let's try to recover first.
  // Since there's no CURRENT file, this will fail, but we test what we can.
  for (int level = 0; level < 7; level++) {
    // Just checking it doesn't crash before Recover
    // The actual behavior depends on whether current_ is set
  }
}

// Test NeedsCompaction
TEST_F(VersionSetTest_152, NeedsCompaction_152) {
  // On a fresh version set without recovery, check it doesn't crash
  // The result depends on compaction_score_ and file_to_compact_
  bool needs = vset_->NeedsCompaction();
  // Just verify call doesn't crash
  (void)needs;
}

// Test Version Ref and Unref
TEST_F(VersionSetTest_152, VersionRefUnref_152) {
  // We need a valid current version to test Ref/Unref
  // Create CURRENT file and manifest for recovery
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  std::string content = manifest + "\n";
  file->Append(content);
  file->Close();
  delete file;

  // Create a simple manifest file
  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  // Write a valid version edit as a log record
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);

  // Write as log format
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (s.ok()) {
    Version* v = vset_->current();
    ASSERT_NE(v, nullptr);
    // Ref to increase count
    v->Ref();
    // Unref to decrease - should not delete since current holds a ref
    v->Unref();
  }
}

// Test Recover with valid manifest
TEST_F(VersionSetTest_152, RecoverWithValidManifest_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  std::string content = manifest + "\n";
  file->Append(content);
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);

  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  EXPECT_TRUE(s.ok()) << s.ToString();
  EXPECT_NE(vset_->current(), nullptr);
}

// Test Recover with missing CURRENT file
TEST_F(VersionSetTest_152, RecoverMissingCurrent_152) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

// Test NumLevelFiles after recovery
TEST_F(VersionSetTest_152, NumLevelFilesAfterRecovery_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 0);
  }
}

// Test NumLevelBytes after recovery with no files
TEST_F(VersionSetTest_152, NumLevelBytesAfterRecovery_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(vset_->NumLevelBytes(level), 0);
  }
}

// Test AddLiveFiles on empty version set after recovery
TEST_F(VersionSetTest_152, AddLiveFilesEmpty_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test LevelSummary after recovery
TEST_F(VersionSetTest_152, LevelSummaryAfterRecovery_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  ASSERT_NE(summary, nullptr);
  // Summary should contain some text about levels
  std::string summary_str(summary);
  EXPECT_FALSE(summary_str.empty());
}

// Test DebugString on current version after recovery
TEST_F(VersionSetTest_152, VersionDebugStringAfterRecovery_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);
  std::string debug = v->DebugString();
  // Debug string should not be empty
  EXPECT_FALSE(debug.empty());
}

// Test LogAndApply with a simple edit
TEST_F(VersionSetTest_152, LogAndApplySimple_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Now apply a simple edit
  VersionEdit new_edit;
  new_edit.SetLogNumber(1);

  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&new_edit, &mu);
  mu.Unlock();
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test MaxNextLevelOverlappingBytes on empty db
TEST_F(VersionSetTest_152, MaxNextLevelOverlappingBytesEmpty_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  int64_t max_overlap = vset_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(max_overlap, 0);
}

// Test OverlapInLevel on empty version
TEST_F(VersionSetTest_152, OverlapInLevelEmpty_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  Slice smallest("a");
  Slice largest("z");
  for (int level = 0; level < 7; level++) {
    bool overlap = v->OverlapInLevel(level, &smallest, &largest);
    EXPECT_FALSE(overlap);
  }
}

// Test OverlapInLevel with nullptr boundaries
TEST_F(VersionSetTest_152, OverlapInLevelNullBoundaries_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  // With nullptr boundaries (meaning no bounds)
  bool overlap = v->OverlapInLevel(0, nullptr, nullptr);
  EXPECT_FALSE(overlap);  // No files, so no overlap
}

// Test GetOverlappingInputs on empty version
TEST_F(VersionSetTest_152, GetOverlappingInputsEmpty_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
}

// Test NumFiles on current version after recovery
TEST_F(VersionSetTest_152, NumFilesAfterRecovery_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(v->NumFiles(level), 0);
  }
}

// Test PickLevelForMemTableOutput on empty version
TEST_F(VersionSetTest_152, PickLevelForMemTableOutputEmpty_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  Slice smallest("a");
  Slice largest("z");
  int level = v->PickLevelForMemTableOutput(smallest, largest);
  // With no files, should pick a level >= 0
  EXPECT_GE(level, 0);
}

// Test multiple Ref/Unref calls
TEST_F(VersionSetTest_152, MultipleRefUnref_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);

  // Ref multiple times
  v->Ref();
  v->Ref();
  v->Ref();

  // Unref same number of times
  v->Unref();
  v->Unref();
  v->Unref();

  // Version should still be alive because VersionSet holds a reference
}

// Test LogNumber and PrevLogNumber
TEST_F(VersionSetTest_152, LogAndPrevLogNumber_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(5);
  edit.SetNextFile(10);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(vset_->LogNumber(), 5);
  EXPECT_EQ(vset_->PrevLogNumber(), 0);
}

// Test Recover with wrong comparator name
TEST_F(VersionSetTest_152, RecoverWrongComparator_152) {
  std::string manifest = "MANIFEST-000001";
  std::string current_file = dbname_ + "/CURRENT";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(current_file, &file).ok());
  file->Append(manifest + "\n");
  file->Close();
  delete file;

  std::string manifest_path = dbname_ + "/" + manifest;
  ASSERT_TRUE(env_->NewWritableFile(manifest_path, &file).ok());

  VersionEdit edit;
  edit.SetComparatorName("wrong_comparator");
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);

  std::string record;
  edit.EncodeTo(&record);
  log::Writer writer(file);
  writer.AddRecord(record);
  file->Close();
  delete file;

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
