#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <climits>

// Include the Catch2 headers needed
#include "catch2/catch_tostring.hpp"

class StringMakerLongTest_270 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal positive value
TEST_F(StringMakerLongTest_270, ConvertPositiveValue_270) {
    std::string result = Catch::StringMaker<long>::convert(42L);
    EXPECT_EQ(result, "42");
}

// Test zero
TEST_F(StringMakerLongTest_270, ConvertZero_270) {
    std::string result = Catch::StringMaker<long>::convert(0L);
    EXPECT_EQ(result, "0");
}

// Test negative value
TEST_F(StringMakerLongTest_270, ConvertNegativeValue_270) {
    std::string result = Catch::StringMaker<long>::convert(-42L);
    EXPECT_EQ(result, "-42");
}

// Test value of 1
TEST_F(StringMakerLongTest_270, ConvertOne_270) {
    std::string result = Catch::StringMaker<long>::convert(1L);
    EXPECT_EQ(result, "1");
}

// Test value of -1
TEST_F(StringMakerLongTest_270, ConvertNegativeOne_270) {
    std::string result = Catch::StringMaker<long>::convert(-1L);
    EXPECT_EQ(result, "-1");
}

// Test LONG_MAX boundary
TEST_F(StringMakerLongTest_270, ConvertLongMax_270) {
    std::string result = Catch::StringMaker<long>::convert(LONG_MAX);
    EXPECT_EQ(result, std::to_string(LONG_MAX));
}

// Test LONG_MIN boundary
TEST_F(StringMakerLongTest_270, ConvertLongMin_270) {
    std::string result = Catch::StringMaker<long>::convert(LONG_MIN);
    EXPECT_EQ(result, std::to_string(LONG_MIN));
}

// Test large positive value
TEST_F(StringMakerLongTest_270, ConvertLargePositive_270) {
    std::string result = Catch::StringMaker<long>::convert(1000000L);
    EXPECT_EQ(result, "1000000");
}

// Test large negative value
TEST_F(StringMakerLongTest_270, ConvertLargeNegative_270) {
    std::string result = Catch::StringMaker<long>::convert(-1000000L);
    EXPECT_EQ(result, "-1000000");
}

// Test that result is non-empty for any value
TEST_F(StringMakerLongTest_270, ResultIsNonEmpty_270) {
    std::string result = Catch::StringMaker<long>::convert(12345L);
    EXPECT_FALSE(result.empty());
}

// Test consistency - same input gives same output
TEST_F(StringMakerLongTest_270, ConsistentResults_270) {
    std::string result1 = Catch::StringMaker<long>::convert(99L);
    std::string result2 = Catch::StringMaker<long>::convert(99L);
    EXPECT_EQ(result1, result2);
}

// Test that different values give different results
TEST_F(StringMakerLongTest_270, DifferentValuesGiveDifferentResults_270) {
    std::string result1 = Catch::StringMaker<long>::convert(1L);
    std::string result2 = Catch::StringMaker<long>::convert(2L);
    EXPECT_NE(result1, result2);
}

// Test that the result matches the long long conversion (since the implementation casts to long long)
TEST_F(StringMakerLongTest_270, MatchesLongLongConversion_270) {
    long value = 12345L;
    std::string longResult = Catch::StringMaker<long>::convert(value);
    std::string longlongResult = Catch::StringMaker<long long>::convert(static_cast<long long>(value));
    EXPECT_EQ(longResult, longlongResult);
}

// Test other integer StringMaker specializations for comparison

class StringMakerIntTest_270 : public ::testing::Test {};

TEST_F(StringMakerIntTest_270, ConvertPositiveInt_270) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerIntTest_270, ConvertZeroInt_270) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerIntTest_270, ConvertNegativeInt_270) {
    std::string result = Catch::StringMaker<int>::convert(-42);
    EXPECT_EQ(result, "-42");
}

class StringMakerLongLongTest_270 : public ::testing::Test {};

