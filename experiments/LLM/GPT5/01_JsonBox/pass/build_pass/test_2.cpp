// File: Convert_encodeToUTF8_Test.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstdint>

// Assuming the real project provides this header with the class in namespace JsonBox.
#include "JsonBox/Convert.h"

using JsonBox::Convert;
using JsonBox::String32;

class ConvertTest_2 : public ::testing::Test {
protected:
    Convert conv;
    // Helper to build std::string from raw bytes safely (including 0x00 if present).
    static std::string Bytes(const std::initializer_list<unsigned char>& b) {
        return std::string(reinterpret_cast<const char*>(b.begin()), b.size());
    }
};

// --- Normal operation ---

TEST_F(ConvertTest_2, Encode_EmptyInput_ReturnsEmpty_2) {
    String32 in{};
    std::string out = conv.encodeToUTF8(in);
    EXPECT_TRUE(out.empty());
}

TEST_F(ConvertTest_2, Encode_ASCII_RoundTripVisibleBytes_2) {
    String32 in{ 'A', 'z', '0', ' ', '!' }; // All < 0x80
    std::string out = conv.encodeToUTF8(in);
    EXPECT_EQ(out, std::string("Az0 !"));
}

TEST_F(ConvertTest_2, Encode_Mixed_ASCII_3Byte_4Byte_2) {
    // Mix: 'H','i', U+20AC (Euro sign), U+1F600 (GRINNING FACE)
    String32 in{ 'H', 'i', 0x20AC, 0x1F600 };
    std::string out = conv.encodeToUTF8(in);

    // Expected UTF-8 bytes:
    // 'H'        -> 0x48
    // 'i'        -> 0x69
    // U+20AC     -> 0xE2 0x82 0xAC
    // U+1F600    -> 0xF0 0x9F 0x98 0x80
    std::string expected = Bytes({0x48,0x69, 0xE2,0x82,0xAC, 0xF0,0x9F,0x98,0x80});
    EXPECT_EQ(out, expected);
}

// --- Boundary conditions for standard UTF-8 ranges ---

TEST_F(ConvertTest_2, Encode_OneByteBoundary_007F_2) {
    // U+007F (DEL) is still 1 byte in UTF-8
    String32 in{ 0x7F };
    std::string out = conv.encodeToUTF8(in);
    std::string expected = Bytes({0x7F});
    EXPECT_EQ(out, expected);
}

TEST_F(ConvertTest_2, Encode_TwoByte_LowerAndUpperBounds_0080_07FF_2) {
    // U+0080  -> 0xC2 0x80
    // U+07FF  -> 0xDF 0xBF
    String32 in{ 0x0080, 0x07FF };
    std::string out = conv.encodeToUTF8(in);
    std::string expected = Bytes({0xC2,0x80, 0xDF,0xBF});
    EXPECT_EQ(out, expected);
}

TEST_F(ConvertTest_2, Encode_ThreeByte_LowerAndUpperBounds_0800_FFFF_2) {
    // U+0800  -> 0xE0 0xA0 0x80
    // U+FFFF  -> 0xEF 0xBF 0xBF
    String32 in{ 0x0800, 0xFFFF };
    std::string out = conv.encodeToUTF8(in);
    std::string expected = Bytes({0xE0,0xA0,0x80, 0xEF,0xBF,0xBF});
    EXPECT_EQ(out, expected);
}

TEST_F(ConvertTest_2, Encode_FourByte_LowerAndUpperBounds_10000_10FFFF_2) {
    // U+10000 -> 0xF0 0x90 0x80 0x80
    // U+10FFFF-> 0xF4 0x8F 0xBF 0xBF
    String32 in{ 0x10000, 0x10FFFF };
    std::string out = conv.encodeToUTF8(in);
    std::string expected = Bytes({0xF0,0x90,0x80,0x80, 0xF4,0x8F,0xBF,0xBF});
    EXPECT_EQ(out, expected);
}

// --- Exceptional / out-of-spec inputs (observable behavior only) ---

TEST_F(ConvertTest_2, Encode_InvalidCodepoint_BeyondUnicodeRange_DoesNotCrash_2) {
    // Values above U+10FFFF are outside Unicode; we only verify that the function
    // handles them without crashing and returns *some* bytes (black-box behavior).
    String32 in{ 0x110000, 0x200000, 0x4000000 };
    std::string out = conv.encodeToUTF8(in);

    // Observable expectations only: output is not empty and length >= number of code points.
    // (Each code point should produce at least one byte.)
    EXPECT_FALSE(out.empty());
    EXPECT_GE(out.size(), in.size());
}

// --- Multi-code-point sequencing ---

TEST_F(ConvertTest_2, Encode_ConcatenationAcrossBoundaries_PreservesOrder_2) {
    // Sequence across 1-, 2-, 3-, and 4-byte regions.
    String32 in{ 0x41,        // 'A'
                 0x07FF,      // 2-byte upper bound
                 0x0800,      // 3-byte lower bound
                 0x1F642 };   // 🙂 (SLIGHTLY SMILING FACE)
    std::string out = conv.encodeToUTF8(in);

    std::string expected = Bytes({
        0x41,                 // 'A'
        0xDF,0xBF,            // U+07FF
        0xE0,0xA0,0x80,       // U+0800
        0xF0,0x9F,0x99,0x82   // U+1F642
    });

    EXPECT_EQ(out, expected);
}
