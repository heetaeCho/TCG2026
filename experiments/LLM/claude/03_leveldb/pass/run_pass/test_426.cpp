#include "gtest/gtest.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test that BytewiseComparator returns a non-null pointer
TEST(BytewiseComparatorTest_426, ReturnsNonNull_426) {
  const Comparator* cmp = BytewiseComparator();
  ASSERT_NE(cmp, nullptr);
}

// Test that BytewiseComparator returns the same instance (singleton)
TEST(BytewiseComparatorTest_426, ReturnsSameInstance_426) {
  const Comparator* cmp1 = BytewiseComparator();
  const Comparator* cmp2 = BytewiseComparator();
  EXPECT_EQ(cmp1, cmp2);
}

// Test that the comparator has a non-empty name
TEST(BytewiseComparatorTest_426, HasName_426) {
  const Comparator* cmp = BytewiseComparator();
  const char* name = cmp->Name();
  ASSERT_NE(name, nullptr);
  EXPECT_GT(strlen(name), 0u);
}

// Test Compare: equal slices
TEST(BytewiseComparatorTest_426, CompareEqual_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(cmp->Compare(a, b), 0);
}

// Test Compare: first slice is less than second
TEST(BytewiseComparatorTest_426, CompareLessThan_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("abc");
  Slice b("abd");
  EXPECT_LT(cmp->Compare(a, b), 0);
}

// Test Compare: first slice is greater than second
TEST(BytewiseComparatorTest_426, CompareGreaterThan_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("abd");
  Slice b("abc");
  EXPECT_GT(cmp->Compare(a, b), 0);
}

// Test Compare: empty slices are equal
TEST(BytewiseComparatorTest_426, CompareEmptySlices_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("");
  Slice b("");
  EXPECT_EQ(cmp->Compare(a, b), 0);
}

// Test Compare: empty slice is less than non-empty slice
TEST(BytewiseComparatorTest_426, CompareEmptyVsNonEmpty_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("");
  Slice b("a");
  EXPECT_LT(cmp->Compare(a, b), 0);
}

// Test Compare: non-empty slice is greater than empty slice
TEST(BytewiseComparatorTest_426, CompareNonEmptyVsEmpty_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("a");
  Slice b("");
  EXPECT_GT(cmp->Compare(a, b), 0);
}

// Test Compare: prefix relationship - shorter is less
TEST(BytewiseComparatorTest_426, ComparePrefixShorterIsLess_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("abc");
  Slice b("abcd");
  EXPECT_LT(cmp->Compare(a, b), 0);
}

// Test Compare: prefix relationship - longer is greater
TEST(BytewiseComparatorTest_426, ComparePrefixLongerIsGreater_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("abcd");
  Slice b("abc");
  EXPECT_GT(cmp->Compare(a, b), 0);
}

// Test FindShortestSeparator: result should be >= start and <= limit
TEST(BytewiseComparatorTest_426, FindShortestSeparatorBasic_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string start = "abc";
  Slice limit("abd");
  std::string original_start = start;
  cmp->FindShortestSeparator(&start, limit);
  // The result should be >= original start
  EXPECT_GE(cmp->Compare(Slice(start), Slice(original_start)), 0);
  // The result should be <= limit
  EXPECT_LE(cmp->Compare(Slice(start), limit), 0);
}

// Test FindShortestSeparator: when start == limit, start should not change or remain valid
TEST(BytewiseComparatorTest_426, FindShortestSeparatorEqualStartAndLimit_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string start = "abc";
  Slice limit("abc");
  std::string original_start = start;
  cmp->FindShortestSeparator(&start, limit);
  // Result should be >= original start and <= limit
  EXPECT_GE(cmp->Compare(Slice(start), Slice(original_start)), 0);
  EXPECT_LE(cmp->Compare(Slice(start), limit), 0);
}

// Test FindShortestSeparator: when start > limit, start should remain unchanged
TEST(BytewiseComparatorTest_426, FindShortestSeparatorStartGreaterThanLimit_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string start = "abd";
  Slice limit("abc");
  std::string original_start = start;
  cmp->FindShortestSeparator(&start, limit);
  // When start > limit, typically start remains unchanged
  EXPECT_EQ(start, original_start);
}

