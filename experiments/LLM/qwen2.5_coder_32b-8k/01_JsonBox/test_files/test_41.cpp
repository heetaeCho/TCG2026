#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ValueTest_41, IsNull_ReturnsTrueForDefaultConstructedValue_41) {

    Value value;

    EXPECT_TRUE(value.isNull());

}



TEST_F(ValueTest_41, IsNull_ReturnsFalseForStringConstructedValue_41) {

    Value value("test");

    EXPECT_FALSE(value.isNull());

}



TEST_F(ValueTest_41, IsNull_ReturnsFalseForIntConstructedValue_41) {

    Value value(123);

    EXPECT_FALSE(value.isNull());

}



TEST_F(ValueTest_41, IsNull_ReturnsFalseForDoubleConstructedValue_41) {

    Value value(123.456);

    EXPECT_FALSE(value.isNull());

}



TEST_F(ValueTest_41, IsNull_ReturnsFalseForObjectConstructedValue_41) {

    Object obj;

    obj["key"] = "value";

    Value value(obj);

    EXPECT_FALSE(value.isNull());

}



TEST_F(ValueTest_41, IsNull_ReturnsFalseForArrayConstructedValue_41) {

    Array arr = {1, 2, 3};

    Value value(arr);

    EXPECT_FALSE(value.isNull());

}



TEST_F(ValueTest_41, IsNull_ReturnsFalseForBoolConstructedValue_41) {

    Value value(true);

    EXPECT_FALSE(value.isNull());

}



TEST_F(ValueTest_41, SetNull_MakesValueNull_41) {

    Value value("test");

    value.setNull();

    EXPECT_TRUE(value.isNull());

}
