// slice_compare_test_13.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

// Helper to normalize sign of compare result.
static int Sign(int x) { return (x > 0) - (x < 0); }

// Normal equality: identical contents and length -> 0
TEST(SliceCompareTest_13, EqualStringsReturnZero_13) {
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(0, a.compare(b));
  EXPECT_EQ(0, b.compare(a));
}

// Normal ordering: differs within common prefix
TEST(SliceCompareTest_13, LexicographicallyLessWithinPrefix_13) {
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_GT(b.compare(a), 0);
}

// Boundary: one is a prefix of the other
TEST(SliceCompareTest_13, PrefixShorterIsLess_13) {
  Slice short_s("abc");
  Slice long_s("abcd");
  EXPECT_LT(short_s.compare(long_s), 0);
  EXPECT_GT(long_s.compare(short_s), 0);
}

// Boundary: empty vs empty
TEST(SliceCompareTest_13, EmptyVsEmptyIsEqual_13) {
  Slice a("");
  Slice b("");
  EXPECT_EQ(0, a.compare(b));
  EXPECT_EQ(0, b.compare(a));
}

// Boundary: empty vs non-empty
TEST(SliceCompareTest_13, EmptyIsLessThanNonEmpty_13) {
  Slice empty("");
  Slice nonempty("x");
  EXPECT_LT(empty.compare(nonempty), 0);
  EXPECT_GT(nonempty.compare(empty), 0);
}

// Binary safety: embedded NULs compared by length-aware interface (ptr+len)
TEST(SliceCompareTest_13, EmbeddedNullBytesHandled_13) {
  const char x_data[] = {'a', '\0', 'b'};
  const char y_data[] = {'a', '\0', 'c'};
  Slice x(x_data, sizeof(x_data));
  Slice y(y_data, sizeof(y_data));
  EXPECT_LT(x.compare(y), 0);
  EXPECT_GT(y.compare(x), 0);
}

// Binary safety: equal min prefix but different sizes decides order
TEST(SliceCompareTest_13, SizeTiebreakAfterEqualPrefix_13) {
  const char base[] = {'a', 'b', 'c', 'd'};
  Slice short_s(base, 3); // "abc"
  Slice long_s(base, 4);  // "abcd"
  EXPECT_LT(short_s.compare(long_s), 0);
  EXPECT_GT(long_s.compare(short_s), 0);
}

// Consistency: self-compare is zero
TEST(SliceCompareTest_13, SelfCompareIsZero_13) {
  std::string s = "leveldb";
  Slice a(s);
  EXPECT_EQ(0, a.compare(a));
}

// Relational properties: antisymmetry (sign flip)
TEST(SliceCompareTest_13, AntisymmetryOfCompare_13) {
  Slice a("foo");
  Slice b("foobar");
  int ab = Sign(a.compare(b));
  int ba = Sign(b.compare(a));
  EXPECT_EQ(-ab, ba);
}

// Transitivity sanity check: a < b and b < c implies a < c (observable ordering)
TEST(SliceCompareTest_13, TransitivitySanity_13) {
  Slice a("a");
  Slice b("ab");
  Slice c("ac");
  EXPECT_LT(a.compare(b), 0);
  EXPECT_LT(b.compare(c), 0);
  EXPECT_LT(a.compare(c), 0);
}
