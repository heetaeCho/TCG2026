#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers::Detail;

using ::testing::_;



class MockMatcherBase : public MatcherBase<int> {

public:

    MOCK_CONST_METHOD1(match, bool(int const&));

    MOCK_CONST_METHOD0(describe, std::string());

};



TEST_F(MatchNotOfTest_144, NegatesMatchResult_144) {

    MockMatcherBase mockMatcher;

    MatchNotOf<int> notMatcher(mockMatcher);



    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(true));

    EXPECT_FALSE(notMatcher.match(42));



    EXPECT_CALL(mockMatcher, match(24)).WillOnce(::testing::Return(false));

    EXPECT_TRUE(notMatcher.match(24));

}



TEST_F(MatchNotOfTest_144, DescribesNegatedMatcher_144) {

    MockMatcherBase mockMatcher;

    MatchNotOf<int> notMatcher(mockMatcher);



    EXPECT_CALL(mockMatcher, describe()).WillOnce(::testing::Return("equals 42"));

    EXPECT_EQ(notMatcher.describe(), "not equals 42");

}
