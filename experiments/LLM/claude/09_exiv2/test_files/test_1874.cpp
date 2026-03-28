#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <stdexcept>

// Include necessary XMP SDK headers
#include "XMP_Environment.h"
#include "XMP_Const.h"

// We need the Unicode conversion utilities
#include "UnicodeConversions.hpp"

// Include the file under test
#include "UnicodeInlines.incl_cpp"

class GetCodePointTest_1874 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: ASCII single byte character 'A' (0x41)
TEST_F(GetCodePointTest_1874, SingleByteASCII_A_1874) {
    XMP_Uns8 utf8[] = { 0x41, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x41u);
    EXPECT_EQ(ptr, utf8 + 1);
}

// Test: ASCII null character (0x00 is technically valid single byte)
TEST_F(GetCodePointTest_1874, SingleByteASCII_NullChar_1874) {
    XMP_Uns8 utf8[] = { 0x00, 0x00, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    // Depending on implementation, null byte might be valid or throw
    try {
        XMP_Uns32 cp = GetCodePoint(&ptr);
        EXPECT_EQ(cp, 0x00u);
        EXPECT_EQ(ptr, utf8 + 1);
    } catch (...) {
        // If implementation rejects null, that's acceptable behavior
        EXPECT_EQ(ptr, utf8); // pointer shouldn't advance on error
    }
}

// Test: ASCII character at boundary (0x7F - DEL, last single byte)
TEST_F(GetCodePointTest_1874, SingleByteASCII_MaxBound_1874) {
    XMP_Uns8 utf8[] = { 0x7F, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x7Fu);
    EXPECT_EQ(ptr, utf8 + 1);
}

// Test: Two-byte UTF-8 character (U+00C9 = É = 0xC3 0xA9)
TEST_F(GetCodePointTest_1874, TwoByteCharacter_EAcute_1874) {
    XMP_Uns8 utf8[] = { 0xC3, 0xA9, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x00E9u); // U+00E9 = é
    EXPECT_EQ(ptr, utf8 + 2);
}

// Test: Two-byte UTF-8 minimum (U+0080 = 0xC2 0x80)
TEST_F(GetCodePointTest_1874, TwoByteCharacter_Min_1874) {
    XMP_Uns8 utf8[] = { 0xC2, 0x80, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x0080u);
    EXPECT_EQ(ptr, utf8 + 2);
}

// Test: Two-byte UTF-8 maximum (U+07FF = 0xDF 0xBF)
TEST_F(GetCodePointTest_1874, TwoByteCharacter_Max_1874) {
    XMP_Uns8 utf8[] = { 0xDF, 0xBF, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x07FFu);
    EXPECT_EQ(ptr, utf8 + 2);
}

// Test: Three-byte UTF-8 character (U+20AC = € = 0xE2 0x82 0xAC)
TEST_F(GetCodePointTest_1874, ThreeByteCharacter_EuroSign_1874) {
    XMP_Uns8 utf8[] = { 0xE2, 0x82, 0xAC, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x20ACu);
    EXPECT_EQ(ptr, utf8 + 3);
}

// Test: Three-byte UTF-8 minimum (U+0800 = 0xE0 0xA0 0x80)
TEST_F(GetCodePointTest_1874, ThreeByteCharacter_Min_1874) {
    XMP_Uns8 utf8[] = { 0xE0, 0xA0, 0x80, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x0800u);
    EXPECT_EQ(ptr, utf8 + 3);
}

// Test: Four-byte UTF-8 character (U+1F600 = 😀 = 0xF0 0x9F 0x98 0x80)
TEST_F(GetCodePointTest_1874, FourByteCharacter_Emoji_1874) {
    XMP_Uns8 utf8[] = { 0xF0, 0x9F, 0x98, 0x80 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x1F600u);
    EXPECT_EQ(ptr, utf8 + 4);
}

// Test: Four-byte UTF-8 minimum (U+10000 = 0xF0 0x90 0x80 0x80)
TEST_F(GetCodePointTest_1874, FourByteCharacter_Min_1874) {
    XMP_Uns8 utf8[] = { 0xF0, 0x90, 0x80, 0x80 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x10000u);
    EXPECT_EQ(ptr, utf8 + 4);
}

// Test: Pointer advances correctly through consecutive characters
TEST_F(GetCodePointTest_1874, ConsecutiveCharacters_PointerAdvances_1874) {
    // "Aé" = 0x41, 0xC3, 0xA9
    XMP_Uns8 utf8[] = { 0x41, 0xC3, 0xA9, 0x00 };
    const XMP_Uns8* ptr = utf8;
    
    XMP_Uns32 cp1 = GetCodePoint(&ptr);
    EXPECT_EQ(cp1, 0x41u);
    EXPECT_EQ(ptr, utf8 + 1);
    
    XMP_Uns32 cp2 = GetCodePoint(&ptr);
    EXPECT_EQ(cp2, 0x00E9u);
    EXPECT_EQ(ptr, utf8 + 3);
}

// Test: Invalid UTF-8 leading byte should throw exception
TEST_F(GetCodePointTest_1874, InvalidLeadingByte_ThrowsException_1874) {
    // 0xFF is never valid in UTF-8
    XMP_Uns8 utf8[] = { 0xFF, 0x00, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    EXPECT_ANY_THROW(GetCodePoint(&ptr));
}

// Test: Invalid continuation byte should throw exception
TEST_F(GetCodePointTest_1874, InvalidContinuationByte_ThrowsException_1874) {
    // 0xC3 expects a continuation byte (0x80-0xBF), but 0x00 is not valid
    XMP_Uns8 utf8[] = { 0xC3, 0x00, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    EXPECT_ANY_THROW(GetCodePoint(&ptr));
}

// Test: Bare continuation byte (0x80) should throw exception
TEST_F(GetCodePointTest_1874, BareContinuationByte_ThrowsException_1874) {
    XMP_Uns8 utf8[] = { 0x80, 0x00, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    EXPECT_ANY_THROW(GetCodePoint(&ptr));
}

// Test: Overlong two-byte encoding should throw exception
TEST_F(GetCodePointTest_1874, OverlongTwoByte_ThrowsException_1874) {
    // Overlong encoding of U+0000: 0xC0 0x80
    XMP_Uns8 utf8[] = { 0xC0, 0x80, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    EXPECT_ANY_THROW(GetCodePoint(&ptr));
}

// Test: 0xFE is invalid in UTF-8
TEST_F(GetCodePointTest_1874, InvalidByte_0xFE_ThrowsException_1874) {
    XMP_Uns8 utf8[] = { 0xFE, 0x00, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    EXPECT_ANY_THROW(GetCodePoint(&ptr));
}

// Test: Space character (0x20)
TEST_F(GetCodePointTest_1874, SingleByteSpace_1874) {
    XMP_Uns8 utf8[] = { 0x20, 0x00, 0x00, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x20u);
    EXPECT_EQ(ptr, utf8 + 1);
}

// Test: CJK character (U+4E16 = 世 = 0xE4 0xB8 0x96)
TEST_F(GetCodePointTest_1874, ThreeByteCharacter_CJK_1874) {
    XMP_Uns8 utf8[] = { 0xE4, 0xB8, 0x96, 0x00 };
    const XMP_Uns8* ptr = utf8;
    XMP_Uns32 cp = GetCodePoint(&ptr);
    EXPECT_EQ(cp, 0x4E16u);
    EXPECT_EQ(ptr, utf8 + 3);
}

// Test: Multiple four-byte sequences read consecutively
TEST_F(GetCodePointTest_1874, MultipleFourByteSequences_1874) {
    // U+10000 followed by U+10001
    XMP_Uns8 utf8[] = { 0xF0, 0x90, 0x80, 0x80, 0xF0, 0x90, 0x80, 0x81 };
    const XMP_Uns8* ptr = utf8;
    
    XMP_Uns32 cp1 = GetCodePoint(&ptr);
    EXPECT_EQ(cp1, 0x10000u);
    EXPECT_EQ(ptr, utf8 + 4);
    
    XMP_Uns32 cp2 = GetCodePoint(&ptr);
    EXPECT_EQ(cp2, 0x10001u);
    EXPECT_EQ(ptr, utf8 + 8);
}
