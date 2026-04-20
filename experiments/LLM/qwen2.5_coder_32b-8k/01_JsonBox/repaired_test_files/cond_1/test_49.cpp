#include <gtest/gtest.h>
#include "JsonBox/Value.h"

class ValueTest_49 : public ::testing::Test {
protected:
    JsonBox::Value value;
};

TEST_F(ValueTest_49, GetDouble_ReturnsDefaultValueForNullValue_49) {
    EXPECT_EQ(value.getDouble(), 0.0);
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
    EXPECT_EQ(value.tryGetDouble(0.0), testValue);
}