#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// We need to define the required types and constants before including the implementation
#ifndef XMP_Uns8
#define XMP_Uns8 uint8_t
#endif

#ifndef XMP_Assert
#define XMP_Assert(x) ((void)0)
#endif

// Define the constants that the function uses
static const XMP_Uns8 kTab = 0x09;
static const XMP_Uns8 kLF  = 0x0A;
static const XMP_Uns8 kCR  = 0x0D;

// Include the static function by copying it here for testing purposes
// Since it's a static function in a .cpp file, we reproduce it for testing
static int CountControlEscape(const XMP_Uns8* escStart, const XMP_Uns8* bufEnd) {
    if (escStart >= bufEnd) return 0;
    
    size_t tailLen = bufEnd - escStart;
    if (tailLen < 5) return -1;
    
    if (strncmp((char*)escStart, "&#x", 3) != 0) return 0;
    
    XMP_Uns8 escValue = 0;
    const XMP_Uns8* escPos = escStart + 3;
    
    if (('0' <= *escPos) && (*escPos <= '9')) {
        escValue = *escPos - '0'; ++escPos;
    } else if (('A' <= *escPos) && (*escPos <= 'F')) {
        escValue = *escPos - 'A' + 10; ++escPos;
    } else if (('a' <= *escPos) && (*escPos <= 'f')) {
        escValue = *escPos - 'a' + 10; ++escPos;
    }
    
    if (('0' <= *escPos) && (*escPos <= '9')) {
        escValue = (escValue << 4) + (*escPos - '0'); ++escPos;
    } else if (('A' <= *escPos) && (*escPos <= 'F')) {
        escValue = (escValue << 4) + (*escPos - 'A' + 10); ++escPos;
    } else if (('a' <= *escPos) && (*escPos <= 'f')) {
        escValue = (escValue << 4) + (*escPos - 'a' + 10); ++escPos;
    }
    
    if (escPos == bufEnd) return -1;
    if (*escPos != ';') return 0;
    
    size_t escLen = escPos - escStart + 1;
    if (escLen < 5) return 0;
    
    if ((escValue == kTab) || (escValue == kLF) || (escValue == kCR)) return 0;
    
    return (int)escLen;
}

class CountControlEscapeTest_1972 : public ::testing::Test {
protected:
    // Helper to call the function with a string
    int callWithString(const char* str) {
        const XMP_Uns8* start = reinterpret_cast<const XMP_Uns8*>(str);
        const XMP_Uns8* end = start + strlen(str);
        return CountControlEscape(start, end);
    }
    
    int callWithStringAndLen(const char* str, size_t len) {
        const XMP_Uns8* start = reinterpret_cast<const XMP_Uns8*>(str);
        const XMP_Uns8* end = start + len;
        return CountControlEscape(start, end);
    }
};

// Test: escStart >= bufEnd returns 0
TEST_F(CountControlEscapeTest_1972, StartEqualToEndReturnsZero_1972) {
    const XMP_Uns8 buf[] = "&#x01;";
    EXPECT_EQ(0, CountControlEscape(buf, buf));
}

TEST_F(CountControlEscapeTest_1972, StartGreaterThanEndReturnsZero_1972) {
    const XMP_Uns8 buf[] = "&#x01;";
    EXPECT_EQ(0, CountControlEscape(buf + 2, buf));
}

// Test: tailLen < 5 returns -1 (partial escape)
TEST_F(CountControlEscapeTest_1972, TailLenLessThan5ReturnsNegOne_1972) {
    EXPECT_EQ(-1, callWithStringAndLen("&#x0", 4));
}

TEST_F(CountControlEscapeTest_1972, TailLenOf1ReturnsNegOne_1972) {
    EXPECT_EQ(-1, callWithStringAndLen("&", 1));
}

TEST_F(CountControlEscapeTest_1972, TailLenOf3ReturnsNegOne_1972) {
    EXPECT_EQ(-1, callWithStringAndLen("&#x", 3));
}

// Test: Not starting with &#x returns 0
TEST_F(CountControlEscapeTest_1972, NotStartingWithAmpHashXReturnsZero_1972) {
    EXPECT_EQ(0, callWithString("&abcd;"));
}

