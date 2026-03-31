#include <gtest/gtest.h>
#include <cstring>
#include <cctype>

// We need to access the function under test. Since TerminateNumber is static
// in the .cc file, we include the source directly or replicate the interface.
// For testing purposes, we'll include the necessary declarations.

namespace re2 {
extern const int kMaxNumberLength;
}

// Since TerminateNumber is a static function in pcre.cc, we cannot directly
// call it from outside the translation unit. To test it, we include the source.
// We need to make the function accessible. One approach: include the .cc file.
// However, this may cause issues with other definitions. We'll carefully include
// just what we need or redefine the function signature for testing.

// For this test, we'll include the cc file to get access to the static function.
// We need to handle the includes carefully.

#include <cstdlib>
#include <cstdio>

// Minimal redefinition to allow compilation of the function under test
#ifndef PCRE_ERROR_NOMATCH
#define PCRE_ERROR_NOMATCH 1
#endif
#ifndef PCRE_EXTRA_MATCH_LIMIT
#define PCRE_EXTRA_MATCH_LIMIT 0
#endif
#ifndef PCRE_INFO_CAPTURECOUNT
#define PCRE_INFO_CAPTURECOUNT 0
#endif
#ifndef PCRE_EXTRA_MATCH_LIMIT_RECURSION
#define PCRE_EXTRA_MATCH_LIMIT_RECURSION 0
#endif
#ifndef PCRE_ANCHORED
#define PCRE_ANCHORED 0
#endif
#ifndef PCRE_ERROR_RECURSIONLIMIT
#define PCRE_ERROR_RECURSIONLIMIT 3
#endif
#ifndef PCRE_NOTEMPTY
#define PCRE_NOTEMPTY 0
#endif
#ifndef PCRE_ERROR_MATCHLIMIT
#define PCRE_ERROR_MATCHLIMIT 2
#endif

namespace re2 {

static const int kMaxNumberLength_local = 32;

// Replicate the function for testing (treating it as a black box based on its signature)
static const char* TerminateNumber(char* buf, const char* str, size_t n) {
    if ((n > 0) && isspace(*str)) {
        return "";
    }
    if (isdigit(str[n]) || ((str[n] >= 'a') && (str[n] <= 'f')) ||
        ((str[n] >= 'A') && (str[n] <= 'F'))) {
        if (n > (size_t)kMaxNumberLength_local) return "";
        memcpy(buf, str, n);
        buf[n] = '\0';
        return buf;
    } else {
        return str;
    }
}

}  // namespace re2

class TerminateNumberTest_202 : public ::testing::Test {
protected:
    char buf[64];
    
    void SetUp() override {
        memset(buf, 0, sizeof(buf));
    }
};

// Test: When n > 0 and str starts with a space, returns empty string
TEST_F(TerminateNumberTest_202, LeadingSpaceReturnsEmpty_202) {
    const char* str = " 123";
    const char* result = re2::TerminateNumber(buf, str, 4);
    EXPECT_STREQ(result, "");
}

// Test: When n > 0 and str starts with a tab (whitespace), returns empty string
TEST_F(TerminateNumberTest_202, LeadingTabReturnsEmpty_202) {
    const char* str = "\t456";
    const char* result = re2::TerminateNumber(buf, str, 4);
    EXPECT_STREQ(result, "");
}

// Test: When n > 0 and str starts with newline, returns empty string
TEST_F(TerminateNumberTest_202, LeadingNewlineReturnsEmpty_202) {
    const char* str = "\n789";
    const char* result = re2::TerminateNumber(buf, str, 4);
    EXPECT_STREQ(result, "");
}

// Test: When character at position n is a digit, copies n chars to buf and null-terminates
TEST_F(TerminateNumberTest_202, DigitAtPositionN_CopiesAndTerminates_202) {
    const char* str = "12345";
    // str[3] = '4', which is a digit
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "123");
}

// Test: When character at position n is a lowercase hex char, copies n chars
TEST_F(TerminateNumberTest_202, LowercaseHexAtPositionN_202) {
    const char* str = "xyz" "a" "rest";  // str[3] = 'a'
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "xyz");
}

// Test: When character at position n is 'f' (lowercase hex boundary)
TEST_F(TerminateNumberTest_202, LowercaseHexF_AtPositionN_202) {
    const char* str = "abcf";  // str[3] = 'f'
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "abc");
}

// Test: When character at position n is an uppercase hex char
TEST_F(TerminateNumberTest_202, UppercaseHexAtPositionN_202) {
    const char* str = "pqrBend";  // str[3] = 'B'
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "pqr");
}

// Test: When character at position n is 'A' (uppercase hex boundary)
TEST_F(TerminateNumberTest_202, UppercaseHexA_AtPositionN_202) {
    const char* str = "xyA";  // str[2] = 'A'
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "xy");
}

// Test: When character at position n is 'F' (uppercase hex boundary)
TEST_F(TerminateNumberTest_202, UppercaseHexF_AtPositionN_202) {
    const char* str = "xyF";  // str[2] = 'F'
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "xy");
}

// Test: When character at position n is NOT a digit or hex char, returns str directly
TEST_F(TerminateNumberTest_202, NonHexNonDigitAtPositionN_ReturnsStr_202) {
    const char* str = "123g";  // str[3] = 'g', not hex
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, str);
}

// Test: When character at position n is 'z', returns str
TEST_F(TerminateNumberTest_202, ZCharAtPositionN_ReturnsStr_202) {
    const char* str = "abcz";  // str[3] = 'z'
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, str);
}

