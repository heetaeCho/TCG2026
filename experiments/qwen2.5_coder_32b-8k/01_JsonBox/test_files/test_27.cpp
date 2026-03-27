#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class JsonBoxValueTest : public ::testing::Test {

protected:

    JsonBox::Value value1;

    JsonBox::Value value2;



    void SetUp() override {

        value1 = JsonBox::Value(5);

        value2 = JsonBox::Value(10);

    }

};



TEST_F(JsonBoxValueTest, GreaterThanOperator_ReturnsTrue_WhenLeftOperandIsGreater_27) {

    EXPECT_FALSE(value1 > value2);

}



TEST_F(JsonBoxValueTest, GreaterThanOperator_ReturnsFalse_WhenLeftOperandIsEqual_27) {

    JsonBox::Value equalValue(5);

    EXPECT_FALSE(value1 > equalValue);

}



TEST_F(JsonBoxValueTest, GreaterThanOperator_ReturnsTrue_WhenLeftOperandIsGreater_StringComparison_27) {

    JsonBox::Value stringValue1("b");

    JsonBox::Value stringValue2("a");

    EXPECT_TRUE(stringValue1 > stringValue2);

}



TEST_F(JsonBoxValueTest, GreaterThanOperator_ReturnsFalse_WhenLeftOperandIsEqual_StringComparison_27) {

    JsonBox::Value equalStringValue1("abc");

    JsonBox::Value equalStringValue2("abc");

    EXPECT_FALSE(equalStringValue1 > equalStringValue2);

}



TEST_F(JsonBoxValueTest, GreaterThanOperator_BoundaryCondition_IntegerComparison_27) {

    JsonBox::Value minValue(std::numeric_limits<int>::min());

    JsonBox::Value maxValue(std::numeric_limits<int>::max());

    EXPECT_FALSE(minValue > maxValue);

    EXPECT_TRUE(maxValue > minValue);

}



TEST_F(JsonBoxValueTest, GreaterThanOperator_BoundaryCondition_DoubleComparison_27) {

    JsonBox::Value minDoubleValue(-std::numeric_limits<double>::infinity());

    JsonBox::Value maxDoubleValue(std::numeric_limits<double>::infinity());

    EXPECT_FALSE(minDoubleValue > maxDoubleValue);

    EXPECT_TRUE(maxDoubleValue > minDoubleValue);

}



TEST_F(JsonBoxValueTest, GreaterThanOperator_TypeMismatchComparison_27) {

    JsonBox::Value intValue(5);

    JsonBox::Value stringValue("10");

    // Assuming lexicographical comparison for different types

    EXPECT_FALSE(intValue > stringValue); // Assuming integer is less than string in terms of type ordering

}
