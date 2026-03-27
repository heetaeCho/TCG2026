#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



// Test Fixture for StringMaker<float> tests

class StringMakerFloatTest_278 : public ::testing::Test {

protected:

    float testValue = 123.456f;

};



TEST_F(StringMakerFloatTest_278, ConvertNormalValue_278) {

    std::string result = Catch::StringMaker<float>::convert(testValue);

    EXPECT_EQ(result, "123.456f");

}



TEST_F(StringMakerFloatTest_278, ConvertZero_278) {

    float zeroValue = 0.0f;

    std::string result = Catch::StringMaker<float>::convert(zeroValue);

    EXPECT_EQ(result, "0.0f");

}



TEST_F(StringMakerFloatTest_278, ConvertNegativeValue_278) {

    float negativeValue = -123.456f;

    std::string result = Catch::StringMaker<float>::convert(negativeValue);

    EXPECT_EQ(result, "-123.456f");

}



TEST_F(StringMakerFloatTest_278, ConvertLargePositiveValue_278) {

    float largeValue = 1e38f;

    std::string result = Catch::StringMaker<float>::convert(largeValue);

    EXPECT_EQ(result, "1e+38f");

}



TEST_F(StringMakerFloatTest_278, ConvertSmallPositiveValue_278) {

    float smallValue = 1e-38f;

    std::string result = Catch::StringMaker<float>::convert(smallValue);

    EXPECT_EQ(result, "1e-38f");

}



TEST_F(StringMakerFloatTest_278, ConvertLargeNegativeValue_278) {

    float largeNegativeValue = -1e38f;

    std::string result = Catch::StringMaker<float>::convert(largeNegativeValue);

    EXPECT_EQ(result, "-1e+38f");

}



TEST_F(StringMakerFloatTest_278, ConvertSmallNegativeValue_278) {

    float smallNegativeValue = -1e-38f;

    std::string result = Catch::StringMaker<float>::convert(smallNegativeValue);

    EXPECT_EQ(result, "-1e-38f");

}
