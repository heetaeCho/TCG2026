#include <gtest/gtest.h>
#include <cstddef>
#include <string>
#include <climits>

// Include the Catch2 headers needed for StringMaker
#include "catch2/catch_tostring.hpp"

// Test fixture for StringMaker<std::byte> tests
class StringMakerByteTest_268 : public ::testing::Test {
protected:
    // Nothing specific needed for setup/teardown
};

// Test: Converting std::byte with value 0
TEST_F(StringMakerByteTest_268, ConvertZeroByte_268) {
    std::byte value = std::byte{0};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "0");
}

// Test: Converting std::byte with value 1
TEST_F(StringMakerByteTest_268, ConvertOneByte_268) {
    std::byte value = std::byte{1};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "1");
}

// Test: Converting std::byte with maximum value (255)
TEST_F(StringMakerByteTest_268, ConvertMaxByte_268) {
    std::byte value = std::byte{255};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "255");
}

// Test: Converting std::byte with value 128 (mid-range)
TEST_F(StringMakerByteTest_268, ConvertMidRangeByte_268) {
    std::byte value = std::byte{128};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "128");
}

// Test: Converting std::byte with value 42 (arbitrary value)
TEST_F(StringMakerByteTest_268, ConvertArbitraryByte_268) {
    std::byte value = std::byte{42};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "42");
}

// Test: Converting std::byte with value 127 (boundary near mid)
TEST_F(StringMakerByteTest_268, ConvertByte127_268) {
    std::byte value = std::byte{127};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "127");
}

// Test: Converting std::byte with value 254 (one less than max)
TEST_F(StringMakerByteTest_268, ConvertByte254_268) {
    std::byte value = std::byte{254};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "254");
}

// Test: Result is a non-empty string for any valid byte
TEST_F(StringMakerByteTest_268, ResultIsNonEmpty_268) {
    for (int i = 0; i < 256; ++i) {
        std::byte value = std::byte{static_cast<unsigned char>(i)};
        std::string result = Catch::StringMaker<std::byte>::convert(value);
        EXPECT_FALSE(result.empty()) << "Result should not be empty for byte value " << i;
    }
}

// Test: Converting std::byte with value 10
TEST_F(StringMakerByteTest_268, ConvertByte10_268) {
    std::byte value = std::byte{10};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "10");
}

// Test: Converting std::byte with value 100
TEST_F(StringMakerByteTest_268, ConvertByte100_268) {
    std::byte value = std::byte{100};
    std::string result = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result, "100");
}

// Test: Consistency - converting the same value twice gives same result
TEST_F(StringMakerByteTest_268, ConsistentConversion_268) {
    std::byte value = std::byte{99};
    std::string result1 = Catch::StringMaker<std::byte>::convert(value);
    std::string result2 = Catch::StringMaker<std::byte>::convert(value);
    EXPECT_EQ(result1, result2);
}

// Test fixture for other StringMaker specializations
class StringMakerIntegralTest_268 : public ::testing::Test {};

// Test: StringMaker<int> with zero
TEST_F(StringMakerIntegralTest_268, ConvertIntZero_268) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

// Test: StringMaker<int> with positive value
TEST_F(StringMakerIntegralTest_268, ConvertIntPositive_268) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

// Test: StringMaker<int> with negative value
TEST_F(StringMakerIntegralTest_268, ConvertIntNegative_268) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

// Test: StringMaker<unsigned int> with zero
TEST_F(StringMakerIntegralTest_268, ConvertUnsignedIntZero_268) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

// Test: StringMaker<unsigned int> with large value
TEST_F(StringMakerIntegralTest_268, ConvertUnsignedIntLarge_268) {
    std::string result = Catch::StringMaker<unsigned int>::convert(4294967295u);
    EXPECT_EQ(result, "4294967295");
}

// Test: StringMaker<long long> with large negative value
TEST_F(StringMakerIntegralTest_268, ConvertLongLongNegative_268) {
    std::string result = Catch::StringMaker<long long>::convert(-9223372036854775807LL);
    EXPECT_FALSE(result.empty());
}

// Test: StringMaker<unsigned long long> with zero
TEST_F(StringMakerIntegralTest_268, ConvertUnsignedLongLongZero_268) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(0ULL);
    EXPECT_EQ(result, "0");
}

// Test fixture for string-related StringMaker tests
class StringMakerStringTest_268 : public ::testing::Test {};

// Test: StringMaker<std::string> with empty string
TEST_F(StringMakerStringTest_268, ConvertEmptyString_268) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should at least contain quotes or something
}

// Test: StringMaker<std::string> with regular string
TEST_F(StringMakerStringTest_268, ConvertRegularString_268) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test: StringMaker<bool> with true
TEST_F(StringMakerStringTest_268, ConvertBoolTrue_268) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

// Test: StringMaker<bool> with false
TEST_F(StringMakerStringTest_268, ConvertBoolFalse_268) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// Test: StringMaker<char> with printable character
TEST_F(StringMakerStringTest_268, ConvertCharPrintable_268) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
}

// Test: StringMaker<float> with zero
TEST_F(StringMakerStringTest_268, ConvertFloatZero_268) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

// Test: StringMaker<double> with a specific value
TEST_F(StringMakerStringTest_268, ConvertDouble_268) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_FALSE(result.empty());
}

// Test: StringMaker<nullptr_t>
TEST_F(StringMakerStringTest_268, ConvertNullptr_268) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}
