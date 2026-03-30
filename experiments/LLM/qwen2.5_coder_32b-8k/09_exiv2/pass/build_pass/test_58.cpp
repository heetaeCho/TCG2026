#include <gtest/gtest.h>

#include "exiv2/error.hpp"



using namespace Exiv2;



TEST(toBasicStringTest_58, IntConversion_58) {

    int number = 42;

    std::string result = toBasicString<char>(number);

    EXPECT_EQ(result, "42");

}



TEST(toBasicStringTest_58, DoubleConversion_58) {

    double number = 3.14159;

    std::string result = toBasicString<char>(number);

    EXPECT_EQ(result, "3.14159");

}



TEST(toBasicStringTest_58, StringConversion_58) {

    std::string text = "Hello, World!";

    std::string result = toBasicString<char>(text);

    EXPECT_EQ(result, "Hello, World!");

}



TEST(toBasicStringTest_58, EmptyStringConversion_58) {

    std::string text = "";

    std::string result = toBasicString<char>(text);

    EXPECT_EQ(result, "");

}



TEST(toBasicStringTest_58, NegativeIntConversion_58) {

    int number = -100;

    std::string result = toBasicString<char>(number);

    EXPECT_EQ(result, "-100");

}



TEST(toBasicStringTest_58, ZeroConversion_58) {

    int number = 0;

    std::string result = toBasicString<char>(number);

    EXPECT_EQ(result, "0");

}
