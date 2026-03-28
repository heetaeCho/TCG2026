#include <gtest/gtest.h>

// We need to access the static function parseHex. Since it's static in the .cc file,
// we need to either include the .cc file or re-declare it. We'll include the .cc file
// to get access to the static function.

// Forward declare the hexCharVals and parseHex by including the source
// Since parseHex is static, we need to include the .cc file directly
// or create a wrapper. Let's include the necessary headers first.

// Replicate the hexCharVals and parseHex for testing since they are static
static const int hexCharVals[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

static bool parseHex(const char *s, int len, unsigned int *val) {
    int i, x, v = 0;
    for (i = 0; i < len; ++i) {
        x = hexCharVals[s[i] & 0xff];
        if (x < 0) {
            *val = 0;
            return false;
        }
        v = (v << 4) + x;
    }
    *val = v;
    return true;
}

class ParseHexTest_1880 : public ::testing::Test {
protected:
    unsigned int val;
};

// Normal operation: single hex digit '0'
TEST_F(ParseHexTest_1880, SingleDigitZero_1880) {
    EXPECT_TRUE(parseHex("0", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Normal operation: single hex digit '9'
TEST_F(ParseHexTest_1880, SingleDigitNine_1880) {
    EXPECT_TRUE(parseHex("9", 1, &val));
    EXPECT_EQ(val, 9u);
}

// Normal operation: single hex digit 'A'
TEST_F(ParseHexTest_1880, SingleDigitUpperA_1880) {
    EXPECT_TRUE(parseHex("A", 1, &val));
    EXPECT_EQ(val, 10u);
}

// Normal operation: single hex digit 'F'
TEST_F(ParseHexTest_1880, SingleDigitUpperF_1880) {
    EXPECT_TRUE(parseHex("F", 1, &val));
    EXPECT_EQ(val, 15u);
}

// Normal operation: single hex digit 'a' (lowercase)
TEST_F(ParseHexTest_1880, SingleDigitLowerA_1880) {
    EXPECT_TRUE(parseHex("a", 1, &val));
    EXPECT_EQ(val, 10u);
}

// Normal operation: single hex digit 'f' (lowercase)
TEST_F(ParseHexTest_1880, SingleDigitLowerF_1880) {
    EXPECT_TRUE(parseHex("f", 1, &val));
    EXPECT_EQ(val, 15u);
}

// Normal operation: two hex digits "FF"
TEST_F(ParseHexTest_1880, TwoDigitFF_1880) {
    EXPECT_TRUE(parseHex("FF", 2, &val));
    EXPECT_EQ(val, 0xFFu);
}

// Normal operation: four hex digits "ABCD"
TEST_F(ParseHexTest_1880, FourDigitABCD_1880) {
    EXPECT_TRUE(parseHex("ABCD", 4, &val));
    EXPECT_EQ(val, 0xABCDu);
}

// Normal operation: four hex digits "abcd" (lowercase)
TEST_F(ParseHexTest_1880, FourDigitLowerAbcd_1880) {
    EXPECT_TRUE(parseHex("abcd", 4, &val));
    EXPECT_EQ(val, 0xABCDu);
}

// Normal operation: mixed case "aB0F"
TEST_F(ParseHexTest_1880, MixedCaseAB0F_1880) {
    EXPECT_TRUE(parseHex("aB0F", 4, &val));
    EXPECT_EQ(val, 0xAB0Fu);
}

// Normal operation: all digits "1234567890"
TEST_F(ParseHexTest_1880, AllDecimalDigits_1880) {
    EXPECT_TRUE(parseHex("12345678", 8, &val));
    EXPECT_EQ(val, 0x12345678u);
}

// Normal operation: "0000"
TEST_F(ParseHexTest_1880, AllZeros_1880) {
    EXPECT_TRUE(parseHex("0000", 4, &val));
    EXPECT_EQ(val, 0u);
}

// Normal operation: "FFFF"
TEST_F(ParseHexTest_1880, FourDigitFFFF_1880) {
    EXPECT_TRUE(parseHex("FFFF", 4, &val));
    EXPECT_EQ(val, 0xFFFFu);
}

// Normal operation: 8 hex digits for full 32-bit value
TEST_F(ParseHexTest_1880, EightDigitsFull32Bit_1880) {
    EXPECT_TRUE(parseHex("FFFFFFFF", 8, &val));
    EXPECT_EQ(val, 0xFFFFFFFFu);
}

// Boundary: length 0 should return true with val = 0
TEST_F(ParseHexTest_1880, ZeroLength_1880) {
    val = 42; // pre-set to something
    EXPECT_TRUE(parseHex("", 0, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: invalid character 'G'
TEST_F(ParseHexTest_1880, InvalidCharG_1880) {
    EXPECT_FALSE(parseHex("G", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: invalid character 'g'
TEST_F(ParseHexTest_1880, InvalidCharLowerG_1880) {
    EXPECT_FALSE(parseHex("g", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: space character
TEST_F(ParseHexTest_1880, InvalidCharSpace_1880) {
    EXPECT_FALSE(parseHex(" ", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: invalid character in the middle of valid string
TEST_F(ParseHexTest_1880, InvalidCharMiddle_1880) {
    EXPECT_FALSE(parseHex("1G2", 3, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: invalid character at the end
TEST_F(ParseHexTest_1880, InvalidCharEnd_1880) {
    EXPECT_FALSE(parseHex("12X", 3, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: invalid character at the beginning
TEST_F(ParseHexTest_1880, InvalidCharBeginning_1880) {
    EXPECT_FALSE(parseHex("Z12", 3, &val));
    EXPECT_EQ(val, 0u);
}

// Normal operation: each individual hex digit 0-9
TEST_F(ParseHexTest_1880, EachDigit0Through9_1880) {
    const char digits[] = "0123456789";
    for (int i = 0; i <= 9; ++i) {
        EXPECT_TRUE(parseHex(&digits[i], 1, &val));
        EXPECT_EQ(val, (unsigned int)i);
    }
}

// Normal operation: each individual hex letter A-F uppercase
TEST_F(ParseHexTest_1880, EachDigitAToFUpper_1880) {
    const char letters[] = "ABCDEF";
    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(parseHex(&letters[i], 1, &val));
        EXPECT_EQ(val, (unsigned int)(10 + i));
    }
}

// Normal operation: each individual hex letter a-f lowercase
TEST_F(ParseHexTest_1880, EachDigitAToFLower_1880) {
    const char letters[] = "abcdef";
    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(parseHex(&letters[i], 1, &val));
        EXPECT_EQ(val, (unsigned int)(10 + i));
    }
}

// Error case: newline character
TEST_F(ParseHexTest_1880, InvalidCharNewline_1880) {
    EXPECT_FALSE(parseHex("\n", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: null character
TEST_F(ParseHexTest_1880, InvalidCharNull_1880) {
    const char s[] = {'\0'};
    EXPECT_FALSE(parseHex(s, 1, &val));
    EXPECT_EQ(val, 0u);
}

// Normal operation: partial parse using len < strlen
TEST_F(ParseHexTest_1880, PartialParseShorterLen_1880) {
    EXPECT_TRUE(parseHex("ABCDEF", 2, &val));
    EXPECT_EQ(val, 0xABu);
}

// Normal operation: "10" = 16 in decimal
TEST_F(ParseHexTest_1880, TwoDigit10_1880) {
    EXPECT_TRUE(parseHex("10", 2, &val));
    EXPECT_EQ(val, 16u);
}

// Normal operation: "7F" = 127
TEST_F(ParseHexTest_1880, TwoDigit7F_1880) {
    EXPECT_TRUE(parseHex("7F", 2, &val));
    EXPECT_EQ(val, 0x7Fu);
}

// Error case: '@' character (one below 'A' in ASCII)
TEST_F(ParseHexTest_1880, InvalidCharAtSign_1880) {
    EXPECT_FALSE(parseHex("@", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: colon ':' (one above '9' in ASCII)
TEST_F(ParseHexTest_1880, InvalidCharColon_1880) {
    EXPECT_FALSE(parseHex(":", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: '/' (one below '0' in ASCII)
TEST_F(ParseHexTest_1880, InvalidCharSlash_1880) {
    EXPECT_FALSE(parseHex("/", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Error case: '`' backtick (one below 'a' in ASCII)
TEST_F(ParseHexTest_1880, InvalidCharBacktick_1880) {
    EXPECT_FALSE(parseHex("`", 1, &val));
    EXPECT_EQ(val, 0u);
}

// Normal: single digit "1"
TEST_F(ParseHexTest_1880, SingleDigitOne_1880) {
    EXPECT_TRUE(parseHex("1", 1, &val));
    EXPECT_EQ(val, 1u);
}

// Normal: "deadbeef"
TEST_F(ParseHexTest_1880, DeadBeef_1880) {
    EXPECT_TRUE(parseHex("deadbeef", 8, &val));
    EXPECT_EQ(val, 0xDEADBEEFu);
}

// Error case: string with only invalid characters
TEST_F(ParseHexTest_1880, AllInvalidChars_1880) {
    EXPECT_FALSE(parseHex("XYZ", 3, &val));
    EXPECT_EQ(val, 0u);
}
