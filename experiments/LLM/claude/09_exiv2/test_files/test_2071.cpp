#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the XMP SDK Unicode conversion headers
// The public API typically wraps these static functions
#include "UnicodeConversions.hpp"

class UTF8ToUTF32NatTest_2071 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ASCII single byte conversion
TEST_F(UTF8ToUTF32NatTest_2071, SingleASCIICharacter_2071) {
    const UTF8Unit utf8In[] = { 0x41 }; // 'A'
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 1, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x41));
}

// Test multiple ASCII characters
TEST_F(UTF8ToUTF32NatTest_2071, MultipleASCIICharacters_2071) {
    const UTF8Unit utf8In[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // "Hello"
    UTF32Unit utf32Out[8] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 5, utf32Out, 8, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 5u);
    EXPECT_EQ(utf32Written, 5u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x48));
    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(0x65));
    EXPECT_EQ(utf32Out[2], static_cast<UTF32Unit>(0x6C));
    EXPECT_EQ(utf32Out[3], static_cast<UTF32Unit>(0x6C));
    EXPECT_EQ(utf32Out[4], static_cast<UTF32Unit>(0x6F));
}

// Test empty input
TEST_F(UTF8ToUTF32NatTest_2071, EmptyInput_2071) {
    const UTF8Unit utf8In[] = { 0x41 }; // dummy, won't be read
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 0, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test two-byte UTF8 character (e.g., U+00E9 é = 0xC3 0xA9)
TEST_F(UTF8ToUTF32NatTest_2071, TwoByteUTF8Character_2071) {
    const UTF8Unit utf8In[] = { 0xC3, 0xA9 }; // é (U+00E9)
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 2, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x00E9));
}

// Test three-byte UTF8 character (e.g., U+4E16 世 = 0xE4 0xB8 0x96)
TEST_F(UTF8ToUTF32NatTest_2071, ThreeByteUTF8Character_2071) {
    const UTF8Unit utf8In[] = { 0xE4, 0xB8, 0x96 }; // 世 (U+4E16)
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 3, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x4E16));
}

// Test four-byte UTF8 character (e.g., U+1F600 😀 = 0xF0 0x9F 0x98 0x80)
TEST_F(UTF8ToUTF32NatTest_2071, FourByteUTF8Character_2071) {
    const UTF8Unit utf8In[] = { 0xF0, 0x9F, 0x98, 0x80 }; // 😀 (U+1F600)
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 4, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x1F600));
}

// Test mixed ASCII and multi-byte
TEST_F(UTF8ToUTF32NatTest_2071, MixedASCIIAndMultiByte_2071) {
    // "Aé" = 0x41, 0xC3, 0xA9
    const UTF8Unit utf8In[] = { 0x41, 0xC3, 0xA9 };
    UTF32Unit utf32Out[8] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 3, utf32Out, 8, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x41));
    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(0xE9));
}

// Test output buffer smaller than needed - only room for 1 code point
TEST_F(UTF8ToUTF32NatTest_2071, OutputBufferTooSmall_2071) {
    const UTF8Unit utf8In[] = { 0x41, 0x42, 0x43 }; // "ABC"
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 3, utf32Out, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x41));
}

// Test truncated multi-byte sequence (incomplete 2-byte sequence)
TEST_F(UTF8ToUTF32NatTest_2071, TruncatedTwoByteSequence_2071) {
    const UTF8Unit utf8In[] = { 0xC3 }; // First byte of é, missing continuation
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 1, utf32Out, 4, &utf8Read, &utf32Written);

    // Should stop at the incomplete character
    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test truncated three-byte sequence
TEST_F(UTF8ToUTF32NatTest_2071, TruncatedThreeByteSequence_2071) {
    const UTF8Unit utf8In[] = { 0xE4, 0xB8 }; // Missing third byte of 世
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 2, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test boundary value 0x7F (max single-byte UTF8)
TEST_F(UTF8ToUTF32NatTest_2071, MaxSingleByteASCII_2071) {
    const UTF8Unit utf8In[] = { 0x7F };
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 1, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x7F));
}

// Test boundary value 0x00 (NUL byte)
TEST_F(UTF8ToUTF32NatTest_2071, NullByte_2071) {
    const UTF8Unit utf8In[] = { 0x00 };
    UTF32Unit utf32Out[4] = { 0xFFFF };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 1, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x00));
}

// Test boundary: smallest two-byte sequence U+0080 = 0xC2 0x80
TEST_F(UTF8ToUTF32NatTest_2071, SmallestTwoByteChar_2071) {
    const UTF8Unit utf8In[] = { 0xC2, 0x80 }; // U+0080
    UTF32Unit utf32Out[4] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 2, utf32Out, 4, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x0080));
}

// Test ASCII followed by truncated multi-byte
TEST_F(UTF8ToUTF32NatTest_2071, ASCIIFollowedByTruncatedMultiByte_2071) {
    const UTF8Unit utf8In[] = { 0x41, 0x42, 0xC3 }; // "AB" + truncated é
    UTF32Unit utf32Out[8] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 3, utf32Out, 8, &utf8Read, &utf32Written);

    // Should convert "AB" and stop at incomplete multi-byte
    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x41));
    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(0x42));
}

// Test zero-length output buffer
TEST_F(UTF8ToUTF32NatTest_2071, ZeroLengthOutputBuffer_2071) {
    const UTF8Unit utf8In[] = { 0x41 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 1, utf32Out, 0, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test multi-byte followed by ASCII
TEST_F(UTF8ToUTF32NatTest_2071, MultiByteFollowedByASCII_2071) {
    const UTF8Unit utf8In[] = { 0xC3, 0xA9, 0x41 }; // éA
    UTF32Unit utf32Out[8] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 3, utf32Out, 8, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0xE9));
    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(0x41));
}

// Test exact output buffer size
TEST_F(UTF8ToUTF32NatTest_2071, ExactOutputBufferSize_2071) {
    const UTF8Unit utf8In[] = { 0x41, 0x42 }; // "AB"
    UTF32Unit utf32Out[2] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 2, utf32Out, 2, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x41));
    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(0x42));
}

// Test larger input with multiple multi-byte sequences
TEST_F(UTF8ToUTF32NatTest_2071, MultipleMultiByteSequences_2071) {
    // "éà" = 0xC3 0xA9 0xC3 0xA0
    const UTF8Unit utf8In[] = { 0xC3, 0xA9, 0xC3, 0xA0 };
    UTF32Unit utf32Out[8] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 4, utf32Out, 8, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0xE9));
    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>(0xE0));
}

// Test output buffer limits with multi-byte characters
TEST_F(UTF8ToUTF32NatTest_2071, OutputBufferLimitWithMultiByte_2071) {
    // Two multi-byte chars but only room for one
    const UTF8Unit utf8In[] = { 0xC3, 0xA9, 0xC3, 0xA0 }; // éà
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    UTF8_to_UTF32(utf8In, 4, utf32Out, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0xE9));
}
