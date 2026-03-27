#include <gtest/gtest.h>

#include <Catch2/src/catch2/catch_tostring.hpp>



using namespace Catch;



TEST(StringMaker_wstring_Convert_264, NormalOperation_264) {

    std::wstring wstr = L"Hello";

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "Hello");

}



TEST(StringMaker_wstring_Convert_264, BoundaryCondition_EmptyString_264) {

    std::wstring wstr = L"";

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "");

}



TEST(StringMaker_wstring_Convert_264, BoundaryCondition_SingleCharacter_264) {

    std::wstring wstr = L"A";

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "A");

}



TEST(StringMaker_wstring_Convert_264, BoundaryCondition_MaxCodePoint_264) {

    std::wstring wstr = L"\U0010FFFF"; // Max Unicode code point

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "?");

}



TEST(StringMaker_wstring_Convert_264, Exceptional_Case_NonBMPCharacters_264) {

    std::wstring wstr = L"\U0001F600"; // Grinning Face Emoji

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "?");

}



TEST(StringMaker_wstring_Convert_264, MixedCharacters_264) {

    std::wstring wstr = L"Hello \U0001F600 World";

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "Hello ? World");

}



TEST(StringMaker_wstring_Convert_264, ASCIICharactersOnly_264) {

    std::wstring wstr = L"ASCII only";

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, "ASCII only");

}