TEST_F(CountControlEscapeTest_1972, NotAmpersandStartReturnsZero_1972) {
    EXPECT_EQ(0, callWithString("Xbcde;"));
}

TEST_F(CountControlEscapeTest_1972, AmpHashButNoXReturnsZero_1972) {
    EXPECT_EQ(0, callWithString("&#012;"));
}

// Test: Prohibited control escape with single hex digit
TEST_F(CountControlEscapeTest_1972, ProhibitedSingleDigitEscape01_1972) {
    // &#x1; has escLen = 5, value = 0x01 (prohibited)
    EXPECT_EQ(5, callWithString("&#x1;"));
}

TEST_F(CountControlEscapeTest_1972, ProhibitedSingleDigitEscape02_1972) {
    // &#x2; value = 0x02 (prohibited)
    EXPECT_EQ(5, callWithString("&#x2;"));
}

// Test: Prohibited control escape with two hex digits
TEST_F(CountControlEscapeTest_1972, ProhibitedTwoDigitEscape01_1972) {
    // &#x01; has escLen = 6, value = 0x01 (prohibited)
    EXPECT_EQ(6, callWithString("&#x01;"));
}

TEST_F(CountControlEscapeTest_1972, ProhibitedTwoDigitEscapeHex1F_1972) {
    // &#x1F; value = 0x1F (prohibited)
    EXPECT_EQ(6, callWithString("&#x1F;"));
}

TEST_F(CountControlEscapeTest_1972, ProhibitedTwoDigitEscapeLowercaseHex_1972) {
    // &#x1f; value = 0x1f (prohibited)
    EXPECT_EQ(6, callWithString("&#x1f;"));
}

// Test: Allowed escapes (Tab=0x09, LF=0x0A, CR=0x0D) return 0
TEST_F(CountControlEscapeTest_1972, AllowedEscapeTabReturnsZero_1972) {
    // &#x09; = Tab
    EXPECT_EQ(0, callWithString("&#x09;"));
}

TEST_F(CountControlEscapeTest_1972, AllowedEscapeLFReturnsZero_1972) {
    // &#x0A; = LF
    EXPECT_EQ(0, callWithString("&#x0A;"));
}

TEST_F(CountControlEscapeTest_1972, AllowedEscapeLFLowercaseReturnsZero_1972) {
    // &#x0a; = LF
    EXPECT_EQ(0, callWithString("&#x0a;"));
}

TEST_F(CountControlEscapeTest_1972, AllowedEscapeCRReturnsZero_1972) {
    // &#x0D; = CR
    EXPECT_EQ(0, callWithString("&#x0D;"));
}

TEST_F(CountControlEscapeTest_1972, AllowedEscapeCRLowercaseReturnsZero_1972) {
    // &#x0d; = CR
    EXPECT_EQ(0, callWithString("&#x0d;"));
}

TEST_F(CountControlEscapeTest_1972, AllowedEscapeTabSingleDigitReturnsZero_1972) {
    // &#x9; = Tab
    EXPECT_EQ(0, callWithString("&#x9;"));
}

// Test: Partial escape (escPos == bufEnd) returns -1
TEST_F(CountControlEscapeTest_1972, PartialEscapeNoSemicolonReturnsNegOne_1972) {
    // "&#x01" with length 5, no semicolon and escPos reaches bufEnd
    EXPECT_EQ(-1, callWithStringAndLen("&#x01", 5));
}

TEST_F(CountControlEscapeTest_1972, PartialEscapeSingleHexDigitReturnsNegOne_1972) {
    // "&#x0" with length 4 → tailLen < 5 → -1
    EXPECT_EQ(-1, callWithStringAndLen("&#x0", 4));
}

// Test: No semicolon at expected position returns 0
TEST_F(CountControlEscapeTest_1972, NoSemicolonAfterHexReturnsZero_1972) {
    // "&#x01X" - no semicolon
    EXPECT_EQ(0, callWithString("&#x01X"));
}

// Test: &#x; is too short (escLen < 5), returns 0
TEST_F(CountControlEscapeTest_1972, EscLenLessThan5CatchesEmptyHex_1972) {
    // "&#x;" has escLen = 4 < 5
    // But wait, after &#x, escPos points to ';', no hex digits parsed
    // escPos = escStart + 3 = pointing to ';'
    // *escPos = ';' which is not a hex digit, so escValue stays 0
    // Then check *escPos == ';' -> yes, escLen = 4
    // escLen < 5 -> return 0
    EXPECT_EQ(0, callWithString("&#x;Z"));
}

