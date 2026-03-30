// slice_size_test_2.cc
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>

using leveldb::Slice;

class SliceTest_2 : public ::testing::Test {};

// [Normal] Default-constructed slice has size 0
TEST(SliceTest_2, DefaultConstructedIsEmpty_2) {
  Slice s;
  EXPECT_EQ(s.size(), static_cast<size_t>(0));
}

// [Normal] Constructed from C string computes length up to first '\0'
TEST(SliceTest_2, FromCStringComputesLength_2) {
  Slice s("hello");
  EXPECT_EQ(s.size(), static_cast<size_t>(5));
}

// [Boundary] Constructed from empty C string has size 0
TEST(SliceTest_2, FromEmptyCString_2) {
  Slice s("");
  EXPECT_EQ(s.size(), static_cast<size_t>(0));
}

// [Normal] Constructed from (ptr, len) respects explicit length (even with embedded nulls)
TEST(SliceTest_2, FromPtrLenRespectsExplicitLength_2) {
  const char buf[] = {'a', '\0', 'b', 'c', 'd'};
  Slice s(buf, sizeof(buf)); // 5 bytes, includes embedded '\0'
  EXPECT_EQ(s.size(), static_cast<size_t>(5));
}

// [Normal] Constructed from std::string matches string size
TEST(SliceTest_2, FromStdStringMatchesSize_2) {
  std::string str = "leveldb";
  Slice s(str);
  EXPECT_EQ(s.size(), str.size());
}

// [Normal] Copy construction preserves size
TEST(SliceTest_2, CopyConstructorPreservesSize_2) {
  Slice original("abcde");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
}

// [Normal] Copy assignment preserves size
TEST(SliceTest_2, AssignmentPreservesSize_2) {
  Slice a("left");
  Slice b("rightside");
  a = b;
  EXPECT_EQ(a.size(), b.size());
}

// [Boundary] clear() results in size 0 (observable via public API)
TEST(SliceTest_2, ClearSetsSizeToZero_2) {
  Slice s("data");
  s.clear();
  EXPECT_EQ(s.size(), static_cast<size_t>(0));
}

// [Boundary] remove_prefix(0) leaves size unchanged
TEST(SliceTest_2, RemovePrefixZeroKeepsSize_2) {
  Slice s("prefix");
  const size_t before = s.size();
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), before);
}

// [Boundary] remove_prefix(n) reduces size by n (for n <= size)
TEST(SliceTest_2, RemovePrefixReducesSize_2) {
  Slice s("hello");
  s.remove_prefix(2);  // "llo"
  EXPECT_EQ(s.size(), static_cast<size_t>(3));
}

// [Boundary] remove_prefix(size) makes it empty
TEST(SliceTest_2, RemovePrefixAllMakesEmpty_2) {
  Slice s("xyz");
  s.remove_prefix(s.size());
  EXPECT_EQ(s.size(), static_cast<size_t>(0));
}

// [Normal] Distance between begin() and end() equals size()
TEST(SliceTest_2, BeginEndDistanceEqualsSize_2) {
  Slice s("distance");
  ASSERT_NE(s.begin(), nullptr);
  ASSERT_NE(s.end(), nullptr);
  EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), s.size());
}
