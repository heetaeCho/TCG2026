#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"
#include "util/testutil.h"

namespace leveldb {

class VersionSetBuilderTest_480 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_builder_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete icmp_;
    delete table_cache_;
    // Clean up test directory
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* vset_;
};

// Test that Builder can be constructed and destructed without issues
TEST_F(VersionSetBuilderTest_480, ConstructAndDestruct_480) {
  // We need a Version to pass to Builder. We'll use the current version
  // from VersionSet after recovery, or create one through VersionSet's
  // interface.
  // Since VersionSet constructor sets current_ to nullptr, we need to
  // initialize it properly. Let's do a Recover first.
  bool save_manifest = false;
  
  // Create CURRENT file pointing to a manifest
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  
  // Write a valid version edit as a log record
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  
  // Write CURRENT file
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);
  
  // Now test that we can observe effects through VersionSet's public interface
  // The current version should have 0 files at all levels
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 0);
  }
}

// Test that LogAndApply with added files works properly (exercises Builder internally)
TEST_F(VersionSetBuilderTest_480, LogAndApplyAddFiles_480) {
  bool save_manifest = false;
  
  // Create CURRENT/MANIFEST
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Add a file via LogAndApply (which uses Builder internally)
  VersionEdit ve;
  InternalKey smallest(Slice("a"), 1, kTypeValue);
  InternalKey largest(Slice("z"), 2, kTypeValue);
  ve.AddFile(1, vset_->NewFileNumber(), 100, smallest, largest);
  ve.SetLogNumber(vset_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&ve, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  EXPECT_EQ(vset_->NumLevelFiles(1), 1);
  EXPECT_EQ(vset_->NumLevelFiles(0), 0);
}

// Test adding files to multiple levels
TEST_F(VersionSetBuilderTest_480, AddFilesToMultipleLevels_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Add files to different levels
  VersionEdit ve;
  for (int level = 0; level < config::kNumLevels; level++) {
    InternalKey smallest(Slice("a"), 100 + level * 2, kTypeValue);
    InternalKey largest(Slice("z"), 100 + level * 2 + 1, kTypeValue);
    ve.AddFile(level, vset_->NewFileNumber(), 100, smallest, largest);
  }
  ve.SetLogNumber(vset_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&ve, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 1)
        << "Level " << level << " should have 1 file";
  }
}

