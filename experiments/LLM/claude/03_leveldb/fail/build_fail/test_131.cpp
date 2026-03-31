#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <vector>
#include <string>

namespace leveldb {

// Helper function to create an InternalKey from user key, sequence number, and value type
static std::string MakeInternalKey(const std::string& user_key, SequenceNumber seq, ValueType type) {
  std::string result = user_key;
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

static InternalKey MakeIKey(const std::string& user_key, SequenceNumber seq = 100, ValueType type = kTypeValue) {
  return InternalKey(user_key, seq, type);
}

class FindFileTest_131 : public ::testing::Test {
 protected:
  void SetUp() override {
    icmp_ = new InternalKeyComparator(BytewiseComparator());
  }

  void TearDown() override {
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
    delete icmp_;
  }

  void AddFile(const std::string& smallest, const std::string& largest,
               SequenceNumber smallest_seq = 100, SequenceNumber largest_seq = 100) {
    FileMetaData* f = new FileMetaData();
    f->number = files_.size() + 1;
    f->smallest = MakeIKey(smallest, smallest_seq);
    f->largest = MakeIKey(largest, largest_seq);
    files_.push_back(f);
  }

  int Find(const std::string& key, SequenceNumber seq = 100) {
    InternalKey target(key, seq, kTypeValue);
    return FindFile(*icmp_, files_, target.Encode());
  }

  InternalKeyComparator* icmp_;
  std::vector<FileMetaData*> files_;
};

// Test with empty file list
TEST_F(FindFileTest_131, EmptyFileList_131) {
  ASSERT_EQ(0, Find("foo"));
}

// Test with a single file, key before the file's range
TEST_F(FindFileTest_131, SingleFileKeyBefore_131) {
  AddFile("b", "d");
  // Key "a" is before file [b, d], so FindFile should return 0
  ASSERT_EQ(0, Find("a"));
}

// Test with a single file, key within the file's range
TEST_F(FindFileTest_131, SingleFileKeyWithin_131) {
  AddFile("b", "d");
  // Key "c" is within [b, d], so FindFile should return 0
  ASSERT_EQ(0, Find("c"));
}

// Test with a single file, key at the file's smallest boundary
TEST_F(FindFileTest_131, SingleFileKeyAtSmallest_131) {
  AddFile("b", "d");
  ASSERT_EQ(0, Find("b"));
}

// Test with a single file, key at the file's largest boundary
TEST_F(FindFileTest_131, SingleFileKeyAtLargest_131) {
  AddFile("b", "d");
  ASSERT_EQ(0, Find("d"));
}

// Test with a single file, key after the file's range
TEST_F(FindFileTest_131, SingleFileKeyAfter_131) {
  AddFile("b", "d");
  // Key "e" is after [b, d], so FindFile should return 1
  ASSERT_EQ(1, Find("e"));
}

// Test with multiple files, key before all files
TEST_F(FindFileTest_131, MultipleFilesKeyBeforeAll_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  ASSERT_EQ(0, Find("a"));
}

// Test with multiple files, key in first file
TEST_F(FindFileTest_131, MultipleFilesKeyInFirst_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  ASSERT_EQ(0, Find("c"));
}

// Test with multiple files, key between first and second file
TEST_F(FindFileTest_131, MultipleFilesKeyBetweenFirstAndSecond_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  // Key "e" is after first file [b,d] but before second file [f,h]
  ASSERT_EQ(1, Find("e"));
}

// Test with multiple files, key in second file
TEST_F(FindFileTest_131, MultipleFilesKeyInSecond_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  ASSERT_EQ(1, Find("g"));
}

// Test with multiple files, key between second and third file
TEST_F(FindFileTest_131, MultipleFilesKeyBetweenSecondAndThird_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  ASSERT_EQ(2, Find("i"));
}

// Test with multiple files, key in third file
TEST_F(FindFileTest_131, MultipleFilesKeyInThird_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  ASSERT_EQ(2, Find("k"));
}

// Test with multiple files, key after all files
TEST_F(FindFileTest_131, MultipleFilesKeyAfterAll_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");
  ASSERT_EQ(3, Find("m"));
}

// Test with multiple files, key at boundaries
TEST_F(FindFileTest_131, MultipleFilesKeyAtBoundaries_131) {
  AddFile("b", "d");
  AddFile("f", "h");
  AddFile("j", "l");

  // At the largest key of first file
  ASSERT_EQ(0, Find("d"));
  // At the smallest key of second file
  ASSERT_EQ(1, Find("f"));
  // At the largest key of second file
  ASSERT_EQ(1, Find("h"));
  // At the smallest key of third file
  ASSERT_EQ(2, Find("j"));
  // At the largest key of third file
  ASSERT_EQ(2, Find("l"));
}

// Test with two files that share a boundary point
TEST_F(FindFileTest_131, AdjacentFiles_131) {
  AddFile("a", "c");
  AddFile("d", "f");
  ASSERT_EQ(0, Find("c"));
  ASSERT_EQ(1, Find("d"));
}

// Test with many files to exercise binary search
TEST_F(FindFileTest_131, ManyFiles_131) {
  // Create 10 files: [aa, ab], [ba, bb], [ca, cb], ..., [ja, jb]
  const char* prefixes = "abcdefghij";
  for (int i = 0; i < 10; i++) {
    std::string smallest(1, prefixes[i]);
    smallest += "a";
    std::string largest(1, prefixes[i]);
    largest += "b";
    AddFile(smallest, largest);
  }

  // Before all
  ASSERT_EQ(0, Find("a"));

  // In first file
  ASSERT_EQ(0, Find("aa"));

  // Between first and second
  ASSERT_EQ(1, Find("az"));

  // In last file
  ASSERT_EQ(9, Find("ja"));

  // After all
  ASSERT_EQ(10, Find("z"));

  // In middle file (fifth file: [ea, eb])
  ASSERT_EQ(4, Find("ea"));
}

// Test sequence number ordering: same user key but different sequence numbers
TEST_F(FindFileTest_131, SequenceNumberOrdering_131) {
  // InternalKey ordering: for same user key, larger sequence number comes first
  AddFile("a", "b", 200, 100);
  
  // Key "b" with a very high sequence number should come before "b" with seq 100
  // Since InternalKey comparison considers seq number (higher seq = smaller internal key for same user key)
  // The file's largest is ("b", 100, kTypeValue)
  // Searching for ("b", 200, kTypeValue) which is "less than" ("b", 100) in internal key order
  ASSERT_EQ(0, Find("b", 200));

  // Searching for ("b", 50) which is "greater than" ("b", 100) in internal key order
  ASSERT_EQ(0, Find("b", 50));
}

// Test with a single point file (smallest == largest user key)
TEST_F(FindFileTest_131, PointFile_131) {
  AddFile("c", "c");
  ASSERT_EQ(0, Find("b"));
  ASSERT_EQ(0, Find("c"));
  ASSERT_EQ(1, Find("d"));
}

}  // namespace leveldb
