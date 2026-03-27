#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



TEST(StringMakerWCharPtrTests_267, ConvertNullString_ReturnsNullString_267) {

    wchar_t* nullStr = nullptr;

    std::string result = Catch::StringMaker<wchar_t*>::convert(nullStr);

    EXPECT_EQ(result, "{null string}");

}



TEST(StringMakerWCharPtrTests_267, ConvertEmptyString_ReturnsEmptyString_267) {

    wchar_t emptyStr[] = L"";

    std::string result = Catch::StringMaker<wchar_t*>::convert(emptyStr);

    EXPECT_EQ(result, "");

}



TEST(StringMakerWCharPtrTests_267, ConvertNonEmptyString_ReturnsConvertedString_267) {

    wchar_t testStr[] = L"Hello, World!";

    std::string expected = "Hello, World!";

    std::string result = Catch::StringMaker<wchar_t*>::convert(testStr);

    EXPECT_EQ(result, expected);

}



TEST(StringMakerWCharPtrTests_267, ConvertLongString_ReturnsConvertedLongString_267) {

    wchar_t longStr[] = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

    std::string expected = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

    std::string result = Catch::StringMaker<wchar_t*>::convert(longStr);

    EXPECT_EQ(result, expected);

}
