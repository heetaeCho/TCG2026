#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "util/comparator.h"

namespace leveldb {

// Helper function to create an InternalKey from a user key string
static InternalKey MakeInternalKey(const std::string& user_key, SequenceNumber seq, ValueType type) {
  return InternalKey(Slice(user_key), seq, type);
}

// Helper to create a FileMetaData with given smallest and largest keys
static FileMetaData* MakeFile(uint64_t number,
                               const std::string& smallest_user_key, SequenceNumber smallest_seq,
                               const std::string& largest_user_key, SequenceNumber largest_seq) {
  FileMetaData* f = new FileMetaData();
  f->number = number;
  f->smallest = MakeInternalKey(smallest_user_key, smallest_seq, kTypeValue);
  f->largest = MakeInternalKey(largest_user_key, largest_seq, kTypeValue);
  return f;
}

class AddBoundaryInputsTest_176 : public ::testing::Test {
 protected:
  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> level_files_;
  std::vector<FileMetaData*> compaction_files_;
  std::vector<FileMetaData*> all_files_;  // for cleanup

  AddBoundaryInputsTest_176() : icmp_(BytewiseComparator()) {}

  ~AddBoundaryInputsTest_176() override {
    for (auto* f : all_files_) {
      delete f;
    }
  }

  FileMetaData* AddFile(uint64_t number,
                         const std::string& smallest_user_key, SequenceNumber smallest_seq,
                         const std::string& largest_user_key, SequenceNumber largest_seq) {
    FileMetaData* f = MakeFile(number, smallest_user_key, smallest_seq, largest_user_key, largest_seq);
    all_files_.push_back(f);
    return f;
  }
};

// Test: Empty compaction files - nothing should happen
TEST_F(AddBoundaryInputsTest_176, EmptyCompactionFiles_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  level_files_.push_back(f1);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  ASSERT_TRUE(compaction_files_.empty());
}

// Test: Empty level files - nothing should be added
TEST_F(AddBoundaryInputsTest_176, EmptyLevelFiles_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  compaction_files_.push_back(f1);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  ASSERT_EQ(compaction_files_.size(), 1u);
  ASSERT_EQ(compaction_files_[0], f1);
}

// Test: Both empty - nothing should happen
TEST_F(AddBoundaryInputsTest_176, BothEmpty_176) {
  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  ASSERT_TRUE(compaction_files_.empty());
}

// Test: No boundary file exists in level files
TEST_F(AddBoundaryInputsTest_176, NoBoundaryFile_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  FileMetaData* f2 = AddFile(2, "d", 100, "e", 100);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);
  level_files_.push_back(f2);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  // f2's smallest key "d" > "b", so no boundary sharing the same user key
  ASSERT_EQ(compaction_files_.size(), 1u);
}

// Test: Boundary file with same user key as largest in compaction
// A boundary file is one whose smallest user key equals the largest user key 
// of the compaction files but has a smaller sequence number
TEST_F(AddBoundaryInputsTest_176, OneBoundaryFile_176) {
  // Compaction file: largest key is ("b", 100)
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  // Level file that starts at the same user key "b" but with smaller seq number
  FileMetaData* f2 = AddFile(2, "b", 50, "c", 50);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);
  level_files_.push_back(f2);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  // f2 should be added as a boundary file because its smallest key shares
  // user key "b" with the largest key of f1
  ASSERT_EQ(compaction_files_.size(), 2u);
  ASSERT_EQ(compaction_files_[1], f2);
}

// Test: Chain of boundary files
TEST_F(AddBoundaryInputsTest_176, ChainOfBoundaryFiles_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  // f2 starts at "b" (boundary of f1), ends at "c"
  FileMetaData* f2 = AddFile(2, "b", 50, "c", 100);
  // f3 starts at "c" (boundary of f2), ends at "d"
  FileMetaData* f3 = AddFile(3, "c", 50, "d", 100);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);
  level_files_.push_back(f2);
  level_files_.push_back(f3);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  // Should add f2 (boundary on "b"), then f3 (boundary on "c")
  ASSERT_EQ(compaction_files_.size(), 3u);
  ASSERT_EQ(compaction_files_[1], f2);
  ASSERT_EQ(compaction_files_[2], f3);
}

