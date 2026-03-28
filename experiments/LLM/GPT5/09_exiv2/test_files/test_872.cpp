// =================================================================================================
// TEST_ID: 872
// File: test_datevalue_tofloat_872.cpp
//
// Unit tests for Exiv2::DateValue::toFloat(size_t)
// Constraints respected:
//  - Treat implementation as a black box (no internal logic inference beyond observable interface).
//  - Use only public interface.
//  - Include normal/boundary/error-ish cases (as observable).
// =================================================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>

#include "value.hpp"  // Exiv2::DateValue

namespace {

class DateValueToFloatTest_872 : public ::testing::Test {};

}  // namespace

TEST_F(DateValueToFloatTest_872, ConvertsReturnedInt64ToFloat_872) {
  // Observable behavior from partial code: toFloat(n) == static_cast<float>(toInt64(n))
  Exiv2::DateValue dv;

  const float f0 = dv.toFloat(0);
  const float f1 = dv.toFloat(1);

  // We can't assume anything about the value itself, but we can check internal consistency:
  // toFloat(n) should be exactly the float cast of toInt64(n).
  EXPECT_EQ(f0, static_cast<float>(dv.toInt64(0)));
  EXPECT_EQ(f1, static_cast<float>(dv.toInt64(1)));
}

TEST_F(DateValueToFloatTest_872, HandlesLargeIndexAsBoundaryWithoutCrashAndIsConsistent_872) {
  Exiv2::DateValue dv;

  const size_t n = (std::numeric_limits<size_t>::max)();

  // Boundary input: very large index. Behavior is implementation-defined, but must remain
  // consistent with the public contract implied by the provided implementation.
  const float f = dv.toFloat(n);
  const int64_t i = dv.toInt64(n);

  EXPECT_EQ(f, static_cast<float>(i));
}

TEST_F(DateValueToFloatTest_872, NegativeToInt64CastsToFloatConsistently_872) {
  // We don't know if toInt64 can be negative for a DateValue instance, but we can still
  // assert the conversion relationship for any returned value.
  Exiv2::DateValue dv;

  const int64_t i = dv.toInt64(0);
  const float f = dv.toFloat(0);

  // If i is negative, this still must hold; if it's not negative, it also holds.
  EXPECT_EQ(f, static_cast<float>(i));
}

TEST_F(DateValueToFloatTest_872, FloatResultIsFiniteForTypicalIndicesIfInt64IsFinite_872) {
  Exiv2::DateValue dv;

  // "Error-ish" / exceptional observability: float could become inf if int64 is huge.
  // We can't force huge values, but we can at least assert that if the cast yieldsRecall it's finite.
  for (size_t n : {size_t{0}, size_t{1}, size_t{2}}) {
    const float f = dv.toFloat(n);
    const float casted = static_cast<float>(dv.toInt64(n));
    EXPECT_EQ(f, casted);

    // If the casted value is finite, then f must be finite too (since they must be equal).
    if (std::isfinite(casted)) {
      EXPECT_TRUE(std::isfinite(f));
    }
  }
}

TEST_F(DateValueToFloatTest_872, MultipleCallsAreStableForSameIndex_872) {
  Exiv2::DateValue dv;

  const float a = dv.toFloat(0);
  const float b = dv.toFloat(0);

  // We do NOT assume the value, only that repeated calls on the same object/index
  // produce the same observable result (a reasonable black-box stability check).
  EXPECT_EQ(a, b);

  // And still consistent with toInt64.
  EXPECT_EQ(a, static_cast<float>(dv.toInt64(0)));
  EXPECT_EQ(b, static_cast<float>(dv.toInt64(0)));
}