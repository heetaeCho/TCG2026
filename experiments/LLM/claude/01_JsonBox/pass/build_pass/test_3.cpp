#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstdint>

// Reproduce the necessary types and class from the provided code
#define MASK2BYTES 0xC0
#define MASKBITS 0x3F
#define MASK6BYTES 0xFC
#define MASK5BYTES 0xF8
#define MASK1BYTE 0x80
#define MASK3BYTES 0xE0
#define MASK4BYTES 0xF0

namespace JsonBox {
    typedef std::vector<int32_t> String32;

    class Convert {
    public:
        static String32 decodeUTF8(const std::string& utf8String) {
            String32 result;
            String32::value_type tmpUnicodeChar;
            for (std::string::const_iterator i = utf8String.begin(); i < utf8String.end();) {
                if ((*i & MASK6BYTES) == MASK6BYTES) {
                    tmpUnicodeChar = ((*i & 0x01) << 30) | ((*(i + 1) & MASKBITS) << 24)
                        | ((*(i + 2) & MASKBITS) << 18) | ((*(i + 3) & MASKBITS) << 12)
                        | ((*(i + 4) & MASKBITS) << 6) | (*(i + 5) & MASKBITS);
                    i += 6;
                } else if ((*i & MASK5BYTES) == MASK5BYTES) {
                    tmpUnicodeChar = ((*i & 0x03) << 24) | ((*(i + 1) & MASKBITS) << 18)
                        | ((*(i + 2) & MASKBITS) << 12) | ((*(i + 3) & MASKBITS) << 6)
                        | (*(i + 4) & MASKBITS);
                    i += 5;
                } else if ((*i & MASK4BYTES) == MASK4BYTES) {
                    tmpUnicodeChar = ((*i & 0x07) << 18) | ((*(i + 1) & MASKBITS) << 12)
                        | ((*(i + 2) & MASKBITS) << 6) | (*(i + 3) & MASKBITS);
                    i += 4;
                } else if ((*i & MASK3BYTES) == MASK3BYTES) {
                    tmpUnicodeChar = ((*i & 0x0F) << 12) | ((*(i + 1) & MASKBITS) << 6)
                        | (*(i + 2) & MASKBITS);
                    i += 3;
                } else if ((*i & MASK2BYTES) == MASK2BYTES) {
                    tmpUnicodeChar = ((*i & 0x1F) << 6) | (*(i + 1) & MASKBITS);
                    i += 2;
                } else {
                    tmpUnicodeChar = *i;
                    i += 1;
                }
                result.push_back(tmpUnicodeChar);
            }
            return result;
        }
    };
}

class ConvertTest_3 : public ::testing::Test {
protected:
    // Helper to build a string from raw bytes
    static std::string makeString(std::initializer_list<unsigned char> bytes) {
        return std::string(bytes.begin(), bytes.end());
    }
};

// Test empty string returns empty result
TEST_F(ConvertTest_3, DecodeUTF8_EmptyString_3) {
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8("");
    EXPECT_TRUE(result.empty());
}

// Test single ASCII character (1-byte)
TEST_F(ConvertTest_3, DecodeUTF8_SingleASCII_3) {
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8("A");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x41);
}

// Test multiple ASCII characters
TEST_F(ConvertTest_3, DecodeUTF8_MultipleASCII_3) {
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8("Hello");
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 'H');
    EXPECT_EQ(result[1], 'e');
    EXPECT_EQ(result[2], 'l');
    EXPECT_EQ(result[3], 'l');
    EXPECT_EQ(result[4], 'o');
}

// Test ASCII boundary: null character (0x00)
TEST_F(ConvertTest_3, DecodeUTF8_NullCharacter_3) {
    std::string input(1, '\0');
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00);
}

// Test ASCII boundary: 0x7F (DEL, highest single-byte value)
TEST_F(ConvertTest_3, DecodeUTF8_MaxSingleByte_3) {
    std::string input(1, 0x7F);
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x7F);
}

// Test 2-byte UTF-8 sequence: U+0080 (0xC2 0x80)
TEST_F(ConvertTest_3, DecodeUTF8_TwoByte_MinValue_3) {
    std::string input = makeString({0xC2, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0080);
}

// Test 2-byte UTF-8 sequence: U+00E9 (é) -> 0xC3 0xA9
TEST_F(ConvertTest_3, DecodeUTF8_TwoByte_EAccent_3) {
    std::string input = makeString({0xC3, 0xA9});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00E9);
}

