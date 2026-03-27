// TEST_ID 350
// File: function_getDomainMax_350_test.cpp

#include <gtest/gtest.h>

#include "poppler/Function.h"

// Test helper that only exposes a controlled way to set up observable inputs for getDomainMax().
// This does NOT re-implement Function logic; it only prepares state via protected inheritance.
class TestableFunction_350 : public Function {
public:
  void SetDomainEntry(int i, double minV, double maxV) {
    domain[i][0] = minV;
    domain[i][1] = maxV;
  }
};

class FunctionTest_350 : public ::testing::Test {
protected:
  TestableFunction_350 func;
};

TEST_F(FunctionTest_350, GetDomainMax_ReturnsConfiguredMaxAtIndex0_350) {
  func.SetDomainEntry(0, -1.0, 2.5);
  EXPECT_DOUBLE_EQ(func.getDomainMax(0), 2.5);
}

TEST_F(FunctionTest_350, GetDomainMax_ReturnsConfiguredMaxAtHighIndex_350) {
  // Boundary within the known max inputs (commonly 32 in this codebase).
  // We only validate observable behavior for a valid index we configure.
  const int idx = 31;
  func.SetDomainEntry(idx, 10.0, 99.0);
  EXPECT_DOUBLE_EQ(func.getDomainMax(idx), 99.0);
}

TEST_F(FunctionTest_350, GetDomainMax_AllowsNegativeMaxValues_350) {
  func.SetDomainEntry(3, -10.0, -0.125);
  EXPECT_DOUBLE_EQ(func.getDomainMax(3), -0.125);
}

TEST_F(FunctionTest_350, GetDomainMax_IndependentAcrossIndices_350) {
  func.SetDomainEntry(1, 0.0, 1.0);
  func.SetDomainEntry(2, 5.0, 6.0);

  EXPECT_DOUBLE_EQ(func.getDomainMax(1), 1.0);
  EXPECT_DOUBLE_EQ(func.getDomainMax(2), 6.0);
}

TEST_F(FunctionTest_350, GetDomainMax_PreservesLargeMagnitudeDouble_350) {
  const double big = 1.234567890123456e300;
  func.SetDomainEntry(4, -big, big);
  EXPECT_DOUBLE_EQ(func.getDomainMax(4), big);
}