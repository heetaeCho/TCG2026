#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



namespace Catch {

    std::string StringMaker<long>::convert(long value);

}



class StringMakerLongTest_270 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(StringMakerLongTest_270, ConvertPositiveValue_270) {

    EXPECT_EQ(Catch::StringMaker<long>::convert(12345), "12345");

}



TEST_F(StringMakerLongTest_270, ConvertNegativeValue_270) {

    EXPECT_EQ(Catch::StringMaker<long>::convert(-67890), "-67890");

}



TEST_F(StringMakerLongTest_270, ConvertZero_270) {

    EXPECT_EQ(Catch::StringMaker<long>::convert(0), "0");

}



TEST_F(StringMakerLongTest_270, ConvertMaximumValue_270) {

    EXPECT_EQ(Catch::StringMaker<long>::convert(LONG_MAX), std::to_string(LONG_MAX));

}



TEST_F(StringMakerLongTest_270, ConvertMinimumValue_270) {

    EXPECT_EQ(Catch::StringMaker<long>::convert(LONG_MIN), std::to_string(LONG_MIN));

}