// Test 2-byte UTF-8 sequence: U+07FF (max 2-byte) -> 0xDF 0xBF
TEST_F(ConvertTest_3, DecodeUTF8_TwoByte_MaxValue_3) {
    std::string input = makeString({0xDF, 0xBF});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x07FF);
}

// Test 3-byte UTF-8 sequence: U+0800 (min 3-byte) -> 0xE0 0xA0 0x80
TEST_F(ConvertTest_3, DecodeUTF8_ThreeByte_MinValue_3) {
    std::string input = makeString({0xE0, 0xA0, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0800);
}

// Test 3-byte UTF-8 sequence: U+FFFF (max 3-byte) -> 0xEF 0xBF 0xBF
TEST_F(ConvertTest_3, DecodeUTF8_ThreeByte_MaxValue_3) {
    std::string input = makeString({0xEF, 0xBF, 0xBF});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFFFF);
}

// Test 3-byte UTF-8 sequence: Euro sign U+20AC -> 0xE2 0x82 0xAC
TEST_F(ConvertTest_3, DecodeUTF8_ThreeByte_EuroSign_3) {
    std::string input = makeString({0xE2, 0x82, 0xAC});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x20AC);
}

// Test 4-byte UTF-8 sequence: U+10000 (min 4-byte) -> 0xF0 0x90 0x80 0x80
TEST_F(ConvertTest_3, DecodeUTF8_FourByte_MinValue_3) {
    std::string input = makeString({0xF0, 0x90, 0x80, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x10000);
}

// Test 4-byte UTF-8 sequence: U+1F600 (😀) -> 0xF0 0x9F 0x98 0x80
TEST_F(ConvertTest_3, DecodeUTF8_FourByte_Emoji_3) {
    std::string input = makeString({0xF0, 0x9F, 0x98, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x1F600);
}

// Test 4-byte UTF-8 sequence: U+10FFFF (max valid Unicode) -> 0xF4 0x8F 0xBF 0xBF
TEST_F(ConvertTest_3, DecodeUTF8_FourByte_MaxUnicode_3) {
    std::string input = makeString({0xF4, 0x8F, 0xBF, 0xBF});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x10FFFF);
}

// Test 5-byte UTF-8 sequence: 0xF8 0x80 0x80 0x80 0x80 -> should decode
TEST_F(ConvertTest_3, DecodeUTF8_FiveByte_3) {
    std::string input = makeString({0xF8, 0x80, 0x80, 0x80, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00000000);
}

// Test 5-byte UTF-8 sequence with some data bits set
TEST_F(ConvertTest_3, DecodeUTF8_FiveByte_WithData_3) {
    // 0xFB = 11111011, so data bits = 0x03 -> (0x03 << 24)
    // continuation bytes all 0x80 -> no additional bits
    std::string input = makeString({0xFB, 0x80, 0x80, 0x80, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x03000000);
}

// Test 6-byte UTF-8 sequence: 0xFC 0x80 0x80 0x80 0x80 0x80 -> should decode
TEST_F(ConvertTest_3, DecodeUTF8_SixByte_3) {
    std::string input = makeString({0xFC, 0x80, 0x80, 0x80, 0x80, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x00000000);
}

// Test 6-byte UTF-8 sequence with data bits
TEST_F(ConvertTest_3, DecodeUTF8_SixByte_WithData_3) {
    // 0xFD = 11111101, data bit = 0x01 -> (0x01 << 30)
    // continuation bytes 0x80 -> no additional data
    std::string input = makeString({0xFD, 0x80, 0x80, 0x80, 0x80, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x40000000);
}

// Test mixed ASCII and multi-byte characters
TEST_F(ConvertTest_3, DecodeUTF8_MixedASCIIAndMultiByte_3) {
    // "Héllo" where é is U+00E9 (0xC3 0xA9)
    std::string input = "H";
    input += makeString({0xC3, 0xA9});
    input += "llo";
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 'H');
    EXPECT_EQ(result[1], 0x00E9);
    EXPECT_EQ(result[2], 'l');
    EXPECT_EQ(result[3], 'l');
    EXPECT_EQ(result[4], 'o');
}

// Test multiple multi-byte characters in sequence
TEST_F(ConvertTest_3, DecodeUTF8_MultipleMultiByteChars_3) {
    // U+00E9 (2-byte) + U+20AC (3-byte) + U+1F600 (4-byte)
    std::string input;
    input += makeString({0xC3, 0xA9});          // é
    input += makeString({0xE2, 0x82, 0xAC});    // €
    input += makeString({0xF0, 0x9F, 0x98, 0x80}); // 😀
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0x00E9);
    EXPECT_EQ(result[1], 0x20AC);
    EXPECT_EQ(result[2], 0x1F600);
}

// Test string with only 2-byte characters
TEST_F(ConvertTest_3, DecodeUTF8_AllTwoByteChars_3) {
    // U+00C0 (À) -> 0xC3 0x80, U+00FF (ÿ) -> 0xC3 0xBF
    std::string input = makeString({0xC3, 0x80, 0xC3, 0xBF});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0x00C0);
    EXPECT_EQ(result[1], 0x00FF);
}

// Test single character at ASCII space (0x20)
TEST_F(ConvertTest_3, DecodeUTF8_Space_3) {
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(" ");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x20);
}

// Test CJK character: U+4E2D (中) -> 0xE4 0xB8 0xAD
TEST_F(ConvertTest_3, DecodeUTF8_CJKCharacter_3) {
    std::string input = makeString({0xE4, 0xB8, 0xAD});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x4E2D);
}

