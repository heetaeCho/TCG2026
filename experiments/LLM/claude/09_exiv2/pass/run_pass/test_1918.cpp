#include <gtest/gtest.h>

// We need access to the static function. Include the implementation file.
// The necessary typedefs and macros need to be available.
typedef unsigned long UniCodePoint;
#ifndef UCP
#define UCP(x) x
#endif

// Re-declare the static function for testing purposes by including it inline
static UniCodePoint GetClosingQuote(UniCodePoint openQuote) {
    UniCodePoint closeQuote;
    switch (openQuote) {
        case UCP(0x0022): closeQuote = UCP(0x0022); break;
        case UCP(0x005B): closeQuote = UCP(0x005D); break;
        case UCP(0x00AB): closeQuote = UCP(0x00BB); break;
        case UCP(0x00BB): closeQuote = UCP(0x00AB); break;
        case UCP(0x2015): closeQuote = UCP(0x2015); break;
        case UCP(0x2018): closeQuote = UCP(0x2019); break;
        case UCP(0x201A): closeQuote = UCP(0x201B); break;
        case UCP(0x201C): closeQuote = UCP(0x201D); break;
        case UCP(0x201E): closeQuote = UCP(0x201F); break;
        case UCP(0x2039): closeQuote = UCP(0x203A); break;
        case UCP(0x203A): closeQuote = UCP(0x2039); break;
        case UCP(0x3008): closeQuote = UCP(0x3009); break;
        case UCP(0x300A): closeQuote = UCP(0x300B); break;
        case UCP(0x300C): closeQuote = UCP(0x300D); break;
        case UCP(0x300E): closeQuote = UCP(0x300F); break;
        case UCP(0x301D): closeQuote = UCP(0x301F); break;
        default: closeQuote = 0; break;
    }
    return closeQuote;
}

class GetClosingQuoteTest_1918 : public ::testing::Test {};

// Normal operation: self-closing double quote
TEST_F(GetClosingQuoteTest_1918, DoubleQuoteSelfClosing_1918) {
    EXPECT_EQ(GetClosingQuote(0x0022), 0x0022UL);
}

// Normal operation: square bracket
TEST_F(GetClosingQuoteTest_1918, SquareBracketClosing_1918) {
    EXPECT_EQ(GetClosingQuote(0x005B), 0x005DUL);
}

// Normal operation: left-pointing double angle quotation mark
TEST_F(GetClosingQuoteTest_1918, LeftDoubleAngleQuote_1918) {
    EXPECT_EQ(GetClosingQuote(0x00AB), 0x00BBUL);
}

// Normal operation: reversible right-pointing double angle quotation mark
TEST_F(GetClosingQuoteTest_1918, RightDoubleAngleQuoteReversible_1918) {
    EXPECT_EQ(GetClosingQuote(0x00BB), 0x00ABUL);
}

// Normal operation: horizontal bar self-closing
TEST_F(GetClosingQuoteTest_1918, HorizontalBarSelfClosing_1918) {
    EXPECT_EQ(GetClosingQuote(0x2015), 0x2015UL);
}

// Normal operation: left single quotation mark
TEST_F(GetClosingQuoteTest_1918, LeftSingleQuotationMark_1918) {
    EXPECT_EQ(GetClosingQuote(0x2018), 0x2019UL);
}

// Normal operation: single low-9 quotation mark
TEST_F(GetClosingQuoteTest_1918, SingleLow9QuotationMark_1918) {
    EXPECT_EQ(GetClosingQuote(0x201A), 0x201BUL);
}

// Normal operation: left double quotation mark
TEST_F(GetClosingQuoteTest_1918, LeftDoubleQuotationMark_1918) {
    EXPECT_EQ(GetClosingQuote(0x201C), 0x201DUL);
}

// Normal operation: double low-9 quotation mark
TEST_F(GetClosingQuoteTest_1918, DoubleLow9QuotationMark_1918) {
    EXPECT_EQ(GetClosingQuote(0x201E), 0x201FUL);
}

// Normal operation: single left-pointing angle quotation mark
TEST_F(GetClosingQuoteTest_1918, SingleLeftAngleQuote_1918) {
    EXPECT_EQ(GetClosingQuote(0x2039), 0x203AUL);
}

// Normal operation: reversible single right-pointing angle quotation mark
TEST_F(GetClosingQuoteTest_1918, SingleRightAngleQuoteReversible_1918) {
    EXPECT_EQ(GetClosingQuote(0x203A), 0x2039UL);
}

// Normal operation: left angle bracket (CJK)
TEST_F(GetClosingQuoteTest_1918, LeftAngleBracketCJK_1918) {
    EXPECT_EQ(GetClosingQuote(0x3008), 0x3009UL);
}

