#include <gtest/gtest.h>

// Forward declare the function under test
namespace re2 {
int fullrune(const char *str, int n);
}

using re2::fullrune;

// Constants from the enum for readability
enum {
    Tx = 128,
    T3 = 224,
    T4 = 240,
};

// ==================== Normal operation tests ====================

// Single-byte ASCII character (c < Tx) with n=1 should return 1 (full rune)
TEST(FullRuneTest_207, SingleByteAsciiReturnsOne_207) {
    const char str[] = "A"; // 0x41, which is < 128
    EXPECT_EQ(1, fullrune(str, 1));
}

// Two-byte sequence with n=2 where first byte indicates 2-byte char (Tx <= c < T3)
TEST(FullRuneTest_207, TwoByteSequenceWithSufficientLength_207) {
    const char str[] = "\xC2\x80"; // 0xC2 = 194, which is >= Tx(128) and < T3(224)
    EXPECT_EQ(1, fullrune(str, 2));
}

// Three-byte sequence with n=3 where first byte indicates 3-byte char (T3 <= c < T4)
TEST(FullRuneTest_207, ThreeByteSequenceWithSufficientLength_207) {
    const char str[] = "\xE0\xA0\x80"; // 0xE0 = 224 = T3, >= T3 and < T4(240)
    EXPECT_EQ(1, fullrune(str, 3));
}

// Four-byte sequence with n=4 where first byte indicates 4-byte char (c >= T4)
TEST(FullRuneTest_207, FourByteSequenceWithSufficientLength_207) {
    const char str[] = "\xF0\x90\x80\x80"; // 0xF0 = 240 = T4
    EXPECT_EQ(1, fullrune(str, 4));
}

// ==================== Boundary condition tests ====================

// n=0 should return 0 (not a full rune, no data)
TEST(FullRuneTest_207, ZeroLengthReturnsZero_207) {
    const char str[] = "A";
    EXPECT_EQ(0, fullrune(str, 0));
}

// Negative n should return 0
TEST(FullRuneTest_207, NegativeLengthReturnsZero_207) {
    const char str[] = "A";
    EXPECT_EQ(0, fullrune(str, -1));
}

// First byte exactly at Tx boundary (128) with n=1 should return 0 (incomplete)
TEST(FullRuneTest_207, FirstByteAtTxWithN1ReturnsZero_207) {
    const char str[] = "\x80"; // 0x80 = 128 = Tx
    EXPECT_EQ(0, fullrune(str, 1));
}

// First byte just below Tx (127) with n=1 should return 1 (single byte)
TEST(FullRuneTest_207, FirstByteJustBelowTxReturnsOne_207) {
    const char str[] = "\x7F"; // 0x7F = 127 < 128
    EXPECT_EQ(1, fullrune(str, 1));
}

// Two-byte char indicator (Tx <= c < T3) with n=2 should return 1
TEST(FullRuneTest_207, TwoByteIndicatorWithN2ReturnsOne_207) {
    const char str[] = "\xC0\x80"; // 0xC0 = 192, Tx(128) <= 192 < T3(224)
    EXPECT_EQ(1, fullrune(str, 2));
}

// First byte just below T3 (223) with n=2 should return 1
TEST(FullRuneTest_207, FirstByteJustBelowT3WithN2ReturnsOne_207) {
    const char str[] = "\xDF\xBF"; // 0xDF = 223 < T3(224)
    EXPECT_EQ(1, fullrune(str, 2));
}

// First byte at T3 (224) with n=2 should return 0 (needs 3 bytes)
TEST(FullRuneTest_207, FirstByteAtT3WithN2ReturnsZero_207) {
    const char str[] = "\xE0\x80"; // 0xE0 = 224 = T3
    EXPECT_EQ(0, fullrune(str, 2));
}

