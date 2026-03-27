// File: Value_tryGetFloat_tests_52.cpp
#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTryGetFloatTest_52 : public ::testing::Test {};

// Returns float when stored as double.
TEST_F(ValueTryGetFloatTest_52, ReturnsFloatFromDouble_52) {
    Value v(3.5); // double ctor
    float out = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(out, 3.5f);
}

// Returns float when stored as integer.
TEST_F(ValueTryGetFloatTest_52, ReturnsFloatFromInteger_52) {
    Value v(42); // int ctor
    float out = v.tryGetFloat(-1.0f);
    EXPECT_FLOAT_EQ(out, 42.0f);
}

// Uses default for non-numeric: string.
TEST_F(ValueTryGetFloatTest_52, ReturnsDefaultWhenString_52) {
    Value v(std::string("hello"));
    float def = 7.25f;
    float out = v.tryGetFloat(def);
    EXPECT_FLOAT_EQ(out, def);
}

// Uses default for non-numeric: null.
TEST_F(ValueTryGetFloatTest_52, ReturnsDefaultWhenNull_52) {
    Value v; // default is null
    float def = -99.0f;
    float out = v.tryGetFloat(def);
    EXPECT_FLOAT_EQ(out, def);
}

// Uses default for non-numeric: boolean.
TEST_F(ValueTryGetFloatTest_52, ReturnsDefaultWhenBoolean_52) {
    Value v(true);
    float def = 1.5f;
    float out = v.tryGetFloat(def);
    EXPECT_FLOAT_EQ(out, def);
}

// Preserves sign and fraction when underlying is double.
TEST_F(ValueTryGetFloatTest_52, PreservesSignAndFraction_52) {
    Value v(-123.75); // double ctor
    float out = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(out, -123.75f);
}

// Handles large-but-finite double within float range.
TEST_F(ValueTryGetFloatTest_52, HandlesLargeDoubleWithinFloatRange_52) {
    // 1e38 is within float max (~3.4e38)
    Value v(1e38);
    float out = v.tryGetFloat(0.0f);
    // Use a relative tolerance appropriate for float representation.
    EXPECT_NEAR(out, static_cast<float>(1e38), static_cast<float>(1e38) * 1e-6f);
}

// Returns default NaN unchanged for non-numeric default.
TEST_F(ValueTryGetFloatTest_52, ReturnsDefaultNaNWhenNonNumeric_52) {
    Value v(std::string("not-a-number"));
    float def = std::numeric_limits<float>::quiet_NaN();
    float out = v.tryGetFloat(def);
    EXPECT_TRUE(std::isnan(out));
}
