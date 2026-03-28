#include <gtest/gtest.h>
#include <QString>
#include <memory>
#include "GooString.h"

// Forward declaration of the function under test
namespace Poppler {
    std::unique_ptr<GooString> QStringToUnicodeGooString(const QString &s);
}

class QStringToUnicodeGooStringTest_1284 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with an empty string - should return an empty GooString
TEST_F(QStringToUnicodeGooStringTest_1284, EmptyStringReturnsEmptyGooString_1284) {
    QString input;
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 0);
}

// Test with an explicitly empty QString
TEST_F(QStringToUnicodeGooStringTest_1284, ExplicitlyEmptyStringReturnsEmptyGooString_1284) {
    QString input("");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 0);
}

// Test with a single ASCII character
TEST_F(QStringToUnicodeGooStringTest_1284, SingleAsciiCharacter_1284) {
    QString input("A");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 1 char * 2 bytes = 4 bytes
    EXPECT_EQ(result->getLength(), 4);
    // Check BOM: 0xFE 0xFF
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // 'A' is U+0041, so high byte = 0x00, low byte = 0x41
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0x41);
}

// Test with a simple ASCII string
TEST_F(QStringToUnicodeGooStringTest_1284, SimpleAsciiString_1284) {
    QString input("Hello");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 5 chars * 2 bytes = 12 bytes
    EXPECT_EQ(result->getLength(), 12);
    const char *data = result->c_str();
    // Check BOM
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // Check 'H' = U+0048
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0x48);
    // Check 'e' = U+0065
    EXPECT_EQ((unsigned char)data[4], 0x00);
    EXPECT_EQ((unsigned char)data[5], 0x65);
    // Check 'l' = U+006C
    EXPECT_EQ((unsigned char)data[6], 0x00);
    EXPECT_EQ((unsigned char)data[7], 0x6C);
    // Check 'l' = U+006C
    EXPECT_EQ((unsigned char)data[8], 0x00);
    EXPECT_EQ((unsigned char)data[9], 0x6C);
    // Check 'o' = U+006F
    EXPECT_EQ((unsigned char)data[10], 0x00);
    EXPECT_EQ((unsigned char)data[11], 0x6F);
}

// Test with a non-ASCII Unicode character (e.g., é = U+00E9)
TEST_F(QStringToUnicodeGooStringTest_1284, NonAsciiUnicodeCharacter_1284) {
    QString input = QString::fromUtf8("é");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 1 char * 2 bytes = 4 bytes
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // é = U+00E9 → high byte 0x00, low byte 0xE9
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0xE9);
}

// Test with a CJK character (e.g., 中 = U+4E2D)
TEST_F(QStringToUnicodeGooStringTest_1284, CJKCharacter_1284) {
    QString input = QString::fromUtf8("中");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 1 char * 2 bytes = 4 bytes
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // 中 = U+4E2D → high byte 0x4E, low byte 0x2D
    EXPECT_EQ((unsigned char)data[2], 0x4E);
    EXPECT_EQ((unsigned char)data[3], 0x2D);
}

// Test with mixed ASCII and non-ASCII characters
TEST_F(QStringToUnicodeGooStringTest_1284, MixedAsciiAndNonAscii_1284) {
    QString input = QString::fromUtf8("Aé");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 2 chars * 2 bytes = 6 bytes
    EXPECT_EQ(result->getLength(), 6);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // 'A' = U+0041
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0x41);
    // 'é' = U+00E9
    EXPECT_EQ((unsigned char)data[4], 0x00);
    EXPECT_EQ((unsigned char)data[5], 0xE9);
}

// Test with a null character embedded in the string
TEST_F(QStringToUnicodeGooStringTest_1284, NullCharacterInString_1284) {
    QString input(QChar(0));
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 1 char * 2 bytes = 4 bytes
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0x00);
}

// Test that the result is a unique_ptr (not null)
TEST_F(QStringToUnicodeGooStringTest_1284, ResultIsNonNull_1284) {
    QString input("test");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
}

// Test with a longer string to verify length calculation
TEST_F(QStringToUnicodeGooStringTest_1284, LongerStringLengthCorrect_1284) {
    QString input("abcdefghij"); // 10 characters
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2 bytes) + 10 chars * 2 bytes = 22 bytes
    EXPECT_EQ(result->getLength(), 22);
}

// Test with a single space character
TEST_F(QStringToUnicodeGooStringTest_1284, SpaceCharacter_1284) {
    QString input(" ");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // ' ' = U+0020
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0x20);
}

// Test BOM is always present for non-empty strings
TEST_F(QStringToUnicodeGooStringTest_1284, BOMPresent_1284) {
    QString input("x");
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    ASSERT_GE(result->getLength(), 2);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
}

// Test with a character in the higher BMP range (e.g., U+FFFD replacement character)
TEST_F(QStringToUnicodeGooStringTest_1284, HighBMPCharacter_1284) {
    QString input(QChar(0xFFFD));
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 4);
    const char *data = result->c_str();
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // U+FFFD → high byte 0xFF, low byte 0xFD
    EXPECT_EQ((unsigned char)data[2], 0xFF);
    EXPECT_EQ((unsigned char)data[3], 0xFD);
}

// Test with multiple Unicode characters from different blocks
TEST_F(QStringToUnicodeGooStringTest_1284, MultipleUnicodeBlocks_1284) {
    QString input;
    input.append(QChar(0x0041)); // Latin A
    input.append(QChar(0x03B1)); // Greek alpha
    input.append(QChar(0x4E2D)); // CJK 中
    auto result = Poppler::QStringToUnicodeGooString(input);
    ASSERT_NE(result, nullptr);
    // BOM (2) + 3*2 = 8
    EXPECT_EQ(result->getLength(), 8);
    const char *data = result->c_str();
    // BOM
    EXPECT_EQ((unsigned char)data[0], 0xFE);
    EXPECT_EQ((unsigned char)data[1], 0xFF);
    // A = U+0041
    EXPECT_EQ((unsigned char)data[2], 0x00);
    EXPECT_EQ((unsigned char)data[3], 0x41);
    // α = U+03B1
    EXPECT_EQ((unsigned char)data[4], 0x03);
    EXPECT_EQ((unsigned char)data[5], 0xB1);
    // 中 = U+4E2D
    EXPECT_EQ((unsigned char)data[6], 0x4E);
    EXPECT_EQ((unsigned char)data[7], 0x2D);
}
