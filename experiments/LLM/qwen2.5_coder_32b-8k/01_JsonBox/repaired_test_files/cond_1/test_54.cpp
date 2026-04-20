#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_54 : public ::testing::Test {

protected:

    void SetUp() override {

        emptyObject = Object();

        nonEmptyObject = {{"key1", Value("value1")}, {"key2", Value(123)}};

    }



    Object emptyObject;

    Object nonEmptyObject;

};



TEST_F(ValueTest_54, GetObject_ReturnsEmptyObjectWhenTypeIsNotObject_54) {

    Value value;

    EXPECT_EQ(value.getObject(), emptyObject);

}



TEST_F(ValueTest_54, GetObject_ReturnsCorrectObjectWhenTypeIsObject_54) {

    Value value(nonEmptyObject);

    EXPECT_EQ(value.getObject(), nonEmptyObject);

}
