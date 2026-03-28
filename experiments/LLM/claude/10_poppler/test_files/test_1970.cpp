#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// We need to include necessary headers
#include "poppler/GfxFont.h"
#include "poppler/GlobalParams.h"
#include "poppler/CharTypes.h"

// Since parseCharName is static in GfxFont.cc, we include the source
// or use a test-accessible declaration. For testing, we extern declare it.
// If the function is truly static, we may need to include the .cc file.
extern int parseCharName(char *charName, Unicode *uBuf, int uLen,
                         bool names, bool ligatures, bool numeric,
                         bool hex, bool variants);

class ParseCharNameTest_1970 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    Unicode uBuf[16];
};

// Test: Zero-length output buffer returns 0
TEST_F(ParseCharNameTest_1970, ZeroLengthOutputBuffer_1970) {
    char name[] = "A";
    int result = parseCharName(name, uBuf, 0, true, true, true, true, true);
    EXPECT_EQ(result, 0);
}

// Test: Negative output buffer length returns 0
TEST_F(ParseCharNameTest_1970, NegativeLengthOutputBuffer_1970) {
    char name[] = "A";
    int result = parseCharName(name, uBuf, -1, true, true, true, true, true);
    EXPECT_EQ(result, 0);
}

// Test: .notdef returns 0 when variants enabled
TEST_F(ParseCharNameTest_1970, NotdefVariant_1970) {
    char name[] = ".notdef";
    int result = parseCharName(name, uBuf, 16, true, true, true, true, true);
    EXPECT_EQ(result, 0);
}

// Test: Name starting with dot returns 0 with variants
TEST_F(ParseCharNameTest_1970, DotOnlyVariant_1970) {
    char name[] = ".something";
    int result = parseCharName(name, uBuf, 16, true, true, true, true, true);
    EXPECT_EQ(result, 0);
}

// Test: uni prefix with valid 4 hex digits
TEST_F(ParseCharNameTest_1970, UniPrefixSingleCodepoint_1970) {
    char name[] = "uni0041"; // 'A' = U+0041
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x0041);
}

// Test: uni prefix with two sets of 4 hex digits
TEST_F(ParseCharNameTest_1970, UniPrefixTwoCodepoints_1970) {
    char name[] = "uni00410042"; // U+0041 and U+0042
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(uBuf[0], 0x0041);
    EXPECT_EQ(uBuf[1], 0x0042);
}

// Test: uni prefix with surrogate range should be skipped
TEST_F(ParseCharNameTest_1970, UniPrefixSurrogateRange_1970) {
    char name[] = "uniD800"; // D800 is in surrogate range
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: uni prefix too short (less than 7 chars)
TEST_F(ParseCharNameTest_1970, UniPrefixTooShort_1970) {
    char name[] = "uni004"; // only 3 hex digits
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: uni prefix with wrong length (not multiple of 4 + 3)
TEST_F(ParseCharNameTest_1970, UniPrefixWrongLength_1970) {
    char name[] = "uni00411"; // length 8, (8-3)=5, not multiple of 4
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    // Length 8, n%4 = 8%4 = 0, not equal to 3, so uni path not taken
    // Then try u prefix: "uni00411" starts with 'u' but not exactly right format
    // n=8, charName[0]='u' but then we need n>=5 && n<=7, n=8 fails
    EXPECT_EQ(result, 0);
}

// Test: u prefix with 4 hex digits (u0041)
TEST_F(ParseCharNameTest_1970, UPrefixFourHexDigits_1970) {
    char name[] = "u0041";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x0041);
}

// Test: u prefix with 5 hex digits
TEST_F(ParseCharNameTest_1970, UPrefixFiveHexDigits_1970) {
    char name[] = "u10041";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x10041);
}

// Test: u prefix with 6 hex digits (max valid supplementary)
TEST_F(ParseCharNameTest_1970, UPrefixSixHexDigits_1970) {
    char name[] = "u10FFFF";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x10FFFF);
}

