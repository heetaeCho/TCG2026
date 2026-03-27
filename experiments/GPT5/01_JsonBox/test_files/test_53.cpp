// File: Value_setDouble_test_53.cpp
#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include "JsonBox/Value.h"

using JsonBox::Value;

class ValueSetDoubleTest_53 : public ::testing::Test {};

// Normal operation: setting on a null value initializes as double with the given value.
TEST_F(ValueSetDoubleTest_53, SetOnNull_MakesDoubleAndStoresValue_53) {
    Value v; // starts as NULL_VALUE per interface
    const double expected = 123.456;
    v.setDouble(expected);

    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), expected);
    // tryGetDouble should return the stored value, not the default
    EXPECT_DOUBLE_EQ(v.tryGetDouble(-1.0), expected);
}

// Normal operation: setting on an existing double updates the stored value.
TEST_F(ValueSetDoubleTest_53, OverwriteExistingDouble_UpdatesValue_53) {
    Value v(1.0);
    const double expected = -9876.5;
    v.setDouble(expected);

    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), expected);
}

// Type replacement: from STRING to DOUBLE; observable via type predicates and getters.
TEST_F(ValueSetDoubleTest_53, ReplaceStringWithDouble_ChangesTypeAndValue_53) {
    Value v(std::string("hello"));
    ASSERT_TRUE(v.isString()); // precondition check based on interface

    const double expected = 3.14159;
    v.setDouble(expected);

    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_DOUBLE_EQ(v.getDouble(), expected);
}

// Type replacement: from INTEGER to DOUBLE.
TEST_F(ValueSetDoubleTest_53, ReplaceIntegerWithDouble_ChangesTypeAndValue_53) {
    Value v(42);
    ASSERT_TRUE(v.isInteger());

    const double expected = 42.75;
    v.setDouble(expected);

    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_DOUBLE_EQ(v.getDouble(), expected);
}

// Boundary case: NaN should be preserved and observable via std::isnan on getDouble().
TEST_F(ValueSetDoubleTest_53, SetDouble_NaN_Preserved_53) {
    Value v;
    const double nanVal = std::numeric_limits<double>::quiet_NaN();
    v.setDouble(nanVal);

    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(std::isnan(v.getDouble()));
    EXPECT_TRUE(std::isnan(v.tryGetDouble(0.0)));
}

// Boundary case: Infinity should be preserved.
TEST_F(ValueSetDoubleTest_53, SetDouble_Infinity_Preserved_53) {
    Value v;
    const double posInf = std::numeric_limits<double>::infinity();
    v.setDouble(posInf);

    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(std::isinf(v.getDouble()));
    EXPECT_GT(v.getDouble(), 0.0);

    const double negInf = -std::numeric_limits<double>::infinity();
    v.setDouble(negInf);

    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(std::isinf(v.getDouble()));
    EXPECT_LT(v.getDouble(), 0.0);
}

// Robustness: multiple sequential sets — last value wins.
TEST_F(ValueSetDoubleTest_53, MultipleSequentialSetDouble_LastWins_53) {
    Value v;
    v.setDouble(1.0);
    v.setDouble(2.5);
    v.setDouble(-7.75);

    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -7.75);
}

// Compatibility: after setDouble, float accessors should reflect the same numeric value (within float precision).
TEST_F(ValueSetDoubleTest_53, AfterSetDouble_GetFloatMatchesWithinPrecision_53) {
    Value v;
    const double setVal = 12345.6789;
    v.setDouble(setVal);

    EXPECT_TRUE(v.isDouble());
    // getFloat() returns a float; compare with static_cast<float>(setVal)
    EXPECT_FLOAT_EQ(v.getFloat(), static_cast<float>(setVal));
}
