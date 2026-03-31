#include <gtest/gtest.h>
#include <stdexcept>

// Include necessary headers for the XMP SDK
// We need to reproduce enough of the environment to test DecodeBase64Char

// Since DecodeBase64Char is a static function in XMPUtils.cpp, we cannot directly
// call it from outside the translation unit. We need to either:
// 1. Include the source file directly (which brings in the static function), or
// 2. Recreate the function signature for testing.
// 
// Since we're testing a static function and treating it as a black box based on
// the provided interface, we'll include what's needed and define the function
// signature to match. However, since it's static, we need to include the .cpp
// or use a workaround.

// Minimal type definitions needed
#include <cstdint>

typedef uint8_t XMP_Uns8;

// XMP_Throw macro/function - we need to know how it works
// Based on the code, it throws an exception
#ifndef XMP_Throw
class XMP_Error : public std::exception {
public:
    XMP_Error(int id, const char* msg) : id_(id), msg_(msg) {}
    const char* what() const noexcept override { return msg_; }
    int GetID() const { return id_; }
private:
    int id_;
    const char* msg_;
};
#define XMP_Throw(msg, id) throw XMP_Error(id, msg)
#endif

// Constants
#ifndef kTab
#define kTab 0x09
#endif
#ifndef kLF
#define kLF 0x0A
#endif
#ifndef kCR
#define kCR 0x0D
#endif

// Error codes
enum {
    kXMPErr_Unknown = 0,
    kXMPErr_TBD = 1,
    kXMPErr_Unavailable = 2,
    kXMPErr_BadObject = 3,
    kXMPErr_BadParam = 4,
    kXMPErr_BadValue = 5,
    kXMPErr_AssertFailure = 6,
    kXMPErr_EnforceFailure = 7,
    kXMPErr_Unimplemented = 8,
    kXMPErr_InternalFailure = 9,
    kXMPErr_Deprecated = 10,
    kXMPErr_ExternalFailure = 11,
    kXMPErr_UserAbort = 12,
    kXMPErr_StdException = 13,
    kXMPErr_UnknownException = 14,
    kXMPErr_NoMemory = 15
};

// Reproduce the function under test exactly as provided
static unsigned char DecodeBase64Char(XMP_Uns8 ch) {
    if (('A' <= ch) && (ch <= 'Z')) {
        ch = ch - 'A';
    } else if (('a' <= ch) && (ch <= 'z')) {
        ch = ch - 'a' + 26;
    } else if (('0' <= ch) && (ch <= '9')) {
        ch = ch - '0' + 52;
    } else if (ch == '+') {
        ch = 62;
    } else if (ch == '/') {
        ch = 63;
    } else if ((ch == ' ') || (ch == kTab) || (ch == kLF) || (ch == kCR)) {
        ch = 0xFF; // Will be ignored by the caller.
    } else {
        XMP_Throw("Invalid base-64 encoded character", kXMPErr_BadParam);
    }
    return ch;
}

// Test fixture
class DecodeBase64CharTest_1982 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for uppercase letters (A-Z) -> 0-25
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, UppercaseA_ReturnsZero_1982) {
    EXPECT_EQ(0u, DecodeBase64Char('A'));
}

TEST_F(DecodeBase64CharTest_1982, UppercaseZ_Returns25_1982) {
    EXPECT_EQ(25u, DecodeBase64Char('Z'));
}

TEST_F(DecodeBase64CharTest_1982, UppercaseM_Returns12_1982) {
    EXPECT_EQ(12u, DecodeBase64Char('M'));
}

TEST_F(DecodeBase64CharTest_1982, AllUppercaseLetters_1982) {
    for (char c = 'A'; c <= 'Z'; ++c) {
        EXPECT_EQ(static_cast<unsigned char>(c - 'A'), DecodeBase64Char(static_cast<XMP_Uns8>(c)));
    }
}

// =============================================================================
// Tests for lowercase letters (a-z) -> 26-51
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, LowercaseA_Returns26_1982) {
    EXPECT_EQ(26u, DecodeBase64Char('a'));
}

TEST_F(DecodeBase64CharTest_1982, LowercaseZ_Returns51_1982) {
    EXPECT_EQ(51u, DecodeBase64Char('z'));
}

TEST_F(DecodeBase64CharTest_1982, LowercaseM_Returns38_1982) {
    EXPECT_EQ(38u, DecodeBase64Char('m'));
}

TEST_F(DecodeBase64CharTest_1982, AllLowercaseLetters_1982) {
    for (char c = 'a'; c <= 'z'; ++c) {
        EXPECT_EQ(static_cast<unsigned char>(c - 'a' + 26), DecodeBase64Char(static_cast<XMP_Uns8>(c)));
    }
}

