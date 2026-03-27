#include <gtest/gtest.h>



// Assuming UCP macro is defined somewhere in the codebase to convert integer to UniCodePoint

#define UCP(x) static_cast<UniCodePoint>(x)



using namespace ::testing;



TEST(IsClosingQuoteTest_1916, NormalOperation_SameOpenCloseQuote_1916) {

    EXPECT_TRUE(IsClosingingQuote(UCP('\''), UCP('\''), UCP('\'')));

}



TEST(IsClosingQuoteTest_1916, NormalOperation_DifferentOpenCloseQuotes_1916) {

    EXPECT_FALSE(IsClosingingQuote(UCP('"'), UCP('\''), UCP('"')));

}



TEST(IsClosingQuoteTest_1916, BoundaryCondition_EmptyString_1916) {

    EXPECT_FALSE(IsClosingingQuote(UCP('\0'), UCP('\0'), UCP('\0')));

}



TEST(IsClosingQuoteTest_1916, BoundaryCondition_OpenCloseSameAsSpecialCase_1916) {

    EXPECT_TRUE(IsClosingingQuote(UCP(0x301E), UCP(0x301D), UCP(0x301E)));

}



TEST(IsClosingQuoteTest_1916, SpecialCase_OpenIsSpecial_CloseIsSpecial_1916) {

    EXPECT_TRUE(IsClosingingQuote(UCP(0x301F), UCP(0x301D), UCP(0x301F)));

}



TEST(IsClosingQuoteTest_1916, SpecialCase_OpenIsNotSpecial_CloseIsSpecial_1916) {

    EXPECT_FALSE(IsClosingingQuote(UCP(0x301E), UCP('\''), UCP(0x301E)));

}



TEST(IsClosingQuoteTest_1916, ExceptionalCase_NonMatchingQuotes_1916) {

    EXPECT_FALSE(IsClosingingQuote(UCP('"'), UCP('\''), UCP('`')));

}
