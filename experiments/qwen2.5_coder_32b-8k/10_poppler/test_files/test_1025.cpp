#include <gtest/gtest.h>

#include "UTF.h"



class UTFTest_1025 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(UTFTest_1025, EmptyString_ReturnsFalse_1025) {

    EXPECT_FALSE(isUtf8WithBom(""));

}



TEST_F(UTFTest_1025, ShortString_LessThanThreeChars_ReturnsFalse_1025) {

    EXPECT_FALSE(isUtf8WithBom("ab"));

}



TEST_F(UTFTest_1025, ThreeCharString_NotBOM_ReturnsFalse_1025) {

    EXPECT_FALSE(isUtf8WithBom("\xef\xbb"));

}



TEST_F(UTFTest_1025, FourCharString_NotBOM_ReturnsFalse_1025) {

    EXPECT_FALSE(isUtf8WithBom("\xef\xbb\xbf\x00"));

}



TEST_F(UTFTest_1025, ValidBOM_ReturnsTrue_1025) {

    EXPECT_TRUE(isUtf8WithBom("\xef\xbb\xbfHelloWorld"));

}



TEST_F(UTFTest_1025, BOMAtStartOfLongString_ReturnsTrue_1025) {

    std::string longStr = "\xef\xbb\xbfaVeryLongStringThatDefinitelyExceedsFourCharacters";

    EXPECT_TRUE(isUtf8WithBom(longStr));

}



TEST_F(UTFTest_1025, BOMInMiddleOfLongString_ReturnsFalse_1025) {

    std::string longStr = "ThisIsAString\xef\xbb\xbfaVeryLongStringThatDefinitelyExceedsFourCharacters";

    EXPECT_FALSE(isUtf8WithBom(longStr));

}



TEST_F(UTFTest_1025, InvalidBOM_ReturnsFalse_1025) {

    EXPECT_FALSE(isUtf8WithBom("\xef\xbb\xbe"));

}
