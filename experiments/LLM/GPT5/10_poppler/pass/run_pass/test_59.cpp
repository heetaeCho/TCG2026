// File: Object_operator_less_59_test.cpp
// Unit tests for: inline bool operator<(const Ref lhs, const Ref rhs) noexcept
// From: ./TestProjects/poppler/poppler/Object.h

#include <gtest/gtest.h>

#include "poppler/Object.h" // Provides Ref and operator<

// The TEST_ID is 59

namespace {

class RefLessOperatorTest_59 : public ::testing::Test {};

TEST_F(RefLessOperatorTest_59, NumSmallerReturnsTrue_59) {
  const Ref lhs{1, 999};
  const Ref rhs{2, 0};

  EXPECT_TRUE(lhs < rhs);
  EXPECT_FALSE(rhs < lhs);
}

TEST_F(RefLessOperatorTest_59, NumGreaterReturnsFalse_59) {
  const Ref lhs{10, 0};
  const Ref rhs{3, 999};

  EXPECT_FALSE(lhs < rhs);
  EXPECT_TRUE(rhs < lhs);
}

TEST_F(RefLessOperatorTest_59, NumEqualGenSmallerReturnsTrue_59) {
  const Ref lhs{7, 1};
  const Ref rhs{7, 2};

  EXPECT_TRUE(lhs < rhs);
  EXPECT_FALSE(rhs < lhs);
}

TEST_F(RefLessOperatorTest_59, NumEqualGenGreaterReturnsFalse_59) {
  const Ref lhs{7, 9};
  const Ref rhs{7, 2};

  EXPECT_FALSE(lhs < rhs);
  EXPECT_TRUE(rhs < lhs);
}

TEST_F(RefLessOperatorTest_59, EqualNumAndGenReturnsFalseBothWays_59) {
  const Ref lhs{42, 24};
  const Ref rhs{42, 24};

  EXPECT_FALSE(lhs < rhs);
  EXPECT_FALSE(rhs < lhs);
}

TEST_F(RefLessOperatorTest_59, BoundaryValues_IntMinAndIntMax_59) {
  const int kMin = std::numeric_limits<int>::min();
  const int kMax = std::numeric_limits<int>::max();

  // num decides first
  {
    const Ref lhs{kMin, kMax};
    const Ref rhs{kMax, kMin};
    EXPECT_TRUE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
  }

  // when num equal, gen decides
  {
    const Ref lhs{0, kMin};
    const Ref rhs{0, kMax};
    EXPECT_TRUE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
  }
}

TEST_F(RefLessOperatorTest_59, SortingOrdersByNumThenGen_59) {
  // This verifies observable behavior when used in ordering contexts.
  // We don't assume implementation beyond operator< semantics.
  std::vector<Ref> refs = {
      Ref{2, 5}, Ref{1, 9}, Ref{2, 1}, Ref{1, 3}, Ref{2, 5}, Ref{1, 3},
  };

  std::sort(refs.begin(), refs.end()); // uses operator<

  // Expected: (1,3), (1,3), (1,9), (2,1), (2,5), (2,5)
  ASSERT_EQ(refs.size(), 6u);
  EXPECT_EQ(refs[0].num, 1);
  EXPECT_EQ(refs[0].gen, 3);
  EXPECT_EQ(refs[1].num, 1);
  EXPECT_EQ(refs[1].gen, 3);
  EXPECT_EQ(refs[2].num, 1);
  EXPECT_EQ(refs[2].gen, 9);
  EXPECT_EQ(refs[3].num, 2);
  EXPECT_EQ(refs[3].gen, 1);
  EXPECT_EQ(refs[4].num, 2);
  EXPECT_EQ(refs[4].gen, 5);
  EXPECT_EQ(refs[5].num, 2);
  EXPECT_EQ(refs[5].gen, 5);
}

TEST_F(RefLessOperatorTest_59, StrictWeakOrderingSanity_59) {
  // A few properties expected of a less-than comparator used for ordering.
  const Ref a{1, 1};
  const Ref b{1, 2};
  const Ref c{2, 0};

  // Irreflexive
  EXPECT_FALSE(a < a);
  EXPECT_FALSE(b < b);
  EXPECT_FALSE(c < c);

  // Transitive (a < b and b < c => a < c)
  ASSERT_TRUE(a < b);
  ASSERT_TRUE(b < c);
  EXPECT_TRUE(a < c);

  // Asymmetric (a < b => !(b < a))
  EXPECT_FALSE(b < a);
}

} // namespace