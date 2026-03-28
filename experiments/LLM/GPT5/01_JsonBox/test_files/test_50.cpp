// File: Value_tryGetDouble_tests_50.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

#include <limits>
#include <cmath>
#include <string>
#include <vector>
#include <map>

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

class ValueTryGetDoubleTest_50 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ValueTryGetDoubleTest_50, ReturnsStoredDoubleWhenTypeIsDouble_50) {
    Value v(3.141592653589793);
    EXPECT_DOUBLE_EQ(3.141592653589793, v.tryGetDouble(0.0));
}

TEST_F(ValueTryGetDoubleTest_50, ReturnsConvertedDoubleWhenTypeIsInteger_50) {
    Value v(42);
    EXPECT_DOUBLE_EQ(42.0, v.tryGetDouble(-1.0));
}

TEST_F(ValueTryGetDoubleTest_50, IgnoresDefaultWhenTypeIsDouble_50) {
    Value v(1.5);
    EXPECT_DOUBLE_EQ(1.5, v.tryGetDouble(999.0)); // should not use default
}

// --- Boundary conditions ---

TEST_F(ValueTryGetDoubleTest_50, HandlesNaNDouble_50) {
    Value v(std::numeric_limits<double>::quiet_NaN());
    double out = v.tryGetDouble(123.0);
    EXPECT_TRUE(std::isnan(out));
}

TEST_F(ValueTryGetDoubleTest_50, HandlesMaxDouble_50) {
    Value v(std::numeric_limits<double>::max());
    EXPECT_DOUBLE_EQ(std::numeric_limits<double>::max(), v.tryGetDouble(0.0));
}

TEST_F(ValueTryGetDoubleTest_50, ConvertsIntMaxToDouble_50) {
    int imax = std::numeric_limits<int>::max();
    Value v(imax);
    EXPECT_DOUBLE_EQ(static_cast<double>(imax), v.tryGetDouble(0.0));
}

TEST_F(ValueTryGetDoubleTest_50, ConvertsIntMinToDouble_50) {
    int imin = std::numeric_limits<int>::min();
    Value v(imin);
    EXPECT_DOUBLE_EQ(static_cast<double>(imin), v.tryGetDouble(0.0));
}

// --- Non-double/integer types should return the default ---

TEST_F(ValueTryGetDoubleTest_50, ReturnsDefaultWhenTypeIsString_50) {
    Value v(std::string("12.34")); // even if numeric-looking, type is STRING
    EXPECT_DOUBLE_EQ(7.7, v.tryGetDouble(7.7));
}

TEST_F(ValueTryGetDoubleTest_50, ReturnsDefaultWhenTypeIsNull_50) {
    Value v; // default constructs to NULL_VALUE
    EXPECT_DOUBLE_EQ(-123.456, v.tryGetDouble(-123.456));
}

TEST_F(ValueTryGetDoubleTest_50, ReturnsDefaultWhenTypeIsBoolean_50) {
    Value v(true);
    EXPECT_DOUBLE_EQ(0.25, v.tryGetDouble(0.25));
}

TEST_F(ValueTryGetDoubleTest_50, ReturnsDefaultWhenTypeIsArray_50) {
    Array arr; // empty array is fine; type must be ARRAY
    Value v(arr);
    EXPECT_DOUBLE_EQ(42.0, v.tryGetDouble(42.0));
}

TEST_F(ValueTryGetDoubleTest_50, ReturnsDefaultWhenTypeIsObject_50) {
    Object obj; // empty object is fine; type must be OBJECT
    Value v(obj);
    EXPECT_DOUBLE_EQ(-0.0, v.tryGetDouble(-0.0));
}
