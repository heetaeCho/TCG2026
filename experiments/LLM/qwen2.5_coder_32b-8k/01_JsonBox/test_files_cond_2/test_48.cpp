#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_48 : public ::testing::Test {
protected:
    Value value;
};

TEST_F(ValueTest_48, SetInteger_ChangesTypeToInteger_48) {
    value.setInteger(10);
    EXPECT_EQ(value.getType(), JsonBox::Value::INTEGER);
}

TEST_F(ValueTest_48, SetInteger_UpdatesValueCorrectly_48) {
    value.setInteger(20);
    EXPECT_EQ(value.getInteger(), 20);
}

TEST_F(ValueTest_48, SetInteger_OverwritesPreviousValue_48) {
    value.setInteger(15);
    value.setInteger(30);
    EXPECT_EQ(value.getInteger(), 30);
}

TEST_F(ValueTest_48, SetInteger_FromOtherType_ChangesTypeAndValue_48) {
    value.setString("Hello");
    value.setInteger(25);
    EXPECT_EQ(value.getType(), JsonBox::Value::INTEGER);
    EXPECT_EQ(value.getInteger(), 25);
}

TEST_F(ValueTest_48, GetInteger_ReturnsDefaultValueWhenNotSet_48) {
    EXPECT_EQ(value.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_48, IsInteger_ReturnsTrueAfterSettingInteger_48) {
    value.setInteger(10);
    EXPECT_TRUE(value.isInteger());
}

TEST_F(ValueTest_48, IsInteger_ReturnsFalseForOtherTypes_48) {
    value.setString("Hello");
    EXPECT_FALSE(value.isInteger());
    value.setDouble(3.14);
    EXPECT_FALSE(value.isInteger());
    value.setBoolean(true);
    EXPECT_FALSE(value.isInteger());
    value.setNull();
    EXPECT_FALSE(value.isInteger());
}

TEST_F(ValueTest_48, SetInteger_DoesNotAffectOtherTypeMethods_48) {
    value.setString("Hello");
    value.setInteger(10);
    EXPECT_EQ(value.getString(), "Hello");
    EXPECT_NE(value.getDouble(), 10.0);
}