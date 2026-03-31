#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>
#include <cstddef>
#include <chrono>

// Include Catch2 headers needed for StringMaker
#include "catch2/catch_tostring.hpp"

class StringMakerDoubleTest_279 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation tests

TEST_F(StringMakerDoubleTest_279, ConvertZero_279) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
    // 0.0 should produce a string containing "0"
    EXPECT_NE(result.find('0'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertPositiveInteger_279) {
    std::string result = Catch::StringMaker<double>::convert(1.0);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('1'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertNegativeInteger_279) {
    std::string result = Catch::StringMaker<double>::convert(-1.0);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
    EXPECT_NE(result.find('1'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertPositiveDecimal_279) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('3'), std::string::npos);
    EXPECT_NE(result.find('.'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertNegativeDecimal_279) {
    std::string result = Catch::StringMaker<double>::convert(-2.718);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertSmallPositive_279) {
    std::string result = Catch::StringMaker<double>::convert(0.001);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertLargePositive_279) {
    std::string result = Catch::StringMaker<double>::convert(1e15);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertVerySmallPositive_279) {
    std::string result = Catch::StringMaker<double>::convert(1e-300);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertVeryLargePositive_279) {
    std::string result = Catch::StringMaker<double>::convert(1e300);
    EXPECT_FALSE(result.empty());
}

// Boundary condition tests

TEST_F(StringMakerDoubleTest_279, ConvertInfinity_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
    // Should contain "inf" in some form
    std::string lower = result;
    for (auto& c : lower) c = std::tolower(c);
    EXPECT_NE(lower.find("inf"), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertNegativeInfinity_279) {
    std::string result = Catch::StringMaker<double>::convert(-std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    for (auto& c : lower) c = std::tolower(c);
    EXPECT_NE(lower.find("inf"), std::string::npos);
    EXPECT_NE(result.find('-'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertNaN_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    for (auto& c : lower) c = std::tolower(c);
    EXPECT_NE(lower.find("nan"), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertMaxDouble_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertMinDouble_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::min());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertLowestDouble_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::lowest());
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

TEST_F(StringMakerDoubleTest_279, ConvertDenormMin_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::denorm_min());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertEpsilon_279) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::epsilon());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_279, ConvertNegativeZero_279) {
    std::string result = Catch::StringMaker<double>::convert(-0.0);
    EXPECT_FALSE(result.empty());
}

// Consistency tests

TEST_F(StringMakerDoubleTest_279, SameValueProducesSameString_279) {
    std::string result1 = Catch::StringMaker<double>::convert(3.14159265358979);
    std::string result2 = Catch::StringMaker<double>::convert(3.14159265358979);
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerDoubleTest_279, DifferentValuesProduceDifferentStrings_279) {
    std::string result1 = Catch::StringMaker<double>::convert(1.0);
    std::string result2 = Catch::StringMaker<double>::convert(2.0);
    EXPECT_NE(result1, result2);
}

// Test other StringMaker specializations that are part of the interface

class StringMakerFloatTest_279 : public ::testing::Test {};

TEST_F(StringMakerFloatTest_279, ConvertFloat_279) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerFloatTest_279, ConvertFloatNaN_279) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    for (auto& c : lower) c = std::tolower(c);
    EXPECT_NE(lower.find("nan"), std::string::npos);
}

TEST_F(StringMakerFloatTest_279, ConvertFloatInfinity_279) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    for (auto& c : lower) c = std::tolower(c);
    EXPECT_NE(lower.find("inf"), std::string::npos);
}

class StringMakerIntTest_279 : public ::testing::Test {};

TEST_F(StringMakerIntTest_279, ConvertInt_279) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerIntTest_279, ConvertNegativeInt_279) {
    std::string result = Catch::StringMaker<int>::convert(-42);
    EXPECT_EQ(result, "-42");
}

TEST_F(StringMakerIntTest_279, ConvertZeroInt_279) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

class StringMakerBoolTest_279 : public ::testing::Test {};

TEST_F(StringMakerBoolTest_279, ConvertTrue_279) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerBoolTest_279, ConvertFalse_279) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

class StringMakerStringTest_279 : public ::testing::Test {};

TEST_F(StringMakerStringTest_279, ConvertString_279) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerStringTest_279, ConvertEmptyString_279) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should produce quoted empty string or similar
}

class StringMakerCharTest_279 : public ::testing::Test {};

TEST_F(StringMakerCharTest_279, ConvertChar_279) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('A'), std::string::npos);
}

class StringMakerNullptrTest_279 : public ::testing::Test {};

TEST_F(StringMakerNullptrTest_279, ConvertNullptr_279) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    for (auto& c : lower) c = std::tolower(c);
    EXPECT_NE(lower.find("null"), std::string::npos);
}

class StringMakerLongLongTest_279 : public ::testing::Test {};

TEST_F(StringMakerLongLongTest_279, ConvertLongLong_279) {
    std::string result = Catch::StringMaker<long long>::convert(1234567890123LL);
    EXPECT_EQ(result, "1234567890123");
}

TEST_F(StringMakerLongLongTest_279, ConvertNegativeLongLong_279) {
    std::string result = Catch::StringMaker<long long>::convert(-1234567890123LL);
    EXPECT_EQ(result, "-1234567890123");
}

class StringMakerUnsignedTest_279 : public ::testing::Test {};

TEST_F(StringMakerUnsignedTest_279, ConvertUnsignedInt_279) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerUnsignedTest_279, ConvertUnsignedLongLong_279) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(18446744073709551615ULL);
    EXPECT_EQ(result, "18446744073709551615");
}

class StringMakerSignedCharTest_279 : public ::testing::Test {};

TEST_F(StringMakerSignedCharTest_279, ConvertSignedChar_279) {
    std::string result = Catch::StringMaker<signed char>::convert(65);
    EXPECT_FALSE(result.empty());
}

class StringMakerUnsignedCharTest_279 : public ::testing::Test {};

TEST_F(StringMakerUnsignedCharTest_279, ConvertUnsignedChar_279) {
    std::string result = Catch::StringMaker<unsigned char>::convert(255);
    EXPECT_FALSE(result.empty());
}

class StringMakerCharPtrTest_279 : public ::testing::Test {};

TEST_F(StringMakerCharPtrTest_279, ConvertCharConstPtr_279) {
    const char* str = "test string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerCharPtrTest_279, ConvertNullCharConstPtr_279) {
    std::string result = Catch::StringMaker<char const*>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}
