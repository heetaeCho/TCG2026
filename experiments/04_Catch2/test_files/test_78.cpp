#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"

#include "catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch;



TEST_F(StringMakerTest_78, ConvertCharPointer_78) {

    const char* str = "Hello";

    EXPECT_EQ(StringMaker<char const*>::convert(str), "Hello");

}



TEST_F(StringMakerTest_78, ConvertString_78) {

    std::string str = "World";

    EXPECT_EQ(StringMaker<std::string>::convert(str), "World");

}



TEST_F(StringMakerTest_78, ConvertBoolTrue_78) {

    bool b = true;

    EXPECT_EQ(StringMaker<bool>::convert(b), "true");

}



TEST_F(StringMakerTest_78, ConvertBoolFalse_78) {

    bool b = false;

    EXPECT_EQ(StringMaker<bool>::convert(b), "false");

}



TEST_F(StringMakerTest_78, ConvertNullptr_78) {

    std::nullptr_t nptr = nullptr;

    EXPECT_EQ(StringMaker<std::nullptr_t>::convert(nptr), "nullptr");

}



TEST_F(StringMakerTest_78, ConvertIntPositive_78) {

    int value = 123;

    EXPECT_EQ(StringMaker<int>::convert(value), "123");

}



TEST_F(StringMakerTest_78, ConvertIntNegative_78) {

    int value = -456;

    EXPECT_EQ(StringMaker<int>::convert(value), "-456");

}



TEST_F(StringMakerTest_78, ConvertZero_78) {

    int value = 0;

    EXPECT_EQ(StringMaker<int>::convert(value), "0");

}



TEST_F(StringMakerTest_78, ConvertUnsignedInt_78) {

    unsigned int value = 789;

    EXPECT_EQ(StringMaker<unsigned int>::convert(value), "789");

}



TEST_F(StringMakerTest_78, ConvertFloatPositive_78) {

    float value = 123.456f;

    EXPECT_EQ(StringMaker<float>::convert(value), "123.456");

}



TEST_F(StringMakerTest_78, ConvertDoubleNegative_78) {

    double value = -987.654;

    EXPECT_EQ(StringMaker<double>::convert(value), "-987.654");

}