TEST_F(StringMakerLongLongTest_270, ConvertPositiveLongLong_270) {
    std::string result = Catch::StringMaker<long long>::convert(42LL);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerLongLongTest_270, ConvertZeroLongLong_270) {
    std::string result = Catch::StringMaker<long long>::convert(0LL);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerLongLongTest_270, ConvertNegativeLongLong_270) {
    std::string result = Catch::StringMaker<long long>::convert(-42LL);
    EXPECT_EQ(result, "-42");
}

TEST_F(StringMakerLongLongTest_270, ConvertLongLongMax_270) {
    std::string result = Catch::StringMaker<long long>::convert(LLONG_MAX);
    EXPECT_EQ(result, std::to_string(LLONG_MAX));
}

TEST_F(StringMakerLongLongTest_270, ConvertLongLongMin_270) {
    std::string result = Catch::StringMaker<long long>::convert(LLONG_MIN);
    EXPECT_EQ(result, std::to_string(LLONG_MIN));
}

class StringMakerUnsignedLongTest_270 : public ::testing::Test {};

TEST_F(StringMakerUnsignedLongTest_270, ConvertUnsignedLong_270) {
    std::string result = Catch::StringMaker<unsigned long>::convert(42UL);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerUnsignedLongTest_270, ConvertUnsignedLongZero_270) {
    std::string result = Catch::StringMaker<unsigned long>::convert(0UL);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerUnsignedLongTest_270, ConvertUnsignedLongMax_270) {
    std::string result = Catch::StringMaker<unsigned long>::convert(ULONG_MAX);
    EXPECT_EQ(result, std::to_string(ULONG_MAX));
}

class StringMakerUnsignedIntTest_270 : public ::testing::Test {};

TEST_F(StringMakerUnsignedIntTest_270, ConvertUnsignedInt_270) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42U);
    EXPECT_EQ(result, "42");
}

class StringMakerUnsignedLongLongTest_270 : public ::testing::Test {};

TEST_F(StringMakerUnsignedLongLongTest_270, ConvertUnsignedLongLong_270) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(42ULL);
    EXPECT_EQ(result, "42");
}

class StringMakerBoolTest_270 : public ::testing::Test {};

TEST_F(StringMakerBoolTest_270, ConvertTrue_270) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerBoolTest_270, ConvertFalse_270) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

class StringMakerFloatTest_270 : public ::testing::Test {};

TEST_F(StringMakerFloatTest_270, ConvertFloatZero_270) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerFloatTest_270, ConvertFloatPositive_270) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_FALSE(result.empty());
    // The result should contain "1.5" in some form
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

class StringMakerDoubleTest_270 : public ::testing::Test {};

TEST_F(StringMakerDoubleTest_270, ConvertDoubleZero_270) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_270, ConvertDoublePositive_270) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

class StringMakerCharTest_270 : public ::testing::Test {};

TEST_F(StringMakerCharTest_270, ConvertCharA_270) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerCharTest_270, ConvertCharSpace_270) {
    std::string result = Catch::StringMaker<char>::convert(' ');
    EXPECT_FALSE(result.empty());
}

class StringMakerSignedCharTest_270 : public ::testing::Test {};

TEST_F(StringMakerSignedCharTest_270, ConvertSignedChar_270) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

class StringMakerUnsignedCharTest_270 : public ::testing::Test {};

TEST_F(StringMakerUnsignedCharTest_270, ConvertUnsignedChar_270) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(65));
    EXPECT_FALSE(result.empty());
}

class StringMakerStringTest_270 : public ::testing::Test {};

TEST_F(StringMakerStringTest_270, ConvertStdString_270) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerStringTest_270, ConvertEmptyString_270) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should have quotes or similar
}

class StringMakerNullptrTest_270 : public ::testing::Test {};

TEST_F(StringMakerNullptrTest_270, ConvertNullptr_270) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}
