#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_exception.hpp"



using namespace Catch;

using namespace Matchers;



// Mock class for exception handling if needed

class MockExceptionMatcher {

public:

    MOCK_METHOD(bool, match, (std::exception const&), (const));

};



TEST(ExceptionMessageMatcherTest_245, ConstructorSetsMessage_245) {

    std::string expectedMessage = "Expected error message";

    ExceptionMessageMatcher matcher(expectedMessage);

    // Assuming there's a way to verify the internal state through public interface

    // For this example, we assume match method uses the message for comparison

    EXPECT_TRUE(matcher.match(std::runtime_error(expectedMessage)));

}



TEST(ExceptionMessageMatcherTest_245, MatchReturnsTrueForMatchingMessage_245) {

    std::string expectedMessage = "Expected error message";

    ExceptionMessageMatcher matcher(expectedMessage);

    EXPECT_TRUE(matcher.match(std::runtime_error(expectedMessage)));

}



TEST(ExceptionMessageMatcherTest_245, MatchReturnsFalseForNonMatchingMessage_245) {

    std::string expectedMessage = "Expected error message";

    std::string differentMessage = "Different error message";

    ExceptionMessageMatcher matcher(expectedMessage);

    EXPECT_FALSE(matcher.match(std::runtime_error(differentMessage)));

}



TEST(ExceptionMessageMatcherTest_245, MatchHandlesEmptyStringCorrectly_245) {

    std::string emptyMessage = "";

    ExceptionMessageMatcher matcher(emptyMessage);

    EXPECT_TRUE(matcher.match(std::runtime_error(emptyMessage)));

}



TEST(ExceptionMessageMatcherTest_245, MatchHandlesLongMessageCorrectly_245) {

    std::string longMessage = "This is a very long error message that should still be handled correctly by the matcher.";

    ExceptionMessageMatcher matcher(longMessage);

    EXPECT_TRUE(matcher.match(std::runtime_error(longMessage)));

}
