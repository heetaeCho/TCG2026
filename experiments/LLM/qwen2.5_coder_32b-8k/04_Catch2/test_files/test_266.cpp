#include <gtest/gtest.h>

#include <catch2/catch_tostring.hpp>



TEST(StringMaker_wchar_t_const_star_Test_266, ConvertNullString_ReturnsNullString_266) {

    EXPECT_EQ(Catch::StringMaker<wchar_t const*>::convert(nullptr), "{null string}");

}



TEST(StringMaker_wchar_t_const_star_Test_266, ConvertEmptyString_ReturnsEmptyString_266) {

    wchar_t const* emptyStr = L"";

    EXPECT_EQ(Catch::StringMaker<wchar_t const*>::convert(emptyStr), "");

}



TEST(StringMaker_wchar_t_const_star_Test_266, ConvertNonEmptyString_ReturnsCorrectString_266) {

    wchar_t const* testStr = L"Hello, World!";

    EXPECT_EQ(Catch::StringMaker<wchar_t const*>::convert(testStr), "Hello, World!");

}



TEST(StringMaker_wchar_t_const_star_Test_266, ConvertLongString_ReturnsCorrectString_266) {

    wchar_t const* longStr = L"A quick brown fox jumps over the lazy dog";

    EXPECT_EQ(Catch::StringMaker<wchar_t const*>::convert(longStr), "A quick brown fox jumps over the lazy dog");

}