// Test FindShortSuccessor: result should be >= start
TEST(BytewiseComparatorTest_426, FindShortSuccessorBasic_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string key = "abc";
  std::string original_key = key;
  cmp->FindShortSuccessor(&key);
  // The result should be >= the original key
  EXPECT_GE(cmp->Compare(Slice(key), Slice(original_key)), 0);
}

// Test FindShortSuccessor with empty key
TEST(BytewiseComparatorTest_426, FindShortSuccessorEmptyKey_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string key = "";
  cmp->FindShortSuccessor(&key);
  // Result should be >= empty string
  EXPECT_GE(cmp->Compare(Slice(key), Slice("")), 0);
}

// Test FindShortSuccessor: result should be shorter or equal in length, or be a valid successor
TEST(BytewiseComparatorTest_426, FindShortSuccessorShortensKey_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string key = "abcdef";
  std::string original_key = key;
  cmp->FindShortSuccessor(&key);
  EXPECT_GE(cmp->Compare(Slice(key), Slice(original_key)), 0);
  // Typically the successor should be no longer than the original
  EXPECT_LE(key.size(), original_key.size());
}

// Test Compare with binary data (including null bytes)
TEST(BytewiseComparatorTest_426, CompareWithNullBytes_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string s1("ab\0c", 4);
  std::string s2("ab\0d", 4);
  Slice a(s1);
  Slice b(s2);
  EXPECT_LT(cmp->Compare(a, b), 0);
}

// Test Compare: single character slices
TEST(BytewiseComparatorTest_426, CompareSingleCharacters_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("a");
  Slice b("b");
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  EXPECT_EQ(cmp->Compare(a, a), 0);
}

// Test Compare: transitivity
TEST(BytewiseComparatorTest_426, CompareTransitivity_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("a");
  Slice b("b");
  Slice c("c");
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_LT(cmp->Compare(b, c), 0);
  EXPECT_LT(cmp->Compare(a, c), 0);
}

// Test Compare: antisymmetry
TEST(BytewiseComparatorTest_426, CompareAntisymmetry_426) {
  const Comparator* cmp = BytewiseComparator();
  Slice a("abc");
  Slice b("def");
  int cmp_ab = cmp->Compare(a, b);
  int cmp_ba = cmp->Compare(b, a);
  // If a < b then b > a
  if (cmp_ab < 0) {
    EXPECT_GT(cmp_ba, 0);
  } else if (cmp_ab > 0) {
    EXPECT_LT(cmp_ba, 0);
  } else {
    EXPECT_EQ(cmp_ba, 0);
  }
}

// Test FindShortestSeparator with wide gap between start and limit
TEST(BytewiseComparatorTest_426, FindShortestSeparatorWideGap_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string start = "aaa";
  Slice limit("zzz");
  std::string original_start = start;
  cmp->FindShortestSeparator(&start, limit);
  EXPECT_GE(cmp->Compare(Slice(start), Slice(original_start)), 0);
  EXPECT_LE(cmp->Compare(Slice(start), limit), 0);
}

// Test FindShortestSeparator: start is prefix of limit
TEST(BytewiseComparatorTest_426, FindShortestSeparatorPrefixRelation_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string start = "abc";
  Slice limit("abcdef");
  std::string original_start = start;
  cmp->FindShortestSeparator(&start, limit);
  EXPECT_GE(cmp->Compare(Slice(start), Slice(original_start)), 0);
  EXPECT_LE(cmp->Compare(Slice(start), limit), 0);
}

// Test FindShortSuccessor with all 0xFF bytes
TEST(BytewiseComparatorTest_426, FindShortSuccessorAllMaxBytes_426) {
  const Comparator* cmp = BytewiseComparator();
  std::string key(3, '\xff');
  std::string original_key = key;
  cmp->FindShortSuccessor(&key);
  // Result should still be >= original
  EXPECT_GE(cmp->Compare(Slice(key), Slice(original_key)), 0);
}

}  // namespace leveldb
