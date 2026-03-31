#include <gtest/gtest.h>
#include <string>
#include <cstddef>
#include "catch2/catch_tostring.hpp"

// Tests for StringMaker<wchar_t const*>::convert
class StringMakerWcharConstPtrTest_266 : public ::testing::Test {};

TEST_F(StringMakerWcharConstPtrTest_266, NullPointerReturnsNullString_266) {
    wchar_t const* str = nullptr;
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

TEST_F(StringMakerWcharConstPtrTest_266, NonNullPointerReturnsStringifiedWstring_266) {
    wchar_t const* str = L"hello";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    // The result should contain the stringified version of the wstring "hello"
    // Based on Catch2's stringify for wstring, it typically wraps in quotes
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
}

TEST_F(StringMakerWcharConstPtrTest_266, EmptyWcharStringReturnsNonNull_266) {
    wchar_t const* str = L"";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerWcharConstPtrTest_266, SingleCharacterWstring_266) {
    wchar_t const* str = L"A";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerWcharConstPtrTest_266, WideStringWithSpaces_266) {
    wchar_t const* str = L"hello world";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerWcharConstPtrTest_266, WideStringWithSpecialChars_266) {
    wchar_t const* str = L"test\n\t";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerWcharConstPtrTest_266, ConsistencyWithWstringStringMaker_266) {
    wchar_t const* str = L"test";
    std::string fromConstPtr = Catch::StringMaker<wchar_t const*>::convert(str);
    std::wstring wstr{str};
    std::string fromWstring = Catch::StringMaker<std::wstring>::convert(wstr);
    EXPECT_EQ(fromConstPtr, fromWstring);
}

TEST_F(StringMakerWcharConstPtrTest_266, LongWideString_266) {
    std::wstring longStr(1000, L'x');
    std::string result = Catch::StringMaker<wchar_t const*>::convert(longStr.c_str());
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

// Additional tests for other StringMaker specializations to ensure broad coverage

class StringMakerIntTest_266 : public ::testing::Test {};

TEST_F(StringMakerIntTest_266, ConvertsZero_266) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerIntTest_266, ConvertsPositiveInt_266) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerIntTest_266, ConvertsNegativeInt_266) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

class StringMakerBoolTest_266 : public ::testing::Test {};

TEST_F(StringMakerBoolTest_266, ConvertsTrue_266) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerBoolTest_266, ConvertsFalse_266) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

class StringMakerCharConstPtrTest_266 : public ::testing::Test {};

TEST_F(StringMakerCharConstPtrTest_266, NullCharPtrReturnsNullString_266) {
    char const* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

TEST_F(StringMakerCharConstPtrTest_266, NonNullCharPtr_266) {
    char const* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

class StringMakerNullptrTest_266 : public ::testing::Test {};

TEST_F(StringMakerNullptrTest_266, ConvertsNullptr_266) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

class StringMakerCharTest_266 : public ::testing::Test {};

TEST_F(StringMakerCharTest_266, ConvertsChar_266) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
}

class StringMakerDoubleTest_266 : public ::testing::Test {};

TEST_F(StringMakerDoubleTest_266, ConvertsDouble_266) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerDoubleTest_266, ConvertsZeroDouble_266) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

class StringMakerFloatTest_266 : public ::testing::Test {};

TEST_F(StringMakerFloatTest_266, ConvertsFloat_266) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_FALSE(result.empty());
}

class StringMakerStringTest_266 : public ::testing::Test {};

TEST_F(StringMakerStringTest_266, ConvertsStdString_266) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerStringTest_266, ConvertsEmptyStdString_266) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty());
}

class StringMakerUnsignedIntTest_266 : public ::testing::Test {};

TEST_F(StringMakerUnsignedIntTest_266, ConvertsUnsignedInt_266) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

class StringMakerLongLongTest_266 : public ::testing::Test {};

TEST_F(StringMakerLongLongTest_266, ConvertsLongLong_266) {
    std::string result = Catch::StringMaker<long long>::convert(123456789LL);
    EXPECT_EQ(result, "123456789");
}

class StringMakerWcharMutablePtrTest_266 : public ::testing::Test {};

TEST_F(StringMakerWcharMutablePtrTest_266, NullMutableWcharPtrReturnsNullString_266) {
    wchar_t* str = nullptr;
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

TEST_F(StringMakerWcharMutablePtrTest_266, NonNullMutableWcharPtr_266) {
    wchar_t str[] = L"test";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}
