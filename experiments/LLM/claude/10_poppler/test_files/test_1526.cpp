#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class Utf8ToUtf16Test_1526 : public ::testing::Test {
protected:
};

// Test empty string input
TEST_F(Utf8ToUtf16Test_1526, EmptyString_1526) {
    std::u16string result = utf8ToUtf16("");
    EXPECT_TRUE(result.empty());
}

// Test simple ASCII string
TEST_F(Utf8ToUtf16Test_1526, SimpleAscii_1526) {
    std::u16string result = utf8ToUtf16("Hello");
    std::u16string expected = u"Hello";
    EXPECT_EQ(result, expected);
}

// Test single ASCII character
TEST_F(Utf8ToUtf16Test_1526, SingleAsciiChar_1526) {
    std::u16string result = utf8ToUtf16("A");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], u'A');
}

// Test null character in string
TEST_F(Utf8ToUtf16Test_1526, NullCharacter_1526) {
    std::string input("\0", 1);
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], u'\0');
}

// Test UTF-8 BOM is stripped
TEST_F(Utf8ToUtf16Test_1526, Utf8BomIsStripped_1526) {
    std::string input = "\xEF\xBB\xBF" "Hello";
    std::u16string result = utf8ToUtf16(input);
    std::u16string expected = u"Hello";
    EXPECT_EQ(result, expected);
}

// Test BOM only (no content after BOM)
TEST_F(Utf8ToUtf16Test_1526, BomOnly_1526) {
    std::string input = "\xEF\xBB\xBF";
    std::u16string result = utf8ToUtf16(input);
    EXPECT_TRUE(result.empty());
}

// Test 2-byte UTF-8 character (e.g., ñ = U+00F1)
TEST_F(Utf8ToUtf16Test_1526, TwoByteUtf8_1526) {
    std::string input = "\xC3\xB1"; // ñ
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00F1);
}

// Test 3-byte UTF-8 character (e.g., € = U+20AC)
TEST_F(Utf8ToUtf16Test_1526, ThreeByteUtf8_1526) {
    std::string input = "\xE2\x82\xAC"; // €
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x20AC);
}

// Test 4-byte UTF-8 character (supplementary plane, requires surrogate pair)
// U+1F600 (😀) = UTF-8: F0 9F 98 80
TEST_F(Utf8ToUtf16Test_1526, FourByteUtf8SurrogatePair_1526) {
    std::string input = "\xF0\x9F\x98\x80"; // U+1F600
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 2u);
    // U+1F600: high surrogate = 0xD83D, low surrogate = 0xDE00
    EXPECT_EQ(result[0], 0xD83D);
    EXPECT_EQ(result[1], 0xDE00);
}

// Test another supplementary character U+10000 (first supplementary)
TEST_F(Utf8ToUtf16Test_1526, FirstSupplementaryChar_1526) {
    std::string input = "\xF0\x90\x80\x80"; // U+10000
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 2u);
    // U+10000: high surrogate = 0xD800, low surrogate = 0xDC00
    EXPECT_EQ(result[0], 0xD800);
    EXPECT_EQ(result[1], 0xDC00);
}

// Test U+10FFFF (max valid Unicode codepoint)
TEST_F(Utf8ToUtf16Test_1526, MaxValidCodepoint_1526) {
    std::string input = "\xF4\x8F\xBF\xBF"; // U+10FFFF
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 2u);
    // U+10FFFF: high surrogate = 0xDBFF, low surrogate = 0xDFFF
    EXPECT_EQ(result[0], 0xDBFF);
    EXPECT_EQ(result[1], 0xDFFF);
}

// Test invalid UTF-8 sequence (continuation byte without start)
TEST_F(Utf8ToUtf16Test_1526, InvalidContinuationByte_1526) {
    std::string input = "\x80"; // lone continuation byte
    std::u16string result = utf8ToUtf16(input);
    // Should produce replacement character(s)
    EXPECT_FALSE(result.empty());
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test truncated 2-byte sequence
TEST_F(Utf8ToUtf16Test_1526, Truncated2ByteSequence_1526) {
    std::string input = "\xC3"; // start of 2-byte, missing continuation
    std::u16string result = utf8ToUtf16(input);
    EXPECT_FALSE(result.empty());
    // Should contain replacement character
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test truncated 3-byte sequence
TEST_F(Utf8ToUtf16Test_1526, Truncated3ByteSequence_1526) {
    std::string input = "\xE2\x82"; // start of 3-byte, missing last continuation
    std::u16string result = utf8ToUtf16(input);
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test truncated 4-byte sequence
TEST_F(Utf8ToUtf16Test_1526, Truncated4ByteSequence_1526) {
    std::string input = "\xF0\x9F\x98"; // start of 4-byte, missing last byte
    std::u16string result = utf8ToUtf16(input);
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test mixed valid and invalid sequences
TEST_F(Utf8ToUtf16Test_1526, MixedValidAndInvalid_1526) {
    std::string input = "A\x80" "B"; // A, invalid, B
    std::u16string result = utf8ToUtf16(input);
    // Should contain 'A', replacement char, 'B'
    bool hasA = false, hasB = false, hasReplacement = false;
    for (auto c : result) {
        if (c == u'A') hasA = true;
        if (c == u'B') hasB = true;
        if (c == 0xFFFD) hasReplacement = true;
    }
    EXPECT_TRUE(hasA);
    EXPECT_TRUE(hasB);
    EXPECT_TRUE(hasReplacement);
}

// Test all ASCII printable characters
TEST_F(Utf8ToUtf16Test_1526, AllAsciiPrintable_1526) {
    std::string input;
    for (char c = 0x20; c < 0x7F; ++c) {
        input += c;
    }
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        EXPECT_EQ(result[i], static_cast<char16_t>(input[i]));
    }
}

// Test boundary: U+007F (last single-byte character)
TEST_F(Utf8ToUtf16Test_1526, LastSingleByte_1526) {
    std::string input = "\x7F";
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x007F);
}

// Test boundary: U+0080 (first 2-byte character)
TEST_F(Utf8ToUtf16Test_1526, FirstTwoByte_1526) {
    std::string input = "\xC2\x80"; // U+0080
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0080);
}

// Test boundary: U+07FF (last 2-byte character)
TEST_F(Utf8ToUtf16Test_1526, LastTwoByte_1526) {
    std::string input = "\xDF\xBF"; // U+07FF
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x07FF);
}

