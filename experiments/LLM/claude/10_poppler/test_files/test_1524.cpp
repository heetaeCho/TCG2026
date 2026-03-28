#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <string_view>
#include "UTF.h"

// Helper to access the function under test
// The function signature: std::vector<Unicode> utf8ToUCS4(std::string_view utf8);

class Utf8ToUCS4Test_1524 : public ::testing::Test {
protected:
    const Unicode REPLACEMENT_CHAR = 0xFFFD; // U+FFFD
};

// Test empty string returns empty vector
TEST_F(Utf8ToUCS4Test_1524, EmptyString_1524) {
    auto result = utf8ToUCS4("");
    EXPECT_TRUE(result.empty());
}

// Test single ASCII character
TEST_F(Utf8ToUCS4Test_1524, SingleAsciiCharacter_1524) {
    auto result = utf8ToUCS4("A");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x41u); // 'A'
}

// Test multiple ASCII characters
TEST_F(Utf8ToUCS4Test_1524, MultipleAsciiCharacters_1524) {
    auto result = utf8ToUCS4("Hello");
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 'H');
    EXPECT_EQ(result[1], 'e');
    EXPECT_EQ(result[2], 'l');
    EXPECT_EQ(result[3], 'l');
    EXPECT_EQ(result[4], 'o');
}

// Test null character (U+0000)
TEST_F(Utf8ToUCS4Test_1524, NullCharacter_1524) {
    std::string_view sv("\0", 1);
    auto result = utf8ToUCS4(sv);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0u);
}

// Test two-byte UTF-8 sequence (e.g., U+00E9 é = 0xC3 0xA9)
TEST_F(Utf8ToUCS4Test_1524, TwoByteUtf8Character_1524) {
    auto result = utf8ToUCS4("\xC3\xA9"); // é
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00E9u);
}

// Test three-byte UTF-8 sequence (e.g., U+4E16 世 = 0xE4 0xB8 0x96)
TEST_F(Utf8ToUCS4Test_1524, ThreeByteUtf8Character_1524) {
    auto result = utf8ToUCS4("\xE4\xB8\x96"); // 世
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x4E16u);
}

// Test four-byte UTF-8 sequence (e.g., U+1F600 😀 = 0xF0 0x9F 0x98 0x80)
TEST_F(Utf8ToUCS4Test_1524, FourByteUtf8Character_1524) {
    auto result = utf8ToUCS4("\xF0\x9F\x98\x80"); // 😀
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x1F600u);
}

// Test mixed ASCII and multi-byte characters
TEST_F(Utf8ToUCS4Test_1524, MixedAsciiAndMultibyte_1524) {
    // "Aé世" = 'A' + U+00E9 + U+4E16
    auto result = utf8ToUCS4("A\xC3\xA9\xE4\xB8\x96");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0x41u);
    EXPECT_EQ(result[1], 0x00E9u);
    EXPECT_EQ(result[2], 0x4E16u);
}

// Test invalid single byte (0xFF is never valid UTF-8)
TEST_F(Utf8ToUCS4Test_1524, InvalidSingleByte_1524) {
    auto result = utf8ToUCS4("\xFF");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], REPLACEMENT_CHAR);
}

// Test invalid continuation byte without leading byte (0x80)
TEST_F(Utf8ToUCS4Test_1524, InvalidContinuationByte_1524) {
    auto result = utf8ToUCS4("\x80");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], REPLACEMENT_CHAR);
}

// Test truncated two-byte sequence (missing continuation)
TEST_F(Utf8ToUCS4Test_1524, TruncatedTwoByteSequence_1524) {
    auto result = utf8ToUCS4("\xC3"); // Missing second byte
    ASSERT_GE(result.size(), 1u);
    EXPECT_EQ(result.back(), REPLACEMENT_CHAR);
}

// Test truncated three-byte sequence (missing one continuation byte)
TEST_F(Utf8ToUCS4Test_1524, TruncatedThreeByteSequence_1524) {
    auto result = utf8ToUCS4("\xE4\xB8"); // Missing third byte
    ASSERT_GE(result.size(), 1u);
    EXPECT_EQ(result.back(), REPLACEMENT_CHAR);
}

