#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <cstring>

// Include the Catch2 headers needed
#include "catch2/catch_tostring.hpp"

// Test fixture
class StringMakerTest_261 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for StringMaker<std::string_view>::convert
// ============================================================

TEST_F(StringMakerTest_261, StringViewConvert_NormalString_261) {
    std::string_view sv = "hello world";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    // The result should contain the original string content (possibly quoted)
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(StringMakerTest_261, StringViewConvert_EmptyString_261) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    // Should produce a valid string representation for empty string
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, StringViewConvert_SingleCharacter_261) {
    std::string_view sv = "A";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerTest_261, StringViewConvert_SpecialCharacters_261) {
    std::string_view sv = "hello\nworld";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    // Should produce some representation that includes the content
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, StringViewConvert_StringWithNullInMiddle_261) {
    // string_view can contain null bytes
    std::string data = "hello";
    data += '\0';
    data += "world";
    std::string_view sv(data.data(), data.size());
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, StringViewConvert_LongString_261) {
    std::string longStr(1000, 'x');
    std::string_view sv = longStr;
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, StringViewConvert_WhitespaceOnly_261) {
    std::string_view sv = "   \t\n  ";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<std::string>::convert
// ============================================================

TEST_F(StringMakerTest_261, StringConvert_NormalString_261) {
    std::string s = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(s);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(StringMakerTest_261, StringConvert_EmptyString_261) {
    std::string s = "";
    std::string result = Catch::StringMaker<std::string>::convert(s);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<int>::convert
// ============================================================

TEST_F(StringMakerTest_261, IntConvert_Zero_261) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_261, IntConvert_Positive_261) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_261, IntConvert_Negative_261) {
    std::string result = Catch::StringMaker<int>::convert(-42);
    EXPECT_EQ(result, "-42");
}

TEST_F(StringMakerTest_261, IntConvert_MaxInt_261) {
    int maxVal = std::numeric_limits<int>::max();
    std::string result = Catch::StringMaker<int>::convert(maxVal);
    EXPECT_EQ(result, std::to_string(maxVal));
}

TEST_F(StringMakerTest_261, IntConvert_MinInt_261) {
    int minVal = std::numeric_limits<int>::min();
    std::string result = Catch::StringMaker<int>::convert(minVal);
    EXPECT_EQ(result, std::to_string(minVal));
}

// ============================================================
// Tests for StringMaker<bool>::convert
// ============================================================

TEST_F(StringMakerTest_261, BoolConvert_True_261) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_261, BoolConvert_False_261) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ============================================================
// Tests for StringMaker<char>::convert
// ============================================================

TEST_F(StringMakerTest_261, CharConvert_NormalChar_261) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerTest_261, CharConvert_NullChar_261) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<float>::convert
// ============================================================

TEST_F(StringMakerTest_261, FloatConvert_Zero_261) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(StringMakerTest_261, FloatConvert_Positive_261) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, FloatConvert_Negative_261) {
    std::string result = Catch::StringMaker<float>::convert(-2.5f);
    EXPECT_NE(result.find("-"), std::string::npos);
}

// ============================================================
// Tests for StringMaker<double>::convert
// ============================================================

TEST_F(StringMakerTest_261, DoubleConvert_Zero_261) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, DoubleConvert_Positive_261) {
    std::string result = Catch::StringMaker<double>::convert(3.14159265358979);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<long long>::convert
// ============================================================

TEST_F(StringMakerTest_261, LongLongConvert_Large_261) {
    long long val = 9223372036854775807LL;
    std::string result = Catch::StringMaker<long long>::convert(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ============================================================
// Tests for StringMaker<unsigned int>::convert
// ============================================================

TEST_F(StringMakerTest_261, UnsignedIntConvert_Zero_261) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_261, UnsignedIntConvert_Max_261) {
    unsigned int maxVal = std::numeric_limits<unsigned int>::max();
    std::string result = Catch::StringMaker<unsigned int>::convert(maxVal);
    EXPECT_EQ(result, std::to_string(maxVal));
}

// ============================================================
// Tests for StringMaker<nullptr_t>::convert
// ============================================================

TEST_F(StringMakerTest_261, NullptrConvert_261) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<char const*>::convert
// ============================================================

TEST_F(StringMakerTest_261, CharPtrConvert_Normal_261) {
    const char* str = "test string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerTest_261, CharPtrConvert_Null_261) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, CharPtrConvert_EmptyString_261) {
    const char* str = "";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<unsigned char>::convert
// ============================================================

TEST_F(StringMakerTest_261, UnsignedCharConvert_Zero_261) {
    std::string result = Catch::StringMaker<unsigned char>::convert(0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, UnsignedCharConvert_Max_261) {
    std::string result = Catch::StringMaker<unsigned char>::convert(255);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<signed char>::convert
// ============================================================

TEST_F(StringMakerTest_261, SignedCharConvert_Positive_261) {
    std::string result = Catch::StringMaker<signed char>::convert(65);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_261, SignedCharConvert_Negative_261) {
    std::string result = Catch::StringMaker<signed char>::convert(-1);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Consistency tests: string_view and string produce same output
// ============================================================

TEST_F(StringMakerTest_261, StringViewAndStringConsistency_261) {
    std::string s = "consistency test";
    std::string_view sv = s;
    std::string resultFromString = Catch::StringMaker<std::string>::convert(s);
    std::string resultFromStringView = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_EQ(resultFromString, resultFromStringView);
}

TEST_F(StringMakerTest_261, StringViewAndStringConsistencyEmpty_261) {
    std::string s = "";
    std::string_view sv = s;
    std::string resultFromString = Catch::StringMaker<std::string>::convert(s);
    std::string resultFromStringView = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_EQ(resultFromString, resultFromStringView);
}

// ============================================================
// Tests for StringMaker<long>::convert
// ============================================================

TEST_F(StringMakerTest_261, LongConvert_Positive_261) {
    std::string result = Catch::StringMaker<long>::convert(123456789L);
    EXPECT_EQ(result, std::to_string(123456789L));
}

TEST_F(StringMakerTest_261, LongConvert_Negative_261) {
    std::string result = Catch::StringMaker<long>::convert(-123456789L);
    EXPECT_EQ(result, std::to_string(-123456789L));
}

// ============================================================
// Tests for StringMaker<unsigned long>::convert
// ============================================================

TEST_F(StringMakerTest_261, UnsignedLongConvert_261) {
    unsigned long val = 999999999UL;
    std::string result = Catch::StringMaker<unsigned long>::convert(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ============================================================
// Tests for StringMaker<unsigned long long>::convert
// ============================================================

TEST_F(StringMakerTest_261, UnsignedLongLongConvert_261) {
    unsigned long long val = 18446744073709551615ULL;
    std::string result = Catch::StringMaker<unsigned long long>::convert(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ============================================================
// Test StringMaker<std::string_view> with unicode-like content
// ============================================================

TEST_F(StringMakerTest_261, StringViewConvert_UnicodeContent_261) {
    std::string_view sv = u8"café";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Test StringMaker<std::string_view> with only spaces
// ============================================================

TEST_F(StringMakerTest_261, StringViewConvert_OnlySpaces_261) {
    std::string_view sv = "     ";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Test StringMaker<std::string_view> partial view of a larger string
// ============================================================

TEST_F(StringMakerTest_261, StringViewConvert_PartialView_261) {
    std::string fullString = "Hello, World!";
    std::string_view sv = std::string_view(fullString).substr(0, 5);
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("Hello"), std::string::npos);
    // Should NOT contain the rest
    EXPECT_EQ(result.find("World"), std::string::npos);
}
