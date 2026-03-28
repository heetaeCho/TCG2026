#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the XMP SDK Unicode conversion headers
// The public API wraps the static functions we want to test
#include "source/UnicodeConversions.hpp"

class UnicodeConversionsTest_2073 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ASCII character conversion (single byte, codepoint <= 0x7F)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_ASCIICharacter_2073) {
    UTF32Unit utf32In[] = { 0x41 }; // 'A'
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Out[0], 0x41);
}

// Test multiple ASCII characters
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MultipleASCII_2073) {
    UTF32Unit utf32In[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // "Hello"
    UTF8Unit utf8Out[16] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 5, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 5u);
    EXPECT_EQ(utf8Written, 5u);
    EXPECT_EQ(utf8Out[0], 'H');
    EXPECT_EQ(utf8Out[1], 'e');
    EXPECT_EQ(utf8Out[2], 'l');
    EXPECT_EQ(utf8Out[3], 'l');
    EXPECT_EQ(utf8Out[4], 'o');
}

// Test 2-byte UTF-8 encoding (codepoints 0x80 - 0x7FF)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_TwoByteCharacter_2073) {
    UTF32Unit utf32In[] = { 0xC9 }; // É (U+00C9)
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xC3);
    EXPECT_EQ(utf8Out[1], 0x89);
}

// Test 3-byte UTF-8 encoding (codepoints 0x800 - 0xFFFF)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_ThreeByteCharacter_2073) {
    UTF32Unit utf32In[] = { 0x4E16 }; // 世 (U+4E16)
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xE4);
    EXPECT_EQ(utf8Out[1], 0xB8);
    EXPECT_EQ(utf8Out[2], 0x96);
}

// Test 4-byte UTF-8 encoding (codepoints 0x10000 - 0x10FFFF)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_FourByteCharacter_2073) {
    UTF32Unit utf32In[] = { 0x1F600 }; // 😀 (U+1F600)
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF0);
    EXPECT_EQ(utf8Out[1], 0x9F);
    EXPECT_EQ(utf8Out[2], 0x98);
    EXPECT_EQ(utf8Out[3], 0x80);
}

// Test empty input (zero length)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_EmptyInput_2073) {
    UTF32Unit utf32In[] = { 0x41 };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 0, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test output buffer too small for multi-byte character
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_OutputBufferTooSmallForMultiByte_2073) {
    UTF32Unit utf32In[] = { 0x4E16 }; // 世 needs 3 bytes
    UTF8Unit utf8Out[2] = {0}; // Only 2 bytes available
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, 2, &utf32Read, &utf8Written);

    // Should not write partial multi-byte sequences
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test mixed ASCII and multi-byte characters
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MixedASCIIAndMultiByte_2073) {
    UTF32Unit utf32In[] = { 0x41, 0xC9, 0x42 }; // A, É, B
    UTF8Unit utf8Out[16] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 3, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 4u); // 1 + 2 + 1
    EXPECT_EQ(utf8Out[0], 0x41);
    EXPECT_EQ(utf8Out[1], 0xC3);
    EXPECT_EQ(utf8Out[2], 0x89);
    EXPECT_EQ(utf8Out[3], 0x42);
}

// Test boundary: output buffer exactly fits
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_ExactFitBuffer_2073) {
    UTF32Unit utf32In[] = { 0x41, 0x42, 0x43 }; // ABC
    UTF8Unit utf8Out[3] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 3, utf8Out, 3, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 3u);
}

// Test output buffer size of 1 with ASCII
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_SingleByteBuffer_2073) {
    UTF32Unit utf32In[] = { 0x41, 0x42 };
    UTF8Unit utf8Out[1] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 2, utf8Out, 1, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Out[0], 0x41);
}

// Test boundary codepoint 0x7F (max single-byte)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MaxSingleByte_2073) {
    UTF32Unit utf32In[] = { 0x7F };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Out[0], 0x7F);
}

// Test boundary codepoint 0x80 (min two-byte)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MinTwoByte_2073) {
    UTF32Unit utf32In[] = { 0x80 };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xC2);
    EXPECT_EQ(utf8Out[1], 0x80);
}

