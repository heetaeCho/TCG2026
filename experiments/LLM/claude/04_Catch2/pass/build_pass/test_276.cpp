#include <gtest/gtest.h>
#include <string>
#include <cstddef>
#include <chrono>

// Include Catch2 headers needed for StringMaker
#include "catch2/catch_tostring.hpp"

// Test fixture
class StringMakerTest_276 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for StringMaker<char>::convert
// ============================================================

TEST_F(StringMakerTest_276, CharConvert_RegularChar_276) {
    std::string result = Catch::StringMaker<char>::convert('A');
    // Should produce some string representation; at minimum it should not be empty
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_NullChar_276) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_NewlineChar_276) {
    std::string result = Catch::StringMaker<char>::convert('\n');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_SpaceChar_276) {
    std::string result = Catch::StringMaker<char>::convert(' ');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_MaxChar_276) {
    std::string result = Catch::StringMaker<char>::convert(static_cast<char>(127));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_MinChar_276) {
    // char might be signed, so minimum could be -128 on most platforms
    std::string result = Catch::StringMaker<char>::convert(static_cast<char>(-128));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_DigitChar_276) {
    std::string result = Catch::StringMaker<char>::convert('0');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_TabChar_276) {
    std::string result = Catch::StringMaker<char>::convert('\t');
    EXPECT_FALSE(result.empty());
}

// The implementation delegates to stringify(static_cast<signed char>(c))
// so char 'A' (65) should produce same result as signed char 65
TEST_F(StringMakerTest_276, CharConvert_ConsistentWithSignedChar_276) {
    char c = 'A';
    std::string charResult = Catch::StringMaker<char>::convert(c);
    std::string signedCharResult = Catch::StringMaker<signed char>::convert(static_cast<signed char>(c));
    EXPECT_EQ(charResult, signedCharResult);
}

TEST_F(StringMakerTest_276, CharConvert_ConsistentWithSignedChar_Zero_276) {
    char c = '\0';
    std::string charResult = Catch::StringMaker<char>::convert(c);
    std::string signedCharResult = Catch::StringMaker<signed char>::convert(static_cast<signed char>(c));
    EXPECT_EQ(charResult, signedCharResult);
}

TEST_F(StringMakerTest_276, CharConvert_ConsistentWithSignedChar_Negative_276) {
    char c = static_cast<char>(-1);
    std::string charResult = Catch::StringMaker<char>::convert(c);
    std::string signedCharResult = Catch::StringMaker<signed char>::convert(static_cast<signed char>(c));
    EXPECT_EQ(charResult, signedCharResult);
}

// ============================================================
// Tests for StringMaker<int>::convert
// ============================================================

TEST_F(StringMakerTest_276, IntConvert_Zero_276) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_276, IntConvert_Positive_276) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_276, IntConvert_Negative_276) {
    std::string result = Catch::StringMaker<int>::convert(-42);
    EXPECT_EQ(result, "-42");
}

TEST_F(StringMakerTest_276, IntConvert_MaxInt_276) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));
}

TEST_F(StringMakerTest_276, IntConvert_MinInt_276) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));
}

// ============================================================
// Tests for StringMaker<unsigned int>::convert
// ============================================================

TEST_F(StringMakerTest_276, UIntConvert_Zero_276) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_276, UIntConvert_Positive_276) {
    std::string result = Catch::StringMaker<unsigned int>::convert(100u);
    EXPECT_EQ(result, "100");
}

// ============================================================
// Tests for StringMaker<long long>::convert
// ============================================================

TEST_F(StringMakerTest_276, LongLongConvert_Large_276) {
    std::string result = Catch::StringMaker<long long>::convert(1234567890123LL);
    EXPECT_EQ(result, "1234567890123");
}

// ============================================================
// Tests for StringMaker<bool>::convert
// ============================================================

TEST_F(StringMakerTest_276, BoolConvert_True_276) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_276, BoolConvert_False_276) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ============================================================
// Tests for StringMaker<std::string>::convert
// ============================================================

TEST_F(StringMakerTest_276, StringConvert_Regular_276) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    // The result should contain "hello" in some form (possibly quoted)
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_276, StringConvert_Empty_276) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Even empty string should produce some representation (e.g., `""`)
}

// ============================================================
// Tests for StringMaker<char const*>::convert
// ============================================================

