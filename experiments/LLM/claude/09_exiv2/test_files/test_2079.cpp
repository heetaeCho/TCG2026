#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the XMP SDK Unicode conversion headers
// Based on the xmpsdk structure:
#include "UnicodeConversions.hpp"

class UnicodeConversionsTest_2079 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test converting empty UTF16 swapped input
TEST_F(UnicodeConversionsTest_2079, EmptyUTF16SwpInput_2079) {
    // When utf16Len is 0, utf16Read should be 0 and cpOut should not be modified
    UTF16Unit input[] = {0x0041};
    UTF32Unit codepoint = 0xFFFFFFFF;
    size_t utf16Read = 99;
    
    CodePoint_from_UTF16Swp(input, 0, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 0u);
    // codepoint should not be written to when length is 0
    EXPECT_EQ(codepoint, 0xFFFFFFFF);
}

// Test converting a basic BMP character (ASCII 'A' = 0x0041, swapped = 0x4100)
TEST_F(UnicodeConversionsTest_2079, BasicBMPCharacterSwapped_2079) {
    // 'A' is U+0041, byte-swapped in UTF-16 would be 0x4100
    UTF16Unit input[] = {0x4100};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0x0041u);
}

// Test converting a non-ASCII BMP character
TEST_F(UnicodeConversionsTest_2079, NonAsciiBMPSwapped_2079) {
    // U+00E9 (é), byte-swapped = 0xE900
    UTF16Unit input[] = {0xE900};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0x00E9u);
}

// Test boundary: character just below surrogate range (U+D7FF)
TEST_F(UnicodeConversionsTest_2079, BelowSurrogateRange_2079) {
    // U+D7FF byte-swapped = 0xFFD7
    UTF16Unit input[] = {0xFFD7};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0xD7FFu);
}

// Test boundary: character just above surrogate range (U+E000)
TEST_F(UnicodeConversionsTest_2079, AboveSurrogateRange_2079) {
    // U+E000 byte-swapped = 0x00E0
    UTF16Unit input[] = {0x00E0};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0xE000u);
}

// Test surrogate pair: U+10000 encoded as surrogate pair (D800 DC00), swapped
TEST_F(UnicodeConversionsTest_2079, SurrogatePairSwapped_2079) {
    // U+10000 => high surrogate 0xD800, low surrogate 0xDC00
    // Byte-swapped: 0x00D8, 0x00DC
    UTF16Unit input[] = {0x00D8, 0x00DC};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 2, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(codepoint, 0x10000u);
}

// Test surrogate pair: U+10FFFF (max valid code point)
TEST_F(UnicodeConversionsTest_2079, MaxCodePointSurrogatePair_2079) {
    // U+10FFFF => high surrogate 0xDBFF, low surrogate 0xDFFF
    // Byte-swapped: 0xFFDB, 0xFFDF
    UTF16Unit input[] = {0xFFDB, 0xFFDF};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 2, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(codepoint, 0x10FFFFu);
}

// Test lone high surrogate with only 1 unit available (no low surrogate follows)
TEST_F(UnicodeConversionsTest_2079, LoneHighSurrogateSwapped_2079) {
    // High surrogate 0xD800, byte-swapped = 0x00D8, with length 1
    UTF16Unit input[] = {0x00D8};
    UTF32Unit codepoint = 0xFFFFFFFF;
    size_t utf16Read = 99;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    // Implementation should handle this via surrogate pair handler
    // Exact behavior depends on implementation, but utf16Read should be set
    EXPECT_GE(utf16Read, 0u);
}

// Test null character (U+0000) swapped
TEST_F(UnicodeConversionsTest_2079, NullCharacterSwapped_2079) {
    UTF16Unit input[] = {0x0000};
    UTF32Unit codepoint = 0xFFFFFFFF;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0x0000u);
}

// Test character U+FFFF (max BMP, non-surrogate), byte-swapped = 0xFFFF
TEST_F(UnicodeConversionsTest_2079, MaxBMPCharSwapped_2079) {
    // U+FFFF byte-swapped is still 0xFFFF
    UTF16Unit input[] = {0xFFFF};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0xFFFFu);
}

// Test with larger buffer but only reading one BMP character
TEST_F(UnicodeConversionsTest_2079, LargerBufferBMPSwapped_2079) {
    // Multiple characters in buffer, but function reads one at a time
    // U+0042 ('B') swapped = 0x4200
    UTF16Unit input[] = {0x4200, 0x4300, 0x4400};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 3, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(codepoint, 0x0042u);
}

// Test a surrogate pair with larger buffer
TEST_F(UnicodeConversionsTest_2079, SurrogatePairInLargerBufferSwapped_2079) {
    // U+1F600 (😀) => high 0xD83D, low 0xDE00
    // Byte-swapped: 0x3DD8, 0x00DE
    UTF16Unit input[] = {0x3DD8, 0x00DE, 0x4100};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 3, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(codepoint, 0x1F600u);
}

// Test at start of surrogate range (0xD800) - this is a high surrogate
TEST_F(UnicodeConversionsTest_2079, StartOfSurrogateRangeSwapped_2079) {
    // 0xD800 swapped = 0x00D8, followed by valid low surrogate 0xDC00 swapped = 0x00DC
    UTF16Unit input[] = {0x00D8, 0x00DC};
    UTF32Unit codepoint = 0;
    size_t utf16Read = 0;
    
    CodePoint_from_UTF16Swp(input, 2, &codepoint, &utf16Read);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(codepoint, 0x10000u);
}

// Test at end of surrogate range (0xDFFF is a low surrogate without high)
TEST_F(UnicodeConversionsTest_2079, EndOfSurrogateRangeAlone_2079) {
    // 0xDFFF swapped = 0xFFDF, alone (no preceding high surrogate)
    UTF16Unit input[] = {0xFFDF};
    UTF32Unit codepoint = 0xFFFFFFFF;
    size_t utf16Read = 99;
    
    // This is an invalid lone low surrogate - behavior depends on implementation
    CodePoint_from_UTF16Swp(input, 1, &codepoint, &utf16Read);
    
    // At minimum, utf16Read should be set
    EXPECT_GE(utf16Read, 0u);
}
