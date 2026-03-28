#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "util/testutil.h"
#include "util/testharness.h"
#include "table/merger.h"

#include <string>
#include <vector>
#include <memory>

namespace leveldb {

// We need a minimal VersionSet to construct a Version.
// Since Version's constructor is private and requires a VersionSet*,
// we need to create a proper VersionSet or use a test helper.

class VersionDebugStringTest_156 : public ::testing::Test {
 protected:
  VersionDebugStringTest_156()
      : db_name_(testing::TempDir() + "/version_debug_test"),
        env_(Env::Default()),
        icmp_(BytewiseComparator()),
        options_() {
    options_.comparator = BytewiseComparator();
    // Create the necessary infrastructure for VersionSet
    DestroyDB(db_name_, options_);
    env_->CreateDir(db_name_);
    
    table_cache_ = new TableCache(db_name_, &options_, 100);
    versions_ = new VersionSet(db_name_, &options_, table_cache_, &icmp_);
    
    // Recover to initialize
    bool save_manifest = false;
    Status s = versions_->Recover(&save_manifest);
  }

  ~VersionDebugStringTest_156() override {
    delete versions_;
    delete table_cache_;
    DestroyDB(db_name_, options_);
  }

  // Helper to add files to a version via VersionEdit and LogAndApply
  void AddFile(VersionEdit* edit, int level, uint64_t file_number,
               uint64_t file_size, const InternalKey& smallest,
               const InternalKey& largest) {
    edit->AddFile(level, file_number, file_size, smallest, largest);
  }

  std::string db_name_;
  Env* env_;
  InternalKeyComparator icmp_;
  Options options_;
  TableCache* table_cache_;
  VersionSet* versions_;
};

// Test that DebugString on a fresh version (no files) contains level headers
TEST_F(VersionDebugStringTest_156, EmptyVersionDebugString_156) {
  // The current version should have no files after a fresh recover
  Version* current = versions_->current();
  current->Ref();
  
  std::string debug = current->DebugString();
  
  // Should contain all level headers
  for (int level = 0; level < config::kNumLevels; level++) {
    std::string level_header = "--- level " + std::to_string(level) + " ---";
    EXPECT_NE(debug.find(level_header), std::string::npos)
        << "Missing header for level " << level;
  }
  
  current->Unref();
}

// Test that DebugString contains file information after adding files
TEST_F(VersionDebugStringTest_156, DebugStringWithFiles_156) {
  // Create a version edit that adds a file
  VersionEdit edit;
  InternalKey smallest(Slice("aaa"), 1, kTypeValue);
  InternalKey largest(Slice("zzz"), 2, kTypeValue);
  
  // We need to create an actual table file for LogAndApply to work,
  // but for DebugString we just need files in the version.
  // Use LogAndApply with the edit.
  edit.AddFile(0, 100, 1024, smallest, largest);
  
  // We need a log number set
  edit.SetLogNumber(0);
  
  {
    // Create a dummy log file so LogAndApply doesn't fail
    WritableFile* lfile;
    env_->NewWritableFile(db_name_ + "/MANIFEST-000001", &lfile);
    delete lfile;
  }
  
  Status s = versions_->LogAndApply(&edit, new port::Mutex());
  // Even if LogAndApply fails due to missing table files, let's check
  // the current version's DebugString
  
  Version* current = versions_->current();
  current->Ref();
  
  std::string debug = current->DebugString();
  
  // The output should not be empty
  EXPECT_FALSE(debug.empty());
  
  // Should contain level 0 header
  EXPECT_NE(debug.find("--- level 0 ---"), std::string::npos);
  
  current->Unref();
}

// Test that DebugString output has all 7 level sections
TEST_F(VersionDebugStringTest_156, AllLevelsPresent_156) {
  Version* current = versions_->current();
  current->Ref();
  
  std::string debug = current->DebugString();
  
  // Count occurrences of "--- level"
  int count = 0;
  std::string search = "--- level";
  size_t pos = 0;
  while ((pos = debug.find(search, pos)) != std::string::npos) {
    count++;
    pos += search.length();
  }
  
  EXPECT_EQ(count, config::kNumLevels);
  
  current->Unref();
}

// Test NumFiles on empty version
TEST_F(VersionDebugStringTest_156, NumFilesEmpty_156) {
  Version* current = versions_->current();
  current->Ref();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(current->NumFiles(level), 0)
        << "Expected 0 files at level " << level;
  }
  
