#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers::Detail;

using ::testing::_;

using ::testing::Eq;



// Mock Matcher for testing purposes

class MockMatcher {

public:

    MOCK_METHOD(bool, match, (int), const);

    MOCK_METHOD(std::string, describe, (), const);

};



TEST_F(MatchAnyOfGenericTest_165, Match_ReturnsTrueWhenOneMatcherMatches_165) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(_)).WillOnce([](int arg) { return arg == 1; });

    EXPECT_CALL(matcher2, match(_)).WillOnce([](int arg) { return false; });



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchers{matcher1, matcher2};

    ASSERT_TRUE(matchers.match(1));

}



TEST_F(MatchAnyOfGenericTest_165, Match_ReturnsFalseWhenNoMatchersMatch_165) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(_)).WillOnce([](int arg) { return false; });

    EXPECT_CALL(matcher2, match(_)).WillOnce([](int arg) { return false; });



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchers{matcher1, matcher2};

    ASSERT_FALSE(matchers.match(1));

}



TEST_F(MatchAnyOfGenericTest_165, Match_ReturnsTrueWhenMultipleMatchersMatch_165) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(_)).WillOnce([](int arg) { return true; });

    EXPECT_CALL(matcher2, match(_)).WillOnce([](int arg) { return true; });



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchers{matcher1, matcher2};

    ASSERT_TRUE(matchers.match(1));

}



TEST_F(MatchAnyOfGenericTest_165, Describe_ReturnsDescriptionOfAllMatchers_165) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, describe()).WillOnce([]() { return "Matcher 1"; });

    EXPECT_CALL(matcher2, describe()).WillOnce([]() { return "Matcher 2"; });



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchers{matcher1, matcher2};

    ASSERT_EQ("Matcher 1 or Matcher 2", matchers.describe());

}



TEST_F(MatchAnyOfGenericTest_165, Constructor_CopiesMatchersCorrectly_165) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, describe()).WillOnce([]() { return "Matcher 1"; });

    EXPECT_CALL(matcher2, describe()).WillOnce([]() { return "Matcher 2"; });



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matchers{matcher1, matcher2};

    ASSERT_EQ("Matcher 1 or Matcher 2", matchers.describe());

}
