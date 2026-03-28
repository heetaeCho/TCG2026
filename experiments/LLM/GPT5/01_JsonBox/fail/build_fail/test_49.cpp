// File: tests/Value_GetDouble_Test.cpp
#include <gtest/gtest.h>
#include <limits>
#include "JsonBox/Value.h"

using JsonBox::Value;

class ValueGetDoubleTest_49 : public ::testing::Test {};

// Normal: returns the stored double as-is.
TEST_F(ValueGetDoubleTest_49, ReturnsStoredDouble_49) {
    Value v(3.14159265);
    EXPECT_DOUBLE_EQ(3.14159265, v.getDouble());
}

// Normal/boundary: negative and very large finite values are returned as stored.
TEST_F(ValueGetDoubleTest_49, HandlesNegativeAndLarge_49) {
    Value neg(-123.456);
    EXPECT_DOUBLE_EQ(-123.456, neg.getDouble());

    // Very large finite value (well within double range, but large)
    Value large(1.0e308);
    EXPECT_DOUBLE_EQ(1.0e308, large.getDouble());
}

// Boundary: NaN is preserved when the Value actually holds a NaN double.
TEST_F(ValueGetDoubleTest_49, PreservesNaNWhenStored_49) {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    Value v(nan);
    const double got = v.getDouble();
    EXPECT_TRUE(std::isnan(got));
}

// Exceptional/other types: for a non-numeric value, getDouble() must match tryGetDouble(0.0),
// demonstrating delegation to tryGetDouble with the EMPTY_DOUBLE default.
TEST_F(ValueGetDoubleTest_49, NonNumericDelegatesToTryGetWithEmptyDefault_49) {
    Value s("hello");
    // Must match using the empty default (0.0).
    EXPECT_DOUBLE_EQ(s.tryGetDouble(0.0), s.getDouble());
    // If a different default would be returned by tryGetDouble, getDouble() should *not* follow it.
    EXPECT_NE(s.tryGetDouble(42.5), s.getDouble());
}

// Exceptional/null: default-constructed (null) Value should use EMPTY_DOUBLE via tryGetDouble.
TEST_F(ValueGetDoubleTest_49, NullUsesEmptyDefault_49) {
    Value n; // null
    EXPECT_DOUBLE_EQ(0.0, n.getDouble());
    EXPECT_DOUBLE_EQ(n.tryGetDouble(0.0), n.getDouble());
}

// Cross-type (integer): do not assume conversion, just require consistency with tryGetDouble(0.0).
TEST_F(ValueGetDoubleTest_49, IntegerConsistencyWithTryGet_49) {
    Value vi(7);
    EXPECT_DOUBLE_EQ(vi.tryGetDouble(0.0), vi.getDouble());
}
