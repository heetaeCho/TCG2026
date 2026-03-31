#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include "leveldb/slice.h"

namespace leveldb {

// ==================== Constructor Tests ====================

TEST(SliceTest_9, DefaultConstructor_9) {
  Slice s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.ToString(), "");
}

TEST(SliceTest_9, ConstructFromCharPtrAndSize_9) {
  const char* data = "hello world";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
  EXPECT_EQ(s.data(), data);
}

TEST(SliceTest_9, ConstructFromString_9) {
  std::string str = "test string";
  Slice s(str);
  EXPECT_EQ(s.size(), str.size());
  EXPECT_EQ(s.ToString(), str);
  EXPECT_EQ(s.data(), str.data());
}

TEST(SliceTest_9, ConstructFromCString_9) {
  const char* cstr = "c-string";
  Slice s(cstr);
  EXPECT_EQ(s.size(), strlen(cstr));
  EXPECT_EQ(s.ToString(), "c-string");
}

TEST(SliceTest_9, ConstructFromEmptyString_9) {
  std::string str = "";
  Slice s(str);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.ToString(), "");
}

TEST(SliceTest_9, ConstructFromEmptyCString_9) {
  const char* cstr = "";
  Slice s(cstr);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// ==================== Copy Tests ====================

TEST(SliceTest_9, CopyConstructor_9) {
  Slice original("hello", 5);
  Slice copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

TEST(SliceTest_9, CopyAssignment_9) {
  Slice original("hello", 5);
  Slice copy;
  copy = original;
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.data(), original.data());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// ==================== data() and size() Tests ====================

TEST(SliceTest_9, DataReturnsPointerToData_9) {
  const char* raw = "abcdef";
  Slice s(raw, 6);
  EXPECT_EQ(s.data(), raw);
}

TEST(SliceTest_9, SizeReturnsCorrectLength_9) {
  Slice s("abcdef", 3);
  EXPECT_EQ(s.size(), 3u);
}

// ==================== empty() Tests ====================

TEST(SliceTest_9, EmptyReturnsTrueForEmptySlice_9) {
  Slice s;
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_9, EmptyReturnsFalseForNonEmptySlice_9) {
  Slice s("a", 1);
  EXPECT_FALSE(s.empty());
}

// ==================== operator[] Tests ====================

TEST(SliceTest_9, SubscriptOperatorAccessFirstElement_9) {
  Slice s("hello", 5);
  EXPECT_EQ(s[0], 'h');
}

TEST(SliceTest_9, SubscriptOperatorAccessLastElement_9) {
  Slice s("hello", 5);
  EXPECT_EQ(s[4], 'o');
}

TEST(SliceTest_9, SubscriptOperatorAccessMiddleElement_9) {
  Slice s("hello", 5);
  EXPECT_EQ(s[2], 'l');
}

// ==================== begin() and end() Tests ====================

TEST(SliceTest_9, BeginReturnsDataPointer_9) {
  const char* raw = "test";
  Slice s(raw, 4);
  EXPECT_EQ(s.begin(), raw);
}

TEST(SliceTest_9, EndReturnsDataPlusSizePointer_9) {
  const char* raw = "test";
  Slice s(raw, 4);
  EXPECT_EQ(s.end(), raw + 4);
}

TEST(SliceTest_9, BeginEqualsEndForEmptySlice_9) {
  Slice s;
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SliceTest_9, IterateWithBeginEnd_9) {
  Slice s("abc", 3);
  std::string result;
  for (const char* it = s.begin(); it != s.end(); ++it) {
    result += *it;
  }
  EXPECT_EQ(result, "abc");
}

// ==================== clear() Tests ====================

TEST(SliceTest_9, ClearMakesSliceEmpty_9) {
  Slice s("hello", 5);
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_9, ClearOnAlreadyEmptySlice_9) {
  Slice s;
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

// ==================== remove_prefix() Tests ====================

TEST(SliceTest_9, RemovePrefixReducesSize_9) {
  Slice s("hello", 5);
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

TEST(SliceTest_9, RemovePrefixZero_9) {
  Slice s("hello", 5);
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceTest_9, RemovePrefixEntireSlice_9) {
  Slice s("hello", 5);
  s.remove_prefix(5);
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
}

TEST(SliceTest_9, RemovePrefixOneByOne_9) {
  Slice s("abcd", 4);
  s.remove_prefix(1);
  EXPECT_EQ(s.ToString(), "bcd");
  s.remove_prefix(1);
  EXPECT_EQ(s.ToString(), "cd");
  s.remove_prefix(1);
  EXPECT_EQ(s.ToString(), "d");
  s.remove_prefix(1);
  EXPECT_TRUE(s.empty());
}

// ==================== ToString() Tests ====================

TEST(SliceTest_9, ToStringReturnsCorrectString_9) {
  Slice s("hello world", 11);
  EXPECT_EQ(s.ToString(), "hello world");
}

TEST(SliceTest_9, ToStringWithPartialData_9) {
  Slice s("hello world", 5);
  EXPECT_EQ(s.ToString(), "hello");
}

TEST(SliceTest_9, ToStringFromEmptySlice_9) {
  Slice s;
  EXPECT_EQ(s.ToString(), "");
}

TEST(SliceTest_9, ToStringWithEmbeddedNull_9) {
  const char data[] = "hel\0lo";
  Slice s(data, 6);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 6u);
  EXPECT_EQ(result[3], '\0');
  EXPECT_EQ(result[4], 'l');
}

// ==================== starts_with() Tests ====================

TEST(SliceTest_9, StartsWithReturnsTrueForPrefix_9) {
  Slice s("hello world");
  Slice prefix("hello");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_9, StartsWithReturnsFalseForNonPrefix_9) {
  Slice s("hello world");
  Slice prefix("world");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceTest_9, StartsWithEmptyPrefix_9) {
  Slice s("hello");
  Slice prefix("");
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_9, StartsWithSameSlice_9) {
  Slice s("hello");
  EXPECT_TRUE(s.starts_with(s));
}

TEST(SliceTest_9, StartsWithLongerPrefix_9) {
  Slice s("hi");
  Slice prefix("hi there");
  EXPECT_FALSE(s.starts_with(prefix));
}

TEST(SliceTest_9, EmptySliceStartsWithEmpty_9) {
  Slice s;
  Slice prefix;
  EXPECT_TRUE(s.starts_with(prefix));
}

TEST(SliceTest_9, EmptySliceDoesNotStartWithNonEmpty_9) {
  Slice s;
  Slice prefix("a");
  EXPECT_FALSE(s.starts_with(prefix));
}

// ==================== compare() Tests ====================

TEST(SliceTest_9, CompareEqualSlices_9) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceTest_9, CompareLessThan_9) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_9, CompareGreaterThan_9) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_9, CompareShorterVsLonger_9) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_9, CompareLongerVsShorter_9) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_9, CompareEmptySlices_9) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

