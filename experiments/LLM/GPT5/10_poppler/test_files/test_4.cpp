// TEST_ID: 4
// Unit tests for GooCheckedOps checkedAdd<long long> specialization.
//
// File under test:
//   ./TestProjects/poppler/goo/GooCheckedOps.h
//
// Notes:
// - Treat implementation as a black box: only verify observable behavior:
//   * return value indicates overflow (true) vs no overflow (false)
//   * output parameter '*z' equals x+y when no overflow occurs
// - Do not rely on private/internal state (none exists here).

#include <gtest/gtest.h>

#include <limits>

#include "TestProjects/poppler/goo/GooCheckedOps.h"

class CheckedAddLongLongTest_4 : public ::testing::Test {};

TEST_F(CheckedAddLongLongTest_4, AddsTwoPositiveNumbers_NoOverflow_4) {
  long long z = 0;
  const long long x = 123;
  const long long y = 456;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, AddsPositiveAndNegative_NoOverflow_4) {
  long long z = 0;
  const long long x = 1000;
  const long long y = -250;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, AddsTwoNegativeNumbers_NoOverflow_4) {
  long long z = 0;
  const long long x = -10;
  const long long y = -20;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, AddsWithZero_NoOverflow_4) {
  long long z = 12345;
  const long long x = 0;
  const long long y = -999;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, MaxPlusOne_Overflows_4) {
  long long z = 777;  // sentinel
  const long long x = (std::numeric_limits<long long>::max)();
  const long long y = 1;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddLongLongTest_4, MinMinusOne_Overflows_4) {
  long long z = -777;  // sentinel
  const long long x = (std::numeric_limits<long long>::min)();
  const long long y = -1;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddLongLongTest_4, Boundary_NoOverflow_MaxPlusZero_4) {
  long long z = 0;
  const long long x = (std::numeric_limits<long long>::max)();
  const long long y = 0;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, Boundary_NoOverflow_MinPlusZero_4) {
  long long z = 0;
  const long long x = (std::numeric_limits<long long>::min)();
  const long long y = 0;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, Boundary_NoOverflow_MaxPlusNegativeOne_4) {
  long long z = 0;
  const long long x = (std::numeric_limits<long long>::max)();
  const long long y = -1;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, Boundary_NoOverflow_MinPlusOne_4) {
  long long z = 0;
  const long long x = (std::numeric_limits<long long>::min)();
  const long long y = 1;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, x + y);
}

TEST_F(CheckedAddLongLongTest_4, OverflowWhenBothPositiveNearMax_4) {
  long long z = 0;
  const long long x = (std::numeric_limits<long long>::max)() - 10;
  const long long y = 11;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_TRUE(overflow);
}

TEST_F(CheckedAddLongLongTest_4, OverflowWhenBothNegativeNearMin_4) {
  long long z = 0;
  const long long x = (std::numeric_limits<long long>::min)() + 10;
  const long long y = -11;

  const bool overflow = checkedAdd<long long>(x, y, &z);

  EXPECT_TRUE(overflow);
}