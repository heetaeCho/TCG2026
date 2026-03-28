#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_62 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_62, LoadValidJsonString_NormalOperation_62) {

    std::string validJson = "{\"key\": \"value\"}";

    value.loadFromString(validJson);

    EXPECT_TRUE(value.isObject());

}



TEST_F(ValueTest_62, LoadEmptyJsonString_BoundaryCondition_62) {

    std::string emptyJson = "{}";

    value.loadFromString(emptyJson);

    EXPECT_TRUE(value.isObject());

}



TEST_F(ValueTest_62, LoadInvalidJsonString_ErrorCase_62) {

    std::string invalidJson = "{invalid}";

    try {

        value.loadFromString(invalidJson);

        FAIL() << "Expected exception not thrown";

    } catch (const std::exception& e) {

        // Expected

    }

}



TEST_F(ValueTest_62, LoadJsonStringWithArray_NormalOperation_62) {

    std::string jsonArray = "[1, 2, 3]";

    value.loadFromString(jsonArray);

    EXPECT_TRUE(value.isArray());

}



TEST_F(ValueTest_62, LoadJsonStringWithBoolean_NormalOperation_62) {

    std::string jsonBool = "true";

    value.loadFromString(jsonBool);

    EXPECT_TRUE(value.isBoolean());

    EXPECT_EQ(true, value.getBoolean());

}



TEST_F(ValueTest_62, LoadJsonStringWithNumber_Integer_NormalOperation_62) {

    std::string jsonInt = "42";

    value.loadFromString(jsonInt);

    EXPECT_TRUE(value.isInteger());

    EXPECT_EQ(42, value.getInteger());

}



TEST_F(ValueTest_62, LoadJsonStringWithNumber_Double_NormalOperation_62) {

    std::string jsonDouble = "3.14";

    value.loadFromString(jsonDouble);

    EXPECT_TRUE(value.isDouble());

    EXPECT_FLOAT_EQ(3.14, value.getDouble());

}



TEST_F(ValueTest_62, LoadJsonStringWithString_NormalOperation_62) {

    std::string jsonString = "\"hello\"";

    value.loadFromString(jsonString);

    EXPECT_TRUE(value.isString());

    EXPECT_EQ("hello", value.getString());

}
