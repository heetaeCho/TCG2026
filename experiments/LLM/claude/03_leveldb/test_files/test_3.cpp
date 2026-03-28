#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>
#include <cstring>

namespace leveldb {

// Test default constructor
TEST(SliceTest_3, DefaultConstructorCreatesEmptySlice_3) {
  Slice s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
  EXPECT_STREQ(s.data(), "");
}

// Test constructor from const char* and size_t
TEST(SliceTest_3, ConstructFromCharPtrAndSize_3) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

// Test constructor from std::string
TEST(SliceTest_3, ConstructFromStdString_3) {
  std::string str = "world";
  Slice s(str);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

// Test constructor from const char* (null-terminated)
TEST(SliceTest_3, ConstructFromCString_3) {
  Slice s("test");
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(s.ToString(), "test");
}

// Test constructor with empty string
TEST(SliceTest_3, ConstructFromEmptyCString_3) {
  Slice s("");
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test constructor from empty std::string
TEST(SliceTest_3, ConstructFromEmptyStdString_3) {
  std::string str;
  Slice s(str);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test constructor with zero size
TEST(SliceTest_3, ConstructWithZeroSize_3) {
  Slice s("data", 0);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test copy constructor
TEST(SliceTest_3, CopyConstructor_3) {
  Slice original("copy me");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.ToString(), original.ToString());
  EXPECT_EQ(copy.data(), original.data());
}

// Test copy assignment
TEST(SliceTest_3, CopyAssignment_3) {
  Slice original("assign me");
  Slice assigned;
  assigned = original;
  EXPECT_EQ(assigned.size(), original.size());
  EXPECT_EQ(assigned.ToString(), original.ToString());
}

// Test data() returns correct pointer
TEST(SliceTest_3, DataReturnsCorrectPointer_3) {
  const char* raw = "pointer test";
  Slice s(raw, 12);
  EXPECT_EQ(s.data(), raw);
}

// Test size() returns correct value
TEST(SliceTest_3, SizeReturnsCorrectValue_3) {
  Slice s("12345");
  EXPECT_EQ(s.size(), 5u);
}

// Test empty() on non-empty slice
TEST(SliceTest_3, EmptyReturnsFalseForNonEmpty_3) {
  Slice s("x");
  EXPECT_FALSE(s.empty());
}

// Test empty() on empty slice
TEST(SliceTest_3, EmptyReturnsTrueForEmpty_3) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

// Test operator[]
TEST(SliceTest_3, OperatorIndexAccessesCorrectCharacter_3) {
  Slice s("abcdef");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[5], 'f');
}

// Test operator[] at boundary
TEST(SliceTest_3, OperatorIndexAtLastPosition_3) {
  Slice s("z");
  EXPECT_EQ(s[0], 'z');
}

// Test ToString()
TEST(SliceTest_3, ToStringReturnsCorrectString_3) {
  Slice s("hello world", 11);
  EXPECT_EQ(s.ToString(), "hello world");
}

// Test ToString() on empty slice
TEST(SliceTest_3, ToStringOnEmptySlice_3) {
  Slice s;
  EXPECT_EQ(s.ToString(), "");
}

// Test ToString() with partial data
TEST(SliceTest_3, ToStringWithPartialData_3) {
  Slice s("hello world", 5);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test clear()
TEST(SliceTest_3, ClearMakesSliceEmpty_3) {
  Slice s("some data");
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test remove_prefix()
TEST(SliceTest_3, RemovePrefixReducesSize_3) {
  Slice s("hello");
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

// Test remove_prefix() with zero
TEST(SliceTest_3, RemovePrefixZeroNoChange_3) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test remove_prefix() entire size
TEST(SliceTest_3, RemovePrefixEntireSize_3) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test starts_with() positive case
TEST(SliceTest_3, StartsWithReturnsTrueForPrefix_3) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() negative case
TEST(SliceTest_3, StartsWithReturnsFalseForNonPrefix_3) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with() empty prefix
TEST(SliceTest_3, StartsWithEmptyPrefixReturnsTrue_3) {
  Slice s("hello");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() when prefix is same as slice
TEST(SliceTest_3, StartsWithSameSliceReturnsTrue_3) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() when prefix is longer than slice
TEST(SliceTest_3, StartsWithLongerPrefixReturnsFalse_3) {
  Slice s("hi");
  Slice prefix("hi there");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with() on empty slice with empty prefix
TEST(SliceTest_3, EmptySliceStartsWithEmptyPrefix_3) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() on empty slice with non-empty prefix
TEST(SliceTest_3, EmptySliceDoesNotStartWithNonEmptyPrefix_3) {
  Slice s;
  Slice prefix("a");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test compare() equal slices
TEST(SliceTest_3, CompareEqualSlicesReturnsZero_3) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare() less than
TEST(SliceTest_3, CompareLessThanReturnsNegative_3) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare() greater than
TEST(SliceTest_3, CompareGreaterThanReturnsPositive_3) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare() with different lengths, same prefix
TEST(SliceTest_3, CompareShorterSliceIsLess_3) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare() longer vs shorter
TEST(SliceTest_3, CompareLongerSliceIsGreater_3) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare() empty slices
TEST(SliceTest_3, CompareEmptySlicesAreEqual_3) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare() empty vs non-empty
TEST(SliceTest_3, CompareEmptyLessThanNonEmpty_3) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare() non-empty vs empty
TEST(SliceTest_3, CompareNonEmptyGreaterThanEmpty_3) {
  Slice a("a");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
}

// Test begin() and end()
TEST(SliceTest_3, BeginEndIterators_3) {
  const char* raw = "test";
  Slice s(raw, 4);
  EXPECT_EQ(s.begin(), raw);
  EXPECT_EQ(s.end(), raw + 4);
}

// Test begin() and end() on empty slice
TEST(SliceTest_3, BeginEqualsEndForEmptySlice_3) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// Test that data with embedded null bytes works correctly
TEST(SliceTest_3, SliceWithEmbeddedNullBytes_3) {
  std::string str("hel\0lo", 6);
  Slice s(str);
  EXPECT_EQ(s.size(), 6u);
  EXPECT_EQ(s[3], '\0');
  EXPECT_EQ(s[4], 'l');
  EXPECT_EQ(s.ToString(), str);
}

// Test compare with embedded null bytes
TEST(SliceTest_3, CompareWithEmbeddedNullBytes_3) {
  std::string s1("ab\0c", 4);
  std::string s2("ab\0d", 4);
  Slice a(s1);
  Slice b(s2);
  EXPECT_LT(a.compare(b), 0);
}

// Test single character slice
TEST(SliceTest_3, SingleCharacterSlice_3) {
  Slice s("x");
  EXPECT_EQ(s.size(), 1u);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s[0], 'x');
  EXPECT_EQ(s.ToString(), "x");
}

// Test multiple remove_prefix calls
TEST(SliceTest_3, MultipleRemovePrefixCalls_3) {
  Slice s("abcdef");
  s.remove_prefix(1);
  EXPECT_EQ(s.ToString(), "bcdef");
  s.remove_prefix(2);
  EXPECT_EQ(s.ToString(), "def");
  s.remove_prefix(3);
  EXPECT_TRUE(s.empty());
}

// Test clear then reuse via assignment
TEST(SliceTest_3, ClearThenAssign_3) {
  Slice s("hello");
  s.clear();
  EXPECT_TRUE(s.empty());
  s = Slice("world");
  EXPECT_EQ(s.ToString(), "world");
  EXPECT_EQ(s.size(), 5u);
}

// Test begin/end can be used for range iteration
TEST(SliceTest_3, RangeIteration_3) {
  Slice s("abc");
  std::string result;
  for (const char* p = s.begin(); p != s.end(); ++p) {
    result += *p;
  }
  EXPECT_EQ(result, "abc");
}

}  // namespace leveldb
