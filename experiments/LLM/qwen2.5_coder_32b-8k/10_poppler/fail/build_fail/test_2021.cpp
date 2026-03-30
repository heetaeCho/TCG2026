#include <gtest/gtest.h>



// Mocking dependencies if necessary

// For this specific function, no external dependencies are required



// Test Suite name includes TEST_ID

class DetermineFallbackFontTest_2021 : public ::testing::Test {

protected:

    // Setup code can be added here if needed

};



// Normal operation test cases

TEST_F(DetermineFallbackFontTest_2021, ZaDb_ReturnsZapfDingbats_2021) {

    const char* result = determineFallbackFont("/ZaDb", "DefaultFont");

    EXPECT_STREQ(result, "ZapfDingbats");

}



TEST_F(DetermineFallbackFontTest_2021, Cour_ReturnsCourier_2021) {

    const char* result = determineFallbackFont("/Cour", "DefaultFont");

    EXPECT_STREQ(result, "Courier");

}



TEST_F(DetermineFallbackFontTest_2021, TiRo_ReturnsTimesNewRoman_2021) {

    const char* result = determineFallbackFont("/TiRo", "DefaultFont");

    EXPECT_STREQ(result, "TimesNewRoman");

}



TEST_F(DetermineFallbackFontTest_2021, HelveticaBold_ReturnsHelveticaBold_2021) {

    const char* result = determineFallbackFont("/Helvetica-Bold", "DefaultFont");

    EXPECT_STREQ(result, "Helvetica-Bold");

}



// Boundary conditions test cases

TEST_F(DetermineFallbackFontTest_2021, EmptyString_ReturnsDefault_2021) {

    const char* result = determineFallbackFont("", "DefaultFont");

    EXPECT_STREQ(result, "DefaultFont");

}



// Exceptional or error cases test cases

TEST_F(DetermineFallbackFontTest_2021, UnknownToken_ReturnsDefault_2021) {

    const char* result = determineFallbackFont("/Unknown", "DefaultFont");

    EXPECT_STREQ(result, "DefaultFont");

}
