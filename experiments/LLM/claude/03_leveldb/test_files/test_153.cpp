#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/options.h"
#include "util/env.h"
#include "util/testutil.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"
#include "leveldb/table.h"
#include "leveldb/db.h"

#include <memory>
#include <string>
#include <vector>

namespace leveldb {

class VersionSetTest_153 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_set_test_153";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    const int table_cache_size = 100;
    cache_ = NewLRUCache(table_cache_size);
    table_cache_ = new TableCache(dbname_, &options_, table_cache_size);

    icmp_ = new InternalKeyComparator(BytewiseComparator());
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    delete cache_;
    // Clean up test directory
    DestroyDB(dbname_, Options());
  }

  // Helper to add a file to a VersionEdit for a specific level
  void AddFileToEdit(VersionEdit* edit, int level, uint64_t file_number,
                     uint64_t file_size, const InternalKey& smallest,
                     const InternalKey& largest) {
    edit->AddFile(level, file_number, file_size, smallest, largest);
  }

  // Helper to build a version with specific files
  Version* BuildVersionWithFiles() {
    // We need to use LogAndApply to create versions with files
    // First recover to initialize
    bool save_manifest = false;

    // Create a CURRENT file pointing to a manifest
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    EXPECT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
    // Write an empty version edit as a snapshot
    {
      log::Writer writer(file);
      std::string record;
      VersionEdit edit;
      edit.SetComparatorName(icmp_->user_comparator()->Name());
      edit.SetLogNumber(0);
      edit.SetNextFile(2);
      edit.SetLastSequence(0);
      edit.EncodeTo(&record);
      EXPECT_TRUE(writer.AddRecord(record).ok());
    }
    delete file;
    EXPECT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());

    EXPECT_TRUE(vset_->Recover(&save_manifest).ok());
    return vset_->current();
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  Cache* cache_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* vset_;
};

// Test OverlapInLevel with no files at any level
TEST_F(VersionSetTest_153, OverlapInLevel_NoFiles_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  Slice smallest("a");
  Slice largest("z");
  // No files at level 0, should not overlap
  EXPECT_FALSE(v->OverlapInLevel(0, &smallest, &largest));
  // No files at level 1
  EXPECT_FALSE(v->OverlapInLevel(1, &smallest, &largest));
}

// Test OverlapInLevel with nullptr smallest and largest (entire range)
TEST_F(VersionSetTest_153, OverlapInLevel_NullRange_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  // With no files, even nullptr range should not overlap
  EXPECT_FALSE(v->OverlapInLevel(0, nullptr, nullptr));
  EXPECT_FALSE(v->OverlapInLevel(1, nullptr, nullptr));
}

// Test OverlapInLevel with nullptr smallest only
TEST_F(VersionSetTest_153, OverlapInLevel_NullSmallest_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  Slice largest("z");
  EXPECT_FALSE(v->OverlapInLevel(0, nullptr, &largest));
}

// Test OverlapInLevel with nullptr largest only
TEST_F(VersionSetTest_153, OverlapInLevel_NullLargest_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  Slice smallest("a");
  EXPECT_FALSE(v->OverlapInLevel(0, &smallest, nullptr));
}

// Test OverlapInLevel after adding files via LogAndApply
TEST_F(VersionSetTest_153, OverlapInLevel_WithFiles_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  // Add a file to level 1
  VersionEdit edit;
  InternalKey smallest_key("b", 1, kTypeValue);
  InternalKey largest_key("d", 2, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 100, smallest_key, largest_key);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Version* new_v = vset_->current();
  ASSERT_NE(new_v, nullptr);

  // Range that overlaps with file [b, d]
  Slice s1("a");
  Slice s2("c");
  EXPECT_TRUE(new_v->OverlapInLevel(1, &s1, &s2));

  // Range that doesn't overlap
  Slice s3("e");
  Slice s4("f");
  EXPECT_FALSE(new_v->OverlapInLevel(1, &s3, &s4));

  // Range completely containing the file
  Slice s5("a");
  Slice s6("z");
  EXPECT_TRUE(new_v->OverlapInLevel(1, &s5, &s6));

  // Range before the file
  Slice s7("0");
  Slice s8("a");
  EXPECT_FALSE(new_v->OverlapInLevel(1, &s7, &s8));
}

