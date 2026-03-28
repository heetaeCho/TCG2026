#include <gtest/gtest.h>
#include <cstdint>
#include <stdexcept>

// Type definitions matching the codebase
typedef uint16_t UTF16Unit;
typedef uint32_t UTF32Unit;

// We need to include or declare the function under test.
// Since it's a static function in a .cpp file, we need to either:
// 1. Include the .cpp file directly, or
// 2. Re-declare it as extern for testing purposes.
// Since the function is static, we'll include the cpp to access it.

// First, let's handle the UC_Throw macro and any dependencies
// UC_Throw likely throws an exception. Based on the XMP SDK, it typically throws XMP_Error.

// We need to replicate enough of the environment to compile and link.
// Let's define the necessary types and include the source.

#include "XMP_Const.h"

// The XMP SDK typically defines XMP_Error or uses a macro UC_Throw that throws.
// We need to include the actual source file to get the static function.
// However, since UC_Throw is a macro defined somewhere in the XMP SDK headers,
// we may need to include those as well.

// Include the source file to get access to the static function
#include "UnicodeConversions.cpp"

class CodePointFromUTF16NatSurrogateTest_2068 : public ::testing::Test {
protected:
    UTF32Unit cpOut;
    size_t utf16Read;
    
    void SetUp() override {
        cpOut = 0;
        utf16Read = 0;
    }
};

// Test: Valid surrogate pair - basic case (e.g., U+10000)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_U10000_2068) {
    // U+10000 => high surrogate 0xD800, low surrogate 0xDC00
    UTF16Unit utf16In[2] = {0xD800, 0xDC00};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x10000u);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair - U+10FFFF (maximum code point)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_U10FFFF_2068) {
    // U+10FFFF => high surrogate 0xDBFF, low surrogate 0xDFFF
    UTF16Unit utf16In[2] = {0xDBFF, 0xDFFF};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x10FFFFu);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair - U+1D11E (Musical Symbol G Clef)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_U1D11E_2068) {
    // U+1D11E => high surrogate 0xD834, low surrogate 0xDD1E
    UTF16Unit utf16In[2] = {0xD834, 0xDD1E};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x1D11Eu);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair - minimum high surrogate with minimum low surrogate
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_MinHighMinLow_2068) {
    UTF16Unit utf16In[2] = {0xD800, 0xDC00};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x10000u);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair - maximum high surrogate with maximum low surrogate
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_MaxHighMaxLow_2068) {
    UTF16Unit utf16In[2] = {0xDBFF, 0xDFFF};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x10FFFFu);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair with extra buffer length (utf16Len > 2)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_ExtraBufferLen_2068) {
    UTF16Unit utf16In[4] = {0xD800, 0xDC00, 0x0041, 0x0042};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 4, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x10000u);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Leading low surrogate (hiUnit > 0xDBFF) should throw
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, LeadingLowSurrogate_Throws_2068) {
    // 0xDC00 is a low surrogate, used as leading unit
    UTF16Unit utf16In[2] = {0xDC00, 0xDC00};
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Leading unit is 0xDFFF (low surrogate range) should throw
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, LeadingUnitDFFF_Throws_2068) {
    UTF16Unit utf16In[2] = {0xDFFF, 0xDC00};
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Not enough input (utf16Len < 2) - should set utf16Read to 0
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, InsufficientInput_Len1_2068) {
    UTF16Unit utf16In[1] = {0xD800};
    UTF32Unit originalCp = 0x12345678;
    cpOut = originalCp;
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 1, &cpOut, &utf16Read);
    
    EXPECT_EQ(utf16Read, 0u);
    // cpOut should not be modified (we check it wasn't written to)
    EXPECT_EQ(cpOut, originalCp);
}

// Test: Not enough input (utf16Len == 0) - should set utf16Read to 0
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, InsufficientInput_Len0_2068) {
    UTF16Unit utf16In[1] = {0xD800};
    UTF32Unit originalCp = 0xABCDEF01;
    cpOut = originalCp;
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 0, &cpOut, &utf16Read);
    
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(cpOut, originalCp);
}

// Test: Valid high surrogate but missing low surrogate (second unit is not in low surrogate range)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, MissingLowSurrogate_TooLow_2068) {
    // Second unit is below 0xDC00
    UTF16Unit utf16In[2] = {0xD800, 0xDBFF};
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Valid high surrogate but second unit is above low surrogate range
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, MissingLowSurrogate_TooHigh_2068) {
    // Second unit is above 0xDFFF
    UTF16Unit utf16In[2] = {0xD800, 0xE000};
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Valid high surrogate but second unit is a regular ASCII-range value
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, MissingLowSurrogate_RegularChar_2068) {
    UTF16Unit utf16In[2] = {0xD800, 0x0041}; // 'A' is not a low surrogate
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Second unit just below low surrogate range (0xDBFF)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, SecondUnitJustBelowLowSurrogateRange_2068) {
    UTF16Unit utf16In[2] = {0xD800, 0xDBFF}; // 0xDBFF < 0xDC00
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Second unit just above low surrogate range (0xE000)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, SecondUnitJustAboveLowSurrogateRange_2068) {
    UTF16Unit utf16In[2] = {0xD800, 0xE000}; // 0xE000 > 0xDFFF
    
    EXPECT_THROW(
        CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Boundary - high surrogate at exact boundary 0xD800
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, HighSurrogateBoundary_D800_2068) {
    UTF16Unit utf16In[2] = {0xD800, 0xDC01};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    // (0xD800 & 0x3FF) = 0, (0xDC01 & 0x3FF) = 1, result = 0 << 10 | 1 + 0x10000 = 0x10001
    EXPECT_EQ(cpOut, 0x10001u);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Boundary - high surrogate at exact boundary 0xDBFF
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, HighSurrogateBoundary_DBFF_2068) {
    UTF16Unit utf16In[2] = {0xDBFF, 0xDC00};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    // (0xDBFF & 0x3FF) = 0x3FF, (0xDC00 & 0x3FF) = 0, result = 0x3FF << 10 | 0 + 0x10000 = 0xFFC00 + 0x10000 = 0x10FC00
    EXPECT_EQ(cpOut, 0x10FC00u);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Low surrogate boundary - exact 0xDC00
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, LowSurrogateBoundary_DC00_2068) {
    UTF16Unit utf16In[2] = {0xD801, 0xDC00};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    // (0xD801 & 0x3FF) = 1, (0xDC00 & 0x3FF) = 0, result = 1 << 10 | 0 + 0x10000 = 0x400 + 0x10000 = 0x10400
    EXPECT_EQ(cpOut, 0x10400u);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Low surrogate boundary - exact 0xDFFF
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, LowSurrogateBoundary_DFFF_2068) {
    UTF16Unit utf16In[2] = {0xD801, 0xDFFF};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    // (0xD801 & 0x3FF) = 1, (0xDFFF & 0x3FF) = 0x3FF, result = 1 << 10 | 0x3FF + 0x10000 = 0x400 + 0x3FF + 0x10000 = 0x107FF
    EXPECT_EQ(cpOut, 0x107FFu);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Emoji character U+1F600 (Grinning Face)
TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_Emoji_U1F600_2068) {
    // U+1F600 => high surrogate 0xD83D, low surrogate 0xDE00
    UTF16Unit utf16In[2] = {0xD83D, 0xDE00};
    
    CodePoint_from_UTF16Nat_Surrogate(utf16In, 2, &cpOut, &utf16Read);
    
    EXPECT_EQ(cpOut, 0x1F600u);
    EXPECT_EQ(utf16Read, 2u);
}