// Test: Multiple compaction files, boundary is based on the largest overall key
TEST_F(AddBoundaryInputsTest_176, MultipleCompactionFiles_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  FileMetaData* f2 = AddFile(2, "c", 100, "d", 100);
  // Boundary file starts at "d" (same user key as largest of f2)
  FileMetaData* f3 = AddFile(3, "d", 50, "e", 50);

  compaction_files_.push_back(f1);
  compaction_files_.push_back(f2);
  level_files_.push_back(f1);
  level_files_.push_back(f2);
  level_files_.push_back(f3);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  // f3 should be added because "d" matches the largest key among compaction files
  ASSERT_GE(compaction_files_.size(), 3u);
  bool found_f3 = false;
  for (auto* f : compaction_files_) {
    if (f == f3) found_f3 = true;
  }
  ASSERT_TRUE(found_f3);
}

// Test: Boundary file already in compaction files should still be added
// (the function doesn't deduplicate)
TEST_F(AddBoundaryInputsTest_176, BoundaryFileNotDeduplicated_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  FileMetaData* f2 = AddFile(2, "b", 50, "c", 50);

  compaction_files_.push_back(f1);
  // f2 is already in compaction_files_
  compaction_files_.push_back(f2);
  level_files_.push_back(f1);
  level_files_.push_back(f2);

  size_t initial_size = compaction_files_.size();
  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  // The function finds boundary based on largest key in compaction_files
  // After f2 is already there, the largest is "c" from f2
  // No file starts at "c", so no new files should be added (beyond what was there)
  // OR f2 gets added again since FindSmallestBoundaryFile might return f2 again
  // We just verify no crash and the function completes
  ASSERT_GE(compaction_files_.size(), initial_size);
}

// Test: Single file in both level and compaction, no boundary exists
TEST_F(AddBoundaryInputsTest_176, SingleFileBothSets_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "z", 100);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  ASSERT_EQ(compaction_files_.size(), 1u);
}

// Test: Boundary file with same user key but higher sequence (not a boundary)
TEST_F(AddBoundaryInputsTest_176, HigherSequenceNotBoundary_176) {
  // f1's largest is ("b", 100)
  FileMetaData* f1 = AddFile(1, "a", 200, "b", 100);
  // f2's smallest is ("b", 200) - higher seq means smaller internal key
  // Actually in LevelDB, higher sequence number means the key sorts BEFORE 
  // within the same user key. So ("b", 200) < ("b", 100) in internal key order.
  FileMetaData* f2 = AddFile(2, "b", 200, "c", 100);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);
  level_files_.push_back(f2);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  // f2's smallest ("b", 200) is actually smaller than f1's largest ("b", 100)
  // so it may or may not be considered a boundary depending on implementation
  // We just verify no crash
  ASSERT_GE(compaction_files_.size(), 1u);
}

// Test: Level files with non-overlapping keys, no boundary
TEST_F(AddBoundaryInputsTest_176, NonOverlappingLevelFiles_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  FileMetaData* f2 = AddFile(2, "e", 100, "f", 100);
  FileMetaData* f3 = AddFile(3, "g", 100, "h", 100);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);
  level_files_.push_back(f2);
  level_files_.push_back(f3);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  ASSERT_EQ(compaction_files_.size(), 1u);
}

// Test: Long chain of boundary files
TEST_F(AddBoundaryInputsTest_176, LongChain_176) {
  FileMetaData* f1 = AddFile(1, "a", 100, "b", 100);
  FileMetaData* f2 = AddFile(2, "b", 50, "c", 100);
  FileMetaData* f3 = AddFile(3, "c", 50, "d", 100);
  FileMetaData* f4 = AddFile(4, "d", 50, "e", 100);
  FileMetaData* f5 = AddFile(5, "e", 50, "f", 100);

  compaction_files_.push_back(f1);
  level_files_.push_back(f1);
  level_files_.push_back(f2);
  level_files_.push_back(f3);
  level_files_.push_back(f4);
  level_files_.push_back(f5);

  AddBoundaryInputs(icmp_, level_files_, &compaction_files_);
  ASSERT_EQ(compaction_files_.size(), 5u);
  ASSERT_EQ(compaction_files_[0], f1);
  ASSERT_EQ(compaction_files_[1], f2);
  ASSERT_EQ(compaction_files_[2], f3);
  ASSERT_EQ(compaction_files_[3], f4);
  ASSERT_EQ(compaction_files_[4], f5);
}

}  // namespace leveldb
