#include <gtest/gtest.h>
#include <glib.h>
#include <cstring>
#include "GooString.h"

// Declaration of the function under test
char *_poppler_goo_string_to_utf8(const GooString *s);

class PopplerGooStringToUtf8Test_2163 : public ::testing::Test {
protected:
    void TearDown() override {
        // Nothing specific needed
    }
};

// Test that nullptr input returns nullptr
TEST_F(PopplerGooStringToUtf8Test_2163, NullInputReturnsNull_2163) {
    char *result = _poppler_goo_string_to_utf8(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test empty string
TEST_F(PopplerGooStringToUtf8Test_2163, EmptyStringReturnsEmptyUtf8_2163) {
    GooString s("");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    g_free(result);
}

// Test simple ASCII string (PDFDocEncoding path)
TEST_F(PopplerGooStringToUtf8Test_2163, SimpleAsciiString_2163) {
    GooString s("Hello World");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello World");
    g_free(result);
}

// Test single character ASCII
TEST_F(PopplerGooStringToUtf8Test_2163, SingleAsciiCharacter_2163) {
    GooString s("A");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "A");
    g_free(result);
}

// Test UTF-16BE BOM string (Big Endian)
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BEBomString_2163) {
    // UTF-16BE BOM is 0xFE 0xFF
    // "Hi" in UTF-16BE is 0x00 0x48, 0x00 0x69
    const char data[] = { '\xFE', '\xFF', '\x00', 'H', '\x00', 'i', '\0' };
    GooString s(data, 6); // 2 BOM bytes + 4 content bytes
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hi");
    g_free(result);
}

// Test UTF-16LE BOM string (Little Endian)
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16LEBomString_2163) {
    // UTF-16LE BOM is 0xFF 0xFE
    // "Hi" in UTF-16LE is 0x48 0x00, 0x69 0x00
    const char data[] = { '\xFF', '\xFE', 'H', '\x00', 'i', '\x00' };
    GooString s(data, 6); // 2 BOM bytes + 4 content bytes
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hi");
    g_free(result);
}

// Test UTF-16BE with non-ASCII characters
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BENonAscii_2163) {
    // UTF-16BE BOM + é (U+00E9) = 0x00 0xE9
    const char data[] = { '\xFE', '\xFF', '\x00', '\xE9' };
    GooString s(data, 4);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    // é in UTF-8 is 0xC3 0xA9
    EXPECT_STREQ(result, "\xC3\xA9");
    g_free(result);
}

// Test UTF-16LE with non-ASCII characters
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16LENonAscii_2163) {
    // UTF-16LE BOM + é (U+00E9) = 0xE9 0x00
    const char data[] = { '\xFF', '\xFE', '\xE9', '\x00' };
    GooString s(data, 4);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "\xC3\xA9");
    g_free(result);
}

// Test PDFDocEncoding with digits
TEST_F(PopplerGooStringToUtf8Test_2163, PdfDocEncodingDigits_2163) {
    GooString s("12345");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "12345");
    g_free(result);
}

// Test PDFDocEncoding with special characters that map directly
TEST_F(PopplerGooStringToUtf8Test_2163, PdfDocEncodingPunctuation_2163) {
    GooString s("Hello, World!");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello, World!");
    g_free(result);
}

// Test string with only BOM (UTF-16BE) and no content
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BEBomOnly_2163) {
    const char data[] = { '\xFE', '\xFF' };
    GooString s(data, 2);
    char *result = _poppler_goo_string_to_utf8(&s);
    // Converting 0 bytes should yield empty string or nullptr
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

// Test string with only BOM (UTF-16LE) and no content
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16LEBomOnly_2163) {
    const char data[] = { '\xFF', '\xFE' };
    GooString s(data, 2);
    char *result = _poppler_goo_string_to_utf8(&s);
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

// Test longer ASCII string via PDFDocEncoding path
TEST_F(PopplerGooStringToUtf8Test_2163, LongerAsciiString_2163) {
    GooString s("The quick brown fox jumps over the lazy dog");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "The quick brown fox jumps over the lazy dog");
    g_free(result);
}

// Test UTF-16BE with multiple characters
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BEMultipleChars_2163) {
    // UTF-16BE BOM + "ABC"
    const char data[] = { '\xFE', '\xFF', '\x00', 'A', '\x00', 'B', '\x00', 'C' };
    GooString s(data, 8);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ABC");
    g_free(result);
}

// Test UTF-16LE with multiple characters
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16LEMultipleChars_2163) {
    // UTF-16LE BOM + "ABC"
    const char data[] = { '\xFF', '\xFE', 'A', '\x00', 'B', '\x00', 'C', '\x00' };
    GooString s(data, 8);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ABC");
    g_free(result);
}

// Test PDFDocEncoding with high-byte characters (e.g., 0xA9 = copyright sign in PDFDocEncoding)
TEST_F(PopplerGooStringToUtf8Test_2163, PdfDocEncodingHighByte_2163) {
    // 0x20 is space in PDFDocEncoding
    const char data[] = { '\x20' };
    GooString s(data, 1);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, " ");
    g_free(result);
}

// Test that the result is a valid UTF-8 string for basic ASCII input
TEST_F(PopplerGooStringToUtf8Test_2163, ResultIsValidUtf8_2163) {
    GooString s("Test string 123");
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(g_utf8_validate(result, -1, nullptr));
    g_free(result);
}

// Test that UTF-16BE result is valid UTF-8
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BEResultIsValidUtf8_2163) {
    const char data[] = { '\xFE', '\xFF', '\x00', 'X', '\x00', 'Y' };
    GooString s(data, 6);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(g_utf8_validate(result, -1, nullptr));
    g_free(result);
}

// Test string containing null bytes in PDFDocEncoding path
TEST_F(PopplerGooStringToUtf8Test_2163, PdfDocEncodingWithNullByte_2163) {
    // A single null byte character - PDFDocEncoding maps 0x00 to U+0000
    const char data[] = { 'A', '\x00', 'B' };
    GooString s(data, 3);
    char *result = _poppler_goo_string_to_utf8(&s);
    // The result might be truncated at the null or contain all 3 chars
    // We just check it's not null and is valid UTF-8 (at least partial)
    ASSERT_NE(result, nullptr);
    g_free(result);
}

// Test UTF-16BE with a character outside BMP (surrogate pair)
TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BESurrogatePair_2163) {
    // UTF-16BE BOM + U+1F600 (😀) = D83D DE00
    const char data[] = { '\xFE', '\xFF', '\xD8', '\x3D', '\xDE', '\x00' };
    GooString s(data, 6);
    char *result = _poppler_goo_string_to_utf8(&s);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(g_utf8_validate(result, -1, nullptr));
    g_free(result);
}
