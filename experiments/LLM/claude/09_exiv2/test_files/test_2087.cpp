#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <cstdint>

// Include the header that declares the public conversion interface
// In exiv2's xmpsdk, UnicodeConversions.hpp typically exposes these
#include "xmpsdk/src/UnicodeConversions.hpp"

// If the static function is not directly accessible, we include the cpp to test it
// This is a pragmatic approach for testing static functions
#include "xmpsdk/src/UnicodeConversions.cpp"

class UTF16SwpToUTF32NatTest_2087 : public ::testing::Test {
protected:
    // Helper to byte-swap a UTF-16 unit
    static UTF16Unit SwapBytes16(UTF16Unit val) {
        return static_cast<UTF16Unit>(((val & 0xFF) << 8) | ((val >> 8) & 0xFF));
    }

    // Helper to create a swapped UTF-16 buffer from native values
    static std::vector<UTF16Unit> MakeSwapped(const std::vector<UTF16Unit>& native) {
        std::vector<UTF16Unit> swapped(native.size());
        for (size_t i = 0; i < native.size(); ++i) {
            swapped[i] = SwapBytes16(native[i]);
        }
        return swapped;
    }
};

// Test basic ASCII-range characters (BMP, no surrogates)
TEST_F(UTF16SwpToUTF32NatTest_2087, BasicASCIIConversion_2087) {
    // 'A' = 0x0041, 'B' = 0x0042, 'C' = 0x0043
    std::vector<UTF16Unit> native = {0x0041, 0x0042, 0x0043};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[3] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 3, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(output[0], 0x0041u);
    EXPECT_EQ(output[1], 0x0042u);
    EXPECT_EQ(output[2], 0x0043u);
}

// Test empty input
TEST_F(UTF16SwpToUTF32NatTest_2087, EmptyInput_2087) {
    UTF16Unit input[1] = {0};
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input, 0, output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test zero-size output buffer
TEST_F(UTF16SwpToUTF32NatTest_2087, ZeroOutputBuffer_2087) {
    std::vector<UTF16Unit> native = {0x0041};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 0, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test surrogate pair: U+10000 = D800 DC00
TEST_F(UTF16SwpToUTF32NatTest_2087, SurrogatePairConversion_2087) {
    // U+10000 is encoded as surrogate pair: high=0xD800, low=0xDC00
    std::vector<UTF16Unit> native = {0xD800, 0xDC00};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x00010000u);
}

// Test surrogate pair: U+10FFFF = DBFF DFFF
TEST_F(UTF16SwpToUTF32NatTest_2087, MaxSurrogatePair_2087) {
    // U+10FFFF is encoded as surrogate pair: high=0xDBFF, low=0xDFFF
    std::vector<UTF16Unit> native = {0xDBFF, 0xDFFF};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x0010FFFFu);
}

// Test mixed BMP and surrogate pair
TEST_F(UTF16SwpToUTF32NatTest_2087, MixedBMPAndSurrogate_2087) {
    // 'A' (0x0041), U+10000 (D800 DC00), 'B' (0x0042)
    std::vector<UTF16Unit> native = {0x0041, 0xD800, 0xDC00, 0x0042};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[3] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 3, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(output[0], 0x0041u);
    EXPECT_EQ(output[1], 0x00010000u);
    EXPECT_EQ(output[2], 0x0042u);
}

// Test incomplete surrogate pair at end of input (only high surrogate)
TEST_F(UTF16SwpToUTF32NatTest_2087, IncompleteSurrogatePairAtEnd_2087) {
    // 'A' followed by lone high surrogate
    std::vector<UTF16Unit> native = {0x0041, 0xD800};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[2] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 2, &utf16Read, &utf32Written);

    // Should convert 'A' and stop at incomplete surrogate
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x0041u);
}

// Test output buffer smaller than input (truncation)
TEST_F(UTF16SwpToUTF32NatTest_2087, OutputBufferSmaller_2087) {
    std::vector<UTF16Unit> native = {0x0041, 0x0042, 0x0043, 0x0044};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[2] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(output[0], 0x0041u);
    EXPECT_EQ(output[1], 0x0042u);
}

// Test single character conversion
TEST_F(UTF16SwpToUTF32NatTest_2087, SingleCharacter_2087) {
    std::vector<UTF16Unit> native = {0x00E9}; // é
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x00E9u);
}

