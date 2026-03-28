// File: slice_empty_test_3.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

// --------------------------
// Basic construction cases
// --------------------------

TEST(SliceTest_3, DefaultCtorIsEmpty_3) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_3, CStringCtorEmptyStringIsEmpty_3) {
  Slice s("");
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_3, CStringCtorNonEmptyIsNotEmpty_3) {
  Slice s("abc");
  EXPECT_FALSE(s.empty());
}

TEST(SliceTest_3, PointerSizeCtorZeroSizeIsEmpty_3) {
  const char* p = "abc";
  Slice s(p, 0);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_3, PointerSizeCtorNonZeroIsNotEmpty_3) {
  const char* p = "abc";
  Slice s(p, 2);
  EXPECT_FALSE(s.empty());
}

TEST(SliceTest_3, StdStringCtorEmptyIsEmpty_3) {
  std::string str;
  Slice s(str);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_3, StdStringCtorNonEmptyIsNotEmpty_3) {
  std::string str = "hello";
  Slice s(str);
  EXPECT_FALSE(s.empty());
}

// --------------------------
// State-changing operations
// --------------------------

TEST(SliceTest_3, ClearMakesSliceEmpty_3) {
  Slice s("data");
  s.clear();                 // Observable effect should be that it's empty afterwards.
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_3, RemovePrefixToZeroBecomesEmpty_3) {
  Slice s("xyz");
  s.remove_prefix(3);        // Remove exactly the current length
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_3, RemovePrefixZeroKeepsNonEmpty_3) {
  Slice s("xyz");
  s.remove_prefix(0);
  EXPECT_FALSE(s.empty());
}

// --------------------------
// Copy / assignment semantics
// --------------------------

TEST(SliceTest_3, CopyCtorPreservesEmptiness_3) {
  Slice a("");
  Slice b(a);
  EXPECT_TRUE(a.empty());
  EXPECT_TRUE(b.empty());

  Slice c("q");
  Slice d(c);
  EXPECT_FALSE(c.empty());
  EXPECT_FALSE(d.empty());
}

TEST(SliceTest_3, CopyAssignmentPreservesEmptiness_3) {
  Slice a("x");
  Slice b;
  EXPECT_TRUE(b.empty());
  b = a;
  EXPECT_FALSE(b.empty());

  Slice c;
  a = c;
  EXPECT_TRUE(a.empty());
}
