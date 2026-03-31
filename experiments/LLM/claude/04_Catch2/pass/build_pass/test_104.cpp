#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <cstddef>
#include <sstream>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Helper to invoke StringMaker::convert via Catch::Detail::stringify
// We use Catch::StringMaker directly where possible.

class StringMakerTest_104 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for integer types
// ============================================================

TEST_F(StringMakerTest_104, ConvertInt_Zero_104) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_104, ConvertInt_Positive_104) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_104, ConvertInt_Negative_104) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerTest_104, ConvertLong_104) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

TEST_F(StringMakerTest_104, ConvertLongLong_104) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST_F(StringMakerTest_104, ConvertUnsignedInt_104) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_104, ConvertUnsignedLong_104) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerTest_104, ConvertUnsignedLongLong_104) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

// ============================================================
// Tests for bool
// ============================================================

TEST_F(StringMakerTest_104, ConvertBool_True_104) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_104, ConvertBool_False_104) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ============================================================
// Tests for char types
// ============================================================

TEST_F(StringMakerTest_104, ConvertChar_104) {
    std::string result = Catch::StringMaker<char>::convert('A');
    // Should contain 'A' somewhere in the output
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertSignedChar_104) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertUnsignedChar_104) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for float / double
// ============================================================

TEST_F(StringMakerTest_104, ConvertFloat_Zero_104) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    // Should represent zero somehow
    EXPECT_NE(result.find('0'), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertFloat_Positive_104) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDouble_Positive_104) {
    std::string result = Catch::StringMaker<double>::convert(2.718);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2.718"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDouble_Negative_104) {
    std::string result = Catch::StringMaker<double>::convert(-1.5);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-1.5"), std::string::npos);
}

// ============================================================
// Tests for string types
// ============================================================

