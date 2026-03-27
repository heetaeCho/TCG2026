// File: Function_getInputSize_347_test.cpp

#include <gtest/gtest.h>

#include "poppler/Function.h"

// These tests treat Function as a black box for observable behavior.
// To *arrange* different input sizes, we use a small derived helper that can
// set the protected member used by getInputSize(). We only assert through the
// public API (getInputSize()).

namespace {

class TestFunction_347 : public Function {
public:
  TestFunction_347() : Function() {}

  void setInputSizeForTest(int v) { m = v; }
};

} // namespace

TEST(FunctionTest_347, GetInputSize_IsStableAcrossRepeatedCalls_347) {
  TestFunction_347 f;

  const int a = f.getInputSize();
  const int b = f.getInputSize();
  const int c = f.getInputSize();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(FunctionTest_347, GetInputSize_ReflectsAssignedPositiveValues_347) {
  TestFunction_347 f;

  f.setInputSizeForTest(1);
  EXPECT_EQ(f.getInputSize(), 1);

  f.setInputSizeForTest(5);
  EXPECT_EQ(f.getInputSize(), 5);

  f.setInputSizeForTest(32);
  EXPECT_EQ(f.getInputSize(), 32);
}

TEST(FunctionTest_347, GetInputSize_AllowsZeroBoundary_347) {
  TestFunction_347 f;

  f.setInputSizeForTest(0);
  EXPECT_EQ(f.getInputSize(), 0);
}

TEST(FunctionTest_347, GetInputSize_HandlesNegativeValuesWithoutThrowing_347) {
  TestFunction_347 f;

  f.setInputSizeForTest(-1);
  EXPECT_EQ(f.getInputSize(), -1);

  f.setInputSizeForTest(-12345);
  EXPECT_EQ(f.getInputSize(), -12345);
}

TEST(FunctionTest_347, GetInputSize_CanChangeMultipleTimes_347) {
  TestFunction_347 f;

  f.setInputSizeForTest(2);
  EXPECT_EQ(f.getInputSize(), 2);

  f.setInputSizeForTest(0);
  EXPECT_EQ(f.getInputSize(), 0);

  f.setInputSizeForTest(16);
  EXPECT_EQ(f.getInputSize(), 16);
}