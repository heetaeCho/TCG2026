// SPDX-License-Identifier: GPL-2.0-or-later
// File: function_getdomainmin_test.cpp
//
// Unit tests for poppler::Function (partial interface)
// Focus: Function::getDomainMin(int)
//
// The TEST_ID is 349

#include <gtest/gtest.h>

#include "poppler/Function.h"

// A small test double that lets us control the protected domain[][]
// without re-implementing any Function logic.
class TestFunction_349 : public Function {
public:
  using Function::Function;

  void SetDomain(int i, double minVal, double maxVal) {
    domain[i][0] = minVal;
    domain[i][1] = maxVal;
  }
};

class FunctionTest_349 : public ::testing::Test {
protected:
  TestFunction_349 func_;
};

TEST_F(FunctionTest_349, GetDomainMin_ReturnsValuePreviouslyStored_349) {
  func_.SetDomain(0, -3.25, 9.5);
  EXPECT_DOUBLE_EQ(func_.getDomainMin(0), -3.25);

  func_.SetDomain(1, 0.0, 1.0);
  EXPECT_DOUBLE_EQ(func_.getDomainMin(1), 0.0);
}

TEST_F(FunctionTest_349, GetDomainMin_HandlesNegativeValues_349) {
  func_.SetDomain(2, -123456.0, -1.0);
  EXPECT_DOUBLE_EQ(func_.getDomainMin(2), -123456.0);
}

TEST_F(FunctionTest_349, GetDomainMin_HandlesPositiveAndFractionalValues_349) {
  func_.SetDomain(3, 42.125, 100.0);
  EXPECT_DOUBLE_EQ(func_.getDomainMin(3), 42.125);
}

TEST_F(FunctionTest_349, GetDomainMin_BoundaryIndexZero_349) {
  func_.SetDomain(0, 7.0, 8.0);
  EXPECT_DOUBLE_EQ(func_.getDomainMin(0), 7.0);
}

TEST_F(FunctionTest_349, GetDomainMin_BoundaryHighIndex31_349) {
  // Based on the known/inferred dependency that Function stores domain[32][2].
  // We only test a valid in-bounds index; out-of-range behavior is unspecified.
  func_.SetDomain(31, -1.0, 1.0);
  EXPECT_DOUBLE_EQ(func_.getDomainMin(31), -1.0);
}