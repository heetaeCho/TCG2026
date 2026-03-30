#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock Matcher class for testing purposes

class MockMatcher {

public:

    MOCK_METHOD1(match, bool(const int& arg));

};



TEST_F(MockMatcherTest_154, MatchReturnsTrueForMatchingValue_154) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(testing::Return(true));



    std::array<void const*, 1> matchers = {static_cast<void const*>(&mockMatcher)};

    bool result = match_any_of<MockMatcher>(42, matchers, std::index_sequence<0>{});



    EXPECT_TRUE(result);

}



TEST_F(MockMatcherTest_154, MatchReturnsFalseForNonMatchingValue_154) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(testing::Return(false));



    std::array<void const*, 1> matchers = {static_cast<void const*>(&mockMatcher)};

    bool result = match_any_of<MockMatcher>(42, matchers, std::index_sequence<0>{});



    EXPECT_FALSE(result);

}



TEST_F(MockMatcherTest_154, MatchAnyOfReturnsTrueIfAnyMatcherMatches_154) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(testing::Return(true));



    std::array<void const*, 2> matchers = {static_cast<void const*>(&mockMatcher1), static_cast<void const*>(&mockMatcher2)};

    bool result = match_any_of<MockMatcher, MockMatcher>(42, matchers, std::index_sequence<0, 1>{});



    EXPECT_TRUE(result);

}



TEST_F(MockMatcherTest_154, MatchAnyOfReturnsFalseIfNoMatchersMatch_154) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(testing::Return(false));



    std::array<void const*, 2> matchers = {static_cast<void const*>(&mockMatcher1), static_cast<void const*>(&mockMatcher2)};

    bool result = match_any_of<MockMatcher, MockMatcher>(42, matchers, std::index_sequence<0, 1>{});



    EXPECT_FALSE(result);

}
