#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MockMatcher {

public:

    MOCK_METHOD(bool, match, (const auto& arg), const);

    MOCK_METHOD(std::string, describe, (), const);

};



TEST_F(MatchAnyOfGenericTest_162, MatchWithSingleMatcher_ReturnsTrue_162) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(testing::_)).WillOnce(testing::Return(true));



    MatchAnyOfGeneric<MockMatcher> matchAny({&mockMatcher});



    bool result = matchAny.match("test");

    EXPECT_TRUE(result);

}



TEST_F(MatchAnyOfGenericTest_162, MatchWithSingleMatcher_ReturnsFalse_162) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(testing::_)).WillOnce(testing::Return(false));



    MatchAnyOfGeneric<MockMatcher> matchAny({&mockMatcher});



    bool result = matchAny.match("test");

    EXPECT_FALSE(result);

}



TEST_F(MatchAnyOfGenericTest_162, MatchWithMultipleMatchers_ReturnsTrueWhenOneMatches_162) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(testing::_)).WillOnce(testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(testing::_)).WillOnce(testing::Return(true));



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchAny({&mockMatcher1, &mockMatcher2});



    bool result = matchAny.match("test");

    EXPECT_TRUE(result);

}



TEST_F(MatchAnyOfGenericTest_162, MatchWithMultipleMatchers_ReturnsFalseWhenNoneMatch_162) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(testing::_)).WillOnce(testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(testing::_)).WillOnce(testing::Return(false));



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchAny({&mockMatcher1, &mockMatcher2});



    bool result = matchAny.match("test");

    EXPECT_FALSE(result);

}



TEST_F(MatchAnyOfGenericTest_162, Describe_CallsDescribeOnMatchers_162) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, describe()).WillOnce(testing::Return("matcher1"));

    EXPECT_CALL(mockMatcher2, describe()).WillOnce(testing::Return("matcher2"));



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchAny({&mockMatcher1, &mockMatcher2});



    std::string description = matchAny.describe();

    EXPECT_EQ(description, "matcher1 or matcher2");

}
