#include <gtest/gtest.h>
#include "UTF.h"

// Test normal whitespace characters
TEST(UnicodeIsWhitespaceTest_1522, TabIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x0009));
}

TEST(UnicodeIsWhitespaceTest_1522, LineFeedIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x000A));
}

TEST(UnicodeIsWhitespaceTest_1522, VerticalTabIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x000B));
}

TEST(UnicodeIsWhitespaceTest_1522, FormFeedIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x000C));
}

TEST(UnicodeIsWhitespaceTest_1522, CarriageReturnIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x000D));
}

TEST(UnicodeIsWhitespaceTest_1522, SpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x0020));
}

TEST(UnicodeIsWhitespaceTest_1522, NextLineIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x0085));
}

TEST(UnicodeIsWhitespaceTest_1522, NoBreakSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x00A0));
}

TEST(UnicodeIsWhitespaceTest_1522, EnQuadIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2000));
}

TEST(UnicodeIsWhitespaceTest_1522, EmQuadIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2001));
}

TEST(UnicodeIsWhitespaceTest_1522, EnSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2002));
}

TEST(UnicodeIsWhitespaceTest_1522, EmSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2003));
}

TEST(UnicodeIsWhitespaceTest_1522, ThreePerEmSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2004));
}

TEST(UnicodeIsWhitespaceTest_1522, FourPerEmSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2005));
}

TEST(UnicodeIsWhitespaceTest_1522, SixPerEmSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2006));
}

TEST(UnicodeIsWhitespaceTest_1522, FigureSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2007));
}

TEST(UnicodeIsWhitespaceTest_1522, PunctuationSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2008));
}

TEST(UnicodeIsWhitespaceTest_1522, ThinSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2009));
}

TEST(UnicodeIsWhitespaceTest_1522, HairSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x200A));
}

TEST(UnicodeIsWhitespaceTest_1522, LineSeparatorIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2028));
}

TEST(UnicodeIsWhitespaceTest_1522, ParagraphSeparatorIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x2029));
}

TEST(UnicodeIsWhitespaceTest_1522, NarrowNoBreakSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x202F));
}

TEST(UnicodeIsWhitespaceTest_1522, MediumMathematicalSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x205F));
}

TEST(UnicodeIsWhitespaceTest_1522, IdeographicSpaceIsWhitespace_1522) {
    EXPECT_TRUE(UnicodeIsWhitespace(0x3000));
}

// Test non-whitespace characters
TEST(UnicodeIsWhitespaceTest_1522, NullIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0000));
}

TEST(UnicodeIsWhitespaceTest_1522, LetterAIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0041)); // 'A'
}

TEST(UnicodeIsWhitespaceTest_1522, DigitZeroIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0030)); // '0'
}

TEST(UnicodeIsWhitespaceTest_1522, ExclamationMarkIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0021)); // '!'
}

// Boundary conditions - values adjacent to whitespace characters
TEST(UnicodeIsWhitespaceTest_1522, BeforeTabIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0008));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterCarriageReturnIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x000E));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x001F));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0021));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeNextLineIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0084));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterNextLineIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0086));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeNoBreakSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x009F));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterNoBreakSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x00A1));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeEnQuadIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x1FFF));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterHairSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x200B));
}

TEST(UnicodeIsWhitespaceTest_1522, BetweenHairSpaceAndLineSeparatorIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x200F));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeLineSeparatorIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x2027));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterParagraphSeparatorIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x202A));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeNarrowNoBreakSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x202E));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterNarrowNoBreakSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x2030));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeMediumMathSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x205E));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterMediumMathSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x2060));
}

TEST(UnicodeIsWhitespaceTest_1522, BeforeIdeographicSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x2FFF));
}

TEST(UnicodeIsWhitespaceTest_1522, AfterIdeographicSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x3001));
}

// Large Unicode values
TEST(UnicodeIsWhitespaceTest_1522, LargeUnicodeValueIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0xFFFF));
}

TEST(UnicodeIsWhitespaceTest_1522, HighUnicodeValueIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x10000));
}

TEST(UnicodeIsWhitespaceTest_1522, MaxUnicodeIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x10FFFF));
}

// Common printable characters that are not whitespace
TEST(UnicodeIsWhitespaceTest_1522, LatinSmallAIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x0061)); // 'a'
}

TEST(UnicodeIsWhitespaceTest_1522, CommaIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x002C)); // ','
}

TEST(UnicodeIsWhitespaceTest_1522, PeriodIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x002E)); // '.'
}

// Zero-width spaces (should NOT be in the whitespace list)
TEST(UnicodeIsWhitespaceTest_1522, ZeroWidthSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0x200B));
}

TEST(UnicodeIsWhitespaceTest_1522, ZeroWidthNoBreakSpaceIsNotWhitespace_1522) {
    EXPECT_FALSE(UnicodeIsWhitespace(0xFEFF));
}
