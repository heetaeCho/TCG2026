// FoFiTrueType_cmpTrueTypeTableTagFunctor_test.cpp
// Unit tests for cmpTrueTypeTableTagFunctor (FoFiTrueType.cc)
//
// The TEST_ID is 48

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

// Minimal interface-only replicas from the provided snippet.
// NOTE: We do not infer any logic beyond the public fields and comparator signature.
struct TrueTypeTable {
  unsigned int tag = 0;
  unsigned int checksum = 0;
  int offset = 0;
  int origOffset = 0;
  int len = 0;
};

struct cmpTrueTypeTableTagFunctor {
  bool operator()(const TrueTypeTable& tab1, const TrueTypeTable& tab2) { return tab1.tag < tab2.tag; }
};

// Test fixture (kept for naming convention consistency across the suite style).
class cmpTrueTypeTableTagFunctorTest_48 : public ::testing::Test {
 protected:
  cmpTrueTypeTableTagFunctor cmp_;
};

TEST_F(cmpTrueTypeTableTagFunctorTest_48, ReturnsTrueWhenLeftTagIsSmaller_48) {
  TrueTypeTable a;
  TrueTypeTable b;
  a.tag = 1u;
  b.tag = 2u;

  EXPECT_TRUE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(cmpTrueTypeTableTagFunctorTest_48, ReturnsFalseWhenTagsAreEqual_48) {
  TrueTypeTable a;
  TrueTypeTable b;
  a.tag = 123456u;
  b.tag = 123456u;

  EXPECT_FALSE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(cmpTrueTypeTableTagFunctorTest_48, IgnoresOtherFieldsWhenComparing_48) {
  TrueTypeTable a;
  TrueTypeTable b;

  a.tag = 10u;
  b.tag = 11u;

  // Deliberately make other fields very different to ensure they don't affect ordering.
  a.checksum = 0xFFFFFFFFu;
  a.offset = -100;
  a.origOffset = 999;
  a.len = 1;

  b.checksum = 0u;
  b.offset = 100;
  b.origOffset = -999;
  b.len = 999999;

  EXPECT_TRUE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(cmpTrueTypeTableTagFunctorTest_48, BoundaryTagsZeroAndMaxUnsigned_48) {
  TrueTypeTable a;
  TrueTypeTable b;

  a.tag = 0u;
  b.tag = 0xFFFFFFFFu;  // Max for 32-bit unsigned; matches common TrueType tag storage size.

  EXPECT_TRUE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(cmpTrueTypeTableTagFunctorTest_48, WorksWithStdSortOrderingByTagAscending_48) {
  std::vector<TrueTypeTable> tabs(5);

  tabs[0].tag = 30u;
  tabs[1].tag = 10u;
  tabs[2].tag = 20u;
  tabs[3].tag = 20u;  // duplicate
  tabs[4].tag = 0u;

  std::sort(tabs.begin(), tabs.end(), cmpTrueTypeTableTagFunctor{});

  // Verify non-decreasing order by tag (stable order among equals is not required by std::sort).
  for (size_t i = 1; i < tabs.size(); ++i) {
    EXPECT_LE(tabs[i - 1].tag, tabs[i].tag);
  }

  EXPECT_EQ(tabs.front().tag, 0u);
  EXPECT_EQ(tabs.back().tag, 30u);
}

TEST_F(cmpTrueTypeTableTagFunctorTest_48, StrictWeakOrderingSanityForEqualElements_48) {
  // If tags are equal, comparator must return false both ways for strict weak ordering.
  TrueTypeTable a;
  TrueTypeTable b;
  TrueTypeTable c;

  a.tag = 42u;
  b.tag = 42u;
  c.tag = 100u;

  EXPECT_FALSE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));

  // Transitivity sanity: if a<b and b<c then a<c.
  EXPECT_TRUE(cmp_(a, c));
  EXPECT_TRUE(cmp_(b, c));
  EXPECT_FALSE(cmp_(c, a));
  EXPECT_FALSE(cmp_(c, b));
}