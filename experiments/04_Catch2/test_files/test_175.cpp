#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



// Mock MatcherBase and MatcherRHS for testing purposes

template<typename ArgLHS>

class MockMatcherBase : public Catch::Matchers::MatcherBase<ArgLHS> {

public:

    MOCK_METHOD(bool, match, (ArgLHS const&), (const override));

};



class MockMatcherRHS {

public:

    MOCK_CONST_METHOD1(match, bool(ArgLHS const&));

};



// Test fixture for the || operator

template<typename ArgLHS>

class OrOperatorTest_175 : public ::testing::Test {

protected:

    MockMatcherBase<ArgLHS> mock_lhs;

    MockMatcherRHS mock_rhs;

};



using testing::_;



TEST_F(OrOperatorTest_175<int>, BothMatchersFalse_ReturnsFalse_175) {

    EXPECT_CALL(mock_lhs, match(_)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_rhs, match(_)).WillOnce(testing::Return(false));



    auto matcher = mock_lhs || mock_rhs;

    EXPECT_FALSE(matcher.match(42));

}



TEST_F(OrOperatorTest_175<int>, LhsMatcherTrue_ReturnsTrue_175) {

    EXPECT_CALL(mock_lhs, match(_)).WillOnce(testing::Return(true));

    EXPECT_CALL(mock_rhs, match(_)).Times(0);



    auto matcher = mock_lhs || mock_rhs;

    EXPECT_TRUE(matcher.match(42));

}



TEST_F(OrOperatorTest_175<int>, RhsMatcherTrue_ReturnsTrue_175) {

    EXPECT_CALL(mock_lhs, match(_)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_rhs, match(_)).WillOnce(testing::Return(true));



    auto matcher = mock_lhs || mock_rhs;

    EXPECT_TRUE(matcher.match(42));

}



TEST_F(OrOperatorTest_175<int>, BothMatchersTrue_ReturnsTrue_175) {

    EXPECT_CALL(mock_lhs, match(_)).WillOnce(testing::Return(true));

    EXPECT_CALL(mock_rhs, match(_)).Times(0);



    auto matcher = mock_lhs || mock_rhs;

    EXPECT_TRUE(matcher.match(42));

}
