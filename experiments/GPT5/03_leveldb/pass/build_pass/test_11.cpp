// File: slice_eq_operator_test_11.cc
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>

using leveldb::Slice;

class SliceEqualityTest_11 : public ::testing::Test {};

// Normal operation: same content, different backing storage
TEST_F(SliceEqualityTest_11, EqualDifferentStorageSameContent_11) {
  std::string a = "hello world";
  std::string b = "hello world";
  Slice sa(a);
  Slice sb(b);
  EXPECT_TRUE(sa == sb);
  EXPECT_TRUE(sb == sa);  // symmetry
}

// Boundary: both empty slices
TEST_F(SliceEqualityTest_11, EmptySlicesAreEqual_11) {
  Slice s1;           // default-constructed: empty
  Slice s2("");       // from C-string: empty
  EXPECT_TRUE(s1 == s2);
  EXPECT_TRUE(s2 == s1);
}

// Boundary: reflexivity
TEST_F(SliceEqualityTest_11, Reflexive_11) {
  Slice s("x", 1);
  EXPECT_TRUE(s == s);
}

// Unequal: same prefix but different sizes
TEST_F(SliceEqualityTest_11, DifferentSizesNotEqual_11) {
  Slice short_s("abc", 2);     // "ab"
  Slice long_s("abc", 3);      // "abc"
  EXPECT_FALSE(short_s == long_s);
  EXPECT_FALSE(long_s == short_s);
}

// Unequal: same size, different content
TEST_F(SliceEqualityTest_11, SameSizeDifferentContentNotEqual_11) {
  Slice s1("abcd", 4);
  Slice s2("abce", 4);
  EXPECT_FALSE(s1 == s2);
  EXPECT_FALSE(s2 == s1);
}

// Normal operation: equal when pointing to same memory and same size
TEST_F(SliceEqualityTest_11, SamePointerSameSizeEqual_11) {
  const char* p = "leveldb";
  Slice s1(p, 7);
  Slice s2(p, 7);
  EXPECT_TRUE(s1 == s2);
}

// Boundary/edge: embedded null bytes treated as data (length-aware)
TEST_F(SliceEqualityTest_11, EmbeddedNullsEquality_11) {
  const char with_null1[] = {'a', '\0', 'b'};
  const char with_null2[] = {'a', '\0', 'b'};
  Slice s1(with_null1, 3);
  Slice s2(with_null2, 3);
  EXPECT_TRUE(s1 == s2);
}

// Edge: embedded nulls but differing trailing byte
TEST_F(SliceEqualityTest_11, EmbeddedNullsDifferentContentNotEqual_11) {
  const char x[] = {'a', '\0', 'b'};
  const char y[] = {'a', '\0', 'c'};
  Slice sx(x, 3);
  Slice sy(y, 3);
  EXPECT_FALSE(sx == sy);
  EXPECT_FALSE(sy == sx);
}

// Boundary: same memory, different sizes (one is a prefix) -> not equal
TEST_F(SliceEqualityTest_11, SamePointerDifferentSizesNotEqual_11) {
  const char* p = "abcdef";
  Slice s_full(p, 6);
  Slice s_prefix(p, 3);
  EXPECT_FALSE(s_full == s_prefix);
  EXPECT_FALSE(s_prefix == s_full);
}
