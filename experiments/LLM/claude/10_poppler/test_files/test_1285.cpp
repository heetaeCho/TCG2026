#include <gtest/gtest.h>
#include <QString>
#include <memory>

// Forward declare the GooString class and function we're testing
class GooString;

namespace Poppler {
std::unique_ptr<GooString> QStringToGooString(const QString &s);
}

// We need to include the actual headers to get GooString definition
#include "GooString.h"
#include "poppler-private.h"

namespace {

class QStringToGooStringTest_1285 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal ASCII string conversion
TEST_F(QStringToGooStringTest_1285, NormalAsciiString_1285) {
    QString input("Hello");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 5);
    std::string resultStr(result->c_str(), result->getLength());
    EXPECT_EQ(resultStr, "Hello");
}

// Test empty string conversion
TEST_F(QStringToGooStringTest_1285, EmptyString_1285) {
    QString input("");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 0);
}

// Test single character string
TEST_F(QStringToGooStringTest_1285, SingleCharacterString_1285) {
    QString input("A");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 1);
    EXPECT_EQ(result->c_str()[0], 'A');
}

// Test string with digits
TEST_F(QStringToGooStringTest_1285, StringWithDigits_1285) {
    QString input("12345");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 5);
    std::string resultStr(result->c_str(), result->getLength());
    EXPECT_EQ(resultStr, "12345");
}

// Test string with spaces
TEST_F(QStringToGooStringTest_1285, StringWithSpaces_1285) {
    QString input("Hello World");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 11);
    std::string resultStr(result->c_str(), result->getLength());
    EXPECT_EQ(resultStr, "Hello World");
}

// Test string with special ASCII characters
TEST_F(QStringToGooStringTest_1285, SpecialAsciiCharacters_1285) {
    QString input("!@#$%");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 5);
    std::string resultStr(result->c_str(), result->getLength());
    EXPECT_EQ(resultStr, "!@#$%");
}

// Test that the returned GooString length matches QString length
TEST_F(QStringToGooStringTest_1285, LengthMatchesQStringLength_1285) {
    QString input("Test string with some length");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), input.length());
}

// Test string with newline and tab characters
TEST_F(QStringToGooStringTest_1285, StringWithWhitespaceChars_1285) {
    QString input("line1\nline2\ttab");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), input.length());
    EXPECT_EQ(result->c_str()[5], '\n');
    EXPECT_EQ(result->c_str()[11], '\t');
}

// Test that result is a unique_ptr (not null) for non-empty input
TEST_F(QStringToGooStringTest_1285, ReturnsValidUniquePtr_1285) {
    QString input("valid");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
}

// Test longer string
TEST_F(QStringToGooStringTest_1285, LongerString_1285) {
    QString input(QString(1000, QChar('x')));
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 1000);
    // Check first and last characters
    EXPECT_EQ(result->c_str()[0], 'x');
    EXPECT_EQ(result->c_str()[999], 'x');
}

// Test string with null-like character in the middle (low unicode values)
TEST_F(QStringToGooStringTest_1285, StringWithMixedContent_1285) {
    QString input("abc123!@#");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 9);
    std::string resultStr(result->c_str(), result->getLength());
    EXPECT_EQ(resultStr, "abc123!@#");
}

// Test that each character is correctly converted for basic ASCII range
TEST_F(QStringToGooStringTest_1285, CharacterByCharacterVerification_1285) {
    QString input("ABCDE");
    auto result = Poppler::QStringToGooString(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c_str()[0], 'A');
    EXPECT_EQ(result->c_str()[1], 'B');
    EXPECT_EQ(result->c_str()[2], 'C');
    EXPECT_EQ(result->c_str()[3], 'D');
    EXPECT_EQ(result->c_str()[4], 'E');
}

} // namespace
