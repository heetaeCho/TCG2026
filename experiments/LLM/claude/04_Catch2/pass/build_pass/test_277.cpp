#include <gtest/gtest.h>
#include <string>
#include <cstddef>
#include <chrono>

// Include the Catch2 headers needed for StringMaker
#include "catch2/catch_tostring.hpp"

// Test unsigned char conversion (the specific function in the .cpp file)
TEST(StringMakerUnsignedChar_277, ConvertZero_277) {
    unsigned char value = 0;
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    // Value 0 corresponds to the null character; we just verify it returns a non-empty string
    // (it should stringify static_cast<char>(0))
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, ConvertPrintableChar_277) {
    unsigned char value = 'A'; // 65
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    // Should contain 'A' in some form since it stringifies char('A')
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST(StringMakerUnsignedChar_277, ConvertSmallLetter_277) {
    unsigned char value = 'z'; // 122
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_NE(result.find('z'), std::string::npos);
}

TEST(StringMakerUnsignedChar_277, ConvertSpace_277) {
    unsigned char value = ' '; // 32
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    // Space character should be represented somehow
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, ConvertMaxValue_277) {
    unsigned char value = 255;
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    // 255 cast to char is implementation-defined but should still produce a string
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, ConvertDigitChar_277) {
    unsigned char value = '0'; // 48
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_NE(result.find('0'), std::string::npos);
}

TEST(StringMakerUnsignedChar_277, ConvertNewline_277) {
    unsigned char value = '\n'; // 10
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, ConvertTab_277) {
    unsigned char value = '\t'; // 9
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, Convert127_277) {
    unsigned char value = 127; // DEL character
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, Convert128_277) {
    unsigned char value = 128; // First value above ASCII range
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_277, ConvertOne_277) {
    unsigned char value = 1;
    std::string result = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_FALSE(result.empty());
}

// Test other StringMaker specializations to verify the broader interface

TEST(StringMakerInt_277, ConvertPositive_277) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerInt_277, ConvertNegative_277) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerInt_277, ConvertZero_277) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerLong_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

TEST(StringMakerLongLong_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST(StringMakerUnsignedInt_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerUnsignedLong_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST(StringMakerUnsignedLongLong_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

TEST(StringMakerSignedChar_277, ConvertValue_277) {
    signed char value = 'B';
    std::string result = Catch::StringMaker<signed char>::convert(value);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChar_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<char>::convert('X');
    EXPECT_NE(result.find('X'), std::string::npos);
}

TEST(StringMakerFloat_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain "3.14" approximately
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerDouble_277, ConvertValue_277) {
    std::string result = Catch::StringMaker<double>::convert(2.718);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

TEST(StringMakerBool_277, ConvertTrue_277) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerBool_277, ConvertFalse_277) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST(StringMakerString_277, ConvertSimple_277) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(StringMakerString_277, ConvertEmpty_277) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should still have quotes or similar
}

TEST(StringMakerStringView_277, ConvertValue_277) {
    std::string_view sv = "test_view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("test_view"), std::string::npos);
}

TEST(StringMakerCharPtr_277, ConvertNonNull_277) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(StringMakerNullptr_277, ConvertNullptr_277) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

TEST(StringMakerUnsignedChar_277, MultipleConversionsConsistent_277) {
    unsigned char value = 'M';
    std::string result1 = Catch::StringMaker<unsigned char>::convert(value);
    std::string result2 = Catch::StringMaker<unsigned char>::convert(value);
    EXPECT_EQ(result1, result2);
}

TEST(StringMakerUnsignedChar_277, DifferentValuesProduceDifferentStrings_277) {
    std::string resultA = Catch::StringMaker<unsigned char>::convert('A');
    std::string resultB = Catch::StringMaker<unsigned char>::convert('B');
    EXPECT_NE(resultA, resultB);
}
