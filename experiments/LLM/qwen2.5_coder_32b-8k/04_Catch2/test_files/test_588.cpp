#include <gtest/gtest.h>

#include "catch2/internal/catch_string_manip.cpp"



class CatchStringManipTest_588 : public ::testing::Test {};



TEST_F(CatchStringManipTest_588, Contains_ReturnsTrueWhenInfixPresent_588) {

    std::string s = "Hello, World!";

    std::string infix = "World";

    EXPECT_TRUE(Catch::contains(s, infix));

}



TEST_F(CatchStringManipTest_588, Contains_ReturnsFalseWhenInfixAbsent_588) {

    std::string s = "Hello, World!";

    std::string infix = "Universe";

    EXPECT_FALSE(Catch::contains(s, infix));

}



TEST_F(CatchStringManipTest_588, Contains_ReturnsTrueForEmptyInfix_588) {

    std::string s = "Hello, World!";

    std::string infix = "";

    EXPECT_TRUE(Catch::contains(s, infix));

}



TEST_F(CatchStringManipTest_588, Contains_ReturnsTrueWhenStringsMatchExactly_588) {

    std::string s = "Hello";

    std::string infix = "Hello";

    EXPECT_TRUE(Catch::contains(s, infix));

}



TEST_F(CatchStringManipTest_588, Contains_ReturnsFalseWhenInfixLongerThanString_588) {

    std::string s = "Hi";

    std::string infix = "Hello";

    EXPECT_FALSE(Catch::contains(s, infix));

}
