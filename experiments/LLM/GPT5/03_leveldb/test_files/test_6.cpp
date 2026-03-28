// slice_operator_index_tests_6.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

// --- Normal operation ---

TEST(SliceOperatorTest_6, AccessWithinBounds_CString_6) {
  Slice s("hello");
  EXPECT_EQ(s[0], 'h');
  EXPECT_EQ(s[1], 'e');
  EXPECT_EQ(s[2], 'l');
  EXPECT_EQ(s[3], 'l');
  EXPECT_EQ(s[4], 'o');
}

TEST(SliceOperatorTest_6, AccessWithinBounds_StdString_6) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s[0], 'w');
  EXPECT_EQ(s[4], 'd');
}

TEST(SliceOperatorTest_6, AccessWithinBounds_PointerLength_6) {
  const char data[] = {'x', 'y', 'z'};
  Slice s(data, 3);
  EXPECT_EQ(s[0], 'x');
  EXPECT_EQ(s[1], 'y');
  EXPECT_EQ(s[2], 'z');
}

TEST(SliceOperatorTest_6, AccessWithEmbeddedNulls_6) {
  const char data[] = {'a', '\0', 'b', 'c'};
  Slice s(data, 4);
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], '\0');   // ensure operator[] returns stored byte even if '\0'
  EXPECT_EQ(s[2], 'b');
  EXPECT_EQ(s[3], 'c');
}

TEST(SliceOperatorTest_6, ConstOperatorIndex_6) {
  const std::string str = "const";
  const Slice s(str);
  EXPECT_EQ(s[0], 'c');
  EXPECT_EQ(s[4], 't');
}

// --- Boundary conditions ---

TEST(SliceOperatorTest_6, FirstAndLastIndex_6) {
  Slice s("edge");
  ASSERT_GE(s.size(), static_cast<size_t>(1));
  EXPECT_EQ(s[0], 'e');
  EXPECT_EQ(s[s.size() - 1], 'e');
}

// --- Exceptional / error cases (observable via assert) ---

#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG  // assert() must be active
TEST(SliceOperatorDeathTest_6, IndexEqualToSizeTriggersAssert_6) {
  Slice s("abc");
  // Accessing s[3] is out-of-bounds for "abc" (size() == 3)
  ASSERT_DEATH({ (void)s[s.size()]; }, ".*");
}

TEST(SliceOperatorDeathTest_6, IndexGreaterThanSizeTriggersAssert_6) {
  Slice s("abc");
  ASSERT_DEATH({ (void)s[100]; }, ".*");
}

TEST(SliceOperatorDeathTest_6, AnyAccessOnEmptySliceTriggersAssert_6) {
  Slice s("");  // empty
  ASSERT_EQ(s.size(), 0u);
  ASSERT_DEATH({ (void)s[0]; }, ".*");
}
#else
// If compiled with NDEBUG, asserts are disabled. Keep placeholders so suite passes.
TEST(SliceOperatorDeathTest_6, SkippedInReleaseBuild_IndexEqualToSize_6) { GTEST_SKIP() << "Assertions disabled (NDEBUG)"; }
TEST(SliceOperatorDeathTest_6, SkippedInReleaseBuild_IndexGreaterThanSize_6) { GTEST_SKIP() << "Assertions disabled (NDEBUG)"; }
TEST(SliceOperatorDeathTest_6, SkippedInReleaseBuild_Empty_6) { GTEST_SKIP() << "Assertions disabled (NDEBUG)"; }
#endif  // NDEBUG
#endif  // GTEST_HAS_DEATH_TEST
