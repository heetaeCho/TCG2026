#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest_46 : public ::testing::Test {

protected:

    JsonBox::Value value;

};



TEST_F(ValueTest_46, GetInteger_DefaultConstructor_ReturnsDefault_46) {

    EXPECT_EQ(value.getInteger(), 0);

}



TEST_F(ValueTest_46, GetInteger_IntegerConstructor_ReturnsCorrectValue_46) {

    JsonBox::Value intValue(42);

    EXPECT_EQ(intValue.getInteger(), 42);

}



TEST_F(ValueTest_46, TryGetInteger_DefaultConstructor_ReturnsDefaultValue_46) {

    EXPECT_EQ(value.tryGetInteger(99), 99);

}



TEST_F(ValueTest_46, TryGetInteger_IntegerConstructor_ReturnsCorrectValue_46) {

    JsonBox::Value intValue(42);

    EXPECT_EQ(intValue.tryGetInteger(99), 42);

}



TEST_F(ValueTest_46, IsInteger_DefaultConstructor_ReturnsFalse_46) {

    EXPECT_FALSE(value.isInteger());

}



TEST_F(ValueTest_46, IsInteger_IntegerConstructor_ReturnsTrue_46) {

    JsonBox::Value intValue(42);

    EXPECT_TRUE(intValue.isInteger());

}



TEST_F(ValueTest_46, SetInteger_ChangesTypeAndValue_46) {

    value.setInteger(100);

    EXPECT_EQ(value.getInteger(), 100);

    EXPECT_TRUE(value.isInteger());

}
