#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>

namespace leveldb {

// ==================== starts_with tests ====================

TEST(SliceStartsWithTest_10, EmptySliceStartsWithEmptySlice_10) {
  Slice a;
  Slice b;
  EXPECT_TRUE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, NonEmptySliceStartsWithEmptySlice_10) {
  Slice a("hello");
  Slice b;
  EXPECT_TRUE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, EmptySliceDoesNotStartWithNonEmpty_10) {
  Slice a;
  Slice b("hello");
  EXPECT_FALSE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, SliceStartsWithItself_10) {
  Slice a("hello");
  EXPECT_TRUE(a.starts_with(a));
}

TEST(SliceStartsWithTest_10, SliceStartsWithPrefix_10) {
  Slice a("hello world");
  Slice b("hello");
  EXPECT_TRUE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, SliceDoesNotStartWithNonPrefix_10) {
  Slice a("hello world");
  Slice b("world");
  EXPECT_FALSE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, SliceDoesNotStartWithLongerSlice_10) {
  Slice a("hel");
  Slice b("hello");
  EXPECT_FALSE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, SingleCharacterPrefix_10) {
  Slice a("abc");
  Slice b("a");
  EXPECT_TRUE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, SingleCharacterMismatch_10) {
  Slice a("abc");
  Slice b("b");
  EXPECT_FALSE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, ExactMatch_10) {
  Slice a("exact");
  Slice b("exact");
  EXPECT_TRUE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, BinaryDataPrefix_10) {
  const char data1[] = {'\0', 'a', 'b', 'c'};
  const char data2[] = {'\0', 'a'};
  Slice a(data1, 4);
  Slice b(data2, 2);
  EXPECT_TRUE(a.starts_with(b));
}

TEST(SliceStartsWithTest_10, BinaryDataMismatch_10) {
  const char data1[] = {'\0', 'a', 'b', 'c'};
  const char data2[] = {'\0', 'b'};
  Slice a(data1, 4);
  Slice b(data2, 2);
  EXPECT_FALSE(a.starts_with(b));
}

// ==================== Constructor tests ====================

TEST(SliceConstructorTest_10, DefaultConstructor_10) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

TEST(SliceConstructorTest_10, CStringConstructor_10) {
  Slice s("hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

TEST(SliceConstructorTest_10, StdStringConstructor_10) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

TEST(SliceConstructorTest_10, DataAndSizeConstructor_10) {
  const char* data = "hello world";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceConstructorTest_10, CopyConstructor_10) {
  Slice original("test");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

TEST(SliceConstructorTest_10, AssignmentOperator_10) {
  Slice a("first");
  Slice b("second");
  a = b;
  EXPECT_EQ(a.ToString(), "second");
  EXPECT_EQ(a.size(), b.size());
}

// ==================== data(), size(), empty() tests ====================

TEST(SliceAccessorTest_10, DataReturnsPointer_10) {
  const char* str = "test";
  Slice s(str);
  EXPECT_EQ(s.data(), str);
}

TEST(SliceAccessorTest_10, SizeReturnsCorrectLength_10) {
  Slice s("abcdef");
  EXPECT_EQ(s.size(), 6u);
}

TEST(SliceAccessorTest_10, EmptyReturnsTrueForDefault_10) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

TEST(SliceAccessorTest_10, EmptyReturnsFalseForNonEmpty_10) {
  Slice s("x");
  EXPECT_FALSE(s.empty());
}

TEST(SliceAccessorTest_10, EmptyReturnsTrueForZeroLength_10) {
  Slice s("data", 0);
  EXPECT_TRUE(s.empty());
}

// ==================== operator[] tests ====================

TEST(SliceIndexTest_10, IndexOperatorReturnsCorrectChar_10) {
  Slice s("abcdef");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[5], 'f');
}

// ==================== begin() and end() tests ====================

TEST(SliceIteratorTest_10, BeginAndEndForNonEmpty_10) {
  Slice s("hello");
  EXPECT_EQ(s.end() - s.begin(), 5);
  EXPECT_EQ(*s.begin(), 'h');
}

TEST(SliceIteratorTest_10, BeginEqualsEndForEmpty_10) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// ==================== ToString() tests ====================

TEST(SliceToStringTest_10, ToStringReturnsCorrectString_10) {
  Slice s("hello");
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceToStringTest_10, ToStringForEmptySlice_10) {
  Slice s;
  EXPECT_EQ(s.ToString(), "");
}

TEST(SliceToStringTest_10, ToStringWithBinaryData_10) {
  const char data[] = {'a', '\0', 'b'};
  Slice s(data, 3);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], 'a');
  EXPECT_EQ(result[1], '\0');
  EXPECT_EQ(result[2], 'b');
}

// ==================== clear() tests ====================

TEST(SliceClearTest_10, ClearMakesSliceEmpty_10) {
  Slice s("hello");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// ==================== remove_prefix() tests ====================

TEST(SliceRemovePrefixTest_10, RemovePrefixReducesSize_10) {
  Slice s("hello world");
  s.remove_prefix(6);
  EXPECT_EQ(s.ToString(), "world");
  EXPECT_EQ(s.size(), 5u);
}

TEST(SliceRemovePrefixTest_10, RemovePrefixZero_10) {
  Slice s("test");
  s.remove_prefix(0);
  EXPECT_EQ(s.ToString(), "test");
}

TEST(SliceRemovePrefixTest_10, RemovePrefixEntireLength_10) {
  Slice s("test");
  s.remove_prefix(4);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// ==================== compare() tests ====================

TEST(SliceCompareTest_10, EqualSlicesCompareToZero_10) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceCompareTest_10, LessThanSlice_10) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_10, GreaterThanSlice_10) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_10, ShorterSliceIsLessThanLonger_10) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_10, LongerSliceIsGreaterThanShorter_10) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceCompareTest_10, EmptySlicesAreEqual_10) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceCompareTest_10, EmptyIsLessThanNonEmpty_10) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceCompareTest_10, NonEmptyIsGreaterThanEmpty_10) {
  Slice a("a");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
}

}  // namespace leveldb