TEST_F(StringMakerTest_104, ConvertString_104) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertString_Empty_104) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // Should return something representing an empty string (e.g., "\"\"")
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertStringView_104) {
    std::string_view sv = "test_view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("test_view"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertCharConstPtr_104) {
    const char* str = "c-string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("c-string"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertCharPtr_104) {
    char buf[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(buf);
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

// ============================================================
// Tests for nullptr
// ============================================================

TEST_F(StringMakerTest_104, ConvertNullptr_104) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// ============================================================
// Tests for pointer types
// ============================================================

TEST_F(StringMakerTest_104, ConvertPointer_NonNull_104) {
    int x = 42;
    std::string result = Catch::StringMaker<int*>::convert(&x);
    // Should contain some hex representation or "0x"
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertPointer_Null_104) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    // Should contain "nullptr" or "0" or "null"
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for std::byte
// ============================================================

TEST_F(StringMakerTest_104, ConvertByte_Zero_104) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertByte_Max_104) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for chrono::duration
// ============================================================

TEST_F(StringMakerTest_104, ConvertDuration_Nanoseconds_104) {
    auto dur = std::chrono::nanoseconds(500);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("ns"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDuration_Microseconds_104) {
    auto dur = std::chrono::microseconds(100);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("us"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDuration_Milliseconds_104) {
    auto dur = std::chrono::milliseconds(250);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("ms"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDuration_Seconds_104) {
    auto dur = std::chrono::seconds(5);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("s"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDuration_Minutes_104) {
    auto dur = std::chrono::minutes(3);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("m"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDuration_Hours_104) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("h"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDuration_Zero_104) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ============================================================
// Tests for chrono::time_point (non-system_clock)
// ============================================================

TEST_F(StringMakerTest_104, ConvertTimePoint_SteadyClock_104) {
    // steady_clock time_point should produce "X since epoch" format
    auto tp = std::chrono::steady_clock::time_point(std::chrono::milliseconds(1000));
    std::string result = Catch::Detail::stringify(tp);
    EXPECT_NE(result.find("since epoch"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertTimePoint_SteadyClock_Zero_104) {
    auto tp = std::chrono::steady_clock::time_point{};
    std::string result = Catch::Detail::stringify(tp);
    EXPECT_NE(result.find("since epoch"), std::string::npos);
}

// ============================================================
// Tests for chrono::time_point (system_clock)
// ============================================================

TEST_F(StringMakerTest_104, ConvertTimePoint_SystemClock_104) {
    // system_clock time_point may produce a date string or "since epoch"
    auto tp = std::chrono::system_clock::time_point(std::chrono::seconds(0));
    std::string result = Catch::Detail::stringify(tp);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertTimePoint_SystemClock_NonZero_104) {
    auto tp = std::chrono::system_clock::time_point(std::chrono::seconds(1609459200)); // 2021-01-01 00:00:00 UTC
    std::string result = Catch::Detail::stringify(tp);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for wstring types
// ============================================================

TEST_F(StringMakerTest_104, ConvertWString_104) {
    std::wstring ws = L"wide string";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertWStringView_104) {
    std::wstring_view wsv = L"wide view";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertWCharConstPtr_104) {
    const wchar_t* ws = L"wchar ptr";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertWCharPtr_104) {
    wchar_t buf[] = L"mutable wchar";
    std::string result = Catch::StringMaker<wchar_t*>::convert(buf);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary tests for integer types
// ============================================================

TEST_F(StringMakerTest_104, ConvertInt_MaxValue_104) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    std::string expected = std::to_string(std::numeric_limits<int>::max());
    EXPECT_EQ(result, expected);
}

TEST_F(StringMakerTest_104, ConvertInt_MinValue_104) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    std::string expected = std::to_string(std::numeric_limits<int>::min());
    EXPECT_EQ(result, expected);
}

TEST_F(StringMakerTest_104, ConvertUnsignedLongLong_MaxValue_104) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(std::numeric_limits<unsigned long long>::max());
    std::string expected = std::to_string(std::numeric_limits<unsigned long long>::max());
    EXPECT_EQ(result, expected);
}

// ============================================================
// Boundary tests for floating point
// ============================================================

TEST_F(StringMakerTest_104, ConvertFloat_NaN_104) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    // Should contain "nan" in some form
    EXPECT_FALSE(result.empty());
    // Convert to lowercase for checking
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    EXPECT_NE(lower.find("nan"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertFloat_Infinity_104) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    EXPECT_NE(lower.find("inf"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDouble_NaN_104) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    EXPECT_NE(lower.find("nan"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDouble_Infinity_104) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    EXPECT_NE(lower.find("inf"), std::string::npos);
}

TEST_F(StringMakerTest_104, ConvertDouble_NegativeInfinity_104) {
    std::string result = Catch::StringMaker<double>::convert(-std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    EXPECT_NE(lower.find("inf"), std::string::npos);
    EXPECT_NE(result.find('-'), std::string::npos);
}

// ============================================================
// Test for strings with special characters
// ============================================================

TEST_F(StringMakerTest_104, ConvertString_WithNewlines_104) {
    std::string input = "line1\nline2";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertString_WithTabs_104) {
    std::string input = "col1\tcol2";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_104, ConvertString_WithQuotes_104) {
    std::string input = "he said \"hi\"";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Test for chrono duration negative values
// ============================================================

TEST_F(StringMakerTest_104, ConvertDuration_Negative_104) {
    auto dur = std::chrono::milliseconds(-500);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_NE(result.find("-"), std::string::npos);
}

// ============================================================
// Test that stringify produces consistent results
// ============================================================

TEST_F(StringMakerTest_104, ConvertInt_Consistency_104) {
    std::string r1 = Catch::StringMaker<int>::convert(42);
    std::string r2 = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(r1, r2);
}

TEST_F(StringMakerTest_104, ConvertString_Consistency_104) {
    std::string input = "consistent";
    std::string r1 = Catch::StringMaker<std::string>::convert(input);
    std::string r2 = Catch::StringMaker<std::string>::convert(input);
    EXPECT_EQ(r1, r2);
}
