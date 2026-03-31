#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>

namespace leveldb {

// Test default constructor
TEST(SliceTest_8, DefaultConstructor_8) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test constructor from const char* and size
TEST(SliceTest_8, ConstructFromCharPtrAndSize_8) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.data(), data);
  EXPECT_FALSE(s.empty());
}

// Test constructor from std::string
TEST(SliceTest_8, ConstructFromString_8) {
  std::string str = "hello world";
  Slice s(str);
  EXPECT_EQ(s.size(), str.size());
  EXPECT_EQ(s.data(), str.data());
  EXPECT_FALSE(s.empty());
}

// Test constructor from const char* (null-terminated)
TEST(SliceTest_8, ConstructFromCharPtr_8) {
  const char* cstr = "test";
  Slice s(cstr);
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(std::string(s.data(), s.size()), "test");
}

// Test empty string constructor
TEST(SliceTest_8, ConstructFromEmptyString_8) {
  std::string str = "";
  Slice s(str);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test operator[]
TEST(SliceTest_8, OperatorIndex_8) {
  Slice s("abcde", 5);
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[2], 'c');
  EXPECT_EQ(s[3], 'd');
  EXPECT_EQ(s[4], 'e');
}

// Test ToString
TEST(SliceTest_8, ToString_8) {
  Slice s("hello", 5);
  std::string result = s.ToString();
  EXPECT_EQ(result, "hello");
}

// Test ToString on empty slice
TEST(SliceTest_8, ToStringEmpty_8) {
  Slice s;
  std::string result = s.ToString();
  EXPECT_EQ(result, "");
}

// Test clear
TEST(SliceTest_8, Clear_8) {
  Slice s("hello", 5);
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test remove_prefix normal case
TEST(SliceTest_8, RemovePrefixNormal_8) {
  Slice s("hello", 5);
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

// Test remove_prefix with zero
TEST(SliceTest_8, RemovePrefixZero_8) {
  Slice s("hello", 5);
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test remove_prefix entire slice
TEST(SliceTest_8, RemovePrefixEntireSlice_8) {
  Slice s("hello", 5);
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test starts_with positive case
TEST(SliceTest_8, StartsWithTrue_8) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with negative case
TEST(SliceTest_8, StartsWithFalse_8) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with empty prefix
TEST(SliceTest_8, StartsWithEmptyPrefix_8) {
  Slice s("hello");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with same string
TEST(SliceTest_8, StartsWithSameString_8) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with prefix longer than string
TEST(SliceTest_8, StartsWithLongerPrefix_8) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test compare equal
TEST(SliceTest_8, CompareEqual_8) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare less than
TEST(SliceTest_8, CompareLessThan_8) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare greater than
TEST(SliceTest_8, CompareGreaterThan_8) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare with different lengths, shorter is prefix
TEST(SliceTest_8, CompareShorterPrefix_8) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare with different lengths, longer is prefix
TEST(SliceTest_8, CompareLongerPrefix_8) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare empty slices
TEST(SliceTest_8, CompareEmptySlices_8) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare empty with non-empty
TEST(SliceTest_8, CompareEmptyWithNonEmpty_8) {
  Slice a;
  Slice b("hello");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test begin and end
TEST(SliceTest_8, BeginEnd_8) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.begin(), s.data());
  EXPECT_EQ(s.end(), s.data() + s.size());
  EXPECT_EQ(s.end() - s.begin(), 5);
}

// Test begin and end on empty slice
TEST(SliceTest_8, BeginEndEmpty_8) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// Test copy constructor
TEST(SliceTest_8, CopyConstructor_8) {
  Slice original("hello", 5);
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Test copy assignment
TEST(SliceTest_8, CopyAssignment_8) {
  Slice original("hello", 5);
  Slice copy;
  copy = original;
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Test slice with embedded null characters
TEST(SliceTest_8, EmbeddedNullCharacters_8) {
  const char data[] = "hel\0lo";
  Slice s(data, 6);
  EXPECT_EQ(s.size(), 6u);
  EXPECT_EQ(s[3], '\0');
  EXPECT_EQ(s[4], 'l');
}

// Test multiple remove_prefix calls
TEST(SliceTest_8, MultipleRemovePrefix_8) {
  Slice s("abcdefgh", 8);
  s.remove_prefix(2);
  EXPECT_EQ(s.ToString(), "cdefgh");
  s.remove_prefix(3);
  EXPECT_EQ(s.ToString(), "fgh");
  s.remove_prefix(3);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test single character slice
TEST(SliceTest_8, SingleCharacterSlice_8) {
  Slice s("x", 1);
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'x');
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.ToString(), "x");
}

// Test remove_prefix preserves data pointer correctly
TEST(SliceTest_8, RemovePrefixDataPointer_8) {
  const char* data = "hello";
  Slice s(data, 5);
  s.remove_prefix(2);
  EXPECT_EQ(s.data(), data + 2);
  EXPECT_EQ(s.size(), 3u);
}

// Test compare symmetry
TEST(SliceTest_8, CompareSymmetry_8) {
  Slice a("abc");
  Slice b("xyz");
  int cmp_ab = a.compare(b);
  int cmp_ba = b.compare(a);
  EXPECT_LT(cmp_ab, 0);
  EXPECT_GT(cmp_ba, 0);
}

}  // namespace leveldb
