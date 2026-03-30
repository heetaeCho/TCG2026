#include <gtest/gtest.h>



// Assuming UCP is a macro that defines Unicode points.

#define UCP(x) x



typedef unsigned long UniCodePoint;



extern UniCodePoint GetClosingQuote(UniCodePoint openQuote);



TEST(GetClosingQuoteTest_1918, DoubleQuote_ReturnsDoubleQuote_1918) {

    EXPECT_EQ(UCP(0x0022), GetClosingQuote(UCP(0x0022)));

}



TEST(GetClosingQuoteTest_1918, OpeningBracket_ReturnsClosingBracket_1918) {

    EXPECT_EQ(UCP(0x005D), GetClosingQuote(UCP(0x005B)));

}



TEST(GetClosingQuoteTest_1918, LeftPointingDoubleAngleQuotationMark_ReturnsRightPointingDoubleAngleQuotationMark_1918) {

    EXPECT_EQ(UCP(0x00BB), GetClosingQuote(UCP(0x00AB)));

}



TEST(GetClosingQuoteTest_1918, RightPointingDoubleAngleQuotationMark_ReturnsLeftPointingDoubleAngleQuotationMark_1918) {

    EXPECT_EQ(UCP(0x00AB), GetClosingQuote(UCP(0x00BB)));

}



TEST(GetClosingQuoteTest_1918, FigureDash_ReturnsFigureDash_1918) {

    EXPECT_EQ(UCP(0x2015), GetClosingQuote(UCP(0x2015)));

}



TEST(GetClosingQuoteTest_1918, LeftSingleQuotationMark_ReturnsRightSingleQuotationMark_1918) {

    EXPECT_EQ(UCP(0x2019), GetClosingQuote(UCP(0x2018)));

}



TEST(GetClosingQuoteTest_1918, SingleLow9QuotationMark_ReturnsSingleHighReversed9QuotationMark_1918) {

    EXPECT_EQ(UCP(0x201B), GetClosingQuote(UCP(0x201A)));

}



TEST(GetClosingQuoteTest_1918, LeftDoubleQuotationMark_ReturnsRightDoubleQuotationMark_1918) {

    EXPECT_EQ(UCP(0x201D), GetClosingQuote(UCP(0x201C)));

}



TEST(GetClosingQuoteTest_1918, LeftDoubleAngleQuotationMark_ReturnsRightDoubleAngleQuotationMark_1918) {

    EXPECT_EQ(UCP(0x203A), GetClosingQuote(UCP(0x2039)));

}



TEST(GetClosingQuoteTest_1918, RightDoubleAngleQuotationMark_ReturnsLeftDoubleAngleQuotationMark_1918) {

    EXPECT_EQ(UCP(0x2039), GetClosingQuote(UCP(0x203A)));

}



TEST(GetClosingQuoteTest_1918, LeftAngularBracket_ReturnsRightAngularBracket_1918) {

    EXPECT_EQ(UCP(0x3009), GetClosingQuote(UCP(0x3008)));

}



TEST(GetClosingQuoteTest_1918, LeftDoubleAngleBracket_ReturnsRightDoubleAngleBracket_1918) {

    EXPECT_EQ(UCP(0x300B), GetClosingQuote(UCP(0x300A)));

}



TEST(GetClosingQuoteTest_1918, LeftCornerBracket_ReturnsRightCornerBracket_1918) {

    EXPECT_EQ(UCP(0x300D), GetClosingQuote(UCP(0x300C)));

}



TEST(GetClosingQuoteTest_1918, LeftWhiteCornerBracket_ReturnsRightWhiteCornerBracket_1918) {

    EXPECT_EQ(UCP(0x300F), GetClosingQuote(UCP(0x300E)));

}



TEST(GetClosingQuoteTest_1918, ReversedDoublePrimeQuotationMark_ReturnsDoublePrimeQuotationMark_1918) {

    EXPECT_EQ(UCP(0x301F), GetClosingQuote(UCP(0x301D)));

}



TEST(GetClosingQuoteTest_1918, UnknownCharacter_ReturnsZero_1918) {

    EXPECT_EQ(0, GetClosingQuote(UCP(0x0000))); // Example of an unknown character

}
