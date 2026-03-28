#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/filename.h"
#include "db/log_writer.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table_cache.h"
#include "table/merger.h"
#include "util/logging.h"

namespace leveldb {

class VersionSetTest_72 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_72";
    env_->CreateDir(dbname_);

    options_.env = env_;
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache(dbname_, &options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    std::vector<std::string> filenames;
    env_->GetChildren(dbname_, &filenames);
    for (const auto& filename : filenames) {
      env_->RemoveFile(dbname_ + "/" + filename);
    }
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  const InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* version_set_;
};

// Test that NewFileNumber returns incrementing numbers
TEST_F(VersionSetTest_72, NewFileNumberIncrementing_72) {
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  uint64_t third = version_set_->NewFileNumber();

  EXPECT_EQ(second, first + 1);
  EXPECT_EQ(third, second + 1);
}

// Test that NewFileNumber starts at 2 (from constructor)
TEST_F(VersionSetTest_72, NewFileNumberStartsAtTwo_72) {
  uint64_t first = version_set_->NewFileNumber();
  EXPECT_EQ(first, 2);
}

// Test LastSequence initial value and SetLastSequence
TEST_F(VersionSetTest_72, LastSequenceInitialValue_72) {
  EXPECT_EQ(version_set_->LastSequence(), 0);
}

TEST_F(VersionSetTest_72, SetLastSequence_72) {
  version_set_->SetLastSequence(100);
  EXPECT_EQ(version_set_->LastSequence(), 100);
}

TEST_F(VersionSetTest_72, SetLastSequenceMultipleTimes_72) {
  version_set_->SetLastSequence(50);
  EXPECT_EQ(version_set_->LastSequence(), 50);
  version_set_->SetLastSequence(200);
  EXPECT_EQ(version_set_->LastSequence(), 200);
}

// Test LogNumber initial value
TEST_F(VersionSetTest_72, LogNumberInitialValue_72) {
  EXPECT_EQ(version_set_->LogNumber(), 0);
}

// Test PrevLogNumber initial value
TEST_F(VersionSetTest_72, PrevLogNumberInitialValue_72) {
  EXPECT_EQ(version_set_->PrevLogNumber(), 0);
}

// Test ManifestFileNumber initial value
TEST_F(VersionSetTest_72, ManifestFileNumberInitialValue_72) {
  EXPECT_EQ(version_set_->ManifestFileNumber(), 0);
}

// Test MarkFileNumberUsed with a number less than next_file_number_
TEST_F(VersionSetTest_72, MarkFileNumberUsedLessThanNext_72) {
  uint64_t first = version_set_->NewFileNumber();
  // Mark a number less than the current next_file_number_ should not change it
  version_set_->MarkFileNumberUsed(1);
  uint64_t second = version_set_->NewFileNumber();
  EXPECT_EQ(second, first + 1);
}

// Test MarkFileNumberUsed with a number greater than or equal to next_file_number_
TEST_F(VersionSetTest_72, MarkFileNumberUsedGreaterThanNext_72) {
  version_set_->MarkFileNumberUsed(100);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_GE(next, 101);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_72, ReuseFileNumber_72) {
  uint64_t num = version_set_->NewFileNumber();
  version_set_->ReuseFileNumber(num);
  uint64_t reused = version_set_->NewFileNumber();
  EXPECT_EQ(reused, num);
}

// Test ReuseFileNumber with a number that isn't the latest
TEST_F(VersionSetTest_72, ReuseFileNumberNotLatest_72) {
  uint64_t num1 = version_set_->NewFileNumber();
  uint64_t num2 = version_set_->NewFileNumber();
  // Try to reuse num1 (not the latest), should not reuse
  version_set_->ReuseFileNumber(num1);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_EQ(next, num2 + 1);
}

// Test NumLevelFiles with no files
TEST_F(VersionSetTest_72, NumLevelFilesInitiallyZero_72) {
  // Before recovery, current_ may be nullptr, so we need to set up properly.
  // Create a CURRENT file to allow Recover.
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(version_set_->NumLevelFiles(level), 0);
  }
}

