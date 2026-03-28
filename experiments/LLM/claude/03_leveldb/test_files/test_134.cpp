#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <vector>
#include <string>

namespace leveldb {

// We need access to SomeFileOverlapsRange which is in the leveldb namespace
// Forward declare if needed
bool SomeFileOverlapsRange(const InternalKeyComparator& icmp,
                           bool disjoint_sorted_files,
                           const std::vector<FileMetaData*>& files,
                           const Slice* smallest_user_key,
                           const Slice* largest_user_key);

class SomeFileOverlapsRangeTest_134 : public ::testing::Test {
 protected:
  SomeFileOverlapsRangeTest_134()
      : icmp_(BytewiseComparator()) {}

  ~SomeFileOverlapsRangeTest_134() override {
    for (auto* f : files_) {
      delete f;
    }
  }

  void AddFile(const std::string& smallest, const std::string& largest) {
    FileMetaData* f = new FileMetaData();
    f->number = next_file_number_++;
    f->smallest = InternalKey(smallest, 100, kTypeValue);
    f->largest = InternalKey(largest, 100, kTypeValue);
    files_.push_back(f);
  }

  bool Overlaps(bool disjoint_sorted, const Slice* smallest,
                const Slice* largest) {
    return SomeFileOverlapsRange(icmp_, disjoint_sorted, files_, smallest,
                                 largest);
  }

  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;
  uint64_t next_file_number_ = 1;
};

// Test with empty file list - should never overlap
TEST_F(SomeFileOverlapsRangeTest_134, EmptyFilesNoOverlap_134) {
  Slice smallest("a");
  Slice largest("z");
  ASSERT_FALSE(Overlaps(false, &smallest, &largest));
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
}

// Test with empty file list and null keys
TEST_F(SomeFileOverlapsRangeTest_134, EmptyFilesNullKeys_134) {
  ASSERT_FALSE(Overlaps(false, nullptr, nullptr));
  ASSERT_FALSE(Overlaps(true, nullptr, nullptr));
}

// Test single file - range completely before file (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeBeforeFile_134) {
  AddFile("d", "f");
  Slice smallest("a");
  Slice largest("c");
  ASSERT_FALSE(Overlaps(false, &smallest, &largest));
}

// Test single file - range completely after file (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeAfterFile_134) {
  AddFile("d", "f");
  Slice smallest("g");
  Slice largest("z");
  ASSERT_FALSE(Overlaps(false, &smallest, &largest));
}

// Test single file - range overlaps file (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeOverlapsFile_134) {
  AddFile("d", "f");
  Slice smallest("e");
  Slice largest("g");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test single file - range completely contains file (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeContainsFile_134) {
  AddFile("d", "f");
  Slice smallest("a");
  Slice largest("z");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test single file - range is contained within file (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointFileContainsRange_134) {
  AddFile("a", "z");
  Slice smallest("d");
  Slice largest("f");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test single file - range touches file boundary exactly (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeTouchesFileBoundary_134) {
  AddFile("d", "f");
  Slice smallest("f");
  Slice largest("g");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test single file - range ends exactly at file start (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeEndsAtFileStart_134) {
  AddFile("d", "f");
  Slice smallest("a");
  Slice largest("d");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test single file - range completely before file (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointRangeBeforeFile_134) {
  AddFile("d", "f");
  Slice smallest("a");
  Slice largest("c");
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
}

// Test single file - range completely after file (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointRangeAfterFile_134) {
  AddFile("d", "f");
  Slice smallest("g");
  Slice largest("z");
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
}

// Test single file - range overlaps file (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointRangeOverlapsFile_134) {
  AddFile("d", "f");
  Slice smallest("e");
  Slice largest("g");
  ASSERT_TRUE(Overlaps(true, &smallest, &largest));
}

// Test multiple files non-disjoint - overlap with one file
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointMultipleFilesOverlapOne_134) {
  AddFile("a", "c");
  AddFile("d", "f");
  AddFile("g", "i");
  Slice smallest("d");
  Slice largest("e");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test multiple files non-disjoint - no overlap
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointMultipleFilesNoOverlap_134) {
  AddFile("a", "b");
  AddFile("d", "e");
  AddFile("g", "h");
  Slice smallest("bb");
  Slice largest("cc");
  ASSERT_FALSE(Overlaps(false, &smallest, &largest));
}

// Test multiple disjoint sorted files - overlap with middle file
TEST_F(SomeFileOverlapsRangeTest_134, DisjointMultipleFilesOverlapMiddle_134) {
  AddFile("a", "c");
  AddFile("d", "f");
  AddFile("g", "i");
  Slice smallest("e");
  Slice largest("e");
  ASSERT_TRUE(Overlaps(true, &smallest, &largest));
}

// Test multiple disjoint sorted files - no overlap in gap
TEST_F(SomeFileOverlapsRangeTest_134, DisjointMultipleFilesNoOverlapGap_134) {
  AddFile("a", "b");
  AddFile("d", "e");
  AddFile("g", "h");
  Slice smallest("bb");
  Slice largest("cc");
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
}

// Test with null smallest_user_key (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointNullSmallestOverlap_134) {
  AddFile("d", "f");
  Slice largest("e");
  ASSERT_TRUE(Overlaps(false, nullptr, &largest));
}

