#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "util/comparator.h"

#include <vector>
#include <string>

namespace leveldb {

// Declaration of the function under test
bool FindLargestKey(const InternalKeyComparator& icmp,
                    const std::vector<FileMetaData*>& files,
                    InternalKey* largest_key);

class FindLargestKeyTest_174 : public ::testing::Test {
 protected:
  FindLargestKeyTest_174()
      : icmp_(BytewiseComparator()) {}

  ~FindLargestKeyTest_174() override {
    for (auto* f : files_) {
      delete f;
    }
  }

  FileMetaData* CreateFile(const std::string& smallest_user_key,
                           SequenceNumber smallest_seq,
                           const std::string& largest_user_key,
                           SequenceNumber largest_seq) {
    FileMetaData* f = new FileMetaData();
    f->smallest = InternalKey(smallest_user_key, smallest_seq, kTypeValue);
    f->largest = InternalKey(largest_user_key, largest_seq, kTypeValue);
    files_.push_back(f);
    return f;
  }

  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;
};

TEST_F(FindLargestKeyTest_174, EmptyFilesReturnsFalse_174) {
  std::vector<FileMetaData*> empty;
  InternalKey result;
  EXPECT_FALSE(FindLargestKey(icmp_, empty, &result));
}

TEST_F(FindLargestKeyTest_174, SingleFileReturnsItsLargest_174) {
  std::vector<FileMetaData*> v;
  FileMetaData* f = CreateFile("a", 100, "z", 100);
  v.push_back(f);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  EXPECT_EQ(icmp_.Compare(result, f->largest), 0);
}

TEST_F(FindLargestKeyTest_174, MultipleFilesReturnsLargest_174) {
  std::vector<FileMetaData*> v;
  FileMetaData* f1 = CreateFile("a", 100, "d", 100);
  FileMetaData* f2 = CreateFile("e", 100, "z", 100);
  FileMetaData* f3 = CreateFile("b", 100, "m", 100);
  v.push_back(f1);
  v.push_back(f2);
  v.push_back(f3);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  // "z" should be the largest user key
  EXPECT_EQ(icmp_.Compare(result, f2->largest), 0);
}

TEST_F(FindLargestKeyTest_174, LargestIsFirstFile_174) {
  std::vector<FileMetaData*> v;
  FileMetaData* f1 = CreateFile("a", 100, "z", 100);
  FileMetaData* f2 = CreateFile("b", 100, "m", 100);
  FileMetaData* f3 = CreateFile("c", 100, "n", 100);
  v.push_back(f1);
  v.push_back(f2);
  v.push_back(f3);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  EXPECT_EQ(icmp_.Compare(result, f1->largest), 0);
}

TEST_F(FindLargestKeyTest_174, LargestIsLastFile_174) {
  std::vector<FileMetaData*> v;
  FileMetaData* f1 = CreateFile("a", 100, "b", 100);
  FileMetaData* f2 = CreateFile("c", 100, "d", 100);
  FileMetaData* f3 = CreateFile("e", 100, "z", 100);
  v.push_back(f1);
  v.push_back(f2);
  v.push_back(f3);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  EXPECT_EQ(icmp_.Compare(result, f3->largest), 0);
}

TEST_F(FindLargestKeyTest_174, SameUserKeyDifferentSequenceNumbers_174) {
  // With the same user key, larger sequence number sorts first (smaller in
  // internal key ordering). So the largest internal key for the same user key
  // is the one with the smallest sequence number.
  std::vector<FileMetaData*> v;
  FileMetaData* f1 = CreateFile("a", 100, "z", 200);
  FileMetaData* f2 = CreateFile("a", 100, "z", 100);
  v.push_back(f1);
  v.push_back(f2);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  // In InternalKey comparison, for same user key, smaller seq is "larger"
  // (because the sorting is descending by sequence number for same user key).
  // So "z" with seq 100 > "z" with seq 200 in internal key ordering.
  EXPECT_EQ(icmp_.Compare(result, f2->largest), 0);
}

TEST_F(FindLargestKeyTest_174, TwoFilesWithIdenticalLargest_174) {
  std::vector<FileMetaData*> v;
  FileMetaData* f1 = CreateFile("a", 100, "m", 100);
  FileMetaData* f2 = CreateFile("b", 100, "m", 100);
  v.push_back(f1);
  v.push_back(f2);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  // Both have the same largest, result should equal either (they're the same)
  EXPECT_EQ(icmp_.Compare(result, f1->largest), 0);
  EXPECT_EQ(icmp_.Compare(result, f2->largest), 0);
}

TEST_F(FindLargestKeyTest_174, ManyFiles_174) {
  std::vector<FileMetaData*> v;
  // Create files with largest keys "b", "c", "d", ..., "y"
  for (char c = 'b'; c <= 'y'; ++c) {
    std::string key(1, c);
    FileMetaData* f = CreateFile("a", 100, key, 100);
    v.push_back(f);
  }
  // Add one more with "z" as largest
  FileMetaData* fz = CreateFile("a", 100, "z", 100);
  v.push_back(fz);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  EXPECT_EQ(icmp_.Compare(result, fz->largest), 0);
}

TEST_F(FindLargestKeyTest_174, LargestInMiddle_174) {
  std::vector<FileMetaData*> v;
  FileMetaData* f1 = CreateFile("a", 100, "c", 100);
  FileMetaData* f2 = CreateFile("a", 100, "z", 100);
  FileMetaData* f3 = CreateFile("a", 100, "m", 100);
  v.push_back(f1);
  v.push_back(f2);
  v.push_back(f3);

  InternalKey result;
  EXPECT_TRUE(FindLargestKey(icmp_, v, &result));
  EXPECT_EQ(icmp_.Compare(result, f2->largest), 0);
}

}  // namespace leveldb
