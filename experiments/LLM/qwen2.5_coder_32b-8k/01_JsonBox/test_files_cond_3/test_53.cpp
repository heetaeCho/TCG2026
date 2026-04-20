#include <gtest/gtest.h>
#include "JsonBox/Value.h"

class ValueTest_53 : public ::testing::Test {
protected:
    JsonBox::Value value;
};

TEST_F(ValueTest_53, SetDouble_ChangesTypeToDouble_53) {
    value.setDouble(42.0);
    EXPECT_EQ(value.getType(), JsonBox::Value::DOUBLE);
}

TEST_F(ValueTest_53, SetDouble_UpdatesValue_53) {
    value.setDouble(42.0);
    EXPECT_DOUBLE_EQ(value.getDouble(), 42.0);
}

TEST_F(ValueTest_53, SetDouble_ReplacesExistingDouble_53) {
    value.setDouble(1.0);
    value.setDouble(42.0);
    EXPECT_DOUBLE_EQ(value.getDouble(), 42.0);
}

TEST_F(ValueTest_53, SetDouble_ClearsPreviousData_53) {
    value.setString("Hello");
    value.setDouble(42.0);
    EXPECT_EQ(value.getType(), JsonBox::Value::DOUBLE);
    EXPECT_FALSE(value.isString());
}

TEST_F(ValueTest_53, GetDouble_ReturnsDefaultValueIfNotDouble_53) {
    value.setString("Hello");
    EXPECT_DOUBLE_EQ(value.getDouble(), 0.0);
}

TEST_F(ValueTest_53, TryGetDouble_ReturnsCorrectValueIfDouble_53) {
    value.setDouble(42.0);
    EXPECT_DOUBLE_EQ(value.tryGetDouble(-1.0), 42.0);
}

TEST_F(ValueTest_53, TryGetDouble_ReturnsDefaultValueIfNotDouble_53) {
    value.setString("Hello");
    EXPECT_DOUBLE_EQ(value.tryGetDouble(-1.0), -1.0);
}