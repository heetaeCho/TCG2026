#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_tostring.hpp"



using namespace Catch;



TEST(StringMakerTests_261, ConvertStringView_NormalOperation_261) {

    std::string_view testString = "Hello, World!";

    EXPECT_EQ(StringMaker<std::string_view>::convert(testString), "Hello, World!");

}



TEST(StringMakerTests_261, ConvertStringView_EmptyString_261) {

    std::string_view testString = "";

    EXPECT_EQ(StringMaker<std::string_view>::convert(testString), "");

}



TEST(StringMakerTests_261, ConvertCString_NormalOperation_261) {

    const char* testString = "Hello, World!";

    EXPECT_EQ(StringMaker<char const*>::convert(testString), "Hello, World!");

}



TEST(StringMakerTests_261, ConvertCString_EmptyString_261) {

    const char* testString = "";

    EXPECT_EQ(StringMaker<char const*>::convert(testString), "");

}



TEST(StringMakerTests_261, ConvertBool_True_261) {

    EXPECT_EQ(StringMaker<bool>::convert(true), "true");

}



TEST(StringMakerTests_261, ConvertBool_False_261) {

    EXPECT_EQ(StringMaker<bool>::convert(false), "false");

}



TEST(StringMakerTests_261, ConvertNullptr_261) {

    EXPECT_EQ(StringMaker<std::nullptr_t>::convert(nullptr), "nullptr");

}



TEST(StringMakerTests_261, ConvertInt_PositiveNumber_261) {

    int testValue = 42;

    EXPECT_EQ(StringMaker<int>::convert(testValue), "42");

}



TEST(StringMakerTests_261, ConvertInt_Zero_261) {

    int testValue = 0;

    EXPECT_EQ(StringMaker<int>::convert(testValue), "0");

}



TEST(StringMakerTests_261, ConvertInt_NegativeNumber_261) {

    int testValue = -42;

    EXPECT_EQ(StringMaker<int>::convert(testValue), "-42");

}



TEST(StringMakerTests_261, ConvertUnsignedInt_PositiveNumber_261) {

    unsigned int testValue = 42u;

    EXPECT_EQ(StringMaker<unsigned int>::convert(testValue), "42");

}



TEST(StringMakerTests_261, ConvertUnsignedInt_Zero_261) {

    unsigned int testValue = 0u;

    EXPECT_EQ(StringMaker<unsigned int>::convert(testValue), "0");

}



TEST(StringMakerTests_261, ConvertFloat_PositiveNumber_261) {

    float testValue = 3.14f;

    EXPECT_EQ(StringMaker<float>::convert(testValue), "3.14");

}



TEST(StringMakerTests_261, ConvertFloat_Zero_261) {

    float testValue = 0.0f;

    EXPECT_EQ(StringMaker<float>::convert(testValue), "0");

}



TEST(StringMakerTests_261, ConvertFloat_NegativeNumber_261) {

    float testValue = -3.14f;

    EXPECT_EQ(StringMaker<float>::convert(testValue), "-3.14");

}
