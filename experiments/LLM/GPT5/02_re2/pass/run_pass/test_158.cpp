// File: regexp_cap_test_158.cc
#include <climits>
#include "gtest/gtest.h"
#include "re2/regexp.h"

using re2::Regexp;

class RegexpCapTest_158 : public ::testing::Test {};

// Normal operation: cap() returns the capture index provided to the factory.
TEST_F(RegexpCapTest_158, CaptureReturnsAssignedCap_158) {
  auto flags = static_cast<typename Regexp::ParseFlags>(0);

  Regexp* sub = Regexp::HaveMatch(123, flags);
  ASSERT_NE(nullptr, sub) << "HaveMatch should produce a valid sub-regexp";

  Regexp* r = Regexp::Capture(sub, flags, /*cap=*/7);
  ASSERT_NE(nullptr, r) << "Capture should succeed with a valid sub-regexp";
  EXPECT_EQ(7, r->cap());

  // Avoid relying on ownership semantics of 'sub' (Capture may consume it).
  // Only Decref the top-level if available.
  r->Decref();
}

// Boundary: cap() with zero (lowest non-negative boundary commonly used for group ids).
TEST_F(RegexpCapTest_158, ZeroCapBoundary_158) {
  auto flags = static_cast<typename Regexp::ParseFlags>(0);

  Regexp* sub = Regexp::HaveMatch(1, flags);
  ASSERT_NE(nullptr, sub);

  Regexp* r = Regexp::Capture(sub, flags, /*cap=*/0);
  ASSERT_NE(nullptr, r);
  EXPECT_EQ(0, r->cap());

  r->Decref();
}

// Boundary: Large positive capture index should be returned unchanged.
TEST_F(RegexpCapTest_158, LargeCapBoundary_158) {
  auto flags = static_cast<typename Regexp::ParseFlags>(0);

  Regexp* sub = Regexp::HaveMatch(42, flags);
  ASSERT_NE(nullptr, sub);

  const int kLargeCap = INT_MAX / 2;  // Large but safe integer.
  Regexp* r = Regexp::Capture(sub, flags, kLargeCap);
  ASSERT_NE(nullptr, r);
  EXPECT_EQ(kLargeCap, r->cap());

  r->Decref();
}
