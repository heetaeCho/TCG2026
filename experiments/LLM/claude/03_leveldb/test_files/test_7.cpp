#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>
#include <cstring>

namespace leveldb {

// Default constructor tests
TEST(SliceTest_7, DefaultConstructor_EmptySlice_7) {
  Slice s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Constructor from const char* and size_t
TEST(SliceTest_7, ConstructorWithDataAndSize_7) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.data(), data);
  EXPECT_FALSE(s.empty());
}

TEST(SliceTest_7, ConstructorWithDataAndSize_PartialString_7) {
  const char* data = "hello world";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

TEST(SliceTest_7, ConstructorWithDataAndSize_ZeroLength_7) {
  const char* data = "hello";
  Slice s(data, 0);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Constructor from std::string
TEST(SliceTest_7, ConstructorFromString_7) {
  std::string str = "hello world";
  Slice s(str);
  EXPECT_EQ(s.size(), str.size());
  EXPECT_EQ(s.data(), str.data());
  EXPECT_EQ(s.ToString(), str);
}

TEST(SliceTest_7, ConstructorFromEmptyString_7) {
  std::string str;
  Slice s(str);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Constructor from const char*
TEST(SliceTest_7, ConstructorFromCString_7) {
  Slice s("hello");
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceTest_7, ConstructorFromEmptyCString_7) {
  Slice s("");
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Copy constructor
TEST(SliceTest_7, CopyConstructor_7) {
  Slice original("test data");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Assignment operator
TEST(SliceTest_7, AssignmentOperator_7) {
  Slice s1("first");
  Slice s2("second");
  s2 = s1;
  EXPECT_EQ(s2.size(), s1.size());
  EXPECT_EQ(s2.data(), s1.data());
  EXPECT_EQ(s2.ToString(), "first");
}

// data() method
TEST(SliceTest_7, DataReturnsPointerToData_7) {
  const char* raw = "raw data";
  Slice s(raw);
  EXPECT_EQ(s.data(), raw);
}

// size() method
TEST(SliceTest_7, SizeReturnsCorrectLength_7) {
  Slice s("abcde");
  EXPECT_EQ(s.size(), 5);
}

// empty() method
TEST(SliceTest_7, EmptyReturnsTrueForEmptySlice_7) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_7, EmptyReturnsFalseForNonEmptySlice_7) {
  Slice s("a");
  EXPECT_FALSE(s.empty());
}

// begin() and end()
TEST(SliceTest_7, BeginReturnsDataPointer_7) {
  const char* raw = "test";
  Slice s(raw);
  EXPECT_EQ(s.begin(), raw);
}

TEST(SliceTest_7, EndReturnsDataPlusSize_7) {
  const char* raw = "test";
  Slice s(raw);
  EXPECT_EQ(s.end(), raw + 4);
}

TEST(SliceTest_7, BeginEqualsEndForEmptySlice_7) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// operator[]
TEST(SliceTest_7, SubscriptOperatorAccessesCorrectCharacter_7) {
  Slice s("abcdef");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[5], 'f');
}

TEST(SliceTest_7, SubscriptOperatorBoundary_7) {
  Slice s("x");
  EXPECT_EQ(s[0], 'x');
}

// clear()
TEST(SliceTest_7, ClearResetsSlice_7) {
  Slice s("some data");
  EXPECT_FALSE(s.empty());
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

TEST(SliceTest_7, ClearOnAlreadyEmptySlice_7) {
  Slice s;
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// remove_prefix()
TEST(SliceTest_7, RemovePrefixRemovesNBytes_7) {
  Slice s("hello world");
  s.remove_prefix(6);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.ToString(), "world");
}

TEST(SliceTest_7, RemovePrefixZeroBytes_7) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceTest_7, RemovePrefixEntireSlice_7) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_7, RemovePrefixOneChar_7) {
  Slice s("abc");
  s.remove_prefix(1);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.ToString(), "bc");
}

// ToString()
TEST(SliceTest_7, ToStringReturnsStdString_7) {
  Slice s("hello");
  std::string result = s.ToString();
  EXPECT_EQ(result, "hello");
}

TEST(SliceTest_7, ToStringOnEmptySlice_7) {
  Slice s;
  std::string result = s.ToString();
  EXPECT_EQ(result, "");
}

TEST(SliceTest_7, ToStringWithNullBytes_7) {
  const char data[] = "he\0lo";
  Slice s(data, 5);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result, std::string(data, 5));
}

