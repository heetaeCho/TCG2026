#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <cstddef>

// Include the Catch2 headers needed for StringMaker
#include "catch2/catch_tostring.hpp"

// Test unsigned int conversion
TEST(StringMakerUnsignedInt_272, Zero_272) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerUnsignedInt_272, One_272) {
    std::string result = Catch::StringMaker<unsigned int>::convert(1u);
    EXPECT_EQ(result, "1");
}

TEST(StringMakerUnsignedInt_272, TypicalValue_272) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerUnsignedInt_272, MaxValue_272) {
    unsigned int maxVal = std::numeric_limits<unsigned int>::max();
    std::string result = Catch::StringMaker<unsigned int>::convert(maxVal);
    EXPECT_EQ(result, std::to_string(maxVal));
}

TEST(StringMakerUnsignedInt_272, LargeValue_272) {
    std::string result = Catch::StringMaker<unsigned int>::convert(1000000u);
    EXPECT_EQ(result, "1000000");
}

TEST(StringMakerUnsignedInt_272, PowerOfTwo_272) {
    std::string result = Catch::StringMaker<unsigned int>::convert(1024u);
    EXPECT_EQ(result, "1024");
}

TEST(StringMakerUnsignedInt_272, ResultIsNotEmpty_272) {
    std::string result = Catch::StringMaker<unsigned int>::convert(123u);
    EXPECT_FALSE(result.empty());
}

// Test int conversion
TEST(StringMakerInt_272, Zero_272) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerInt_272, PositiveValue_272) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerInt_272, NegativeValue_272) {
    std::string result = Catch::StringMaker<int>::convert(-42);
    EXPECT_EQ(result, "-42");
}

TEST(StringMakerInt_272, MaxValue_272) {
    int maxVal = std::numeric_limits<int>::max();
    std::string result = Catch::StringMaker<int>::convert(maxVal);
    EXPECT_EQ(result, std::to_string(maxVal));
}

TEST(StringMakerInt_272, MinValue_272) {
    int minVal = std::numeric_limits<int>::min();
    std::string result = Catch::StringMaker<int>::convert(minVal);
    EXPECT_EQ(result, std::to_string(minVal));
}

// Test long long conversion
TEST(StringMakerLongLong_272, Zero_272) {
    std::string result = Catch::StringMaker<long long>::convert(0LL);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerLongLong_272, LargePositive_272) {
    long long val = 9999999999LL;
    std::string result = Catch::StringMaker<long long>::convert(val);
    EXPECT_EQ(result, "9999999999");
}

TEST(StringMakerLongLong_272, LargeNegative_272) {
    long long val = -9999999999LL;
    std::string result = Catch::StringMaker<long long>::convert(val);
    EXPECT_EQ(result, "-9999999999");
}

// Test unsigned long long conversion
TEST(StringMakerUnsignedLongLong_272, Zero_272) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(0ULL);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerUnsignedLongLong_272, MaxValue_272) {
    unsigned long long maxVal = std::numeric_limits<unsigned long long>::max();
    std::string result = Catch::StringMaker<unsigned long long>::convert(maxVal);
    EXPECT_EQ(result, std::to_string(maxVal));
}

// Test bool conversion
TEST(StringMakerBool_272, True_272) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerBool_272, False_272) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// Test char conversion
TEST(StringMakerChar_272, PrintableChar_272) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    // Should contain the character 'A' somewhere in the representation
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST(StringMakerChar_272, Space_272) {
    std::string result = Catch::StringMaker<char>::convert(' ');
    EXPECT_FALSE(result.empty());
}

// Test string conversion
TEST(StringMakerString_272, EmptyString_272) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should at least have quotes or something
}

TEST(StringMakerString_272, NormalString_272) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test nullptr conversion
TEST(StringMakerNullptr_272, Nullptr_272) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// Test float conversion
TEST(StringMakerFloat_272, Zero_272) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerFloat_272, PositiveValue_272) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST(StringMakerFloat_272, NegativeValue_272) {
    std::string result = Catch::StringMaker<float>::convert(-3.14f);
    EXPECT_FALSE(result.empty());
}

// Test double conversion
TEST(StringMakerDouble_272, Zero_272) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerDouble_272, Pi_272) {
    std::string result = Catch::StringMaker<double>::convert(3.14159265358979);
    EXPECT_FALSE(result.empty());
}

// Test unsigned long conversion
TEST(StringMakerUnsignedLong_272, Zero_272) {
    std::string result = Catch::StringMaker<unsigned long>::convert(0UL);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerUnsignedLong_272, MaxValue_272) {
    unsigned long maxVal = std::numeric_limits<unsigned long>::max();
    std::string result = Catch::StringMaker<unsigned long>::convert(maxVal);
    EXPECT_EQ(result, std::to_string(maxVal));
}

// Test long conversion
TEST(StringMakerLong_272, Zero_272) {
    std::string result = Catch::StringMaker<long>::convert(0L);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerLong_272, NegativeValue_272) {
    std::string result = Catch::StringMaker<long>::convert(-100L);
    EXPECT_EQ(result, "-100");
}

// Test signed char conversion
TEST(StringMakerSignedChar_272, Zero_272) {
    std::string result = Catch::StringMaker<signed char>::convert(0);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerSignedChar_272, PositiveValue_272) {
    std::string result = Catch::StringMaker<signed char>::convert(65);
    EXPECT_FALSE(result.empty());
}

// Test unsigned char conversion
TEST(StringMakerUnsignedChar_272, Zero_272) {
    std::string result = Catch::StringMaker<unsigned char>::convert(0);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerUnsignedChar_272, MaxValue_272) {
    std::string result = Catch::StringMaker<unsigned char>::convert(255);
    EXPECT_FALSE(result.empty());
}

// Test consistency: converting same value twice yields same result
TEST(StringMakerConsistency_272, UnsignedIntConsistent_272) {
    std::string result1 = Catch::StringMaker<unsigned int>::convert(12345u);
    std::string result2 = Catch::StringMaker<unsigned int>::convert(12345u);
    EXPECT_EQ(result1, result2);
}

TEST(StringMakerConsistency_272, IntConsistent_272) {
    std::string result1 = Catch::StringMaker<int>::convert(-999);
    std::string result2 = Catch::StringMaker<int>::convert(-999);
    EXPECT_EQ(result1, result2);
}

// Test that different values produce different strings
TEST(StringMakerDistinct_272, DifferentUnsignedIntsProduceDifferentStrings_272) {
    std::string result1 = Catch::StringMaker<unsigned int>::convert(1u);
    std::string result2 = Catch::StringMaker<unsigned int>::convert(2u);
    EXPECT_NE(result1, result2);
}

// Test pointer conversion
TEST(StringMakerPointer_272, NullPointer_272) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerPointer_272, NonNullPointer_272) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// Test const char* conversion
TEST(StringMakerCharPtr_272, NullCString_272) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerCharPtr_272, NonNullCString_272) {
    const char* str = "test";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("test"), std::string::npos);
}

// Test wstring conversion
TEST(StringMakerWString_272, EmptyWString_272) {
    std::wstring ws;
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty()); // Should at least produce quotes or empty repr
}

TEST(StringMakerWString_272, NonEmptyWString_272) {
    std::wstring ws = L"hello";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

// Test string_view conversion
TEST(StringMakerStringView_272, EmptyStringView_272) {
    std::string_view sv;
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerStringView_272, NonEmptyStringView_272) {
    std::string_view sv = "world";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("world"), std::string::npos);
}

// Test std::byte conversion
TEST(StringMakerByte_272, ZeroByte_272) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerByte_272, MaxByte_272) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}
