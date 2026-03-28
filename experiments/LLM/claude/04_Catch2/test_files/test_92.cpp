#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <chrono>
#include <cstddef>

#include "catch2/catch_tostring.hpp"

// Tests for StringMaker with C-style arrays
TEST(StringMakerArrayTest_92, IntArrayConversion_92) {
    int arr[] = {1, 2, 3};
    std::string result = Catch::StringMaker<int[3]>::convert(arr);
    // Should produce some string representation of the array
    EXPECT_FALSE(result.empty());
    // The result should contain the elements
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST(StringMakerArrayTest_92, SingleElementArray_92) {
    int arr[] = {42};
    std::string result = Catch::StringMaker<int[1]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST(StringMakerArrayTest_92, DoubleArrayConversion_92) {
    double arr[] = {1.5, 2.5};
    std::string result = Catch::StringMaker<double[2]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1.5"), std::string::npos);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

TEST(StringMakerArrayTest_92, CharArrayConversion_92) {
    char arr[] = {'a', 'b', 'c'};
    std::string result = Catch::StringMaker<char[3]>::convert(arr);
    EXPECT_FALSE(result.empty());
}

// Tests for basic types
TEST(StringMakerBasicTypes_92, IntConversion_92) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_92, NegativeIntConversion_92) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerBasicTypes_92, ZeroIntConversion_92) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerBasicTypes_92, LongConversion_92) {
    std::string result = Catch::StringMaker<long>::convert(123456789L);
    EXPECT_EQ(result, "123456789");
}

TEST(StringMakerBasicTypes_92, LongLongConversion_92) {
    std::string result = Catch::StringMaker<long long>::convert(123456789012345LL);
    EXPECT_EQ(result, "123456789012345");
}

TEST(StringMakerBasicTypes_92, UnsignedIntConversion_92) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_92, UnsignedLongConversion_92) {
    std::string result = Catch::StringMaker<unsigned long>::convert(42UL);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_92, UnsignedLongLongConversion_92) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(42ULL);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_92, FloatConversion_92) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST(StringMakerBasicTypes_92, DoubleConversion_92) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerBasicTypes_92, BoolTrueConversion_92) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerBasicTypes_92, BoolFalseConversion_92) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST(StringMakerBasicTypes_92, CharConversion_92) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST(StringMakerBasicTypes_92, SignedCharConversion_92) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBasicTypes_92, UnsignedCharConversion_92) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(65));
    EXPECT_FALSE(result.empty());
}

// Tests for string types
TEST(StringMakerStringTypes_92, StdStringConversion_92) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST(StringMakerStringTypes_92, EmptyStdStringConversion_92) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty()); // Should at least have quotes or something
}

TEST(StringMakerStringTypes_92, CharPointerConversion_92) {
    const char* str = "test string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST(StringMakerStringTypes_92, NullCharPointerConversion_92) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerStringTypes_92, StringViewConversion_92) {
    std::string_view sv = "string_view test";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("string_view test"), std::string::npos);
}

// Tests for pointer types
TEST(StringMakerPointerTypes_92, NullptrConversion_92) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    // Should indicate null in some way
}

TEST(StringMakerPointerTypes_92, IntPointerConversion_92) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerPointerTypes_92, NullIntPointerConversion_92) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// Tests for std::byte
TEST(StringMakerByteTest_92, ByteConversion_92) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerByteTest_92, ZeroByteConversion_92) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// Tests for chrono types
TEST(StringMakerChronoTest_92, MillisecondsConversion_92) {
    auto dur = std::chrono::milliseconds(500);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("500"), std::string::npos);
}

TEST(StringMakerChronoTest_92, SecondsConversion_92) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
}

TEST(StringMakerChronoTest_92, MinutesConversion_92) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5"), std::string::npos);
}

TEST(StringMakerChronoTest_92, HoursConversion_92) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST(StringMakerChronoTest_92, ZeroDurationConversion_92) {
    auto dur = std::chrono::milliseconds(0);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST(StringMakerChronoTest_92, NegativeDurationConversion_92) {
    auto dur = std::chrono::milliseconds(-100);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Tests for arrays of different sizes
TEST(StringMakerArrayTest_92, LargeIntArray_92) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::string result = Catch::StringMaker<int[10]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
}

TEST(StringMakerArrayTest_92, StringArrayConversion_92) {
    std::string arr[] = {"hello", "world"};
    std::string result = Catch::StringMaker<std::string[2]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("world"), std::string::npos);
}

TEST(StringMakerArrayTest_92, BoolArrayConversion_92) {
    bool arr[] = {true, false, true};
    std::string result = Catch::StringMaker<bool[3]>::convert(arr);
    EXPECT_FALSE(result.empty());
}

// Tests for wstring types
TEST(StringMakerWStringTypes_92, WStringConversion_92) {
    std::wstring input = L"wide string";
    std::string result = Catch::StringMaker<std::wstring>::convert(input);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerWStringTypes_92, EmptyWStringConversion_92) {
    std::wstring input = L"";
    std::string result = Catch::StringMaker<std::wstring>::convert(input);
    EXPECT_FALSE(result.empty()); // Should at least have quotes or representation
}

TEST(StringMakerWStringTypes_92, WCharPointerConversion_92) {
    const wchar_t* str = L"wchar test";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// Edge cases for numeric types
TEST(StringMakerEdgeCases_92, MaxIntConversion_92) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerEdgeCases_92, MinIntConversion_92) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerEdgeCases_92, MaxUnsignedLongLongConversion_92) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(std::numeric_limits<unsigned long long>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerEdgeCases_92, DoubleInfinityConversion_92) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerEdgeCases_92, DoubleNaNConversion_92) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerEdgeCases_92, FloatInfinityConversion_92) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerEdgeCases_92, FloatNaNConversion_92) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

// Test for vector (range-based)
TEST(StringMakerRangeTest_92, VectorIntConversion_92) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string result = Catch::StringMaker<std::vector<int>>::convert(vec);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
}

TEST(StringMakerRangeTest_92, EmptyVectorConversion_92) {
    std::vector<int> vec;
    std::string result = Catch::StringMaker<std::vector<int>>::convert(vec);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerRangeTest_92, VectorStringConversion_92) {
    std::vector<std::string> vec = {"foo", "bar"};
    std::string result = Catch::StringMaker<std::vector<std::string>>::convert(vec);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("foo"), std::string::npos);
    EXPECT_NE(result.find("bar"), std::string::npos);
}
