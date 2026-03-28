#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <vector>

// Forward declarations for the types and functions we need
typedef unsigned char UTF8Unit;
typedef uint32_t UTF32Unit;

extern void ToUTF32Native(const UTF8Unit* utf8In, size_t utf8Len, std::string* utf32Str);

// Error codes from XMP_Const.h
enum {
    kXMPErr_Unknown = 0,
    kXMPErr_BadXML = 201,
    kXMPErr_BadUnicode = 205
};

class ToUTF32NativeTest_2057 : public ::testing::Test {
protected:
    std::string utf32Str;
};

// Test: Empty input produces empty output
TEST_F(ToUTF32NativeTest_2057, EmptyInput_ProducesEmptyOutput_2057) {
    const UTF8Unit* emptyInput = reinterpret_cast<const UTF8Unit*>("");
    ToUTF32Native(emptyInput, 0, &utf32Str);
    EXPECT_TRUE(utf32Str.empty());
}

// Test: Single ASCII character converts correctly
TEST_F(ToUTF32NativeTest_2057, SingleAsciiCharacter_2057) {
    const UTF8Unit input[] = { 'A' };
    ToUTF32Native(input, 1, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>('A'));
}

// Test: Multiple ASCII characters convert correctly
TEST_F(ToUTF32NativeTest_2057, MultipleAsciiCharacters_2057) {
    const char* text = "Hello";
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(text);
    ToUTF32Native(input, 5, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 20u); // 5 characters * 4 bytes each
    
    for (size_t i = 0; i < 5; ++i) {
        UTF32Unit result;
        std::memcpy(&result, utf32Str.data() + i * 4, 4);
        EXPECT_EQ(result, static_cast<UTF32Unit>(text[i]));
    }
}

// Test: Two-byte UTF-8 sequence (e.g., U+00E9, é = 0xC3 0xA9)
TEST_F(ToUTF32NativeTest_2057, TwoByteUTF8Character_2057) {
    const UTF8Unit input[] = { 0xC3, 0xA9 }; // é (U+00E9)
    ToUTF32Native(input, 2, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x00E9));
}

// Test: Three-byte UTF-8 sequence (e.g., U+4E16, 世 = 0xE4 0xB8 0x96)
TEST_F(ToUTF32NativeTest_2057, ThreeByteUTF8Character_2057) {
    const UTF8Unit input[] = { 0xE4, 0xB8, 0x96 }; // 世 (U+4E16)
    ToUTF32Native(input, 3, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x4E16));
}

// Test: Four-byte UTF-8 sequence (e.g., U+1F600, 😀 = 0xF0 0x9F 0x98 0x80)
TEST_F(ToUTF32NativeTest_2057, FourByteUTF8Character_2057) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 }; // 😀 (U+1F600)
    ToUTF32Native(input, 4, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x1F600));
}

// Test: Mixed ASCII and multi-byte characters
TEST_F(ToUTF32NativeTest_2057, MixedAsciiAndMultiByte_2057) {
    // "Aé" = 'A' (1 byte) + 'é' (2 bytes) = 3 bytes total
    const UTF8Unit input[] = { 0x41, 0xC3, 0xA9 };
    ToUTF32Native(input, 3, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 8u); // 2 UTF-32 code units * 4 bytes
    
    UTF32Unit result0, result1;
    std::memcpy(&result0, utf32Str.data(), 4);
    std::memcpy(&result1, utf32Str.data() + 4, 4);
    EXPECT_EQ(result0, static_cast<UTF32Unit>('A'));
    EXPECT_EQ(result1, static_cast<UTF32Unit>(0x00E9));
}

// Test: Incomplete UTF-8 sequence throws exception
TEST_F(ToUTF32NativeTest_2057, IncompleteUTF8Sequence_ThrowsException_2057) {
    // 0xC3 is the start of a 2-byte sequence but we only provide 1 byte
    const UTF8Unit input[] = { 0xC3 };
    EXPECT_ANY_THROW(ToUTF32Native(input, 1, &utf32Str));
}

// Test: Incomplete 3-byte UTF-8 sequence throws exception
TEST_F(ToUTF32NativeTest_2057, IncompleteThreeByteSequence_ThrowsException_2057) {
    // 0xE4 starts a 3-byte sequence, but only 2 bytes provided
    const UTF8Unit input[] = { 0xE4, 0xB8 };
    EXPECT_ANY_THROW(ToUTF32Native(input, 2, &utf32Str));
}

// Test: Incomplete 4-byte UTF-8 sequence throws exception
TEST_F(ToUTF32NativeTest_2057, IncompleteFourByteSequence_ThrowsException_2057) {
    // 0xF0 starts a 4-byte sequence, but only 3 bytes provided
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98 };
    EXPECT_ANY_THROW(ToUTF32Native(input, 3, &utf32Str));
}

