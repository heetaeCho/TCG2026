#include <gtest/gtest.h>
#include <QString>
#include <vector>
#include "poppler-private.h"
#include "GlobalParams.h"
#include "CharTypes.h"

// Ensure globalParams is initialized before tests run
class UnicodeToQStringTest_1282 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test with empty input (len == 0)
TEST_F(UnicodeToQStringTest_1282, EmptyInput_1282) {
    Unicode u[] = { 0 };
    QString result = Poppler::unicodeToQString(u, 0);
    EXPECT_TRUE(result.isEmpty());
}

// Test with a single ASCII character
TEST_F(UnicodeToQStringTest_1282, SingleAsciiCharacter_1282) {
    Unicode u[] = { 'A' };
    QString result = Poppler::unicodeToQString(u, 1);
    EXPECT_EQ(result, QString("A"));
}

// Test with multiple ASCII characters
TEST_F(UnicodeToQStringTest_1282, MultipleAsciiCharacters_1282) {
    Unicode u[] = { 'H', 'e', 'l', 'l', 'o' };
    QString result = Poppler::unicodeToQString(u, 5);
    EXPECT_EQ(result, QString("Hello"));
}

// Test trailing null characters are stripped
TEST_F(UnicodeToQStringTest_1282, TrailingNullsAreStripped_1282) {
    Unicode u[] = { 'A', 'B', 0, 0, 0 };
    QString result = Poppler::unicodeToQString(u, 5);
    EXPECT_EQ(result, QString("AB"));
}

// Test all null characters results in empty string
TEST_F(UnicodeToQStringTest_1282, AllNullCharacters_1282) {
    Unicode u[] = { 0, 0, 0 };
    QString result = Poppler::unicodeToQString(u, 3);
    EXPECT_TRUE(result.isEmpty());
}

// Test with a single null character
TEST_F(UnicodeToQStringTest_1282, SingleNullCharacter_1282) {
    Unicode u[] = { 0 };
    QString result = Poppler::unicodeToQString(u, 1);
    EXPECT_TRUE(result.isEmpty());
}

// Test with non-ASCII Unicode characters (e.g., accented characters)
TEST_F(UnicodeToQStringTest_1282, NonAsciiUnicode_1282) {
    // U+00E9 is 'é'
    Unicode u[] = { 0x00E9 };
    QString result = Poppler::unicodeToQString(u, 1);
    EXPECT_EQ(result, QString::fromUtf8("\xC3\xA9"));
}

// Test with CJK character
TEST_F(UnicodeToQStringTest_1282, CJKCharacter_1282) {
    // U+4E2D is '中'
    Unicode u[] = { 0x4E2D };
    QString result = Poppler::unicodeToQString(u, 1);
    EXPECT_EQ(result, QString::fromUtf8("\xE4\xB8\xAD"));
}

// Test with mixed ASCII and Unicode characters
TEST_F(UnicodeToQStringTest_1282, MixedAsciiAndUnicode_1282) {
    Unicode u[] = { 'H', 0x00E9, 'l', 'l', 'o' };
    QString result = Poppler::unicodeToQString(u, 5);
    EXPECT_EQ(result, QString::fromUtf8("H\xC3\xA9llo"));
}

// Test with embedded null (not trailing)
TEST_F(UnicodeToQStringTest_1282, EmbeddedNullNotTrailing_1282) {
    Unicode u[] = { 'A', 0, 'B' };
    QString result = Poppler::unicodeToQString(u, 3);
    // Trailing 'B' is not null, so len stays 3
    // The embedded null should be handled by mapUnicode
    EXPECT_EQ(result.length(), 3);  // 'A', null char, 'B'
}

// Test with emoji / supplementary plane character
TEST_F(UnicodeToQStringTest_1282, SupplementaryPlaneCharacter_1282) {
    // U+1F600 is '😀' (Grinning Face)
    Unicode u[] = { 0x1F600 };
    QString result = Poppler::unicodeToQString(u, 1);
    // In UTF-16 (QString), this is a surrogate pair
    EXPECT_EQ(result, QString::fromUcs4(reinterpret_cast<const uint*>(u), 1));
}

// Test with trailing nulls and a single valid character
TEST_F(UnicodeToQStringTest_1282, SingleCharWithTrailingNulls_1282) {
    Unicode u[] = { 'X', 0, 0, 0, 0 };
    QString result = Poppler::unicodeToQString(u, 5);
    EXPECT_EQ(result, QString("X"));
}

// Test with space characters
TEST_F(UnicodeToQStringTest_1282, SpaceCharacters_1282) {
    Unicode u[] = { ' ', ' ', ' ' };
    QString result = Poppler::unicodeToQString(u, 3);
    EXPECT_EQ(result, QString("   "));
}

// Test with numeric digits
TEST_F(UnicodeToQStringTest_1282, NumericDigits_1282) {
    Unicode u[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    QString result = Poppler::unicodeToQString(u, 10);
    EXPECT_EQ(result, QString("0123456789"));
}

// Test with special ASCII characters
TEST_F(UnicodeToQStringTest_1282, SpecialAsciiCharacters_1282) {
    Unicode u[] = { '!', '@', '#', '$', '%' };
    QString result = Poppler::unicodeToQString(u, 5);
    EXPECT_EQ(result, QString("!@#$%"));
}

// Test with large array of characters
TEST_F(UnicodeToQStringTest_1282, LargeArray_1282) {
    const int size = 1000;
    std::vector<Unicode> u(size, 'A');
    QString result = Poppler::unicodeToQString(u.data(), size);
    EXPECT_EQ(result.length(), size);
    EXPECT_EQ(result, QString(size, 'A'));
}

// Test that only trailing nulls are stripped (not leading or middle)
TEST_F(UnicodeToQStringTest_1282, OnlyTrailingNullsStripped_1282) {
    Unicode u[] = { 0, 'A', 0, 'B', 0 };
    QString result = Poppler::unicodeToQString(u, 5);
    // Trailing null stripped, effective len = 4: {0, 'A', 0, 'B'}
    EXPECT_EQ(result.length(), 4);
}

// Test with BOM character
TEST_F(UnicodeToQStringTest_1282, BOMCharacter_1282) {
    Unicode u[] = { 0xFEFF, 'A', 'B' };
    QString result = Poppler::unicodeToQString(u, 3);
    // BOM should be converted as a regular character
    EXPECT_FALSE(result.isEmpty());
    EXPECT_TRUE(result.endsWith("AB"));
}

// Test with multiple different non-ASCII chars
TEST_F(UnicodeToQStringTest_1282, MultipleNonAscii_1282) {
    // U+00C0 'À', U+00D1 'Ñ', U+00FC 'ü'
    Unicode u[] = { 0x00C0, 0x00D1, 0x00FC };
    QString result = Poppler::unicodeToQString(u, 3);
    QString expected = QString::fromUtf8("\xC3\x80\xC3\x91\xC3\xBC");
    EXPECT_EQ(result, expected);
}
