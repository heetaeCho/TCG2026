#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "leveldb/db.h"
#include "db/dbformat.h"
#include "util/testutil.h"
#include "port/port.h"

#include <set>
#include <string>
#include <vector>

namespace leveldb {

class VersionSetTest_70 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_70";
    
    // Create the database directory
    env_->CreateDir(dbname_);
    
    // Write a CURRENT file pointing to a manifest
    // We need to create a proper DB to get a valid VersionSet
    options_.env = env_;
    options_.create_if_missing = true;
    
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    delete icmp_;
    
    // Cleanup
    DestroyDB(dbname_, Options());
  }

  // Helper to initialize the VersionSet via Recover after creating a valid DB
  void InitializeDB() {
    // Create a real DB to have valid manifest files
    DB* db = nullptr;
    Options opts;
    opts.create_if_missing = true;
    Status s = DB::Open(opts, dbname_, &db);
    ASSERT_TRUE(s.ok()) << s.ToString();
    delete db;
    
    // Now re-create our VersionSet and recover
    delete version_set_;
    delete table_cache_;
    
    table_cache_ = new TableCache(dbname_, &options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
    
    bool save_manifest = false;
    s = version_set_->Recover(&save_manifest);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  const InternalKeyComparator* icmp_;
  VersionSet* version_set_;
};

// Test that current() returns non-null after a successful Recover
TEST_F(VersionSetTest_70, CurrentReturnsNonNullAfterRecover_70) {
  InitializeDB();
  ASSERT_NE(nullptr, version_set_->current());
}

// Test Recover on a valid DB
TEST_F(VersionSetTest_70, RecoverSucceeds_70) {
  DB* db = nullptr;
  Options opts;
  opts.create_if_missing = true;
  Status s = DB::Open(opts, dbname_, &db);
  ASSERT_TRUE(s.ok());
  delete db;

  delete version_set_;
  delete table_cache_;
  table_cache_ = new TableCache(dbname_, &options_, 100);
  version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);

  bool save_manifest = false;
  s = version_set_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test Recover on a non-existent DB fails
TEST_F(VersionSetTest_70, RecoverFailsOnNonExistentDB_70) {
  std::string bad_dbname = testing::TempDir() + "/nonexistent_db_70";
  
  TableCache* tc = new TableCache(bad_dbname, &options_, 100);
  VersionSet* vs = new VersionSet(bad_dbname, &options_, tc, icmp_);
  
  bool save_manifest = false;
  Status s = vs->Recover(&save_manifest);
  EXPECT_FALSE(s.ok());
  
  delete vs;
  delete tc;
}

// Test LastSequence and SetLastSequence
TEST_F(VersionSetTest_70, LastSequenceGetAndSet_70) {
  InitializeDB();
  
  uint64_t initial_seq = version_set_->LastSequence();
  EXPECT_EQ(0u, initial_seq);
  
  version_set_->SetLastSequence(100);
  EXPECT_EQ(100u, version_set_->LastSequence());
  
  version_set_->SetLastSequence(200);
  EXPECT_EQ(200u, version_set_->LastSequence());
}

// Test NewFileNumber returns incrementing values
TEST_F(VersionSetTest_70, NewFileNumberIncrementing_70) {
  InitializeDB();
  
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  uint64_t third = version_set_->NewFileNumber();
  
  EXPECT_LT(first, second);
  EXPECT_LT(second, third);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_70, ReuseFileNumber_70) {
  InitializeDB();
  
  uint64_t num = version_set_->NewFileNumber();
  // Reuse it - should allow this number to be returned again
  version_set_->ReuseFileNumber(num);
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_EQ(num, next);
}

// Test NumLevelFiles returns 0 for empty DB
TEST_F(VersionSetTest_70, NumLevelFilesEmptyDB_70) {
  InitializeDB();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, version_set_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes returns 0 for empty DB
TEST_F(VersionSetTest_70, NumLevelBytesEmptyDB_70) {
  InitializeDB();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, version_set_->NumLevelBytes(level));
  }
}

// Test ManifestFileNumber is valid after recovery
TEST_F(VersionSetTest_70, ManifestFileNumberValid_70) {
  InitializeDB();
  
  uint64_t manifest_num = version_set_->ManifestFileNumber();
  EXPECT_GT(manifest_num, 0u);
}

// Test LogNumber after recovery
TEST_F(VersionSetTest_70, LogNumberAfterRecover_70) {
  InitializeDB();
  
  // LogNumber should be a valid number
  uint64_t log_num = version_set_->LogNumber();
  EXPECT_GE(log_num, 0u);
}

// Test PrevLogNumber after recovery
TEST_F(VersionSetTest_70, PrevLogNumberAfterRecover_70) {
  InitializeDB();
  
  uint64_t prev_log = version_set_->PrevLogNumber();
  EXPECT_GE(prev_log, 0u);
}

// Test AddLiveFiles on empty DB
TEST_F(VersionSetTest_70, AddLiveFilesEmptyDB_70) {
  InitializeDB();
  
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  // For an empty DB, there should be no live SST files
  // (but there may be zero or more depending on manifest state)
  // We just check it doesn't crash
}

// Test NeedsCompaction on empty DB
TEST_F(VersionSetTest_70, NeedsCompactionEmptyDB_70) {
  InitializeDB();
  
  // Empty DB should not need compaction
  bool needs = version_set_->NeedsCompaction();
  // We just verify it returns without crashing
  (void)needs;
}

