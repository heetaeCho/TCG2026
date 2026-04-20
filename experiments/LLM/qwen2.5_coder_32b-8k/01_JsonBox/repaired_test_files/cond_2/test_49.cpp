#include <gtest/gtest.h>
#include "JsonBox/Value.h"

class ValueTest_49 : public ::testing::Test {
protected:
    JsonBox::Value value;
};

TEST_F(ValueTest_49, GetDouble_ReturnsDefaultValueForNullValue_49) {
    const double defaultDouble = 0.0; // Using a local constant to mimic EMPTY_DOUBLE
    EXPECT_EQ(value.getDouble(), defaultDouble);
}

TEST_F(ValueTest_49, GetDouble_ReturnsCorrectValueAfterSetDouble_49) {
    double testValue = 3.14;
    value.setDouble(testValue);
    EXPECT_EQ(value.getDouble(), testValue);
}

TEST_F(ValueTest_49, TryGetDouble_ReturnsDefaultValueForNullValue_49) {
    double defaultValue = 2.71;
    EXPECT_EQ(value.tryGetDouble(defaultValue), defaultValue);
}

TEST_F(ValueTest_49, TryGetDouble_ReturnsCorrectValueAfterSetDouble_49) {
    double testValue = 3.14;
    value.setDouble(testValue);
    const double defaultDouble = 0.0; // Using a local constant to mimic EMPTY_DOUBLE
    EXPECT_EQ(value.tryGetDouble(defaultDouble), testValue);
}