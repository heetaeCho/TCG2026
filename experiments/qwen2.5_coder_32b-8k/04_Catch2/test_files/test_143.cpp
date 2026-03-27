#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MatchNotOfMock : public MatcherBase<int> {

public:

    MOCK_METHOD1(match, bool(int const& arg));

    MOCK_METHOD0(describe, std::string());

};



TEST_F(MatchNotOfTest_143, NormalOperation_ReturnsOppositeOfUnderlyingMatcher_143) {

    MatchNotOfMock underlyingMatcher;

    EXPECT_CALL(underlyingMatcher, match(42)).WillOnce(::testing::Return(true));

    

    MatchNotOf<int> matchNotOf(underlyingMatcher);

    bool result = matchNotOf.match(42);

    

    EXPECT_FALSE(result);

}



TEST_F(MatchNotOfTest_143, BoundaryCondition_ReturnsOppositeForFalse_143) {

    MatchNotOfMock underlyingMatcher;

    EXPECT_CALL(underlyingMatcher, match(0)).WillOnce(::testing::Return(false));

    

    MatchNotOf<int> matchNotOf(underlyingMatcher);

    bool result = matchNotOf.match(0);

    

    EXPECT_TRUE(result);

}



TEST_F(MatchNotOfTest_143, BoundaryCondition_ReturnsOppositeForTrue_143) {

    MatchNotOfMock underlyingMatcher;

    EXPECT_CALL(underlyingMatcher, match(-1)).WillOnce(::testing::Return(true));

    

    MatchNotOf<int> matchNotOf(underlyingMatcher);

    bool result = matchNotOf.match(-1);

    

    EXPECT_FALSE(result);

}



TEST_F(MatchNotOfTest_143, ExternalInteraction_VerifyUnderlyingMatcherCall_143) {

    MatchNotOfMock underlyingMatcher;

    EXPECT_CALL(underlyingMatcher, match(100)).Times(1);

    

    MatchNotOf<int> matchNotOf(underlyingMatcher);

    matchNotOf.match(100);

}