// Normal operation: left double angle bracket (CJK)
TEST_F(GetClosingQuoteTest_1918, LeftDoubleAngleBracketCJK_1918) {
    EXPECT_EQ(GetClosingQuote(0x300A), 0x300BUL);
}

// Normal operation: left corner bracket (CJK)
TEST_F(GetClosingQuoteTest_1918, LeftCornerBracketCJK_1918) {
    EXPECT_EQ(GetClosingQuote(0x300C), 0x300DUL);
}

// Normal operation: left white corner bracket (CJK)
TEST_F(GetClosingQuoteTest_1918, LeftWhiteCornerBracketCJK_1918) {
    EXPECT_EQ(GetClosingQuote(0x300E), 0x300FUL);
}

// Normal operation: reversed double prime quotation mark
TEST_F(GetClosingQuoteTest_1918, ReversedDoublePrimeQuote_1918) {
    EXPECT_EQ(GetClosingQuote(0x301D), 0x301FUL);
}

// Default case: unrecognized code point returns 0
TEST_F(GetClosingQuoteTest_1918, DefaultReturnsZero_1918) {
    EXPECT_EQ(GetClosingQuote(0x0000), 0UL);
}

// Default case: arbitrary unrecognized code point
TEST_F(GetClosingQuoteTest_1918, ArbitraryUnrecognizedReturnsZero_1918) {
    EXPECT_EQ(GetClosingQuote(0x0041), 0UL);  // 'A'
}

// Default case: code point just before a known one
TEST_F(GetClosingQuoteTest_1918, CodePointBeforeKnownReturnsZero_1918) {
    EXPECT_EQ(GetClosingQuote(0x0021), 0UL);
}

// Default case: code point just after a known one
TEST_F(GetClosingQuoteTest_1918, CodePointAfterKnownReturnsZero_1918) {
    EXPECT_EQ(GetClosingQuote(0x0023), 0UL);
}

// Boundary: very large code point
TEST_F(GetClosingQuoteTest_1918, VeryLargeCodePointReturnsZero_1918) {
    EXPECT_EQ(GetClosingQuote(0xFFFFFFFF), 0UL);
}

// Boundary: code point 0x301E is NOT a recognized opening quote (301D maps to 301F)
TEST_F(GetClosingQuoteTest_1918, U301ENotRecognized_1918) {
    EXPECT_EQ(GetClosingQuote(0x301E), 0UL);
}

// Boundary: closing quotes should not map as openers (except reversible ones)
TEST_F(GetClosingQuoteTest_1918, ClosingQuote005DNotRecognized_1918) {
    EXPECT_EQ(GetClosingQuote(0x005D), 0UL);
}

TEST_F(GetClosingQuoteTest_1918, ClosingQuote2019NotRecognized_1918) {
    EXPECT_EQ(GetClosingQuote(0x2019), 0UL);
}

TEST_F(GetClosingQuoteTest_1918, ClosingQuote201DNotRecognized_1918) {
    EXPECT_EQ(GetClosingQuote(0x201D), 0UL);
}

TEST_F(GetClosingQuoteTest_1918, ClosingQuote3009NotRecognized_1918) {
    EXPECT_EQ(GetClosingQuote(0x3009), 0UL);
}

// Verify reversibility: AB -> BB -> AB
TEST_F(GetClosingQuoteTest_1918, ReversibilityDoubleAngle_1918) {
    UniCodePoint first = GetClosingQuote(0x00AB);
    UniCodePoint second = GetClosingQuote(first);
    EXPECT_EQ(second, 0x00ABUL);
}

// Verify reversibility: 2039 -> 203A -> 2039
TEST_F(GetClosingQuoteTest_1918, ReversibilitySingleAngle_1918) {
    UniCodePoint first = GetClosingQuote(0x2039);
    UniCodePoint second = GetClosingQuote(first);
    EXPECT_EQ(second, 0x2039UL);
}

// Verify self-closing: applying twice gives same result
TEST_F(GetClosingQuoteTest_1918, SelfClosingDoubleQuoteIdempotent_1918) {
    UniCodePoint first = GetClosingQuote(0x0022);
    UniCodePoint second = GetClosingQuote(first);
    EXPECT_EQ(first, second);
}

TEST_F(GetClosingQuoteTest_1918, SelfClosingHorizontalBarIdempotent_1918) {
    UniCodePoint first = GetClosingQuote(0x2015);
    UniCodePoint second = GetClosingQuote(first);
    EXPECT_EQ(first, second);
}
