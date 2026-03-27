#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers_templated.hpp>



using namespace Catch::Matchers::Detail;



class MockMatcher {

public:

    MOCK_METHOD(bool, match, (const std::string& arg), (const));

    MOCK_METHOD(std::string, describe, (), (const override));

};



TEST_F(MatchAllOfGenericTest_159, TwoMockMatchersMatch_ReturnsTrue_159) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillRepeatedly(::testing::Return(true));



    MatchAllOfGeneric<MockMatcher, MockMatcher> allOfMatcher(matcher1, matcher2);

    bool result = allOfMatcher.match("test");



    EXPECT_TRUE(result);

}



TEST_F(MatchAllOfGenericTest_159, TwoMockMatchersOneDoesNotMatch_ReturnsFalse_159) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillRepeatedly(::testing::Return(false));



    MatchAllOfGeneric<MockMatcher, MockMatcher> allOfMatcher(matcher1, matcher2);

    bool result = allOfMatcher.match("test");



    EXPECT_FALSE(result);

}



TEST_F(MatchAllOfGenericTest_159, SingleMockMatcherMatches_ReturnsTrue_159) {

    MockMatcher matcher;



    EXPECT_CALL(matcher, match(::testing::_)).WillRepeatedly(::testing::Return(true));



    MatchAllOfGeneric<MockMatcher> allOfMatcher(matcher);

    bool result = allOfMatcher.match("test");



    EXPECT_TRUE(result);

}



TEST_F(MatchAllOfGenericTest_159, SingleMockMatcherDoesNotMatch_ReturnsFalse_159) {

    MockMatcher matcher;



    EXPECT_CALL(matcher, match(::testing::_)).WillRepeatedly(::testing::Return(false));



    MatchAllOfGeneric<MockMatcher> allOfMatcher(matcher);

    bool result = allOfMatcher.match("test");



    EXPECT_FALSE(result);

}



TEST_F(MatchAllOfGenericTest_159, MultipleMockMatchersAllMatch_ReturnsTrue_159) {

    MockMatcher matcher1;

    MockMatcher matcher2;

    MockMatcher matcher3;



    EXPECT_CALL(matcher1, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(matcher3, match(::testing::_)).WillRepeatedly(::testing::Return(true));



    MatchAllOfGeneric<MockMatcher, MockMatcher, MockMatcher> allOfMatcher(matcher1, matcher2, matcher3);

    bool result = allOfMatcher.match("test");



    EXPECT_TRUE(result);

}



TEST_F(MatchAllOfGenericTest_159, MultipleMockMatchersOneDoesNotMatch_ReturnsFalse_159) {

    MockMatcher matcher1;

    MockMatcher matcher2;

    MockMatcher matcher3;



    EXPECT_CALL(matcher1, match(::testing::_)).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillRepeatedly(::testing::Return(false));

    EXPECT_CALL(matcher3, match(::testing::_)).WillRepeatedly(::testing::Return(true));



    MatchAllOfGeneric<MockMatcher, MockMatcher, MockMatcher> allOfMatcher(matcher1, matcher2, matcher3);

    bool result = allOfMatcher.match("test");



    EXPECT_FALSE(result);

}
