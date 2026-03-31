#include <gtest/gtest.h>
#include <cstdint>

// Minimal type definitions needed by XMPMeta-Parse.cpp
typedef uint8_t XMP_Uns8;

#ifndef XMP_Assert
#define XMP_Assert(expr) ((void)0)
#endif

// Extract the function for testing by including the relevant portion
// We replicate the static function signature since it's static and not accessible otherwise
static int CountUTF8(const XMP_Uns8* charStart, const XMP_Uns8* bufEnd) {
    if (charStart >= bufEnd) return 0;
    if ((*charStart & 0xC0) != 0xC0) return 0;
    int byteCount = 2;
    XMP_Uns8 firstByte = *charStart;
    for (firstByte = firstByte << 2; (firstByte & 0x80) != 0; firstByte = firstByte << 1)
        ++byteCount;
    if ((charStart + byteCount) > bufEnd) return -byteCount;
    for (int i = 1; i < byteCount; ++i) {
        if ((charStart[i] & 0xC0) != 0x80) return 0;
    }
    return byteCount;
}

class CountUTF8Test_1971 : public ::testing::Test {
protected:
};

// === Normal Operation Tests ===

TEST_F(CountUTF8Test_1971, TwoByteCharValid_1971) {
    // 0xC3 0xA9 is 'é' (U+00E9), a valid 2-byte UTF-8 sequence
    XMP_Uns8 buf[] = {0xC3, 0xA9};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, 2);
}

TEST_F(CountUTF8Test_1971, ThreeByteCharValid_1971) {
    // 0xE4 0xB8 0xAD is '中' (U+4E2D), a valid 3-byte UTF-8 sequence
    XMP_Uns8 buf[] = {0xE4, 0xB8, 0xAD};
    int result = CountUTF8(buf, buf + 3);
    EXPECT_EQ(result, 3);
}

TEST_F(CountUTF8Test_1971, FourByteCharValid_1971) {
    // 0xF0 0x9F 0x98 0x80 is '😀' (U+1F600), a valid 4-byte UTF-8 sequence
    XMP_Uns8 buf[] = {0xF0, 0x9F, 0x98, 0x80};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 4);
}

TEST_F(CountUTF8Test_1971, FiveByteCharValid_1971) {
    // 0xF8 followed by 4 continuation bytes (5-byte sequence, technically invalid Unicode but valid encoding pattern)
    XMP_Uns8 buf[] = {0xF8, 0x80, 0x80, 0x80, 0x80};
    int result = CountUTF8(buf, buf + 5);
    EXPECT_EQ(result, 5);
}

TEST_F(CountUTF8Test_1971, SixByteCharValid_1971) {
    // 0xFC followed by 5 continuation bytes (6-byte sequence)
    XMP_Uns8 buf[] = {0xFC, 0x80, 0x80, 0x80, 0x80, 0x80};
    int result = CountUTF8(buf, buf + 6);
    EXPECT_EQ(result, 6);
}

TEST_F(CountUTF8Test_1971, ValidTwoByteInLargerBuffer_1971) {
    // Valid 2-byte sequence within a larger buffer
    XMP_Uns8 buf[] = {0xC3, 0xA9, 0x41, 0x42};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 2);
}

// === Boundary Condition Tests ===

TEST_F(CountUTF8Test_1971, CharStartEqualsBufEnd_1971) {
    XMP_Uns8 buf[] = {0xC3};
    int result = CountUTF8(buf, buf);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, CharStartGreaterThanBufEnd_1971) {
    XMP_Uns8 buf[] = {0xC3, 0xA9};
    int result = CountUTF8(buf + 1, buf);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, TwoByteSequenceTruncatedAtOne_1971) {
    // 2-byte sequence but buffer only has 1 byte
    XMP_Uns8 buf[] = {0xC3};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, -2);
}

TEST_F(CountUTF8Test_1971, ThreeByteSequenceTruncatedAtOne_1971) {
    XMP_Uns8 buf[] = {0xE4};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, -3);
}

TEST_F(CountUTF8Test_1971, ThreeByteSequenceTruncatedAtTwo_1971) {
    XMP_Uns8 buf[] = {0xE4, 0xB8};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, -3);
}

TEST_F(CountUTF8Test_1971, FourByteSequenceTruncatedAtOne_1971) {
    XMP_Uns8 buf[] = {0xF0};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, -4);
}

TEST_F(CountUTF8Test_1971, FourByteSequenceTruncatedAtTwo_1971) {
    XMP_Uns8 buf[] = {0xF0, 0x9F};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, -4);
}

TEST_F(CountUTF8Test_1971, FourByteSequenceTruncatedAtThree_1971) {
    XMP_Uns8 buf[] = {0xF0, 0x9F, 0x98};
    int result = CountUTF8(buf, buf + 3);
    EXPECT_EQ(result, -4);
}

// === Error/Invalid Input Tests ===

