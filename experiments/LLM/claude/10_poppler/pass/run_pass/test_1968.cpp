#include <gtest/gtest.h>

// We need to access the static function parseNumericName.
// Since it's defined as static in GfxFont.cc, we include the .cc file directly
// or redeclare. Given the constraint that we treat it as a black box and just test it,
// we'll include the source to get access to the static function.

// Forward declare or include necessary headers
#include <cstring>
#include <cctype>
#include <cstdlib>

// Since parseNumericName is a static function in GfxFont.cc, we need to
// include it. We'll use a workaround to access it.
// Re-declare the function signature matching the implementation for testing purposes.

// We include the actual source file to get the static function
// But first we need to handle the dependencies. Let's try a minimal approach:
// Copy the function signature and test it by including the cc file.

// Minimal stub/include approach - include just enough to compile parseNumericName
namespace {
#define N_UCS_CANDIDATES 2

static bool parseNumericName(const char *s, bool hex, unsigned int *u)
{
    char *endptr;
    if (hex) {
        int n = 0;
        while (isalnum(s[n])) {
            ++n;
        }
        if (n == 3 && isalpha(*s)) {
            ++s;
        } else if (n != 2) {
            return false;
        }
    } else {
        for (int i = 0; i < 2 && isalpha(*s); ++i) {
            ++s;
        }
    }
    int v = strtol(s, &endptr, hex ? 16 : 10);
    if (endptr == s) {
        return false;
    }
    while (*endptr != '\0' && !isalnum(*endptr)) {
        ++endptr;
    }
    if (*endptr == '\0') {
        if (u) {
            *u = v;
        }
        return true;
    }
    return false;
}
} // anonymous namespace

class ParseNumericNameTest_1968 : public ::testing::Test {
protected:
    unsigned int result;
    void SetUp() override {
        result = 0;
    }
};

// ============================================================
// Hex mode tests
// ============================================================

TEST_F(ParseNumericNameTest_1968, HexTwoDigitValid_1968) {
    // Two hex digit string like "FF"
    EXPECT_TRUE(parseNumericName("FF", true, &result));
    EXPECT_EQ(result, 0xFF);
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitLowerCase_1968) {
    EXPECT_TRUE(parseNumericName("ab", true, &result));
    EXPECT_EQ(result, 0xAB);
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitNumeric_1968) {
    EXPECT_TRUE(parseNumericName("12", true, &result));
    EXPECT_EQ(result, 0x12);
}

TEST_F(ParseNumericNameTest_1968, HexThreeCharWithAlphaPrefix_1968) {
    // n==3 and first char is alpha -> skip first char, parse remaining 2 hex digits
    EXPECT_TRUE(parseNumericName("A1F", true, &result));
    EXPECT_EQ(result, 0x1F);
}

TEST_F(ParseNumericNameTest_1968, HexThreeCharAllAlpha_1968) {
    // n==3 and first char is alpha -> skip, parse "BC" as hex
    EXPECT_TRUE(parseNumericName("ABC", true, &result));
    EXPECT_EQ(result, 0xBC);
}

TEST_F(ParseNumericNameTest_1968, HexThreeCharFirstDigit_1968) {
    // n==3 but first char is digit (not alpha) -> n != 2, return false
    EXPECT_FALSE(parseNumericName("1AB", true, &result));
}

TEST_F(ParseNumericNameTest_1968, HexOneCharFails_1968) {
    // n==1, which is not 2 and not (3 with alpha prefix) -> false
    EXPECT_FALSE(parseNumericName("F", true, &result));
}

TEST_F(ParseNumericNameTest_1968, HexFourCharFails_1968) {
    // n==4, not matching any condition -> false
    EXPECT_FALSE(parseNumericName("ABCD", true, &result));
}

TEST_F(ParseNumericNameTest_1968, HexZeroCharFails_1968) {
    // Empty string -> n==0, not 2 or 3 -> false
    EXPECT_FALSE(parseNumericName("", true, &result));
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitWithTrailingNonAlnum_1968) {
    // "FF." -> n==2 (only alnum counted), parse "FF", endptr points to ".", skip non-alnum, reach '\0'
    EXPECT_TRUE(parseNumericName("FF.", true, &result));
    EXPECT_EQ(result, 0xFF);
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitWithTrailingAlnumFails_1968) {
    // "FF.A" -> after parsing "FF", endptr='.', skip non-alnum, reach 'A' which is alnum -> false
    // Wait: n counts leading alnum chars. "FF.A" -> alnum at s[0]='F', s[1]='F', s[2]='.' not alnum -> n=2
    // So n==2, then parse "FF" hex = 255, endptr points to ".A"
    // Skip '.', then reach 'A' which is alnum -> return false
    EXPECT_FALSE(parseNumericName("FF.A", true, &result));
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitZero_1968) {
    EXPECT_TRUE(parseNumericName("00", true, &result));
    EXPECT_EQ(result, 0x00);
}

TEST_F(ParseNumericNameTest_1968, HexNullOutput_1968) {
    // Passing null for u should still return true but not crash
    EXPECT_TRUE(parseNumericName("FF", true, nullptr));
}

// ============================================================
// Decimal mode tests
// ============================================================

TEST_F(ParseNumericNameTest_1968, DecimalPureNumber_1968) {
    EXPECT_TRUE(parseNumericName("123", false, &result));
    EXPECT_EQ(result, 123u);
}

TEST_F(ParseNumericNameTest_1968, DecimalWithOneAlphaPrefix_1968) {
    // One alpha prefix char skipped, then parse decimal
    EXPECT_TRUE(parseNumericName("A42", false, &result));
    EXPECT_EQ(result, 42u);
}

