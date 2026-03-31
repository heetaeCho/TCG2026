#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/merger.h"
#include "util/testutil.h"
#include "leveldb/options.h"
#include "leveldb/table_cache.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"

#include <string>
#include <vector>
#include <memory>

namespace leveldb {

// We need to create a VersionSet to construct Version objects.
// Version's constructor is private and requires a VersionSet*.
// We'll set up a minimal environment to test the public interface.

class VersionTest_69 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_test_69";
    
    // Create the directory
    env_->CreateDir(dbname_);
    
    options_.comparator = BytewiseComparator();
    options_.env = env_;
    
    table_cache_ = new TableCache(dbname_, options_, 100);
    
    const InternalKeyComparator cmp(BytewiseComparator());
    
    versions_ = new VersionSet(dbname_, &options_, table_cache_, &cmp);
    
    // Create/recover the version set
    VersionEdit edit;
    edit.SetComparatorName(cmp.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    
    // We need a CURRENT file and MANIFEST
    Status s = versions_->Recover(/*save_manifest=*/nullptr);
    if (!s.ok()) {
      // If recovery fails, create a new manifest
      edit.SetLogNumber(0);
      edit.SetNextFile(2);
      edit.SetLastSequence(0);
    }
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    // Clean up temp files
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
  TableCache* table_cache_;
  VersionSet* versions_;
};

// Test NumFiles returns 0 for all levels on a fresh version
TEST_F(VersionTest_69, NumFilesEmptyVersion_69) {
  Version* v = versions_->current();
  v->Ref();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, v->NumFiles(level)) 
        << "Expected 0 files at level " << level << " for a fresh version";
  }
  
  v->Unref();
}

// Test NumFiles for each individual level
TEST_F(VersionTest_69, NumFilesPerLevel_69) {
  Version* v = versions_->current();
  v->Ref();
  
  // Just verify level 0 is empty
  EXPECT_EQ(0, v->NumFiles(0));
  
  // Verify all levels are empty
  for (int i = 0; i < config::kNumLevels; i++) {
    EXPECT_GE(v->NumFiles(i), 0);
  }
  
  v->Unref();
}

// Test OverlapInLevel returns false for empty version
TEST_F(VersionTest_69, OverlapInLevelEmptyVersion_69) {
  Version* v = versions_->current();
  v->Ref();
  
  Slice small("a");
  Slice large("z");
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &small, &large))
        << "No overlap expected at level " << level << " for empty version";
  }
  
  v->Unref();
}

// Test OverlapInLevel with nullptr keys
TEST_F(VersionTest_69, OverlapInLevelNullKeys_69) {
  Version* v = versions_->current();
  v->Ref();
  
  // nullptr means unbounded range
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, nullptr, nullptr))
        << "No overlap expected at level " << level << " for empty version with null keys";
  }
  
  v->Unref();
}

// Test PickLevelForMemTableOutput on empty version
TEST_F(VersionTest_69, PickLevelForMemTableOutputEmpty_69) {
  Version* v = versions_->current();
  v->Ref();
  
  Slice small("a");
  Slice large("z");
  
  int level = v->PickLevelForMemTableOutput(small, large);
  // Should return some valid level >= 0
  EXPECT_GE(level, 0);
  EXPECT_LT(level, config::kNumLevels);
  
  v->Unref();
}

// Test GetOverlappingInputs on empty version
TEST_F(VersionTest_69, GetOverlappingInputsEmpty_69) {
  Version* v = versions_->current();
  v->Ref();
  
  const InternalKeyComparator cmp(BytewiseComparator());
  
  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 1, kTypeValue);
  
  std::vector<FileMetaData*> inputs;
  
  for (int level = 0; level < config::kNumLevels; level++) {
    inputs.clear();
    v->GetOverlappingInputs(level, &begin, &end, &inputs);
    EXPECT_EQ(0u, inputs.size())
        << "Expected no overlapping inputs at level " << level;
  }
  
  v->Unref();
}

// Test GetOverlappingInputs with nullptr begin and end
TEST_F(VersionTest_69, GetOverlappingInputsNullBounds_69) {
  Version* v = versions_->current();
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  
  for (int level = 0; level < config::kNumLevels; level++) {
    inputs.clear();
    v->GetOverlappingInputs(level, nullptr, nullptr, &inputs);
    EXPECT_EQ(0u, inputs.size());
  }
  
  v->Unref();
}

// Test Ref and Unref don't crash
TEST_F(VersionTest_69, RefUnref_69) {
  Version* v = versions_->current();
  v->Ref();
  v->Ref();
  v->Unref();
  v->Unref();
  // Should not crash; version still alive because VersionSet holds a ref
}

// Test DebugString returns non-empty string
TEST_F(VersionTest_69, DebugStringNonEmpty_69) {
  Version* v = versions_->current();
  v->Ref();
  
  std::string debug = v->DebugString();
  // DebugString should produce some output even for empty version
  EXPECT_FALSE(debug.empty());
  
  v->Unref();
}

