#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace ::testing;



// Mock matcher classes for testing

class MockMatcherLHS {

public:

    MOCK_CONST_METHOD1(match, bool(Catch::Detail::noncopyable_string));

};



class MockMatcherRHS {

public:

    MOCK_CONST_METHOD1(match, bool(Catch::Detail::noncopyable_string));

};



TEST_F(MockMatcherTest_169, BothMatchersMatch_169) {

    MockMatcherLHS mockMatcherLHS;

    MockMatcherRHS mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, match(_)).WillOnce(Return(true));

    EXPECT_CALL(mockMatcherRHS, match(_)).WillOnce(Return(true));



    auto matcher = mockMatcherLHS && mockMatcherRHS;

    bool result = matcher.match("test");



    EXPECT_TRUE(result);

}



TEST_F(MockMatcherTest_169, LHSDoesNotMatch_169) {

    MockMatcherLHS mockMatcherLHS;

    MockMatcherRHS mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, match(_)).WillOnce(Return(false));

    EXPECT_CALL(mockMatcherRHS, match(_)).WillOnce(Return(true));



    auto matcher = mockMatcherLHS && mockMatcherRHS;

    bool result = matcher.match("test");



    EXPECT_FALSE(result);

}



TEST_F(MockMatcherTest_169, RHSDoesNotMatch_169) {

    MockMatcherLHS mockMatcherLHS;

    MockMatcherRHS mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, match(_)).WillOnce(Return(true));

    EXPECT_CALL(mockMatcherRHS, match(_)).WillOnce(Return(false));



    auto matcher = mockMatcherLHS && mockMatcherRHS;

    bool result = matcher.match("test");



    EXPECT_FALSE(result);

}



TEST_F(MockMatcherTest_169, BothMatchersDoNotMatch_169) {

    MockMatcherLHS mockMatcherLHS;

    MockMatcherRHS mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, match(_)).WillOnce(Return(false));

    EXPECT_CALL(mockMatcherRHS, match(_)).WillOnce(Return(false));



    auto matcher = mockMatcherLHS && mockMatcherRHS;

    bool result = matcher.match("test");



    EXPECT_FALSE(result);

}
