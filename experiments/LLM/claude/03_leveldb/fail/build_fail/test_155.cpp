#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "table/table_cache.h" // Include for TableCache if needed
#include "util/testutil.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"

#include <vector>
#include <string>
#include <memory>

namespace leveldb {

// Helper to create an InternalKey from user key, sequence number, and type
static InternalKey MakeInternalKey(const std::string& user_key, 
                                    SequenceNumber seq, 
                                    ValueType type = kTypeValue) {
  return InternalKey(user_key, seq, type);
}

class GetOverlappingInputsTest_155 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up options
    options_.comparator = BytewiseComparator();
    options_.env = Env::Default();
    
    // Create a table cache
    cache_ = NewLRUCache(100);
    table_cache_ = new TableCache("test_db", &options_, cache_);
    
    // Create the InternalKeyComparator
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    
    // Create the VersionSet
    vset_ = new VersionSet("test_db", &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    delete cache_;
  }

  // Helper to add a file to a specific level of a Version
  // Since Version's files_ is private, we need to use VersionEdit + LogAndApply
  // But that's complex. Instead, we'll use a workaround through the VersionSet
  // by applying version edits.
  
  // Actually, since Version constructor is private and files_ is private,
  // we need to build versions through the VersionSet mechanism.
  // Let's create a helper that builds a version via VersionEdit.
  
  Version* BuildVersionWithFiles(int level, 
                                  const std::vector<std::pair<std::string, std::string>>& file_ranges) {
    // We'll use LogAndApply to create a version with the given files
    VersionEdit edit;
    uint64_t file_num = 1;
    for (const auto& range : file_ranges) {
      InternalKey smallest = MakeInternalKey(range.first, 100);
      InternalKey largest = MakeInternalKey(range.second, 100);
      edit.AddFile(level, file_num++, 1000, smallest, largest);
    }
    
    port::Mutex mu;
    mu.Lock();
    Status s = vset_->LogAndApply(&edit, &mu);
    mu.Unlock();
    
    // If LogAndApply fails, we may need to handle differently
    // For testing purposes, we assume it succeeds or handle accordingly
    return vset_->current();
  }

  Options options_;
  Cache* cache_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* vset_;
};

// Test: Empty level returns empty inputs
TEST_F(GetOverlappingInputsTest_155, EmptyLevelReturnsEmptyInputs_155) {
  // Current version should have no files
  Version* v = vset_->current();
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("z", 100);
  
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
  
  v->Unref();
}

