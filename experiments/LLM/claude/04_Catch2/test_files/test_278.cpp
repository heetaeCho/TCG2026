#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>
#include <cstring>

// Include the Catch2 headers needed
#include "catch2/catch_tostring.hpp"

class StringMakerFloatTest_278 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that converting a simple positive float ends with 'f'
TEST_F(StringMakerFloatTest_278, PositiveFloatEndsWithF_278) {
    std::string result = Catch::StringMaker<float>::convert(1.0f);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that converting zero ends with 'f'
TEST_F(StringMakerFloatTest_278, ZeroEndsWithF_278) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that converting a negative float ends with 'f'
TEST_F(StringMakerFloatTest_278, NegativeFloatEndsWithF_278) {
    std::string result = Catch::StringMaker<float>::convert(-1.5f);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that the result is non-empty for a normal value
TEST_F(StringMakerFloatTest_278, ResultIsNonEmpty_278) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

// Test conversion of a very small positive float
TEST_F(StringMakerFloatTest_278, VerySmallPositiveFloat_278) {
    std::string result = Catch::StringMaker<float>::convert(1e-30f);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test conversion of a very large positive float
TEST_F(StringMakerFloatTest_278, VeryLargePositiveFloat_278) {
    std::string result = Catch::StringMaker<float>::convert(1e30f);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test conversion of negative zero
TEST_F(StringMakerFloatTest_278, NegativeZero_278) {
    std::string result = Catch::StringMaker<float>::convert(-0.0f);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test conversion of positive infinity
TEST_F(StringMakerFloatTest_278, PositiveInfinity_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    ASSERT_FALSE(result.empty());
    // Result should end with 'f'
    EXPECT_EQ(result.back(), 'f');
}

// Test conversion of negative infinity
TEST_F(StringMakerFloatTest_278, NegativeInfinity_278) {
    std::string result = Catch::StringMaker<float>::convert(-std::numeric_limits<float>::infinity());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test conversion of NaN
TEST_F(StringMakerFloatTest_278, NaN_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that float max value converts properly
TEST_F(StringMakerFloatTest_278, FloatMax_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::max());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that float min (smallest positive normal) converts properly
TEST_F(StringMakerFloatTest_278, FloatMin_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::min());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that float denorm_min converts properly
TEST_F(StringMakerFloatTest_278, FloatDenormMin_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::denorm_min());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that float epsilon converts properly
TEST_F(StringMakerFloatTest_278, FloatEpsilon_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::epsilon());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test that the string contains some numeric representation for a known value
TEST_F(StringMakerFloatTest_278, ContainsNumericContent_278) {
    std::string result = Catch::StringMaker<float>::convert(42.0f);
    // The result should contain "42" somewhere before the trailing 'f'
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test that 1.5f produces a string containing "1.5"
TEST_F(StringMakerFloatTest_278, KnownValueRepresentation_278) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_NE(result.find("1.5"), std::string::npos);
    EXPECT_EQ(result.back(), 'f');
}

// Test that different values produce different strings
TEST_F(StringMakerFloatTest_278, DifferentValuesProduceDifferentStrings_278) {
    std::string result1 = Catch::StringMaker<float>::convert(1.0f);
    std::string result2 = Catch::StringMaker<float>::convert(2.0f);
    EXPECT_NE(result1, result2);
}

// Test that the string has more than just the 'f' suffix
TEST_F(StringMakerFloatTest_278, StringHasMoreThanJustF_278) {
    std::string result = Catch::StringMaker<float>::convert(1.0f);
    EXPECT_GT(result.size(), 1u);
}

// Test that the lowest float converts properly
TEST_F(StringMakerFloatTest_278, FloatLowest_278) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::lowest());
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), 'f');
}

// Test converting the same value twice produces the same result (determinism)
TEST_F(StringMakerFloatTest_278, DeterministicOutput_278) {
    std::string result1 = Catch::StringMaker<float>::convert(3.14159f);
    std::string result2 = Catch::StringMaker<float>::convert(3.14159f);
    EXPECT_EQ(result1, result2);
}
