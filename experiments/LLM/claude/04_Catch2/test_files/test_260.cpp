#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <cstring>
#include <chrono>

// Include Catch2 headers needed for StringMaker
#include "catch2/catch_tostring.hpp"

// Test fixture
class StringMakerTest_260 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== std::string tests ====================

TEST_F(StringMakerTest_260, ConvertEmptyString_260) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // Empty string should produce some representation (likely `""`)
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\"\""), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertSimpleString_260) {
    std::string input = "hello";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // Should contain the string content
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertStringWithSpecialChars_260) {
    std::string input = "hello\nworld";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // Should contain some representation of the string
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertStringWithQuotes_260) {
    std::string input = "he said \"hi\"";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertStringWithTab_260) {
    std::string input = "hello\tworld";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertLongString_260) {
    std::string input(1000, 'a');
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

// ==================== int tests ====================

TEST_F(StringMakerTest_260, ConvertIntZero_260) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_260, ConvertIntPositive_260) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_260, ConvertIntNegative_260) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerTest_260, ConvertIntMax_260) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertIntMin_260) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

// ==================== long tests ====================

TEST_F(StringMakerTest_260, ConvertLongZero_260) {
    std::string result = Catch::StringMaker<long>::convert(0L);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_260, ConvertLongPositive_260) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

// ==================== long long tests ====================

TEST_F(StringMakerTest_260, ConvertLongLongPositive_260) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST_F(StringMakerTest_260, ConvertLongLongNegative_260) {
    std::string result = Catch::StringMaker<long long>::convert(-9876543210LL);
    EXPECT_EQ(result, "-9876543210");
}

// ==================== unsigned int tests ====================

TEST_F(StringMakerTest_260, ConvertUnsignedIntZero_260) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_260, ConvertUnsignedIntPositive_260) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

// ==================== unsigned long tests ====================

TEST_F(StringMakerTest_260, ConvertUnsignedLongPositive_260) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

// ==================== unsigned long long tests ====================

TEST_F(StringMakerTest_260, ConvertUnsignedLongLongPositive_260) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(100ULL);
    EXPECT_EQ(result, "100");
}

// ==================== bool tests ====================

TEST_F(StringMakerTest_260, ConvertBoolTrue_260) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_260, ConvertBoolFalse_260) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ==================== char tests ====================

TEST_F(StringMakerTest_260, ConvertCharRegular_260) {
    std::string result = Catch::StringMaker<char>::convert('a');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('a'), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertCharNull_260) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertCharNewline_260) {
    std::string result = Catch::StringMaker<char>::convert('\n');
    EXPECT_FALSE(result.empty());
}

// ==================== signed char tests ====================

TEST_F(StringMakerTest_260, ConvertSignedChar_260) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

// ==================== unsigned char tests ====================

TEST_F(StringMakerTest_260, ConvertUnsignedChar_260) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// ==================== float tests ====================

TEST_F(StringMakerTest_260, ConvertFloatZero_260) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('0'), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertFloatPositive_260) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertFloatNegative_260) {
    std::string result = Catch::StringMaker<float>::convert(-1.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

// ==================== double tests ====================

TEST_F(StringMakerTest_260, ConvertDoubleZero_260) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertDoublePositive_260) {
    std::string result = Catch::StringMaker<double>::convert(3.14159265358979);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertDoubleNegative_260) {
    std::string result = Catch::StringMaker<double>::convert(-2.718);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

// ==================== nullptr tests ====================

TEST_F(StringMakerTest_260, ConvertNullptr_260) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    // Should be "nullptr" or similar
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// ==================== char const* tests ====================

TEST_F(StringMakerTest_260, ConvertCharConstPtrNull_260) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertCharConstPtrEmpty_260) {
    const char* str = "";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertCharConstPtrNormal_260) {
    const char* str = "test";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("test"), std::string::npos);
}

// ==================== char* tests ====================

TEST_F(StringMakerTest_260, ConvertCharPtrNormal_260) {
    char str[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

// ==================== string_view tests ====================

TEST_F(StringMakerTest_260, ConvertStringViewEmpty_260) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertStringViewNormal_260) {
    std::string_view sv = "hello view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("hello view"), std::string::npos);
}

// ==================== pointer tests ====================

TEST_F(StringMakerTest_260, ConvertIntPointerNull_260) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertIntPointerNonNull_260) {
    int x = 5;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ==================== std::byte tests ====================

TEST_F(StringMakerTest_260, ConvertByteZero_260) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertByteMax_260) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}

