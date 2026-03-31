#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <cstddef>
#include <chrono>

// Include the header for StringMaker
#include "catch2/catch_tostring.hpp"

// Test fixture for StringMaker tests
class StringMakerTest_269 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ========== int tests ==========

TEST_F(StringMakerTest_269, ConvertIntZero_269) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_269, ConvertIntPositive_269) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_269, ConvertIntNegative_269) {
    std::string result = Catch::StringMaker<int>::convert(-42);
    EXPECT_EQ(result, "-42");
}

TEST_F(StringMakerTest_269, ConvertIntMax_269) {
    std::string result = Catch::StringMaker<int>::convert(INT_MAX);
    EXPECT_EQ(result, std::to_string(INT_MAX));
}

TEST_F(StringMakerTest_269, ConvertIntMin_269) {
    std::string result = Catch::StringMaker<int>::convert(INT_MIN);
    EXPECT_EQ(result, std::to_string(INT_MIN));
}

TEST_F(StringMakerTest_269, ConvertIntOne_269) {
    std::string result = Catch::StringMaker<int>::convert(1);
    EXPECT_EQ(result, "1");
}

TEST_F(StringMakerTest_269, ConvertIntNegativeOne_269) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

// ========== long tests ==========

TEST_F(StringMakerTest_269, ConvertLongZero_269) {
    std::string result = Catch::StringMaker<long>::convert(0L);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_269, ConvertLongPositive_269) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

TEST_F(StringMakerTest_269, ConvertLongNegative_269) {
    std::string result = Catch::StringMaker<long>::convert(-123456L);
    EXPECT_EQ(result, "-123456");
}

TEST_F(StringMakerTest_269, ConvertLongMax_269) {
    std::string result = Catch::StringMaker<long>::convert(LONG_MAX);
    EXPECT_EQ(result, std::to_string(LONG_MAX));
}

TEST_F(StringMakerTest_269, ConvertLongMin_269) {
    std::string result = Catch::StringMaker<long>::convert(LONG_MIN);
    EXPECT_EQ(result, std::to_string(LONG_MIN));
}

// ========== long long tests ==========

TEST_F(StringMakerTest_269, ConvertLongLongZero_269) {
    std::string result = Catch::StringMaker<long long>::convert(0LL);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_269, ConvertLongLongPositive_269) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST_F(StringMakerTest_269, ConvertLongLongNegative_269) {
    std::string result = Catch::StringMaker<long long>::convert(-9876543210LL);
    EXPECT_EQ(result, "-9876543210");
}

TEST_F(StringMakerTest_269, ConvertLongLongMax_269) {
    std::string result = Catch::StringMaker<long long>::convert(LLONG_MAX);
    EXPECT_EQ(result, std::to_string(LLONG_MAX));
}

TEST_F(StringMakerTest_269, ConvertLongLongMin_269) {
    std::string result = Catch::StringMaker<long long>::convert(LLONG_MIN);
    EXPECT_EQ(result, std::to_string(LLONG_MIN));
}

// ========== unsigned int tests ==========

TEST_F(StringMakerTest_269, ConvertUnsignedIntZero_269) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_269, ConvertUnsignedIntPositive_269) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_269, ConvertUnsignedIntMax_269) {
    std::string result = Catch::StringMaker<unsigned int>::convert(UINT_MAX);
    EXPECT_EQ(result, std::to_string(UINT_MAX));
}

// ========== unsigned long tests ==========

TEST_F(StringMakerTest_269, ConvertUnsignedLongZero_269) {
    std::string result = Catch::StringMaker<unsigned long>::convert(0UL);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_269, ConvertUnsignedLongPositive_269) {
    std::string result = Catch::StringMaker<unsigned long>::convert(123456UL);
    EXPECT_EQ(result, "123456");
}

TEST_F(StringMakerTest_269, ConvertUnsignedLongMax_269) {
    std::string result = Catch::StringMaker<unsigned long>::convert(ULONG_MAX);
    EXPECT_EQ(result, std::to_string(ULONG_MAX));
}

// ========== unsigned long long tests ==========

TEST_F(StringMakerTest_269, ConvertUnsignedLongLongZero_269) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(0ULL);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_269, ConvertUnsignedLongLongPositive_269) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(9876543210ULL);
    EXPECT_EQ(result, "9876543210");
}

TEST_F(StringMakerTest_269, ConvertUnsignedLongLongMax_269) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(ULLONG_MAX);
    EXPECT_EQ(result, std::to_string(ULLONG_MAX));
}

// ========== bool tests ==========

TEST_F(StringMakerTest_269, ConvertBoolTrue_269) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_269, ConvertBoolFalse_269) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ========== char tests ==========

