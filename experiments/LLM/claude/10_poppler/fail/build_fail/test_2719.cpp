#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstring>

// Include necessary headers
#include "GooString.h"
#include "UnicodeMap.h"
#include "PDFDocEncoding.h"

// We need to include or declare the function under test
// Since it's a static function in pdfdetach.cc, we need to make it accessible
// We'll include the source or re-declare it for testing purposes

// Forward declare the helper function used inside getFileName
bool hasUnicodeByteOrderMarkAndLengthIsEven(const std::string &s);

// We need to extract the static function for testing. Since it's static in a .cc file,
// we include the source file directly to access it.
#include "pdfdetach.cc"

class GetFileNameTest_2719 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a basic Latin1/ASCII UnicodeMap for testing
        // We'll use the "Latin1" encoding which should map ASCII characters directly
    }
};

// Test with empty string (non-Unicode)
TEST_F(GetFileNameTest_2719, EmptyString_ReturnsEmpty_2719) {
    GooString input("");
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_TRUE(result.empty());
}

// Test with simple ASCII filename (non-Unicode, PDFDocEncoding)
TEST_F(GetFileNameTest_2719, SimpleAsciiFilename_2719) {
    GooString input("test.pdf");
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    // PDFDocEncoding for ASCII range should map to same characters
    EXPECT_FALSE(result.empty());
    // For basic ASCII characters, PDFDocEncoding maps to the same Unicode code points
    // and Latin1 UnicodeMap should map them back to the same bytes
    EXPECT_EQ(result, "test.pdf");
}

// Test with Unicode BOM prefix (UTF-16BE encoded string)
TEST_F(GetFileNameTest_2719, UnicodeBOMString_2719) {
    // UTF-16BE BOM is 0xFE 0xFF
    // Followed by UTF-16BE encoded "AB" -> 0x00 0x41 0x00 0x42
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0xFF);
    raw.push_back((char)0x00);
    raw.push_back((char)0x41); // 'A'
    raw.push_back((char)0x00);
    raw.push_back((char)0x42); // 'B'
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "AB");
}

// Test with Unicode BOM but empty content (just the BOM)
TEST_F(GetFileNameTest_2719, UnicodeBOMOnly_ReturnsEmpty_2719) {
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0xFF);
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_TRUE(result.empty());
}

// Test single character non-Unicode
TEST_F(GetFileNameTest_2719, SingleCharNonUnicode_2719) {
    GooString input("A");
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "A");
}

// Test single Unicode character (BOM + one UTF-16BE char)
TEST_F(GetFileNameTest_2719, SingleUnicodeChar_2719) {
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0xFF);
    raw.push_back((char)0x00);
    raw.push_back((char)0x5A); // 'Z'
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "Z");
}

// Test with filename containing dot and extension
TEST_F(GetFileNameTest_2719, FilenameWithExtension_2719) {
    GooString input("document.txt");
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "document.txt");
}

// Test with filename containing spaces
TEST_F(GetFileNameTest_2719, FilenameWithSpaces_2719) {
    GooString input("my file.pdf");
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "my file.pdf");
}

// Test that a string starting with 0xFE but not followed by 0xFF is not treated as Unicode
TEST_F(GetFileNameTest_2719, FalseUnicodeBOM_NotUnicode_2719) {
    // 0xFE followed by something other than 0xFF - should not be treated as BOM
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0x00); // Not 0xFF, so not a BOM
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    // Should be treated as PDFDocEncoding, not Unicode
    EXPECT_FALSE(result.empty());
}

// Test Unicode string with multiple characters
TEST_F(GetFileNameTest_2719, UnicodeMultipleChars_2719) {
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0xFF);
    // "Hello" in UTF-16BE
    raw.push_back((char)0x00); raw.push_back((char)0x48); // H
    raw.push_back((char)0x00); raw.push_back((char)0x65); // e
    raw.push_back((char)0x00); raw.push_back((char)0x6C); // l
    raw.push_back((char)0x00); raw.push_back((char)0x6C); // l
    raw.push_back((char)0x00); raw.push_back((char)0x6F); // o
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "Hello");
}

// Test with odd-length string that starts with BOM-like bytes
// hasUnicodeByteOrderMarkAndLengthIsEven should return false for odd length
TEST_F(GetFileNameTest_2719, OddLengthWithBOMBytes_TreatedAsNonUnicode_2719) {
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0xFF);
    raw.push_back((char)0x41); // Makes it odd length (3)
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    // Since length is odd, should not be treated as Unicode
    // All 3 bytes processed via PDFDocEncoding
    EXPECT_FALSE(result.empty());
}

// Test with numeric characters in filename
TEST_F(GetFileNameTest_2719, NumericFilename_2719) {
    GooString input("12345.dat");
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "12345.dat");
}

// Test with UTF-8 UnicodeMap for Unicode encoded string
TEST_F(GetFileNameTest_2719, UnicodeWithUTF8Map_2719) {
    std::string raw;
    raw.push_back((char)0xFE);
    raw.push_back((char)0xFF);
    raw.push_back((char)0x00);
    raw.push_back((char)0x41); // 'A'
    
    GooString input(raw);
    auto uMap = UnicodeMap::parse("UTF-8");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, "A");
}

// Test with long filename
TEST_F(GetFileNameTest_2719, LongFilename_2719) {
    std::string longName(255, 'x');
    longName += ".pdf";
    GooString input(longName);
    auto uMap = UnicodeMap::parse("Latin1");
    ASSERT_NE(uMap, nullptr);
    
    std::string result = getFileName(input, *uMap);
    EXPECT_EQ(result, longName);
}
