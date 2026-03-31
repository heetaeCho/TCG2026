#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <chrono>
#include <cstddef>
#include <sstream>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// ============================================================
// Tests for StringMaker with various types
// ============================================================

// --- Integer types ---

TEST(StringMakerTest_91, ConvertInt_91) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerTest_91, ConvertIntZero_91) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerTest_91, ConvertNegativeInt_91) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerTest_91, ConvertLong_91) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

TEST(StringMakerTest_91, ConvertLongLong_91) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST(StringMakerTest_91, ConvertUnsignedInt_91) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerTest_91, ConvertUnsignedLong_91) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST(StringMakerTest_91, ConvertUnsignedLongLong_91) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

// --- Boolean ---

TEST(StringMakerTest_91, ConvertBoolTrue_91) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerTest_91, ConvertBoolFalse_91) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// --- Char types ---

TEST(StringMakerTest_91, ConvertChar_91) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertSignedChar_91) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertUnsignedChar_91) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// --- Floating point types ---

TEST(StringMakerTest_91, ConvertFloat_91) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain some representation of 3.14
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertDouble_91) {
    std::string result = Catch::StringMaker<double>::convert(2.718281828);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertFloatZero_91) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertDoubleNegative_91) {
    std::string result = Catch::StringMaker<double>::convert(-1.5);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-1.5"), std::string::npos);
}

// --- String types ---

TEST(StringMakerTest_91, ConvertStdString_91) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertStdStringEmpty_91) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should at least have quotes or something
}

TEST(StringMakerTest_91, ConvertCharConstPointer_91) {
    const char* str = "test string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertCharPointer_91) {
    char str[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertStringView_91) {
    std::string_view sv = "view test";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("view test"), std::string::npos);
}

// --- nullptr ---

TEST(StringMakerTest_91, ConvertNullptr_91) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    // Typically "nullptr" or "NULL" or "0"
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// --- Pointer types ---

TEST(StringMakerTest_91, ConvertNullPointer_91) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertNonNullPointer_91) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
    // Should contain some hex address representation
}

// --- std::byte ---

TEST(StringMakerTest_91, ConvertStdByte_91) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertStdByteZero_91) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// --- Containers / Ranges ---

TEST(StringMakerTest_91, ConvertVectorInt_91) {
    std::vector<int> v = {1, 2, 3};
    std::string result = Catch::StringMaker<std::vector<int>>::convert(v);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertEmptyVector_91) {
    std::vector<int> v;
    std::string result = Catch::StringMaker<std::vector<int>>::convert(v);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertVectorString_91) {
    std::vector<std::string> v = {"hello", "world"};
    std::string result = Catch::StringMaker<std::vector<std::string>>::convert(v);
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("world"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertSetInt_91) {
    std::set<int> s = {10, 20, 30};
    std::string result = Catch::StringMaker<std::set<int>>::convert(s);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

// --- Chrono durations ---

TEST(StringMakerTest_91, ConvertChronoMilliseconds_91) {
    auto dur = std::chrono::milliseconds(500);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("500"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertChronoSeconds_91) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertChronoMinutes_91) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertChronoHours_91) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertChronoMicroseconds_91) {
    auto dur = std::chrono::microseconds(1234);
    std::string result = Catch::StringMaker<std::chrono::microseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1234"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertChronoNanoseconds_91) {
    auto dur = std::chrono::nanoseconds(999);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("999"), std::string::npos);
}

TEST(StringMakerTest_91, ConvertChronoZeroDuration_91) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

// --- Boundary tests for integer types ---

TEST(StringMakerTest_91, ConvertIntMax_91) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertIntMin_91) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertUnsignedLongLongMax_91) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(
        std::numeric_limits<unsigned long long>::max());
    EXPECT_FALSE(result.empty());
}

// --- Special floating point values ---

TEST(StringMakerTest_91, ConvertFloatInfinity_91) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertFloatNegInfinity_91) {
    std::string result = Catch::StringMaker<float>::convert(-std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertFloatNaN_91) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertDoubleInfinity_91) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertDoubleNaN_91) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

// --- Wide string types ---

TEST(StringMakerTest_91, ConvertWstring_91) {
    std::wstring ws = L"wide string";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertWstringEmpty_91) {
    std::wstring ws;
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertWcharConstPointer_91) {
    const wchar_t* ws = L"wchar test";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertWcharPointer_91) {
    wchar_t ws[] = L"mutable wchar";
    std::string result = Catch::StringMaker<wchar_t*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

// --- C-style array ---

TEST(StringMakerTest_91, ConvertCStyleArrayInt_91) {
    int arr[] = {1, 2, 3, 4, 5};
    std::string result = Catch::StringMaker<int[5]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
}

// --- Map container ---

TEST(StringMakerTest_91, ConvertMap_91) {
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
    std::string result = Catch::StringMaker<std::map<std::string, int>>::convert(m);
    EXPECT_FALSE(result.empty());
}

// --- Pair (if streamable or has StringMaker specialization) ---

TEST(StringMakerTest_91, ConvertVectorOfPairs_91) {
    std::vector<std::pair<int, int>> v = {{1, 2}, {3, 4}};
    std::string result = Catch::StringMaker<std::vector<std::pair<int, int>>>::convert(v);
    EXPECT_FALSE(result.empty());
}

// --- Single element vector ---

TEST(StringMakerTest_91, ConvertSingleElementVector_91) {
    std::vector<int> v = {42};
    std::string result = Catch::StringMaker<std::vector<int>>::convert(v);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
}

// --- String with special characters ---

TEST(StringMakerTest_91, ConvertStringWithSpecialChars_91) {
    std::string s = "hello\nworld\ttab";
    std::string result = Catch::StringMaker<std::string>::convert(s);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertStringWithQuotes_91) {
    std::string s = "he said \"hi\"";
    std::string result = Catch::StringMaker<std::string>::convert(s);
    EXPECT_FALSE(result.empty());
}

// --- Char edge cases ---

TEST(StringMakerTest_91, ConvertNullChar_91) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertNewlineChar_91) {
    std::string result = Catch::StringMaker<char>::convert('\n');
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_91, ConvertTabChar_91) {
    std::string result = Catch::StringMaker<char>::convert('\t');
    EXPECT_FALSE(result.empty());
}
