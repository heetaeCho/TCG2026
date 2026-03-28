#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <chrono>

#include "catch2/catch_tostring.hpp"

// Test fixture for StringMaker tests
class StringMakerTest_83 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Tests for basic integer types ====================

TEST_F(StringMakerTest_83, ConvertInt_83) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_83, ConvertIntZero_83) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_83, ConvertNegativeInt_83) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerTest_83, ConvertLong_83) {
    std::string result = Catch::StringMaker<long>::convert(100000L);
    EXPECT_EQ(result, "100000");
}

TEST_F(StringMakerTest_83, ConvertLongLong_83) {
    std::string result = Catch::StringMaker<long long>::convert(9999999999LL);
    EXPECT_EQ(result, "9999999999");
}

TEST_F(StringMakerTest_83, ConvertUnsignedInt_83) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_83, ConvertUnsignedLong_83) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100000UL);
    EXPECT_EQ(result, "100000");
}

TEST_F(StringMakerTest_83, ConvertUnsignedLongLong_83) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(9999999999ULL);
    EXPECT_EQ(result, "9999999999");
}

// ==================== Tests for char types ====================

TEST_F(StringMakerTest_83, ConvertChar_83) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    // Should contain 'A' somewhere in the representation
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertSignedChar_83) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertUnsignedChar_83) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(65));
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for bool ====================

TEST_F(StringMakerTest_83, ConvertBoolTrue_83) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_83, ConvertBoolFalse_83) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ==================== Tests for floating point types ====================

TEST_F(StringMakerTest_83, ConvertFloat_83) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain "3.14" as part of the representation
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertFloatZero_83) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertDouble_83) {
    std::string result = Catch::StringMaker<double>::convert(3.14159);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertDoubleZero_83) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for string types ====================

TEST_F(StringMakerTest_83, ConvertStdString_83) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertStdStringEmpty_83) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should still have quotes or similar
}

TEST_F(StringMakerTest_83, ConvertStringView_83) {
    std::string_view sv = "test_view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test_view"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertCharConstPtr_83) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertCharPtr_83) {
    char str[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertCharConstPtrNull_83) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for nullptr ====================

TEST_F(StringMakerTest_83, ConvertNullptr_83) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// ==================== Tests for pointer types ====================

TEST_F(StringMakerTest_83, ConvertPointerNonNull_83) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertPointerNull_83) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for unsigned char arrays (the specific code provided) ====================

TEST_F(StringMakerTest_83, ConvertUnsignedCharArray_83) {
    unsigned char arr[] = "Hello";
    // The array specialization should convert unsigned char arrays
    std::string result = Catch::StringMaker<unsigned char[6]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Hello"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertUnsignedCharArraySingleChar_83) {
    unsigned char arr[] = "A";
    std::string result = Catch::StringMaker<unsigned char[2]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertUnsignedCharArrayEmpty_83) {
    unsigned char arr[] = "";
    std::string result = Catch::StringMaker<unsigned char[1]>::convert(arr);
    EXPECT_FALSE(result.empty()); // Should still produce quoted empty string or similar
}

TEST_F(StringMakerTest_83, ConvertSignedCharConstPtr_83) {
    signed char str[] = "test";
    std::string result = Catch::StringMaker<signed char const*>::convert(
        reinterpret_cast<signed char const*>(str));
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for std::byte ====================

TEST_F(StringMakerTest_83, ConvertStdByte_83) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertStdByteZero_83) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for chrono durations ====================

TEST_F(StringMakerTest_83, ConvertChronoDurationNanoseconds_83) {
    auto dur = std::chrono::nanoseconds(500);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertChronoDurationMilliseconds_83) {
    auto dur = std::chrono::milliseconds(100);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertChronoDurationSeconds_83) {
    auto dur = std::chrono::seconds(5);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "s" for seconds
    EXPECT_NE(result.find("s"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertChronoDurationMinutes_83) {
    auto dur = std::chrono::minutes(2);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "m" for minutes
    EXPECT_NE(result.find("m"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertChronoDurationHours_83) {
    auto dur = std::chrono::hours(3);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "h" for hours
    EXPECT_NE(result.find("h"), std::string::npos);
}

TEST_F(StringMakerTest_83, ConvertChronoDurationZero_83) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for wstring types ====================

TEST_F(StringMakerTest_83, ConvertWstring_83) {
    std::wstring ws = L"wide";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertWstringEmpty_83) {
    std::wstring ws = L"";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertWstringView_83) {
    std::wstring_view wsv = L"wide_view";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertWcharConstPtr_83) {
    const wchar_t* ws = L"wchar";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertWcharPtr_83) {
    wchar_t ws[] = L"wchar_mut";
    std::string result = Catch::StringMaker<wchar_t*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

// ==================== Boundary tests for integer limits ====================

TEST_F(StringMakerTest_83, ConvertIntMax_83) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertIntMin_83) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertUnsignedIntMax_83) {
    std::string result = Catch::StringMaker<unsigned int>::convert(std::numeric_limits<unsigned int>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertLongLongMax_83) {
    std::string result = Catch::StringMaker<long long>::convert(std::numeric_limits<long long>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertLongLongMin_83) {
    std::string result = Catch::StringMaker<long long>::convert(std::numeric_limits<long long>::min());
    EXPECT_FALSE(result.empty());
}

// ==================== Boundary tests for floating point ====================

TEST_F(StringMakerTest_83, ConvertFloatInfinity_83) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertFloatNegativeInfinity_83) {
    std::string result = Catch::StringMaker<float>::convert(-std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertFloatNaN_83) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertDoubleInfinity_83) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_83, ConvertDoubleNaN_83) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

// ==================== Tests for char array with embedded null ====================

TEST_F(StringMakerTest_83, ConvertUnsignedCharArrayWithNullInMiddle_83) {
    unsigned char arr[6] = {'H', 'e', '\0', 'l', 'o', '\0'};
    std::string result = Catch::StringMaker<unsigned char[6]>::convert(arr);
    // The convert function uses catch_strnlen, so it should stop at first null
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("He"), std::string::npos);
}

// ==================== Tests for char arrays ====================

TEST_F(StringMakerTest_83, ConvertCharArray_83) {
    char arr[] = "TestArray";
    std::string result = Catch::StringMaker<char[10]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("TestArray"), std::string::npos);
}
