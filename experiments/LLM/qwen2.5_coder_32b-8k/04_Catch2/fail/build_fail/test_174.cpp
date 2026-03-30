#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using ::testing::_;



// Mock MatcherBase for testing purposes

template<typename ArgRHS>

class MockMatcherBase : public MatcherBase<ArgRHS> {

public:

    MOCK_METHOD(bool, match, (ArgRHS const& arg), (const override));

};



// Mock generic matcher for testing purposes

class MockGenericMatcher {

public:

    template<typename T>

    bool match(T const& arg) const {

        return matchImpl(arg);

    }



private:

    MOCK_CONST_METHOD1(matchImpl, bool(const auto&));

};



TEST_F(Catch2MatchersTest_174, GenericMatcherOrOperator_ReturnsTrueWhenEitherMatcherMatches_174) {

    MockGenericMatcher mockMatcherLHS;

    MockMatcherBase<int> mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, matchImpl(5)).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockMatcherRHS, match(5)).WillOnce(::testing::Return(true));



    auto matcher = mockMatcherLHS || mockMatcherRHS;

    bool result = matcher.match(5);



    EXPECT_TRUE(result);

}



TEST_F(Catch2MatchersTest_174, GenericMatcherOrOperator_ReturnsFalseWhenNeitherMatcherMatches_174) {

    MockGenericMatcher mockMatcherLHS;

    MockMatcherBase<int> mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, matchImpl(5)).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockMatcherRHS, match(5)).WillOnce(::testing::Return(false));



    auto matcher = mockMatcherLHS || mockMatcherRHS;

    bool result = matcher.match(5);



    EXPECT_FALSE(result);

}



TEST_F(Catch2MatchersTest_174, GenericMatcherOrOperator_ReturnsTrueWhenFirstMatcherMatches_174) {

    MockGenericMatcher mockMatcherLHS;

    MockMatcherBase<int> mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, matchImpl(5)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcherRHS, match(5)).Times(0);



    auto matcher = mockMatcherLHS || mockMatcherRHS;

    bool result = matcher.match(5);



    EXPECT_TRUE(result);

}



TEST_F(Catch2MatchersTest_174, GenericMatcherOrOperator_ReturnsTrueWhenSecondMatcherMatches_174) {

    MockGenericMatcher mockMatcherLHS;

    MockMatcherBase<int> mockMatcherRHS;



    EXPECT_CALL(mockMatcherLHS, matchImpl(5)).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockMatcherRHS, match(5)).WillOnce(::testing::Return(true));



    auto matcher = mockMatcherLHS || mockMatcherRHS;

    bool result = matcher.match(5);



    EXPECT_TRUE(result);

}