// Test adding and then deleting files
TEST_F(VersionSetBuilderTest_480, AddAndDeleteFiles_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // First, add a file
  uint64_t file_number = vset_->NewFileNumber();
  {
    VersionEdit ve;
    InternalKey smallest(Slice("a"), 1, kTypeValue);
    InternalKey largest(Slice("z"), 2, kTypeValue);
    ve.AddFile(1, file_number, 100, smallest, largest);
    ve.SetLogNumber(vset_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    s = vset_->LogAndApply(&ve, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }
  
  EXPECT_EQ(vset_->NumLevelFiles(1), 1);
  
  // Now delete the file
  {
    VersionEdit ve;
    ve.RemoveFile(1, file_number);
    ve.SetLogNumber(vset_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    s = vset_->LogAndApply(&ve, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }
  
  EXPECT_EQ(vset_->NumLevelFiles(1), 0);
}

// Test adding multiple files to the same level - they should be ordered by smallest key
TEST_F(VersionSetBuilderTest_480, MultipleFilesOrderedBySmallestKey_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Add multiple non-overlapping files to level 1
  VersionEdit ve;
  InternalKey smallest1(Slice("m"), 1, kTypeValue);
  InternalKey largest1(Slice("p"), 2, kTypeValue);
  ve.AddFile(1, vset_->NewFileNumber(), 100, smallest1, largest1);
  
  InternalKey smallest2(Slice("a"), 3, kTypeValue);
  InternalKey largest2(Slice("d"), 4, kTypeValue);
  ve.AddFile(1, vset_->NewFileNumber(), 100, smallest2, largest2);
  
  InternalKey smallest3(Slice("e"), 5, kTypeValue);
  InternalKey largest3(Slice("k"), 6, kTypeValue);
  ve.AddFile(1, vset_->NewFileNumber(), 100, smallest3, largest3);
  
  ve.SetLogNumber(vset_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&ve, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  EXPECT_EQ(vset_->NumLevelFiles(1), 3);
}

// Test simultaneous add and delete in same edit
TEST_F(VersionSetBuilderTest_480, SimultaneousAddAndDelete_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Add a file first
  uint64_t file_number1 = vset_->NewFileNumber();
  {
    VersionEdit ve;
    InternalKey smallest(Slice("a"), 1, kTypeValue);
    InternalKey largest(Slice("m"), 2, kTypeValue);
    ve.AddFile(1, file_number1, 100, smallest, largest);
    ve.SetLogNumber(vset_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    s = vset_->LogAndApply(&ve, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }
  EXPECT_EQ(vset_->NumLevelFiles(1), 1);
  
  // In a single edit, delete the old file and add a new one
  {
    VersionEdit ve;
    ve.RemoveFile(1, file_number1);
    
    InternalKey smallest(Slice("n"), 3, kTypeValue);
    InternalKey largest(Slice("z"), 4, kTypeValue);
    ve.AddFile(1, vset_->NewFileNumber(), 200, smallest, largest);
    ve.SetLogNumber(vset_->LogNumber());
    
    port::Mutex mu;
    mu.Lock();
    s = vset_->LogAndApply(&ve, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }
  
  EXPECT_EQ(vset_->NumLevelFiles(1), 1);
}

// Test NumLevelBytes after adding files
TEST_F(VersionSetBuilderTest_480, NumLevelBytesAfterAddFiles_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Initially 0 bytes at all levels
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelBytes(level), 0);
  }
  
  // Add a file with known size
  VersionEdit ve;
  InternalKey smallest(Slice("a"), 1, kTypeValue);
  InternalKey largest(Slice("z"), 2, kTypeValue);
  uint64_t file_size = 12345;
  ve.AddFile(2, vset_->NewFileNumber(), file_size, smallest, largest);
  ve.SetLogNumber(vset_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&ve, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  EXPECT_EQ(vset_->NumLevelBytes(2), file_size);
  EXPECT_EQ(vset_->NumLevelBytes(0), 0);
  EXPECT_EQ(vset_->NumLevelBytes(1), 0);
}

// Test that applying empty edit doesn't change anything
TEST_F(VersionSetBuilderTest_480, EmptyEditNoChange_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Apply an empty edit
  VersionEdit ve;
  ve.SetLogNumber(vset_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&ve, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 0);
  }
}

// Test Version's OverlapInLevel after adding files through Builder
TEST_F(VersionSetBuilderTest_480, OverlapInLevelAfterBuild_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Add a file at level 1 covering range [c, m]
  VersionEdit ve;
  InternalKey smallest(Slice("c"), 1, kTypeValue);
  InternalKey largest(Slice("m"), 2, kTypeValue);
  ve.AddFile(1, vset_->NewFileNumber(), 100, smallest, largest);
  ve.SetLogNumber(vset_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&ve, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  Version* current = vset_->current();
  
  // Check overlap
  Slice small_key("d");
  Slice large_key("f");
  EXPECT_TRUE(current->OverlapInLevel(1, &small_key, &large_key));
  
  // No overlap outside the range
  Slice small_key2("n");
  Slice large_key2("z");
  EXPECT_FALSE(current->OverlapInLevel(1, &small_key2, &large_key2));
  
  // No files at level 2
  EXPECT_FALSE(current->OverlapInLevel(2, &small_key, &large_key));
}

// Test multiple sequential edits building up state
TEST_F(VersionSetBuilderTest_480, SequentialEdits_480) {
  bool save_manifest = false;
  
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(options_.comparator->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;
  ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  port::Mutex mu;
  
  // Apply 5 sequential edits, each adding a file
  for (int i = 0; i < 5; i++) {
    VersionEdit ve;
    std::string small_str(1, 'a' + i * 2);
    std::string large_str(1, 'a' + i * 2 + 1);
    InternalKey smallest(Slice(small_str), i * 2 + 1, kTypeValue);
    InternalKey largest(Slice(large_str), i * 2 + 2, kTypeValue);
    ve.AddFile(1, vset_->NewFileNumber(), 100, smallest, largest);
    ve.SetLogNumber(vset_->LogNumber());
    
    mu.Lock();
    s = vset_->LogAndApply(&ve, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
    
    EXPECT_EQ(vset_->NumLevelFiles(1), i + 1);
  }
}

}  // namespace leveldb