// Test: u prefix with surrogate value
TEST_F(ParseCharNameTest_1970, UPrefixSurrogate_1970) {
    char name[] = "uD800";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: u prefix value above 10FFFF
TEST_F(ParseCharNameTest_1970, UPrefixAboveMaxUnicode_1970) {
    char name[] = "u110000";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: u prefix with too many digits (8 chars total, n=8 > 7)
TEST_F(ParseCharNameTest_1970, UPrefixTooManyDigits_1970) {
    char name[] = "u1000000"; // 8 chars
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: u prefix with non-hex characters
TEST_F(ParseCharNameTest_1970, UPrefixNonHexChars_1970) {
    char name[] = "u00GG";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: Variant name with dot (e.g., "A.swash")
TEST_F(ParseCharNameTest_1970, VariantWithDot_1970) {
    char name[] = "uni0041.swash";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, true);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x0041);
}

// Test: Ligature with underscore
TEST_F(ParseCharNameTest_1970, LigatureWithUnderscore_1970) {
    char name[] = "uni0041_uni0042";
    int result = parseCharName(name, uBuf, 16, false, true, false, false, false);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(uBuf[0], 0x0041);
    EXPECT_EQ(uBuf[1], 0x0042);
}

// Test: Ligature disabled does not split on underscore
TEST_F(ParseCharNameTest_1970, LigatureDisabled_1970) {
    char name[] = "uni0041_uni0042";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    // Without ligature processing, the name "uni0041_uni0042" has length 15
    // n=15, n>=7? yes. n%4 = 15%4 = 3. So uni prefix path taken.
    // But the hex digits after "uni" include '_' which is not hex
    // uni0041 = first 4 hex chars OK (0041), then _uni = not valid hex
    // So partial result
    EXPECT_GE(result, 1);
    EXPECT_EQ(uBuf[0], 0x0041);
}

// Test: uni with E000 (private use area, valid)
TEST_F(ParseCharNameTest_1970, UniPrefixPrivateUseArea_1970) {
    char name[] = "uniE000";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0xE000);
}

// Test: uni with FFFF (valid)
TEST_F(ParseCharNameTest_1970, UniPrefixFFFF_1970) {
    char name[] = "uniFFFF";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0xFFFF);
}

// Test: uni with D7FF (boundary, valid)
TEST_F(ParseCharNameTest_1970, UniPrefixD7FF_1970) {
    char name[] = "uniD7FF";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0xD7FF);
}

// Test: uni with DFFF (surrogate, invalid)
TEST_F(ParseCharNameTest_1970, UniPrefixDFFF_1970) {
    char name[] = "uniDFFF";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: Empty char name
TEST_F(ParseCharNameTest_1970, EmptyCharName_1970) {
    char name[] = "";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: All flags disabled with unknown name
TEST_F(ParseCharNameTest_1970, AllFlagsDisabledUnknownName_1970) {
    char name[] = "randomname";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 0);
}

// Test: Output buffer of size 1 with multi-codepoint uni
TEST_F(ParseCharNameTest_1970, SmallBufferUniMultiple_1970) {
    char name[] = "uni00410042";
    int result = parseCharName(name, uBuf, 1, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x0041);
}

// Test: Ligature with empty component between underscores
TEST_F(ParseCharNameTest_1970, LigatureEmptyComponent_1970) {
    char name[] = "uni0041__uni0042";
    int result = parseCharName(name, uBuf, 16, false, true, false, false, false);
    // The empty component between underscores should be skipped
    EXPECT_EQ(result, 2);
    EXPECT_EQ(uBuf[0], 0x0041);
    EXPECT_EQ(uBuf[1], 0x0042);
}

// Test: u prefix with exactly E000 (boundary in private use)
TEST_F(ParseCharNameTest_1970, UPrefixE000_1970) {
    char name[] = "uE000";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0xE000);
}

// Test: uni prefix with 0000
TEST_F(ParseCharNameTest_1970, UniPrefix0000_1970) {
    char name[] = "uni0000";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x0000);
}

// Test: Variant combined with ligature
TEST_F(ParseCharNameTest_1970, VariantAndLigature_1970) {
    char name[] = "uni0041_uni0042.alt";
    int result = parseCharName(name, uBuf, 16, false, true, false, false, true);
    // Variant processing first strips ".alt", then ligature processes "uni0041_uni0042"
    EXPECT_EQ(result, 2);
    EXPECT_EQ(uBuf[0], 0x0041);
    EXPECT_EQ(uBuf[1], 0x0042);
}

// Test: uni with lowercase hex
TEST_F(ParseCharNameTest_1970, UniPrefixLowercaseHex_1970) {
    char name[] = "uni00ff";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x00FF);
}

// Test: uni with mixed case hex
TEST_F(ParseCharNameTest_1970, UniPrefixMixedCaseHex_1970) {
    char name[] = "uni00Ff";
    int result = parseCharName(name, uBuf, 16, false, false, false, false, false);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uBuf[0], 0x00FF);
}
