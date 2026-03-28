#include <gtest/gtest.h>

#include "UTF.h"



class UnicodeTest_1021 : public ::testing::Test {

protected:

    // You can add any necessary setup or teardown here if needed.

};



TEST_F(UnicodeTest_1021, ValidUnicodeInRange_1021) {

    EXPECT_TRUE(UnicodeIsValid(0x0000));

    EXPECT_TRUE(UnicodeIsValid(0x7FFF));

    EXPECT_TRUE(UnicodeIsValid(0xD800 - 1)); // Before surrogate range

    EXPECT_TRUE(UnicodeIsValid(0xE000));   // After surrogate range

    EXPECT_TRUE(UnicodeIsValid(0xFDD0 - 1)); // Before noncharacter code points

    EXPECT_TRUE(UnicodeIsValid(0xFDEF + 1)); // After noncharacter code points

    EXPECT_TRUE(UnicodeIsValid(0x10FFFF)); // Maximum valid Unicode code point

}



TEST_F(UnicodeTest_1021, InvalidSurrogateCodePoints_1021) {

    EXPECT_FALSE(UnicodeIsValid(0xD800));

    EXPECT_FALSE(UnicodeIsValid(0xDBFF));

    EXPECT_FALSE(UnicodeIsValid(0xDC00));

    EXPECT_FALSE(UnicodeIsValid(0xDFFF));

}



TEST_F(UnicodeTest_1021, InvalidNoncharacterCodePoints_1021) {

    for (Unicode ucs4 = 0xFDD0; ucs4 <= 0xFDEF; ++ucs4) {

        EXPECT_FALSE(UnicodeIsValid(ucs4)) << "Failed at code point: " << std::hex << ucs4;

    }

}



TEST_F(UnicodeTest_1021, InvalidCodePointsAboveMax_1021) {

    EXPECT_FALSE(UnicodeIsValid(0x110000));

    EXPECT_FALSE(UnicodeIsValid(0xFFFFFFFF));

}



TEST_F(UnicodeTest_1021, ValidNonBMPCodePoints_1021) {

    EXPECT_TRUE(UnicodeIsValid(0x10000));

    EXPECT_TRUE(UnicodeIsValid(0x10FFF));

}



TEST_F(UnicodeTest_1021, InvalidCodePointsWithFFFEOrFFFF_1021) {

    for (int i = 0; i < 0x110000; ++i) {

        if ((i & 0xfffe) == 0xfffe || (i & 0xfffe) == 0xffff) {

            EXPECT_FALSE(UnicodeIsValid(i)) << "Failed at code point: " << std::hex << i;

        }

    }

}
