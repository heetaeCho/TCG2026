#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include <string>

namespace leveldb {

// Test for operator!= with equal slices
TEST(SliceNotEqualOperatorTest_12, EqualSlicesReturnFalse_12) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_FALSE(a != b);
}

// Test for operator!= with different slices
TEST(SliceNotEqualOperatorTest_12, DifferentSlicesReturnTrue_12) {
  Slice a("hello");
  Slice b("world");
  EXPECT_TRUE(a != b);
}

// Test for operator!= with empty slices
TEST(SliceNotEqualOperatorTest_12, BothEmptySlicesReturnFalse_12) {
  Slice a;
  Slice b;
  EXPECT_FALSE(a != b);
}

// Test for operator!= with one empty and one non-empty slice
TEST(SliceNotEqualOperatorTest_12, EmptyAndNonEmptyReturnTrue_12) {
  Slice a;
  Slice b("hello");
  EXPECT_TRUE(a != b);
}

// Test for operator!= with same data different lengths
TEST(SliceNotEqualOperatorTest_12, SamePrefixDifferentLengthReturnTrue_12) {
  Slice a("hello");
  Slice b("hell");
  EXPECT_TRUE(a != b);
}

// Test for operator!= with slices constructed from std::string
TEST(SliceNotEqualOperatorTest_12, StdStringEqualSlicesReturnFalse_12) {
  std::string s1 = "test";
  std::string s2 = "test";
  Slice a(s1);
  Slice b(s2);
  EXPECT_FALSE(a != b);
}

// Test for operator!= with slices constructed from std::string different values
TEST(SliceNotEqualOperatorTest_12, StdStringDifferentSlicesReturnTrue_12) {
  std::string s1 = "test1";
  std::string s2 = "test2";
  Slice a(s1);
  Slice b(s2);
  EXPECT_TRUE(a != b);
}

// Test for operator!= with data+size constructor
TEST(SliceNotEqualOperatorTest_12, DataSizeConstructorEqual_12) {
  const char* data = "hello world";
  Slice a(data, 5);
  Slice b("hello");
  EXPECT_FALSE(a != b);
}

// Test for operator!= with data+size constructor different
TEST(SliceNotEqualOperatorTest_12, DataSizeConstructorDifferent_12) {
  const char* data = "hello world";
  Slice a(data, 5);
  Slice b(data, 6);
  EXPECT_TRUE(a != b);
}

// Test for operator!= symmetry
TEST(SliceNotEqualOperatorTest_12, Symmetry_12) {
  Slice a("abc");
  Slice b("def");
  EXPECT_EQ(a != b, b != a);
}

// Test for operator!= symmetry with equal slices
TEST(SliceNotEqualOperatorTest_12, SymmetryEqual_12) {
  Slice a("abc");
  Slice b("abc");
  EXPECT_EQ(a != b, b != a);
}

// Test for operator!= with single character slices
TEST(SliceNotEqualOperatorTest_12, SingleCharEqual_12) {
  Slice a("a");
  Slice b("a");
  EXPECT_FALSE(a != b);
}

// Test for operator!= with single character slices different
TEST(SliceNotEqualOperatorTest_12, SingleCharDifferent_12) {
  Slice a("a");
  Slice b("b");
  EXPECT_TRUE(a != b);
}

// Test for operator!= with binary data containing null bytes
TEST(SliceNotEqualOperatorTest_12, BinaryDataWithNullBytes_12) {
  Slice a("he\0lo", 5);
  Slice b("he\0lo", 5);
  EXPECT_FALSE(a != b);
}

// Test for operator!= with binary data containing different null byte patterns
TEST(SliceNotEqualOperatorTest_12, BinaryDataDifferentNullPatterns_12) {
  Slice a("he\0lo", 5);
  Slice b("he\0la", 5);
  EXPECT_TRUE(a != b);
}