// Test truncated four-byte sequence
TEST_F(Utf8ToUCS4Test_1524, TruncatedFourByteSequence_1524) {
    auto result = utf8ToUCS4("\xF0\x9F\x98"); // Missing fourth byte
    ASSERT_GE(result.size(), 1u);
    EXPECT_EQ(result.back(), REPLACEMENT_CHAR);
}

// Test overlong encoding: U+002F encoded as 0xC0 0xAF (invalid)
TEST_F(Utf8ToUCS4Test_1524, OverlongEncoding_1524) {
    auto result = utf8ToUCS4("\xC0\xAF");
    // Overlong encodings should produce replacement characters
    for (auto c : result) {
        // Each output should be a replacement char since this is invalid
        EXPECT_EQ(c, REPLACEMENT_CHAR);
    }
    EXPECT_GE(result.size(), 1u);
}

// Test invalid byte followed by valid ASCII
TEST_F(Utf8ToUCS4Test_1524, InvalidByteFollowedByValidAscii_1524) {
    auto result = utf8ToUCS4("\xFF" "A");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], REPLACEMENT_CHAR);
    EXPECT_EQ(result[1], 0x41u);
}

// Test valid followed by invalid followed by valid
TEST_F(Utf8ToUCS4Test_1524, ValidInvalidValid_1524) {
    auto result = utf8ToUCS4("A\xFEB");
    ASSERT_GE(result.size(), 3u);
    EXPECT_EQ(result[0], 0x41u); // 'A'
    EXPECT_EQ(result[1], REPLACEMENT_CHAR); // invalid
    EXPECT_EQ(result[2], 0x42u); // 'B'
}

// Test U+007F (max single byte, DEL)
TEST_F(Utf8ToUCS4Test_1524, MaxSingleByte_1524) {
    auto result = utf8ToUCS4("\x7F");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x7Fu);
}

// Test U+0080 (min two-byte: 0xC2 0x80)
TEST_F(Utf8ToUCS4Test_1524, MinTwoByte_1524) {
    auto result = utf8ToUCS4("\xC2\x80");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x80u);
}

// Test U+07FF (max two-byte: 0xDF 0xBF)
TEST_F(Utf8ToUCS4Test_1524, MaxTwoByte_1524) {
    auto result = utf8ToUCS4("\xDF\xBF");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x07FFu);
}

// Test U+0800 (min three-byte: 0xE0 0xA0 0x80)
TEST_F(Utf8ToUCS4Test_1524, MinThreeByte_1524) {
    auto result = utf8ToUCS4("\xE0\xA0\x80");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0800u);
}

// Test U+FFFF (max three-byte: 0xEF 0xBF 0xBF)
TEST_F(Utf8ToUCS4Test_1524, MaxThreeByte_1524) {
    auto result = utf8ToUCS4("\xEF\xBF\xBF");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFFFFu);
}

// Test U+10000 (min four-byte: 0xF0 0x90 0x80 0x80)
TEST_F(Utf8ToUCS4Test_1524, MinFourByte_1524) {
    auto result = utf8ToUCS4("\xF0\x90\x80\x80");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x10000u);
}

// Test U+10FFFF (max valid Unicode: 0xF4 0x8F 0xBF 0xBF)
TEST_F(Utf8ToUCS4Test_1524, MaxUnicode_1524) {
    auto result = utf8ToUCS4("\xF4\x8F\xBF\xBF");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x10FFFFu);
}

// Test multiple invalid bytes in a row
TEST_F(Utf8ToUCS4Test_1524, MultipleInvalidBytes_1524) {
    auto result = utf8ToUCS4("\xFF\xFE\xFD");
    ASSERT_EQ(result.size(), 3u);
    for (auto c : result) {
        EXPECT_EQ(c, REPLACEMENT_CHAR);
    }
}

// Test all ASCII printable characters
TEST_F(Utf8ToUCS4Test_1524, AllAsciiPrintable_1524) {
    std::string ascii;
    for (char c = 0x20; c < 0x7F; c++) {
        ascii.push_back(c);
    }
    auto result = utf8ToUCS4(ascii);
    ASSERT_EQ(result.size(), static_cast<size_t>(0x7F - 0x20));
    for (size_t i = 0; i < result.size(); i++) {
        EXPECT_EQ(result[i], static_cast<Unicode>(0x20 + i));
    }
}

