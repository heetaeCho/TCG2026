#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JsonBox/Value.h"

#include "JsonBox/Grammar.h"



using namespace JsonBox;



class ValueTest_69 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(ValueTest_69, EmptyObjectSerialization_69) {

    Object emptyObject;

    std::ostringstream output;

    output << emptyObject;



    EXPECT_EQ(output.str(), "{}");

}



TEST_F(ValueTest_69, SingleKeyObjectSerialization_69) {

    Object obj = {{"key", Value("value")}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"key": "value"})");

}



TEST_F(ValueTest_69, MultipleKeysObjectSerialization_69) {

    Object obj = {{"key1", Value("value1")}, {"key2", Value(42)}, {"key3", Value(true)}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"key1": "value1", "key2": 42, "key3": true})");

}



TEST_F(ValueTest_69, NestedObjectSerialization_69) {

    Object innerObj = {{"innerKey", Value("innerValue")}};

    Object obj = {{"outerKey", Value(innerObj)}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"outerKey": {"innerKey": "innerValue"}})");

}



TEST_F(ValueTest_69, StringWithSpecialCharactersSerialization_69) {

    Object obj = {{"key", Value("\"special\": \"value\"")}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"key": "\"special\": \"value\""})");

}



TEST_F(ValueTest_69, EmptyStringSerialization_69) {

    Object obj = {{"key", Value("")}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"key": ""})");

}



TEST_F(ValueTest_69, BooleanValuesSerialization_69) {

    Object obj = {{"trueKey", Value(true)}, {"falseKey", Value(false)}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"trueKey": true, "falseKey": false})");

}



TEST_F(ValueTest_69, IntegerValuesSerialization_69) {

    Object obj = {{"intKey", Value(123)}, {"negativeIntKey", Value(-456)}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"intKey": 123, "negativeIntKey": -456})");

}



TEST_F(ValueTest_69, DoubleValuesSerialization_69) {

    Object obj = {{"doubleKey", Value(123.45)}, {"negativeDoubleKey", Value(-678.90)}};

    std::ostringstream output;

    output << obj;



    EXPECT_EQ(output.str(), R"({"doubleKey": 123.45, "negativeDoubleKey": -678.9})");

}
