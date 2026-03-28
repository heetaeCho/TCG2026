#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;



// Test fixture for StringMaker tests

class StringMakerTest_81 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed

};



TEST_F(StringMakerTest_81, ConvertCharPointerToString_81) {

    const char* testString = "Hello, World!";

    EXPECT_EQ(StringMaker<char const*>::convert(testString), std::string("Hello, World!"));

}



TEST_F(StringMakerTest_81, ConvertNullptrToString_81) {

    EXPECT_EQ(StringMaker<std::nullptr_t>::convert(nullptr), std::string("nullptr"));

}



TEST_F(StringMakerTest_81, ConvertBoolToStringTrue_81) {

    EXPECT_EQ(StringMaker<bool>::convert(true), std::string("true"));

}



TEST_F(StringMakerTest_81, ConvertBoolToStringFalse_81) {

    EXPECT_EQ(StringMaker<bool>::convert(false), std::string("false"));

}



TEST_F(StringMakerTest_81, ConvertIntToStringPositive_81) {

    EXPECT_EQ(StringMaker<int>::convert(42), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertIntToStringNegative_81) {

    EXPECT_EQ(StringMaker<int>::convert(-42), std::string("-42"));

}



TEST_F(StringMakerTest_81, ConvertUnsignedIntToString_81) {

    EXPECT_EQ(StringMaker<unsigned int>::convert(42u), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertLongToStringPositive_81) {

    EXPECT_EQ(StringMaker<long>::convert(42l), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertLongToStringNegative_81) {

    EXPECT_EQ(StringMaker<long>::convert(-42l), std::string("-42"));

}



TEST_F(StringMakerTest_81, ConvertUnsignedLongToString_81) {

    EXPECT_EQ(StringMaker<unsigned long>::convert(42ul), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertLongLongToStringPositive_81) {

    EXPECT_EQ(StringMaker<long long>::convert(42ll), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertLongLongToStringNegative_81) {

    EXPECT_EQ(StringMaker<long long>::convert(-42ll), std::string("-42"));

}



TEST_F(StringMakerTest_81, ConvertUnsignedLongLongToString_81) {

    EXPECT_EQ(StringMaker<unsigned long long>::convert(42ull), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertSignedCharToString_81) {

    signed char testChar = 'A';

    EXPECT_EQ(StringMaker<signed char>::convert(testChar), std::string("A"));

}



TEST_F(StringMakerTest_81, ConvertUnsignedCharToString_81) {

    unsigned char testChar = 'B';

    EXPECT_EQ(StringMaker<unsigned char>::convert(testChar), std::string("B"));

}



TEST_F(StringMakerTest_81, ConvertFloatToStringPositive_81) {

    EXPECT_EQ(StringMaker<float>::convert(42.0f), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertFloatToStringNegative_81) {

    EXPECT_EQ(StringMaker<float>::convert(-42.0f), std::string("-42"));

}



TEST_F(StringMakerTest_81, ConvertDoubleToStringPositive_81) {

    EXPECT_EQ(StringMaker<double>::convert(42.0), std::string("42"));

}



TEST_F(StringMakerTest_81, ConvertDoubleToStringNegative_81) {

    EXPECT_EQ(StringMaker<double>::convert(-42.0), std::string("-42"));

}
