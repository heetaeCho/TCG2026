#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include <string>
#include <cstring>

namespace leveldb {

// Test default constructor
TEST(SliceTest_2, DefaultConstructor_2) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test constructor from const char* and size_t
TEST(SliceTest_2, CharPtrWithSizeConstructor_2) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

// Test constructor from std::string
TEST(SliceTest_2, StringConstructor_2) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

// Test constructor from const char* (null-terminated)
TEST(SliceTest_2, CStringConstructor_2) {
  Slice s("test");
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(s.ToString(), "test");
}

// Test empty slice
TEST(SliceTest_2, EmptySlice_2) {
  Slice s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test non-empty slice is not empty
TEST(SliceTest_2, NonEmptySlice_2) {
  Slice s("abc");
  EXPECT_FALSE(s.empty());
}

// Test data() returns correct pointer
TEST(SliceTest_2, DataReturnsCorrectPointer_2) {
  const char* raw = "hello";
  Slice s(raw, 5);
  EXPECT_EQ(s.data(), raw);
}

// Test size() returns correct value
TEST(SliceTest_2, SizeReturnsCorrectValue_2) {
  Slice s("abcdef");
  EXPECT_EQ(s.size(), 6u);
}

// Test operator[]
TEST(SliceTest_2, SubscriptOperator_2) {
  Slice s("abcde");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[4], 'e');
}

// Test ToString
TEST(SliceTest_2, ToString_2) {
  Slice s("hello world");
  EXPECT_EQ(s.ToString(), "hello world");
}

// Test ToString on empty slice
TEST(SliceTest_2, ToStringEmpty_2) {
  Slice s;
  EXPECT_EQ(s.ToString(), "");
}

// Test clear
TEST(SliceTest_2, Clear_2) {
  Slice s("something");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test remove_prefix
TEST(SliceTest_2, RemovePrefix_2) {
  Slice s("hello");
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

// Test remove_prefix with zero
TEST(SliceTest_2, RemovePrefixZero_2) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test remove_prefix entire slice
TEST(SliceTest_2, RemovePrefixEntire_2) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test starts_with positive case
TEST(SliceTest_2, StartsWithTrue_2) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with negative case
TEST(SliceTest_2, StartsWithFalse_2) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with empty prefix
TEST(SliceTest_2, StartsWithEmptyPrefix_2) {
  Slice s("hello");
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with same string
TEST(SliceTest_2, StartsWithSameString_2) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with longer prefix
TEST(SliceTest_2, StartsWithLongerPrefix_2) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test compare equal slices
TEST(SliceTest_2, CompareEqual_2) {
  Slice a("abc");
  Slice b("abc");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare less than
TEST(SliceTest_2, CompareLessThan_2) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare greater than
TEST(SliceTest_2, CompareGreaterThan_2) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare with different lengths (prefix)
TEST(SliceTest_2, CompareShorterPrefix_2) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare with different lengths (longer)
TEST(SliceTest_2, CompareLongerPrefix_2) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare empty slices
TEST(SliceTest_2, CompareEmptySlices_2) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare empty with non-empty
TEST(SliceTest_2, CompareEmptyWithNonEmpty_2) {
  Slice a;
  Slice b("abc");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test begin and end
TEST(SliceTest_2, BeginEnd_2) {
  const char* raw = "hello";
  Slice s(raw, 5);
  EXPECT_EQ(s.begin(), raw);
  EXPECT_EQ(s.end(), raw + 5);
}

// Test begin and end for empty slice
TEST(SliceTest_2, BeginEndEmpty_2) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// Test copy constructor
TEST(SliceTest_2, CopyConstructor_2) {
  Slice original("test");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.ToString(), original.ToString());
  EXPECT_EQ(copy.data(), original.data());
}

// Test assignment operator
TEST(SliceTest_2, AssignmentOperator_2) {
  Slice a("hello");
  Slice b("world");
  b = a;
  EXPECT_EQ(b.size(), a.size());
  EXPECT_EQ(b.ToString(), a.ToString());
  EXPECT_EQ(b.data(), a.data());
}

// Test slice with embedded null bytes
TEST(SliceTest_2, EmbeddedNullBytes_2) {
  const char data[] = "he\0lo";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s[2], '\0');
  EXPECT_EQ(s[3], 'l');
}

// Test slice from string with embedded nulls
TEST(SliceTest_2, StringWithEmbeddedNulls_2) {
  std::string str("he\0lo", 5);
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), str);
}

// Test single character slice
TEST(SliceTest_2, SingleCharacter_2) {
  Slice s("x");
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'x');
  EXPECT_FALSE(s.empty());
}

// Test remove_prefix followed by operations
TEST(SliceTest_2, RemovePrefixThenOperations_2) {
  Slice s("hello world");
  s.remove_prefix(6);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
  EXPECT_EQ(s[0], 'w');
  EXPECT_FALSE(s.empty());
}

// Test multiple remove_prefix calls
TEST(SliceTest_2, MultipleRemovePrefix_2) {
  Slice s("abcdef");
  s.remove_prefix(2);
  EXPECT_EQ(s.ToString(), "cdef");
  s.remove_prefix(2);
  EXPECT_EQ(s.ToString(), "ef");
  s.remove_prefix(2);
  EXPECT_TRUE(s.empty());
}

// Test comparison symmetry
TEST(SliceTest_2, CompareSymmetry_2) {
  Slice a("abc");
  Slice b("def");
  int cmp_ab = a.compare(b);
  int cmp_ba = b.compare(a);
  EXPECT_LT(cmp_ab, 0);
  EXPECT_GT(cmp_ba, 0);
}

// Test self-comparison
TEST(SliceTest_2, CompareSelf_2) {
  Slice s("hello");
  EXPECT_EQ(s.compare(s), 0);
}

// Test starts_with on empty slice with empty prefix
TEST(SliceTest_2, EmptyStartsWithEmpty_2) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

}  // namespace leveldb
