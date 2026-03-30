// File: slice_not_equal_test.cc
#include <gtest/gtest.h>
#include "leveldb/slice.h"

using leveldb::Slice;

namespace {

TEST(SliceNotEqualTest_12, ReflexiveSelfComparison_False_12) {
  Slice a("abc");
  EXPECT_FALSE(a != a);
}

TEST(SliceNotEqualTest_12, IdenticalContent_FromCStr_False_12) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_FALSE(a != b);
  EXPECT_FALSE(b != a); // symmetry
}

TEST(SliceNotEqualTest_12, CopyConstructedSlices_False_12) {
  Slice a("leveldb");
  Slice b = a; // copy
  EXPECT_FALSE(a != b);
  EXPECT_FALSE(b != a);
}

TEST(SliceNotEqualTest_12, DifferentContent_SameSize_True_12) {
  Slice a("abc");
  Slice b("abx");
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(b != a);
}

TEST(SliceNotEqualTest_12, DifferentSizes_True_12) {
  Slice a("abc");
  Slice b("ab");
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(b != a);
}

TEST(SliceNotEqualTest_12, EmptyVsEmpty_False_12) {
  Slice a;        // default-constructed empty
  Slice b("");    // empty c-string
  EXPECT_FALSE(a != b);
  EXPECT_FALSE(b != a);
}

TEST(SliceNotEqualTest_12, EmptyVsNonEmpty_True_12) {
  Slice empty;
  Slice non_empty("x");
  EXPECT_TRUE(empty != non_empty);
  EXPECT_TRUE(non_empty != empty);
}

TEST(SliceNotEqualTest_12, EmbeddedNulls_EqualBytes_False_12) {
  const char s1[] = {'a', '\0', 'b'};
  const char s2[] = {'a', '\0', 'b'};
  Slice a(s1, sizeof(s1));
  Slice b(s2, sizeof(s2));
  EXPECT_FALSE(a != b);
  EXPECT_FALSE(b != a);
}

TEST(SliceNotEqualTest_12, EmbeddedNulls_DifferentBytes_True_12) {
  const char s1[] = {'a', '\0', 'b'};
  const char s2[] = {'a', '\0', 'c'};
  Slice a(s1, sizeof(s1));
  Slice b(s2, sizeof(s2));
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(b != a);
}

TEST(SliceNotEqualTest_12, TemporaryConstruction_EqualContent_False_12) {
  EXPECT_FALSE(Slice("xyz") != Slice(std::string("xyz")));
}

} // namespace
