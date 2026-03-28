#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/exceptions.h"

TEST(BadSubscriptWithKey_87, ReturnsStringContainingBadSubscriptMessage_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("testkey");
    // Should contain the base BAD_SUBSCRIPT message
    EXPECT_NE(result.find(YAML::ErrorMsg::BAD_SUBSCRIPT), std::string::npos);
}

TEST(BadSubscriptWithKey_87, ReturnsStringContainingTheKey_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("mykey");
    EXPECT_NE(result.find("mykey"), std::string::npos);
}

TEST(BadSubscriptWithKey_87, FormatsKeyWithParenthesesAndQuotes_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("foo");
    // Expected format: "operator[] call on a scalar (key: \"foo\")"
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"foo\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, EmptyKey_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("");
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, KeyWithSpecialCharacters_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("key with spaces & symbols!@#");
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"key with spaces & symbols!@#\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, KeyWithQuotes_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("key\"with\"quotes");
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"key\"with\"quotes\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, KeyWithNewlines_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("line1\nline2");
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"line1\nline2\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, KeyWithNullCharacterInMiddle_87) {
    // Passing a C-string that terminates at the null
    const char key[] = "abc";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"abc\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, LongKey_87) {
    std::string longKey(1000, 'x');
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(longKey.c_str());
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"" + longKey + "\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, SingleCharacterKey_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("a");
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"a\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptWithKey_87, NumericKey_87) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY("12345");
    std::string expected = std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"12345\")";
    EXPECT_EQ(result, expected);
}

TEST(BadSubscriptConstant_87, BadSubscriptIsExpectedValue_87) {
    EXPECT_STREQ(YAML::ErrorMsg::BAD_SUBSCRIPT, "operator[] call on a scalar");
}
