#include <gtest/gtest.h>

// We need to access the static function. Since it's in an anonymous-like static context,
// we'll include the source or declare it. Since it's a static function in a .cpp file,
// we need to either include the .cpp or recreate the declaration for testing purposes.
// However, per constraints, we must not re-implement. We'll include the cpp file directly
// to access the static function.

// Include the necessary headers from exiv2
#include "minoltamn_int.hpp"

// Since inRange is a static function defined in the .cpp file, we need to include
// the .cpp to access it in our test translation unit.
// This is a common technique for testing static (file-scope) functions.
namespace Exiv2 {
namespace Internal {
// Forward declare to access the static function - we include the cpp
static bool inRange(long value, long min, long max);
}  // namespace Internal
}  // namespace Exiv2

// Include the implementation file to get access to the static function
#include "minoltamn_int.cpp"

namespace {

using Exiv2::Internal::inRange;

// Test normal cases where value is within range
TEST(InRangeTest_1017, ValueWithinRange_1017) {
  EXPECT_TRUE(inRange(5, 1, 10));
}

TEST(InRangeTest_1017, ValueInMiddleOfRange_1017) {
  EXPECT_TRUE(inRange(50, 0, 100));
}

// Test boundary conditions - value equals min
TEST(InRangeTest_1017, ValueEqualsMin_1017) {
  EXPECT_TRUE(inRange(1, 1, 10));
}

// Test boundary conditions - value equals max
TEST(InRangeTest_1017, ValueEqualsMax_1017) {
  EXPECT_TRUE(inRange(10, 1, 10));
}

// Test boundary conditions - value equals both min and max
TEST(InRangeTest_1017, ValueEqualsMinAndMax_1017) {
  EXPECT_TRUE(inRange(5, 5, 5));
}

// Test value below range
TEST(InRangeTest_1017, ValueBelowRange_1017) {
  EXPECT_FALSE(inRange(0, 1, 10));
}

// Test value above range
TEST(InRangeTest_1017, ValueAboveRange_1017) {
  EXPECT_FALSE(inRange(11, 1, 10));
}

// Test value just below min
TEST(InRangeTest_1017, ValueJustBelowMin_1017) {
  EXPECT_FALSE(inRange(0, 1, 10));
}

// Test value just above max
TEST(InRangeTest_1017, ValueJustAboveMax_1017) {
  EXPECT_FALSE(inRange(11, 1, 10));
}

// Test with negative values - value in range
TEST(InRangeTest_1017, NegativeValuesInRange_1017) {
  EXPECT_TRUE(inRange(-5, -10, -1));
}

// Test with negative values - value equals min
TEST(InRangeTest_1017, NegativeValueEqualsMin_1017) {
  EXPECT_TRUE(inRange(-10, -10, -1));
}

// Test with negative values - value equals max
TEST(InRangeTest_1017, NegativeValueEqualsMax_1017) {
  EXPECT_TRUE(inRange(-1, -10, -1));
}

// Test with negative values - value below range
TEST(InRangeTest_1017, NegativeValueBelowRange_1017) {
  EXPECT_FALSE(inRange(-11, -10, -1));
}

// Test with negative values - value above range
TEST(InRangeTest_1017, NegativeValueAboveRange_1017) {
  EXPECT_FALSE(inRange(0, -10, -1));
}

// Test with range spanning negative to positive
TEST(InRangeTest_1017, RangeSpansNegativeToPositive_1017) {
  EXPECT_TRUE(inRange(0, -5, 5));
}

// Test with zero as value, min, and max
TEST(InRangeTest_1017, AllZeros_1017) {
  EXPECT_TRUE(inRange(0, 0, 0));
}

// Test with zero value below range
TEST(InRangeTest_1017, ZeroBelowRange_1017) {
  EXPECT_FALSE(inRange(0, 1, 10));
}

// Test with zero value above range
TEST(InRangeTest_1017, ZeroAboveRange_1017) {
  EXPECT_FALSE(inRange(0, -10, -1));
}

// Test with large positive values
TEST(InRangeTest_1017, LargePositiveValues_1017) {
  EXPECT_TRUE(inRange(1000000, 0, 2000000));
}

// Test with large negative values
TEST(InRangeTest_1017, LargeNegativeValues_1017) {
  EXPECT_TRUE(inRange(-1000000, -2000000, 0));
}

// Test with LONG_MIN and LONG_MAX boundaries
TEST(InRangeTest_1017, LongMinMax_1017) {
  long lmin = std::numeric_limits<long>::min();
  long lmax = std::numeric_limits<long>::max();
  EXPECT_TRUE(inRange(0, lmin, lmax));
  EXPECT_TRUE(inRange(lmin, lmin, lmax));
  EXPECT_TRUE(inRange(lmax, lmin, lmax));
}

// Test value far below the range
TEST(InRangeTest_1017, ValueFarBelowRange_1017) {
  EXPECT_FALSE(inRange(-1000, 0, 100));
}

// Test value far above the range
TEST(InRangeTest_1017, ValueFarAboveRange_1017) {
  EXPECT_FALSE(inRange(1000, 0, 100));
}

// Test single element range with value not matching
TEST(InRangeTest_1017, SingleElementRangeNotMatching_1017) {
  EXPECT_FALSE(inRange(6, 5, 5));
  EXPECT_FALSE(inRange(4, 5, 5));
}

}  // namespace
