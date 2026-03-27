// Copyright (C) 2026
// Unit tests for Ref equality operator (Object.h)
//
// The TEST_ID is 57
//
// Notes:
// - Treat implementation as a black box: we only validate observable behavior of operator==
// - No access to private state (Ref is a struct with public members here anyway)
// - No mocking needed

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class RefEqualityTest_57 : public ::testing::Test {};

TEST_F(RefEqualityTest_57, EqualWhenNumAndGenMatch_57) {
  Ref a{1, 2};
  Ref b{1, 2};

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a); // symmetry
}

TEST_F(RefEqualityTest_57, NotEqualWhenNumDiffersButGenSame_57) {
  Ref a{1, 2};
  Ref b{2, 2};

  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == a);
}

TEST_F(RefEqualityTest_57, NotEqualWhenGenDiffersButNumSame_57) {
  Ref a{10, 3};
  Ref b{10, 4};

  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == a);
}

TEST_F(RefEqualityTest_57, NotEqualWhenBothNumAndGenDiffer_57) {
  Ref a{10, 3};
  Ref b{11, 4};

  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == a);
}

TEST_F(RefEqualityTest_57, BoundaryValuesZeroAndNegative_57) {
  // Boundary-ish inputs for ints: zero and negative.
  Ref zero{0, 0};
  Ref zero2{0, 0};
  Ref neg{-1, -1};
  Ref neg2{-1, -1};
  Ref mixed{-1, 0};

  EXPECT_TRUE(zero == zero2);
  EXPECT_TRUE(neg == neg2);

  EXPECT_FALSE(zero == neg);
  EXPECT_FALSE(neg == mixed);   // gen differs
  EXPECT_FALSE(mixed == neg);   // gen differs (symmetry)
}

TEST_F(RefEqualityTest_57, WorksWithInvalidRefConstant_57) {
  // If Ref::INVALID() exists and is usable, equality should behave consistently.
  // This is an observable, interface-level check: INVALID should equal itself,
  // and typically not equal a clearly different Ref.
  Ref invalid1 = Ref::INVALID();
  Ref invalid2 = Ref::INVALID();

  EXPECT_TRUE(invalid1 == invalid2);
  EXPECT_TRUE(invalid1 == invalid1);

  Ref other{1, 0};
  // We don't assume what INVALID's values are, but if it's truly "invalid",
  // it should not match a common-looking ref. If it does, this expectation
  // will catch it (and that would be an observable contract issue).
  EXPECT_FALSE(invalid1 == other);
}

TEST_F(RefEqualityTest_57, ReflexiveProperty_57) {
  Ref a{123, 456};
  EXPECT_TRUE(a == a);
}

TEST_F(RefEqualityTest_57, TransitivePropertyForEqualTriplet_57) {
  Ref a{7, 8};
  Ref b{7, 8};
  Ref c{7, 8};

  ASSERT_TRUE(a == b);
  ASSERT_TRUE(b == c);
  EXPECT_TRUE(a == c); // transitivity
}

} // namespace