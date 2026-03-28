// File: slice_starts_with_test_10.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

// Normal operation: typical positive case
TEST(SliceStartsWithTest_10, ReturnsTrueForValidPrefix_10) {
  Slice s("leveldb");
  Slice prefix("lev");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Normal operation: exact match is a prefix
TEST(SliceStartsWithTest_10, ReturnsTrueForExactMatch_10) {
  Slice s("abc");
  Slice prefix("abc");
  EXPECT_TRUE(s.starts_with(prefix));
}

// Boundary: empty prefix should always be true
TEST(SliceStartsWithTest_10, EmptyPrefixReturnsTrue_10) {
  Slice s("anything");
  Slice empty_prefix("");
  EXPECT_TRUE(s.starts_with(empty_prefix));
}

// Boundary: both empty -> true
TEST(SliceStartsWithTest_10, BothEmptyReturnsTrue_10) {
  Slice empty("");
  Slice empty_prefix("");
  EXPECT_TRUE(empty.starts_with(empty_prefix));
}

// Boundary/Exceptional (observable): receiver empty, non-empty prefix -> false
TEST(SliceStartsWithTest_10, EmptyReceiverNonEmptyPrefixReturnsFalse_10) {
  Slice empty("");
  Slice prefix("a");
  EXPECT_FALSE(empty.starts_with(prefix));
}

// Negative: first character differs -> false
TEST(SliceStartsWithTest_10, NonMatchingFirstCharacterReturnsFalse_10) {
  Slice s("abc");
  Slice prefix("x");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Boundary: prefix longer than receiver -> false
TEST(SliceStartsWithTest_10, PrefixLongerThanReceiverReturnsFalse_10) {
  Slice s("ab");
  Slice prefix("abc");
  EXPECT_FALSE(s.starts_with(prefix));
}

// Case sensitivity: verify comparison is case-sensitive (bytes)
TEST(SliceStartsWithTest_10, CaseSensitiveComparison_10) {
  Slice s("Hello");
  Slice lower_prefix("he");
  EXPECT_FALSE(s.starts_with(lower_prefix));  // 'H' != 'h'
}

// Binary data: handles embedded nulls (positive)
TEST(SliceStartsWithTest_10, HandlesEmbeddedNullBytesTrue_10) {
  const char data[] = {'a', '\0', 'b', 'c'};
  const char pre[]  = {'a', '\0'};
  Slice s(data, sizeof(data));
  Slice prefix(pre, sizeof(pre));
  EXPECT_TRUE(s.starts_with(prefix));
}

// Binary data: handles embedded nulls (negative mismatch later)
TEST(SliceStartsWithTest_10, HandlesEmbeddedNullBytesFalse_10) {
  const char data[] = {'a', '\0', 'b', 'c'};
  const char pre[]  = {'a', '\0', 'x'};
  Slice s(data, sizeof(data));
  Slice prefix(pre, sizeof(pre));
  EXPECT_FALSE(s.starts_with(prefix));
}
