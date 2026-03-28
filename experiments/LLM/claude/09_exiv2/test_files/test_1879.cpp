#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

// Include necessary XMP SDK headers
#include "public/include/XMP_Const.h"
#include "public/include/XMP_Environment.h"
#include "source/UnicodeConversions.hpp"
#include "source/UnicodeConversions.cpp"

// The function under test is defined in UnicodeInlines.incl_cpp
// It may be included transitively. We include it here if needed.
#include "UnicodeInlines.incl_cpp"

class VerifyUTF8Test_1879 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(VerifyUTF8Test_1879, EmptyString_DoesNotThrow_1879) {
    // Empty string should be valid UTF-8
    EXPECT_NO_THROW(VerifyUTF8(""));
}

TEST_F(VerifyUTF8Test_1879, PureASCIIString_DoesNotThrow_1879) {
    // Pure ASCII string (all bytes < 0x80) should be valid
    EXPECT_NO_THROW(VerifyUTF8("Hello, World!"));
}

TEST_F(VerifyUTF8Test_1879, SimpleASCIIAlphanumeric_DoesNotThrow_1879) {
    EXPECT_NO_THROW(VerifyUTF8("abcdefghijklmnopqrstuvwxyz0123456789"));
}

TEST_F(VerifyUTF8Test_1879, ASCIIWithSpecialChars_DoesNotThrow_1879) {
    EXPECT_NO_THROW(VerifyUTF8("!@#$%^&*()_+-=[]{}|;':\",./<>?"));
}

TEST_F(VerifyUTF8Test_1879, SingleASCIIChar_DoesNotThrow_1879) {
    EXPECT_NO_THROW(VerifyUTF8("A"));
}

TEST_F(VerifyUTF8Test_1879, ASCIIControlChars_DoesNotThrow_1879) {
    // Control characters are < 0x80, so they should pass the ASCII check
    EXPECT_NO_THROW(VerifyUTF8("\t\n\r"));
}

// ============================================================
// Valid multi-byte UTF-8 sequences
// ============================================================