// First byte just below T4 (239) with n=3 should return 1
TEST(FullRuneTest_207, FirstByteJustBelowT4WithN3ReturnsOne_207) {
    const char str[] = "\xEF\xBF\xBF"; // 0xEF = 239 < T4(240)
    EXPECT_EQ(1, fullrune(str, 3));
}

// First byte at T4 (240) with n=3 should return 0 (needs 4 bytes)
TEST(FullRuneTest_207, FirstByteAtT4WithN3ReturnsZero_207) {
    const char str[] = "\xF0\x80\x80"; // 0xF0 = 240 = T4
    EXPECT_EQ(0, fullrune(str, 3));
}

// First byte above T4 with n=4 should return 1
TEST(FullRuneTest_207, FirstByteAboveT4WithN4ReturnsOne_207) {
    const char str[] = "\xF4\x80\x80\x80"; // 0xF4 = 244 > T4
    EXPECT_EQ(1, fullrune(str, 4));
}

// n > 3 always returns 1 for multi-byte leading byte
TEST(FullRuneTest_207, NGreaterThan3AlwaysReturnsOneForMultibyte_207) {
    const char str[] = "\xF4\x80\x80\x80\x80"; // 0xF4 with n=5
    EXPECT_EQ(1, fullrune(str, 5));
}

// ==================== Incomplete sequence tests ====================

// Two-byte character indicator but only n=1
TEST(FullRuneTest_207, TwoByteCharWithN1ReturnsZero_207) {
    const char str[] = "\xC2"; // 0xC2 = 194, needs 2 bytes
    EXPECT_EQ(0, fullrune(str, 1));
}

// Three-byte character indicator but only n=1
TEST(FullRuneTest_207, ThreeByteCharWithN1ReturnsZero_207) {
    const char str[] = "\xE0"; // 0xE0 = 224 = T3, needs 3 bytes
    EXPECT_EQ(0, fullrune(str, 1));
}

// Four-byte character indicator but only n=1
TEST(FullRuneTest_207, FourByteCharWithN1ReturnsZero_207) {
    const char str[] = "\xF0"; // 0xF0 = 240 = T4, needs 4 bytes
    EXPECT_EQ(0, fullrune(str, 1));
}

// Four-byte character indicator but only n=2
TEST(FullRuneTest_207, FourByteCharWithN2ReturnsZero_207) {
    const char str[] = "\xF0\x80"; // 0xF0 = T4, needs 4 but only 2
    EXPECT_EQ(0, fullrune(str, 2));
}

// ==================== Edge: null character as first byte ====================

// Null character (0x00 < Tx) with n=1 should return 1
TEST(FullRuneTest_207, NullCharacterReturnsOne_207) {
    const char str[] = "\x00";
    EXPECT_EQ(1, fullrune(str, 1));
}

// ==================== Additional boundary: continuation byte range ====================

// Continuation byte 0xBF (191) as first byte, >= Tx but < T3, with n=2
TEST(FullRuneTest_207, ContinuationByteAsLeadWithN2_207) {
    const char str[] = "\xBF\x80"; // 0xBF = 191, Tx(128) <= 191 < T3(224)
    EXPECT_EQ(1, fullrune(str, 2));
}

// Continuation byte 0x80 as first byte with n=1
TEST(FullRuneTest_207, ContinuationByte80WithN1_207) {
    const char str[] = "\x80";
    EXPECT_EQ(0, fullrune(str, 1));
}

// First byte 0xFF (255) with n=3 should return 0 (>= T4, needs 4)
TEST(FullRuneTest_207, FirstByte0xFFWithN3ReturnsZero_207) {
    const char str[] = "\xFF\x80\x80";
    EXPECT_EQ(0, fullrune(str, 3));
}

// First byte 0xFF with n=4 should return 1 (n > 3)
TEST(FullRuneTest_207, FirstByte0xFFWithN4ReturnsOne_207) {
    const char str[] = "\xFF\x80\x80\x80";
    EXPECT_EQ(1, fullrune(str, 4));
}
