#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock class to simulate a matcher for testing purposes

class MockMatcher {

public:

    MOCK_METHOD1(match, bool(const int& arg));

};



TEST_F(MatchAnyOfGenericTest_161, MatchReturnsTrueWhenOneMatcherMatches_161) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(::testing::Return(true));



    std::array<void const*, 2> matchers = {static_cast<MockMatcher*>(&mockMatcher1), static_cast<MockMatcher*>(&mockMatcher2)};

    MatchAnyOfGeneric<std::tuple<MockMatcher&, MockMatcher&>> matcher(matchers);



    EXPECT_TRUE(matcher.match(42));

}



TEST_F(MatchAnyOfGenericTest_161, MatchReturnsFalseWhenNoMatchersMatch_161) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(::testing::Return(false));



    std::array<void const*, 2> matchers = {static_cast<MockMatcher*>(&mockMatcher1), static_cast<MockMatcher*>(&mockMatcher2)};

    MatchAnyOfGeneric<std::tuple<MockMatcher&, MockMatcher&>> matcher(matchers);



    EXPECT_FALSE(matcher.match(42));

}



TEST_F(MatchAnyOfGenericTest_161, MatchReturnsTrueWhenAllMatchersMatch_161) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(::testing::Return(true));



    std::array<void const*, 2> matchers = {static_cast<MockMatcher*>(&mockMatcher1), static_cast<MockMatcher*>(&mockMatcher2)};

    MatchAnyOfGeneric<std::tuple<MockMatcher&, MockMatcher&>> matcher(matchers);



    EXPECT_TRUE(matcher.match(42));

}



TEST_F(MatchAnyOfGenericTest_161, BoundaryConditionWithSingleMatcherMatching_161) {

    MockMatcher mockMatcher;



    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(true));



    std::array<void const*, 1> matchers = {static_cast<MockMatcher*>(&mockMatcher)};

    MatchAnyOfGeneric<std::tuple<MockMatcher&>> matcher(matchers);



    EXPECT_TRUE(matcher.match(42));

}



TEST_F(MatchAnyOfGenericTest_161, BoundaryConditionWithSingleMatcherNotMatching_161) {

    MockMatcher mockMatcher;



    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(false));



    std::array<void const*, 1> matchers = {static_cast<MockMatcher*>(&mockMatcher)};

    MatchAnyOfGeneric<std::tuple<MockMatcher&>> matcher(matchers);



    EXPECT_FALSE(matcher.match(42));

}
