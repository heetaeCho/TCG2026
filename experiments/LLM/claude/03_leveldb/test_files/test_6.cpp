#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include <string>

namespace leveldb {

// Test default constructor
TEST(SliceTest_6, DefaultConstructor_6) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test constructor from const char* and size_t
TEST(SliceTest_6, CharPtrWithSizeConstructor_6) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

// Test constructor from std::string
TEST(SliceTest_6, StringConstructor_6) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

// Test constructor from const char*
TEST(SliceTest_6, CharPtrConstructor_6) {
  Slice s("test");
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(s.ToString(), "test");
}

// Test copy constructor
TEST(SliceTest_6, CopyConstructor_6) {
  Slice original("copy me");
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Test copy assignment operator
TEST(SliceTest_6, CopyAssignment_6) {
  Slice a("first");
  Slice b("second");
  b = a;
  EXPECT_EQ(b.ToString(), "first");
  EXPECT_EQ(b.size(), a.size());
}

// Test data() method
TEST(SliceTest_6, DataMethod_6) {
  const char* raw = "rawdata";
  Slice s(raw, 7);
  EXPECT_EQ(s.data(), raw);
}

// Test size() method
TEST(SliceTest_6, SizeMethod_6) {
  Slice s("abcdef");
  EXPECT_EQ(s.size(), 6u);
}

// Test empty() with non-empty slice
TEST(SliceTest_6, EmptyFalse_6) {
  Slice s("notempty");
  EXPECT_FALSE(s.empty());
}

// Test empty() with empty slice
TEST(SliceTest_6, EmptyTrue_6) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

// Test empty slice from empty string
TEST(SliceTest_6, EmptyFromEmptyString_6) {
  std::string str;
  Slice s(str);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test operator[]
TEST(SliceTest_6, SubscriptOperator_6) {
  Slice s("abcde");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[2], 'c');
  EXPECT_EQ(s[3], 'd');
  EXPECT_EQ(s[4], 'e');
}

// Test operator[] at boundary (last valid index)
TEST(SliceTest_6, SubscriptOperatorBoundary_6) {
  Slice s("x");
  EXPECT_EQ(s[0], 'x');
}

// Test begin() and end()
TEST(SliceTest_6, BeginEnd_6) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.begin(), s.data());
  EXPECT_EQ(s.end(), s.data() + s.size());
}

// Test begin() equals end() for empty slice
TEST(SliceTest_6, BeginEqualsEndForEmpty_6) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

// Test clear()
TEST(SliceTest_6, Clear_6) {
  Slice s("notempty");
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test remove_prefix()
TEST(SliceTest_6, RemovePrefix_6) {
  Slice s("hello world");
  s.remove_prefix(6);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

// Test remove_prefix with zero
TEST(SliceTest_6, RemovePrefixZero_6) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test remove_prefix entire string
TEST(SliceTest_6, RemovePrefixEntireString_6) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test ToString()
TEST(SliceTest_6, ToString_6) {
  Slice s("convert me");
  std::string result = s.ToString();
  EXPECT_EQ(result, "convert me");
}

// Test ToString() for empty slice
TEST(SliceTest_6, ToStringEmpty_6) {
  Slice s;
  std::string result = s.ToString();
  EXPECT_EQ(result, "");
}

// Test starts_with() positive case
TEST(SliceTest_6, StartsWithTrue_6) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() negative case
TEST(SliceTest_6, StartsWithFalse_6) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with() empty prefix
TEST(SliceTest_6, StartsWithEmptyPrefix_6) {
  Slice s("hello");
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() same string
TEST(SliceTest_6, StartsWithSameString_6) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() prefix longer than slice
TEST(SliceTest_6, StartsWithLongerPrefix_6) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with() empty slice with empty prefix
TEST(SliceTest_6, StartsWithBothEmpty_6) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test compare() equal slices
TEST(SliceTest_6, CompareEqual_6) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare() less than
TEST(SliceTest_6, CompareLessThan_6) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare() greater than
TEST(SliceTest_6, CompareGreaterThan_6) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare() with different lengths, shorter is prefix
TEST(SliceTest_6, CompareShorterPrefix_6) {
  Slice a("abc");
  Slice b("abcde");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare() with different lengths, longer is prefix
TEST(SliceTest_6, CompareLongerPrefix_6) {
  Slice a("abcde");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare() both empty
TEST(SliceTest_6, CompareBothEmpty_6) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare() one empty
TEST(SliceTest_6, CompareOneEmpty_6) {
  Slice a("hello");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
  EXPECT_LT(b.compare(a), 0);
}

// Test with embedded null characters
TEST(SliceTest_6, EmbeddedNulls_6) {
  std::string str("hel\0lo", 6);
  Slice s(str);
  EXPECT_EQ(s.size(), 6u);
  EXPECT_EQ(s[3], '\0');
  EXPECT_EQ(s[4], 'l');
  EXPECT_EQ(s[5], 'o');
}

// Test ToString preserves embedded nulls
TEST(SliceTest_6, ToStringWithEmbeddedNulls_6) {
  std::string str("ab\0cd", 5);
  Slice s(str);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result, str);
}

// Test compare with embedded nulls
TEST(SliceTest_6, CompareWithEmbeddedNulls_6) {
  std::string str1("ab\0cd", 5);
  std::string str2("ab\0ce", 5);
  Slice a(str1);
  Slice b(str2);
  EXPECT_LT(a.compare(b), 0);
}

// Test constructing from char* with size zero
TEST(SliceTest_6, ZeroSizeConstruction_6) {
  Slice s("hello", 0);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test remove_prefix then access data
TEST(SliceTest_6, RemovePrefixThenAccess_6) {
  Slice s("abcdef");
  s.remove_prefix(3);
  EXPECT_EQ(s[0], 'd');
  EXPECT_EQ(s[1], 'e');
  EXPECT_EQ(s[2], 'f');
}

// Test iteration using begin/end
TEST(SliceTest_6, IterationBeginEnd_6) {
  Slice s("abc");
  std::string result;
  for (const char* p = s.begin(); p != s.end(); ++p) {
    result += *p;
  }
  EXPECT_EQ(result, "abc");
}

// Test multiple operations in sequence
TEST(SliceTest_6, SequentialOperations_6) {
  Slice s("hello world");
  EXPECT_EQ(s.size(), 11u);
  s.remove_prefix(6);
  EXPECT_EQ(s.ToString(), "world");
  EXPECT_EQ(s.size(), 5u);
  s.clear();
  EXPECT_TRUE(s.empty());
}

}  // namespace leveldb
