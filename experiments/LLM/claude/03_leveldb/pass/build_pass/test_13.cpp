#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>

namespace leveldb {

// ==================== compare() Tests ====================

TEST(SliceCompareTest_13, EqualSlices_13) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceCompareTest_13, FirstSliceLessThanSecond_13) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, FirstSliceGreaterThanSecond_13) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, ShorterSliceIsPrefix_13) {
  Slice a("hello");
  Slice b("helloworld");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, LongerSliceIsPrefixOfShorter_13) {
  Slice a("helloworld");
  Slice b("hello");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, BothEmpty_13) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceCompareTest_13, EmptyVsNonEmpty_13) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, NonEmptyVsEmpty_13) {
  Slice a("a");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, SingleCharEqual_13) {
  Slice a("a");
  Slice b("a");
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceCompareTest_13, SingleCharLessThan_13) {
  Slice a("a");
  Slice b("b");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, SingleCharGreaterThan_13) {
  Slice a("b");
  Slice b("a");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, CompareWithSelf_13) {
  Slice a("test");
  EXPECT_EQ(a.compare(a), 0);
}

TEST(SliceCompareTest_13, BinaryDataWithNulls_13) {
  Slice a("ab\0cd", 5);
  Slice b("ab\0ce", 5);
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, BinaryDataEqualWithNulls_13) {
  Slice a("ab\0cd", 5);
  Slice b("ab\0cd", 5);
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceCompareTest_13, BinaryDataDifferentLengthsWithNulls_13) {
  Slice a("ab\0c", 4);
  Slice b("ab\0cd", 5);
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, DifferentContentSameLengthFirstByteDiffers_13) {
  Slice a("xbc");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, DifferentContentSameLengthLastByteDiffers_13) {
  Slice a("abx");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, CompareShorterWithDifferentContent_13) {
  Slice a("b");
  Slice b("aa");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, CompareFromStdString_13) {
  std::string s1 = "apple";
  std::string s2 = "banana";
  Slice a(s1);
  Slice b(s2);
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_13, SymmetryProperty_13) {
  Slice a("abc");
  Slice b("def");
  int cmp1 = a.compare(b);
  int cmp2 = b.compare(a);
  EXPECT_LT(cmp1, 0);
  EXPECT_GT(cmp2, 0);
}

TEST(SliceCompareTest_13, TransitivityProperty_13) {
  Slice a("a");
  Slice b("b");
  Slice c("c");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_LT(b.compare(c), 0);
  EXPECT_LT(a.compare(c), 0);
}

// ==================== Constructor Tests ====================

TEST(SliceConstructorTest_13, DefaultConstructor_13) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

TEST(SliceConstructorTest_13, CStringConstructor_13) {
  Slice s("hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceConstructorTest_13, DataAndLengthConstructor_13) {
  const char* data = "hello world";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceConstructorTest_13, StdStringConstructor_13) {
  std::string str = "hello";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceConstructorTest_13, CopyConstructor_13) {
  Slice a("test");
  Slice b(a);
  EXPECT_EQ(a.compare(b), 0);
  EXPECT_EQ(a.size(), b.size());
}

// ==================== data(), size(), empty() Tests ====================

TEST(SliceAccessorTest_13, DataReturnsPointer_13) {
  const char* str = "hello";
  Slice s(str);
  EXPECT_EQ(s.data(), str);
}

TEST(SliceAccessorTest_13, SizeReturnsCorrectSize_13) {
  Slice s("hello");
  EXPECT_EQ(s.size(), 5u);
}

TEST(SliceAccessorTest_13, EmptyOnEmptySlice_13) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

TEST(SliceAccessorTest_13, EmptyOnNonEmptySlice_13) {
  Slice s("a");
  EXPECT_FALSE(s.empty());
}

// ==================== operator[] Tests ====================

TEST(SliceIndexTest_13, IndexAccess_13) {
  Slice s("hello");
  EXPECT_EQ(s[0], 'h');
  EXPECT_EQ(s[1], 'e');
  EXPECT_EQ(s[4], 'o');
}

// ==================== begin() / end() Tests ====================

TEST(SliceIteratorTest_13, BeginEndForNonEmpty_13) {
  Slice s("hello");
  EXPECT_EQ(s.end() - s.begin(), 5);
  EXPECT_EQ(*s.begin(), 'h');
}

TEST(SliceIteratorTest_13, BeginEqualsEndForEmpty_13) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// ==================== clear() Tests ====================

TEST(SliceClearTest_13, ClearMakesEmpty_13) {
  Slice s("hello");
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// ==================== remove_prefix() Tests ====================

TEST(SliceRemovePrefixTest_13, RemovePrefixReducesSize_13) {
  Slice s("hello");
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

TEST(SliceRemovePrefixTest_13, RemoveEntirePrefix_13) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_TRUE(s.empty());
}

TEST(SliceRemovePrefixTest_13, RemoveZeroPrefix_13) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// ==================== ToString() Tests ====================

TEST(SliceToStringTest_13, ToStringReturnsCorrectString_13) {
  Slice s("hello");
  std::string result = s.ToString();
  EXPECT_EQ(result, "hello");
}

TEST(SliceToStringTest_13, ToStringOnEmpty_13) {
  Slice s;
  std::string result = s.ToString();
  EXPECT_EQ(result, "");
}

TEST(SliceToStringTest_13, ToStringWithBinaryData_13) {
  std::string original("hel\0lo", 6);
  Slice s(original);
  std::string result = s.ToString();
  EXPECT_EQ(result, original);
  EXPECT_EQ(result.size(), 6u);
}

// ==================== starts_with() Tests ====================

TEST(SliceStartsWithTest_13, StartsWithTrue_13) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceStartsWithTest_13, StartsWithFalse_13) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceStartsWithTest_13, StartsWithEmptyPrefix_13) {
  Slice s("hello");
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceStartsWithTest_13, StartsWithSelf_13) {
  Slice s("hello");
  EXPECT_TRUE(s.starts_with(s));
}

TEST(SliceStartsWithTest_13, StartsWithLongerPrefix_13) {
  Slice s("hi");
  Slice prefix("high");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceStartsWithTest_13, EmptyStartsWithEmpty_13) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// ==================== Assignment operator Tests ====================

TEST(SliceAssignmentTest_13, AssignmentOperator_13) {
  Slice a("hello");
  Slice b;
  b = a;
  EXPECT_EQ(a.compare(b), 0);
  EXPECT_EQ(b.ToString(), "hello");
}

}  // namespace leveldb