// Test BMP character just below surrogate range
TEST_F(UTF16SwpToUTF32NatTest_2087, CharBelowSurrogateRange_2087) {
    std::vector<UTF16Unit> native = {0xD7FF};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0xD7FFu);
}

// Test BMP character just above surrogate range
TEST_F(UTF16SwpToUTF32NatTest_2087, CharAboveSurrogateRange_2087) {
    std::vector<UTF16Unit> native = {0xE000};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0xE000u);
}

// Test maximum BMP value (0xFFFF)
TEST_F(UTF16SwpToUTF32NatTest_2087, MaxBMPValue_2087) {
    std::vector<UTF16Unit> native = {0xFFFF};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0xFFFFu);
}

// Test multiple surrogate pairs
TEST_F(UTF16SwpToUTF32NatTest_2087, MultipleSurrogatePairs_2087) {
    // U+10000 (D800 DC00) and U+10001 (D800 DC01)
    std::vector<UTF16Unit> native = {0xD800, 0xDC00, 0xD800, 0xDC01};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[2] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(output[0], 0x00010000u);
    EXPECT_EQ(output[1], 0x00010001u);
}

// Test surrogate pair with insufficient output space
TEST_F(UTF16SwpToUTF32NatTest_2087, SurrogatePairNoOutputSpace_2087) {
    // Surrogate pair needs 1 UTF-32 unit but output has 0 space
    std::vector<UTF16Unit> native = {0xD800, 0xDC00};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 0, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test output buffer exactly fits surrogate pair result
TEST_F(UTF16SwpToUTF32NatTest_2087, OutputBufferExactFitSurrogate_2087) {
    // BMP + surrogate pair, output size = 2
    std::vector<UTF16Unit> native = {0x0041, 0xD800, 0xDC00};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[2] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(output[0], 0x0041u);
    EXPECT_EQ(output[1], 0x00010000u);
}

// Test surrogate pair followed by BMP, with output limited to 1
TEST_F(UTF16SwpToUTF32NatTest_2087, SurrogateThenBMPLimitedOutput_2087) {
    std::vector<UTF16Unit> native = {0xD800, 0xDC00, 0x0042};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x00010000u);
}

// Test null character (U+0000) which is valid UTF-16
TEST_F(UTF16SwpToUTF32NatTest_2087, NullCharacter_2087) {
    std::vector<UTF16Unit> native = {0x0000};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0xFFFFFFFF};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x0000u);
}

// Test large BMP sequence
TEST_F(UTF16SwpToUTF32NatTest_2087, LargeBMPSequence_2087) {
    const size_t count = 100;
    std::vector<UTF16Unit> native(count);
    for (size_t i = 0; i < count; ++i) {
        native[i] = static_cast<UTF16Unit>(0x0041 + (i % 26)); // A-Z repeating
    }
    std::vector<UTF16Unit> input = MakeSwapped(native);
    std::vector<UTF32Unit> output(count, 0);
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output.data(), count, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, count);
    EXPECT_EQ(utf32Written, count);
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(output[i], static_cast<UTF32Unit>(0x0041 + (i % 26)));
    }
}

// Test CJK character (BMP)
TEST_F(UTF16SwpToUTF32NatTest_2087, CJKCharacter_2087) {
    // U+4E2D (中)
    std::vector<UTF16Unit> native = {0x4E2D};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x4E2Du);
}

// Test emoji as surrogate pair: U+1F600 = D83D DE00
TEST_F(UTF16SwpToUTF32NatTest_2087, EmojiSurrogatePair_2087) {
    std::vector<UTF16Unit> native = {0xD83D, 0xDE00};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x0001F600u);
}

// Test lone high surrogate at input start (only 1 unit in input)
TEST_F(UTF16SwpToUTF32NatTest_2087, LoneHighSurrogateOnly_2087) {
    std::vector<UTF16Unit> native = {0xD800};
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), input.size(), output, 1, &utf16Read, &utf32Written);

    // Should not convert anything - incomplete surrogate pair
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test both input and output are length 1 with BMP char
TEST_F(UTF16SwpToUTF32NatTest_2087, SingleUnitBothBuffers_2087) {
    std::vector<UTF16Unit> native = {0x007A}; // 'z'
    std::vector<UTF16Unit> input = MakeSwapped(native);
    UTF32Unit output[1] = {0};
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Nat(input.data(), 1, output, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0x007Au);
}
