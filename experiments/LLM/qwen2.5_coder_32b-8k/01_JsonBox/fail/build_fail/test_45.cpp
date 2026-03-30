#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_45, SetString_ChangesTypeToString_45) {

    value.setString("test");

    EXPECT_EQ(value.getType(), Type::STRING);

}



TEST_F(ValueTest_45, SetString_SetsCorrectStringValue_45) {

    value.setString("test");

    EXPECT_EQ(value.getString(), "test");

}



TEST_F(ValueTest_45, SetString_ReplacesExistingValue_45) {

    value.setInteger(123);

    value.setString("new test");

    EXPECT_EQ(value.getType(), Type::STRING);

    EXPECT_EQ(value.getString(), "new test");

}



TEST_F(ValueTest_45, SetString_EmptyStringSetsCorrectly_45) {

    value.setString("");

    EXPECT_EQ(value.getType(), Type::STRING);

    EXPECT_EQ(value.getString(), "");

}



TEST_F(ValueTest_45, TryGetString_ReturnsDefaultValueWhenNotString_45) {

    value.setInteger(123);

    EXPECT_EQ(value.tryGetString("default"), "default");

}



TEST_F(ValueTest_45, IsString_ReturnsTrueAfterSetString_45) {

    value.setString("test");

    EXPECT_TRUE(value.isString());

}



TEST_F(ValueTest_45, IsString_ReturnsFalseInitially_45) {

    EXPECT_FALSE(value.isString());

}
