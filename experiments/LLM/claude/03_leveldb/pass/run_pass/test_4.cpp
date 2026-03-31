#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>
#include <cstring>

namespace leveldb {

// Test default constructor
TEST(SliceTest_4, DefaultConstructorCreatesEmptySlice_4) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test constructor from const char* and size_t
TEST(SliceTest_4, ConstructFromCharPtrAndSize_4) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.data(), data);
  EXPECT_FALSE(s.empty());
}

// Test constructor from std::string
TEST(SliceTest_4, ConstructFromString_4) {
  std::string str = "hello world";
  Slice s(str);
  EXPECT_EQ(s.size(), str.size());
  EXPECT_EQ(s.data(), str.data());
  EXPECT_FALSE(s.empty());
}

// Test constructor from const char* (null-terminated)
TEST(SliceTest_4, ConstructFromNullTerminatedCharPtr_4) {
  const char* data = "test";
  Slice s(data);
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(s.data(), data);
}

// Test empty string constructor
TEST(SliceTest_4, ConstructFromEmptyString_4) {
  std::string str = "";
  Slice s(str);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test empty const char* constructor
TEST(SliceTest_4, ConstructFromEmptyCharPtr_4) {
  const char* data = "";
  Slice s(data);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test data() returns correct pointer
TEST(SliceTest_4, DataReturnsCorrectPointer_4) {
  const char* raw = "abcdef";
  Slice s(raw, 6);
  EXPECT_EQ(s.data(), raw);
}

// Test size() returns correct value
TEST(SliceTest_4, SizeReturnsCorrectValue_4) {
  Slice s("abc", 3);
  EXPECT_EQ(s.size(), 3u);
}

// Test empty() on non-empty slice
TEST(SliceTest_4, EmptyReturnsFalseForNonEmptySlice_4) {
  Slice s("a", 1);
  EXPECT_FALSE(s.empty());
}

// Test empty() on empty slice
TEST(SliceTest_4, EmptyReturnsTrueForEmptySlice_4) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

// Test operator[] access
TEST(SliceTest_4, OperatorBracketAccessesCorrectCharacter_4) {
  Slice s("hello", 5);
  EXPECT_EQ(s[0], 'h');
  EXPECT_EQ(s[1], 'e');
  EXPECT_EQ(s[2], 'l');
  EXPECT_EQ(s[3], 'l');
  EXPECT_EQ(s[4], 'o');
}

// Test operator[] at boundary
TEST(SliceTest_4, OperatorBracketAtLastIndex_4) {
  Slice s("xyz", 3);
  EXPECT_EQ(s[2], 'z');
}

// Test clear()
TEST(SliceTest_4, ClearMakesSliceEmpty_4) {
  Slice s("hello", 5);
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test remove_prefix
TEST(SliceTest_4, RemovePrefixReducesSizeAndAdvancesData_4) {
  const char* data = "hello";
  Slice s(data, 5);
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.data(), data + 2);
  EXPECT_EQ(s[0], 'l');
}

// Test remove_prefix with zero
TEST(SliceTest_4, RemovePrefixZeroNoChange_4) {
  const char* data = "hello";
  Slice s(data, 5);
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.data(), data);
}

// Test remove_prefix entire slice
TEST(SliceTest_4, RemovePrefixEntireSlice_4) {
  Slice s("hello", 5);
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test ToString
TEST(SliceTest_4, ToStringReturnsCorrectString_4) {
  Slice s("hello", 5);
  std::string result = s.ToString();
  EXPECT_EQ(result, "hello");
}

// Test ToString on empty slice
TEST(SliceTest_4, ToStringOnEmptySlice_4) {
  Slice s;
  std::string result = s.ToString();
  EXPECT_EQ(result, "");
}

// Test ToString with embedded null
TEST(SliceTest_4, ToStringWithEmbeddedNull_4) {
  const char data[] = "he\0lo";
  Slice s(data, 5);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result[2], '\0');
  EXPECT_EQ(result[3], 'l');
}

// Test starts_with returns true
TEST(SliceTest_4, StartsWithReturnsTrueForPrefix_4) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with returns false
TEST(SliceTest_4, StartsWithReturnsFalseForNonPrefix_4) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with with empty prefix
TEST(SliceTest_4, StartsWithEmptyPrefixReturnsTrue_4) {
  Slice s("hello");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with with same slice
TEST(SliceTest_4, StartsWithSameSliceReturnsTrue_4) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with when prefix is longer
TEST(SliceTest_4, StartsWithLongerPrefixReturnsFalse_4) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test compare equal slices
TEST(SliceTest_4, CompareEqualSlicesReturnsZero_4) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare less than
TEST(SliceTest_4, CompareLessThanReturnsNegative_4) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare greater than
TEST(SliceTest_4, CompareGreaterThanReturnsPositive_4) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare with different lengths, same prefix
TEST(SliceTest_4, CompareShorterSliceIsLessThan_4) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare with different lengths, same prefix (reverse)
TEST(SliceTest_4, CompareLongerSliceIsGreaterThan_4) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare empty slices
TEST(SliceTest_4, CompareEmptySlicesReturnsZero_4) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare empty with non-empty
TEST(SliceTest_4, CompareEmptyWithNonEmptyReturnsNegative_4) {
  Slice a;
  Slice b("hello");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare non-empty with empty
TEST(SliceTest_4, CompareNonEmptyWithEmptyReturnsPositive_4) {
  Slice a("hello");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
}

// Test begin() returns data()
TEST(SliceTest_4, BeginReturnsData_4) {
  const char* raw = "hello";
  Slice s(raw, 5);
  EXPECT_EQ(s.begin(), s.data());
  EXPECT_EQ(s.begin(), raw);
}

// Test end() returns data() + size()
TEST(SliceTest_4, EndReturnsDataPlusSize_4) {
  const char* raw = "hello";
  Slice s(raw, 5);
  EXPECT_EQ(s.end(), s.data() + s.size());
  EXPECT_EQ(s.end(), raw + 5);
}

// Test begin() and end() for empty slice
TEST(SliceTest_4, BeginEqualsEndForEmptySlice_4) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// Test copy constructor
TEST(SliceTest_4, CopyConstructorCreatesIdenticalSlice_4) {
  Slice original("hello", 5);
  Slice copy(original);
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.compare(original), 0);
}

// Test copy assignment
TEST(SliceTest_4, CopyAssignmentCreatesIdenticalSlice_4) {
  Slice original("hello", 5);
  Slice copy;
  copy = original;
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.compare(original), 0);
}

// Test with binary data (embedded nulls)
TEST(SliceTest_4, HandlesEmbeddedNullCharacters_4) {
  const char data[] = {'a', '\0', 'b', '\0', 'c'};
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], '\0');
  EXPECT_EQ(s[2], 'b');
  EXPECT_EQ(s[3], '\0');
  EXPECT_EQ(s[4], 'c');
}

// Test iterator-style traversal with begin/end
TEST(SliceTest_4, IterateWithBeginEnd_4) {
  Slice s("abc", 3);
  std::string result;
  for (const char* p = s.begin(); p != s.end(); ++p) {
    result += *p;
  }
  EXPECT_EQ(result, "abc");
}

// Test remove_prefix then ToString
TEST(SliceTest_4, RemovePrefixThenToString_4) {
  Slice s("hello world");
  s.remove_prefix(6);
  EXPECT_EQ(s.ToString(), "world");
}

// Test single character slice
TEST(SliceTest_4, SingleCharacterSlice_4) {
  Slice s("x", 1);
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'x');
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.ToString(), "x");
}

// Test compare with single character differences
TEST(SliceTest_4, CompareSingleCharDifference_4) {
  Slice a("a");
  Slice b("b");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test starts_with on empty slice with empty prefix
TEST(SliceTest_4, EmptySliceStartsWithEmptyPrefix_4) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with on empty slice with non-empty prefix
TEST(SliceTest_4, EmptySliceDoesNotStartWithNonEmptyPrefix_4) {
  Slice s;
  Slice prefix("a");
  EXPECT_FALSE(s.starts_with(prefix));
}

}  // namespace leveldb
