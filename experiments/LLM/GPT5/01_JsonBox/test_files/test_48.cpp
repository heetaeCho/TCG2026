// File: Value_setInteger_tests_48.cpp
#include <gtest/gtest.h>
#include <climits>
#include "JsonBox/Value.h"

using JsonBox::Value;

class ValueSetIntegerTest_48 : public ::testing::Test {};

// Normal operation: from null -> integer
TEST_F(ValueSetIntegerTest_48, SetInteger_OnNull_SetsTypeAndValue_48) {
    Value v;                    // starts as NULL_VALUE per interface
    v.setInteger(42);

    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_EQ(Value::getType() /* compile-time hint: method is const */, v.getType()); // type query available
    EXPECT_EQ(42, v.getInteger());
    EXPECT_EQ(42, v.tryGetInteger(-1));  // should ignore default when integer is set
}

// Normal operation: updating an existing integer
TEST_F(ValueSetIntegerTest_48, SetInteger_OnExistingInteger_UpdatesValue_48) {
    Value v(1);
    v.setInteger(99);

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(99, v.getInteger());
}

// Type replacement: from string -> integer
TEST_F(ValueSetIntegerTest_48, SetInteger_ReplacesStringTypeWithInteger_48) {
    Value v(std::string("abc"));
    v.setInteger(-7);

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-7, v.getInteger());
}

// Type replacement: from double -> integer
TEST_F(ValueSetIntegerTest_48, SetInteger_ReplacesDoubleTypeWithInteger_48) {
    Value v(3.14);
    v.setInteger(10);

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(10, v.getInteger());
}

// Boundary: INT_MAX
TEST_F(ValueSetIntegerTest_48, SetInteger_SetsIntMaxBoundary_48) {
    Value v;
    v.setInteger(INT_MAX);

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(INT_MAX, v.getInteger());
}

// Boundary: INT_MIN
TEST_F(ValueSetIntegerTest_48, SetInteger_SetsIntMinBoundary_48) {
    Value v;
    v.setInteger(INT_MIN);

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(INT_MIN, v.getInteger());
}

// Multiple calls: last value wins
TEST_F(ValueSetIntegerTest_48, SetInteger_MultipleCalls_LastValueWins_48) {
    Value v;
    v.setInteger(1);
    v.setInteger(2);
    v.setInteger(-3);

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-3, v.getInteger());
}

// Postcondition with tryGetInteger: default ignored when integer present
TEST_F(ValueSetIntegerTest_48, SetInteger_AfterSet_TryGetIntegerIgnoresDefault_48) {
    Value v;
    v.setInteger(123);

    EXPECT_EQ(123, v.tryGetInteger(9999));
}
