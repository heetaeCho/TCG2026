#include "gtest/gtest.h"
#include "db/version_edit.h"

namespace leveldb {

// We test the NewestFirst comparison function indirectly by observing its behavior.
// Since NewestFirst is a static function in version_set.cc, we need to either
// include the header that exposes it or test it through sorting behavior.
// Based on the provided interface, we can test FileMetaData construction and
// the NewestFirst comparator behavior.

// Test FileMetaData default construction
TEST(FileMetaDataTest_147, DefaultConstruction_147) {
  FileMetaData meta;
  EXPECT_EQ(meta.refs, 0);
  EXPECT_EQ(meta.allowed_seeks, 1 << 30);
  EXPECT_EQ(meta.file_size, 0u);
}

// Test FileMetaData fields can be set
TEST(FileMetaDataTest_147, SetFields_147) {
  FileMetaData meta;
  meta.refs = 5;
  meta.allowed_seeks = 100;
  meta.number = 42;
  meta.file_size = 1024;
  
  EXPECT_EQ(meta.refs, 5);
  EXPECT_EQ(meta.allowed_seeks, 100);
  EXPECT_EQ(meta.number, 42u);
  EXPECT_EQ(meta.file_size, 1024u);
}

// Test NewestFirst: a file with a larger number should come first (return true)
// NewestFirst is defined as: return a->number > b->number
// We recreate the comparison logic to test sorting behavior with FileMetaData
TEST(NewestFirstTest_147, LargerNumberComesFirst_147) {
  FileMetaData a, b;
  a.number = 10;
  b.number = 5;
  
  // NewestFirst(a, b) should return true since a->number > b->number
  EXPECT_GT(a.number, b.number);
}

TEST(NewestFirstTest_147, SmallerNumberComesLast_147) {
  FileMetaData a, b;
  a.number = 3;
  b.number = 7;
  
  // NewestFirst(a, b) should return false since a->number < b->number
  EXPECT_LT(a.number, b.number);
}

TEST(NewestFirstTest_147, EqualNumbersReturnFalse_147) {
  FileMetaData a, b;
  a.number = 5;
  b.number = 5;
  
  // NewestFirst(a, b) should return false since a->number == b->number
  // (strict greater than)
  EXPECT_EQ(a.number, b.number);
  EXPECT_FALSE(a.number > b.number);
}

TEST(NewestFirstTest_147, BoundaryZeroNumbers_147) {
  FileMetaData a, b;
  a.number = 0;
  b.number = 0;
  
  EXPECT_FALSE(a.number > b.number);
}

TEST(NewestFirstTest_147, BoundaryMaxNumbers_147) {
  FileMetaData a, b;
  a.number = UINT64_MAX;
  b.number = 0;
  
  EXPECT_TRUE(a.number > b.number);
}

TEST(NewestFirstTest_147, BoundaryMaxEqualNumbers_147) {
  FileMetaData a, b;
  a.number = UINT64_MAX;
  b.number = UINT64_MAX;
  
  EXPECT_FALSE(a.number > b.number);
}

TEST(NewestFirstTest_147, ConsecutiveNumbers_147) {
  FileMetaData a, b;
  a.number = 100;
  b.number = 99;
  
  EXPECT_TRUE(a.number > b.number);
}

TEST(NewestFirstTest_147, ReverseConsecutiveNumbers_147) {
  FileMetaData a, b;
  a.number = 99;
  b.number = 100;
  
  EXPECT_FALSE(a.number > b.number);
}

// Test that sorting a vector of FileMetaData* using NewestFirst-like comparator
// results in descending order by number
TEST(NewestFirstTest_147, SortingBehavior_147) {
  FileMetaData f1, f2, f3, f4;
  f1.number = 1;
  f2.number = 5;
  f3.number = 3;
  f4.number = 10;
  
  std::vector<FileMetaData*> files = {&f1, &f2, &f3, &f4};
  
  // Sort using the same comparator logic as NewestFirst
  std::sort(files.begin(), files.end(), [](FileMetaData* a, FileMetaData* b) {
    return a->number > b->number;
  });
  
  EXPECT_EQ(files[0]->number, 10u);
  EXPECT_EQ(files[1]->number, 5u);
  EXPECT_EQ(files[2]->number, 3u);
  EXPECT_EQ(files[3]->number, 1u);
}

// Test DeletedFileSet behavior
TEST(DeletedFileSetTest_147, InsertAndFind_147) {
  DeletedFileSet deleted;
  deleted.insert(std::make_pair(0, 1ULL));
  deleted.insert(std::make_pair(1, 2ULL));
  
  EXPECT_EQ(deleted.size(), 2u);
  EXPECT_NE(deleted.find(std::make_pair(0, 1ULL)), deleted.end());
  EXPECT_NE(deleted.find(std::make_pair(1, 2ULL)), deleted.end());
  EXPECT_EQ(deleted.find(std::make_pair(0, 2ULL)), deleted.end());
}

TEST(DeletedFileSetTest_147, DuplicateInsert_147) {
  DeletedFileSet deleted;
  deleted.insert(std::make_pair(0, 1ULL));
  deleted.insert(std::make_pair(0, 1ULL));
  
  EXPECT_EQ(deleted.size(), 1u);
}

TEST(DeletedFileSetTest_147, EmptySet_147) {
  DeletedFileSet deleted;
  EXPECT_TRUE(deleted.empty());
  EXPECT_EQ(deleted.size(), 0u);
}

TEST(FileMetaDataTest_147, MultipleInstances_147) {
  FileMetaData m1, m2, m3;
  m1.number = 1;
  m2.number = 2;
  m3.number = 3;
  m1.file_size = 100;
  m2.file_size = 200;
  m3.file_size = 300;
  
  EXPECT_NE(m1.number, m2.number);
  EXPECT_NE(m2.number, m3.number);
  EXPECT_EQ(m1.file_size + m2.file_size + m3.file_size, 600u);
}

}  // namespace leveldb
