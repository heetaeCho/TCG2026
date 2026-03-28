// -*- mode: c++; -*-
// TEST_ID: 491
//
// Unit tests for GfxPattern::getPatternRefNum() (black-box interface tests)
//
// Constraints honored:
// - No re-implementation/inference of internal logic
// - Only uses observable behavior via public interface
// - No private state access
// - No mocking (no external collaborators involved in the provided interface)

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

class GfxPatternTest_491 : public ::testing::Test {};

// Normal operation: should return the ref num passed at construction.
TEST_F(GfxPatternTest_491, GetPatternRefNum_ReturnsCtorValue_491) {
  const int type = 0;
  const int refNum = 123;

  GfxPattern p(type, refNum);
  EXPECT_EQ(p.getPatternRefNum(), refNum);
}

// Boundary: zero ref num.
TEST_F(GfxPatternTest_491, GetPatternRefNum_AllowsZero_491) {
  const int type = 1;
  const int refNum = 0;

  GfxPattern p(type, refNum);
  EXPECT_EQ(p.getPatternRefNum(), refNum);
}

// Boundary: negative ref num (should be returned as-is if allowed by interface).
TEST_F(GfxPatternTest_491, GetPatternRefNum_AllowsNegative_491) {
  const int type = 2;
  const int refNum = -7;

  GfxPattern p(type, refNum);
  EXPECT_EQ(p.getPatternRefNum(), refNum);
}

// Boundary: extreme int values.
TEST_F(GfxPatternTest_491, GetPatternRefNum_IntMin_491) {
  const int type = 3;
  const int refNum = std::numeric_limits<int>::min();

  GfxPattern p(type, refNum);
  EXPECT_EQ(p.getPatternRefNum(), refNum);
}

TEST_F(GfxPatternTest_491, GetPatternRefNum_IntMax_491) {
  const int type = 4;
  const int refNum = std::numeric_limits<int>::max();

  GfxPattern p(type, refNum);
  EXPECT_EQ(p.getPatternRefNum(), refNum);
}

// Normal operation: multiple instances keep their own values.
TEST_F(GfxPatternTest_491, GetPatternRefNum_MultipleInstancesIndependent_491) {
  GfxPattern p1(0, 10);
  GfxPattern p2(0, 20);
  GfxPattern p3(1, 10);

  EXPECT_EQ(p1.getPatternRefNum(), 10);
  EXPECT_EQ(p2.getPatternRefNum(), 20);
  EXPECT_EQ(p3.getPatternRefNum(), 10);
}

// Exceptional/error cases:
// For the provided interface, there is no observable error signaling (no throws,
// no error return codes), so no exception-focused tests are applicable.