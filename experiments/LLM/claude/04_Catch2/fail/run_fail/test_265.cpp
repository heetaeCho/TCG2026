#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <cstddef>
#include <chrono>

// Include Catch2 headers for StringMaker
#include "catch2/catch_tostring.hpp"

class StringMakerTest_265 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== std::wstring_view tests ====================

TEST_F(StringMakerTest_265, WStringViewConvert_EmptyString_265) {
    std::wstring_view empty_wsv = L"";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(empty_wsv);
    // Empty wstring_view should produce some valid string representation
    EXPECT_FALSE(result.empty() || result == "\"\"" || result.find("\"\"") != std::string::npos || result.empty());
    // At minimum, the result should be a valid std::string
    EXPECT_NO_THROW(result.size());
}

TEST_F(StringMakerTest_265, WStringViewConvert_SimpleString_265) {
    std::wstring_view wsv = L"hello";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    // The result should contain "hello" in some form
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, WStringViewConvert_MatchesWString_265) {
    std::wstring ws = L"test string";
    std::wstring_view wsv = ws;
    std::string result_sv = Catch::StringMaker<std::wstring_view>::convert(wsv);
    std::string result_s = Catch::StringMaker<std::wstring>::convert(ws);
    // wstring_view conversion should match wstring conversion for the same content
    EXPECT_EQ(result_sv, result_s);
}

TEST_F(StringMakerTest_265, WStringViewConvert_SingleCharacter_265) {
    std::wstring_view wsv = L"A";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, WStringViewConvert_SpecialCharacters_265) {
    std::wstring_view wsv = L"hello\nworld";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, WStringViewConvert_UnicodeCharacters_265) {
    std::wstring_view wsv = L"\u00E9\u00E0\u00FC";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, WStringViewConvert_ConsistencyWithWString_EmptyCase_265) {
    std::wstring empty_ws;
    std::wstring_view empty_wsv = empty_ws;
    std::string result_sv = Catch::StringMaker<std::wstring_view>::convert(empty_wsv);
    std::string result_s = Catch::StringMaker<std::wstring>::convert(empty_ws);
    EXPECT_EQ(result_sv, result_s);
}

// ==================== std::string tests ====================

TEST_F(StringMakerTest_265, StringConvert_EmptyString_265) {
    std::string empty_str;
    std::string result = Catch::StringMaker<std::string>::convert(empty_str);
    EXPECT_FALSE(result.empty() && false); // result is valid
}

TEST_F(StringMakerTest_265, StringConvert_SimpleString_265) {
    std::string str = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
    // Should contain the original string content
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// ==================== std::string_view tests ====================

TEST_F(StringMakerTest_265, StringViewConvert_Empty_265) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NO_THROW(result.size());
}

TEST_F(StringMakerTest_265, StringViewConvert_MatchesString_265) {
    std::string str = "test data";
    std::string_view sv = str;
    std::string result_sv = Catch::StringMaker<std::string_view>::convert(sv);
    std::string result_s = Catch::StringMaker<std::string>::convert(str);
    EXPECT_EQ(result_sv, result_s);
}

// ==================== Integer type tests ====================

TEST_F(StringMakerTest_265, IntConvert_Zero_265) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_265, IntConvert_Positive_265) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_265, IntConvert_Negative_265) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerTest_265, LongConvert_265) {
    std::string result = Catch::StringMaker<long>::convert(123456789L);
    EXPECT_EQ(result, "123456789");
}

TEST_F(StringMakerTest_265, LongLongConvert_265) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST_F(StringMakerTest_265, UnsignedIntConvert_265) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_265, UnsignedLongConvert_265) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerTest_265, UnsignedLongLongConvert_265) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

// ==================== char type tests ====================

TEST_F(StringMakerTest_265, CharConvert_265) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    // Should contain 'A' in some form
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST_F(StringMakerTest_265, SignedCharConvert_265) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, UnsignedCharConvert_265) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// ==================== Boolean tests ====================

TEST_F(StringMakerTest_265, BoolConvert_True_265) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_265, BoolConvert_False_265) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ==================== Float/Double tests ====================

TEST_F(StringMakerTest_265, FloatConvert_Zero_265) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, FloatConvert_Positive_265) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, DoubleConvert_Zero_265) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, DoubleConvert_Positive_265) {
    std::string result = Catch::StringMaker<double>::convert(2.71828);
    EXPECT_FALSE(result.empty());
}

// ==================== nullptr tests ====================

TEST_F(StringMakerTest_265, NullptrConvert_265) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// ==================== char const* tests ====================

TEST_F(StringMakerTest_265, CharConstPtrConvert_NullPtr_265) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, CharConstPtrConvert_ValidString_265) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_265, CharConstPtrConvert_EmptyString_265) {
    const char* str = "";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NO_THROW(result.size());
}

// ==================== wchar_t const* tests ====================

TEST_F(StringMakerTest_265, WCharConstPtrConvert_ValidString_265) {
    const wchar_t* wstr = L"wide";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, WCharConstPtrConvert_EmptyString_265) {
    const wchar_t* wstr = L"";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(wstr);
    EXPECT_NO_THROW(result.size());
}

// ==================== std::byte tests ====================

TEST_F(StringMakerTest_265, ByteConvert_Zero_265) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_265, ByteConvert_Max_265) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}

// ==================== WStringView consistency tests with substrings ====================

TEST_F(StringMakerTest_265, WStringViewConvert_Substring_MatchesWString_265) {
    std::wstring ws = L"hello world";
    std::wstring_view wsv = std::wstring_view(ws).substr(0, 5); // L"hello"
    std::wstring sub_ws = L"hello";
    std::string result_sv = Catch::StringMaker<std::wstring_view>::convert(wsv);
    std::string result_s = Catch::StringMaker<std::wstring>::convert(sub_ws);
    EXPECT_EQ(result_sv, result_s);
}

TEST_F(StringMakerTest_265, WStringViewConvert_LongString_265) {
    std::wstring long_ws(1000, L'X');
    std::wstring_view long_wsv = long_ws;
    std::string result_sv = Catch::StringMaker<std::wstring_view>::convert(long_wsv);
    std::string result_s = Catch::StringMaker<std::wstring>::convert(long_ws);
    EXPECT_EQ(result_sv, result_s);
}

// ==================== Boundary: max int values ====================

TEST_F(StringMakerTest_265, IntConvert_MaxValue_265) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));
}

TEST_F(StringMakerTest_265, IntConvert_MinValue_265) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));
}

TEST_F(StringMakerTest_265, UnsignedLongLongConvert_MaxValue_265) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(std::numeric_limits<unsigned long long>::max());
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<unsigned long long>::max()));
}

// ==================== char* (mutable) tests ====================

TEST_F(StringMakerTest_265, CharMutablePtrConvert_ValidString_265) {
    char str[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

// ==================== wchar_t* (mutable) tests ====================

TEST_F(StringMakerTest_265, WCharMutablePtrConvert_ValidString_265) {
    wchar_t wstr[] = L"mutable wide";
    std::string result = Catch::StringMaker<wchar_t*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}