// Test boundary codepoint 0x7FF (max two-byte)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MaxTwoByte_2073) {
    UTF32Unit utf32In[] = { 0x7FF };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xDF);
    EXPECT_EQ(utf8Out[1], 0xBF);
}

// Test boundary codepoint 0x800 (min three-byte)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MinThreeByte_2073) {
    UTF32Unit utf32In[] = { 0x800 };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xE0);
    EXPECT_EQ(utf8Out[1], 0xA0);
    EXPECT_EQ(utf8Out[2], 0x80);
}

// Test boundary codepoint 0xFFFF (max three-byte)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MaxThreeByte_2073) {
    UTF32Unit utf32In[] = { 0xFFFF };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xEF);
    EXPECT_EQ(utf8Out[1], 0xBF);
    EXPECT_EQ(utf8Out[2], 0xBF);
}

// Test boundary codepoint 0x10000 (min four-byte)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MinFourByte_2073) {
    UTF32Unit utf32In[] = { 0x10000 };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF0);
    EXPECT_EQ(utf8Out[1], 0x90);
    EXPECT_EQ(utf8Out[2], 0x80);
    EXPECT_EQ(utf8Out[3], 0x80);
}

// Test boundary codepoint 0x10FFFF (max valid Unicode)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_MaxUnicode_2073) {
    UTF32Unit utf32In[] = { 0x10FFFF };
    UTF8Unit utf8Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF4);
    EXPECT_EQ(utf8Out[1], 0x8F);
    EXPECT_EQ(utf8Out[2], 0xBF);
    EXPECT_EQ(utf8Out[3], 0xBF);
}

// Test NUL character (U+0000)
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_NulCharacter_2073) {
    UTF32Unit utf32In[] = { 0x00 };
    UTF8Unit utf8Out[8] = {0xFF, 0xFF};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Out[0], 0x00);
}

// Test partial conversion when output buffer runs out mid-stream
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_PartialConversion_2073) {
    // 3 ASCII + 1 three-byte char, buffer only has 4 bytes
    UTF32Unit utf32In[] = { 0x41, 0x42, 0x43, 0x4E16 };
    UTF8Unit utf8Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 4, utf8Out, 4, &utf32Read, &utf8Written);

    // Should convert 3 ASCII (3 bytes) but not the 3-byte char (would need 6 total)
    // Only 1 byte left which is not enough for a 3-byte sequence
    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 3u);
}

// Test consecutive multi-byte characters
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_ConsecutiveMultiByte_2073) {
    UTF32Unit utf32In[] = { 0xC9, 0xE8 }; // É, è
    UTF8Unit utf8Out[16] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 2, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf8Written, 4u); // 2 + 2
}

// Test zero-length output buffer
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_ZeroLengthOutput_2073) {
    UTF32Unit utf32In[] = { 0x41 };
    UTF8Unit utf8Out[1] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 1, utf8Out, 0, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test alternating ASCII and multi-byte
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_AlternatingASCIIAndMultiByte_2073) {
    UTF32Unit utf32In[] = { 0x41, 0x100, 0x42, 0x200, 0x43 };
    UTF8Unit utf8Out[32] = {0};
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In, 5, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

    // A(1) + Ā(2) + B(1) + Ȁ(2) + C(1) = 7 bytes
    EXPECT_EQ(utf32Read, 5u);
    EXPECT_EQ(utf8Written, 7u);
}

// Test large number of ASCII characters
TEST_F(UnicodeConversionsTest_2073, UTF32ToUTF8_LargeASCIIBlock_2073) {
    const size_t count = 256;
    std::vector<UTF32Unit> utf32In(count, 0x61); // 'a' repeated
    std::vector<UTF8Unit> utf8Out(count + 1, 0);
    size_t utf32Read = 0;
    size_t utf8Written = 0;

    UTF32Nat_to_UTF8(utf32In.data(), count, utf8Out.data(), count, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, count);
    EXPECT_EQ(utf8Written, count);
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(utf8Out[i], 0x61);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
