#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

// Since IsValidCaptureName is a static function in parse.cc, we cannot directly
// call it from outside the translation unit. However, we can test it indirectly
// through the RE2 parsing interface, since capture group names are validated
// during regex parsing.
//
// The pattern (?P<name>...) uses IsValidCaptureName to validate the capture name.

namespace {

class IsValidCaptureNameTest_532 : public ::testing::Test {
protected:
    bool IsValidCaptureName(const std::string& name) {
        // We test IsValidCaptureName indirectly by attempting to parse a regex
        // with a named capture group. If the name is valid, parsing succeeds.
        // If invalid, parsing fails.
        std::string pattern = "(?P<" + name + ">.)";
        re2::RE2 re(pattern);
        return re.ok();
    }
};

// Normal operation: simple ASCII letter names
TEST_F(IsValidCaptureNameTest_532, SimpleAlphaName_532) {
    EXPECT_TRUE(IsValidCaptureName("abc"));
}

TEST_F(IsValidCaptureNameTest_532, SingleLetter_532) {
    EXPECT_TRUE(IsValidCaptureName("a"));
}

TEST_F(IsValidCaptureNameTest_532, SingleUppercaseLetter_532) {
    EXPECT_TRUE(IsValidCaptureName("A"));
}

TEST_F(IsValidCaptureNameTest_532, MixedCaseLetters_532) {
    EXPECT_TRUE(IsValidCaptureName("AbCdEf"));
}

TEST_F(IsValidCaptureNameTest_532, LettersWithDigits_532) {
    // Digits (Nd category) should be allowed in capture names
    EXPECT_TRUE(IsValidCaptureName("abc123"));
}

TEST_F(IsValidCaptureNameTest_532, NameStartingWithDigit_532) {
    // Digits are in Nd category, which is included, so starting with digit should be valid
    EXPECT_TRUE(IsValidCaptureName("1abc"));
}

TEST_F(IsValidCaptureNameTest_532, AllDigits_532) {
    EXPECT_TRUE(IsValidCaptureName("123"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithUnderscore_532) {
    // Underscore (U+005F) is in the Pc (Connector_Punctuation) category
    EXPECT_TRUE(IsValidCaptureName("foo_bar"));
}

TEST_F(IsValidCaptureNameTest_532, UnderscoreOnly_532) {
    EXPECT_TRUE(IsValidCaptureName("_"));
}

TEST_F(IsValidCaptureNameTest_532, LeadingUnderscore_532) {
    EXPECT_TRUE(IsValidCaptureName("_abc"));
}

// Boundary condition: empty name
TEST_F(IsValidCaptureNameTest_532, EmptyName_532) {
    // Empty name should be invalid. We test this differently since (?P<>.)
    // might fail for other reasons too, but the function should return false.
    // We can't easily test empty via RE2 pattern, but let's try.
    std::string pattern = "(?P<>.)";
    re2::RE2 re(pattern);
    EXPECT_FALSE(re.ok());
}

// Error cases: names with invalid characters
TEST_F(IsValidCaptureNameTest_532, NameWithSpace_532) {
    EXPECT_FALSE(IsValidCaptureName("foo bar"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithHyphen_532) {
    EXPECT_FALSE(IsValidCaptureName("foo-bar"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithDot_532) {
    EXPECT_FALSE(IsValidCaptureName("foo.bar"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithExclamation_532) {
    EXPECT_FALSE(IsValidCaptureName("foo!"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithAtSign_532) {
    EXPECT_FALSE(IsValidCaptureName("foo@bar"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithHash_532) {
    EXPECT_FALSE(IsValidCaptureName("#foo"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithPlus_532) {
    EXPECT_FALSE(IsValidCaptureName("foo+bar"));
}

// Unicode letter names (Lu, Ll, Lt, Lm, Lo categories)
TEST_F(IsValidCaptureNameTest_532, UnicodeLetterGreek_532) {
    // Greek letters are in Lu/Ll categories
    EXPECT_TRUE(IsValidCaptureName("αβγ"));
}

TEST_F(IsValidCaptureNameTest_532, UnicodeCyrillic_532) {
    EXPECT_TRUE(IsValidCaptureName("привет"));
}

TEST_F(IsValidCaptureNameTest_532, UnicodeChineseCharacters_532) {
    // CJK characters are in Lo category
    EXPECT_TRUE(IsValidCaptureName("名前"));
}

TEST_F(IsValidCaptureNameTest_532, MixedAsciiAndUnicode_532) {
    EXPECT_TRUE(IsValidCaptureName("name名前"));
}

// Test with Nl (Letter_Number) category - e.g., Roman numerals
TEST_F(IsValidCaptureNameTest_532, RomanNumerals_532) {
    // U+2160 = Ⅰ (Roman numeral one) is in Nl category
    EXPECT_TRUE(IsValidCaptureName("Ⅰ"));
}

// Test Pc category characters other than underscore
TEST_F(IsValidCaptureNameTest_532, ConnectorPunctuation_532) {
    // U+203F = ‿ (undertie) is in Pc category
    EXPECT_TRUE(IsValidCaptureName("a‿b"));
}

// Combining marks (Mn, Mc categories)
TEST_F(IsValidCaptureNameTest_532, CombiningMark_532) {
    // U+0300 = combining grave accent (Mn category)
    // It should be valid as part of a name
    std::string name = "a\xCC\x80"; // 'a' + U+0300
    EXPECT_TRUE(IsValidCaptureName(name));
}

// Invalid: symbol characters
TEST_F(IsValidCaptureNameTest_532, NameWithDollarSign_532) {
    EXPECT_FALSE(IsValidCaptureName("$foo"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithPercent_532) {
    EXPECT_FALSE(IsValidCaptureName("foo%"));
}

// Long valid name
TEST_F(IsValidCaptureNameTest_532, LongValidName_532) {
    std::string longName(100, 'a');
    EXPECT_TRUE(IsValidCaptureName(longName));
}

// Name with only combining marks (Mn) - these are valid Unicode categories in the list
TEST_F(IsValidCaptureNameTest_532, OnlyCombiningMark_532) {
    // U+0300 = combining grave accent (Mn category)
    std::string name = "\xCC\x80"; // Just U+0300
    EXPECT_TRUE(IsValidCaptureName(name));
}

// Verify capture names work end-to-end with RE2
TEST_F(IsValidCaptureNameTest_532, CaptureGroupFunctional_532) {
    re2::RE2 re("(?P<word>\\w+)");
    ASSERT_TRUE(re.ok());
    std::string match;
    EXPECT_TRUE(RE2::FullMatch("hello", re, &match));
    EXPECT_EQ(match, "hello");
}

TEST_F(IsValidCaptureNameTest_532, UnicodeCaptureGroupFunctional_532) {
    re2::RE2 re("(?P<名前>\\w+)");
    ASSERT_TRUE(re.ok());
    std::string match;
    EXPECT_TRUE(RE2::FullMatch("hello", re, &match));
    EXPECT_EQ(match, "hello");
}

// Test with tab, newline - should be invalid
TEST_F(IsValidCaptureNameTest_532, NameWithTab_532) {
    EXPECT_FALSE(IsValidCaptureName("foo\tbar"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithNewline_532) {
    EXPECT_FALSE(IsValidCaptureName("foo\nbar"));
}

TEST_F(IsValidCaptureNameTest_532, NameWithNullByte_532) {
    std::string name("foo\0bar", 7);
    EXPECT_FALSE(IsValidCaptureName(name));
}

// Parentheses and angle brackets - should be invalid
TEST_F(IsValidCaptureNameTest_532, NameWithAngleBracket_532) {
    // This would break the pattern syntax, but the name validator should reject it
    // We can't easily test this via RE2 pattern as it confuses the parser
    // Just test with other special chars
    EXPECT_FALSE(IsValidCaptureName("foo(bar"));
}

}  // namespace