// Test OverlapInLevel at level 0 (different behavior - all files checked)
TEST_F(VersionSetTest_153, OverlapInLevel_Level0_WithFiles_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  // Add a file to level 0
  VersionEdit edit;
  InternalKey smallest_key("b", 1, kTypeValue);
  InternalKey largest_key("d", 2, kTypeValue);
  edit.AddFile(0, vset_->NewFileNumber(), 100, smallest_key, largest_key);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Version* new_v = vset_->current();

  // Range overlapping
  Slice s1("c");
  Slice s2("e");
  EXPECT_TRUE(new_v->OverlapInLevel(0, &s1, &s2));

  // Range not overlapping
  Slice s3("e");
  Slice s4("f");
  EXPECT_FALSE(new_v->OverlapInLevel(0, &s3, &s4));
}

// Test PickLevelForMemTableOutput with empty version
TEST_F(VersionSetTest_153, PickLevelForMemTableOutput_Empty_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  Slice smallest("a");
  Slice largest("z");
  int level = v->PickLevelForMemTableOutput(smallest, largest);
  // With no files, it should be able to push to a deeper level
  EXPECT_GE(level, 0);
}

// Test NumFiles on empty version
TEST_F(VersionSetTest_153, NumFiles_Empty_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(0, v->NumFiles(i));
  }
}

// Test NumFiles after adding files
TEST_F(VersionSetTest_153, NumFiles_AfterAdd_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  VersionEdit edit;
  InternalKey sk("a", 1, kTypeValue);
  InternalKey lk("b", 2, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 100, sk, lk);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Version* new_v = vset_->current();
  EXPECT_EQ(1, new_v->NumFiles(1));
  EXPECT_EQ(0, new_v->NumFiles(0));
  EXPECT_EQ(0, new_v->NumFiles(2));
}

// Test VersionSet basic accessors
TEST_F(VersionSetTest_153, VersionSet_BasicAccessors_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  EXPECT_EQ(v, vset_->current());
  EXPECT_EQ(0u, vset_->LastSequence());
  vset_->SetLastSequence(100);
  EXPECT_EQ(100u, vset_->LastSequence());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_153, VersionSet_NewFileNumber_153) {
  BuildVersionWithFiles();

  uint64_t fn1 = vset_->NewFileNumber();
  uint64_t fn2 = vset_->NewFileNumber();
  EXPECT_LT(fn1, fn2);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_153, VersionSet_ReuseFileNumber_153) {
  BuildVersionWithFiles();

  uint64_t fn1 = vset_->NewFileNumber();
  vset_->ReuseFileNumber(fn1);
  uint64_t fn2 = vset_->NewFileNumber();
  EXPECT_EQ(fn1, fn2);
}

// Test NumLevelFiles
TEST_F(VersionSetTest_153, VersionSet_NumLevelFiles_153) {
  BuildVersionWithFiles();

  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(0, vset_->NumLevelFiles(i));
  }
}

// Test AddLiveFiles on empty version set
TEST_F(VersionSetTest_153, VersionSet_AddLiveFiles_Empty_153) {
  BuildVersionWithFiles();

  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test AddLiveFiles after adding files
TEST_F(VersionSetTest_153, VersionSet_AddLiveFiles_WithFiles_153) {
  BuildVersionWithFiles();

  VersionEdit edit;
  uint64_t file_num = vset_->NewFileNumber();
  InternalKey sk("a", 1, kTypeValue);
  InternalKey lk("b", 2, kTypeValue);
  edit.AddFile(1, file_num, 100, sk, lk);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.count(file_num) > 0);
}

