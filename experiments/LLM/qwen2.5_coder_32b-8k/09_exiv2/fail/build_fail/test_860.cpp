#include <gtest/gtest.h>

#include "value.cpp"



namespace {



class LangAltValueTest_860 : public ::testing::Test {

protected:

    Exiv2::LangAltValue langAltValue;

};



TEST_F(LangAltValueTest_860, ToFloat_ReturnsZero_860) {

    // Arrange

    size_t index = 0; // Using an arbitrary index as it does not affect the return value



    // Act

    float result = langAltValue.toFloat(index);



    // Assert

    EXPECT_FLOAT_EQ(result, 0.0F);

}



TEST_F(LangAltValueTest_860, ToFloat_SetsOkToFalse_860) {

    // Arrange

    size_t index = 0; // Using an arbitrary index as it does not affect the return value



    // Act

    langAltValue.toFloat(index);



    // Assert

    EXPECT_FALSE(langAltValue.ok_);

}



}  // namespace
