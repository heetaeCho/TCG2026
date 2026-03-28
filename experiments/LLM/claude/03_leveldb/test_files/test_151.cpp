#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"
#include "leveldb/table_cache.h"
#include "table/merger.h"
#include "util/logging.h"
#include "util/testutil.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <vector>
#include <memory>

namespace leveldb {

// We need access to Version through VersionSet since Version's constructor is private.
// We'll create a minimal setup to get a Version object.

class VersionTest_151 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/version_test_151";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    const int table_cache_size = 100;
    table_cache_ = new TableCache(dbname_, options_, table_cache_size);

    InternalKeyComparator icmp(options_.comparator);
    versions_ = new VersionSet(dbname_, &options_, table_cache_, &icmp);

    Status s = versions_->Recover(nullptr);
    // If recovery fails due to missing CURRENT, we create the necessary files
    if (!s.ok()) {
      // Create initial version set
      VersionEdit edit;
      edit.SetComparatorName(options_.comparator->Name());
      edit.SetLogNumber(0);
      edit.SetNextFile(2);
      edit.SetLastSequence(0);
      s = versions_->LogAndApply(&edit, &mu_);
    }
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    // Cleanup
    std::vector<std::string> filenames;
    env_->GetChildren(dbname_, &filenames);
    for (const auto& f : filenames) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  Version* current() { return versions_->current(); }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  VersionSet* versions_;
  port::Mutex mu_;
};

TEST_F(VersionTest_151, RefIncreasesReferenceCount_151) {
  // Ref should not crash and should be callable multiple times
  Version* v = current();
  // current() already has ref count managed by VersionSet
  // We can call Ref and then Unref without crashing
  v->Ref();
  v->Unref();
}

TEST_F(VersionTest_151, MultipleRefUnref_151) {
  Version* v = current();
  v->Ref();
  v->Ref();
  v->Unref();
  v->Unref();
  // Should not crash - balanced ref/unref
}

TEST_F(VersionTest_151, NumFilesInitiallyZero_151) {
  Version* v = current();
  for (int level = 0; level < 7; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
}

TEST_F(VersionTest_151, OverlapInLevelEmptyVersion_151) {
  Version* v = current();
  Slice small("a");
  Slice large("z");
  // No files at any level, so no overlap expected
  for (int level = 0; level < 7; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &small, &large));
  }
}

TEST_F(VersionTest_151, OverlapInLevelWithNullKeys_151) {
  Version* v = current();
  // nullptr means unbounded range
  for (int level = 0; level < 7; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, nullptr, nullptr));
  }
}

TEST_F(VersionTest_151, PickLevelForMemTableOutputEmptyVersion_151) {
  Version* v = current();
  Slice small("a");
  Slice large("z");
  int level = v->PickLevelForMemTableOutput(small, large);
  // With empty version, should return some valid level >= 0
  EXPECT_GE(level, 0);
  EXPECT_LT(level, 7);
}

TEST_F(VersionTest_151, GetOverlappingInputsEmpty_151) {
  Version* v = current();
  std::vector<FileMetaData*> inputs;
  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 0, kTypeValue);
  
  for (int level = 0; level < 7; level++) {
    inputs.clear();
    v->GetOverlappingInputs(level, &begin, &end, &inputs);
    EXPECT_TRUE(inputs.empty());
  }
}

TEST_F(VersionTest_151, GetOverlappingInputsNullBounds_151) {
  Version* v = current();
  std::vector<FileMetaData*> inputs;
  // nullptr begin/end should work (means unbounded)
  for (int level = 0; level < 7; level++) {
    inputs.clear();
    v->GetOverlappingInputs(level, nullptr, nullptr, &inputs);
    EXPECT_TRUE(inputs.empty());
  }
}

TEST_F(VersionTest_151, DebugStringNotEmpty_151) {
  Version* v = current();
  std::string debug = v->DebugString();
  // DebugString should return some non-empty string with level info
  EXPECT_FALSE(debug.empty());
}

TEST_F(VersionTest_151, DebugStringContainsLevelInfo_151) {
  Version* v = current();
  std::string debug = v->DebugString();
  // Should contain at least some level markers
  // Typically the debug string contains "--- level X ---" style markers
  EXPECT_NE(std::string::npos, debug.find("level"));
}

TEST_F(VersionTest_151, UpdateStatsWithEmptyStats_151) {
  Version* v = current();
  Version::GetStats stats;
  stats.seek_file = nullptr;
  stats.seek_file_level = -1;
  // With null seek_file, UpdateStats should return false (no compaction needed)
  EXPECT_FALSE(v->UpdateStats(stats));
}

TEST_F(VersionTest_151, AddIteratorsOnEmptyVersion_151) {
  Version* v = current();
  ReadOptions roptions;
  std::vector<Iterator*> iters;
  v->AddIterators(roptions, &iters);
  // Even empty version may add iterators (one per level for levels > 0)
  // Clean up iterators
  for (auto* it : iters) {
    delete it;
  }
}

