// File: Value_tryGetInteger_tests_47.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

//
// Test suite for Value::tryGetInteger
//
TEST(ValueTryGetIntegerTest_47, ReturnsStoredInteger_WhenTypeIsInteger_47) {
    Value v_int(123);
    EXPECT_EQ(123, v_int.tryGetInteger(-1));
}

TEST(ValueTryGetIntegerTest_47, ReturnsZero_WhenStoredIsZeroInteger_47) {
    Value v_int(0);
    EXPECT_EQ(0, v_int.tryGetInteger(999));
}

TEST(ValueTryGetIntegerTest_47, TruncatesTowardZero_ForPositiveFractionalDouble_47) {
    Value v_double(3.9);
    // static_cast<int>(3.9) == 3
    EXPECT_EQ(3, v_double.tryGetInteger(-1));
}

TEST(ValueTryGetIntegerTest_47, TruncatesTowardZero_ForNegativeFractionalDouble_47) {
    Value v_double(-7.8);
    // static_cast<int>(-7.8) == -7 (toward zero)
    EXPECT_EQ(-7, v_double.tryGetInteger(100));
}

TEST(ValueTryGetIntegerTest_47, ReturnsSameValue_ForIntegralDouble_47) {
    Value v_double(42.0);
    EXPECT_EQ(42, v_double.tryGetInteger(-1));
}

TEST(ValueTryGetIntegerTest_47, ReturnsDefault_WhenTypeIsString_47) {
    Value v_str(std::string("123"));
    EXPECT_EQ(77, v_str.tryGetInteger(77));
}

TEST(ValueTryGetIntegerTest_47, ReturnsDefault_WhenTypeIsBooleanTrue_47) {
    Value v_true(true);
    EXPECT_EQ(-5, v_true.tryGetInteger(-5));
}

TEST(ValueTryGetIntegerTest_47, ReturnsDefault_WhenTypeIsBooleanFalse_47) {
    Value v_false(false);
    EXPECT_EQ(8080, v_false.tryGetInteger(8080));
}

TEST(ValueTryGetIntegerTest_47, ReturnsDefault_WhenTypeIsNull_47) {
    Value v_null; // default ctor -> NULL_VALUE
    EXPECT_EQ(31415, v_null.tryGetInteger(31415));
}

TEST(ValueTryGetIntegerTest_47, ReturnsDefault_WhenTypeIsObject_47) {
    Object obj; // empty object is fine
    Value v_obj(obj);
    EXPECT_EQ(1234, v_obj.tryGetInteger(1234));
}

TEST(ValueTryGetIntegerTest_47, ReturnsDefault_WhenTypeIsArray_47) {
    Array arr; // empty array is fine
    Value v_arr(arr);
    EXPECT_EQ(-999, v_arr.tryGetInteger(-999));
}
