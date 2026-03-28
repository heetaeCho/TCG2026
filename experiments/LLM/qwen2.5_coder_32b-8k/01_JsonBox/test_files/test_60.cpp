#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_60 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_60, SetBoolean_Initial_60) {

    value.setBoolean(true);

    EXPECT_TRUE(value.getBoolean());

}



TEST_F(ValueTest_60, SetBoolean_ChangeToFalse_60) {

    value.setBoolean(true);

    value.setBoolean(false);

    EXPECT_FALSE(value.getBoolean());

}



TEST_F(ValueTest_60, SetBoolean_TypeChangeFromNull_60) {

    EXPECT_EQ(value.getType(), Value::NULL_VALUE);

    value.setBoolean(true);

    EXPECT_EQ(value.getType(), Value::BOOLEAN);

}



TEST_F(ValueTest_60, SetBoolean_TypeChangeFromOtherType_60) {

    value.setString("test");

    EXPECT_EQ(value.getType(), Value::STRING);

    value.setBoolean(true);

    EXPECT_EQ(value.getType(), Value::BOOLEAN);

}



TEST_F(ValueTest_60, GetBoolean_DefaultValue_60) {

    bool defaultValue = false;

    EXPECT_EQ(value.tryGetBoolean(defaultValue), defaultValue);

}



TEST_F(ValueTest_60, GetBoolean_AfterSetBoolean_60) {

    value.setBoolean(true);

    EXPECT_TRUE(value.getBoolean());

}



TEST_F(ValueTest_60, IsBoolean_AfterSetBoolean_60) {

    value.setBoolean(false);

    EXPECT_TRUE(value.isBoolean());

}



TEST_F(ValueTest_60, IsBoolean_Initially_60) {

    EXPECT_FALSE(value.isBoolean());

}