// ==================== wstring tests ====================

TEST_F(StringMakerTest_260, ConvertWstringEmpty_260) {
    std::wstring ws = L"";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertWstringNormal_260) {
    std::wstring ws = L"hello wide";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

// ==================== wstring_view tests ====================

TEST_F(StringMakerTest_260, ConvertWstringViewEmpty_260) {
    std::wstring_view wsv = L"";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertWstringViewNormal_260) {
    std::wstring_view wsv = L"wide view";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

// ==================== wchar_t const* tests ====================

TEST_F(StringMakerTest_260, ConvertWcharConstPtrNull_260) {
    const wchar_t* str = nullptr;
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertWcharConstPtrNormal_260) {
    const wchar_t* str = L"wide cstr";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ==================== wchar_t* tests ====================

TEST_F(StringMakerTest_260, ConvertWcharPtrNormal_260) {
    wchar_t str[] = L"mutable wide";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ==================== chrono duration tests ====================

TEST_F(StringMakerTest_260, ConvertChronoDurationNanoseconds_260) {
    auto dur = std::chrono::nanoseconds(500);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertChronoDurationMilliseconds_260) {
    auto dur = std::chrono::milliseconds(100);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertChronoDurationSeconds_260) {
    auto dur = std::chrono::seconds(5);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "s" for seconds
    EXPECT_NE(result.find('s'), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertChronoDurationMinutes_260) {
    auto dur = std::chrono::minutes(3);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "m" for minutes
    EXPECT_NE(result.find('m'), std::string::npos);
}

TEST_F(StringMakerTest_260, ConvertChronoDurationHours_260) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "h" for hours
    EXPECT_NE(result.find('h'), std::string::npos);
}

// ==================== Consistency tests ====================

TEST_F(StringMakerTest_260, ConvertSameStringProducesSameResult_260) {
    std::string input = "consistency";
    std::string result1 = Catch::StringMaker<std::string>::convert(input);
    std::string result2 = Catch::StringMaker<std::string>::convert(input);
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerTest_260, ConvertDifferentStringsProduceDifferentResults_260) {
    std::string input1 = "abc";
    std::string input2 = "xyz";
    std::string result1 = Catch::StringMaker<std::string>::convert(input1);
    std::string result2 = Catch::StringMaker<std::string>::convert(input2);
    EXPECT_NE(result1, result2);
}

TEST_F(StringMakerTest_260, ConvertSameIntProducesSameResult_260) {
    std::string result1 = Catch::StringMaker<int>::convert(42);
    std::string result2 = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result1, result2);
}

// ==================== String with embedded null ====================

TEST_F(StringMakerTest_260, ConvertStringWithEmbeddedNull_260) {
    std::string input("hel\0lo", 6);
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

// ==================== String with unicode-like content ====================

TEST_F(StringMakerTest_260, ConvertStringWithHighBytes_260) {
    std::string input = "\xc3\xa9"; // UTF-8 for 'é'
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}

// ==================== Edge case for numbers ====================

TEST_F(StringMakerTest_260, ConvertUnsignedLongLongMax_260) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(
        std::numeric_limits<unsigned long long>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertLongLongMin_260) {
    std::string result = Catch::StringMaker<long long>::convert(
        std::numeric_limits<long long>::min());
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('-'), std::string::npos);
}

// ==================== Float special values ====================

TEST_F(StringMakerTest_260, ConvertFloatNaN_260) {
    std::string result = Catch::StringMaker<float>::convert(
        std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertFloatInfinity_260) {
    std::string result = Catch::StringMaker<float>::convert(
        std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertDoubleNaN_260) {
    std::string result = Catch::StringMaker<double>::convert(
        std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertDoubleInfinity_260) {
    std::string result = Catch::StringMaker<double>::convert(
        std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_260, ConvertDoubleNegativeInfinity_260) {
    std::string result = Catch::StringMaker<double>::convert(
        -std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

// ==================== Duration zero ====================

TEST_F(StringMakerTest_260, ConvertChronoDurationZeroSeconds_260) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('0'), std::string::npos);
}

// ==================== Single character string ====================

TEST_F(StringMakerTest_260, ConvertSingleCharString_260) {
    std::string input = "x";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("x"), std::string::npos);
}
