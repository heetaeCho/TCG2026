#include <gtest/gtest.h>

#include "stringsource.h"



namespace YAML {



class StringCharSourceTest_107 : public ::testing::Test {

protected:

    const char* testString = "HelloWorld";

    std::size_t testSize = 10;

    StringCharSource source;



    StringCharSourceTest_107() : source(testString, testSize) {}

};



TEST_F(StringCharSourceTest_107, OperatorPlusEqualsIncreasesOffset_107) {

    std::size_t initialOffset = 0;

    std::size_t offsetToAdd = 5;



    source += offsetToAdd;



    EXPECT_EQ(source[testSize - 1], testString[initialOffset + offsetToAdd]);

}



TEST_F(StringCharSourceTest_107, OperatorPlusEqualsAtBoundaryDoesNotOverflow_107) {

    std::size_t offsetToAdd = testSize;



    source += offsetToAdd;



    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_107, OperatorBoolReturnsTrueWhenWithinBounds_107) {

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_107, OperatorBoolReturnsFalseWhenAtBoundary_107) {

    source += testSize;



    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_107, OperatorExclamationMarkReturnsFalseWhenWithinBounds_107) {

    EXPECT_FALSE(static_cast<bool>(!source));

}



TEST_F(StringCharSourceTest_107, OperatorExclamationMarkReturnsTrueWhenAtBoundary_107) {

    source += testSize;



    EXPECT_TRUE(static_cast<bool>(!source));

}



TEST_F(StringCharSourceTest_107, OperatorSubscriptAccessesCorrectCharacter_107) {

    std::size_t index = 5;



    char expectedChar = testString[index];

    char actualChar = source[index];



    EXPECT_EQ(actualChar, expectedChar);

}



TEST_F(StringCharSourceTest_107, OperatorPlusReturnsNewInstanceWithOffset_107) {

    int offsetToAdd = 3;

    StringCharSource newSource = source + offsetToAdd;



    EXPECT_EQ(newSource[0], testString[offsetToAdd]);

}



TEST_F(StringCharSourceTest_107, OperatorIncrementIncreasesOffsetByOne_107) {

    char initialChar = source[0];

    ++source;

    char nextChar = source[0];



    EXPECT_NE(initialChar, nextChar);

}



} // namespace YAML