TEST_F(CountUTF8Test_1971, SingleByteASCII_1971) {
    // ASCII character (0x41 = 'A'), top bit not set
    XMP_Uns8 buf[] = {0x41};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ContinuationByteAsFirst_1971) {
    // 0x80 has pattern 10xxxxxx - continuation byte, not a valid start
    XMP_Uns8 buf[] = {0x80, 0x80};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ByteWithOnlyHighBitSet_1971) {
    // 0x80 = 10000000, only one high bit set (pattern 10xxxxxx)
    XMP_Uns8 buf[] = {0x80};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, TwoByteSequenceInvalidContinuation_1971) {
    // 0xC3 expects a continuation byte (10xxxxxx), but 0x41 is ASCII
    XMP_Uns8 buf[] = {0xC3, 0x41};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ThreeByteSequenceInvalidSecondByte_1971) {
    // 0xE4 expects continuation bytes, but second byte 0x41 is invalid
    XMP_Uns8 buf[] = {0xE4, 0x41, 0xAD};
    int result = CountUTF8(buf, buf + 3);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ThreeByteSequenceInvalidThirdByte_1971) {
    // Valid first two bytes but third byte is not a continuation byte
    XMP_Uns8 buf[] = {0xE4, 0xB8, 0x41};
    int result = CountUTF8(buf, buf + 3);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, FourByteSequenceInvalidSecondByte_1971) {
    XMP_Uns8 buf[] = {0xF0, 0x41, 0x98, 0x80};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, FourByteSequenceInvalidThirdByte_1971) {
    XMP_Uns8 buf[] = {0xF0, 0x9F, 0x41, 0x80};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, FourByteSequenceInvalidFourthByte_1971) {
    XMP_Uns8 buf[] = {0xF0, 0x9F, 0x98, 0x41};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ZeroByte_1971) {
    // 0x00 is a valid ASCII NUL, should return 0
    XMP_Uns8 buf[] = {0x00};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ByteValue7F_1971) {
    // 0x7F is the highest single-byte value (DEL)
    XMP_Uns8 buf[] = {0x7F};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, 0);
}

TEST_F(CountUTF8Test_1971, ByteBF_1971) {
    // 0xBF = 10111111, continuation byte only
    XMP_Uns8 buf[] = {0xBF};
    int result = CountUTF8(buf, buf + 1);
    EXPECT_EQ(result, 0);
}

// === Edge cases with minimum valid leading bytes ===

TEST_F(CountUTF8Test_1971, MinimumTwoByteLeader_1971) {
    // 0xC0 is minimum 2-byte leader: 11000000
    XMP_Uns8 buf[] = {0xC0, 0x80};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, 2);
}

TEST_F(CountUTF8Test_1971, MaximumTwoByteLeader_1971) {
    // 0xDF = 11011111, max 2-byte leader
    XMP_Uns8 buf[] = {0xDF, 0xBF};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, 2);
}

TEST_F(CountUTF8Test_1971, MinimumThreeByteLeader_1971) {
    // 0xE0 = 11100000
    XMP_Uns8 buf[] = {0xE0, 0x80, 0x80};
    int result = CountUTF8(buf, buf + 3);
    EXPECT_EQ(result, 3);
}

TEST_F(CountUTF8Test_1971, MinimumFourByteLeader_1971) {
    // 0xF0 = 11110000
    XMP_Uns8 buf[] = {0xF0, 0x80, 0x80, 0x80};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 4);
}

TEST_F(CountUTF8Test_1971, AllFF_TwoBytes_1971) {
    // 0xFF = 11111111, would indicate a very long sequence
    // After shifts: firstByte << 2 = 0xFC, then counts up
    // 0xFF should give byteCount = 7 (2 initial + 5 more from loop: bits 7,6,5,4,3 all set after << 2)
    // Actually let's trace: firstByte = 0xFF
    // firstByte <<= 2 => 0xFC (11111100), bit 7 set => byteCount=3, firstByte <<= 1 => 0xF8 (11111000), bit 7 set => 4, => 0xF0 => 5, => 0xE0 => 6, => 0xC0 => 7, => 0x80 => 8, => 0x00 bit 7 not set
    // So byteCount = 8
    // With only 2 bytes in buffer, should return -8
    XMP_Uns8 buf[] = {0xFF, 0x80};
    int result = CountUTF8(buf, buf + 2);
    EXPECT_EQ(result, -8);
}

TEST_F(CountUTF8Test_1971, AllFF_LargeBuffer_1971) {
    // 0xFF with enough continuation bytes for 8 byte count
    XMP_Uns8 buf[] = {0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
    int result = CountUTF8(buf, buf + 8);
    EXPECT_EQ(result, 8);
}

TEST_F(CountUTF8Test_1971, FE_LeadByte_1971) {
    // 0xFE = 11111110
    // firstByte << 2 = 0xF8 (11111000) => byteCount 3, << => 0xF0 => 4, => 0xE0 => 5, => 0xC0 => 6, => 0x80 => 7, => 0x00 stop
    // byteCount = 7
    XMP_Uns8 buf[] = {0xFE, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
    int result = CountUTF8(buf, buf + 7);
    EXPECT_EQ(result, 7);
}

// === Multiple valid sequences in buffer, only first counted ===

TEST_F(CountUTF8Test_1971, MultipleSequencesOnlyFirstCounted_1971) {
    // Two 2-byte sequences back to back, function should only count the first
    XMP_Uns8 buf[] = {0xC3, 0xA9, 0xC3, 0xA9};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 2);
}

// Exact boundary: buffer ends exactly at the end of the sequence
TEST_F(CountUTF8Test_1971, ExactBoundaryThreeByte_1971) {
    XMP_Uns8 buf[] = {0xE4, 0xB8, 0xAD};
    int result = CountUTF8(buf, buf + 3);
    EXPECT_EQ(result, 3);
}

TEST_F(CountUTF8Test_1971, ExactBoundaryFourByte_1971) {
    XMP_Uns8 buf[] = {0xF0, 0x9F, 0x98, 0x80};
    int result = CountUTF8(buf, buf + 4);
    EXPECT_EQ(result, 4);
}
