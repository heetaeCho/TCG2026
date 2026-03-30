#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers::Detail;



class MockMatcher {

public:

    MOCK_CONST_METHOD1(match, bool(const int&));

    MOCK_CONST_METHOD0(describe, std::string());

};



TEST_F(MatchNotOfGenericTest_166, MatchReturnsTrueWhenUnderlyingMatcherReturnsFalse_166) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(false));

    

    MatchNotOfGeneric<MockMatcher> matchNotOfGeneric(mockMatcher);

    bool result = matchNotOfGeneric.match(42);

    

    EXPECT_TRUE(result);

}



TEST_F(MatchNotOfGenericTest_166, MatchReturnsFalseWhenUnderlyingMatcherReturnsTrue_166) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(true));

    

    MatchNotOfGeneric<MockMatcher> matchNotOfGeneric(mockMatcher);

    bool result = matchNotOfGeneric.match(42);

    

    EXPECT_FALSE(result);

}



TEST_F(MatchNotOfGenericTest_166, DescribeDelegatesToUnderlyingMatcher_166) {

    MockMatcher mockMatcher;

    std::string expectedDescription = "not some description";

    EXPECT_CALL(mockMatcher, describe()).WillOnce(::testing::Return(expectedDescription));

    

    MatchNotOfGeneric<MockMatcher> matchNotOfGeneric(mockMatcher);

    std::string result = matchNotOfGeneric.describe();

    

    EXPECT_EQ(result, expectedDescription);

}