// Test boundary: U+0800 (first 3-byte character)
TEST_F(Utf8ToUtf16Test_1526, FirstThreeByte_1526) {
    std::string input = "\xE0\xA0\x80"; // U+0800
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0800);
}

// Test boundary: U+FFFF (last BMP character)
TEST_F(Utf8ToUtf16Test_1526, LastBmpChar_1526) {
    std::string input = "\xEF\xBF\xBF"; // U+FFFF
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFFFF);
}

// Test multiple 4-byte characters
TEST_F(Utf8ToUtf16Test_1526, MultipleFourByteChars_1526) {
    // U+1F600 U+1F601
    std::string input = "\xF0\x9F\x98\x80\xF0\x9F\x98\x81";
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 4u); // two surrogate pairs
}

// Test 0xFE and 0xFF bytes (never valid in UTF-8)
TEST_F(Utf8ToUtf16Test_1526, InvalidBytes_FE_FF_1526) {
    std::string input = "\xFE\xFF";
    std::u16string result = utf8ToUtf16(input);
    // Should produce replacement characters
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test overlong encoding (2-byte encoding of U+002F '/')
TEST_F(Utf8ToUtf16Test_1526, OverlongEncoding_1526) {
    std::string input = "\xC0\xAF"; // overlong encoding of '/'
    std::u16string result = utf8ToUtf16(input);
    // Should produce replacement character(s), not '/'
    bool hasSlash = false;
    for (auto c : result) {
        if (c == u'/') {
            hasSlash = true;
        }
    }
    // Overlong sequences should be rejected
    bool hasReplacement = false;
    for (auto c : result) {
        if (c == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test string with BOM followed by multi-byte characters
TEST_F(Utf8ToUtf16Test_1526, BomWithMultiByteContent_1526) {
    std::string input = "\xEF\xBB\xBF\xC3\xB1"; // BOM + ñ
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00F1);
}

// Test long ASCII string
TEST_F(Utf8ToUtf16Test_1526, LongAsciiString_1526) {
    std::string input(1000, 'x');
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1000u);
    for (auto c : result) {
        EXPECT_EQ(c, u'x');
    }
}

// Test CJK character (U+4E2D, 中)
TEST_F(Utf8ToUtf16Test_1526, CjkCharacter_1526) {
    std::string input = "\xE4\xB8\xAD"; // U+4E2D
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x4E2D);
}

// Test sequence ending with incomplete multibyte at the end
TEST_F(Utf8ToUtf16Test_1526, ValidThenIncompleteAtEnd_1526) {
    std::string input = "A\xC3"; // 'A' followed by incomplete 2-byte
    std::u16string result = utf8ToUtf16(input);
    EXPECT_GE(result.size(), 2u);
    EXPECT_EQ(result[0], u'A');
    // The incomplete sequence should produce a replacement
    bool hasReplacement = false;
    for (size_t i = 1; i < result.size(); ++i) {
        if (result[i] == 0xFFFD) {
            hasReplacement = true;
        }
    }
    EXPECT_TRUE(hasReplacement);
}

// Test U+FEFF (BOM character encoded in content, not at start)
TEST_F(Utf8ToUtf16Test_1526, BomCharInMiddle_1526) {
    std::string input = "A\xEF\xBB\xBF" "B"; // A + BOM char + B
    std::u16string result = utf8ToUtf16(input);
    // BOM in the middle should be preserved as U+FEFF
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], u'A');
    EXPECT_EQ(result[1], 0xFEFF);
    EXPECT_EQ(result[2], u'B');
}

// Test replacement character U+FFFD in input
TEST_F(Utf8ToUtf16Test_1526, ReplacementCharInInput_1526) {
    std::string input = "\xEF\xBF\xBD"; // U+FFFD in UTF-8
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFFFD);
}

// Test musical symbol (U+1D11E, 𝄞) - 4-byte UTF-8
TEST_F(Utf8ToUtf16Test_1526, MusicalSymbol_1526) {
    std::string input = "\xF0\x9D\x84\x9E"; // U+1D11E
    std::u16string result = utf8ToUtf16(input);
    EXPECT_EQ(result.size(), 2u);
    // U+1D11E: high surrogate = 0xD834, low surrogate = 0xDD1E
    EXPECT_EQ(result[0], 0xD834);
    EXPECT_EQ(result[1], 0xDD1E);
}
