#include <gtest/gtest.h>
#include "XMPUtils-FileInfo.cpp"

#define TEST_ID 1915

// Test the ClassifyCharacter function for normal ASCII characters
TEST_F(XMPUtilsFileInfoTest, ClassifyCharacter_NormalASCII_1915) {
    const char* testStr = "Hello";
    size_t offset = 0;
    UniCharKind charKind;
    size_t charSize;
    UniCodePoint uniChar;

    // Test for character 'H'
    ClassifyCharacter(testStr, offset, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1);
    EXPECT_EQ(uniChar, 'H');

    // Test for character 'e'
    ClassifyCharacter(testStr, offset + 1, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 1);
    EXPECT_EQ(uniChar, 'e');
}

// Test the ClassifyCharacter function for boundary cases
TEST_F(XMPUtilsFileInfoTest, ClassifyCharacter_BoundaryCases_1915) {
    const char* testStr = " ";
    size_t offset = 0;
    UniCharKind charKind;
    size_t charSize;
    UniCodePoint uniChar;

    // Test for space character
    ClassifyCharacter(testStr, offset, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_space);
    EXPECT_EQ(charSize, 1);
    EXPECT_EQ(uniChar, ' ');

    // Test for control character
    testStr = "\x01";  // Control character
    ClassifyCharacter(testStr, 0, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_control);
    EXPECT_EQ(charSize, 1);
    EXPECT_EQ(uniChar, 0x01);
}

// Test the ClassifyCharacter function for multi-byte characters
TEST_F(XMPUtilsFileInfoTest, ClassifyCharacter_MultiByteCharacter_1915) {
    const char* testStr = "\xC2\xA9";  // Unicode '©' character (UTF-8 encoded)
    size_t offset = 0;
    UniCharKind charKind;
    size_t charSize;
    UniCodePoint uniChar;

    // Test for multi-byte character '©'
    ClassifyCharacter(testStr, offset, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_normal);
    EXPECT_EQ(charSize, 2);  // UTF-8 encoded character is 2 bytes
    EXPECT_EQ(uniChar, 0x00A9);  // Unicode value of '©'
}

// Test the ClassifyCharacter function for Unicode character ranges (upper bits)
TEST_F(XMPUtilsFileInfoTest, ClassifyCharacter_UnicodeRanges_1915) {
    const char* testStr = "\xEF\xBC\x8C";  // Full-width comma (U+FF0C)
    size_t offset = 0;
    UniCharKind charKind;
    size_t charSize;
    UniCodePoint uniChar;

    // Test for full-width comma character
    ClassifyCharacter(testStr, offset, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3);  // UTF-8 encoded character is 3 bytes
    EXPECT_EQ(uniChar, 0xFF0C);  // Unicode value of U+FF0C

    // Test for ideographic comma (U+3001)
    testStr = "\xE3\x80\x81";  // UTF-8 encoded ideographic comma
    ClassifyCharacter(testStr, offset, &charKind, &charSize, &uniChar);
    EXPECT_EQ(charKind, UCK_comma);
    EXPECT_EQ(charSize, 3);  // UTF-8 encoded character is 3 bytes
    EXPECT_EQ(uniChar, 0x3001);  // Unicode value of U+3001
}

// Test the ClassifyCharacter function for incorrect or malformed input
TEST_F(XMPUtilsFileInfoTest, ClassifyCharacter_MalformedInput_1915) {
    const char* testStr = "\x80";  // Invalid UTF-8 byte
    size_t offset = 0;
    UniCharKind charKind;
    size_t charSize;
    UniCodePoint uniChar;

    // Test for malformed input that should be handled
    EXPECT_THROW(ClassifyCharacter(testStr, offset, &charKind, &charSize, &uniChar), std::invalid_argument);
}