// Test long ASCII string
TEST_F(ConvertTest_3, DecodeUTF8_LongASCIIString_3) {
    std::string input(1000, 'x');
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1000u);
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], 'x');
    }
}

// Test that character count differs from byte count for multi-byte strings
TEST_F(ConvertTest_3, DecodeUTF8_CharCountDiffersFromByteCount_3) {
    // 3 characters encoded as: 1 + 2 + 3 = 6 bytes
    std::string input;
    input += 'A';                              // 1 byte
    input += makeString({0xC3, 0xA9});          // 2 bytes (é)
    input += makeString({0xE2, 0x82, 0xAC});    // 3 bytes (€)
    ASSERT_EQ(input.size(), 6u);
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 3u);
}

// Test 2-byte boundary value: U+0080 -> 0xC2 0x80
TEST_F(ConvertTest_3, DecodeUTF8_TwoByteBoundaryLow_3) {
    std::string input = makeString({0xC2, 0x80});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x80);
}

// Test return type is correct (vector with proper values)
TEST_F(ConvertTest_3, DecodeUTF8_ReturnTypeConsistency_3) {
    std::string input = "AB";
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result.at(0), 0x41);
    EXPECT_EQ(result.at(1), 0x42);
}

// Test 4-byte max value: 0xF7 0xBF 0xBF 0xBF -> U+1FFFFF
TEST_F(ConvertTest_3, DecodeUTF8_FourByte_MaxEncodable_3) {
    std::string input = makeString({0xF7, 0xBF, 0xBF, 0xBF});
    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x1FFFFF);
}

// Test combination of all byte-length encodings
TEST_F(ConvertTest_3, DecodeUTF8_AllByteLengths_3) {
    std::string input;
    input += makeString({0x41});                                    // 1-byte: 'A'
    input += makeString({0xC3, 0xA9});                              // 2-byte: é
    input += makeString({0xE2, 0x82, 0xAC});                        // 3-byte: €
    input += makeString({0xF0, 0x9F, 0x98, 0x80});                  // 4-byte: 😀
    input += makeString({0xF8, 0x80, 0x80, 0x80, 0x80});            // 5-byte
    input += makeString({0xFC, 0x80, 0x80, 0x80, 0x80, 0x80});      // 6-byte

    JsonBox::String32 result = JsonBox::Convert::decodeUTF8(input);
    ASSERT_EQ(result.size(), 6u);
    EXPECT_EQ(result[0], 0x41);
    EXPECT_EQ(result[1], 0x00E9);
    EXPECT_EQ(result[2], 0x20AC);
    EXPECT_EQ(result[3], 0x1F600);
    EXPECT_EQ(result[4], 0x00);
    EXPECT_EQ(result[5], 0x00);
}