// Test PickCompaction on empty DB
TEST_F(VersionSetTest_70, PickCompactionEmptyDB_70) {
  InitializeDB();
  
  Compaction* c = version_set_->PickCompaction();
  // Empty DB should not pick a compaction
  EXPECT_EQ(nullptr, c);
  delete c;
}

// Test LevelSummary
TEST_F(VersionSetTest_70, LevelSummary_70) {
  InitializeDB();
  
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = version_set_->LevelSummary(&scratch);
  ASSERT_NE(nullptr, summary);
  // Summary should be a non-empty string
  EXPECT_GT(strlen(summary), 0u);
}

// Test MaxNextLevelOverlappingBytes on empty DB
TEST_F(VersionSetTest_70, MaxNextLevelOverlappingBytesEmpty_70) {
  InitializeDB();
  
  int64_t result = version_set_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, result);
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_70, MarkFileNumberUsed_70) {
  InitializeDB();
  
  // Mark a large file number as used
  version_set_->MarkFileNumberUsed(1000);
  
  // Next file number should be greater than 1000
  uint64_t next = version_set_->NewFileNumber();
  EXPECT_GT(next, 1000u);
}

// Test LogAndApply with a simple edit
TEST_F(VersionSetTest_70, LogAndApplySimple_70) {
  InitializeDB();
  
  VersionEdit edit;
  edit.SetLogNumber(version_set_->LogNumber());
  
  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test CompactRange returns nullptr when no files exist in the level
TEST_F(VersionSetTest_70, CompactRangeEmptyLevel_70) {
  InitializeDB();
  
  InternalKey begin(Slice("a"), kMaxSequenceNumber, kValueTypeForSeek);
  InternalKey end(Slice("z"), 0, static_cast<ValueType>(0));
  
  Compaction* c = version_set_->CompactRange(0, &begin, &end);
  // With no files, this should return nullptr
  EXPECT_EQ(nullptr, c);
  delete c;
}

// Test that SetLastSequence with same value works
TEST_F(VersionSetTest_70, SetLastSequenceSameValue_70) {
  InitializeDB();
  
  version_set_->SetLastSequence(42);
  EXPECT_EQ(42u, version_set_->LastSequence());
  
  version_set_->SetLastSequence(42);
  EXPECT_EQ(42u, version_set_->LastSequence());
}

// Test SetLastSequence with max uint64_t
TEST_F(VersionSetTest_70, SetLastSequenceLargeValue_70) {
  InitializeDB();
  
  uint64_t large_val = 0xFFFFFFFFFFFFFFULL;  // Large but not max to avoid issues
  version_set_->SetLastSequence(large_val);
  EXPECT_EQ(large_val, version_set_->LastSequence());
}

// Test multiple NewFileNumber calls
TEST_F(VersionSetTest_70, MultipleNewFileNumbers_70) {
  InitializeDB();
  
  std::set<uint64_t> numbers;
  for (int i = 0; i < 100; i++) {
    uint64_t num = version_set_->NewFileNumber();
    // Each number should be unique
    EXPECT_TRUE(numbers.insert(num).second) << "Duplicate file number: " << num;
  }
}

// Test LogAndApply with adding a file
TEST_F(VersionSetTest_70, LogAndApplyAddFile_70) {
  InitializeDB();
  
  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 1, kTypeValue);
  edit.AddFile(1, file_number, 100, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // After adding a file to level 1, NumLevelFiles should reflect it
  EXPECT_EQ(1, version_set_->NumLevelFiles(1));
}

// Test AddLiveFiles includes added files
TEST_F(VersionSetTest_70, AddLiveFilesIncludesAddedFiles_70) {
  InitializeDB();
  
  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 1, kTypeValue);
  edit.AddFile(2, file_number, 200, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  
  EXPECT_TRUE(live.count(file_number) > 0);
}

// Test current() returns a valid Version after LogAndApply
TEST_F(VersionSetTest_70, CurrentUpdatedAfterLogAndApply_70) {
  InitializeDB();
  
  Version* v_before = version_set_->current();
  ASSERT_NE(nullptr, v_before);
  
  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 1, kTypeValue);
  edit.AddFile(0, file_number, 100, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  
  Version* v_after = version_set_->current();
  ASSERT_NE(nullptr, v_after);
  // The current version should have changed
  EXPECT_NE(v_before, v_after);
}

// Test ReuseFileNumber with a number that's not the latest doesn't reuse
TEST_F(VersionSetTest_70, ReuseFileNumberOldNumber_70) {
  InitializeDB();
  
  uint64_t first = version_set_->NewFileNumber();
  uint64_t second = version_set_->NewFileNumber();
  
  // Try to reuse first - should not work since second was already allocated
  version_set_->ReuseFileNumber(first);
  uint64_t third = version_set_->NewFileNumber();
  EXPECT_GT(third, second);
}

// Test NumLevelBytes after adding a file
TEST_F(VersionSetTest_70, NumLevelBytesAfterAddFile_70) {
  InitializeDB();
  
  VersionEdit edit;
  uint64_t file_number = version_set_->NewFileNumber();
  uint64_t file_size = 12345;
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 1, kTypeValue);
  edit.AddFile(1, file_number, file_size, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  
  EXPECT_EQ(static_cast<int64_t>(file_size), version_set_->NumLevelBytes(1));
}

}  // namespace leveldb
