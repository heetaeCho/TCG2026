#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_tostring.hpp"



using namespace Catch;

using ::testing::Eq;



class StringMakerTest_269 : public ::testing::Test {};



TEST_F(StringMakerTest_269, ConvertIntToPositiveString_269) {

    EXPECT_EQ(StringMaker<int>::convert(42), "42");

}



TEST_F(StringMakerTest_269, ConvertIntToNegativeString_269) {

    EXPECT_EQ(StringMaker<int>::convert(-42), "-42");

}



TEST_F(StringMakerTest_269, ConvertIntToZeroString_269) {

    EXPECT_EQ(StringMaker<int>::convert(0), "0");

}



TEST_F(StringMakerTest_269, ConvertLongToPositiveString_269) {

    EXPECT_EQ(StringMaker<long>::convert(1234567890L), "1234567890");

}



TEST_F(StringMakerTest_269, ConvertLongToNegativeString_269) {

    EXPECT_EQ(StringMaker<long>::convert(-1234567890L), "-1234567890");

}



TEST_F(StringMakerTest_269, ConvertLongToZeroString_269) {

    EXPECT_EQ(StringMaker<long>::convert(0L), "0");

}



TEST_F(StringMakerTest_269, ConvertLongLongToPositiveString_269) {

    EXPECT_EQ(StringMaker<long long>::convert(123456789012345LL), "123456789012345");

}



TEST_F(StringMakerTest_269, ConvertLongLongToNegativeString_269) {

    EXPECT_EQ(StringMaker<long long>::convert(-123456789012345LL), "-123456789012345");

}



TEST_F(StringMakerTest_269, ConvertLongLongToZeroString_269) {

    EXPECT_EQ(StringMaker<long long>::convert(0LL), "0");

}



TEST_F(StringMakerTest_269, ConvertUnsignedIntToString_269) {

    EXPECT_EQ(StringMaker<unsigned int>::convert(42U), "42");

}



TEST_F(StringMakerTest_269, ConvertUnsignedLongToString_269) {

    EXPECT_EQ(StringMaker<unsigned long>::convert(1234567890UL), "1234567890");

}



TEST_F(StringMakerTest_269, ConvertUnsignedLongLongToString_269) {

    EXPECT_EQ(StringMaker<unsigned long long>::convert(123456789012345ULL), "123456789012345");

}



TEST_F(StringMakerTest_269, ConvertSignedCharToString_269) {

    EXPECT_EQ(StringMaker<signed char>::convert('A'), "65");

}



TEST_F(StringMakerTest_269, ConvertCharToString_269) {

    EXPECT_EQ(StringMaker<char>::convert('A'), "65");

}



TEST_F(StringMakerTest_269, ConvertUnsignedCharToString_269) {

    EXPECT_EQ(StringMaker<unsigned char>::convert('A'), "65");

}



TEST_F(StringMakerTest_269, ConvertFloatToString_269) {

    EXPECT_THAT(StringMaker<float>::convert(3.14f), Eq("3.14"));

}



TEST_F(StringMakerTest_269, ConvertDoubleToString_269) {

    EXPECT_THAT(StringMaker<double>::convert(3.14159), Eq("3.14159"));

}



TEST_F(StringMakerTest_269, ConvertApproxToString_269) {

    EXPECT_EQ(StringMaker<Catch::Approx>::convert(Approx(3.14)), "WithinAbs(3.14, 0.000001)");

}



TEST_F(StringMakerTest_269, ConvertCStringToString_269) {

    EXPECT_EQ(StringMaker<char const*>::convert("Hello"), "Hello");

}



TEST_F(StringMakerTest_269, ConvertStdStringToString_269) {

    EXPECT_EQ(StringMaker<std::string>::convert("World"), "World");

}



TEST_F(StringMakerTest_269, ConvertStringViewToString_269) {

    EXPECT_EQ(StringMaker<std::string_view>::convert("Hello World"), "Hello World");

}



TEST_F(StringMakerTest_269, ConvertWStringToString_269) {

    EXPECT_EQ(StringMaker<std::wstring>::convert(L"Unicode"), "Unicode");

}



TEST_F(StringMakerTest_269, ConvertWStringViewToString_269) {

    EXPECT_EQ(StringMaker<std::wstring_view>::convert(L"Wide String"), "Wide String");

}



TEST_F(StringMakerTest_269, ConvertWCharPtrToString_269) {

    EXPECT_EQ(StringMaker<wchar_t const*>::convert(L"Hello"), "Hello");

}