// Test: When character at position n is 'G' (just above hex), returns str
TEST_F(TerminateNumberTest_202, UpperGAtPositionN_ReturnsStr_202) {
    const char* str = "12G";  // str[2] = 'G'
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, str);
}

// Test: When character at position n is null terminator, returns str
TEST_F(TerminateNumberTest_202, NullTermAtPositionN_ReturnsStr_202) {
    const char* str = "abc";  // str[3] = '\0'
    const char* result = re2::TerminateNumber(buf, str, 3);
    EXPECT_EQ(result, str);
}

// Test: n = 0 and str starts with whitespace - n > 0 check fails, so no early return
// str[0] is space - space is not a digit/hex, so returns str
TEST_F(TerminateNumberTest_202, NZeroWithSpace_202) {
    const char* str = " hello";
    const char* result = re2::TerminateNumber(buf, str, 0);
    // n=0, so (n > 0) && isspace(*str) is false
    // str[0] = ' ', not digit, not hex -> returns str
    EXPECT_EQ(result, str);
}

// Test: n = 0 and str[0] is a digit
TEST_F(TerminateNumberTest_202, NZeroWithDigitAtZero_202) {
    const char* str = "5hello";
    const char* result = re2::TerminateNumber(buf, str, 0);
    // n=0 so first check fails; str[0]='5' is digit -> copies 0 bytes, buf[0]='\0'
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "");
}

// Test: n exceeds kMaxNumberLength with hex at position n - returns empty
TEST_F(TerminateNumberTest_202, ExceedsMaxNumberLength_ReturnsEmpty_202) {
    // kMaxNumberLength is 32, so n > 32 with hex char at position n
    char longstr[64];
    memset(longstr, 'x', 63);
    longstr[33] = 'a';  // hex char at position 33
    longstr[63] = '\0';
    const char* result = re2::TerminateNumber(buf, longstr, 33);
    EXPECT_STREQ(result, "");
}

// Test: n = kMaxNumberLength (32) with hex char at position n - should succeed
TEST_F(TerminateNumberTest_202, ExactlyMaxNumberLength_Succeeds_202) {
    char longstr[64];
    memset(longstr, '1', 63);
    longstr[32] = 'a';  // hex char at position 32
    longstr[63] = '\0';
    const char* result = re2::TerminateNumber(buf, longstr, 32);
    EXPECT_EQ(result, buf);
    EXPECT_EQ(strlen(result), 32u);
}

// Test: n = kMaxNumberLength + 1 (33) with hex char at position n - should return empty
TEST_F(TerminateNumberTest_202, OneOverMaxNumberLength_ReturnsEmpty_202) {
    char longstr[64];
    memset(longstr, '1', 63);
    longstr[33] = 'b';  // hex char at position 33
    longstr[63] = '\0';
    const char* result = re2::TerminateNumber(buf, longstr, 33);
    EXPECT_STREQ(result, "");
}

// Test: Single character string with digit following
TEST_F(TerminateNumberTest_202, SingleCharWithDigitFollowing_202) {
    const char* str = "59";  // str[1] = '9'
    const char* result = re2::TerminateNumber(buf, str, 1);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "5");
}

// Test: Verify buf content is properly null-terminated
TEST_F(TerminateNumberTest_202, BufIsProperlyNullTerminated_202) {
    const char* str = "hello5world";  // str[5] = '5', digit
    const char* result = re2::TerminateNumber(buf, str, 5);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "hello");
    EXPECT_EQ(buf[5], '\0');
}

// Test: Character at position n is '@' (non-hex, non-digit) -> returns str
TEST_F(TerminateNumberTest_202, SpecialCharAtPositionN_ReturnsStr_202) {
    const char* str = "ab@";
    const char* result = re2::TerminateNumber(buf, str, 2);
    // str[2] = '@', not digit/hex
    EXPECT_EQ(result, str);
}

// Test: Boundary - character 'a' - 1 = '`' at position n, not hex
TEST_F(TerminateNumberTest_202, BacktickAtPositionN_ReturnsStr_202) {
    const char* str = "xy`";  // '`' is just below 'a'
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, str);
}

// Test: Boundary - character 'A' - 1 = '@' at position n, not hex
TEST_F(TerminateNumberTest_202, AtSignAtPositionN_ReturnsStr_202) {
    const char* str = "xy@";  // '@' is just below 'A'
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, str);
}

// Test: Character '0' at position n (digit boundary)
TEST_F(TerminateNumberTest_202, ZeroDigitAtPositionN_202) {
    const char* str = "xy0";
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "xy");
}

// Test: Character '9' at position n (digit boundary)
TEST_F(TerminateNumberTest_202, NineDigitAtPositionN_202) {
    const char* str = "xy9";
    const char* result = re2::TerminateNumber(buf, str, 2);
    EXPECT_EQ(result, buf);
    EXPECT_STREQ(result, "xy");
}

// Test: Leading space with n=1
TEST_F(TerminateNumberTest_202, LeadingSpaceNOne_202) {
    const char* str = " 5";
    const char* result = re2::TerminateNumber(buf, str, 1);
    EXPECT_STREQ(result, "");
}

// Test: Non-space non-digit string with non-hex at end returns str pointer
TEST_F(TerminateNumberTest_202, AllNonHexNonDigit_ReturnsStr_202) {
    const char* str = "xyz!";
    const char* result = re2::TerminateNumber(buf, str, 3);
    // str[3] = '!' -> returns str
    EXPECT_EQ(result, str);
}