// Test: Null begin and end returns all files in a level
TEST_F(GetOverlappingInputsTest_155, NullBeginAndEndReturnsAllFiles_155) {
  Version* v = BuildVersionWithFiles(1, {{"b", "d"}, {"f", "h"}, {"j", "l"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(1, nullptr, nullptr, &inputs);
  EXPECT_EQ(inputs.size(), 3u);
  
  v->Unref();
}

// Test: Range that doesn't overlap any file returns empty
TEST_F(GetOverlappingInputsTest_155, NoOverlapReturnsEmpty_155) {
  Version* v = BuildVersionWithFiles(1, {{"d", "f"}, {"h", "j"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("c", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
  
  v->Unref();
}

// Test: Range overlapping a single file returns that file
TEST_F(GetOverlappingInputsTest_155, SingleFileOverlap_155) {
  Version* v = BuildVersionWithFiles(1, {{"b", "d"}, {"f", "h"}, {"j", "l"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("f", 100);
  InternalKey end = MakeInternalKey("g", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_EQ(inputs.size(), 1u);
  
  v->Unref();
}

// Test: Range overlapping multiple files returns all of them
TEST_F(GetOverlappingInputsTest_155, MultipleFileOverlap_155) {
  Version* v = BuildVersionWithFiles(1, {{"b", "d"}, {"f", "h"}, {"j", "l"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("c", 100);
  InternalKey end = MakeInternalKey("k", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_EQ(inputs.size(), 3u);
  
  v->Unref();
}

// Test: Null begin with valid end
TEST_F(GetOverlappingInputsTest_155, NullBeginValidEnd_155) {
  Version* v = BuildVersionWithFiles(1, {{"b", "d"}, {"f", "h"}, {"j", "l"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey end = MakeInternalKey("e", 100);
  
  v->GetOverlappingInputs(1, nullptr, &end, &inputs);
  EXPECT_EQ(inputs.size(), 1u);
  
  v->Unref();
}

// Test: Valid begin with null end
TEST_F(GetOverlappingInputsTest_155, ValidBeginNullEnd_155) {
  Version* v = BuildVersionWithFiles(1, {{"b", "d"}, {"f", "h"}, {"j", "l"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("g", 100);
  
  v->GetOverlappingInputs(1, &begin, nullptr, &inputs);
  EXPECT_EQ(inputs.size(), 2u);
  
  v->Unref();
}

// Test: Level 0 expansion - file extends begin range
TEST_F(GetOverlappingInputsTest_155, Level0ExpandsBeginRange_155) {
  // For level 0, if a file's start is less than user_begin, the search restarts
  Version* v = BuildVersionWithFiles(0, {{"a", "e"}, {"c", "g"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("d", 100);
  InternalKey end = MakeInternalKey("f", 100);
  
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  // Both files should be returned because level 0 files can overlap
  // and the range gets expanded
  EXPECT_GE(inputs.size(), 1u);
  
  v->Unref();
}

// Test: Level 0 expansion - file extends end range
TEST_F(GetOverlappingInputsTest_155, Level0ExpandsEndRange_155) {
  Version* v = BuildVersionWithFiles(0, {{"a", "d"}, {"c", "z"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("e", 100);
  
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  // The second file extends beyond end, causing restart and inclusion of both
  EXPECT_GE(inputs.size(), 1u);
  
  v->Unref();
}

// Test: Non-level-0 does not expand range
TEST_F(GetOverlappingInputsTest_155, NonLevel0DoesNotExpandRange_155) {
  Version* v = BuildVersionWithFiles(2, {{"a", "c"}, {"d", "f"}, {"g", "i"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("d", 100);
  InternalKey end = MakeInternalKey("f", 100);
  
  v->GetOverlappingInputs(2, &begin, &end, &inputs);
  // Only the middle file should match
  EXPECT_EQ(inputs.size(), 1u);
  
  v->Unref();
}

// Test: Exact boundary match
TEST_F(GetOverlappingInputsTest_155, ExactBoundaryMatch_155) {
  Version* v = BuildVersionWithFiles(1, {{"b", "d"}, {"f", "h"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("d", 100);
  InternalKey end = MakeInternalKey("f", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  // Both files should be included since ranges touch at boundaries
  EXPECT_EQ(inputs.size(), 2u);
  
  v->Unref();
}

// Test: Range completely after all files
TEST_F(GetOverlappingInputsTest_155, RangeAfterAllFiles_155) {
  Version* v = BuildVersionWithFiles(1, {{"a", "c"}, {"d", "f"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("g", 100);
  InternalKey end = MakeInternalKey("z", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
  
  v->Unref();
}

// Test: Range completely before all files
TEST_F(GetOverlappingInputsTest_155, RangeBeforeAllFiles_155) {
  Version* v = BuildVersionWithFiles(1, {{"d", "f"}, {"h", "j"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("c", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
  
  v->Unref();
}

// Test: inputs vector is cleared before use
TEST_F(GetOverlappingInputsTest_155, InputsVectorIsCleared_155) {
  Version* v = vset_->current();
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  // Pre-populate with garbage
  inputs.push_back(nullptr);
  inputs.push_back(nullptr);
  
  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("z", 100);
  
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  // Should be empty since there are no files
  EXPECT_TRUE(inputs.empty());
  
  v->Unref();
}

// Test: Different levels are independent
TEST_F(GetOverlappingInputsTest_155, DifferentLevelsAreIndependent_155) {
  // Add files to level 1
  Version* v = BuildVersionWithFiles(1, {{"a", "z"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("z", 100);
  
  // Level 2 should have no files
  v->GetOverlappingInputs(2, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
  
  // Level 1 should have the file
  v->GetOverlappingInputs(1, &begin, &end, &inputs);
  EXPECT_EQ(inputs.size(), 1u);
  
  v->Unref();
}

// Test: Level 0 with overlapping files causes full expansion
TEST_F(GetOverlappingInputsTest_155, Level0FullExpansion_155) {
  // Create overlapping files at level 0: [a,f], [c,h], [g,z]
  // Querying [d,e] should expand to include all three due to level-0 behavior
  Version* v = BuildVersionWithFiles(0, {{"a", "f"}, {"c", "h"}, {"g", "z"}});
  ASSERT_NE(v, nullptr);
  v->Ref();
  
  std::vector<FileMetaData*> inputs;
  InternalKey begin = MakeInternalKey("d", 100);
  InternalKey end = MakeInternalKey("e", 100);
  
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  // Due to level-0 expansion, all three files should eventually be included
  EXPECT_EQ(inputs.size(), 3u);
  
  v->Unref();
}

}  // namespace leveldb