TEST(SliceTest_9, CompareEmptyWithNonEmpty_9) {
  Slice a;
  Slice b("a");
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_9, CompareNonEmptyWithEmpty_9) {
  Slice a("a");
  Slice b;
  EXPECT_GT(a.compare(b), 0);
}

TEST(SliceTest_9, CompareSingleCharSlices_9) {
  Slice a("a");
  Slice b("b");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

TEST(SliceTest_9, CompareWithSelf_9) {
  Slice a("hello");
  EXPECT_EQ(a.compare(a), 0);
}

// ==================== Equality Operators (if defined) ====================

TEST(SliceTest_9, SliceFromBinaryData_9) {
  const char binary[] = {'\x00', '\x01', '\x02', '\x03'};
  Slice s(binary, 4);
  EXPECT_EQ(s.size(), 4u);
  EXPECT_EQ(s[0], '\x00');
  EXPECT_EQ(s[1], '\x01');
  EXPECT_EQ(s[2], '\x02');
  EXPECT_EQ(s[3], '\x03');
}

TEST(SliceTest_9, CompareBinaryData_9) {
  const char data1[] = {'\x00', '\x01'};
  const char data2[] = {'\x00', '\x02'};
  Slice a(data1, 2);
  Slice b(data2, 2);
  EXPECT_LT(a.compare(b), 0);
}

TEST(SliceTest_9, ToStringPreservesBinaryData_9) {
  const char data[] = {'\x00', '\x41', '\x00', '\x42'};
  Slice s(data, 4);
  std::string result = s.ToString();
  EXPECT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0], '\x00');
  EXPECT_EQ(result[1], '\x41');
  EXPECT_EQ(result[2], '\x00');
  EXPECT_EQ(result[3], '\x42');
}

// ==================== Large Data Tests ====================

TEST(SliceTest_9, LargeStringSlice_9) {
  std::string large(10000, 'x');
  Slice s(large);
  EXPECT_EQ(s.size(), 10000u);
  EXPECT_EQ(s.ToString(), large);
}

TEST(SliceTest_9, RemovePrefixOnLargeSlice_9) {
  std::string large(10000, 'a');
  Slice s(large);
  s.remove_prefix(9999);
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'a');
}

}  // namespace leveldb