// Test GetOverlappingInputs with no files
TEST_F(VersionSetTest_153, GetOverlappingInputs_Empty_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  InternalKey begin("a", 1, kTypeValue);
  InternalKey end("z", 1, kTypeValue);
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
}

// Test GetOverlappingInputs with matching files
TEST_F(VersionSetTest_153, GetOverlappingInputs_WithMatch_153) {
  BuildVersionWithFiles();

  VersionEdit edit;
  uint64_t fn = vset_->NewFileNumber();
  InternalKey sk("b", 1, kTypeValue);
  InternalKey lk("d", 2, kTypeValue);
  edit.AddFile(1, fn, 100, sk, lk);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  Version* v = vset_->current();
  InternalKey begin("a", 1, kTypeValue);
  InternalKey end("c", 1, kTypeValue);
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_EQ(1u, inputs.size());
}

// Test GetOverlappingInputs with no match
TEST_F(VersionSetTest_153, GetOverlappingInputs_NoMatch_153) {
  BuildVersionWithFiles();

  VersionEdit edit;
  uint64_t fn = vset_->NewFileNumber();
  InternalKey sk("b", 1, kTypeValue);
  InternalKey lk("d", 2, kTypeValue);
  edit.AddFile(1, fn, 100, sk, lk);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  Version* v = vset_->current();
  InternalKey begin("e", 1, kTypeValue);
  InternalKey end("f", 1, kTypeValue);
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
}

// Test OverlapInLevel with exact boundary match
TEST_F(VersionSetTest_153, OverlapInLevel_ExactBoundary_153) {
  BuildVersionWithFiles();

  VersionEdit edit;
  InternalKey sk("b", 1, kTypeValue);
  InternalKey lk("d", 2, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 100, sk, lk);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  Version* v = vset_->current();

  // Exact boundary - smallest matches largest of file
  Slice s1("d");
  Slice s2("e");
  EXPECT_TRUE(v->OverlapInLevel(1, &s1, &s2));

  // Exact boundary - largest matches smallest of file
  Slice s3("a");
  Slice s4("b");
  EXPECT_TRUE(v->OverlapInLevel(1, &s3, &s4));
}

// Test OverlapInLevel with multiple files in a level
TEST_F(VersionSetTest_153, OverlapInLevel_MultipleFiles_153) {
  BuildVersionWithFiles();

  VersionEdit edit;
  InternalKey sk1("a", 1, kTypeValue);
  InternalKey lk1("c", 2, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 100, sk1, lk1);

  InternalKey sk2("e", 3, kTypeValue);
  InternalKey lk2("g", 4, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 100, sk2, lk2);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  Version* v = vset_->current();

  // Overlaps first file
  Slice s1("b");
  Slice s2("b");
  EXPECT_TRUE(v->OverlapInLevel(1, &s1, &s2));

  // Overlaps second file
  Slice s3("f");
  Slice s4("f");
  EXPECT_TRUE(v->OverlapInLevel(1, &s3, &s4));

  // Between files - no overlap
  Slice s5("d");
  Slice s6("d");
  EXPECT_FALSE(v->OverlapInLevel(1, &s5, &s6));

  // Spanning both files
  Slice s7("b");
  Slice s8("f");
  EXPECT_TRUE(v->OverlapInLevel(1, &s7, &s8));
}

// Test NumLevelBytes
TEST_F(VersionSetTest_153, VersionSet_NumLevelBytes_153) {
  BuildVersionWithFiles();

  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(0, vset_->NumLevelBytes(i));
  }

  VersionEdit edit;
  InternalKey sk("a", 1, kTypeValue);
  InternalKey lk("b", 2, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 12345, sk, lk);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  EXPECT_EQ(12345, vset_->NumLevelBytes(1));
  EXPECT_EQ(0, vset_->NumLevelBytes(0));
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_153, VersionSet_MarkFileNumberUsed_153) {
  BuildVersionWithFiles();

  vset_->MarkFileNumberUsed(1000);
  uint64_t fn = vset_->NewFileNumber();
  EXPECT_GT(fn, 1000u);
}