// Test with null smallest_user_key that doesn't overlap (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointNullSmallestNoOverlap_134) {
  AddFile("d", "f");
  Slice largest("c");
  ASSERT_FALSE(Overlaps(false, nullptr, &largest));
}

// Test with null largest_user_key (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointNullLargestOverlap_134) {
  AddFile("d", "f");
  Slice smallest("e");
  ASSERT_TRUE(Overlaps(false, &smallest, nullptr));
}

// Test with null largest_user_key that doesn't overlap (non-disjoint)
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointNullLargestNoOverlap_134) {
  AddFile("d", "f");
  Slice smallest("g");
  ASSERT_FALSE(Overlaps(false, &smallest, nullptr));
}

// Test with both null keys (non-disjoint) - should overlap any file
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointBothNullOverlap_134) {
  AddFile("d", "f");
  ASSERT_TRUE(Overlaps(false, nullptr, nullptr));
}

// Test with null smallest_user_key (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointNullSmallestOverlap_134) {
  AddFile("d", "f");
  Slice largest("e");
  ASSERT_TRUE(Overlaps(true, nullptr, &largest));
}

// Test with null smallest_user_key that doesn't overlap (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointNullSmallestNoOverlap_134) {
  AddFile("d", "f");
  Slice largest("c");
  ASSERT_FALSE(Overlaps(true, nullptr, &largest));
}

// Test with null largest_user_key (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointNullLargestOverlap_134) {
  AddFile("d", "f");
  Slice smallest("e");
  ASSERT_TRUE(Overlaps(true, &smallest, nullptr));
}

// Test with null largest_user_key that doesn't overlap (disjoint sorted)
TEST_F(SomeFileOverlapsRangeTest_134, DisjointNullLargestNoOverlap_134) {
  AddFile("d", "f");
  Slice smallest("g");
  ASSERT_FALSE(Overlaps(true, &smallest, nullptr));
}

// Test with both null keys (disjoint sorted) - should overlap any file
TEST_F(SomeFileOverlapsRangeTest_134, DisjointBothNullOverlap_134) {
  AddFile("d", "f");
  ASSERT_TRUE(Overlaps(true, nullptr, nullptr));
}

// Test disjoint sorted with range after all files
TEST_F(SomeFileOverlapsRangeTest_134, DisjointRangeAfterAllFiles_134) {
  AddFile("a", "b");
  AddFile("c", "d");
  AddFile("e", "f");
  Slice smallest("g");
  Slice largest("z");
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
}

// Test disjoint sorted with range before all files
TEST_F(SomeFileOverlapsRangeTest_134, DisjointRangeBeforeAllFiles_134) {
  AddFile("d", "e");
  AddFile("f", "g");
  AddFile("h", "i");
  Slice smallest("a");
  Slice largest("c");
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
}

// Test disjoint sorted with range spanning multiple files
TEST_F(SomeFileOverlapsRangeTest_134, DisjointRangeSpansMultipleFiles_134) {
  AddFile("a", "b");
  AddFile("c", "d");
  AddFile("e", "f");
  Slice smallest("b");
  Slice largest("e");
  ASSERT_TRUE(Overlaps(true, &smallest, &largest));
}

// Test boundary: single point range matching file start
TEST_F(SomeFileOverlapsRangeTest_134, DisjointPointRangeAtFileStart_134) {
  AddFile("b", "d");
  Slice key("b");
  ASSERT_TRUE(Overlaps(true, &key, &key));
}

// Test boundary: single point range matching file end
TEST_F(SomeFileOverlapsRangeTest_134, DisjointPointRangeAtFileEnd_134) {
  AddFile("b", "d");
  Slice key("d");
  ASSERT_TRUE(Overlaps(true, &key, &key));
}

// Test boundary: single point range between files
TEST_F(SomeFileOverlapsRangeTest_134, DisjointPointRangeBetweenFiles_134) {
  AddFile("a", "b");
  AddFile("d", "e");
  Slice key("c");
  ASSERT_FALSE(Overlaps(true, &key, &key));
}

// Test non-disjoint with overlapping files
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointOverlappingFiles_134) {
  AddFile("a", "d");
  AddFile("c", "f");
  AddFile("e", "h");
  Slice smallest("d");
  Slice largest("d");
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test non-disjoint - range in gap between non-overlapping files
TEST_F(SomeFileOverlapsRangeTest_134, NonDisjointRangeInGapBetweenFiles_134) {
  AddFile("a", "b");
  AddFile("e", "f");
  Slice smallest("c");
  Slice largest("d");
  ASSERT_FALSE(Overlaps(false, &smallest, &largest));
}

// Test with identical smallest and largest in file
TEST_F(SomeFileOverlapsRangeTest_134, SingleKeyFile_134) {
  AddFile("c", "c");
  Slice smallest("c");
  Slice largest("c");
  ASSERT_TRUE(Overlaps(true, &smallest, &largest));
  ASSERT_TRUE(Overlaps(false, &smallest, &largest));
}

// Test with identical smallest and largest in file, range misses
TEST_F(SomeFileOverlapsRangeTest_134, SingleKeyFileMiss_134) {
  AddFile("c", "c");
  Slice smallest("d");
  Slice largest("d");
  ASSERT_FALSE(Overlaps(true, &smallest, &largest));
  ASSERT_FALSE(Overlaps(false, &smallest, &largest));
}

}  // namespace leveldb
