#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers
#include "UnicodeConversions.hpp"

// We need to handle the UC_Throw / XMP_Error mechanism
// Include XMP headers that define the exception type
#include "XMP_Const.h"

// Forward declaration of the function under test
extern void FromUTF16(const UTF16Unit* utf16In, size_t utf16Len, std::string* utf8Str, bool bigEndian);

class FromUTF16Test_2058 : public ::testing::Test {
protected:
    std::string utf8Result;
};

// Test: Empty input produces empty output (Big Endian)
TEST_F(FromUTF16Test_2058, EmptyInputBigEndian_2058) {
    const UTF16Unit* emptyInput = nullptr;
    FromUTF16(emptyInput, 0, &utf8Result, true);
    EXPECT_TRUE(utf8Result.empty());
}

// Test: Empty input produces empty output (Little Endian)
TEST_F(FromUTF16Test_2058, EmptyInputLittleEndian_2058) {
    const UTF16Unit* emptyInput = nullptr;
    FromUTF16(emptyInput, 0, &utf8Result, false);
    EXPECT_TRUE(utf8Result.empty());
}

// Test: Single ASCII character in Big Endian UTF-16
TEST_F(FromUTF16Test_2058, SingleAsciiCharBigEndian_2058) {
    // 'A' = U+0041, Big Endian: 0x00 0x41
    UTF16Unit input[] = { 0x0041 };
    // For big endian, the byte order should be 0x00 0x41
    // On a little-endian system, we need to swap bytes
    UTF16Unit beBuf[1];
    beBuf[0] = (0x00 << 8) | 0x41; // 0x0041 in big endian representation
    // Actually, the function takes UTF16Unit values and interprets them based on bigEndian flag
    // For big endian: bytes are [high_byte, low_byte] in memory
    // UTF16Unit is typically uint16_t
    // We store raw bytes: 0x00 0x41 for 'A' in BE
    unsigned char rawBE[] = { 0x00, 0x41 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 1, &utf8Result, true);
    EXPECT_EQ(utf8Result, "A");
}

// Test: Single ASCII character in Little Endian UTF-16
TEST_F(FromUTF16Test_2058, SingleAsciiCharLittleEndian_2058) {
    // 'A' = U+0041, Little Endian: 0x41 0x00
    unsigned char rawLE[] = { 0x41, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    EXPECT_EQ(utf8Result, "A");
}

// Test: Multiple ASCII characters in Little Endian
TEST_F(FromUTF16Test_2058, MultipleAsciiCharsLittleEndian_2058) {
    // "Hello" in UTF-16 LE
    unsigned char rawLE[] = {
        0x48, 0x00,  // H
        0x65, 0x00,  // e
        0x6C, 0x00,  // l
        0x6C, 0x00,  // l
        0x6F, 0x00   // o
    };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 5, &utf8Result, false);
    EXPECT_EQ(utf8Result, "Hello");
}

// Test: Multiple ASCII characters in Big Endian
TEST_F(FromUTF16Test_2058, MultipleAsciiCharsBigEndian_2058) {
    // "Hello" in UTF-16 BE
    unsigned char rawBE[] = {
        0x00, 0x48,  // H
        0x00, 0x65,  // e
        0x00, 0x6C,  // l
        0x00, 0x6C,  // l
        0x00, 0x6F   // o
    };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 5, &utf8Result, true);
    EXPECT_EQ(utf8Result, "Hello");
}

