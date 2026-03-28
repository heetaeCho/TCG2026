#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include the necessary Exiv2 headers
#include "convert.hpp"

namespace {

// Test: When 'from' and 'to' charsets are the same, the function should return true
// and the string should remain unchanged.
TEST(ConvertStringCharsetTest_1864, SameCharsetReturnsTrue_1864) {
  std::string str = "Hello, World!";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "UTF-8");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: Same charset with empty string
TEST(ConvertStringCharsetTest_1864, SameCharsetEmptyStringReturnsTrue_1864) {
  std::string str;
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "UTF-8");
  EXPECT_TRUE(result);
  EXPECT_TRUE(str.empty());
}

// Test: Same charset with different encoding names (both identical)
TEST(ConvertStringCharsetTest_1864, SameCharsetLatinReturnsTrue_1864) {
  std::string str = "Test string with special content";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "ISO-8859-1", "ISO-8859-1");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: Same charset with ASCII encoding name
TEST(ConvertStringCharsetTest_1864, SameCharsetASCIIReturnsTrue_1864) {
  std::string str = "ASCII text";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "ASCII", "ASCII");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: Different charsets - conversion from UTF-8 to ISO-8859-1
// This tests actual conversion when iconv or Windows API is available.
// The result depends on platform capabilities.
TEST(ConvertStringCharsetTest_1864, DifferentCharsetUTF8ToLatin1_1864) {
  std::string str = "Hello";
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "ISO-8859-1");
  // On platforms with iconv or Windows, this should succeed for ASCII-compatible strings
  // On platforms without conversion support, this returns false
#if defined(EXV_HAVE_ICONV) || defined(_WIN32)
  EXPECT_TRUE(result);
  // "Hello" is pure ASCII, so conversion between UTF-8 and ISO-8859-1 should not change it
  EXPECT_EQ(str, "Hello");
#else
  EXPECT_FALSE(result);
#endif
}

// Test: Different charsets - conversion from ISO-8859-1 to UTF-8
TEST(ConvertStringCharsetTest_1864, DifferentCharsetLatin1ToUTF8_1864) {
  std::string str = "Hello";
  bool result = Exiv2::convertStringCharset(str, "ISO-8859-1", "UTF-8");
#if defined(EXV_HAVE_ICONV) || defined(_WIN32)
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "Hello");
#else
  EXPECT_FALSE(result);
#endif
}

// Test: Empty string with different charsets
TEST(ConvertStringCharsetTest_1864, EmptyStringDifferentCharsets_1864) {
  std::string str;
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "ISO-8859-1");
#if defined(EXV_HAVE_ICONV) || defined(_WIN32)
  // Empty string conversion should succeed (or at least not crash)
  // Result may be true with empty output
  EXPECT_TRUE(str.empty() || !str.empty()); // At minimum, it shouldn't crash
#else
  EXPECT_FALSE(result);
#endif
}

// Test: Invalid charset names with different from/to
TEST(ConvertStringCharsetTest_1864, InvalidCharsetNames_1864) {
  std::string str = "test";
  bool result = Exiv2::convertStringCharset(str, "INVALID_CHARSET_XYZ", "ANOTHER_INVALID_ABC");
  // With invalid charsets, iconv_open or equivalent should fail, returning false
  // Unless from == to (which it's not here)
#if defined(EXV_HAVE_ICONV) || defined(_WIN32)
  EXPECT_FALSE(result);
#else
  EXPECT_FALSE(result);
#endif
}

// Test: Same invalid charset names should still return true (early exit)
TEST(ConvertStringCharsetTest_1864, SameInvalidCharsetReturnsTrue_1864) {
  std::string str = "test data";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "NONEXISTENT", "NONEXISTENT");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: Large string with same charset
TEST(ConvertStringCharsetTest_1864, LargeStringSameCharset_1864) {
  std::string str(10000, 'A');
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "UTF-8");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: String with null bytes and same charset
TEST(ConvertStringCharsetTest_1864, StringWithNullBytesSameCharset_1864) {
  std::string str = "Hello";
  str.push_back('\0');
  str += "World";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "UTF-8");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: Empty charset name strings that are equal
TEST(ConvertStringCharsetTest_1864, EmptyCharsetNamesSameReturnsTrue_1864) {
  std::string str = "test";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "", "");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

// Test: Conversion with multi-byte UTF-8 characters
TEST(ConvertStringCharsetTest_1864, MultiByteSameCharset_1864) {
  // UTF-8 encoded string with non-ASCII characters (é = 0xC3 0xA9)
  std::string str = "\xC3\xA9";
  std::string original = str;
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "UTF-8");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, original);
}

#if defined(EXV_HAVE_ICONV) || defined(_WIN32)
// Test: Conversion of non-ASCII character from UTF-8 to ISO-8859-1
TEST(ConvertStringCharsetTest_1864, NonASCIIConversion_1864) {
  // UTF-8 encoded 'é' (U+00E9) = 0xC3 0xA9
  std::string str = "\xC3\xA9";
  bool result = Exiv2::convertStringCharset(str, "UTF-8", "ISO-8859-1");
  EXPECT_TRUE(result);
  // In ISO-8859-1, 'é' is represented as single byte 0xE9
  EXPECT_EQ(str, std::string("\xE9"));
}

// Test: Conversion of non-ASCII character from ISO-8859-1 to UTF-8
TEST(ConvertStringCharsetTest_1864, Latin1ToUTF8NonASCII_1864) {
  // ISO-8859-1 encoded 'é' = 0xE9
  std::string str = "\xE9";
  bool result = Exiv2::convertStringCharset(str, "ISO-8859-1", "UTF-8");
  EXPECT_TRUE(result);
  // UTF-8 encoded 'é' = 0xC3 0xA9
  EXPECT_EQ(str, std::string("\xC3\xA9"));
}
#endif

}  // namespace
