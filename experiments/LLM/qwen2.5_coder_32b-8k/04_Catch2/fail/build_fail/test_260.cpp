#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



namespace Catch {

    struct StringMakerTest : ::testing::Test {};

}



TEST_F(StringMakerTest_260, ConvertStdString_ReturnsSameString_260) {

    std::string input = "Hello, World!";

    EXPECT_EQ(Catch::StringMaker<std::string>::convert(input), input);

}



TEST_F(StringMakerTest_260, ConvertCharConstPtr_ReturnsSameString_260) {

    const char* input = "Hello, World!";

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(input), std::string(input));

}



TEST_F(StringMakerTest_260, ConvertBoolTrue_ReturnsTrueString_260) {

    EXPECT_EQ(Catch::StringMaker<bool>::convert(true), "true");

}



TEST_F(StringMakerTest_260, ConvertBoolFalse_ReturnsFalseString_260) {

    EXPECT_EQ(Catch::StringMaker<bool>::convert(false), "false");

}



TEST_F(StringMakerTest_260, ConvertNullptr_ReturnsNullString_260) {

    EXPECT_EQ(Catch::StringMaker<std::nullptr_t>::convert(nullptr), "nullptr");

}



TEST_F(StringMakerTest_260, ConvertInt_ReturnsCorrectString_260) {

    int value = 42;

    EXPECT_EQ(Catch::StringMaker<int>::convert(value), std::to_string(value));

}



TEST_F(StringMakerTest_260, ConvertLong_ReturnsCorrectString_260) {

    long value = 987654321;

    EXPECT_EQ(Catch::StringMaker<long>::convert(value), std::to_string(value));

}



TEST_F(StringMakerTest_260, ConvertLongLong_ReturnsCorrectString_260) {

    long long value = 123456789012345LL;

    EXPECT_EQ(Catch::StringMaker<long long>::convert(value), std::to_string(value));

}



TEST_F(StringMakerTest_260, ConvertUnsignedInt_ReturnsCorrectString_260) {

    unsigned int value = 42u;

    EXPECT_EQ(Catch::StringMaker<unsigned int>::convert(value), std::to_string(value));

}



TEST_F(StringMakerTest_260, ConvertUnsignedLong_ReturnsCorrectString_260) {

    unsigned long value = 987654321ul;

    EXPECT_EQ(Catch::StringMaker<unsigned long>::convert(value), std::to_string(value));

}



TEST_F(StringMakerTest_260, ConvertUnsignedLongLong_ReturnsCorrectString_260) {

    unsigned long long value = 123456789012345ULL;

    EXPECT_EQ(Catch::StringMaker<unsigned long long>::convert(value), std::to_string(value));

}



TEST_F(StringMakerTest_260, ConvertSignedChar_ReturnsCorrectString_260) {

    signed char value = 'A';

    EXPECT_EQ(Catch::StringMaker<signed char>::convert(value), std::string(1, value));

}



TEST_F(StringMakerTest_260, ConvertChar_ReturnsCorrectString_260) {

    char value = 'B';

    EXPECT_EQ(Catch::StringMaker<char>::convert(value), std::string(1, value));

}



TEST_F(StringMakerTest_260, ConvertUnsignedChar_ReturnsCorrectString_260) {

    unsigned char value = 'C';

    EXPECT_EQ(Catch::StringMaker<unsigned char>::convert(value), std::string(1, value));

}



TEST_F(StringMakerTest_260, ConvertFloat_ReturnsCorrectString_260) {

    float value = 3.14f;

    EXPECT_EQ(Catch::StringMaker<float>::convert(value), "3.14");

}



TEST_F(StringMakerTest_260, ConvertDouble_ReturnsCorrectString_260) {

    double value = 2.71828;

    EXPECT_EQ(Catch::StringMaker<double>::convert(value), "2.71828");

}