TEST_F(StringMakerTest_269, ConvertCharA_269) {
    std::string result = Catch::StringMaker<char>::convert('A');
    // The result should contain 'A' in some representation
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST_F(StringMakerTest_269, ConvertCharZero_269) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertCharSpace_269) {
    std::string result = Catch::StringMaker<char>::convert(' ');
    EXPECT_FALSE(result.empty());
}

// ========== signed char tests ==========

TEST_F(StringMakerTest_269, ConvertSignedCharPositive_269) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertSignedCharNegative_269) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(-1));
    EXPECT_FALSE(result.empty());
}

// ========== unsigned char tests ==========

TEST_F(StringMakerTest_269, ConvertUnsignedCharZero_269) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(0));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertUnsignedCharMax_269) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// ========== float tests ==========

TEST_F(StringMakerTest_269, ConvertFloatZero_269) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    // Should contain "0" somewhere
    EXPECT_NE(result.find('0'), std::string::npos);
}

TEST_F(StringMakerTest_269, ConvertFloatPositive_269) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertFloatNegative_269) {
    std::string result = Catch::StringMaker<float>::convert(-2.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

// ========== double tests ==========

TEST_F(StringMakerTest_269, ConvertDoubleZero_269) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertDoublePositive_269) {
    std::string result = Catch::StringMaker<double>::convert(3.14159265358979);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertDoubleNegative_269) {
    std::string result = Catch::StringMaker<double>::convert(-1.0);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

TEST_F(StringMakerTest_269, ConvertDoubleLargeValue_269) {
    std::string result = Catch::StringMaker<double>::convert(1e300);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertDoubleSmallValue_269) {
    std::string result = Catch::StringMaker<double>::convert(1e-300);
    EXPECT_FALSE(result.empty());
}

// ========== string tests ==========

TEST_F(StringMakerTest_269, ConvertStringEmpty_269) {
    std::string result = Catch::StringMaker<std::string>::convert(std::string(""));
    EXPECT_FALSE(result.empty()); // Should at least have quotes or something
}

TEST_F(StringMakerTest_269, ConvertStringNormal_269) {
    std::string result = Catch::StringMaker<std::string>::convert(std::string("hello"));
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_269, ConvertStringWithSpecialChars_269) {
    std::string result = Catch::StringMaker<std::string>::convert(std::string("hello\nworld"));
    EXPECT_FALSE(result.empty());
}

// ========== string_view tests ==========

TEST_F(StringMakerTest_269, ConvertStringViewEmpty_269) {
    std::string result = Catch::StringMaker<std::string_view>::convert(std::string_view(""));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertStringViewNormal_269) {
    std::string result = Catch::StringMaker<std::string_view>::convert(std::string_view("test"));
    EXPECT_NE(result.find("test"), std::string::npos);
}

// ========== const char* tests ==========

TEST_F(StringMakerTest_269, ConvertCharPtrNormal_269) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_269, ConvertCharPtrNull_269) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ========== nullptr_t tests ==========

TEST_F(StringMakerTest_269, ConvertNullptr_269) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    // Typically "nullptr" but we don't assume exact format
}

// ========== pointer tests ==========

TEST_F(StringMakerTest_269, ConvertPointerNull_269) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertPointerNonNull_269) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ========== std::byte tests ==========

TEST_F(StringMakerTest_269, ConvertByteZero_269) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertByteMax_269) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertByteMidValue_269) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{127});
    EXPECT_FALSE(result.empty());
}

// ========== Consistency tests ==========

TEST_F(StringMakerTest_269, ConvertIntConsistency_269) {
    // Same value should produce same result
    std::string result1 = Catch::StringMaker<int>::convert(42);
    std::string result2 = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerTest_269, ConvertDifferentIntsDifferentResults_269) {
    std::string result1 = Catch::StringMaker<int>::convert(42);
    std::string result2 = Catch::StringMaker<int>::convert(43);
    EXPECT_NE(result1, result2);
}

TEST_F(StringMakerTest_269, ConvertIntNotEmpty_269) {
    std::string result = Catch::StringMaker<int>::convert(100);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "100");
}

// ========== Boundary: int near zero ==========

TEST_F(StringMakerTest_269, ConvertIntMinusTwo_269) {
    EXPECT_EQ(Catch::StringMaker<int>::convert(-2), "-2");
}

TEST_F(StringMakerTest_269, ConvertIntTwo_269) {
    EXPECT_EQ(Catch::StringMaker<int>::convert(2), "2");
}

// ========== wstring tests ==========

TEST_F(StringMakerTest_269, ConvertWStringEmpty_269) {
    std::string result = Catch::StringMaker<std::wstring>::convert(std::wstring(L""));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_269, ConvertWStringNormal_269) {
    std::string result = Catch::StringMaker<std::wstring>::convert(std::wstring(L"hello"));
    EXPECT_FALSE(result.empty());
}
