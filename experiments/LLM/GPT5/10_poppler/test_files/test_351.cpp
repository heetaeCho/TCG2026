// TEST_ID: 351
// Unit tests for poppler::Function (Function.h)

#include <gtest/gtest.h>

#include "poppler/Function.h"

namespace {

// Test helper that allows controlled setup via protected members (no assumptions about parsing/init).
class TestFunction_351 final : public Function {
public:
  using Function::Function;

  void SetRange(int i, double minV, double maxV) {
    range[i][0] = minV;
    range[i][1] = maxV;
    hasRange = true;
  }
};

class FunctionTest_351 : public ::testing::Test {};

} // namespace

TEST_F(FunctionTest_351, GetRangeMinReturnsPreviouslySetMin_351) {
  TestFunction_351 f;
  f.SetRange(0, -3.5, 9.25);

  EXPECT_DOUBLE_EQ(f.getRangeMin(0), -3.5);
}

TEST_F(FunctionTest_351, GetRangeMinWorksOnConstObject_351) {
  TestFunction_351 f;
  f.SetRange(1, 0.0, 1.0);

  const TestFunction_351& cf = f;
  EXPECT_DOUBLE_EQ(cf.getRangeMin(1), 0.0);
}

TEST_F(FunctionTest_351, GetRangeMinIsIndependentOfMax_351) {
  TestFunction_351 f;
  f.SetRange(2, 1.25, 100.0);
  EXPECT_DOUBLE_EQ(f.getRangeMin(2), 1.25);

  // Change only max; min should remain unchanged.
  f.SetRange(2, 1.25, -999.0);
  EXPECT_DOUBLE_EQ(f.getRangeMin(2), 1.25);
}

TEST_F(FunctionTest_351, GetRangeMinDifferentIndicesDoNotInterfere_351) {
  TestFunction_351 f;
  f.SetRange(0, -1.0, 0.0);
  f.SetRange(3, 42.0, 43.0);

  EXPECT_DOUBLE_EQ(f.getRangeMin(0), -1.0);
  EXPECT_DOUBLE_EQ(f.getRangeMin(3), 42.0);
}

TEST_F(FunctionTest_351, GetRangeMinBoundaryIndexZero_351) {
  TestFunction_351 f;
  f.SetRange(0, 123.456, 789.0);

  EXPECT_DOUBLE_EQ(f.getRangeMin(0), 123.456);
}

TEST_F(FunctionTest_351, GetRangeMinBoundaryLastIndex_351) {
  // Based on the provided class definition: range is double[32][2], valid indices are [0..31].
  TestFunction_351 f;
  constexpr int kLast = 31;
  f.SetRange(kLast, -0.125, 0.125);

  EXPECT_DOUBLE_EQ(f.getRangeMin(kLast), -0.125);
}