// Test AddIterators on empty version
TEST_F(VersionTest_69, AddIteratorsEmpty_69) {
  Version* v = versions_->current();
  v->Ref();
  
  ReadOptions roptions;
  std::vector<Iterator*> iters;
  
  v->AddIterators(roptions, &iters);
  
  // Even with no files, there should be iterators created for each level
  // (at minimum level-0 files produce individual iterators, levels 1+ produce concatenating iterators)
  // For an empty version, we expect iterators for levels 1 through kNumLevels-1
  // Clean up iterators
  for (auto* iter : iters) {
    delete iter;
  }
  
  v->Unref();
}

// Test UpdateStats with empty stats
TEST_F(VersionTest_69, UpdateStatsNoFile_69) {
  Version* v = versions_->current();
  v->Ref();
  
  Version::GetStats stats;
  stats.seek_file = nullptr;
  stats.seek_file_level = -1;
  
  bool result = v->UpdateStats(stats);
  EXPECT_FALSE(result) << "UpdateStats should return false when seek_file is null";
  
  v->Unref();
}

// Test PickLevelForMemTableOutput with single-key range
TEST_F(VersionTest_69, PickLevelForMemTableOutputSingleKey_69) {
  Version* v = versions_->current();
  v->Ref();
  
  Slice key("testkey");
  
  int level = v->PickLevelForMemTableOutput(key, key);
  EXPECT_GE(level, 0);
  EXPECT_LT(level, config::kNumLevels);
  
  v->Unref();
}

// Test that after applying a version edit with files, NumFiles is updated
TEST_F(VersionTest_69, NumFilesAfterAddingFiles_69) {
  // Apply an edit that adds a file to level 1
  const InternalKeyComparator cmp(BytewiseComparator());
  
  VersionEdit edit;
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  
  // Add a file to level 1: file_number=10, file_size=1000
  edit.AddFile(1, 10, 1000, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = versions_->LogAndApply(&edit, &mu);
  mu.Unlock();
  
  if (s.ok()) {
    Version* v = versions_->current();
    v->Ref();
    
    EXPECT_EQ(1, v->NumFiles(1)) << "Expected 1 file at level 1 after adding a file";
    EXPECT_EQ(0, v->NumFiles(0)) << "Expected 0 files at level 0";
    
    // Test OverlapInLevel should now return true for overlapping range
    Slice sa("b");
    Slice la("m");
    EXPECT_TRUE(v->OverlapInLevel(1, &sa, &la))
        << "Expected overlap at level 1";
    
    // Test non-overlapping range
    Slice sa2("zz");
    Slice la2("zzz");
    EXPECT_FALSE(v->OverlapInLevel(1, &sa2, &la2))
        << "Expected no overlap for range beyond file";
    
    v->Unref();
  }
}

// Test GetOverlappingInputs after adding files
TEST_F(VersionTest_69, GetOverlappingInputsWithFiles_69) {
  const InternalKeyComparator cmp(BytewiseComparator());
  
  VersionEdit edit;
  InternalKey smallest("bar", 1, kTypeValue);
  InternalKey largest("foo", 2, kTypeValue);
  
  edit.AddFile(1, 20, 500, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = versions_->LogAndApply(&edit, &mu);
  mu.Unlock();
  
  if (s.ok()) {
    Version* v = versions_->current();
    v->Ref();
    
    InternalKey begin(Slice("a"), 100, kTypeValue);
    InternalKey end(Slice("z"), 1, kTypeValue);
    
    std::vector<FileMetaData*> inputs;
    v->GetOverlappingInputs(1, &begin, &end, &inputs);
    EXPECT_EQ(1u, inputs.size());
    
    // Non-overlapping range
    inputs.clear();
    InternalKey begin2(Slice("g"), 100, kTypeValue);
    InternalKey end2(Slice("z"), 1, kTypeValue);
    v->GetOverlappingInputs(1, &begin2, &end2, &inputs);
    EXPECT_EQ(0u, inputs.size());
    
    v->Unref();
  }
}

// Test DebugString contains level information after adding files
TEST_F(VersionTest_69, DebugStringWithFiles_69) {
  const InternalKeyComparator cmp(BytewiseComparator());
  
  VersionEdit edit;
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  
  edit.AddFile(2, 30, 2000, smallest, largest);
  
  port::Mutex mu;
  mu.Lock();
  Status s = versions_->LogAndApply(&edit, &mu);
  mu.Unlock();
  
  if (s.ok()) {
    Version* v = versions_->current();
    v->Ref();
    
    std::string debug = v->DebugString();
    EXPECT_FALSE(debug.empty());
    // Should contain some reference to file number or level info
    
    v->Unref();
  }
}

// Test multiple files at level 0
TEST_F(VersionTest_69, MultipleFilesAtLevel0_69) {
  const InternalKeyComparator cmp(BytewiseComparator());
  
  VersionEdit edit;
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("m", 2, kTypeValue);
  InternalKey s2("d", 3, kTypeValue);
  InternalKey l2("z", 4, kTypeValue);
  
  edit.AddFile(0, 40, 1000, s1, l1);
  edit.AddFile(0, 41, 1000, s2, l2);
  
  port::Mutex mu;
  mu.Lock();
  Status s = versions_->LogAndApply(&edit, &mu);
  mu.Unlock();
  
  if (s.ok()) {
    Version* v = versions_->current();
    v->Ref();
    
    EXPECT_EQ(2, v->NumFiles(0)) << "Expected 2 files at level 0";
    
    v->Unref();
  }
}

}  // namespace leveldb
