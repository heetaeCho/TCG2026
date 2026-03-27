#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_exception.hpp"



using namespace Catch::Matchers;



class ExceptionMessageMatcherTest_244 : public ::testing::Test {

protected:

    std::string testMessage = "Test exception message";

    ExceptionMessageMatcher matcher{testMessage};

};



TEST_F(ExceptionMessageMatcherTest_244, DescribeReturnsCorrectString_244) {

    EXPECT_EQ(matcher.describe(), "exception message matches \"Test exception message\"");

}



TEST_F(ExceptionMessageMatcherTest_244, MatchReturnsTrueForMatchingException_244) {

    std::exception testException(testMessage);

    EXPECT_TRUE(matcher.match(testException));

}



TEST_F(ExceptionMessageMatcherTest_244, MatchReturnsFalseForNonMatchingException_244) {

    std::exception testException("Different message");

    EXPECT_FALSE(matcher.match(testException));

}
