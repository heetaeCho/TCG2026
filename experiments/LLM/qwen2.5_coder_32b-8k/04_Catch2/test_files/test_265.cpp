#include <gtest/gtest.h>

#include <Catch2/src/catch_tostring.hpp>



using namespace Catch;



TEST(StringMakerWstringViewTest_265, ConvertEmptyStringView_ReturnsEmptyString_265) {

    std::wstring_view emptyStr;

    EXPECT_EQ(StringMaker<std::wstring_view>::convert(emptyStr), "");

}



TEST(StringMakerWstringViewTest_265, ConvertNonEmptyStringView_ReturnsEquivalentString_265) {

    std::wstring_view str(L"Hello, World!");

    EXPECT_EQ(StringMaker<std::wstring_view>::convert(str), "Hello, World!");

}



TEST(StringMakerWstringViewTest_265, ConvertSingleCharStringView_ReturnsSingleCharString_265) {

    std::wstring_view singleCharStr(L"A");

    EXPECT_EQ(StringMaker<std::wstring_view>::convert(singleCharStr), "A");

}



TEST(StringMakerWstringViewTest_265, ConvertUnicodeStringView_ReturnsEquivalentString_265) {

    std::wstring_view unicodeStr(L"こんにちは");

    EXPECT_EQ(StringMaker<std::wstring_view>::convert(unicodeStr), "こんにちは");

}