// Test: Non-hex character after &#x
TEST_F(CountControlEscapeTest_1972, NonHexAfterPrefixThenSemicolon_1972) {
    // "&#xG;" - 'G' is not hex, escPos stays at position 3
    // escPos still points to 'G', then check second hex: 'G' not hex
    // then check escPos == bufEnd? No
    // *escPos = 'G' != ';' -> return 0
    EXPECT_EQ(0, callWithString("&#xG;"));
}

// Test: uppercase hex digits
TEST_F(CountControlEscapeTest_1972, UppercaseHexDigits_1972) {
    // &#x0B; = value 0x0B (prohibited, not tab/lf/cr)
    EXPECT_EQ(6, callWithString("&#x0B;"));
}

// Test: mixed case hex digits
TEST_F(CountControlEscapeTest_1972, MixedCaseHexDigits_1972) {
    // &#xFf; = value 0xFF (prohibited)
    EXPECT_EQ(6, callWithString("&#xFf;"));
}

TEST_F(CountControlEscapeTest_1972, MixedCaseHexDigitsReverse_1972) {
    // &#xfF; = value 0xFF (prohibited)
    EXPECT_EQ(6, callWithString("&#xfF;"));
}

// Test: Value 0x00 is prohibited
TEST_F(CountControlEscapeTest_1972, NullValueProhibited_1972) {
    // &#x00; = value 0x00
    EXPECT_EQ(6, callWithString("&#x00;"));
}

// Test: Extra content after the escape doesn't affect result
TEST_F(CountControlEscapeTest_1972, ExtraContentAfterEscape_1972) {
    EXPECT_EQ(6, callWithString("&#x01;extra data"));
}

// Test: Only processes first escape
TEST_F(CountControlEscapeTest_1972, OnlyProcessesFirstEscape_1972) {
    EXPECT_EQ(6, callWithString("&#x01;&#x02;"));
}

// Test: Single hex digit values
TEST_F(CountControlEscapeTest_1972, SingleHexA_1972) {
    // &#xA; = 0x0A = LF (allowed)
    EXPECT_EQ(0, callWithString("&#xA;"));
}

TEST_F(CountControlEscapeTest_1972, SingleHexD_1972) {
    // &#xD; = 0x0D = CR (allowed)
    EXPECT_EQ(0, callWithString("&#xD;"));
}

TEST_F(CountControlEscapeTest_1972, SingleHexB_1972) {
    // &#xB; = 0x0B (prohibited)
    EXPECT_EQ(5, callWithString("&#xB;"));
}

TEST_F(CountControlEscapeTest_1972, SingleHexF_1972) {
    // &#xF; = 0x0F (prohibited)
    EXPECT_EQ(5, callWithString("&#xF;"));
}

// Test: Exactly 5 bytes total (minimum for a valid escape &#xH;)
TEST_F(CountControlEscapeTest_1972, ExactlyFiveBytesValidEscape_1972) {
    EXPECT_EQ(5, callWithString("&#x1;"));
}

// Test: Partial escape with exactly tailLen = 5 but no semicolon yet
TEST_F(CountControlEscapeTest_1972, FiveBytesPartialTwoDigitEscape_1972) {
    // "&#x01" tailLen = 5, two hex digits parsed, escPos = 5 = bufEnd -> return -1
    EXPECT_EQ(-1, callWithStringAndLen("&#x01", 5));
}

// Test: Value 0x08 (backspace) is prohibited
TEST_F(CountControlEscapeTest_1972, BackspaceProhibited_1972) {
    EXPECT_EQ(6, callWithString("&#x08;"));
}

// Test: Value 0x0E is prohibited  
TEST_F(CountControlEscapeTest_1972, Value0EProhibited_1972) {
    EXPECT_EQ(6, callWithString("&#x0E;"));
}

// Test: Value 0x7F (DEL) is prohibited
TEST_F(CountControlEscapeTest_1972, DELProhibited_1972) {
    EXPECT_EQ(6, callWithString("&#x7F;"));
}