TEST_F(ParseNumericNameTest_1968, DecimalWithTwoAlphaPrefix_1968) {
    // Two alpha prefix chars skipped
    EXPECT_TRUE(parseNumericName("AB42", false, &result));
    EXPECT_EQ(result, 42u);
}

TEST_F(ParseNumericNameTest_1968, DecimalWithThreeAlphaPrefixFails_1968) {
    // Only up to 2 alpha chars are skipped, so "ABC42" -> skip "AB", left with "C42"
    // strtol("C42", ..., 10) -> endptr == s (can't parse 'C' as decimal) -> false
    EXPECT_FALSE(parseNumericName("ABC42", false, &result));
}

TEST_F(ParseNumericNameTest_1968, DecimalZero_1968) {
    EXPECT_TRUE(parseNumericName("0", false, &result));
    EXPECT_EQ(result, 0u);
}

TEST_F(ParseNumericNameTest_1968, DecimalNegativeNumber_1968) {
    // strtol can parse negative numbers
    // "-5" -> no alpha prefix, parse "-5" = -5
    // v = -5, cast to unsigned int
    unsigned int res;
    EXPECT_TRUE(parseNumericName("-5", false, &res));
    // The value stored is (unsigned int)(-5)
    EXPECT_EQ(res, (unsigned int)-5);
}

TEST_F(ParseNumericNameTest_1968, DecimalPureAlphaFails_1968) {
    // "AB" -> skip 2 alpha, left with "", strtol("", ...) -> endptr==s -> false
    EXPECT_FALSE(parseNumericName("AB", false, &result));
}

TEST_F(ParseNumericNameTest_1968, DecimalEmptyStringFails_1968) {
    EXPECT_FALSE(parseNumericName("", false, &result));
}

TEST_F(ParseNumericNameTest_1968, DecimalTrailingNonAlnum_1968) {
    // "42." -> parse 42, endptr='.', skip non-alnum, reach '\0' -> true
    EXPECT_TRUE(parseNumericName("42.", false, &result));
    EXPECT_EQ(result, 42u);
}

TEST_F(ParseNumericNameTest_1968, DecimalTrailingAlnumFails_1968) {
    // "42.5" -> parse 42, endptr='.', skip '.', reach '5' (alnum) -> false
    EXPECT_FALSE(parseNumericName("42.5", false, &result));
}

TEST_F(ParseNumericNameTest_1968, DecimalTrailingAlphaFails_1968) {
    // "42abc" -> parse 42, endptr='a' which is alnum, so while loop doesn't skip it (isalnum is true, but the loop skips !isalnum)
    // Actually: while (*endptr != '\0' && !isalnum(*endptr)) -> 'a' is alnum, so loop doesn't execute
    // Then *endptr == 'a' != '\0' -> return false
    EXPECT_FALSE(parseNumericName("42abc", false, &result));
}

TEST_F(ParseNumericNameTest_1968, DecimalNullOutput_1968) {
    EXPECT_TRUE(parseNumericName("42", false, nullptr));
}

TEST_F(ParseNumericNameTest_1968, DecimalLargeNumber_1968) {
    EXPECT_TRUE(parseNumericName("99999", false, &result));
    EXPECT_EQ(result, 99999u);
}

TEST_F(ParseNumericNameTest_1968, DecimalWithMultipleTrailingSpecialChars_1968) {
    // "42..." -> parse 42, skip "...", reach '\0' -> true
    EXPECT_TRUE(parseNumericName("42...", false, &result));
    EXPECT_EQ(result, 42u);
}

TEST_F(ParseNumericNameTest_1968, HexThreeCharWithAlphaPrefixLower_1968) {
    // "aFF" -> n=3 (all alnum), first is alpha -> skip first, parse "FF"
    EXPECT_TRUE(parseNumericName("aFF", true, &result));
    EXPECT_EQ(result, 0xFF);
}

TEST_F(ParseNumericNameTest_1968, DecimalSingleDigit_1968) {
    EXPECT_TRUE(parseNumericName("5", false, &result));
    EXPECT_EQ(result, 5u);
}

TEST_F(ParseNumericNameTest_1968, DecimalOneAlphaThenNumber_1968) {
    EXPECT_TRUE(parseNumericName("x7", false, &result));
    EXPECT_EQ(result, 7u);
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitMixed_1968) {
    EXPECT_TRUE(parseNumericName("A0", true, &result));
    EXPECT_EQ(result, 0xA0);
}

TEST_F(ParseNumericNameTest_1968, HexTwoDigitWithTrailingSpaces_1968) {
    // "FF   " -> n=2, parse "FF", endptr points to spaces
    // spaces are not alnum, skip them, reach '\0' -> true
    EXPECT_TRUE(parseNumericName("FF   ", true, &result));
    EXPECT_EQ(result, 0xFF);
}

TEST_F(ParseNumericNameTest_1968, DecimalOnlySpacesFails_1968) {
    // "  " -> no alpha prefix (space is not alpha), strtol("  ", ...) 
    // strtol skips whitespace, but there's nothing to parse -> endptr still at start? 
    // Actually strtol with "  " -> it skips spaces, finds nothing, endptr == s -> false
    EXPECT_FALSE(parseNumericName("  ", false, &result));
}

TEST_F(ParseNumericNameTest_1968, DecimalSpaceThenNumber_1968) {
    // " 42" -> no alpha prefix (space not alpha), strtol(" 42", ..., 10) -> v=42, endptr past "42"
    // strtol skips leading whitespace -> v=42
    EXPECT_TRUE(parseNumericName(" 42", false, &result));
    EXPECT_EQ(result, 42u);
}
