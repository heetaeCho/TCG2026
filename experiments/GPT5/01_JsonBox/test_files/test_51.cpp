// File: Value_getFloat_tests_51.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueGetFloatTest_51 : public ::testing::Test {};

// Normal operation: when the value holds a double, return it as float.
TEST_F(ValueGetFloatTest_51, GetFloat_ReturnsDoubleValue_51) {
    Value v(3.141592653589793);
    EXPECT_FLOAT_EQ(3.1415927f, v.getFloat()); // EXPECT_FLOAT_EQ handles float precision
}

// Normal operation: when the value holds an integer, return it as float.
TEST_F(ValueGetFloatTest_51, GetFloat_ReturnsIntegerAsFloat_51) {
    Value v(42);
    EXPECT_FLOAT_EQ(42.0f, v.getFloat());
}

// Normal operation / typical numeric: negative and fractional value.
TEST_F(ValueGetFloatTest_51, GetFloat_ReturnsNegativeFractional_51) {
    Value v(-123.5);
    EXPECT_FLOAT_EQ(-123.5f, v.getFloat());
}

// Boundary-ish (within float range): large finite value should round to float.
TEST_F(ValueGetFloatTest_51, GetFloat_LargeFiniteWithinFloatRange_51) {
    const float f = 3.4028232e38f; // near FLT_MAX
    Value v(static_cast<double>(f));
    EXPECT_FLOAT_EQ(f, v.getFloat());
}

// Error/Type-mismatch cases should fall back to default used by getFloat()
// (which passes a default of 0 to tryGetFloat). We only assert the observable result.

TEST_F(ValueGetFloatTest_51, GetFloat_OnStringReturnsZero_51) {
    Value v(std::string("hello"));
    EXPECT_FLOAT_EQ(0.0f, v.getFloat());
}

TEST_F(ValueGetFloatTest_51, GetFloat_OnBooleanReturnsZero_51) {
    Value v(true);
    EXPECT_FLOAT_EQ(0.0f, v.getFloat());
}

TEST_F(ValueGetFloatTest_51, GetFloat_OnNullReturnsZero_51) {
    Value v; // default-constructed null
    EXPECT_FLOAT_EQ(0.0f, v.getFloat());
}

TEST_F(ValueGetFloatTest_51, GetFloat_OnArrayReturnsZero_51) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2.5));
    Value v(arr);
    EXPECT_FLOAT_EQ(0.0f, v.getFloat());
}

TEST_F(ValueGetFloatTest_51, GetFloat_OnObjectReturnsZero_51) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value("text");
    Value v(obj);
    EXPECT_FLOAT_EQ(0.0f, v.getFloat());
}
