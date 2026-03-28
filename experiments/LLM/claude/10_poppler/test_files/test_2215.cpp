#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <memory>

// Poppler headers
#include "poppler/GlobalParams.h"
#include "poppler/UnicodeMap.h"
#include "poppler/CharTypes.h"
#include "goo/GooString.h"

// We need access to the static function. Since it's static in the .cc file,
// we include the source to get access for testing purposes.
// In practice, you might expose this via a test-only header or friend declaration.
#include "glib/poppler-document.cc"

class UnicodeToCharTest_2215 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test: Empty input (length 0) should return an empty string
TEST_F(UnicodeToCharTest_2215, EmptyInput_ReturnsEmptyString_2215) {
    Unicode unicode[] = {};
    gchar *result = unicode_to_char(unicode, 0);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    g_free(result);
}

// Test: Single ASCII character
TEST_F(UnicodeToCharTest_2215, SingleAsciiCharacter_2215) {
    Unicode unicode[] = { 'A' };
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "A");
    g_free(result);
}

// Test: Multiple ASCII characters
TEST_F(UnicodeToCharTest_2215, MultipleAsciiCharacters_2215) {
    Unicode unicode[] = { 'H', 'e', 'l', 'l', 'o' };
    gchar *result = unicode_to_char(unicode, 5);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello");
    g_free(result);
}

// Test: Single non-ASCII Unicode character (e.g., U+00E9 = é)
TEST_F(UnicodeToCharTest_2215, SingleNonAsciiCharacter_2215) {
    Unicode unicode[] = { 0x00E9 }; // é
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    // é in UTF-8 is 0xC3 0xA9
    EXPECT_STREQ(result, "\xC3\xA9");
    g_free(result);
}

// Test: Mixed ASCII and non-ASCII characters
TEST_F(UnicodeToCharTest_2215, MixedAsciiAndNonAscii_2215) {
    Unicode unicode[] = { 'c', 'a', 'f', 0x00E9 }; // café
    gchar *result = unicode_to_char(unicode, 4);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "caf\xC3\xA9");
    g_free(result);
}

// Test: Unicode character requiring 3 bytes in UTF-8 (e.g., U+4E16 = 世)
TEST_F(UnicodeToCharTest_2215, ThreeByteUtf8Character_2215) {
    Unicode unicode[] = { 0x4E16 }; // 世
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    // 世 in UTF-8 is 0xE4 0xB8 0x96
    EXPECT_STREQ(result, "\xE4\xB8\x96");
    g_free(result);
}

// Test: Unicode character requiring 4 bytes in UTF-8 (e.g., U+1F600 = 😀)
TEST_F(UnicodeToCharTest_2215, FourByteUtf8Character_2215) {
    Unicode unicode[] = { 0x1F600 }; // 😀
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    // 😀 in UTF-8 is 0xF0 0x9F 0x98 0x80
    EXPECT_STREQ(result, "\xF0\x9F\x98\x80");
    g_free(result);
}

// Test: Null character (U+0000) - should still produce a valid result
TEST_F(UnicodeToCharTest_2215, NullUnicodeCharacter_2215) {
    Unicode unicode[] = { 0x0000 };
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    // The result for U+0000 mapped through UTF-8 map - at minimum should not crash
    g_free(result);
}

// Test: Length of 1 with a simple space character
TEST_F(UnicodeToCharTest_2215, SpaceCharacter_2215) {
    Unicode unicode[] = { ' ' };
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, " ");
    g_free(result);
}

// Test: Multiple multi-byte characters
TEST_F(UnicodeToCharTest_2215, MultipleMultiByteCharacters_2215) {
    Unicode unicode[] = { 0x4E16, 0x754C }; // 世界
    gchar *result = unicode_to_char(unicode, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "\xE4\xB8\x96\xE7\x95\x8C");
    g_free(result);
}

// Test: Result is a newly allocated string (can be freed independently)
TEST_F(UnicodeToCharTest_2215, ResultIsNewlyAllocated_2215) {
    Unicode unicode[] = { 'T', 'e', 's', 't' };
    gchar *result1 = unicode_to_char(unicode, 4);
    gchar *result2 = unicode_to_char(unicode, 4);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    // Two calls should return different pointers (newly allocated each time)
    EXPECT_NE(result1, result2);
    EXPECT_STREQ(result1, result2);
    g_free(result1);
    g_free(result2);
}

// Test: Subset of array (use only first 3 of 5 characters)
TEST_F(UnicodeToCharTest_2215, SubsetOfArray_2215) {
    Unicode unicode[] = { 'H', 'e', 'l', 'l', 'o' };
    gchar *result = unicode_to_char(unicode, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hel");
    g_free(result);
}

// Test: Various 2-byte UTF-8 characters
TEST_F(UnicodeToCharTest_2215, TwoByteUtf8Characters_2215) {
    Unicode unicode[] = { 0x00FC }; // ü
    gchar *result = unicode_to_char(unicode, 1);
    ASSERT_NE(result, nullptr);
    // ü in UTF-8 is 0xC3 0xBC
    EXPECT_STREQ(result, "\xC3\xBC");
    g_free(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
