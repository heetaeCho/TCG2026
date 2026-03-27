#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"

#include <vector>



using namespace Catch::Matchers;



// Mock class to simulate a matcher

class MockMatcher : public MatcherGenericBase {

public:

    MOCK_METHOD(bool, match, (const std::string& elem), (const override));

    MOCK_METHOD(std::string, describe, (), (const override));

};



// Test fixture for AllMatchMatcher

class AllMatchMatcherTest_177 : public ::testing::Test {

protected:

    MockMatcher mockMatcher;

    AllMatchMatcher<MockMatcher> allMatchMatcher{mockMatcher};

};



TEST_F(AllMatchMatcherTest_177, AllElementsMatch_177) {

    std::vector<std::string> elements = {"test1", "test2", "test3"};

    EXPECT_CALL(mockMatcher, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    EXPECT_TRUE(allMatchMatcher.match(elements));

}



TEST_F(AllMatchMatcherTest_177, OneElementDoesNotMatch_177) {

    std::vector<std::string> elements = {"test1", "test2", "test3"};

    EXPECT_CALL(mockMatcher, match(::testing::_)).WillOnce(::testing::Return(true))

                                               .WillOnce(::testing::Return(false))

                                               .WillOnce(::testing::Return(true));

    EXPECT_FALSE(allMatchMatcher.match(elements));

}



TEST_F(AllMatchMatcherTest_177, EmptyRangeMatches_177) {

    std::vector<std::string> elements = {};

    EXPECT_CALL(mockMatcher, match(::testing::_)).Times(0);

    EXPECT_TRUE(allMatchMatcher.match(elements));

}



TEST_F(AllMatchMatcherTest_177, SingleElementMatches_177) {

    std::vector<std::string> elements = {"test1"};

    EXPECT_CALL(mockMatcher, match("test1")).WillOnce(::testing::Return(true));

    EXPECT_TRUE(allMatchMatcher.match(elements));

}



TEST_F(AllMatchMatcherTest_177, SingleElementDoesNotMatch_177) {

    std::vector<std::string> elements = {"test1"};

    EXPECT_CALL(mockMatcher, match("test1")).WillOnce(::testing::Return(false));

    EXPECT_FALSE(allMatchMatcher.match(elements));

}