TEST_F(VerifyUTF8Test_1879, ValidTwoByteUTF8_DoesNotThrow_1879) {
    // U+00C9 (É) = 0xC3 0x89
    const char str[] = {(char)0xC3, (char)0x89, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidThreeByteUTF8_DoesNotThrow_1879) {
    // U+20AC (€) = 0xE2 0x82 0xAC
    const char str[] = {(char)0xE2, (char)0x82, (char)0xAC, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidFourByteUTF8_DoesNotThrow_1879) {
    // U+1F600 (😀) = 0xF0 0x9F 0x98 0x80
    const char str[] = {(char)0xF0, (char)0x9F, (char)0x98, (char)0x80, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, MixedASCIIAndMultibyte_DoesNotThrow_1879) {
    // "Hé" = 'H' 0xC3 0xA9
    const char str[] = {'H', (char)0xC3, (char)0xA9, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, MultipleMultibyteChars_DoesNotThrow_1879) {
    // Two 2-byte chars: é (C3 A9) ü (C3 BC)
    const char str[] = {(char)0xC3, (char)0xA9, (char)0xC3, (char)0xBC, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidMinimalTwoByte_DoesNotThrow_1879) {
    // U+0080 = 0xC2 0x80 (smallest 2-byte sequence)
    const char str[] = {(char)0xC2, (char)0x80, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidMaxTwoByte_DoesNotThrow_1879) {
    // U+07FF = 0xDF 0xBF (largest 2-byte sequence)
    const char str[] = {(char)0xDF, (char)0xBF, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidMinimalThreeByte_DoesNotThrow_1879) {
    // U+0800 = 0xE0 0xA0 0x80 (smallest 3-byte sequence)
    const char str[] = {(char)0xE0, (char)0xA0, (char)0x80, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidMaxThreeByte_DoesNotThrow_1879) {
    // U+FFFD = 0xEF 0xBF 0xBD
    const char str[] = {(char)0xEF, (char)0xBF, (char)0xBD, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

// ============================================================
// Invalid UTF-8 sequences (boundary/error cases)
// ============================================================

TEST_F(VerifyUTF8Test_1879, InvalidLoneContinuationByte_Throws_1879) {
    // A lone continuation byte (0x80-0xBF) is invalid
    const char str[] = {(char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidLoneContinuationByteMid_Throws_1879) {
    const char str[] = {(char)0xBF, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidTruncatedTwoByte_Throws_1879) {
    // Start of 2-byte sequence but missing continuation
    const char str[] = {(char)0xC3, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidTruncatedThreeByte_OnlySuffix_Throws_1879) {
    // Start of 3-byte sequence, only 1 continuation byte
    const char str[] = {(char)0xE2, (char)0x82, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidTruncatedThreeByte_NoContinuation_Throws_1879) {
    // Start of 3-byte sequence, no continuation bytes
    const char str[] = {(char)0xE2, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidTruncatedFourByte_Throws_1879) {
    // Start of 4-byte sequence, only 2 continuation bytes
    const char str[] = {(char)0xF0, (char)0x9F, (char)0x98, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidOverlongTwoByte_Throws_1879) {
    // Overlong encoding of U+0000: 0xC0 0x80
    const char str[] = {(char)0xC0, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidOverlongTwoByteC1_Throws_1879) {
    // Overlong: 0xC1 0xBF (encodes U+007F which should be 1 byte)
    const char str[] = {(char)0xC1, (char)0xBF, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidOverlongThreeByte_Throws_1879) {
    // Overlong: 0xE0 0x80 0x80 (overlong encoding of U+0000)
    const char str[] = {(char)0xE0, (char)0x80, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidByteFE_Throws_1879) {
    // 0xFE is never valid in UTF-8
    const char str[] = {(char)0xFE, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidByteFF_Throws_1879) {
    // 0xFF is never valid in UTF-8
    const char str[] = {(char)0xFF, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidSequenceAfterValidASCII_Throws_1879) {
    // Valid ASCII followed by invalid byte
    const char str[] = {'A', 'B', (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidContinuationWithoutLeader_Throws_1879) {
    // Multiple continuation bytes without a leading byte
    const char str[] = {(char)0x80, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidTwoByteWithWrongContinuation_Throws_1879) {
    // 2-byte leader followed by non-continuation byte
    const char str[] = {(char)0xC3, (char)0x28, 0x00}; // 0x28 is '(' not a continuation
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ValidUTF8FollowedByASCII_DoesNotThrow_1879) {
    // Valid 2-byte char followed by ASCII
    const char str[] = {(char)0xC3, (char)0xA9, 'A', 'B', 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ASCIIFollowedByValidUTF8_DoesNotThrow_1879) {
    // ASCII followed by valid multibyte
    const char str[] = {'A', 'B', (char)0xC3, (char)0xA9, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

// ============================================================
// Boundary: bytes at exact threshold (0x7F and 0x80)
// ============================================================

TEST_F(VerifyUTF8Test_1879, ByteAt0x7F_DoesNotThrow_1879) {
    // 0x7F is DEL, but still valid ASCII (< 0x80)
    const char str[] = {(char)0x7F, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, ByteAt0x01_DoesNotThrow_1879) {
    // Smallest non-null ASCII byte
    const char str[] = {(char)0x01, 0x00};
    EXPECT_NO_THROW(VerifyUTF8(str));
}

// ============================================================
// Surrogate halves (invalid in UTF-8)
// ============================================================

TEST_F(VerifyUTF8Test_1879, InvalidSurrogateHalf_Throws_1879) {
    // U+D800 encoded as UTF-8: 0xED 0xA0 0x80 (invalid)
    const char str[] = {(char)0xED, (char)0xA0, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidHighSurrogate_Throws_1879) {
    // U+DBFF encoded as UTF-8: 0xED 0xAF 0xBF (invalid)
    const char str[] = {(char)0xED, (char)0xAF, (char)0xBF, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidLowSurrogate_Throws_1879) {
    // U+DC00 encoded as UTF-8: 0xED 0xB0 0x80 (invalid)
    const char str[] = {(char)0xED, (char)0xB0, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

// ============================================================
// Beyond Unicode range
// ============================================================

TEST_F(VerifyUTF8Test_1879, InvalidFiveByteSequence_Throws_1879) {
    // 5-byte sequence (0xF8 lead) is invalid in modern UTF-8
    const char str[] = {(char)0xF8, (char)0x80, (char)0x80, (char)0x80, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

TEST_F(VerifyUTF8Test_1879, InvalidSixByteSequence_Throws_1879) {
    // 6-byte sequence (0xFC lead) is invalid in modern UTF-8
    const char str[] = {(char)0xFC, (char)0x80, (char)0x80, (char)0x80, (char)0x80, (char)0x80, 0x00};
    EXPECT_ANY_THROW(VerifyUTF8(str));
}

// ============================================================
// Long valid strings
// ============================================================

TEST_F(VerifyUTF8Test_1879, LongValidASCIIString_DoesNotThrow_1879) {
    std::string longStr(1000, 'A');
    EXPECT_NO_THROW(VerifyUTF8(longStr.c_str()));
}

TEST_F(VerifyUTF8Test_1879, LongValidMixedUTF8String_DoesNotThrow_1879) {
    // Build a long string with repeated valid 2-byte chars
    std::string longStr;
    for (int i = 0; i < 500; ++i) {
        longStr += (char)0xC3;
        longStr += (char)0xA9; // é
    }
    EXPECT_NO_THROW(VerifyUTF8(longStr.c_str()));
}
