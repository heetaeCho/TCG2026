#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_exception.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



// Mocking an exception for testing purposes

struct TestException : public std::exception {

    const char* what() const noexcept override { return "Test Exception"; }

};



class ExceptionMessageMatchesMatcherTest_240 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ExceptionMessageMatchesMatcherTest_240, Match_ReturnsTrueForMatchingExceptionMessage_240) {

    ExceptionMessageMatchesMatcher<std::string> matcher("Test Exception");

    TestException ex;

    EXPECT_TRUE(matcher.match(ex));

}



TEST_F(ExceptionMessageMatchesMatcherTest_240, Match_ReturnsFalseForNonMatchingExceptionMessage_240) {

    ExceptionMessageMatchesMatcher<std::string> matcher("Another Message");

    TestException ex;

    EXPECT_FALSE(matcher.match(ex));

}



TEST_F(ExceptionMessageMatchesMatcherTest_240, Describe_ReturnsCorrectDescription_240) {

    ExceptionMessageMatchesMatcher<std::string> matcher("Expected Exception");

    EXPECT_EQ(matcher.describe(), "has message that matches Expected Exception");

}
