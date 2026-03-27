#include <gtest/gtest.h>



extern const int hexCharVals[256];



// Test fixture for parseHex function tests.

class ParseHexTest_1880 : public ::testing::Test {

protected:

    unsigned int result;

};



TEST_F(ParseHexTest_1880, ValidSingleDigitHex_1880) {

    const char* hexString = "A";

    EXPECT_TRUE(parseHex(hexString, 1, &result));

    EXPECT_EQ(result, 10);

}



TEST_F(ParseHexTest_1880, ValidTwoDigitHex_1880) {

    const char* hexString = "1F";

    EXPECT_TRUE(parseHex(hexString, 2, &result));

    EXPECT_EQ(result, 31);

}



TEST_F(ParseHexTest_1880, ValidFourDigitHex_1880) {

    const char* hexString = "1A3F";

    EXPECT_TRUE(parseHex(hexString, 4, &result));

    EXPECT_EQ(result, 6719);

}



TEST_F(ParseHexTest_1880, InvalidCharacterInHex_1880) {

    const char* hexString = "1G3F";

    EXPECT_FALSE(parseHex(hexString, 4, &result));

    EXPECT_EQ(result, 0);

}



TEST_F(ParseHexTest_1880, EmptyHexString_1880) {

    const char* hexString = "";

    EXPECT_FALSE(parseHex(hexString, 0, &result));

    EXPECT_EQ(result, 0);

}



TEST_F(ParseHexTest_1880, NullHexString_1880) {

    const char* hexString = nullptr;

    EXPECT_FALSE(parseHex(hexString, 2, &result));

    // result is not specified in the interface to be a specific value if null is passed

}



TEST_F(ParseHexTest_1880, HexStringWithLeadingZeros_1880) {

    const char* hexString = "001F";

    EXPECT_TRUE(parseHex(hexString, 4, &result));

    EXPECT_EQ(result, 31);

}



TEST_F(ParseHexTest_1880, BoundaryConditionMaxValidLength_1880) {

    const char* hexString = "FFFFFFFF";

    EXPECT_TRUE(parseHex(hexString, 8, &result));

    EXPECT_EQ(result, 0xFFFFFFFF);

}
