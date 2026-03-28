#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "table/table_cache.h"
#include "util/comparator.h"
#include "util/options.h"
#include "util/env.h"
#include "util/testutil.h"
#include "db/log_writer.h"
#include "db/dbformat.h"

#include <string>
#include <set>
#include <vector>

namespace leveldb {

class VersionSetTest_78 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_test_78";
    env_->CreateDir(dbname_);

    // Create CURRENT file pointing to a manifest
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
    // Write an empty version edit as a snapshot
    {
      log::Writer writer(file);
      VersionEdit edit;
      edit.SetComparatorName(BytewiseComparator()->Name());
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

    options_ = Options();
    options_.env = env_;
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache(dbname_, &options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);

    bool save_manifest = false;
    ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    delete icmp_;
    // Clean up files
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
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* version_set_;
};

// Test that current() returns a non-null version after recovery
TEST_F(VersionSetTest_78, CurrentVersionNotNull_78) {
  ASSERT_NE(nullptr, version_set_->current());
}

// Test NeedsCompaction returns false initially (no files, no compaction needed)
TEST_F(VersionSetTest_78, NeedsCompactionInitiallyFalse_78) {
  EXPECT_FALSE(version_set_->NeedsCompaction());
}

// Test ManifestFileNumber returns a valid number
TEST_F(VersionSetTest_78, ManifestFileNumber_78) {
  uint64_t manifest_num = version_set_->ManifestFileNumber();
  EXPECT_GT(manifest_num, 0u);
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_78, NewFileNumberIncrements_78) {
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  EXPECT_EQ(second, first + 1);
}

// Test ReuseFileNumber can reuse the last allocated number
TEST_F(VersionSetTest_78, ReuseFileNumber_78) {
  uint64_t num = version_set_->NewFileNumber();
  version_set_->ReuseFileNumber(num);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_EQ(next, num);
}

// Test LastSequence and SetLastSequence
TEST_F(VersionSetTest_78, LastSequenceGetSet_78) {
  EXPECT_EQ(0u, version_set_->LastSequence());
  version_set_->SetLastSequence(100);
  EXPECT_EQ(100u, version_set_->LastSequence());
}

// Test SetLastSequence with larger values
TEST_F(VersionSetTest_78, SetLastSequenceLargeValue_78) {
  uint64_t large_seq = 1000000000ULL;
  version_set_->SetLastSequence(large_seq);
  EXPECT_EQ(large_seq, version_set_->LastSequence());
}

// Test LogNumber
TEST_F(VersionSetTest_78, LogNumber_78) {
  uint64_t log_num = version_set_->LogNumber();
  // After initial recovery with log_number 0, it should be 0
  EXPECT_EQ(0u, log_num);
}

// Test PrevLogNumber
TEST_F(VersionSetTest_78, PrevLogNumber_78) {
  uint64_t prev_log = version_set_->PrevLogNumber();
  EXPECT_EQ(0u, prev_log);
}

// Test NumLevelFiles on empty database
TEST_F(VersionSetTest_78, NumLevelFilesEmpty_78) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes on empty database
TEST_F(VersionSetTest_78, NumLevelBytesEmpty_78) {
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

// Test AddLiveFiles on empty database
TEST_F(VersionSetTest_78, AddLiveFilesEmpty_78) {
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test LevelSummary returns non-null
TEST_F(VersionSetTest_78, LevelSummary_78) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  ASSERT_NE(nullptr, summary);
  // Should contain some meaningful content
  EXPECT_GT(strlen(summary), 0u);
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_78, MarkFileNumberUsed_78) {
  uint64_t high_num = 1000;
  version_set_->MarkFileNumberUsed(high_num);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_GT(next, high_num);
}

// Test LogAndApply with empty edit
TEST_F(VersionSetTest_78, LogAndApplyEmptyEdit_78) {
  port::Mutex mu;
  mu.Lock();
  VersionEdit edit;
  edit.SetLogNumber(version_set_->LogNumber());
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  EXPECT_TRUE(s.ok());
}

// Test LogAndApply adding a file
TEST_F(VersionSetTest_78, LogAndApplyAddFile_78) {
  port::Mutex mu;
  mu.Lock();

  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  edit.SetLogNumber(version_set_->LogNumber());
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(1, file_number, 1000, smallest, largest);

  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(1, version_set_->NumLevelFiles(1));
}

// Test that after adding a file, AddLiveFiles includes it
TEST_F(VersionSetTest_78, AddLiveFilesAfterAdd_78) {
  port::Mutex mu;
  mu.Lock();

  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  edit.SetLogNumber(version_set_->LogNumber());

  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(2, file_number, 500, smallest, largest);

  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_TRUE(live.count(file_number) > 0);
}

// Test MaxNextLevelOverlappingBytes on empty database
TEST_F(VersionSetTest_78, MaxNextLevelOverlappingBytesEmpty_78) {
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test PickCompaction on empty database returns null
TEST_F(VersionSetTest_78, PickCompactionEmpty_78) {
  Compaction* c = version_set_->PickCompaction();
  EXPECT_EQ(nullptr, c);
}

// Test CompactRange on empty database
TEST_F(VersionSetTest_78, CompactRangeEmpty_78) {
  InternalKey begin("a", 1, kTypeValue);
  InternalKey end("z", 1, kTypeValue);
  Compaction* c = version_set_->CompactRange(0, &begin, &end);
  // On empty db, should return nullptr since no files
  EXPECT_EQ(nullptr, c);
}

// Test CompactRange with nullptr begin and end
TEST_F(VersionSetTest_78, CompactRangeNullBounds_78) {
  Compaction* c = version_set_->CompactRange(0, nullptr, nullptr);
  EXPECT_EQ(nullptr, c);
}

// Test Recover sets save_manifest appropriately
TEST_F(VersionSetTest_78, RecoverSetsFlags_78) {
  // Create a fresh VersionSet and recover
  VersionSet* vs2 = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  bool save_manifest = false;
  Status s = vs2->Recover(&save_manifest);
  EXPECT_TRUE(s.ok());
  delete vs2;
}

// Test NumLevelBytes after adding files
TEST_F(VersionSetTest_78, NumLevelBytesAfterAdd_78) {
  port::Mutex mu;
  mu.Lock();

  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  edit.SetLogNumber(version_set_->LogNumber());

  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  uint64_t file_size = 12345;
  edit.AddFile(3, file_number, file_size, smallest, largest);

  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  EXPECT_EQ(static_cast<int64_t>(file_size), version_set_->NumLevelBytes(3));
}

// Test Version's NumFiles method through current version
TEST_F(VersionSetTest_78, VersionNumFilesEmpty_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
}

// Test Version Ref and Unref
TEST_F(VersionSetTest_78, VersionRefUnref_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  v->Ref();
  v->Unref();
  // Should still be alive since current holds a ref
  EXPECT_NE(nullptr, version_set_->current());
}

// Test DebugString on current version
TEST_F(VersionSetTest_78, VersionDebugString_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test OverlapInLevel on empty version
TEST_F(VersionSetTest_78, VersionOverlapInLevelEmpty_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  Slice small_key("a");
  Slice large_key("z");
  for (int level = 0; level < 7; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &small_key, &large_key));
  }
}

// Test OverlapInLevel with null keys on empty version
TEST_F(VersionSetTest_78, VersionOverlapInLevelNullKeys_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  EXPECT_FALSE(v->OverlapInLevel(0, nullptr, nullptr));
}

// Test PickLevelForMemTableOutput on empty version
TEST_F(VersionSetTest_78, VersionPickLevelForMemTableOutputEmpty_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  Slice small_key("a");
  Slice large_key("z");
  int level = v->PickLevelForMemTableOutput(small_key, large_key);
  EXPECT_GE(level, 0);
}

// Test GetOverlappingInputs on empty version
TEST_F(VersionSetTest_78, VersionGetOverlappingInputsEmpty_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  InternalKey begin("a", 1, kTypeValue);
  InternalKey end("z", 1, kTypeValue);
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
}

// Test multiple NewFileNumber calls produce strictly increasing values
TEST_F(VersionSetTest_78, NewFileNumberStrictlyIncreasing_78) {
  std::vector<uint64_t> nums;
  for (int i = 0; i < 10; i++) {
    nums.push_back(version_set_->NewFileNumber());
  }
  for (size_t i = 1; i < nums.size(); i++) {
    EXPECT_EQ(nums[i], nums[i - 1] + 1);
  }
}

// Test NeedsCompaction after adding many files to level 0
TEST_F(VersionSetTest_78, NeedsCompactionAfterManyLevel0Files_78) {
  port::Mutex mu;
  
  // Add many files to level 0 to trigger compaction need
  for (int i = 0; i < 5; i++) {
    mu.Lock();
    VersionEdit edit;
    uint64_t file_number = version_set_->NewFileNumber();
    edit.SetLogNumber(version_set_->LogNumber());

    char small_buf[16], large_buf[16];
    snprintf(small_buf, sizeof(small_buf), "a%05d", i);
    snprintf(large_buf, sizeof(large_buf), "z%05d", i);
    InternalKey smallest(small_buf, i + 1, kTypeValue);
    InternalKey largest(large_buf, i + 2, kTypeValue);
    edit.AddFile(0, file_number, 1000000, smallest, largest);

    Status s = version_set_->LogAndApply(&edit, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok());
  }

  // With 5 files in level 0 (threshold is typically 4), should need compaction
  EXPECT_TRUE(version_set_->NeedsCompaction());
}

// Test LogAndApply with file deletion
TEST_F(VersionSetTest_78, LogAndApplyDeleteFile_78) {
  port::Mutex mu;
  
  // First add a file
  mu.Lock();
  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  edit.SetLogNumber(version_set_->LogNumber());
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(1, file_number, 1000, smallest, largest);
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(1, version_set_->NumLevelFiles(1));

  // Now delete that file
  mu.Lock();
  VersionEdit edit2;
  edit2.SetLogNumber(version_set_->LogNumber());
  edit2.RemoveFile(1, file_number);
  s = version_set_->LogAndApply(&edit2, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(0, version_set_->NumLevelFiles(1));
}

// Test that adding files to multiple levels works
TEST_F(VersionSetTest_78, AddFilesToMultipleLevels_78) {
  port::Mutex mu;
  mu.Lock();

  VersionEdit edit;
  edit.SetLogNumber(version_set_->LogNumber());

  for (int level = 0; level < 7; level++) {
    uint64_t file_number = version_set_->NewFileNumber();
    char small_buf[16], large_buf[16];
    snprintf(small_buf, sizeof(small_buf), "a%d", level);
    snprintf(large_buf, sizeof(large_buf), "z%d", level);
    InternalKey smallest(small_buf, 1, kTypeValue);
    InternalKey largest(large_buf, 2, kTypeValue);
    edit.AddFile(level, file_number, 100 * (level + 1), smallest, largest);
  }

  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(1, version_set_->NumLevelFiles(level));
  }
}

// Test Version::AddIterators on empty version
TEST_F(VersionSetTest_78, VersionAddIteratorsEmpty_78) {
  Version* v = version_set_->current();
  ASSERT_NE(nullptr, v);
  ReadOptions ropts;
  std::vector<Iterator*> iters;
  v->AddIterators(ropts, &iters);
  // Should have at least level-0 iterators (0 files) + one for each other level
  // Cleanup iterators
  for (auto* iter : iters) {
    delete iter;
  }
}

}  // namespace leveldb
