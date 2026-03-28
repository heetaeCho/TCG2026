#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_exception.hpp"



using namespace Catch::Matchers;



class ExceptionMessageMatcherTest : public ::testing::Test {

protected:

    std::string test_message = "Test exception message";

    ExceptionMessageMatcher matcher{test_message};

};



TEST_F(ExceptionMessageMatcherTest_243, Match_ReturnsTrueForExactMatch_243) {

    std::exception ex(test_message);

    EXPECT_TRUE(matcher.match(ex));

}



TEST_F(ExceptionMessageMatcherTest_243, Match_ReturnsFalseForDifferentMessage_243) {

    std::string different_message = "Different exception message";

    std::exception ex(different_message);

    EXPECT_FALSE(matcher.match(ex));

}



TEST_F(ExceptionMessageMatcherTest_243, Describe_ReturnsExpectedDescription_243) {

    std::string expected_description = "Exception with message \"" + test_message + "\"";

    EXPECT_EQ(expected_description, matcher.describe());

}
