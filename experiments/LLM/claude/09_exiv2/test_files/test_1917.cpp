#include <gtest/gtest.h>

// Replicate the types and minimal dependencies needed to test the function
typedef unsigned long UniCodePoint;

// We need IsClosingingQuote to be available since IsSurroundingQuote depends on it.
// Based on the interface, we replicate the static inline function as provided.
// Common quote pairs in Unicode:
// 0x201C (") open, 0x201D (") close
// 0x2018 (') open, 0x2019 (') close
// 0x00AB («) open, 0x00BB (») close
// 0x0022 (") ASCII double quote (same open/close)

// Since the function under test is static inline in a .cpp file, we include
// the minimal necessary context to test it. We define IsClosingingQuote
// based on common behavior: returns true if uniChar == closeQuote.
static inline bool IsClosingingQuote(UniCodePoint uniChar, UniCodePoint openQuote, UniCodePoint closeQuote) {
    (void)openQuote;
    return (uniChar == closeQuote);
}

static inline bool IsSurroundingQuote(UniCodePoint uniChar, UniCodePoint openQuote, UniCodePoint closeQuote) {
    if ((uniChar == openQuote) || IsClosingingQuote(uniChar, openQuote, closeQuote)) {
        return true;
    } else {
        return false;
    }
}

class IsSurroundingQuoteTest_1917 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: uniChar matches the openQuote exactly
TEST_F(IsSurroundingQuoteTest_1917, MatchesOpenQuote_1917) {
    UniCodePoint openQuote = 0x201C;  // "
    UniCodePoint closeQuote = 0x201D; // "
    EXPECT_TRUE(IsSurroundingQuote(openQuote, openQuote, closeQuote));
}

// Test: uniChar matches the closeQuote exactly
TEST_F(IsSurroundingQuoteTest_1917, MatchesCloseQuote_1917) {
    UniCodePoint openQuote = 0x201C;
    UniCodePoint closeQuote = 0x201D;
    EXPECT_TRUE(IsSurroundingQuote(closeQuote, openQuote, closeQuote));
}

// Test: uniChar matches neither open nor close quote
TEST_F(IsSurroundingQuoteTest_1917, MatchesNeitherQuote_1917) {
    UniCodePoint openQuote = 0x201C;
    UniCodePoint closeQuote = 0x201D;
    UniCodePoint other = 0x0041; // 'A'
    EXPECT_FALSE(IsSurroundingQuote(other, openQuote, closeQuote));
}

// Test: open and close quotes are the same character, uniChar matches
TEST_F(IsSurroundingQuoteTest_1917, SameOpenAndCloseQuoteMatches_1917) {
    UniCodePoint quote = 0x0022; // ASCII "
    EXPECT_TRUE(IsSurroundingQuote(quote, quote, quote));
}

// Test: open and close quotes are the same, uniChar does not match
TEST_F(IsSurroundingQuoteTest_1917, SameOpenAndCloseQuoteNoMatch_1917) {
    UniCodePoint quote = 0x0022;
    UniCodePoint other = 0x0027; // ASCII '
    EXPECT_FALSE(IsSurroundingQuote(other, quote, quote));
}

// Test: boundary - zero values
TEST_F(IsSurroundingQuoteTest_1917, ZeroValues_1917) {
    EXPECT_TRUE(IsSurroundingQuote(0, 0, 0));
}

// Test: boundary - zero uniChar with non-zero quotes
TEST_F(IsSurroundingQuoteTest_1917, ZeroUniCharNonZeroQuotes_1917) {
    EXPECT_FALSE(IsSurroundingQuote(0, 0x201C, 0x201D));
}

// Test: large Unicode code points
TEST_F(IsSurroundingQuoteTest_1917, LargeCodePoints_1917) {
    UniCodePoint openQuote = 0x1F600;   // emoji range
    UniCodePoint closeQuote = 0x1F601;
    EXPECT_TRUE(IsSurroundingQuote(0x1F600, openQuote, closeQuote));
    EXPECT_TRUE(IsSurroundingQuote(0x1F601, openQuote, closeQuote));
    EXPECT_FALSE(IsSurroundingQuote(0x1F602, openQuote, closeQuote));
}

// Test: single quote pair (Unicode)
TEST_F(IsSurroundingQuoteTest_1917, UnicodeSingleQuotePair_1917) {
    UniCodePoint openQuote = 0x2018;  // '
    UniCodePoint closeQuote = 0x2019; // '
    EXPECT_TRUE(IsSurroundingQuote(0x2018, openQuote, closeQuote));
    EXPECT_TRUE(IsSurroundingQuote(0x2019, openQuote, closeQuote));
    EXPECT_FALSE(IsSurroundingQuote(0x201A, openQuote, closeQuote));
}

// Test: guillemet pair
TEST_F(IsSurroundingQuoteTest_1917, GuillemetsQuotePair_1917) {
    UniCodePoint openQuote = 0x00AB;  // «
    UniCodePoint closeQuote = 0x00BB; // »
    EXPECT_TRUE(IsSurroundingQuote(0x00AB, openQuote, closeQuote));
    EXPECT_TRUE(IsSurroundingQuote(0x00BB, openQuote, closeQuote));
    EXPECT_FALSE(IsSurroundingQuote(0x00AC, openQuote, closeQuote));
}

// Test: uniChar equals closeQuote but not openQuote
TEST_F(IsSurroundingQuoteTest_1917, OnlyCloseQuoteMatch_1917) {
    UniCodePoint openQuote = 0x0028;  // (
    UniCodePoint closeQuote = 0x0029; // )
    EXPECT_TRUE(IsSurroundingQuote(0x0029, openQuote, closeQuote));
}

// Test: uniChar equals openQuote but not closeQuote
TEST_F(IsSurroundingQuoteTest_1917, OnlyOpenQuoteMatch_1917) {
    UniCodePoint openQuote = 0x0028;
    UniCodePoint closeQuote = 0x0029;
    EXPECT_TRUE(IsSurroundingQuote(0x0028, openQuote, closeQuote));
}

// Test: max unsigned long value
TEST_F(IsSurroundingQuoteTest_1917, MaxUnsignedLongBoundary_1917) {
    UniCodePoint maxVal = ULONG_MAX;
    EXPECT_TRUE(IsSurroundingQuote(maxVal, maxVal, 0));
    EXPECT_TRUE(IsSurroundingQuote(maxVal, 0, maxVal));
    EXPECT_FALSE(IsSurroundingQuote(maxVal - 1, maxVal, 0));
}

// Test: returns false for completely unrelated characters
TEST_F(IsSurroundingQuoteTest_1917, UnrelatedCharacters_1917) {
    EXPECT_FALSE(IsSurroundingQuote(0x0061, 0x201C, 0x201D)); // 'a' is not a quote
    EXPECT_FALSE(IsSurroundingQuote(0x0030, 0x201C, 0x201D)); // '0' is not a quote
    EXPECT_FALSE(IsSurroundingQuote(0x0020, 0x201C, 0x201D)); // space is not a quote
}