// Test Ref and Unref
TEST_F(VersionSetTest_153, Version_RefUnref_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  // The current version is already ref'd by VersionSet
  // Adding another ref should work
  v->Ref();
  // And unref should not destroy it since VersionSet still holds a ref
  v->Unref();
  // Version should still be valid (current)
  EXPECT_EQ(v, vset_->current());
}

// Test LevelSummary
TEST_F(VersionSetTest_153, VersionSet_LevelSummary_153) {
  BuildVersionWithFiles();

  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  ASSERT_NE(summary, nullptr);
  EXPECT_GT(strlen(summary), 0u);
}

// Test DebugString
TEST_F(VersionSetTest_153, Version_DebugString_153) {
  Version* v = BuildVersionWithFiles();
  ASSERT_NE(v, nullptr);

  std::string debug = v->DebugString();
  // Should produce some output
  EXPECT_FALSE(debug.empty());
}

// Test NeedsCompaction on empty version
TEST_F(VersionSetTest_153, VersionSet_NeedsCompaction_Empty_153) {
  BuildVersionWithFiles();
  // With no files and no compaction pressure, should not need compaction
  // (This depends on implementation, but typically true for empty)
  // We just verify it doesn't crash
  bool needs = vset_->NeedsCompaction();
  (void)needs;  // Just checking it doesn't crash
}

// Test SetLastSequence boundary
TEST_F(VersionSetTest_153, VersionSet_SetLastSequence_Boundary_153) {
  BuildVersionWithFiles();

  vset_->SetLastSequence(0);
  EXPECT_EQ(0u, vset_->LastSequence());

  vset_->SetLastSequence(UINT64_MAX);
  EXPECT_EQ(UINT64_MAX, vset_->LastSequence());
}

// Test LogAndApply with file deletion
TEST_F(VersionSetTest_153, VersionSet_LogAndApply_DeleteFile_153) {
  BuildVersionWithFiles();

  // First add a file
  VersionEdit edit1;
  uint64_t fn = vset_->NewFileNumber();
  InternalKey sk("a", 1, kTypeValue);
  InternalKey lk("b", 2, kTypeValue);
  edit1.AddFile(1, fn, 100, sk, lk);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit1, &mu).ok());
  mu.Unlock();

  EXPECT_EQ(1, vset_->NumLevelFiles(1));

  // Now delete it
  VersionEdit edit2;
  edit2.RemoveFile(1, fn);

  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit2, &mu).ok());
  mu.Unlock();

  EXPECT_EQ(0, vset_->NumLevelFiles(1));
}

// Test multiple levels with files
TEST_F(VersionSetTest_153, OverlapInLevel_DifferentLevels_153) {
  BuildVersionWithFiles();

  VersionEdit edit;
  InternalKey sk1("a", 1, kTypeValue);
  InternalKey lk1("c", 2, kTypeValue);
  edit.AddFile(1, vset_->NewFileNumber(), 100, sk1, lk1);

  InternalKey sk2("x", 3, kTypeValue);
  InternalKey lk2("z", 4, kTypeValue);
  edit.AddFile(2, vset_->NewFileNumber(), 100, sk2, lk2);

  port::Mutex mu;
  mu.Lock();
  ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  mu.Unlock();

  Version* v = vset_->current();

  // Check level 1 overlap
  Slice s1("b");
  Slice s2("b");
  EXPECT_TRUE(v->OverlapInLevel(1, &s1, &s2));
  EXPECT_FALSE(v->OverlapInLevel(2, &s1, &s2));

  // Check level 2 overlap
  Slice s3("y");
  Slice s4("y");
  EXPECT_FALSE(v->OverlapInLevel(1, &s3, &s4));
  EXPECT_TRUE(v->OverlapInLevel(2, &s3, &s4));
}

}  // namespace leveldb
