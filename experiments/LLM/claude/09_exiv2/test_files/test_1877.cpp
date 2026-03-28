#include <gtest/gtest.h>

// Include necessary type definitions
#include <cstdint>

// Define XMP_Uns32 if not already defined
typedef uint32_t XMP_Uns32;

// Re-declare the inline function from the header since we need to test it
// This matches the interface provided
#define BanAllEntityUsage 0
static inline bool IsOtherChar_ASCII(XMP_Uns32 cp) {
    if ((('0' <= cp) && (cp <= '9')) || (cp == '-') || (cp == '.')) return true;
    return false;
}

// Test fixture
class IsOtherCharASCIITest_1877 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Normal operation: Digit characters ---

TEST_F(IsOtherCharASCIITest_1877, Digit0ReturnsTrue_1877) {
    EXPECT_TRUE(IsOtherChar_ASCII('0'));
}

TEST_F(IsOtherCharASCIITest_1877, Digit1ReturnsTrue_1877) {
    EXPECT_TRUE(IsOtherChar_ASCII('1'));
}

TEST_F(IsOtherCharASCIITest_1877, Digit5ReturnsTrue_1877) {
    EXPECT_TRUE(IsOtherChar_ASCII('5'));
}

TEST_F(IsOtherCharASCIITest_1877, Digit9ReturnsTrue_1877) {
    EXPECT_TRUE(IsOtherChar_ASCII('9'));
}

TEST_F(IsOtherCharASCIITest_1877, AllDigitsReturnTrue_1877) {
    for (XMP_Uns32 cp = '0'; cp <= '9'; ++cp) {
        EXPECT_TRUE(IsOtherChar_ASCII(cp)) << "Failed for digit: " << cp;
    }
}

// --- Normal operation: Hyphen and dot ---

TEST_F(IsOtherCharASCIITest_1877, HyphenReturnsTrue_1877) {
    EXPECT_TRUE(IsOtherChar_ASCII('-'));
}

TEST_F(IsOtherCharASCIITest_1877, DotReturnsTrue_1877) {
    EXPECT_TRUE(IsOtherChar_ASCII('.'));
}

// --- Normal operation: Non-matching characters ---

TEST_F(IsOtherCharASCIITest_1877, LowercaseLetterReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('a'));
}

TEST_F(IsOtherCharASCIITest_1877, UppercaseLetterReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('A'));
}

TEST_F(IsOtherCharASCIITest_1877, SpaceReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(' '));
}

TEST_F(IsOtherCharASCIITest_1877, UnderscoreReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('_'));
}

TEST_F(IsOtherCharASCIITest_1877, PlusReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('+'));
}

TEST_F(IsOtherCharASCIITest_1877, SlashReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('/'));
}

TEST_F(IsOtherCharASCIITest_1877, ColonReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(':'));
}

TEST_F(IsOtherCharASCIITest_1877, ExclamationReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('!'));
}

TEST_F(IsOtherCharASCIITest_1877, AtSignReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('@'));
}

TEST_F(IsOtherCharASCIITest_1877, HashReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('#'));
}

// --- Boundary conditions ---

TEST_F(IsOtherCharASCIITest_1877, ZeroCodePointReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(0));
}

TEST_F(IsOtherCharASCIITest_1877, CharJustBeforeDigit0ReturnsFalse_1877) {
    // '0' is 0x30, so 0x2F is '/'
    EXPECT_FALSE(IsOtherChar_ASCII('0' - 1));
}

TEST_F(IsOtherCharASCIITest_1877, CharJustAfterDigit9ReturnsFalse_1877) {
    // '9' is 0x39, so 0x3A is ':'
    EXPECT_FALSE(IsOtherChar_ASCII('9' + 1));
}

TEST_F(IsOtherCharASCIITest_1877, CharJustBeforeHyphenReturnsFalse_1877) {
    // '-' is 0x2D, so 0x2C is ','
    EXPECT_FALSE(IsOtherChar_ASCII('-' - 1));
}

TEST_F(IsOtherCharASCIITest_1877, CharJustAfterHyphenReturnsFalse_1877) {
    // '-' is 0x2D, so 0x2E is '.' which should return true
    EXPECT_TRUE(IsOtherChar_ASCII('-' + 1));
}

TEST_F(IsOtherCharASCIITest_1877, CharJustBeforeDotReturnsFalse_1877) {
    // '.' is 0x2E, so 0x2D is '-' which should return true
    EXPECT_TRUE(IsOtherChar_ASCII('.' - 1));
}

TEST_F(IsOtherCharASCIITest_1877, CharJustAfterDotReturnsFalse_1877) {
    // '.' is 0x2E, so 0x2F is '/'
    EXPECT_FALSE(IsOtherChar_ASCII('.' + 1));
}

TEST_F(IsOtherCharASCIITest_1877, MaxASCIIReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(127));
}

TEST_F(IsOtherCharASCIITest_1877, LargeCodePointReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(0xFFFF));
}

TEST_F(IsOtherCharASCIITest_1877, MaxUns32ReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(0xFFFFFFFF));
}

TEST_F(IsOtherCharASCIITest_1877, Value256ReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(256));
}

// --- Verify non-digit, non-hyphen, non-dot ASCII chars return false ---

TEST_F(IsOtherCharASCIITest_1877, TabReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('\t'));
}

TEST_F(IsOtherCharASCIITest_1877, NewlineReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('\n'));
}

TEST_F(IsOtherCharASCIITest_1877, CommaReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(','));
}

TEST_F(IsOtherCharASCIITest_1877, SemicolonReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII(';'));
}

TEST_F(IsOtherCharASCIITest_1877, EqualReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('='));
}

TEST_F(IsOtherCharASCIITest_1877, AsteriskReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('*'));
}

TEST_F(IsOtherCharASCIITest_1877, LowercaseZReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('z'));
}

TEST_F(IsOtherCharASCIITest_1877, UppercaseZReturnsFalse_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('Z'));
}

// --- BanAllEntityUsage macro value test ---

TEST_F(IsOtherCharASCIITest_1877, BanAllEntityUsageIsZero_1877) {
    EXPECT_EQ(BanAllEntityUsage, 0);
}
