#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



// Test that ChompIndicator returns a valid RegEx object

TEST(ChompIndicatorTest_151, ReturnsValidRegExObject_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_TRUE(&regex != nullptr);

}



// Test that ChompIndicator regex matches '+' character

TEST(ChompIndicatorTest_151, MatchesPlusCharacter_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_TRUE(regex.Matches('+'));

}



// Test that ChompIndicator regex matches '-' character

TEST(ChompIndicatorTest_151, MatchesMinusCharacter_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_TRUE(regex.Matches('-'));

}



// Test that ChompIndicator regex does not match other characters

TEST(ChompIndicatorTest_151, DoesNotMatchOtherCharacters_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_FALSE(regex.Matches('a'));

    EXPECT_FALSE(regex.Matches('0'));

    EXPECT_FALSE(regex.Matches(' '));

}



// Test that ChompIndicator regex matches string "+"

TEST(ChompIndicatorTest_151, MatchesStringPlus_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_TRUE(regex.Matches("+"));

}



// Test that ChompIndicator regex matches string "-"

TEST(ChompIndicatorTest_151, MatchesStringMinus_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_TRUE(regex.Matches("-"));

}



// Test that ChompIndicator regex does not match other strings

TEST(ChompIndicatorTest_151, DoesNotMatchOtherStrings_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_FALSE(regex.Matches("a"));

    EXPECT_FALSE(regex.Matches("0"));

    EXPECT_FALSE(regex.Matches(" "));

}



// Test that ChompIndicator regex returns correct match position for "+"

TEST(ChompIndicatorTest_151, MatchPositionForPlus_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_EQ(regex.Match("+"), 1);

}



// Test that ChompIndicator regex returns correct match position for "-"

TEST(ChompIndicatorTest_151, MatchPositionForMinus_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_EQ(regex.Match("-"), 1);

}



// Test that ChompIndicator regex returns -1 for non-matching characters

TEST(ChompIndicatorTest_151, NonMatchingCharacterReturnsNegativeOne_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_EQ(regex.Match("a"), -1);

    EXPECT_EQ(regex.Match("0"), -1);

    EXPECT_EQ(regex.Match(" "), -1);

}



// Test that ChompIndicator regex returns -1 for non-matching strings

TEST(ChompIndicatorTest_151, NonMatchingStringReturnsNegativeOne_151) {

    const RegEx& regex = ChompIndicator();

    EXPECT_EQ(regex.Match("abc"), -1);

    EXPECT_EQ(regex.Match("012"), -1);

    EXPECT_EQ(regex.Match("   "), -1);

}
