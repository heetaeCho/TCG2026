#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/testutil.h"
#include "util/env.h"
#include "leveldb/options.h"
#include "leveldb/cache.h"

#include <string>
#include <vector>
#include <set>
#include <memory>

namespace leveldb {

class VersionSetTest_171 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_171";
    env_->CreateDir(dbname_);

    options_.env = env_;
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

// Test MaxNextLevelOverlappingBytes with a fresh/empty VersionSet
// When there are no files at any level, the result should be 0.
TEST_F(VersionSetTest_171, MaxNextLevelOverlappingBytesEmpty_171) {
  // We need to initialize the version set via Recover or LogAndApply
  // to have a valid current_ version. Let's create a CURRENT file
  // pointing to a manifest.
  
  // Create a manifest file
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  // Write a version edit as a log record
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // With no files, MaxNextLevelOverlappingBytes should return 0
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test that NumLevelFiles returns 0 for all levels on a fresh database
TEST_F(VersionSetTest_171, NumLevelFilesEmpty_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

// Test that NumLevelBytes returns 0 for all levels on a fresh database
TEST_F(VersionSetTest_171, NumLevelBytesEmpty_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

// Test LastSequence and SetLastSequence
TEST_F(VersionSetTest_171, LastSequenceGetSet_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  EXPECT_EQ(0u, version_set_->LastSequence());
  
  version_set_->SetLastSequence(100);
  EXPECT_EQ(100u, version_set_->LastSequence());
  
  version_set_->SetLastSequence(999);
  EXPECT_EQ(999u, version_set_->LastSequence());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_171, NewFileNumberIncreases_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  uint64_t third = version_set_->NewFileNumber();
  
  EXPECT_LT(first, second);
  EXPECT_LT(second, third);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_171, ReuseFileNumber_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  uint64_t num = version_set_->NewFileNumber();
  // Reuse the file number - this should allow the same number to be returned again
  version_set_->ReuseFileNumber(num);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_EQ(num, next);
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_171, MarkFileNumberUsed_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Mark a high file number as used
  version_set_->MarkFileNumberUsed(1000);
  
  // Next file number should be > 1000
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_GT(next, 1000u);
}

// Test current() returns non-null after Recover
TEST_F(VersionSetTest_171, CurrentVersionNonNull_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  EXPECT_NE(nullptr, version_set_->current());
}

// Test ManifestFileNumber returns a valid value after Recover
TEST_F(VersionSetTest_171, ManifestFileNumber_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Manifest file number should be set after recovery
  uint64_t manifest_num = version_set_->ManifestFileNumber();
  EXPECT_GT(manifest_num, 0u);
}

// Test LogAndApply with a simple edit adding a file
TEST_F(VersionSetTest_171, LogAndApplyAddFile_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Apply an edit that adds a file to level 1
  VersionEdit edit;
  InternalKey smallest, largest;
  smallest.DecodeFrom(
      Slice(std::string("aaa\x01\x00\x00\x00\x00\x00\x00\x01", 11)));
  largest.DecodeFrom(
      Slice(std::string("zzz\x01\x00\x00\x00\x00\x00\x00\x01", 11)));
  
  uint64_t file_number = version_set_->NewFileNumber();
  edit.AddFile(1, file_number, 1000, smallest, largest);
  edit.SetLogNumber(version_set_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  EXPECT_EQ(1, version_set_->NumLevelFiles(1));
  EXPECT_EQ(1000, version_set_->NumLevelBytes(1));
}

// Test MaxNextLevelOverlappingBytes with files added at multiple levels
TEST_F(VersionSetTest_171, MaxNextLevelOverlappingBytesWithFiles_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &wfile).ok());
  
  {
    log::Writer writer(wfile);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete wfile;
  
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Add a file at level 1 covering keys "a" to "z"
  {
    VersionEdit edit;
    ParsedInternalKey parsed_small("a", 1, kTypeValue);
    ParsedInternalKey parsed_large("z", 2, kTypeValue);
    std::string small_buf, large_buf;
    AppendInternalKey(&small_buf, parsed_small);
    AppendInternalKey(&large_buf, parsed_large);
    InternalKey smallest, largest;
    smallest.DecodeFrom(small_buf);
    largest.DecodeFrom(large_buf);
    
    uint64_t fnum = version_set_->NewFileNumber();
    edit.AddFile(1, fnum, 500, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
    mu.Unlock();
  }
  
  // Add a file at level 2 covering keys "a" to "m"
  {
    VersionEdit edit;
    ParsedInternalKey parsed_small("a", 3, kTypeValue);
    ParsedInternalKey parsed_large("m", 4, kTypeValue);
    std::string small_buf, large_buf;
    AppendInternalKey(&small_buf, parsed_small);
    AppendInternalKey(&large_buf, parsed_large);
    InternalKey smallest, largest;
    smallest.DecodeFrom(small_buf);
    largest.DecodeFrom(large_buf);
    
    uint64_t fnum = version_set_->NewFileNumber();
    edit.AddFile(2, fnum, 2000, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
    mu.Unlock();
  }
  
  // Add another file at level 2 covering keys "n" to "z"
  {
    VersionEdit edit;
    ParsedInternalKey parsed_small("n", 5, kTypeValue);
    ParsedInternalKey parsed_large("z", 6, kTypeValue);
    std::string small_buf, large_buf;
    AppendInternalKey(&small_buf, parsed_small);
    AppendInternalKey(&large_buf, parsed_large);
    InternalKey smallest, largest;
    smallest.DecodeFrom(small_buf);
    largest.DecodeFrom(large_buf);
    
    uint64_t fnum = version_set_->NewFileNumber();
    edit.AddFile(2, fnum, 3000, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
    mu.Unlock();
  }
  
  // The level-1 file overlaps with both level-2 files, so
  // MaxNextLevelOverlappingBytes should be 2000 + 3000 = 5000
  int64_t max_overlap = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(5000, max_overlap);
}

// Test AddLiveFiles
TEST_F(VersionSetTest_171, AddLiveFilesEmpty_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test AddLiveFiles after adding files
TEST_F(VersionSetTest_171, AddLiveFilesWithFiles_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &wfile).ok());
  
  {
    log::Writer writer(wfile);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete wfile;
  
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Add a file
  VersionEdit edit;
  ParsedInternalKey parsed_small("a", 1, kTypeValue);
  ParsedInternalKey parsed_large("z", 2, kTypeValue);
  std::string small_buf, large_buf;
  AppendInternalKey(&small_buf, parsed_small);
  AppendInternalKey(&large_buf, parsed_large);
  InternalKey smallest, largest;
  smallest.DecodeFrom(small_buf);
  largest.DecodeFrom(large_buf);
  
  uint64_t fnum = version_set_->NewFileNumber();
  edit.AddFile(0, fnum, 1000, smallest, largest);
  edit.SetLogNumber(version_set_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();
  
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_EQ(1u, live.size());
  EXPECT_TRUE(live.count(fnum) > 0);
}

// Test LevelSummary returns a non-null string
TEST_F(VersionSetTest_171, LevelSummary_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  EXPECT_NE(nullptr, summary);
  EXPECT_GT(strlen(summary), 0u);
}

// Test NeedsCompaction on empty database
TEST_F(VersionSetTest_171, NeedsCompactionEmpty_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
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
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Empty database should not need compaction
  EXPECT_FALSE(version_set_->NeedsCompaction());
}

// Test Recover with missing CURRENT file fails
TEST_F(VersionSetTest_171, RecoverMissingCurrentFile_171) {
  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

// Test Version::NumFiles
TEST_F(VersionSetTest_171, VersionNumFiles_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &wfile).ok());
  
  {
    log::Writer writer(wfile);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete wfile;
  
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
}

// Test Version::DebugString returns non-empty
TEST_F(VersionSetTest_171, VersionDebugString_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &wfile).ok());
  
  {
    log::Writer writer(wfile);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete wfile;
  
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test MaxNextLevelOverlappingBytes with files only at the last level
// (no level+1 to overlap with for those files)
TEST_F(VersionSetTest_171, MaxNextLevelOverlappingBytesLastLevel_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &wfile).ok());
  
  {
    log::Writer writer(wfile);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete wfile;
  
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Add a file at the highest level (kNumLevels - 1 = 6)
  // This file has no next level, so it shouldn't contribute to overlap
  {
    VersionEdit edit;
    ParsedInternalKey parsed_small("a", 1, kTypeValue);
    ParsedInternalKey parsed_large("z", 2, kTypeValue);
    std::string small_buf, large_buf;
    AppendInternalKey(&small_buf, parsed_small);
    AppendInternalKey(&large_buf, parsed_large);
    InternalKey smallest, largest;
    smallest.DecodeFrom(small_buf);
    largest.DecodeFrom(large_buf);
    
    uint64_t fnum = version_set_->NewFileNumber();
    edit.AddFile(config::kNumLevels - 1, fnum, 10000, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
    mu.Unlock();
  }
  
  // Files only at the last level - no overlap contribution
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test MaxNextLevelOverlappingBytes with non-overlapping files
TEST_F(VersionSetTest_171, MaxNextLevelOverlappingBytesNoOverlap_171) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &wfile).ok());
  
  {
    log::Writer writer(wfile);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());
  }
  delete wfile;
  
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  
  // Add a file at level 1 covering "a" to "c"
  {
    VersionEdit edit;
    ParsedInternalKey parsed_small("a", 1, kTypeValue);
    ParsedInternalKey parsed_large("c", 2, kTypeValue);
    std::string small_buf, large_buf;
    AppendInternalKey(&small_buf, parsed_small);
    AppendInternalKey(&large_buf, parsed_large);
    InternalKey smallest, largest;
    smallest.DecodeFrom(small_buf);
    largest.DecodeFrom(large_buf);
    
    uint64_t fnum = version_set_->NewFileNumber();
    edit.AddFile(1, fnum, 500, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
    mu.Unlock();
  }
  
  // Add a file at level 2 covering "x" to "z" (no overlap with level 1 file)
  {
    VersionEdit edit;
    ParsedInternalKey parsed_small("x", 3, kTypeValue);
    ParsedInternalKey parsed_large("z", 4, kTypeValue);
    std::string small_buf, large_buf;
    AppendInternalKey(&small_buf, parsed_small);
    AppendInternalKey(&large_buf, parsed_large);
    InternalKey smallest, largest;
    smallest.DecodeFrom(small_buf);
    largest.DecodeFrom(large_buf);
    
    uint64_t fnum = version_set_->NewFileNumber();
    edit.AddFile(2, fnum, 3000, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    ASSERT_TRUE(version_set_->LogAndApply(&edit, &mu).ok());
    mu.Unlock();
  }
  
  // No overlap between level 1 and level 2 files
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

}  // namespace leveldb
