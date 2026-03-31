#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "db/dbformat.h"
#include "util/testutil.h"

#include <vector>
#include <string>
#include <cstring>

namespace leveldb {

// Helper to create an InternalKey string
static std::string MakeInternalKey(const std::string& user_key, uint64_t seq,
                                   ValueType type) {
  std::string result;
  result = user_key;
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

// We need to access the LevelFileNumIterator which is a private nested class.
// Since we can't directly instantiate it, we'll use Version's public interface
// or rely on the fact that NewConcatenatingIterator / internal iteration
// uses LevelFileNumIterator. However, the test prompt asks us to test
// LevelFileNumIterator::Seek specifically.
//
// Since LevelFileNumIterator is internal to version_set.cc, we test it
// indirectly through the public interfaces that create and use it.
// The main way to exercise it is via Version::NewConcatenatingIterator
// or the internal iterators returned by Version.

class LevelFileNumIteratorTest_136 : public ::testing::Test {
 protected:
  LevelFileNumIteratorTest_136()
      : icmp_(BytewiseComparator()) {}

  void SetUp() override {}

  void TearDown() override {
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
  }

  FileMetaData* AddFile(uint64_t number, const std::string& smallest_key,
                        const std::string& largest_key,
                        uint64_t smallest_seq = 100,
                        uint64_t largest_seq = 100) {
    FileMetaData* f = new FileMetaData();
    f->number = number;
    f->file_size = 1000;
    f->smallest = InternalKey(smallest_key, smallest_seq, kTypeValue);
    f->largest = InternalKey(largest_key, largest_seq, kTypeValue);
    files_.push_back(f);
    return f;
  }

  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;
};

// We can test the LevelFileNumIterator indirectly through version_set internals.
// Since LevelFileNumIterator is defined in the .cc file (not header-exposed),
// we test it through the Table cache / Version iteration mechanisms.

// However, FindFile is exposed in version_set.h as a free function.
// Let's test FindFile which is used by Seek.

TEST_F(LevelFileNumIteratorTest_136, FindFileEmptyFileList_136) {
  int result = FindFile(icmp_, files_, InternalKey("abc", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
}

TEST_F(LevelFileNumIteratorTest_136, FindFileSingleFile_136) {
  AddFile(1, "b", "d");
  
  // Key before the file
  int result = FindFile(icmp_, files_, InternalKey("a", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // Key within the file range
  result = FindFile(icmp_, files_, InternalKey("c", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // Key at the largest boundary
  result = FindFile(icmp_, files_, InternalKey("d", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // Key after the file
  result = FindFile(icmp_, files_, InternalKey("e", 100, kTypeValue).Encode());
  EXPECT_EQ(1, result);
}

TEST_F(LevelFileNumIteratorTest_136, FindFileMultipleFiles_136) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");
  
  // Before all files
  int result = FindFile(icmp_, files_, InternalKey("0", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // In first file
  result = FindFile(icmp_, files_, InternalKey("a", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // Between first and second file
  result = FindFile(icmp_, files_, InternalKey("b", 50, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // In second file
  result = FindFile(icmp_, files_, InternalKey("c", 100, kTypeValue).Encode());
  EXPECT_EQ(1, result);
  
  // In third file
  result = FindFile(icmp_, files_, InternalKey("e", 100, kTypeValue).Encode());
  EXPECT_EQ(2, result);
  
  // After all files
  result = FindFile(icmp_, files_, InternalKey("g", 100, kTypeValue).Encode());
  EXPECT_EQ(3, result);
}

TEST_F(LevelFileNumIteratorTest_136, FindFileSequenceNumberOrdering_136) {
  // With same user key but different sequence numbers
  AddFile(1, "a", "b");
  
  // Higher sequence number should come first (newer)
  int result = FindFile(icmp_, files_, InternalKey("b", 200, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  result = FindFile(icmp_, files_, InternalKey("b", 1, kTypeValue).Encode());
  EXPECT_EQ(0, result);
}

TEST_F(LevelFileNumIteratorTest_136, FindFileAtBoundary_136) {
  AddFile(1, "a", "c");
  AddFile(2, "d", "f");
  
  // Exact boundary of first file largest key
  int result = FindFile(icmp_, files_, InternalKey("c", 100, kTypeValue).Encode());
  EXPECT_EQ(0, result);
  
  // Exact boundary of second file smallest key
  result = FindFile(icmp_, files_, InternalKey("d", 100, kTypeValue).Encode());
  EXPECT_EQ(1, result);
}

// Test SomeFileOverlapsRange which is also part of version_set and related
TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeEmpty_136) {
  bool result = SomeFileOverlapsRange(icmp_, false, files_, nullptr, nullptr);
  EXPECT_FALSE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeNoOverlap_136) {
  AddFile(1, "a", "b");
  AddFile(2, "d", "e");
  
  Slice small("f");
  Slice large("g");
  bool result = SomeFileOverlapsRange(icmp_, false, files_, &small, &large);
  EXPECT_FALSE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeWithOverlap_136) {
  AddFile(1, "a", "c");
  AddFile(2, "d", "f");
  
  Slice small("b");
  Slice large("e");
  bool result = SomeFileOverlapsRange(icmp_, false, files_, &small, &large);
  EXPECT_TRUE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeNullBounds_136) {
  AddFile(1, "a", "c");
  
  // nullptr means unbounded
  bool result = SomeFileOverlapsRange(icmp_, false, files_, nullptr, nullptr);
  EXPECT_TRUE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeDisjointLevel0_136) {
  // For level 0 (disjoint_sorted_files = false), files may overlap
  AddFile(1, "a", "d");
  AddFile(2, "b", "e");
  
  Slice small("c");
  Slice large("c");
  bool result = SomeFileOverlapsRange(icmp_, false, files_, &small, &large);
  EXPECT_TRUE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeSortedFiles_136) {
  // For sorted files (disjoint_sorted_files = true)
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");
  
  Slice small("c");
  Slice large("d");
  bool result = SomeFileOverlapsRange(icmp_, true, files_, &small, &large);
  EXPECT_TRUE(result);
  
  Slice small2("g");
  Slice large2("h");
  result = SomeFileOverlapsRange(icmp_, true, files_, &small2, &large2);
  EXPECT_FALSE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsExactBoundary_136) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  
  // Exactly at boundary
  Slice small("b");
  Slice large("b");
  bool result = SomeFileOverlapsRange(icmp_, true, files_, &small, &large);
  EXPECT_TRUE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeOnlySmallBound_136) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  
  Slice small("c");
  bool result = SomeFileOverlapsRange(icmp_, true, files_, &small, nullptr);
  EXPECT_TRUE(result);
}

TEST_F(LevelFileNumIteratorTest_136, SomeFileOverlapsRangeOnlyLargeBound_136) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  
  Slice large("a");
  bool result = SomeFileOverlapsRange(icmp_, true, files_, nullptr, &large);
  EXPECT_TRUE(result);
}

TEST_F(LevelFileNumIteratorTest_136, FindFileManyFiles_136) {
  // Test with many files to exercise binary search
  for (int i = 0; i < 100; i++) {
    std::string smallest(1, static_cast<char>('a' + (i % 26)));
    smallest += std::to_string(i);
    std::string largest = smallest + "z";
    AddFile(i + 1, smallest, largest);
  }
  
  // This should not crash and should return a valid index
  int result = FindFile(icmp_, files_, InternalKey("m50", 100, kTypeValue).Encode());
  EXPECT_GE(result, 0);
  EXPECT_LE(result, static_cast<int>(files_.size()));
}

}  // namespace leveldb