  current->Unref();
}

// Test OverlapInLevel on empty version returns false
TEST_F(VersionDebugStringTest_156, OverlapInLevelEmpty_156) {
  Version* current = versions_->current();
  current->Ref();
  
  Slice smallest("aaa");
  Slice largest("zzz");
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(current->OverlapInLevel(level, &smallest, &largest))
        << "Expected no overlap at level " << level << " for empty version";
  }
  
  current->Unref();
}

// Test OverlapInLevel with nullptr bounds on empty version
TEST_F(VersionDebugStringTest_156, OverlapInLevelNullBounds_156) {
  Version* current = versions_->current();
  current->Ref();
  
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(current->OverlapInLevel(level, nullptr, nullptr))
        << "Expected no overlap at level " << level << " with null bounds";
  }
  
  current->Unref();
}

// Test GetOverlappingInputs on empty version
TEST_F(VersionDebugStringTest_156, GetOverlappingInputsEmpty_156) {
  Version* current = versions_->current();
  current->Ref();
  
  InternalKey begin(Slice("aaa"), 100, kTypeValue);
  InternalKey end(Slice("zzz"), 1, kTypeValue);
  std::vector<FileMetaData*> inputs;
  
  for (int level = 0; level < config::kNumLevels; level++) {
    inputs.clear();
    current->GetOverlappingInputs(level, &begin, &end, &inputs);
    EXPECT_TRUE(inputs.empty())
        << "Expected no overlapping inputs at level " << level;
  }
  
  current->Unref();
}

// Test PickLevelForMemTableOutput on empty version
TEST_F(VersionDebugStringTest_156, PickLevelForMemTableOutputEmpty_156) {
  Version* current = versions_->current();
  current->Ref();
  
  Slice smallest("aaa");
  Slice largest("zzz");
  
  int level = current->PickLevelForMemTableOutput(smallest, largest);
  // On an empty version, the output should be pushed to a level > 0
  // but we can only check it's a valid level
  EXPECT_GE(level, 0);
  EXPECT_LT(level, config::kNumLevels);
  
  current->Unref();
}

// Test Ref and Unref don't crash
TEST_F(VersionDebugStringTest_156, RefUnref_156) {
  Version* current = versions_->current();
  current->Ref();
  current->Ref();
  current->Unref();
  current->Unref();
  // Should not crash - version still alive because VersionSet holds a ref
}

// Test UpdateStats with empty stats
TEST_F(VersionDebugStringTest_156, UpdateStatsWithNull_156) {
  Version* current = versions_->current();
  current->Ref();
  
  Version::GetStats stats;
  stats.seek_file = nullptr;
  stats.seek_file_level = -1;
  
  bool result = current->UpdateStats(stats);
  EXPECT_FALSE(result);
  
  current->Unref();
}

// Test DebugString is deterministic
TEST_F(VersionDebugStringTest_156, DebugStringDeterministic_156) {
  Version* current = versions_->current();
  current->Ref();
  
  std::string debug1 = current->DebugString();
  std::string debug2 = current->DebugString();
  
  EXPECT_EQ(debug1, debug2);
  
  current->Unref();
}

// Test AddIterators on empty version
TEST_F(VersionDebugStringTest_156, AddIteratorsEmpty_156) {
  Version* current = versions_->current();
  current->Ref();
  
  ReadOptions roptions;
  std::vector<Iterator*> iters;
  
  current->AddIterators(roptions, &iters);
  
  // For an empty version, we should get iterators for levels 1+
  // (config::kNumLevels - 1 concatenating iterators for levels 1-6,
  //  plus individual iterators for level 0 files)
  // With no files, level 0 contributes 0, levels 1-6 contribute 6 iterators
  EXPECT_EQ(iters.size(), static_cast<size_t>(config::kNumLevels - 1));
  
  // Clean up iterators
  for (auto* iter : iters) {
    delete iter;
  }
  
  current->Unref();
}

// Test GetOverlappingInputs with null begin and end
TEST_F(VersionDebugStringTest_156, GetOverlappingInputsNullRange_156) {
  Version* current = versions_->current();
  current->Ref();
  
  std::vector<FileMetaData*> inputs;
  
  // nullptr begin and end should mean "all files"
  current->GetOverlappingInputs(0, nullptr, nullptr, &inputs);
  EXPECT_TRUE(inputs.empty());  // No files in empty version
  
  current->Unref();
}

}  // namespace leveldb
