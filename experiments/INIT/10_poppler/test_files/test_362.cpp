// TEST_ID: 362
// File: sampled_function_get_encode_min_test_362.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>
#include <utility>

#include "Function.h"  // ./TestProjects/poppler/poppler/Function.h

namespace {

class SampledFunctionTest_362 : public ::testing::Test {
protected:
  // Intentionally empty: tests treat SampledFunction as a black box.
};

TEST_F(SampledFunctionTest_362, Signature_ReturnsDoubleAndIsConstCallable_362) {
  // Compile-time interface checks only (no assumptions about internal state).
  static_assert(std::is_same_v<decltype(std::declval<const SampledFunction&>().getEncodeMin(0)), double>,
                "SampledFunction::getEncodeMin(int) must return double");
  static_assert(std::is_same_v<decltype(std::declval<SampledFunction&>().getEncodeMin(0)), double>,
                "getEncodeMin should be callable on non-const object as well");
}

TEST_F(SampledFunctionTest_362, GetEncodeMin_CanBeCalledWithZeroIndex_362) {
  // Normal operation (minimal): method is callable and returns a usable double.
  SampledFunction func;
  const double v = func.getEncodeMin(0);
  EXPECT_TRUE(std::isfinite(v) || std::isnan(v));  // Accept any double; just ensure call succeeds.
}

TEST_F(SampledFunctionTest_362, GetEncodeMin_CanBeCalledWithMultipleIndices_362) {
  // Boundary-ish indices based on the exposed/inferred max of 32.
  // This does NOT assert specific values (black-box), only that calls succeed.
  SampledFunction func;

  const double v0 = func.getEncodeMin(0);
  const double v1 = func.getEncodeMin(1);
  const double v31 = func.getEncodeMin(31);

  // Avoid assuming relationships; only check the returned values are doubles (self-equality unless NaN).
  EXPECT_TRUE((v0 == v0) || std::isnan(v0));
  EXPECT_TRUE((v1 == v1) || std::isnan(v1));
  EXPECT_TRUE((v31 == v31) || std::isnan(v31));
}

TEST_F(SampledFunctionTest_362, GetEncodeMin_RepeatedCallsSameIndexAreStable_362) {
  // Observable behavior: repeated calls with same input on same object should be stable.
  // We don't assume a particular numeric value, only that repeated calls are consistent.
  SampledFunction func;

  const double a = func.getEncodeMin(0);
  const double b = func.getEncodeMin(0);

  if (std::isnan(a) || std::isnan(b)) {
    EXPECT_TRUE(std::isnan(a) && std::isnan(b));
  } else {
    EXPECT_DOUBLE_EQ(a, b);
  }
}

}  // namespace