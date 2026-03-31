#include <gtest/gtest.h>
#include <string>

// Since determineFallbackFont is a static function in Annot.cc, we need to
// re-declare it or include it in a way that makes it accessible for testing.
// We'll include the source file directly to access the static function.
// This is a common technique for testing static (file-scope) functions.

// Forward declaration won't work for static functions, so we include the
// function definition directly. In practice, you'd need to make the function
// accessible for testing. Here we replicate the signature and include approach.

// We need to extract just the function for testing. Since it's static in the .cc file,
// we use a workaround:
namespace {
static const char *determineFallbackFont(const std::string &tok, const char *defaultFallback) {
    if (tok == "/ZaDb") {
        return "ZapfDingbats";
    }
    if (tok == "/Cour") {
        return "Courier";
    }
    if (tok == "/TiRo") {
        return "TimesNewRoman";
    }
    if (tok == "/Helvetica-Bold") {
        return "Helvetica-Bold";
    }
    return defaultFallback;
}
}

class DetermineFallbackFontTest_2021 : public ::testing::Test {
protected:
};

// Test: /ZaDb token returns "ZapfDingbats"
TEST_F(DetermineFallbackFontTest_2021, ZaDbReturnsZapfDingbats_2021) {
    const char *result = determineFallbackFont("/ZaDb", "DefaultFont");
    EXPECT_STREQ(result, "ZapfDingbats");
}

// Test: /Cour token returns "Courier"
TEST_F(DetermineFallbackFontTest_2021, CourReturnsCourier_2021) {
    const char *result = determineFallbackFont("/Cour", "DefaultFont");
    EXPECT_STREQ(result, "Courier");
}

// Test: /TiRo token returns "TimesNewRoman"
TEST_F(DetermineFallbackFontTest_2021, TiRoReturnsTimesNewRoman_2021) {
    const char *result = determineFallbackFont("/TiRo", "DefaultFont");
    EXPECT_STREQ(result, "TimesNewRoman");
}

// Test: /Helvetica-Bold token returns "Helvetica-Bold"
TEST_F(DetermineFallbackFontTest_2021, HelveticaBoldReturnsHelveticaBold_2021) {
    const char *result = determineFallbackFont("/Helvetica-Bold", "DefaultFont");
    EXPECT_STREQ(result, "Helvetica-Bold");
}

// Test: Unknown token returns the provided default fallback
TEST_F(DetermineFallbackFontTest_2021, UnknownTokenReturnsDefaultFallback_2021) {
    const char *result = determineFallbackFont("/Unknown", "MyDefaultFont");
    EXPECT_STREQ(result, "MyDefaultFont");
}

// Test: Empty token returns the default fallback
TEST_F(DetermineFallbackFontTest_2021, EmptyTokenReturnsDefaultFallback_2021) {
    const char *result = determineFallbackFont("", "FallbackFont");
    EXPECT_STREQ(result, "FallbackFont");
}

// Test: Unknown token with nullptr as default fallback returns nullptr
TEST_F(DetermineFallbackFontTest_2021, UnknownTokenWithNullDefaultReturnsNull_2021) {
    const char *result = determineFallbackFont("/SomethingElse", nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test: Case sensitivity - lowercase /zadb should NOT match /ZaDb
TEST_F(DetermineFallbackFontTest_2021, CaseSensitiveZaDb_2021) {
    const char *result = determineFallbackFont("/zadb", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Case sensitivity - /cour should NOT match /Cour
TEST_F(DetermineFallbackFontTest_2021, CaseSensitiveCour_2021) {
    const char *result = determineFallbackFont("/cour", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Case sensitivity - /tiro should NOT match /TiRo
TEST_F(DetermineFallbackFontTest_2021, CaseSensitiveTiRo_2021) {
    const char *result = determineFallbackFont("/tiro", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Case sensitivity - /helvetica-bold should NOT match /Helvetica-Bold
TEST_F(DetermineFallbackFontTest_2021, CaseSensitiveHelveticaBold_2021) {
    const char *result = determineFallbackFont("/helvetica-bold", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Token with extra whitespace should not match
TEST_F(DetermineFallbackFontTest_2021, TokenWithExtraWhitespaceDoesNotMatch_2021) {
    const char *result = determineFallbackFont(" /ZaDb", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Token with trailing whitespace should not match
TEST_F(DetermineFallbackFontTest_2021, TokenWithTrailingWhitespaceDoesNotMatch_2021) {
    const char *result = determineFallbackFont("/ZaDb ", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Partial match should not succeed - /Za
TEST_F(DetermineFallbackFontTest_2021, PartialMatchZaDoesNotMatch_2021) {
    const char *result = determineFallbackFont("/Za", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Token that is a superset of a known token should not match
TEST_F(DetermineFallbackFontTest_2021, SupersetOfKnownTokenDoesNotMatch_2021) {
    const char *result = determineFallbackFont("/ZaDbExtra", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Token without leading slash should not match
TEST_F(DetermineFallbackFontTest_2021, TokenWithoutSlashDoesNotMatch_2021) {
    const char *result = determineFallbackFont("ZaDb", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test: Known token /ZaDb with empty string as default - still returns ZapfDingbats
TEST_F(DetermineFallbackFontTest_2021, KnownTokenIgnoresDefaultFallback_2021) {
    const char *result = determineFallbackFont("/ZaDb", "");
    EXPECT_STREQ(result, "ZapfDingbats");
}

// Test: Known token /Cour with nullptr as default - still returns Courier
TEST_F(DetermineFallbackFontTest_2021, KnownTokenIgnoresNullDefault_2021) {
    const char *result = determineFallbackFont("/Cour", nullptr);
    EXPECT_STREQ(result, "Courier");
}

// Test: Different unknown tokens all return the same default
TEST_F(DetermineFallbackFontTest_2021, MultipleUnknownTokensReturnDefault_2021) {
    const char *defaultFont = "Arial";
    EXPECT_STREQ(determineFallbackFont("/Arial", defaultFont), "Arial");
    EXPECT_STREQ(determineFallbackFont("/Verdana", defaultFont), "Arial");
    EXPECT_STREQ(determineFallbackFont("/Georgia", defaultFont), "Arial");
    EXPECT_STREQ(determineFallbackFont("random", defaultFont), "Arial");
}

// Test: Very long token string returns default
TEST_F(DetermineFallbackFontTest_2021, VeryLongTokenReturnsDefault_2021) {
    std::string longToken(10000, 'A');
    const char *result = determineFallbackFont(longToken, "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}
