#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



// Test suite for Value class

class ValueTest_35 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ValueTest_35, IsInteger_ReturnsTrueForIntegerValue_35) {

    Value value(42);

    EXPECT_TRUE(value.isInteger());

}



TEST_F(ValueTest_35, IsInteger_ReturnsFalseForNonIntegerValue_35) {

    Value stringValue("Hello");

    EXPECT_FALSE(stringValue.isInteger());



    Value doubleValue(3.14);

    EXPECT_FALSE(doubleValue.isInteger());



    Value objectValue(Object{{"key", "value"}});

    EXPECT_FALSE(objectValue.isInteger());



    Value arrayValue(Array{1, 2, 3});

    EXPECT_FALSE(arrayValue.isInteger());



    Value booleanValue(true);

    EXPECT_FALSE(booleanValue.isInteger());



    Value nullValue;

    EXPECT_FALSE(nullValue.isInteger());

}



TEST_F(ValueTest_35, IsInteger_ReturnsTrueForAssignedIntegerValue_35) {

    Value value;

    value = 42;

    EXPECT_TRUE(value.isInteger());

}



TEST_F(ValueTest_35, IsInteger_ReturnsFalseForDefaultConstructedValue_35) {

    Value defaultValue;

    EXPECT_FALSE(defaultValue.isInteger());

}
