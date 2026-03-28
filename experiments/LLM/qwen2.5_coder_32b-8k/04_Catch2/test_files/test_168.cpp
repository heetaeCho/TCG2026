#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MockMatcher : public MatcherGenericBase {

public:

    MOCK_METHOD1(match, bool(const int&));

    MOCK_METHOD0(describe, std::string());

};



TEST_F(MockMatcherTest_168, Match_ReturnsTrue_168) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(testing::Return(true));



    bool result = mockMatcher.match(42);

    ASSERT_TRUE(result);

}



TEST_F(MockMatcherTest_168, Match_ReturnsFalse_168) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(testing::Return(false));



    bool result = mockMatcher.match(42);

    ASSERT_FALSE(result);

}



TEST_F(MockMatcherTest_168, Describe_ReturnsNonEmptyString_168) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, describe()).WillOnce(testing::Return("Expected description"));



    std::string description = mockMatcher.describe();

    ASSERT_FALSE(description.empty());

}



TEST_F(MatchNotOfGenericTest_168, Match_ReturnsFalseWhenOriginalReturnsTrue_168) {

    MockMatcher mockMatcher;

    MatchNotOfGeneric<MockMatcher> notMatcher(mockMatcher);

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(testing::Return(true));



    bool result = notMatcher.match(42);

    ASSERT_FALSE(result);

}



TEST_F(MatchNotOfGenericTest_168, Match_ReturnsTrueWhenOriginalReturnsFalse_168) {

    MockMatcher mockMatcher;

    MatchNotOfGeneric<MockMatcher> notMatcher(mockMatcher);

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(testing::Return(false));



    bool result = notMatcher.match(42);

    ASSERT_TRUE(result);

}



TEST_F(MatchNotOfGenericTest_168, Describe_DelegatesToOriginal_168) {

    MockMatcher mockMatcher;

    MatchNotOfGeneric<MockMatcher> notMatcher(mockMatcher);

    EXPECT_CALL(mockMatcher, describe()).WillOnce(testing::Return("Expected description"));



    std::string description = notMatcher.describe();

    ASSERT_EQ(description, "Expected description");

}