// Test BOM (U+FEFF = 0xEF 0xBB 0xBF)
TEST_F(Utf8ToUCS4Test_1524, ByteOrderMark_1524) {
    auto result = utf8ToUCS4("\xEF\xBB\xBF");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFEFFu);
}

// Test replacement character itself (U+FFFD = 0xEF 0xBF 0xBD)
TEST_F(Utf8ToUCS4Test_1524, ReplacementCharacterItself_1524) {
    auto result = utf8ToUCS4("\xEF\xBF\xBD");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFFFDu);
}

// Test incomplete sequence at end of string followed by nothing
TEST_F(Utf8ToUCS4Test_1524, IncompleteSequenceAtEnd_1524) {
    // Two-byte sequence start at end of string
    auto result = utf8ToUCS4("A\xC3");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0x41u);
    EXPECT_EQ(result[1], REPLACEMENT_CHAR);
}

// Test sequence with embedded null bytes
TEST_F(Utf8ToUCS4Test_1524, EmbeddedNulls_1524) {
    std::string_view sv("A\0B", 3);
    auto result = utf8ToUCS4(sv);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0x41u);
    EXPECT_EQ(result[1], 0x00u);
    EXPECT_EQ(result[2], 0x42u);
}

// Test long valid UTF-8 string
TEST_F(Utf8ToUCS4Test_1524, LongValidString_1524) {
    // Create a string with 1000 copies of U+00E9 (é)
    std::string input;
    for (int i = 0; i < 1000; i++) {
        input += "\xC3\xA9";
    }
    auto result = utf8ToUCS4(input);
    ASSERT_EQ(result.size(), 1000u);
    for (auto c : result) {
        EXPECT_EQ(c, 0x00E9u);
    }
}

// Test invalid leading byte 0xC0 (overlong)
TEST_F(Utf8ToUCS4Test_1524, OverlongC0_1524) {
    auto result = utf8ToUCS4("\xC0\x80");
    // Should produce replacement chars since C0 80 is overlong encoding for U+0000
    EXPECT_GE(result.size(), 1u);
    for (auto c : result) {
        EXPECT_EQ(c, REPLACEMENT_CHAR);
    }
}

// Test invalid leading byte 0xC1 (overlong)
TEST_F(Utf8ToUCS4Test_1524, OverlongC1_1524) {
    auto result = utf8ToUCS4("\xC1\xBF");
    EXPECT_GE(result.size(), 1u);
    for (auto c : result) {
        EXPECT_EQ(c, REPLACEMENT_CHAR);
    }
}

// Test surrogate half (U+D800 = 0xED 0xA0 0x80) - should be rejected
TEST_F(Utf8ToUCS4Test_1524, SurrogateHalf_1524) {
    auto result = utf8ToUCS4("\xED\xA0\x80");
    // Surrogates are not valid Unicode scalar values, decoder should reject
    EXPECT_GE(result.size(), 1u);
    // At least one replacement char expected
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == REPLACEMENT_CHAR) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test five-byte sequence (0xF8...) - invalid in modern UTF-8
TEST_F(Utf8ToUCS4Test_1524, FiveByteSequenceInvalid_1524) {
    auto result = utf8ToUCS4("\xF8\x80\x80\x80\x80");
    EXPECT_GE(result.size(), 1u);
    for (auto c : result) {
        EXPECT_EQ(c, REPLACEMENT_CHAR);
    }
}

// Test six-byte sequence (0xFC...) - invalid in modern UTF-8
TEST_F(Utf8ToUCS4Test_1524, SixByteSequenceInvalid_1524) {
    auto result = utf8ToUCS4("\xFC\x80\x80\x80\x80\x80");
    EXPECT_GE(result.size(), 1u);
    for (auto c : result) {
        EXPECT_EQ(c, REPLACEMENT_CHAR);
    }
}

// Test valid multi-codepoint emoji (family emoji)
TEST_F(Utf8ToUCS4Test_1524, MultipleFourByteCharacters_1524) {
    // Two emoji: U+1F600 U+1F601
    auto result = utf8ToUCS4("\xF0\x9F\x98\x80\xF0\x9F\x98\x81");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0x1F600u);
    EXPECT_EQ(result[1], 0x1F601u);
}
