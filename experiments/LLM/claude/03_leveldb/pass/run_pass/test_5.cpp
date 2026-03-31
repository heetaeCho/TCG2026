#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include <string>
#include <cstring>

namespace leveldb {

// Test default constructor
TEST(SliceTest_5, DefaultConstructor_5) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_STREQ(s.data(), "");
}

// Test constructor from const char* and size
TEST(SliceTest_5, CharPtrWithSizeConstructor_5) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.data(), data);
  EXPECT_FALSE(s.empty());
}

// Test constructor from std::string
TEST(SliceTest_5, StringConstructor_5) {
  std::string str = "hello world";
  Slice s(str);
  EXPECT_EQ(s.size(), str.size());
  EXPECT_EQ(s.data(), str.data());
}

// Test constructor from const char*
TEST(SliceTest_5, CharPtrConstructor_5) {
  const char* cstr = "test string";
  Slice s(cstr);
  EXPECT_EQ(s.size(), strlen(cstr));
  EXPECT_EQ(s.data(), cstr);
}

// Test end() method
TEST(SliceTest_5, EndMethod_5) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.end(), s.data() + s.size());
}

// Test end() on empty slice
TEST(SliceTest_5, EndOnEmptySlice_5) {
  Slice s;
  EXPECT_EQ(s.end(), s.data() + 0);
  EXPECT_EQ(s.end(), s.data());
}

// Test begin() method
TEST(SliceTest_5, BeginMethod_5) {
  const char* data = "hello";
  Slice s(data, 5);
  EXPECT_EQ(s.begin(), s.data());
}

// Test begin() and end() consistency
TEST(SliceTest_5, BeginEndConsistency_5) {
  std::string str = "test";
  Slice s(str);
  EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), s.size());
}

// Test operator[]
TEST(SliceTest_5, IndexOperator_5) {
  Slice s("abcde", 5);
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
  EXPECT_EQ(s[2], 'c');
  EXPECT_EQ(s[3], 'd');
  EXPECT_EQ(s[4], 'e');
}

// Test empty() on non-empty slice
TEST(SliceTest_5, EmptyOnNonEmptySlice_5) {
  Slice s("data", 4);
  EXPECT_FALSE(s.empty());
}

// Test empty() on empty slice
TEST(SliceTest_5, EmptyOnEmptySlice_5) {
  Slice s("", 0);
  EXPECT_TRUE(s.empty());
}

// Test ToString()
TEST(SliceTest_5, ToString_5) {
  std::string original = "hello world";
  Slice s(original);
  std::string result = s.ToString();
  EXPECT_EQ(result, original);
}

// Test ToString() on empty slice
TEST(SliceTest_5, ToStringEmpty_5) {
  Slice s;
  EXPECT_EQ(s.ToString(), "");
}

// Test clear()
TEST(SliceTest_5, Clear_5) {
  Slice s("hello", 5);
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test remove_prefix()
TEST(SliceTest_5, RemovePrefix_5) {
  const char* data = "hello";
  Slice s(data, 5);
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.data(), data + 2);
  EXPECT_EQ(s[0], 'l');
}

// Test remove_prefix with zero
TEST(SliceTest_5, RemovePrefixZero_5) {
  Slice s("hello", 5);
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s[0], 'h');
}

// Test remove_prefix entire string
TEST(SliceTest_5, RemovePrefixEntireString_5) {
  Slice s("hello", 5);
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// Test starts_with() positive case
TEST(SliceTest_5, StartsWithTrue_5) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() negative case
TEST(SliceTest_5, StartsWithFalse_5) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test starts_with() empty prefix
TEST(SliceTest_5, StartsWithEmptyPrefix_5) {
  Slice s("hello");
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() same string
TEST(SliceTest_5, StartsWithSameString_5) {
  Slice s("hello");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Test starts_with() prefix longer than slice
TEST(SliceTest_5, StartsWithLongerPrefix_5) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test compare() equal slices
TEST(SliceTest_5, CompareEqual_5) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare() less than
TEST(SliceTest_5, CompareLessThan_5) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test compare() greater than
TEST(SliceTest_5, CompareGreaterThan_5) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test compare() with different lengths, same prefix
TEST(SliceTest_5, CompareDifferentLengthsSamePrefix_5) {
  Slice a("hello");
  Slice b("helloworld");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test compare() empty slices
TEST(SliceTest_5, CompareEmptySlices_5) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare() empty vs non-empty
TEST(SliceTest_5, CompareEmptyVsNonEmpty_5) {
  Slice a;
  Slice b("hello");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Test copy constructor
TEST(SliceTest_5, CopyConstructor_5) {
  Slice original("hello", 5);
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.compare(original), 0);
}

// Test assignment operator
TEST(SliceTest_5, AssignmentOperator_5) {
  Slice original("hello", 5);
  Slice assigned;
  assigned = original;
  EXPECT_EQ(assigned.size(), original.size());
  EXPECT_EQ(assigned.data(), original.data());
  EXPECT_EQ(assigned.compare(original), 0);
}

// Test end() with data containing null bytes
TEST(SliceTest_5, EndWithNullBytes_5) {
  const char data[] = "hel\0lo";
  Slice s(data, 6);
  EXPECT_EQ(s.size(), 6u);
  EXPECT_EQ(s.end(), s.data() + 6);
  EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), 6u);
}

// Test slice with single character
TEST(SliceTest_5, SingleCharacter_5) {
  Slice s("a", 1);
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s.end() - s.begin(), 1);
  EXPECT_FALSE(s.empty());
}

// Test ToString with embedded nulls
TEST(SliceTest_5, ToStringWithEmbeddedNulls_5) {
  const char data[] = "hel\0lo";
  Slice s(data, 6);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 6u);
  EXPECT_EQ(result, std::string(data, 6));
}

// Test end() after remove_prefix
TEST(SliceTest_5, EndAfterRemovePrefix_5) {
  const char* data = "hello world";
  Slice s(data, 11);
  const char* original_end = s.end();
  s.remove_prefix(5);
  // After remove_prefix, end should remain the same (data moves forward, size decreases)
  EXPECT_EQ(s.end(), original_end);
}

// Test end() after clear
TEST(SliceTest_5, EndAfterClear_5) {
  Slice s("hello", 5);
  s.clear();
  EXPECT_EQ(s.end(), s.data());
}

}  // namespace leveldb