// Test: Non-ASCII BMP character (e.g., U+00E9 'é') in Little Endian
TEST_F(FromUTF16Test_2058, NonAsciiBMPCharLittleEndian_2058) {
    // U+00E9 in UTF-16 LE: 0xE9 0x00
    unsigned char rawLE[] = { 0xE9, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    // U+00E9 in UTF-8: 0xC3 0xA9
    std::string expected("\xC3\xA9");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Non-ASCII BMP character in Big Endian
TEST_F(FromUTF16Test_2058, NonAsciiBMPCharBigEndian_2058) {
    // U+00E9 in UTF-16 BE: 0x00 0xE9
    unsigned char rawBE[] = { 0x00, 0xE9 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 1, &utf8Result, true);
    std::string expected("\xC3\xA9");
    EXPECT_EQ(utf8Result, expected);
}

// Test: CJK character U+4E2D (中) in Little Endian
TEST_F(FromUTF16Test_2058, CJKCharacterLittleEndian_2058) {
    // U+4E2D in UTF-16 LE: 0x2D 0x4E
    unsigned char rawLE[] = { 0x2D, 0x4E };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    // U+4E2D in UTF-8: 0xE4 0xB8 0xAD
    std::string expected("\xE4\xB8\xAD");
    EXPECT_EQ(utf8Result, expected);
}

// Test: CJK character U+4E2D (中) in Big Endian
TEST_F(FromUTF16Test_2058, CJKCharacterBigEndian_2058) {
    // U+4E2D in UTF-16 BE: 0x4E 0x2D
    unsigned char rawBE[] = { 0x4E, 0x2D };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 1, &utf8Result, true);
    std::string expected("\xE4\xB8\xAD");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Surrogate pair (U+10000, first supplementary character) in Little Endian
TEST_F(FromUTF16Test_2058, SurrogatePairLittleEndian_2058) {
    // U+10000 => surrogate pair: high = 0xD800, low = 0xDC00
    // UTF-16 LE: 0x00 0xD8, 0x00 0xDC
    unsigned char rawLE[] = { 0x00, 0xD8, 0x00, 0xDC };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 2, &utf8Result, false);
    // U+10000 in UTF-8: 0xF0 0x90 0x80 0x80
    std::string expected("\xF0\x90\x80\x80");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Surrogate pair (U+10000) in Big Endian
TEST_F(FromUTF16Test_2058, SurrogatePairBigEndian_2058) {
    // U+10000 => surrogate pair: high = 0xD800, low = 0xDC00
    // UTF-16 BE: 0xD8 0x00, 0xDC 0x00
    unsigned char rawBE[] = { 0xD8, 0x00, 0xDC, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 2, &utf8Result, true);
    std::string expected("\xF0\x90\x80\x80");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Surrogate pair for emoji U+1F600 (😀) in Little Endian
TEST_F(FromUTF16Test_2058, EmojiSurrogatePairLittleEndian_2058) {
    // U+1F600 => high = 0xD83D, low = 0xDE00
    // UTF-16 LE: 0x3D 0xD8, 0x00 0xDE
    unsigned char rawLE[] = { 0x3D, 0xD8, 0x00, 0xDE };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 2, &utf8Result, false);
    // U+1F600 in UTF-8: 0xF0 0x9F 0x98 0x80
    std::string expected("\xF0\x9F\x98\x80");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Mixed ASCII and non-ASCII in Little Endian
TEST_F(FromUTF16Test_2058, MixedContentLittleEndian_2058) {
    // "Aé" in UTF-16 LE: A=0x41 0x00, é=0xE9 0x00
    unsigned char rawLE[] = { 0x41, 0x00, 0xE9, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 2, &utf8Result, false);
    std::string expected("A\xC3\xA9");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Previous result is erased before new conversion
TEST_F(FromUTF16Test_2058, PreviousResultIsErased_2058) {
    utf8Result = "some previous content";
    unsigned char rawLE[] = { 0x42, 0x00 }; // 'B'
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    EXPECT_EQ(utf8Result, "B");
}

// Test: Incomplete surrogate (lone high surrogate) should throw
TEST_F(FromUTF16Test_2058, LoneHighSurrogateThrows_2058) {
    // High surrogate 0xD800 alone, LE: 0x00 0xD8
    unsigned char rawLE[] = { 0x00, 0xD8 };
    // This should cause an error because the surrogate is incomplete
    // The function throws via UC_Throw with kXMPErr_BadXML or similar
    EXPECT_ANY_THROW(
        FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false)
    );
}

// Test: Single character length=1 in LE
TEST_F(FromUTF16Test_2058, SingleUnitLength_2058) {
    unsigned char rawLE[] = { 0x20, 0x00 }; // space
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    EXPECT_EQ(utf8Result, " ");
}

// Test: Large BMP value U+FFFD (replacement character) in Big Endian
TEST_F(FromUTF16Test_2058, ReplacementCharBigEndian_2058) {
    // U+FFFD in UTF-16 BE: 0xFF 0xFD
    unsigned char rawBE[] = { 0xFF, 0xFD };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 1, &utf8Result, true);
    // U+FFFD in UTF-8: 0xEF 0xBF 0xBD
    std::string expected("\xEF\xBF\xBD");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Null character U+0000 in Little Endian
TEST_F(FromUTF16Test_2058, NullCharacterLittleEndian_2058) {
    unsigned char rawLE[] = { 0x00, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    // U+0000 should produce a null byte in UTF-8
    EXPECT_EQ(utf8Result.size(), 1u);
    EXPECT_EQ(utf8Result[0], '\0');
}

// Test: Multiple surrogate pairs in sequence (Big Endian)
TEST_F(FromUTF16Test_2058, MultipleSurrogatePairsBigEndian_2058) {
    // U+10000 and U+10001
    // U+10000: D800 DC00, U+10001: D800 DC01
    unsigned char rawBE[] = {
        0xD8, 0x00, 0xDC, 0x00,  // U+10000
        0xD8, 0x00, 0xDC, 0x01   // U+10001
    };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 4, &utf8Result, true);
    // U+10000: F0 90 80 80, U+10001: F0 90 80 81
    std::string expected("\xF0\x90\x80\x80\xF0\x90\x80\x81");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Verify output string is not empty for valid input
TEST_F(FromUTF16Test_2058, OutputNotEmptyForValidInput_2058) {
    unsigned char rawLE[] = { 0x58, 0x00 }; // 'X'
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    EXPECT_FALSE(utf8Result.empty());
}

// Test: Two-byte UTF-8 range character U+0080 in LE
TEST_F(FromUTF16Test_2058, TwoByteUTF8RangeCharLE_2058) {
    // U+0080 in UTF-16 LE: 0x80 0x00
    unsigned char rawLE[] = { 0x80, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 1, &utf8Result, false);
    // U+0080 in UTF-8: 0xC2 0x80
    std::string expected("\xC2\x80");
    EXPECT_EQ(utf8Result, expected);
}

// Test: Three-byte UTF-8 range character U+0800 in BE
TEST_F(FromUTF16Test_2058, ThreeByteUTF8RangeCharBE_2058) {
    // U+0800 in UTF-16 BE: 0x08 0x00
    unsigned char rawBE[] = { 0x08, 0x00 };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawBE), 1, &utf8Result, true);
    // U+0800 in UTF-8: 0xE0 0xA0 0x80
    std::string expected("\xE0\xA0\x80");
    EXPECT_EQ(utf8Result, expected);
}

// Test: String with ASCII characters and surrogate pair mixed in LE
TEST_F(FromUTF16Test_2058, MixedAsciiAndSurrogatePairLE_2058) {
    // "A" + U+1F600 + "B"
    // A: 0x41 0x00
    // U+1F600: 0x3D 0xD8 0x00 0xDE
    // B: 0x42 0x00
    unsigned char rawLE[] = {
        0x41, 0x00,
        0x3D, 0xD8, 0x00, 0xDE,
        0x42, 0x00
    };
    FromUTF16(reinterpret_cast<const UTF16Unit*>(rawLE), 4, &utf8Result, false);
    std::string expected("A\xF0\x9F\x98\x80""B");
    EXPECT_EQ(utf8Result, expected);
}