// Test NumLevelBytes with no files
TEST_F(VersionSetTest_72, NumLevelBytesInitiallyZero_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(version_set_->NumLevelBytes(level), 0);
  }
}

// Test current() returns non-null after recovery
TEST_F(VersionSetTest_72, CurrentAfterRecovery_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_NE(version_set_->current(), nullptr);
}

// Test Recover with missing CURRENT file
TEST_F(VersionSetTest_72, RecoverMissingCurrentFile_72) {
  bool save_manifest = false;
  Status s = version_set_->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
}

// Test LevelSummary returns non-null
TEST_F(VersionSetTest_72, LevelSummaryReturnsNonNull_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  EXPECT_NE(summary, nullptr);
  EXPECT_GT(strlen(summary), 0u);
}

// Test AddLiveFiles
TEST_F(VersionSetTest_72, AddLiveFilesEmptyInitially_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test NeedsCompaction after fresh recovery
TEST_F(VersionSetTest_72, NeedsCompactionAfterRecovery_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  // With no files, compaction should not be needed
  EXPECT_FALSE(version_set_->NeedsCompaction());
}

// Test multiple NewFileNumber calls produce unique numbers
TEST_F(VersionSetTest_72, NewFileNumberUniqueness_72) {
  std::set<uint64_t> numbers;
  for (int i = 0; i < 1000; i++) {
    uint64_t num = version_set_->NewFileNumber();
    EXPECT_EQ(numbers.count(num), 0u) << "Duplicate file number: " << num;
    numbers.insert(num);
  }
  EXPECT_EQ(numbers.size(), 1000u);
}

// Test SetLastSequence with max value
TEST_F(VersionSetTest_72, SetLastSequenceMaxValue_72) {
  uint64_t max_val = UINT64_MAX;
  version_set_->SetLastSequence(max_val);
  EXPECT_EQ(version_set_->LastSequence(), max_val);
}

// Test MarkFileNumberUsed boundary: exact next_file_number_
TEST_F(VersionSetTest_72, MarkFileNumberUsedExactBoundary_72) {
  // next_file_number_ starts at 2
  // NewFileNumber returns 2 and increments to 3
  uint64_t num = version_set_->NewFileNumber();  // returns 2, next is 3
  EXPECT_EQ(num, 2);

  // Mark number 3 as used - should bump next to at least 4
  version_set_->MarkFileNumberUsed(3);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_GE(next, 4);
}

// Test LogAndApply after recovery
TEST_F(VersionSetTest_72, LogAndApplyAfterRecovery_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  port::Mutex mu;
  VersionEdit new_edit;
  new_edit.SetLogNumber(version_set_->LogNumber());
  mu.Lock();
  Status s = version_set_->LogAndApply(&new_edit, &mu);
  mu.Unlock();
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test MaxNextLevelOverlappingBytes with empty database
TEST_F(VersionSetTest_72, MaxNextLevelOverlappingBytesEmpty_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(result, 0);
}

// Test PickCompaction with empty database returns null
TEST_F(VersionSetTest_72, PickCompactionEmptyReturnsNull_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  Compaction* c = version_set_->PickCompaction();
  EXPECT_EQ(c, nullptr);
}

// Test CompactRange on empty database
TEST_F(VersionSetTest_72, CompactRangeEmptyReturnsNull_72) {
  std::string manifest = "MANIFEST-000001";
  WritableFile* file;
  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
  log::Writer writer(file);
  VersionEdit edit;
  edit.SetComparatorName(icmp_->user_comparator()->Name());
  edit.SetLogNumber(0);
  edit.SetNextFile(2);
  edit.SetLastSequence(0);
  std::string record;
  edit.EncodeTo(&record);
  ASSERT_TRUE(writer.AddRecord(record).ok());
  delete file;

  ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/CURRENT", &file).ok());
  ASSERT_TRUE(file->Append(manifest + "\n").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;

  bool save_manifest = false;
  ASSERT_TRUE(version_set_->Recover(&save_manifest).ok());

  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 100, kTypeValue);
  Compaction* c = version_set_->CompactRange(0, &begin, &end);
  EXPECT_EQ(c, nullptr);
}

}  // namespace leveldb
