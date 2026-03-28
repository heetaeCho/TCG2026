#include <gtest/gtest.h>
#include <string>
#include "catch2/catch_tostring.hpp"

// Tests for StringMaker<char const*>::convert

TEST(StringMakerCharConstPtr_262, ConvertNonNullString_262) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should contain the string content, likely quoted
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(StringMakerCharConstPtr_262, ConvertNullString_262) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

TEST(StringMakerCharConstPtr_262, ConvertEmptyString_262) {
    const char* str = "";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should not be null string representation
    EXPECT_NE(result, "{null string}");
}

TEST(StringMakerCharConstPtr_262, ConvertSingleCharString_262) {
    const char* str = "a";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("a"), std::string::npos);
    EXPECT_NE(result, "{null string}");
}

TEST(StringMakerCharConstPtr_262, ConvertStringWithSpaces_262) {
    const char* str = "hello world";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST(StringMakerCharConstPtr_262, ConvertStringWithSpecialChars_262) {
    const char* str = "line1\nline2";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // The result should represent the string in some form
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerCharConstPtr_262, ConvertLongString_262) {
    std::string longStr(1000, 'x');
    std::string result = Catch::StringMaker<char const*>::convert(longStr.c_str());
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerCharConstPtr_262, ConvertStringWithNullInMiddle_262) {
    // C-string stops at first null terminator
    const char str[] = "abc\0def";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should only contain "abc" portion since it's a C-string
    EXPECT_NE(result.find("abc"), std::string::npos);
    EXPECT_NE(result, "{null string}");
}

TEST(StringMakerCharConstPtr_262, ConvertStringWithQuotes_262) {
    const char* str = "he said \"hi\"";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerCharConstPtr_262, ConvertStringWithTab_262) {
    const char* str = "col1\tcol2";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

// Additional tests for other StringMaker specializations that are available

TEST(StringMakerBool_262, ConvertTrue_262) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerBool_262, ConvertFalse_262) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST(StringMakerInt_262, ConvertPositive_262) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerInt_262, ConvertZero_262) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerInt_262, ConvertNegative_262) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerNullptr_262, ConvertNullptr_262) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChar_262, ConvertChar_262) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST(StringMakerString_262, ConvertStdString_262) {
    std::string input = "test string";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST(StringMakerString_262, ConvertEmptyStdString_262) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result, "{null string}");
}

TEST(StringMakerDouble_262, ConvertDouble_262) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerFloat_262, ConvertFloat_262) {
    std::string result = Catch::StringMaker<float>::convert(2.5f);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

TEST(StringMakerCharPtr_262, ConvertNonNullCharPtr_262) {
    char str[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

TEST(StringMakerUnsignedInt_262, ConvertUnsignedInt_262) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerLongLong_262, ConvertLongLong_262) {
    std::string result = Catch::StringMaker<long long>::convert(123456789LL);
    EXPECT_EQ(result, "123456789");
}