// Test Slice basic interface: default constructor creates empty slice
TEST(SliceBasicTest_12, DefaultConstructorIsEmpty_12) {
  Slice s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test Slice basic interface: const char* constructor
TEST(SliceBasicTest_12, CStringConstructor_12) {
  Slice s("hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.ToString(), "hello");
}

// Test Slice basic interface: std::string constructor
TEST(SliceBasicTest_12, StdStringConstructor_12) {
  std::string str = "world";
  Slice s(str);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "world");
}

// Test Slice basic interface: data+size constructor
TEST(SliceBasicTest_12, DataSizeConstructor_12) {
  const char* data = "hello world";
  Slice s(data, 5);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test Slice operator[]
TEST(SliceBasicTest_12, IndexOperator_12) {
  Slice s("abcde");
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[4], 'e');
}

// Test Slice clear
TEST(SliceBasicTest_12, Clear_12) {
  Slice s("hello");
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test Slice remove_prefix
TEST(SliceBasicTest_12, RemovePrefix_12) {
  Slice s("hello");
  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.ToString(), "llo");
}

// Test Slice starts_with
TEST(SliceBasicTest_12, StartsWith_12) {
  Slice s("hello world");
  EXPECT_TRUE(s.starts_with("hello"));
  EXPECT_FALSE(s.starts_with("world"));
}

// Test Slice starts_with with empty prefix
TEST(SliceBasicTest_12, StartsWithEmpty_12) {
  Slice s("hello");
  Slice empty;
  EXPECT_TRUE(s.starts_with(empty));
}

// Test Slice starts_with with same slice
TEST(SliceBasicTest_12, StartsWithSelf_12) {
  Slice s("hello");
  EXPECT_TRUE(s.starts_with(s));
}

// Test Slice compare
TEST(SliceBasicTest_12, CompareEqual_12) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(a.compare(b), 0);
}

// Test Slice compare less than
TEST(SliceBasicTest_12, CompareLessThan_12) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
}

// Test Slice compare greater than
TEST(SliceBasicTest_12, CompareGreaterThan_12) {
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test Slice compare with prefix
TEST(SliceBasicTest_12, ComparePrefixShorter_12) {
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(a.compare(b), 0);
}

// Test Slice compare with prefix longer
TEST(SliceBasicTest_12, ComparePrefixLonger_12) {
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(a.compare(b), 0);
}

// Test Slice begin and end
TEST(SliceBasicTest_12, BeginEnd_12) {
  Slice s("hello");
  EXPECT_EQ(s.end() - s.begin(), 5);
  EXPECT_EQ(s.begin(), s.data());
}

// Test Slice copy constructor
TEST(SliceBasicTest_12, CopyConstructor_12) {
  Slice a("hello");
  Slice b(a);
  EXPECT_FALSE(a != b);
  EXPECT_EQ(a.ToString(), b.ToString());
}

// Test Slice copy assignment
TEST(SliceBasicTest_12, CopyAssignment_12) {
  Slice a("hello");
  Slice b("world");
  b = a;
  EXPECT_FALSE(a != b);
  EXPECT_EQ(b.ToString(), "hello");
}

// Test Slice ToString
TEST(SliceBasicTest_12, ToString_12) {
  Slice s("hello");
  std::string str = s.ToString();
  EXPECT_EQ(str, "hello");
}

// Test Slice with binary data in ToString
TEST(SliceBasicTest_12, ToStringBinaryData_12) {
  std::string original("he\0lo", 5);
  Slice s(original);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), original);
}

// Test remove_prefix all bytes
TEST(SliceBasicTest_12, RemovePrefixAll_12) {
  Slice s("hello");
  s.remove_prefix(5);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Test remove_prefix zero bytes
TEST(SliceBasicTest_12, RemovePrefixZero_12) {
  Slice s("hello");
  s.remove_prefix(0);
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "hello");
}

// Test starts_with longer prefix returns false
TEST(SliceBasicTest_12, StartsWithLongerPrefix_12) {
  Slice s("hi");
  Slice prefix("hello");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Test operator!= self comparison
TEST(SliceNotEqualOperatorTest_12, SelfComparison_12) {
  Slice a("hello");
  EXPECT_FALSE(a != a);
}

// Test compare empty slices
TEST(SliceBasicTest_12, CompareEmptySlices_12) {
  Slice a;
  Slice b;
  EXPECT_EQ(a.compare(b), 0);
}

// Test compare empty with non-empty
TEST(SliceBasicTest_12, CompareEmptyWithNonEmpty_12) {
  Slice a;
  Slice b("hello");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

}  // namespace leveldb
