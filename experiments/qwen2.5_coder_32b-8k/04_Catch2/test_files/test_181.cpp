#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class MockMatcher {

public:

    MOCK_METHOD1(match, bool(const int&));

};



TEST_F(AnyMatchMatcherTest_181, MatchWithEmptyRange_ReturnsFalse_181) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::_)).Times(0);



    AnyMatchMatcher<MockMatcher> matcher(mockMatcher);

    std::vector<int> emptyRange;



    bool result = matcher.match(emptyRange);

    EXPECT_FALSE(result);

}



TEST_F(AnyMatchMatcherTest_181, MatchWithAllNonMatchingElements_ReturnsFalse_181) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::_)).WillRepeatedly(::testing::Return(false));



    AnyMatchMatcher<MockMatcher> matcher(mockMatcher);

    std::vector<int> range = {1, 2, 3};



    bool result = matcher.match(range);

    EXPECT_FALSE(result);

}



TEST_F(AnyMatchMatcherTest_181, MatchWithOneMatchingElement_ReturnsTrue_181) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::Eq(1))).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockMatcher, match(::testing::Eq(2))).WillOnce(::testing::Return(true));



    AnyMatchMatcher<MockMatcher> matcher(mockMatcher);

    std::vector<int> range = {1, 2, 3};



    bool result = matcher.match(range);

    EXPECT_TRUE(result);

}



TEST_F(AnyMatchMatcherTest_181, MatchWithAllMatchingElements_ReturnsTrue_181) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::_)).WillRepeatedly(::testing::Return(true));



    AnyMatchMatcher<MockMatcher> matcher(mockMatcher);

    std::vector<int> range = {1, 2, 3};



    bool result = matcher.match(range);

    EXPECT_TRUE(result);

}



TEST_F(AnyMatchMatcherTest_181, MatchWithSingleElementMatching_ReturnsTrue_181) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::Eq(1))).WillOnce(::testing::Return(true));



    AnyMatchMatcher<MockMatcher> matcher(mockMatcher);

    std::vector<int> range = {1};



    bool result = matcher.match(range);

    EXPECT_TRUE(result);

}



TEST_F(AnyMatchMatcherTest_181, MatchWithSingleElementNonMatching_ReturnsFalse_181) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::Eq(1))).WillOnce(::testing::Return(false));



    AnyMatchMatcher<MockMatcher> matcher(mockMatcher);

    std::vector<int> range = {1};



    bool result = matcher.match(range);

    EXPECT_FALSE(result);

}
