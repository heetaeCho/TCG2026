#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_exception.hpp"



using namespace Catch::Matchers;



class ExceptionMessageMatchesMatcherTest_241 : public ::testing::Test {

protected:

    ExceptionMessageMatchesMatcher<std::string> matcher;

    

    ExceptionMessageMatchesMatcherTest_241() 

        : matcher("Expected exception message") {}

};



TEST_F(ExceptionMessageMatchesMatcherTest_241, Match_ReturnsTrueForMatchingExceptionMessage_241) {

    std::exception ex("Expected exception message");

    EXPECT_TRUE(matcher.match(ex));

}



TEST_F(ExceptionMessageMatchesMatcherTest_241, Match_ReturnsFalseForNonMatchingExceptionMessage_241) {

    std::exception ex("Unexpected exception message");

    EXPECT_FALSE(matcher.match(ex));

}



TEST_F(ExceptionMessageMatchesMatcherTest_241, Describe_ReturnsCorrectDescription_241) {

    EXPECT_EQ(matcher.describe(), " matches \"Expected exception message\"");

}



TEST_F(ExceptionMessageMatchesMatcherTest_241, Match_HandlesEmptyExceptionMessage_241) {

    ExceptionMessageMatchesMatcher<std::string> emptyMatcher("");

    std::exception ex("");

    EXPECT_TRUE(emptyMatcher.match(ex));

}



TEST_F(ExceptionMessageMatchesMatcherTest_241, Describe_ReturnsCorrectDescriptionForEmptyString_241) {

    ExceptionMessageMatchesMatcher<std::string> emptyMatcher("");

    EXPECT_EQ(emptyMatcher.describe(), " matches \"\"");

}