TEST_F(StringMakerTest_276, CStringConvert_Regular_276) {
    std::string result = Catch::StringMaker<char const*>::convert("test");
    EXPECT_NE(result.find("test"), std::string::npos);
}

TEST_F(StringMakerTest_276, CStringConvert_Nullptr_276) {
    std::string result = Catch::StringMaker<char const*>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<std::nullptr_t>::convert
// ============================================================

TEST_F(StringMakerTest_276, NullptrConvert_276) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    // Should contain "null" or "nullptr" in some form
    // Convert to lowercase for comparison
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    EXPECT_TRUE(lower.find("null") != std::string::npos);
}

// ============================================================
// Tests for StringMaker<float>::convert
// ============================================================

TEST_F(StringMakerTest_276, FloatConvert_Zero_276) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(StringMakerTest_276, FloatConvert_Positive_276) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(StringMakerTest_276, FloatConvert_Negative_276) {
    std::string result = Catch::StringMaker<float>::convert(-3.14f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-"), std::string::npos);
}

// ============================================================
// Tests for StringMaker<double>::convert
// ============================================================

TEST_F(StringMakerTest_276, DoubleConvert_Zero_276) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, DoubleConvert_Positive_276) {
    std::string result = Catch::StringMaker<double>::convert(2.5);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

// ============================================================
// Tests for StringMaker<signed char>::convert
// ============================================================

TEST_F(StringMakerTest_276, SignedCharConvert_Positive_276) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, SignedCharConvert_Zero_276) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(0));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, SignedCharConvert_Negative_276) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(-1));
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<unsigned char>::convert
// ============================================================

TEST_F(StringMakerTest_276, UnsignedCharConvert_Zero_276) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(0));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, UnsignedCharConvert_Max_276) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<long>::convert
// ============================================================

TEST_F(StringMakerTest_276, LongConvert_Zero_276) {
    std::string result = Catch::StringMaker<long>::convert(0L);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_276, LongConvert_Positive_276) {
    std::string result = Catch::StringMaker<long>::convert(999L);
    EXPECT_EQ(result, "999");
}

// ============================================================
// Tests for StringMaker<unsigned long>::convert
// ============================================================

TEST_F(StringMakerTest_276, ULongConvert_Zero_276) {
    std::string result = Catch::StringMaker<unsigned long>::convert(0UL);
    EXPECT_EQ(result, "0");
}

// ============================================================
// Tests for StringMaker<unsigned long long>::convert
// ============================================================

TEST_F(StringMakerTest_276, ULongLongConvert_Large_276) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(9999999999999ULL);
    EXPECT_EQ(result, "9999999999999");
}

// ============================================================
// Tests for pointer conversion
// ============================================================

TEST_F(StringMakerTest_276, PointerConvert_Nullptr_276) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, PointerConvert_NonNull_276) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<std::string_view>::convert
// ============================================================

TEST_F(StringMakerTest_276, StringViewConvert_Regular_276) {
    std::string_view sv = "hello world";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(StringMakerTest_276, StringViewConvert_Empty_276) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<std::byte>::convert
// ============================================================

TEST_F(StringMakerTest_276, ByteConvert_Zero_276) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, ByteConvert_Max_276) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Char special characters - boundary tests
// ============================================================

TEST_F(StringMakerTest_276, CharConvert_CarriageReturn_276) {
    std::string result = Catch::StringMaker<char>::convert('\r');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_Backslash_276) {
    std::string result = Catch::StringMaker<char>::convert('\\');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_SingleQuote_276) {
    std::string result = Catch::StringMaker<char>::convert('\'');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_276, CharConvert_DoubleQuote_276) {
    std::string result = Catch::StringMaker<char>::convert('"');
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Multiple chars give different results
// ============================================================

TEST_F(StringMakerTest_276, CharConvert_DifferentCharsProduceDifferentResults_276) {
    std::string resultA = Catch::StringMaker<char>::convert('A');
    std::string resultB = Catch::StringMaker<char>::convert('B');
    EXPECT_NE(resultA, resultB);
}

TEST_F(StringMakerTest_276, IntConvert_DifferentValuesProduceDifferentResults_276) {
    std::string result1 = Catch::StringMaker<int>::convert(1);
    std::string result2 = Catch::StringMaker<int>::convert(2);
    EXPECT_NE(result1, result2);
}
