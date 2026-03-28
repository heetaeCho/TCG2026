#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest : public ::testing::Test {

protected:

    JsonBox::Value value;

};



TEST_F(ValueTest_17, AssignCString_NormalOperation_17) {

    const char* testString = "Hello, World!";

    value = testString;

    EXPECT_EQ(value.getString(), testString);

}



TEST_F(ValueTest_17, AssignEmptyCString_NormalOperation_17) {

    const char* testString = "";

    value = testString;

    EXPECT_EQ(value.getString(), "");

}



TEST_F(ValueTest_17, CheckTypeAfterAssignCString_NormalOperation_17) {

    value = "Sample";

    EXPECT_TRUE(value.isString());

}



TEST_F(ValueTest_17, AssignNullPointer_ExceptionalCase_17) {

    const char* testString = nullptr;

    EXPECT_THROW(value = testString, std::invalid_argument);

}



TEST_F(ValueTest_17, ReassignCString_NormalOperation_17) {

    value = "First";

    value = "Second";

    EXPECT_EQ(value.getString(), "Second");

}