// Test: Output string is cleared before writing
TEST_F(ToUTF32NativeTest_2057, OutputStringIsClearedBeforeWriting_2057) {
    utf32Str = "pre-existing data that should be erased";
    const UTF8Unit input[] = { 'X' };
    ToUTF32Native(input, 1, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>('X'));
}

// Test: Null byte in UTF-8 input converts to U+0000
TEST_F(ToUTF32NativeTest_2057, NullByteConvertsToZero_2057) {
    const UTF8Unit input[] = { 0x00 };
    ToUTF32Native(input, 1, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0));
}

// Test: All printable ASCII characters
TEST_F(ToUTF32NativeTest_2057, AllPrintableAscii_2057) {
    std::vector<UTF8Unit> input;
    for (int i = 0x20; i <= 0x7E; ++i) {
        input.push_back(static_cast<UTF8Unit>(i));
    }
    ToUTF32Native(input.data(), input.size(), &utf32Str);
    ASSERT_EQ(utf32Str.size(), input.size() * 4);
    
    for (size_t i = 0; i < input.size(); ++i) {
        UTF32Unit result;
        std::memcpy(&result, utf32Str.data() + i * 4, 4);
        EXPECT_EQ(result, static_cast<UTF32Unit>(input[i]));
    }
}

// Test: Boundary - single byte max ASCII (0x7F)
TEST_F(ToUTF32NativeTest_2057, MaxSingleByteAscii_2057) {
    const UTF8Unit input[] = { 0x7F }; // DEL character, still single-byte
    ToUTF32Native(input, 1, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x7F));
}

// Test: Boundary - minimum two-byte character (U+0080 = 0xC2 0x80)
TEST_F(ToUTF32NativeTest_2057, MinTwoByteCharacter_2057) {
    const UTF8Unit input[] = { 0xC2, 0x80 }; // U+0080
    ToUTF32Native(input, 2, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x0080));
}

// Test: Boundary - maximum two-byte character (U+07FF = 0xDF 0xBF)
TEST_F(ToUTF32NativeTest_2057, MaxTwoByteCharacter_2057) {
    const UTF8Unit input[] = { 0xDF, 0xBF }; // U+07FF
    ToUTF32Native(input, 2, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x07FF));
}

// Test: Boundary - minimum three-byte character (U+0800 = 0xE0 0xA0 0x80)
TEST_F(ToUTF32NativeTest_2057, MinThreeByteCharacter_2057) {
    const UTF8Unit input[] = { 0xE0, 0xA0, 0x80 }; // U+0800
    ToUTF32Native(input, 3, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0x0800));
}

// Test: Larger input that requires multiple buffer fills
TEST_F(ToUTF32NativeTest_2057, LargerInput_2057) {
    // Create a string of 5000 ASCII characters (exceeds internal buffer of 4096)
    std::vector<UTF8Unit> input(5000, 'Z');
    ToUTF32Native(input.data(), input.size(), &utf32Str);
    ASSERT_EQ(utf32Str.size(), 5000u * 4);
    
    // Verify first and last characters
    UTF32Unit first, last;
    std::memcpy(&first, utf32Str.data(), 4);
    std::memcpy(&last, utf32Str.data() + (4999 * 4), 4);
    EXPECT_EQ(first, static_cast<UTF32Unit>('Z'));
    EXPECT_EQ(last, static_cast<UTF32Unit>('Z'));
}

// Test: Multiple calls reuse output string correctly
TEST_F(ToUTF32NativeTest_2057, MultipleCalls_OutputIsReset_2057) {
    const UTF8Unit input1[] = { 'A', 'B', 'C' };
    ToUTF32Native(input1, 3, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 12u);
    
    const UTF8Unit input2[] = { 'X' };
    ToUTF32Native(input2, 1, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>('X'));
}

// Test: Invalid continuation byte (standalone continuation byte 0x80)
TEST_F(ToUTF32NativeTest_2057, InvalidStandaloneContinuationByte_2057) {
    const UTF8Unit input[] = { 0x80 }; // Invalid: standalone continuation byte
    // This should either throw or produce replacement; we expect an exception based on the implementation
    EXPECT_ANY_THROW(ToUTF32Native(input, 1, &utf32Str));
}

// Test: BOM in UTF-8 (EF BB BF = U+FEFF)
TEST_F(ToUTF32NativeTest_2057, UTF8BOM_2057) {
    const UTF8Unit input[] = { 0xEF, 0xBB, 0xBF }; // BOM U+FEFF
    ToUTF32Native(input, 3, &utf32Str);
    ASSERT_EQ(utf32Str.size(), 4u);
    UTF32Unit result;
    std::memcpy(&result, utf32Str.data(), 4);
    EXPECT_EQ(result, static_cast<UTF32Unit>(0xFEFF));
}
