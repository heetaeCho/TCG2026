#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include <vector>

namespace leveldb {

// Declaration of the function under test
FileMetaData* FindSmallestBoundaryFile(
    const InternalKeyComparator& icmp,
    const std::vector<FileMetaData*>& level_files,
    const InternalKey& largest_key);

class FindSmallestBoundaryFileTest_175 : public ::testing::Test {
 protected:
  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;
  std::vector<FileMetaData*> allocated_files_;

  FindSmallestBoundaryFileTest_175()
      : icmp_(BytewiseComparator()) {}

  ~FindSmallestBoundaryFileTest_175() override {
    for (auto* f : allocated_files_) {
      delete f;
    }
  }

  FileMetaData* CreateFile(const Slice& smallest_user_key,
                           SequenceNumber smallest_seq,
                           const Slice& largest_user_key,
                           SequenceNumber largest_seq) {
    FileMetaData* f = new FileMetaData();
    f->smallest = InternalKey(smallest_user_key, smallest_seq, kTypeValue);
    f->largest = InternalKey(largest_user_key, largest_seq, kTypeValue);
    allocated_files_.push_back(f);
    return f;
  }
};

// Test with empty file list - should return nullptr
TEST_F(FindSmallestBoundaryFileTest_175, EmptyFileList_175) {
  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_EQ(nullptr, result);
}

// Test when no file has a boundary condition - should return nullptr
TEST_F(FindSmallestBoundaryFileTest_175, NoBoundaryFiles_175) {
  // File with completely different user key
  FileMetaData* f1 = CreateFile("aaa", 100, "bbb", 50);
  files_.push_back(f1);

  InternalKey largest_key("zzz", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_EQ(nullptr, result);
}

// Test when a file has the same user key but smaller sequence number
// (which means larger internal key since sequence numbers are sorted descending)
TEST_F(FindSmallestBoundaryFileTest_175, SingleBoundaryFile_175) {
  // largest_key is ("key", 100, kTypeValue)
  // A boundary file must have:
  //   - icmp.Compare(f->smallest, largest_key) > 0
  //     => same user_key but smaller sequence number (since internal key ordering
  //        puts larger sequence numbers first)
  //   - user_cmp->Compare(f->smallest.user_key(), largest_key.user_key()) == 0
  //     => same user key
  FileMetaData* f1 = CreateFile("key", 50, "key2", 40);
  files_.push_back(f1);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_NE(nullptr, result);
  ASSERT_EQ(f1, result);
}

// Test when file has same user key and same sequence number - not a boundary
TEST_F(FindSmallestBoundaryFileTest_175, SameUserKeySameSequence_175) {
  FileMetaData* f1 = CreateFile("key", 100, "key2", 50);
  files_.push_back(f1);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  // icmp.Compare(f->smallest, largest_key) should be 0 (not > 0), so not a boundary
  ASSERT_EQ(nullptr, result);
}

// Test when file has same user key but higher sequence number - not a boundary
TEST_F(FindSmallestBoundaryFileTest_175, SameUserKeyHigherSequence_175) {
  FileMetaData* f1 = CreateFile("key", 200, "key2", 50);
  files_.push_back(f1);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  // icmp.Compare: same user key, seq 200 > 100, so internal key is smaller
  // (in internal key ordering, larger seq = smaller key), so Compare < 0, not > 0
  ASSERT_EQ(nullptr, result);
}

// Test when file has different user key that is larger - not a boundary
// because user keys must be equal
TEST_F(FindSmallestBoundaryFileTest_175, DifferentUserKeyLarger_175) {
  FileMetaData* f1 = CreateFile("key2", 50, "key3", 40);
  files_.push_back(f1);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  // user_cmp->Compare("key2", "key") != 0
  ASSERT_EQ(nullptr, result);
}

// Test with multiple boundary files - should return the one with smallest internal key
TEST_F(FindSmallestBoundaryFileTest_175, MultipleBoundaryFiles_175) {
  // Both have same user key "key" with sequences less than 100
  FileMetaData* f1 = CreateFile("key", 50, "key2", 40);
  FileMetaData* f2 = CreateFile("key", 80, "key3", 30);
  files_.push_back(f1);
  files_.push_back(f2);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_NE(nullptr, result);
  // In internal key ordering, seq 80 < seq 50 means ("key", 80) < ("key", 50)
  // So ("key", 80) is the smallest boundary file
  ASSERT_EQ(f2, result);
}

// Test with mix of boundary and non-boundary files
TEST_F(FindSmallestBoundaryFileTest_175, MixedFiles_175) {
  // Non-boundary: different user key
  FileMetaData* f1 = CreateFile("aaa", 50, "bbb", 40);
  // Boundary: same user key, lower sequence
  FileMetaData* f2 = CreateFile("key", 30, "key5", 20);
  // Non-boundary: same user key, higher sequence (not > in icmp)
  FileMetaData* f3 = CreateFile("key", 200, "key6", 10);
  files_.push_back(f1);
  files_.push_back(f2);
  files_.push_back(f3);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_NE(nullptr, result);
  ASSERT_EQ(f2, result);
}

// Test with a single file that is not a boundary
TEST_F(FindSmallestBoundaryFileTest_175, SingleNonBoundaryFile_175) {
  FileMetaData* f1 = CreateFile("other", 100, "other2", 50);
  files_.push_back(f1);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_EQ(nullptr, result);
}

// Test boundary with multiple files having same user key but different sequences,
// all lower than the largest_key's sequence
TEST_F(FindSmallestBoundaryFileTest_175, MultipleBoundarySelectsSmallest_175) {
  FileMetaData* f1 = CreateFile("key", 10, "key2", 5);
  FileMetaData* f2 = CreateFile("key", 20, "key3", 15);
  FileMetaData* f3 = CreateFile("key", 90, "key4", 85);
  files_.push_back(f1);
  files_.push_back(f2);
  files_.push_back(f3);

  InternalKey largest_key("key", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_NE(nullptr, result);
  // In internal key ordering for same user key:
  // seq 90 is smallest internal key among {90, 20, 10} since higher seq = smaller internal key
  // So f3 ("key", 90) should be returned
  ASSERT_EQ(f3, result);
}

// Test that file with smallest.user_key() smaller than largest_key.user_key() is not boundary
TEST_F(FindSmallestBoundaryFileTest_175, SmallerUserKeyNotBoundary_175) {
  FileMetaData* f1 = CreateFile("abc", 50, "xyz", 40);
  files_.push_back(f1);

  InternalKey largest_key("def", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_EQ(nullptr, result);
}

// Test with sequence number 1 (near minimum)
TEST_F(FindSmallestBoundaryFileTest_175, BoundarySequenceOne_175) {
  FileMetaData* f1 = CreateFile("key", 1, "key2", 1);
  files_.push_back(f1);

  InternalKey largest_key("key", 2, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_NE(nullptr, result);
  ASSERT_EQ(f1, result);
}

// Test with large number of files, only one is boundary
TEST_F(FindSmallestBoundaryFileTest_175, ManyFilesOneBoundary_175) {
  for (int i = 0; i < 100; ++i) {
    std::string user_key = "other" + std::to_string(i);
    FileMetaData* f = CreateFile(user_key, 50, user_key + "z", 40);
    files_.push_back(f);
  }
  // Add one boundary file
  FileMetaData* boundary = CreateFile("target", 50, "targetz", 40);
  files_.push_back(boundary);

  InternalKey largest_key("target", 100, kTypeValue);
  FileMetaData* result = FindSmallestBoundaryFile(icmp_, files_, largest_key);
  ASSERT_NE(nullptr, result);
  ASSERT_EQ(boundary, result);
}

}  // namespace leveldb