TEST_F(VersionTest_151, PickLevelSmallRange_151) {
  Version* v = current();
  Slice small("abc");
  Slice large("abd");
  int level = v->PickLevelForMemTableOutput(small, large);
  EXPECT_GE(level, 0);
  EXPECT_LT(level, 7);
}

TEST_F(VersionTest_151, PickLevelSingleKeyRange_151) {
  Version* v = current();
  Slice key("testkey");
  int level = v->PickLevelForMemTableOutput(key, key);
  EXPECT_GE(level, 0);
  EXPECT_LT(level, 7);
}

TEST_F(VersionTest_151, VersionWithFilesAfterEdit_151) {
  // Add a file via VersionEdit and check NumFiles
  mu_.Lock();
  VersionEdit edit;
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(1, 10, 1000, smallest, largest);
  Status s = versions_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  
  ASSERT_TRUE(s.ok());
  
  Version* v = current();
  EXPECT_EQ(1, v->NumFiles(1));
  EXPECT_EQ(0, v->NumFiles(0));
  EXPECT_EQ(0, v->NumFiles(2));
}

TEST_F(VersionTest_151, OverlapInLevelWithFile_151) {
  mu_.Lock();
  VersionEdit edit;
  InternalKey smallest("c", 1, kTypeValue);
  InternalKey largest("m", 2, kTypeValue);
  edit.AddFile(1, 11, 500, smallest, largest);
  Status s = versions_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  
  ASSERT_TRUE(s.ok());
  
  Version* v = current();
  
  // Overlapping range
  Slice small_key("a");
  Slice large_key("d");
  EXPECT_TRUE(v->OverlapInLevel(1, &small_key, &large_key));
  
  // Non-overlapping range (entirely before)
  Slice before_small("a");
  Slice before_large("b");
  EXPECT_FALSE(v->OverlapInLevel(1, &before_small, &before_large));
  
  // Non-overlapping range (entirely after)
  Slice after_small("n");
  Slice after_large("z");
  EXPECT_FALSE(v->OverlapInLevel(1, &after_small, &after_large));
}

TEST_F(VersionTest_151, GetOverlappingInputsWithFile_151) {
  mu_.Lock();
  VersionEdit edit;
  InternalKey smallest("c", 1, kTypeValue);
  InternalKey largest("m", 2, kTypeValue);
  edit.AddFile(1, 12, 500, smallest, largest);
  Status s = versions_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  
  ASSERT_TRUE(s.ok());
  
  Version* v = current();
  std::vector<FileMetaData*> inputs;
  
  // Overlapping range should find the file
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("d", 0, kTypeValue);
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_EQ(1u, inputs.size());
  
  // Non-overlapping range
  inputs.clear();
  InternalKey begin2("n", 100, kTypeValue);
  InternalKey end2("z", 0, kTypeValue);
  v->GetOverlappingInputs(1, &begin2, &end2, &inputs);
  EXPECT_EQ(0u, inputs.size());
}

TEST_F(VersionTest_151, RecordReadSampleOnEmptyVersion_151) {
  Version* v = current();
  // Create a valid internal key
  InternalKey ikey("testkey", 100, kTypeValue);
  Slice encoded = ikey.Encode();
  // On empty version, should return false (no compaction triggered)
  EXPECT_FALSE(v->RecordReadSample(encoded));
}

TEST_F(VersionTest_151, DebugStringAfterAddingFiles_151) {
  mu_.Lock();
  VersionEdit edit;
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, 13, 1000, smallest, largest);
  Status s = versions_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  
  ASSERT_TRUE(s.ok());
  
  Version* v = current();
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

TEST_F(VersionTest_151, MultipleFilesInSameLevel_151) {
  mu_.Lock();
  VersionEdit edit;
  // Add two non-overlapping files to level 1
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("c", 2, kTypeValue);
  edit.AddFile(1, 14, 500, s1, l1);
  
  InternalKey s2("d", 3, kTypeValue);
  InternalKey l2("f", 4, kTypeValue);
  edit.AddFile(1, 15, 500, s2, l2);
  
  Status s = versions_->LogAndApply(&edit, &mu_);
  mu_.Unlock();
  
  ASSERT_TRUE(s.ok());
  
  Version* v = current();
  EXPECT_EQ(2, v->NumFiles(1));
  
  // Query range that spans both files
  std::vector<FileMetaData*> inputs;
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("f", 0, kTypeValue);
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_EQ(2u, inputs.size());
  
  // Query range that spans only first file
  inputs.clear();
  InternalKey begin2("a", 100, kTypeValue);
  InternalKey end2("b", 0, kTypeValue);
  v->GetOverlappingInputs(1, &begin2, &end2, &inputs);
  EXPECT_EQ(1u, inputs.size());
}

}  // namespace leveldb
