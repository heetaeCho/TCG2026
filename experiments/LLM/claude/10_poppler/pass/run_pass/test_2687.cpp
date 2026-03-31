#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <memory>

// Poppler headers needed
#include "GlobalParams.h"
#include "UnicodeMap.h"
#include "UTF.h"

// The function under test is static in pdfsig.cc, so we need to include it
// or replicate its signature. Since it's static, we include the implementation.
// We'll define it here matching the exact implementation to test it.
static std::string TextStringToUTF8(const std::string &str)
{
    const UnicodeMap *utf8Map = globalParams->getUtf8Map();
    std::vector<Unicode> u = TextStringToUCS4(str);
    std::string convertedStr;
    for (auto &c : u) {
        char buf[8];
        const int n = utf8Map->mapUnicode(c, buf, sizeof(buf));
        convertedStr.append(buf, n);
    }
    return convertedStr;
}

class TextStringToUTF8Test_2687 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test with an empty string
TEST_F(TextStringToUTF8Test_2687, EmptyString_2687)
{
    std::string input = "";
    std::string result = TextStringToUTF8(input);
    EXPECT_TRUE(result.empty());
}

// Test with a simple ASCII string (PDFDocEncoding for ASCII range)
TEST_F(TextStringToUTF8Test_2687, SimpleASCIIString_2687)
{
    std::string input = "Hello";
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "Hello");
}

// Test with a single ASCII character
TEST_F(TextStringToUTF8Test_2687, SingleASCIIChar_2687)
{
    std::string input = "A";
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "A");
}

// Test with digits and punctuation
TEST_F(TextStringToUTF8Test_2687, DigitsAndPunctuation_2687)
{
    std::string input = "123-456!";
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "123-456!");
}

// Test with a UTF-16BE BOM prefix (0xFE 0xFF) which indicates UTF-16BE encoding
TEST_F(TextStringToUTF8Test_2687, UTF16BEWithBOM_2687)
{
    // UTF-16BE BOM followed by U+0048 (H), U+0069 (i)
    std::string input;
    input += '\xFE';
    input += '\xFF';
    input += '\x00';
    input += '\x48'; // 'H'
    input += '\x00';
    input += '\x69'; // 'i'
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "Hi");
}

// Test with spaces
TEST_F(TextStringToUTF8Test_2687, StringWithSpaces_2687)
{
    std::string input = "Hello World";
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "Hello World");
}

// Test with UTF-16BE BOM and non-ASCII characters (e.g., U+00E9 = é)
TEST_F(TextStringToUTF8Test_2687, UTF16BENonASCII_2687)
{
    std::string input;
    input += '\xFE';
    input += '\xFF';
    input += '\x00';
    input += '\xE9'; // U+00E9 = é
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "\xC3\xA9"); // UTF-8 for é
}

// Test with a longer ASCII string
TEST_F(TextStringToUTF8Test_2687, LongerASCIIString_2687)
{
    std::string input = "The quick brown fox jumps over the lazy dog";
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "The quick brown fox jumps over the lazy dog");
}

// Test with UTF-8 BOM (0xEF 0xBB 0xBF) prefix indicating UTF-8 encoding
TEST_F(TextStringToUTF8Test_2687, UTF8BOMPrefix_2687)
{
    std::string input;
    input += '\xEF';
    input += '\xBB';
    input += '\xBF';
    input += 'T';
    input += 'e';
    input += 's';
    input += 't';
    std::string result = TextStringToUTF8(input);
    EXPECT_EQ(result, "Test");
}

// Test with single byte that maps to non-trivial PDFDocEncoding
// In PDFDocEncoding, byte 0x80-0xFF have specific Unicode mappings
TEST_F(TextStringToUTF8Test_2687, PDFDocEncodingSpecialChar_2687)
{
    // 0xA9 in PDFDocEncoding should be copyright sign U+00A9
    std::string input;
    input += '\xA9';
    std::string result = TextStringToUTF8(input);
    // UTF-8 for U+00A9 is 0xC2 0xA9
    EXPECT_EQ(result, "\xC2\xA9");
}

// Test that the result is a valid non-empty string for non-empty input
TEST_F(TextStringToUTF8Test_2687, NonEmptyInputProducesNonEmptyOutput_2687)
{
    std::string input = "X";
    std::string result = TextStringToUTF8(input);
    EXPECT_FALSE(result.empty());
}
