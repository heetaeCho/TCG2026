#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include <string>
#include <cstring>

namespace leveldb {

// Test equality operator with identical slices
TEST(SliceEqualityTest_11, EqualSlicesFromStringLiterals_11) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_TRUE(a == b);
}

// Test equality operator with different slices
TEST(SliceEqualityTest_11, DifferentSlicesAreNotEqual_11) {
  Slice a("hello");
  Slice b("world");
  EXPECT_FALSE(a == b);
}

// Test equality operator with empty slices
TEST(SliceEqualityTest_11, EmptySlicesAreEqual_11) {
  Slice a;
  Slice b;
  EXPECT_TRUE(a == b);
}

// Test equality operator with different lengths
TEST(SliceEqualityTest_11, DifferentLengthSlicesAreNotEqual_11) {
  Slice a("hello");
  Slice b("hell");
  EXPECT_FALSE(a == b);
}

// Test equality operator with same prefix but different lengths
TEST(SliceEqualityTest_11, SamePrefixDifferentLength_11) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_FALSE(a == b);
}

// Test equality with slices containing null bytes
TEST(SliceEqualityTest_11, SlicesWithNullBytes_11) {
  Slice a("he\0lo", 5);
  Slice b("he\0lo", 5);
  EXPECT_TRUE(a == b);
}

// Test equality with slices containing different data after null byte
TEST(SliceEqualityTest_11, SlicesWithDifferentDataAfterNullByte_11) {
  Slice a("he\0lo", 5);
  Slice b("he\0lx", 5);
  EXPECT_FALSE(a == b);
}

// Test equality with one empty and one non-empty slice
TEST(SliceEqualityTest_11, OneEmptyOneNonEmpty_11) {
  Slice a;
  Slice b("hello");
  EXPECT_FALSE(a == b);
}

// Test equality operator is symmetric
TEST(SliceEqualityTest_11, SymmetricEquality_11) {
  Slice a("test");
  Slice b("test");
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

// Test equality operator symmetry for non-equal slices
TEST(SliceEqualityTest_11, SymmetricInequality_11) {
  Slice a("foo");
  Slice b("bar");
  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == a);
}

// Test default constructor creates empty slice
TEST(SliceConstructorTest_11, DefaultConstructor_11) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test construction from const char*
TEST(SliceConstructorTest_11, FromCString_11) {
  Slice s("hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

// Test construction from std::string
TEST(SliceConstructorTest_11, FromStdString_11) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.data(), str.data());
}

// Test construction from pointer and length
TEST(SliceConstructorTest_11, FromPointerAndLength_11) {
  const char* data = "hello world";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

// Test data() returns correct pointer
TEST(SliceMethodTest_11, DataReturnsCorrectPointer_11) {
  const char* str = "test";
  Slice s(str);
  EXPECT_EQ(s.data(), str);
}

// Test size() returns correct value
TEST(SliceMethodTest_11, SizeReturnsCorrectValue_11) {
  Slice s("abc");
  EXPECT_EQ(s.size(), 3u);
}

// Test empty() on empty slice
TEST(SliceMethodTest_11, EmptyOnEmptySlice_11) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

// Test empty() on non-empty slice
TEST(SliceMethodTest_11, EmptyOnNonEmptySlice_11) {
  Slice s("x");
  EXPECT_FALSE(s.empty());
}

// Test operator[] access
TEST(SliceMethodTest_11, SubscriptOperator_11) {
  Slice s("abcdef");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[3], 'd');
  EXPECT_EQ(s[5], 'f');
}

// Test begin() and end()
TEST(SliceMethodTest_11, BeginEnd_11) {
  Slice s("hello");
  EXPECT_EQ(s.begin(), s.data());
  EXPECT_EQ(s.end(), s.data() + s.size());
  EXPECT_EQ(s.end() - s.begin(), 5);
}

// Test clear()
TEST(SliceMethodTest_11, ClearMakesSliceEmpty_11) {
  Slice s("hello");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test remove_prefix
TEST(SliceMethodTest_11, RemovePrefix_11) {
  Slice s("hello world");
  s.remove_prefix(6);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "world");
}

// Test remove_prefix with 0
TEST(SliceMethodTest_11, RemovePrefixZero_11) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

// Test remove_prefix entire string
TEST(SliceMethodTest_11, RemovePrefixEntireString_11) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test ToString
TEST(SliceMethodTest_11, ToString_11) {
  Slice s("hello");
  std::string str = s.ToString();
  EXPECT_EQ(str, "hello");
}

// Test ToString with empty slice
TEST(SliceMethodTest_11, ToStringEmpty_11) {
  Slice s;
  std::string str = s.ToString();
  EXPECT_EQ(str, "");
}

// Test starts_with returns true for matching prefix
TEST(SliceMethodTest_11, StartsWithTrue_11) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with returns false for non-matching prefix
TEST(SliceMethodTest_11, StartsWithFalse_11) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with with empty prefix
TEST(SliceMethodTest_11, StartsWithEmptyPrefix_11) {
  Slice s("hello");
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with where prefix is longer than the slice
TEST(SliceMethodTest_11, StartsWithLongerPrefix_11) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with with identical slices
TEST(SliceMethodTest_11, StartsWithIdentical_11) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test compare returns 0 for equal slices
TEST(SliceCompareTest_11, EqualSlicesCompareToZero_11) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare returns negative for lexicographically smaller
TEST(SliceCompareTest_11, SmallerSliceComparesNegative_11) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare returns positive for lexicographically larger
TEST(SliceCompareTest_11, LargerSliceComparesPositive_11) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare where one is a prefix of the other
TEST(SliceCompareTest_11, PrefixComparison_11) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test compare with empty slices
TEST(SliceCompareTest_11, EmptySlicesCompareToZero_11) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare with one empty and one non-empty
TEST(SliceCompareTest_11, EmptyVsNonEmpty_11) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test copy constructor
TEST(SliceCopyTest_11, CopyConstructor_11) {
  Slice a("hello");
  Slice b(a);
  EXPECT_TRUE(a == b);
  EXPECT_EQ(a.data(), b.data());
  EXPECT_EQ(a.size(), b.size());
}

// Test assignment operator
TEST(SliceCopyTest_11, AssignmentOperator_11) {
  Slice a("hello");
  Slice b;
  b = a;
  EXPECT_TRUE(a == b);
  EXPECT_EQ(a.data(), b.data());
  EXPECT_EQ(a.size(), b.size());
}

// Test single character slices
TEST(SliceEqualityTest_11, SingleCharacterSlices_11) {
  Slice a("a");
  Slice b("a");
  Slice c("b");
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
}

// Test equality with binary data
TEST(SliceEqualityTest_11, BinaryData_11) {
  char data1[] = {0x00, 0x01, 0x02, 0x03};
  char data2[] = {0x00, 0x01, 0x02, 0x03};
  char data3[] = {0x00, 0x01, 0x02, 0x04};
  Slice a(data1, 4);
  Slice b(data2, 4);
  Slice c(data3, 4);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
}

// Test ToString with embedded null bytes
TEST(SliceMethodTest_11, ToStringWithNullBytes_11) {
  Slice s("he\0lo", 5);
  std::string str = s.ToString();
  EXPECT_EQ(str.size(), 5u);
  EXPECT_EQ(str, std::string("he\0lo", 5));
}

}  // namespace leveldb
