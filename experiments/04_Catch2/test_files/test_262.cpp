#include <gtest/gtest.h>

#include <Catch2/src/catch2/catch_tostring.hpp>



namespace Catch {

    std::string StringMaker<char const*>::convert(char const* str);

}



TEST(CatchStringMakerTest_262, ConvertNullPointer_ReturnsNullString_262) {

    char const* nullStr = nullptr;

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(nullStr), "{null string}");

}



TEST(CatchStringMakerTest_262, ConvertEmptyCString_ReturnsEmptyString_262) {

    char const* emptyStr = "";

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(emptyStr), "");

}



TEST(CatchStringMakerTest_262, ConvertNonEmptyCString_ReturnsSameString_262) {

    char const* testStr = "Hello, World!";

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(testStr), "Hello, World!");

}



TEST(CatchStringMakerTest_262, ConvertLongCString_ReturnsFullString_262) {

    char const* longStr = "This is a longer string to test the conversion function.";

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(longStr), "This is a longer string to test the conversion function.");

}
