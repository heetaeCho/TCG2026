#include <glib.h>
#include <gtest/gtest.h>
#include <memory>
#include <cstring>

// We need to include the header that declares the function, or declare it ourselves.
// Since _poppler_goo_string_from_utf8 is a static function in the .cc file,
// we need a way to test it. We'll include the source or use a workaround.
// For testing purposes, we'll re-declare the necessary types and include the source.

#include "poppler/GooString.h"
#include "poppler/UTF.h"

// Since the function is static, we need to include the .cc file to access it,
// or we create a test wrapper. We'll use an include approach for testing.
// In practice, we'd need to make the function accessible for testing.

// Forward declare or include to get the function visible
// We'll define a wrapper that includes the static function
namespace {
#include "poppler-document.cc"
}

class PopplerGooStringFromUtf8Test_2164 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns nullptr
TEST_F(PopplerGooStringFromUtf8Test_2164, NullInputReturnsNullptr_2164)
{
    auto result = _poppler_goo_string_from_utf8(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a simple ASCII string is converted and has BOM
TEST_F(PopplerGooStringFromUtf8Test_2164, SimpleAsciiString_2164)
{
    const gchar *input = "Hello";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // The result should have a Unicode BOM (0xFE 0xFF) at the beginning
    ASSERT_GE(result->getLength(), 2);
    const char *data = result->c_str();
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
}

// Test that an empty string is handled correctly
TEST_F(PopplerGooStringFromUtf8Test_2164, EmptyString_2164)
{
    const gchar *input = "";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // Even an empty string should have at least the BOM
    ASSERT_GE(result->getLength(), 2);
    const char *data = result->c_str();
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
}

// Test with a multi-byte UTF-8 string (e.g., a non-ASCII character)
TEST_F(PopplerGooStringFromUtf8Test_2164, MultiBytUtf8String_2164)
{
    // "é" is U+00E9, UTF-8: 0xC3 0xA9, UTF-16BE: 0x00 0xE9
    const gchar *input = "é";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    ASSERT_GE(result->getLength(), 4); // BOM (2) + one UTF-16 char (2)
    const char *data = result->c_str();
    // Check BOM
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
    // Check the character encoding (UTF-16BE for é is 0x00E9)
    EXPECT_EQ(static_cast<unsigned char>(data[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(data[3]), 0xE9);
}

// Test with a longer UTF-8 string
TEST_F(PopplerGooStringFromUtf8Test_2164, LongerUtf8String_2164)
{
    const gchar *input = "Hello, World!";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 13 characters * 2 bytes each = 28 bytes
    EXPECT_EQ(result->getLength(), 2 + 13 * 2);
}

// Test with a string containing characters outside BMP (surrogate pairs)
TEST_F(PopplerGooStringFromUtf8Test_2164, SupplementaryPlaneCharacter_2164)
{
    // U+1F600 (😀) - requires surrogate pair in UTF-16
    // UTF-8: F0 9F 98 80
    const gchar *input = "\xF0\x9F\x98\x80";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // BOM (2) + surrogate pair (4 bytes)
    EXPECT_EQ(result->getLength(), 2 + 4);
    const char *data = result->c_str();
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
}

// Test with a single ASCII character
TEST_F(PopplerGooStringFromUtf8Test_2164, SingleAsciiCharacter_2164)
{
    const gchar *input = "A";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // BOM (2) + 1 UTF-16 character (2) = 4 bytes
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(data[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(data[3]), 0x41);
}

// Test with mixed ASCII and non-ASCII UTF-8 characters
TEST_F(PopplerGooStringFromUtf8Test_2164, MixedAsciiAndNonAscii_2164)
{
    // "Aé" -> A is 0x0041, é is 0x00E9 in UTF-16BE
    const gchar *input = "Aé";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // BOM (2) + 2 UTF-16 characters (4) = 6 bytes
    EXPECT_EQ(result->getLength(), 6);
    const char *data = result->c_str();
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(data[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(data[3]), 0x41);
    EXPECT_EQ(static_cast<unsigned char>(data[4]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(data[5]), 0xE9);
}

// Test with CJK character
TEST_F(PopplerGooStringFromUtf8Test_2164, CJKCharacter_2164)
{
    // "中" is U+4E2D, UTF-8: E4 B8 AD, UTF-16BE: 4E 2D
    const gchar *input = "中";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // BOM (2) + 1 UTF-16 character (2) = 4
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(data[2]), 0x4E);
    EXPECT_EQ(static_cast<unsigned char>(data[3]), 0x2D);
}

// Test with string containing null-like but valid UTF-8
TEST_F(PopplerGooStringFromUtf8Test_2164, StringWithSpaces_2164)
{
    const gchar *input = "A B";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // BOM (2) + 3 UTF-16 characters (6) = 8
    EXPECT_EQ(result->getLength(), 8);
}

// Test that the result is a unique_ptr (ownership semantics)
TEST_F(PopplerGooStringFromUtf8Test_2164, ReturnsUniquePtr_2164)
{
    const gchar *input = "test";
    auto result = _poppler_goo_string_from_utf8(input);
    ASSERT_NE(result, nullptr);
    // Verify we can move it
    auto moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    EXPECT_NE(moved, nullptr);
}
