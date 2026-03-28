#include <gtest/gtest.h>

#include <cctype>



// Assuming the function isInt is part of a class or namespace,

// we will define it here for testing purposes.

namespace TestNamespace {

    bool isInt(const char *s) { 

        if (*s == '-' || *s == '+') { ++s; } 

        while (isdigit(*s)) { ++s; } 

        return *s == 0; 

    }

}



using namespace TestNamespace;



TEST(isIntTest_2741, PositiveInteger_2741) {

    EXPECT_TRUE(isInt("123"));

}



TEST(isIntTest_2741, NegativeInteger_2741) {

    EXPECT_TRUE(isInt("-123"));

}



TEST(isIntTest_2741, PositiveWithPlusSign_2741) {

    EXPECT_TRUE(isInt("+123"));

}



TEST(isIntTest_2741, Zero_2741) {

    EXPECT_TRUE(isInt("0"));

}



TEST(isIntTest_2741, NonDigitCharacter_2741) {

    EXPECT_FALSE(isInt("abc"));

}



TEST(isIntTest_2741, LeadingSpaces_2741) {

    EXPECT_FALSE(isInt(" 123"));

}



TEST(isIntTest_2741, TrailingCharacters_2741) {

    EXPECT_FALSE(isInt("123a"));

}



TEST(isIntTest_2741, EmptyString_2741) {

    EXPECT_FALSE(isInt(""));

}



TEST(isIntTest_2741, OnlyPlusSign_2741) {

    EXPECT_FALSE(isInt("+"));

}



TEST(isIntTest_2741, OnlyMinusSign_2741) {

    EXPECT_FALSE(isInt("-"));

}
