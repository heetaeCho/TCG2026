// TEST_ID: 46
//
// Unit tests for cmpTrueTypeLocaOffsetFunctor in:
//   ./TestProjects/poppler/fofi/FoFiTrueType.cc
//
// Constraints note:
// - Treat as black box: we only verify observable comparator behavior via operator() results
//   and effects when used with standard algorithms (std::sort).
// - No private state access, no re-implementation beyond calling the public operator().

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

// Include the real header if available in your build.
// If the production code provides these via a header, prefer including it instead.
// For this exercise, we rely on the provided declarations.
struct TrueTypeLoca {
  int idx = 0;
  int newOffset = 0;
};

struct cmpTrueTypeLocaOffsetFunctor {
  bool operator()(const TrueTypeLoca loca1, const TrueTypeLoca loca2);
};

// If your build links the real implementation from FoFiTrueType.cc, do NOT define operator()
// here. The test should compile and link against the production object/library.

class CmpTrueTypeLocaOffsetFunctorTest_46 : public ::testing::Test {
 protected:
  cmpTrueTypeLocaOffsetFunctor cmp_;
};

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, ReturnsFalseForIdenticalObjects_46) {
  TrueTypeLoca a;
  a.idx = 7;
  a.newOffset = 123;

  // Comparator should be strict-weak-ordering style: a is not less than itself.
  EXPECT_FALSE(cmp_(a, a));
}

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, ImposesOrderByOffsetWhenOffsetsDiffer_46) {
  TrueTypeLoca a;
  a.idx = 1;
  a.newOffset = 10;

  TrueTypeLoca b;
  b.idx = 999;       // idx shouldn't matter if offsets differ
  b.newOffset = 20;

  EXPECT_TRUE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, BreaksTiesByIdxWhenOffsetsEqual_46) {
  TrueTypeLoca a;
  a.idx = 1;
  a.newOffset = 100;

  TrueTypeLoca b;
  b.idx = 2;
  b.newOffset = 100;

  EXPECT_TRUE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, TieWithEqualOffsetAndIdxIsNotLessEitherWay_46) {
  TrueTypeLoca a;
  a.idx = 5;
  a.newOffset = 42;

  TrueTypeLoca b;
  b.idx = 5;
  b.newOffset = 42;

  EXPECT_FALSE(cmp_(a, b));
  EXPECT_FALSE(cmp_(b, a));
}

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, BoundaryOffsetsIncludingNegativeAndZero_46) {
  TrueTypeLoca neg;
  neg.idx = 0;
  neg.newOffset = -1;

  TrueTypeLoca zero;
  zero.idx = 0;
  zero.newOffset = 0;

  TrueTypeLoca pos;
  pos.idx = 0;
  pos.newOffset = 1;

  EXPECT_TRUE(cmp_(neg, zero));
  EXPECT_TRUE(cmp_(zero, pos));
  EXPECT_TRUE(cmp_(neg, pos));

  EXPECT_FALSE(cmp_(zero, neg));
  EXPECT_FALSE(cmp_(pos, zero));
  EXPECT_FALSE(cmp_(pos, neg));
}

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SortOrdersByOffsetThenIdx_46) {
  // Mix offsets and duplicate offsets with varying idx to validate observable ordering via std::sort.
  TrueTypeLoca t1{3, 200};  // (idx=3, offset=200)
  TrueTypeLoca t2{1, 100};  // (idx=1, offset=100)
  TrueTypeLoca t3{2, 100};  // (idx=2, offset=100)
  TrueTypeLoca t4{0, 50};   // (idx=0, offset=50)
  TrueTypeLoca t5{9, 200};  // (idx=9, offset=200)

  std::vector<TrueTypeLoca> v{t1, t2, t3, t4, t5};

  std::sort(v.begin(), v.end(), cmp_);

  // Expect ascending by newOffset, then by idx for equal offsets.
  ASSERT_EQ(v.size(), 5u);

  EXPECT_EQ(v[0].newOffset, 50);
  EXPECT_EQ(v[0].idx, 0);

  EXPECT_EQ(v[1].newOffset, 100);
  EXPECT_EQ(v[1].idx, 1);

  EXPECT_EQ(v[2].newOffset, 100);
  EXPECT_EQ(v[2].idx, 2);

  EXPECT_EQ(v[3].newOffset, 200);
  EXPECT_EQ(v[3].idx, 3);

  EXPECT_EQ(v[4].newOffset, 200);
  EXPECT_EQ(v[4].idx, 9);
}

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, StrictWeakOrderingSanity_NoMutualLess_46) {
  TrueTypeLoca a{1, 10};
  TrueTypeLoca b{2, 10};  // same offset, higher idx

  // For strict weak ordering: cannot have both a<b and b<a true simultaneously.
  const bool ab = cmp_(a, b);
  const bool ba = cmp_(b, a);

  EXPECT_NE(ab, ba);  // one true, the other false in this setup
  EXPECT_TRUE(ab);
  EXPECT_FALSE(ba);
}