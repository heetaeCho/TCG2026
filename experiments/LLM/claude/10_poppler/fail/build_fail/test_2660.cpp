#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include GooString header
#include "goo/GooString.h"

// Include the .cc file to access the static function
// This is necessary because EscapeSpecialChars is static (file-scoped)
#include "utils/HtmlLinks.cc"

class EscapeSpecialCharsTest_2660 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: String with no special characters returns nullptr (no copy needed)
TEST_F(EscapeSpecialCharsTest_2660, NoSpecialChars_ReturnsNull_2660) {
    GooString input("Hello World");
    auto result = EscapeSpecialChars(&input);
    EXPECT_EQ(result, nullptr);
}

// Test: Empty string returns nullptr
TEST_F(EscapeSpecialCharsTest_2660, EmptyString_ReturnsNull_2660) {
    GooString input("");
    auto result = EscapeSpecialChars(&input);
    EXPECT_EQ(result, nullptr);
}

// Test: String with double quote is escaped
TEST_F(EscapeSpecialCharsTest_2660, DoubleQuoteEscaped_2660) {
    GooString input("say \"hello\"");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "say &quot;hello&quot;");
}

// Test: String with ampersand is escaped
TEST_F(EscapeSpecialCharsTest_2660, AmpersandEscaped_2660) {
    GooString input("a&b");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "a&amp;b");
}

// Test: String with less-than sign is escaped
TEST_F(EscapeSpecialCharsTest_2660, LessThanEscaped_2660) {
    GooString input("a<b");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "a&lt;b");
}

// Test: String with greater-than sign is escaped
TEST_F(EscapeSpecialCharsTest_2660, GreaterThanEscaped_2660) {
    GooString input("a>b");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "a&gt;b");
}

// Test: String with all four special characters
TEST_F(EscapeSpecialCharsTest_2660, AllSpecialCharsEscaped_2660) {
    GooString input("\"&<>");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&quot;&amp;&lt;&gt;");
}

// Test: String with special characters mixed with normal text
TEST_F(EscapeSpecialCharsTest_2660, MixedContent_2660) {
    GooString input("Hello <world> & \"friends\"");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "Hello &lt;world&gt; &amp; &quot;friends&quot;");
}

// Test: String with only one special character
TEST_F(EscapeSpecialCharsTest_2660, SingleSpecialChar_2660) {
    GooString input("&");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&amp;");
}

// Test: String with consecutive special characters
TEST_F(EscapeSpecialCharsTest_2660, ConsecutiveSpecialChars_2660) {
    GooString input("<<>>");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&lt;&lt;&gt;&gt;");
}

// Test: Special character at the beginning
TEST_F(EscapeSpecialCharsTest_2660, SpecialCharAtBeginning_2660) {
    GooString input("<hello");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&lt;hello");
}

// Test: Special character at the end
TEST_F(EscapeSpecialCharsTest_2660, SpecialCharAtEnd_2660) {
    GooString input("hello>");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "hello&gt;");
}

// Test: Long string with no special characters
TEST_F(EscapeSpecialCharsTest_2660, LongStringNoSpecialChars_2660) {
    GooString input("This is a fairly long string with no special characters at all just normal text 1234567890");
    auto result = EscapeSpecialChars(&input);
    EXPECT_EQ(result, nullptr);
}

// Test: String with multiple ampersands
TEST_F(EscapeSpecialCharsTest_2660, MultipleAmpersands_2660) {
    GooString input("a&b&c&d");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "a&amp;b&amp;c&amp;d");
}

// Test: Already escaped-looking string (should still escape the ampersand)
TEST_F(EscapeSpecialCharsTest_2660, AlreadyEscapedLooking_2660) {
    GooString input("&amp;");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&amp;amp;");
}

// Test: Single character strings that are special
TEST_F(EscapeSpecialCharsTest_2660, SingleCharQuote_2660) {
    GooString input("\"");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&quot;");
}

TEST_F(EscapeSpecialCharsTest_2660, SingleCharLessThan_2660) {
    GooString input("<");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&lt;");
}

TEST_F(EscapeSpecialCharsTest_2660, SingleCharGreaterThan_2660) {
    GooString input(">");
    auto result = EscapeSpecialChars(&input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->toStr().c_str(), "&gt;");
}

// Test: Original string is not modified
TEST_F(EscapeSpecialCharsTest_2660, OriginalStringUnmodified_2660) {
    GooString input("a<b");
    std::string originalContent = input.toStr();
    auto result = EscapeSpecialChars(&input);
    EXPECT_EQ(input.toStr(), originalContent);
}

// Test: Single non-special character returns null
TEST_F(EscapeSpecialCharsTest_2660, SingleNonSpecialChar_2660) {
    GooString input("a");
    auto result = EscapeSpecialChars(&input);
    EXPECT_EQ(result, nullptr);
}