// starts_with()
TEST(SliceTest_7, StartsWithReturnsTrueForPrefix_7) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_7, StartsWithReturnsFalseForNonPrefix_7) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceTest_7, StartsWithEmptyPrefix_7) {
  Slice s("hello");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_7, StartsWithIdenticalSlice_7) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_7, StartsWithLongerPrefixReturnsFalse_7) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceTest_7, EmptySliceStartsWithEmpty_7) {
  Slice s("");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_7, EmptySliceDoesNotStartWithNonEmpty_7) {
  Slice s("");
  Slice prefix("a");
  EXPECT_FALSE(s.starts_with(prefix));
}

// compare()
TEST(SliceTest_7, CompareEqualSlices_7) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceTest_7, CompareLessThan_7) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_7, CompareGreaterThan_7) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_7, CompareShorterVsLonger_7) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_7, CompareLongerVsShorter_7) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_7, CompareEmptySlices_7) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceTest_7, CompareEmptyVsNonEmpty_7) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_7, CompareNonEmptyVsEmpty_7) {
  Slice a("a");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_7, CompareSingleCharacters_7) {
  Slice a("a");
  Slice b("b");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Interaction tests: remove_prefix then compare
TEST(SliceTest_7, RemovePrefixThenCompare_7) {
  Slice a("hello world");
  a.remove_prefix(6);
  Slice b("world");
  EXPECT_EQ(a.compare(b), 0);
}

// Slice with binary data (contains null bytes)
TEST(SliceTest_7, BinaryDataHandling_7) {
  const char data1[] = {'\0', 'a', 'b', '\0', 'c'};
  const char data2[] = {'\0', 'a', 'b', '\0', 'c'};
  Slice s1(data1, 5);
  Slice s2(data2, 5);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s1.compare(s2), 0);
}

TEST(SliceTest_7, BinaryDataDifferent_7) {
  const char data1[] = {'\0', 'a', 'b', '\0', 'c'};
  const char data2[] = {'\0', 'a', 'b', '\0', 'd'};
  Slice s1(data1, 5);
  Slice s2(data2, 5);
  EXPECT_LT(s1.compare(s2), 0);
}

// Equality operators if they exist (testing through compare)
TEST(SliceTest_7, CompareSymmetry_7) {
  Slice a("foo");
  Slice b("bar");
  int cmp1 = a.compare(b);
  int cmp2 = b.compare(a);
  // If a > b, then b < a
  if (cmp1 > 0) {
    EXPECT_LT(cmp2, 0);
  } else if (cmp1 < 0) {
    EXPECT_GT(cmp2, 0);
  } else {
    EXPECT_EQ(cmp2, 0);
  }
}

// Test clear after remove_prefix
TEST(SliceTest_7, ClearAfterRemovePrefix_7) {
  Slice s("hello world");
  s.remove_prefix(3);
  EXPECT_EQ(s.size(), 8);
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

// Multiple remove_prefix calls
TEST(SliceTest_7, MultipleRemovePrefix_7) {
  Slice s("abcdefgh");
  s.remove_prefix(2);
  EXPECT_EQ(s.ToString(), "cdefgh");
  s.remove_prefix(3);
  EXPECT_EQ(s.ToString(), "fgh");
  s.remove_prefix(3);
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

}  // namespace leveldb