// =============================================================================
// Tests for digits (0-9) -> 52-61
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, Digit0_Returns52_1982) {
    EXPECT_EQ(52u, DecodeBase64Char('0'));
}

TEST_F(DecodeBase64CharTest_1982, Digit9_Returns61_1982) {
    EXPECT_EQ(61u, DecodeBase64Char('9'));
}

TEST_F(DecodeBase64CharTest_1982, Digit5_Returns57_1982) {
    EXPECT_EQ(57u, DecodeBase64Char('5'));
}

TEST_F(DecodeBase64CharTest_1982, AllDigits_1982) {
    for (char c = '0'; c <= '9'; ++c) {
        EXPECT_EQ(static_cast<unsigned char>(c - '0' + 52), DecodeBase64Char(static_cast<XMP_Uns8>(c)));
    }
}

// =============================================================================
// Tests for special base64 characters
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, PlusSign_Returns62_1982) {
    EXPECT_EQ(62u, DecodeBase64Char('+'));
}

TEST_F(DecodeBase64CharTest_1982, ForwardSlash_Returns63_1982) {
    EXPECT_EQ(63u, DecodeBase64Char('/'));
}

// =============================================================================
// Tests for whitespace characters -> 0xFF (ignored)
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, Space_Returns0xFF_1982) {
    EXPECT_EQ(0xFFu, DecodeBase64Char(' '));
}

TEST_F(DecodeBase64CharTest_1982, Tab_Returns0xFF_1982) {
    EXPECT_EQ(0xFFu, DecodeBase64Char(static_cast<XMP_Uns8>(kTab)));
}

TEST_F(DecodeBase64CharTest_1982, LineFeed_Returns0xFF_1982) {
    EXPECT_EQ(0xFFu, DecodeBase64Char(static_cast<XMP_Uns8>(kLF)));
}

TEST_F(DecodeBase64CharTest_1982, CarriageReturn_Returns0xFF_1982) {
    EXPECT_EQ(0xFFu, DecodeBase64Char(static_cast<XMP_Uns8>(kCR)));
}

// =============================================================================
// Tests for invalid characters -> throws exception
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, InvalidChar_ExclamationMark_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('!'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_AtSign_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('@'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Hash_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('#'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Equals_Throws_1982) {
    // '=' is used as padding in base64 but this function doesn't handle it
    EXPECT_THROW(DecodeBase64Char('='), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_NullByte_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char(0x00), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Hyphen_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('-'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Underscore_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('_'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Period_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('.'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Comma_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char(','), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_Tilde_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char('~'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_HighByte_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char(0x80), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, InvalidChar_0xFE_Throws_1982) {
    EXPECT_THROW(DecodeBase64Char(0xFE), XMP_Error);
}

// =============================================================================
// Tests for exception error code
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, InvalidChar_ThrowsWithBadParamCode_1982) {
    try {
        DecodeBase64Char('$');
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(kXMPErr_BadParam, e.GetID());
    }
}

// =============================================================================
// Boundary tests
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, BoundaryBefore_A_Throws_1982) {
    // '@' is the character just before 'A' in ASCII
    EXPECT_THROW(DecodeBase64Char('@'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, BoundaryAfter_Z_Throws_1982) {
    // '[' is the character just after 'Z' in ASCII
    EXPECT_THROW(DecodeBase64Char('['), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, BoundaryBefore_a_Throws_1982) {
    // '`' is the character just before 'a' in ASCII
    EXPECT_THROW(DecodeBase64Char('`'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, BoundaryAfter_z_Throws_1982) {
    // '{' is the character just after 'z' in ASCII
    EXPECT_THROW(DecodeBase64Char('{'), XMP_Error);
}

TEST_F(DecodeBase64CharTest_1982, BoundaryBefore_0_Throws_1982) {
    // '/' is the character just before '0' in ASCII, but '/' is a valid base64 char
    EXPECT_EQ(63u, DecodeBase64Char('/'));
}

TEST_F(DecodeBase64CharTest_1982, BoundaryAfter_9_Throws_1982) {
    // ':' is the character just after '9' in ASCII
    EXPECT_THROW(DecodeBase64Char(':'), XMP_Error);
}

// =============================================================================
// Test specific return values for known base64 encoding table
// =============================================================================

TEST_F(DecodeBase64CharTest_1982, Base64Table_B_Returns1_1982) {
    EXPECT_EQ(1u, DecodeBase64Char('B'));
}

TEST_F(DecodeBase64CharTest_1982, Base64Table_b_Returns27_1982) {
    EXPECT_EQ(27u, DecodeBase64Char('b'));
}

TEST_F(DecodeBase64CharTest_1982, Base64Table_1_Returns53_1982) {
    EXPECT_EQ(53u, DecodeBase64Char('1'));
}
