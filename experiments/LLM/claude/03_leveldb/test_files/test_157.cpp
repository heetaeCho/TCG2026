#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "util/comparator.h"

#include <set>

namespace leveldb {

// Replicate the BySmallestKey struct as it appears in version_set.cc
// We need this to test since it's defined in the .cc file
struct BySmallestKey {
  const InternalKeyComparator* internal_comparator;

  bool operator()(FileMetaData* f1, FileMetaData* f2) const {
    int r = internal_comparator->Compare(f1->smallest, f2->smallest);
    if (r != 0) {
      return (r < 0);
    } else {
      return (f1->number < f2->number);
    }
  }
};

typedef std::set<FileMetaData*, BySmallestKey> FileSet;

class BySmallestKeyTest_157 : public ::testing::Test {
 protected:
  void SetUp() override {
    cmp_ = new InternalKeyComparator(BytewiseComparator());
    by_smallest_key_.internal_comparator = cmp_;
  }

  void TearDown() override {
    delete cmp_;
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
  }

  FileMetaData* CreateFile(uint64_t number, const std::string& smallest_user_key,
                           SequenceNumber smallest_seq,
                           const std::string& largest_user_key,
                           SequenceNumber largest_seq) {
    FileMetaData* f = new FileMetaData();
    f->number = number;
    f->smallest.SetFrom(ParsedInternalKey(smallest_user_key, smallest_seq, kTypeValue));
    f->largest.SetFrom(ParsedInternalKey(largest_user_key, largest_seq, kTypeValue));
    files_.push_back(f);
    return f;
  }

  InternalKeyComparator* cmp_;
  BySmallestKey by_smallest_key_;
  std::vector<FileMetaData*> files_;
};

// Test that files with different smallest keys are ordered by smallest key
TEST_F(BySmallestKeyTest_157, DifferentSmallestKeys_157) {
  FileMetaData* f1 = CreateFile(1, "aaa", 100, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "ccc", 100, "ddd", 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

// Test that files with the same smallest key are ordered by file number
TEST_F(BySmallestKeyTest_157, SameSmallestKeyDifferentNumbers_157) {
  FileMetaData* f1 = CreateFile(1, "aaa", 100, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "aaa", 100, "ccc", 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

// Test that the same file is not less than itself (strict weak ordering)
TEST_F(BySmallestKeyTest_157, SameFile_157) {
  FileMetaData* f1 = CreateFile(1, "aaa", 100, "bbb", 100);

  EXPECT_FALSE(by_smallest_key_(f1, f1));
}

// Test ordering when smallest keys differ only by sequence number
// InternalKey comparison: same user key => higher sequence number comes first (is "smaller")
TEST_F(BySmallestKeyTest_157, SameUserKeyDifferentSequence_157) {
  FileMetaData* f1 = CreateFile(1, "aaa", 200, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "aaa", 100, "ccc", 100);

  // Higher sequence number should be "smaller" in internal key ordering
  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

// Test with reversed alphabetical order
TEST_F(BySmallestKeyTest_157, ReversedAlphabetical_157) {
  FileMetaData* f1 = CreateFile(1, "zzz", 100, "zzz", 100);
  FileMetaData* f2 = CreateFile(2, "aaa", 100, "aaa", 100);

  EXPECT_FALSE(by_smallest_key_(f1, f2));
  EXPECT_TRUE(by_smallest_key_(f2, f1));
}

// Test that FileSet (std::set with BySmallestKey comparator) properly orders files
TEST_F(BySmallestKeyTest_157, FileSetOrdering_157) {
  FileSet file_set(by_smallest_key_);

  FileMetaData* f1 = CreateFile(3, "ccc", 100, "ddd", 100);
  FileMetaData* f2 = CreateFile(1, "aaa", 100, "bbb", 100);
  FileMetaData* f3 = CreateFile(2, "bbb", 100, "ccc", 100);

  file_set.insert(f1);
  file_set.insert(f2);
  file_set.insert(f3);

  auto it = file_set.begin();
  EXPECT_EQ((*it)->number, 1u);  // "aaa" smallest
  ++it;
  EXPECT_EQ((*it)->number, 2u);  // "bbb" smallest
  ++it;
  EXPECT_EQ((*it)->number, 3u);  // "ccc" smallest
}

// Test FileSet with duplicate smallest keys but different file numbers
TEST_F(BySmallestKeyTest_157, FileSetDuplicateSmallestKeys_157) {
  FileSet file_set(by_smallest_key_);

  FileMetaData* f1 = CreateFile(5, "aaa", 100, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "aaa", 100, "ccc", 100);
  FileMetaData* f3 = CreateFile(8, "aaa", 100, "ddd", 100);

  file_set.insert(f1);
  file_set.insert(f2);
  file_set.insert(f3);

  EXPECT_EQ(file_set.size(), 3u);

  auto it = file_set.begin();
  EXPECT_EQ((*it)->number, 2u);  // smallest file number
  ++it;
  EXPECT_EQ((*it)->number, 5u);
  ++it;
  EXPECT_EQ((*it)->number, 8u);  // largest file number
}

// Test with empty string keys
TEST_F(BySmallestKeyTest_157, EmptyStringKeys_157) {
  FileMetaData* f1 = CreateFile(1, "", 100, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "aaa", 100, "ccc", 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

// Test with single character keys
TEST_F(BySmallestKeyTest_157, SingleCharKeys_157) {
  FileMetaData* f1 = CreateFile(1, "a", 100, "b", 100);
  FileMetaData* f2 = CreateFile(2, "b", 100, "c", 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

// Test that file number is the tiebreaker, not file size or other fields
TEST_F(BySmallestKeyTest_157, TiebreakerIsFileNumber_157) {
  FileMetaData* f1 = CreateFile(10, "aaa", 100, "bbb", 100);
  f1->file_size = 9999;

  FileMetaData* f2 = CreateFile(5, "aaa", 100, "bbb", 100);
  f2->file_size = 1;

  // f2 has smaller number, so f2 < f1
  EXPECT_TRUE(by_smallest_key_(f2, f1));
  EXPECT_FALSE(by_smallest_key_(f1, f2));
}

// Test transitivity: if a < b and b < c, then a < c
TEST_F(BySmallestKeyTest_157, Transitivity_157) {
  FileMetaData* f1 = CreateFile(1, "aaa", 100, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "bbb", 100, "ccc", 100);
  FileMetaData* f3 = CreateFile(3, "ccc", 100, "ddd", 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_TRUE(by_smallest_key_(f2, f3));
  EXPECT_TRUE(by_smallest_key_(f1, f3));
}

// Test with long keys
TEST_F(BySmallestKeyTest_157, LongKeys_157) {
  std::string long_key_a(1000, 'a');
  std::string long_key_b(1000, 'b');

  FileMetaData* f1 = CreateFile(1, long_key_a, 100, long_key_a, 100);
  FileMetaData* f2 = CreateFile(2, long_key_b, 100, long_key_b, 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

// Test prefix relationship: "aaa" vs "aaab"
TEST_F(BySmallestKeyTest_157, PrefixKeys_157) {
  FileMetaData* f1 = CreateFile(1, "aaa", 100, "bbb", 100);
  FileMetaData* f2 = CreateFile(2, "aaab", 100, "ccc", 100);

  EXPECT_TRUE(by_smallest_key_(f1, f2));
  EXPECT_FALSE(by_smallest_key_(f2, f1));
}

}  // namespace leveldb
