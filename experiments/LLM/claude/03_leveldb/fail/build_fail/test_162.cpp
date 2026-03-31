#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "leveldb/db.h"
#include "leveldb/comparator.h"
#include "util/testutil.h"
#include "db/dbformat.h"
#include "port/port.h"

#include <string>
#include <vector>
#include <set>

namespace leveldb {

class VersionSetTest_162 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "version_set_test_162";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    icmp_ = new InternalKeyComparator(options_.comparator);
    table_cache_ = new TableCache(dbname_, &options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    std::vector<std::string> children;
    env_->GetChildren(dbname_, &children);
    for (const auto& child : children) {
      env_->RemoveFile(dbname_ + "/" + child);
    }
    env_->RemoveDir(dbname_);
  }

  // Helper to create a valid DB so Recover can work
  Status CreateManifest() {
    // Write a CURRENT file pointing to a manifest
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    Status s = env_->NewWritableFile(dbname_ + "/" + manifest, &file);
    if (!s.ok()) return s;

    log::Writer log(file);
    VersionEdit edit;
    edit.SetComparatorName(options_.comparator->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    s = log.AddRecord(record);
    if (!s.ok()) {
      delete file;
      return s;
    }
    s = file->Close();
    delete file;
    if (!s.ok()) return s;

    return SetCurrentFile(env_, dbname_, 1);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* version_set_;
};

TEST_F(VersionSetTest_162, ConstructionDefaults_162) {
  // After construction, current() should not be nullptr after Recover,
  // but before Recover it's set to nullptr in the constructor.
  // We can test LastSequence and file number accessors.
  EXPECT_EQ(0, version_set_->LastSequence());
}

TEST_F(VersionSetTest_162, SetAndGetLastSequence_162) {
  version_set_->SetLastSequence(100);
  EXPECT_EQ(100, version_set_->LastSequence());
}

TEST_F(VersionSetTest_162, SetLastSequenceMonotonic_162) {
  version_set_->SetLastSequence(50);
  EXPECT_EQ(50, version_set_->LastSequence());
  version_set_->SetLastSequence(200);
  EXPECT_EQ(200, version_set_->LastSequence());
}

TEST_F(VersionSetTest_162, NewFileNumberIncrementing_162) {
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

TEST_F(VersionSetTest_162, ReuseFileNumber_162) {
  uint64_t num = version_set_->NewFileNumber();
  version_set_->ReuseFileNumber(num);
  uint64_t next = version_set_->NewFileNumber();
  // After reuse, the same number should be returned
  EXPECT_EQ(num, next);
}

TEST_F(VersionSetTest_162, ReuseFileNumberOnlyLastAllocated_162) {
  uint64_t num1 = version_set_->NewFileNumber();
  uint64_t num2 = version_set_->NewFileNumber();
  // Try to reuse num1 (which is not the last allocated)
  version_set_->ReuseFileNumber(num1);
  uint64_t next = version_set_->NewFileNumber();
  // Should not reuse num1 since num2 was allocated after it
  EXPECT_EQ(num2 + 1, next);
}

TEST_F(VersionSetTest_162, RecoverFromValidManifest_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // After recovery, current() should not be null
  EXPECT_NE(nullptr, version_set_->current());
}

TEST_F(VersionSetTest_162, RecoverFromMissingManifest_162) {
  // No CURRENT file exists, Recover should fail
  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

TEST_F(VersionSetTest_162, NumLevelFilesAfterRecover_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Initially there should be zero files at each level
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

TEST_F(VersionSetTest_162, NumLevelBytesAfterRecover_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

TEST_F(VersionSetTest_162, LogAndApplyWithNewFile_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionEdit edit;
  // Add a file to level 0
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, version_set_->NewFileNumber(), 100, smallest, largest);
  edit.SetLogNumber(version_set_->LogNumber());

  port::Mutex mu;
  mu.Lock();
  s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(1, version_set_->NumLevelFiles(0));
}

TEST_F(VersionSetTest_162, AddLiveFilesEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  // With no files added, live set should be empty
  EXPECT_TRUE(live.empty());
}

TEST_F(VersionSetTest_162, AddLiveFilesAfterAddingFile_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionEdit edit;
  uint64_t file_num = version_set_->NewFileNumber();
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, file_num, 100, smallest, largest);
  edit.SetLogNumber(version_set_->LogNumber());

  port::Mutex mu;
  mu.Lock();
  s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_EQ(1u, live.size());
  EXPECT_NE(live.end(), live.find(file_num));
}

TEST_F(VersionSetTest_162, MarkFileNumberUsed_162) {
  // MarkFileNumberUsed should advance the next file number if needed
  version_set_->MarkFileNumberUsed(1000);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_GT(next, 1000u);
}

TEST_F(VersionSetTest_162, LevelSummary_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  EXPECT_NE(nullptr, summary);
  EXPECT_GT(strlen(summary), 0u);
}

TEST_F(VersionSetTest_162, NeedsCompactionInitially_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // With no files, should not need compaction
  EXPECT_FALSE(version_set_->NeedsCompaction());
}

TEST_F(VersionSetTest_162, PickCompactionEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Compaction* c = version_set_->PickCompaction();
  // With no files and no compaction needed, should return nullptr
  EXPECT_EQ(nullptr, c);
  delete c;
}

TEST_F(VersionSetTest_162, VersionRefUnref_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  // current() already has a ref, add another
  v->Ref();
  // Should be safe to unref once
  v->Unref();
  // Version still alive because current holds a ref
  EXPECT_EQ(v, version_set_->current());
}

TEST_F(VersionSetTest_162, VersionNumFiles_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
}

TEST_F(VersionSetTest_162, VersionOverlapInLevelEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  Slice smallest("a");
  Slice largest("z");
  // No files at any level, should return false
  for (int level = 0; level < 7; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &smallest, &largest));
  }
}

TEST_F(VersionSetTest_162, VersionPickLevelForMemTableOutput_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  Slice smallest("a");
  Slice largest("z");
  int level = v->PickLevelForMemTableOutput(smallest, largest);
  // With no files, should pick a level >= 0
  EXPECT_GE(level, 0);
}

TEST_F(VersionSetTest_162, VersionDebugString_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

TEST_F(VersionSetTest_162, VersionGetOverlappingInputsEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  std::vector<FileMetaData*> inputs;
  InternalKey begin("a", 1, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
}

TEST_F(VersionSetTest_162, VersionGetOverlappingInputsNullBounds_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  std::vector<FileMetaData*> inputs;
  // Pass nullptr for begin and end to get all files
  v->GetOverlappingInputs(0, nullptr, nullptr, &inputs);
  EXPECT_TRUE(inputs.empty());
}

TEST_F(VersionSetTest_162, CompactRangeEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  InternalKey begin("a", 1, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  Compaction* c = version_set_->CompactRange(0, &begin, &end);
  // No files to compact
  EXPECT_EQ(nullptr, c);
  delete c;
}

TEST_F(VersionSetTest_162, MaxNextLevelOverlappingBytesEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

TEST_F(VersionSetTest_162, LogAndApplyDeleteFile_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // First add a file
  VersionEdit edit;
  uint64_t file_num = version_set_->NewFileNumber();
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, file_num, 100, smallest, largest);
  edit.SetLogNumber(version_set_->LogNumber());

  port::Mutex mu;
  mu.Lock();
  s = version_set_->LogAndApply(&edit, &mu);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(1, version_set_->NumLevelFiles(0));

  // Now delete the file
  VersionEdit edit2;
  edit2.RemoveFile(0, file_num);
  edit2.SetLogNumber(version_set_->LogNumber());
  s = version_set_->LogAndApply(&edit2, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(0, version_set_->NumLevelFiles(0));
}

TEST_F(VersionSetTest_162, ManifestFileNumber_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  uint64_t manifest_num = version_set_->ManifestFileNumber();
  EXPECT_GT(manifest_num, 0u);
}

TEST_F(VersionSetTest_162, LogNumber_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // LogNumber should be the value set during manifest creation
  uint64_t log_num = version_set_->LogNumber();
  EXPECT_EQ(0u, log_num);
}

TEST_F(VersionSetTest_162, PrevLogNumber_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  uint64_t prev_log = version_set_->PrevLogNumber();
  EXPECT_EQ(0u, prev_log);
}

TEST_F(VersionSetTest_162, VersionAddIteratorsEmpty_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* v = version_set_->current();
  ReadOptions read_options;
  std::vector<Iterator*> iters;
  v->AddIterators(read_options, &iters);
  // With no files, we still get level iterators (one per non-zero level)
  // Clean up iterators
  for (auto* iter : iters) {
    delete iter;
  }
}

TEST_F(VersionSetTest_162, MultipleLogAndApply_162) {
  Status s = CreateManifest();
  ASSERT_TRUE(s.ok()) << s.ToString();

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  port::Mutex mu;
  mu.Lock();

  // Add multiple files across different levels
  for (int i = 0; i < 3; i++) {
    VersionEdit edit;
    uint64_t file_num = version_set_->NewFileNumber();
    char small_buf[2] = {static_cast<char>('a' + i * 2), '\0'};
    char large_buf[2] = {static_cast<char>('b' + i * 2), '\0'};
    InternalKey smallest(Slice(small_buf), 1 + i, kTypeValue);
    InternalKey largest(Slice(large_buf), 2 + i, kTypeValue);
    edit.AddFile(0, file_num, 100, smallest, largest);
    edit.SetLogNumber(version_set_->LogNumber());
    s = version_set_->LogAndApply(&edit, &mu);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  mu.Unlock();
  EXPECT_EQ(3, version_set_->NumLevelFiles(0));
}

}  // namespace leveldb
