#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class MockMatcher {

public:

    MOCK_METHOD(bool, match, (const int&), (const));

    MOCK_METHOD(std::string, describe, (), (const));

};



TEST_F(AllMatchMatcherTest_176, Describe_DelegatesToInnerMatcher_176) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, describe()).WillOnce(::testing::Return("mock description"));

    AllMatchMatcher<MockMatcher> allMatchMatcher(mockMatcher);

    EXPECT_EQ(allMatchMatcher.describe(), "all match mock description");

}



TEST_F(AllMatchMatcherTest_176, Match_ReturnsTrueIfAllElementsMatch_176) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    AllMatchMatcher<MockMatcher> allMatchMatcher(mockMatcher);

    std::vector<int> range = {1, 2, 3};

    EXPECT_TRUE(allMatchMatcher.match(range));

}



TEST_F(AllMatchMatcherTest_176, Match_ReturnsFalseIfAnyElementDoesNotMatch_176) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::_)).WillOnce(::testing::Return(true))

                                                 .WillOnce(::testing::Return(false))

                                                 .WillOnce(::testing::Return(true));

    AllMatchMatcher<MockMatcher> allMatchMatcher(mockMatcher);

    std::vector<int> range = {1, 2, 3};

    EXPECT_FALSE(allMatchMatcher.match(range));

}



TEST_F(AllMatchMatcherTest_176, Match_ReturnsTrueForEmptyRange_176) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(::testing::_)).Times(0);

    AllMatchMatcher<MockMatcher> allMatchMatcher(mockMatcher);

    std::vector<int> range = {};

    EXPECT_TRUE(allMatchMatcher.match(range));

}
