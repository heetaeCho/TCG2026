#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include "leveldb/slice.h"

namespace leveldb {

// Default constructor tests
TEST(SliceTest_1, DefaultConstructorCreatesEmptySlice_1) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Constructor from const char* and size_t
TEST(SliceTest_1, ConstructFromCharPtrAndSize_1) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
  EXPECT_FALSE(s.empty());
}

TEST(SliceTest_1, ConstructFromCharPtrAndSizeIncludingNulls_1) {
  const char data[] = "he\0lo";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s[2], '\0');
  EXPECT_EQ(s[3], 'l');
}

// Constructor from std::string
TEST(SliceTest_1, ConstructFromStdString_1) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

TEST(SliceTest_1, ConstructFromEmptyStdString_1) {
  std::string str;
  Slice s(str);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Constructor from const char*
TEST(SliceTest_1, ConstructFromCString_1) {
  Slice s("test");
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(s.ToString(), "test");
}

TEST(SliceTest_1, ConstructFromEmptyCString_1) {
  Slice s("");
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Copy constructor
TEST(SliceTest_1, CopyConstructor_1) {
  Slice original("copy_me");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.ToString(), original.ToString());
  EXPECT_EQ(copy.data(), original.data());
}

// Assignment operator
TEST(SliceTest_1, AssignmentOperator_1) {
  Slice a("first");
  Slice b("second");
  b = a;
  EXPECT_EQ(b.size(), a.size());
  EXPECT_EQ(b.ToString(), "first");
  EXPECT_EQ(b.data(), a.data());
}

// data()
TEST(SliceTest_1, DataReturnsCorrectPointer_1) {
  const char* raw = "rawdata";
  Slice s(raw, 7);
  EXPECT_EQ(s.data(), raw);
}

// size()
TEST(SliceTest_1, SizeReturnsCorrectValue_1) {
  Slice s("abcdef");
  EXPECT_EQ(s.size(), 6u);
}

// empty()
TEST(SliceTest_1, EmptyReturnsTrueForEmptySlice_1) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_1, EmptyReturnsFalseForNonEmptySlice_1) {
  Slice s("notempty");
  EXPECT_FALSE(s.empty());
}

// begin() and end()
TEST(SliceTest_1, BeginEqualsData_1) {
  Slice s("begin");
  EXPECT_EQ(s.begin(), s.data());
}

TEST(SliceTest_1, EndEqualsDataPlusSize_1) {
  Slice s("range");
  EXPECT_EQ(s.end(), s.data() + s.size());
}

TEST(SliceTest_1, BeginEqualsEndForEmptySlice_1) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// operator[]
TEST(SliceTest_1, IndexOperatorReturnsCorrectChar_1) {
  Slice s("abcde");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[4], 'e');
}

TEST(SliceTest_1, IndexOperatorFirstAndLastChar_1) {
  Slice s("xyz");
  EXPECT_EQ(s[0], 'x');
  EXPECT_EQ(s[2], 'z');
}

// clear()
TEST(SliceTest_1, ClearMakesSliceEmpty_1) {
  Slice s("notempty");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

TEST(SliceTest_1, ClearOnAlreadyEmptySlice_1) {
  Slice s;
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// remove_prefix()
TEST(SliceTest_1, RemovePrefixReducesSize_1) {
  Slice s("hello");
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

TEST(SliceTest_1, RemovePrefixOfZero_1) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceTest_1, RemovePrefixEntireSlice_1) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_1, RemovePrefixAdvancesDataPointer_1) {
  const char* original = "abcdef";
  Slice s(original, 6);
  s.remove_prefix(3);
  EXPECT_EQ(s.data(), original + 3);
  EXPECT_EQ(s[0], 'd');
}

// ToString()
TEST(SliceTest_1, ToStringReturnsCorrectString_1) {
  Slice s("convert");
  std::string result = s.ToString();
  EXPECT_EQ(result, "convert");
}

TEST(SliceTest_1, ToStringOnEmptySlice_1) {
  Slice s;
  std::string result = s.ToString();
  EXPECT_EQ(result, "");
}

TEST(SliceTest_1, ToStringPreservesEmbeddedNulls_1) {
  const char data[] = "ab\0cd";
  Slice s(data, 5);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result[2], '\0');
  EXPECT_EQ(result[3], 'c');
}

// starts_with()
TEST(SliceTest_1, StartsWithReturnsTrueForMatchingPrefix_1) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_1, StartsWithReturnsFalseForNonMatchingPrefix_1) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceTest_1, StartsWithReturnsTrueForEmptyPrefix_1) {
  Slice s("anything");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_1, StartsWithReturnsTrueForSameSlice_1) {
  Slice s("exact");
  Slice prefix("exact");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_1, StartsWithReturnsFalseWhenPrefixLonger_1) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceTest_1, EmptySliceStartsWithEmpty_1) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// compare()
TEST(SliceTest_1, CompareEqualSlicesReturnsZero_1) {
  Slice a("abc");
  Slice b("abc");
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceTest_1, CompareLessThanReturnsNegative_1) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_1, CompareGreaterThanReturnsPositive_1) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_1, CompareShorterSliceIsLess_1) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_1, CompareLongerSliceIsGreater_1) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_1, CompareEmptySlices_1) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceTest_1, CompareEmptyWithNonEmpty_1) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

TEST(SliceTest_1, CompareSingleCharSlices_1) {
  Slice a("a");
  Slice b("b");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Equality and inequality operators (if they exist — these are commonly defined inline)
TEST(SliceTest_1, EqualityOperator_1) {
  Slice a("same");
  Slice b("same");
  EXPECT_TRUE(a == b);
}

TEST(SliceTest_1, InequalityOperator_1) {
  Slice a("one");
  Slice b("two");
  EXPECT_TRUE(a != b);
}

TEST(SliceTest_1, EqualityWithDifferentLengths_1) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_FALSE(a == b);
}

// Practical usage tests
TEST(SliceTest_1, SliceFromSubstring_1) {
  std::string str = "hello world";
  Slice s(str.data() + 6, 5);
  EXPECT_EQ(s.ToString(), "world");
  EXPECT_EQ(s.size(), 5u);
}

TEST(SliceTest_1, MultipleRemovePrefixCalls_1) {
  Slice s("abcdefgh");
  s.remove_prefix(2);
  EXPECT_EQ(s.ToString(), "cdefgh");
  s.remove_prefix(3);
  EXPECT_EQ(s.ToString(), "fgh");
  s.remove_prefix(3);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_1, SlicePointsToOriginalData_1) {
  std::string str = "original";
  Slice s(str);
  EXPECT_EQ(s.data(), str.data());
}

}  // namespace leveldb
