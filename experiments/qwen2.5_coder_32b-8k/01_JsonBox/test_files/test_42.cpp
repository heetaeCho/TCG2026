#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest_42 : public ::testing::Test {

protected:

    JsonBox::Value value;

};



TEST_F(ValueTest_42, GetString_DefaultConstructor_ReturnsEmptyString_42) {

    EXPECT_EQ(value.getString(), "");

}



TEST_F(ValueTest_42, GetString_StringConstructor_ReturnsCorrectString_42) {

    JsonBox::Value stringValue("test");

    EXPECT_EQ(stringValue.getString(), "test");

}



TEST_F(ValueTest_42, GetString_CStringConstructor_ReturnsCorrectString_42) {

    JsonBox::Value cStringValue("test_cstring");

    EXPECT_EQ(cStringValue.getString(), "test_cstring");

}



TEST_F(ValueTest_42, GetString_NonStringType_ReturnsEmptyString_42) {

    JsonBox::Value intValue(10);

    EXPECT_EQ(intValue.getString(), "");

}



TEST_F(ValueTest_42, GetString_AfterSetString_ReturnsCorrectString_42) {

    value.setString("set_test");

    EXPECT_EQ(value.getString(), "set_test");

}



TEST_F(ValueTest_42, TryGetString_DefaultConstructor_ReturnsDefaultValue_42) {

    EXPECT_EQ(value.tryGetString("default"), "default");

}



TEST_F(ValueTest_42, TryGetString_StringType_ReturnsCorrectString_42) {

    JsonBox::Value stringValue("test_try");

    EXPECT_EQ(stringValue.tryGetString("default"), "test_try");

}
