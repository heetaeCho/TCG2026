#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest_51 : public ::testing::Test {

protected:

    JsonBox::Value value;

};



TEST_F(ValueTest_51, GetFloat_DefaultValue_51) {

    // Arrange & Act & Assert

    EXPECT_FLOAT_EQ(0.0f, value.getFloat());

}



TEST_F(ValueTest_51, SetAndGetFloat_NormalOperation_51) {

    // Arrange

    float testValue = 3.14f;

    value.setDouble(testValue);



    // Act & Assert

    EXPECT_FLOAT_EQ(testValue, value.getFloat());

}



TEST_F(ValueTest_51, TryGetFloat_DefaultValue_51) {

    // Arrange & Act & Assert

    float defaultValue = 2.71f;

    EXPECT_FLOAT_EQ(defaultValue, value.tryGetFloat(defaultValue));

}



TEST_F(ValueTest_51, TryGetFloat_NormalOperation_51) {

    // Arrange

    float testValue = 3.14f;

    value.setDouble(testValue);

    float defaultValue = 2.71f;



    // Act & Assert

    EXPECT_FLOAT_EQ(testValue, value.tryGetFloat(defaultValue));

}



TEST_F(ValueTest_51, SetAndGetFloat_BoundaryConditions_51) {

    // Arrange

    float testValue = std::numeric_limits<float>::max();

    value.setDouble(testValue);



    // Act & Assert

    EXPECT_FLOAT_EQ(testValue, value.getFloat());



    // Arrange

    testValue = std::numeric_limits<float>::lowest();

    value.setDouble(testValue);



    // Act & Assert

    EXPECT_FLOAT_EQ(testValue, value.getFloat());

}



TEST_F(ValueTest_51, SetAndGetFloat_ExceptionalCases_51) {

    // Arrange

    value.setDouble(std::nanf(""));



    // Act & Assert

    EXPECT_TRUE(std::isnan(value.getFloat()));



    // Arrange

    value.setDouble(std::numeric_limits<float>::infinity());



    // Act & Assert

    EXPECT_TRUE(std::isinf(value.getFloat()));

}
