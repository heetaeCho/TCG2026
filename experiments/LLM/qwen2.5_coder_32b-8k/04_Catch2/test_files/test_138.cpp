#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock MatcherBase for testing MatchAllOf

class MockMatcher : public MatcherBase<int> {

public:

    MOCK_METHOD(bool, match, (int const& arg), (const, override));

    MOCK_METHOD(std::string, describe, (), (const, override));

};



class MatchAllOfTest_138 : public ::testing::Test {

protected:

    void SetUp() override {

        matcher1 = std::make_shared<MockMatcher>();

        matcher2 = std::make_shared<MockMatcher>();



        EXPECT_CALL(*matcher1, match(::testing::_)).WillRepeatedly(testing::Return(true));

        EXPECT_CALL(*matcher2, match(::testing::_)).WillRepeatedly(testing::Return(true));



        EXPECT_CALL(*matcher1, describe()).WillOnce(testing::Return("matcher1"));

        EXPECT_CALL(*matcher2, describe()).WillOnce(testing::Return("matcher2"));



        matchAllOf = MatchAllOf<int>();

    }



    std::shared_ptr<MockMatcher> matcher1;

    std::shared_ptr<MockMatcher> matcher2;

    MatchAllOf<int> matchAllOf;

};



// Normal operation

TEST_F(MatchAllOfTest_138, SingleMatcherMatch_138) {

    matchAllOf.m_matchers.push_back(matcher1.get());

    EXPECT_TRUE(matchAllOf.match(42));

}



TEST_F(MatchAllOfTest_138, MultipleMatchersMatch_138) {

    matchAllOf.m_matchers.push_back(matcher1.get());

    matchAllOf.m_matchers.push_back(matcher2.get());

    EXPECT_TRUE(matchAllOf.match(42));

}



// Boundary conditions

TEST_F(MatchAllOfTest_138, NoMatchersMatch_138) {

    EXPECT_TRUE(matchAllOf.match(42)); // Empty MatchAllOf should match anything

}



// Exceptional or error cases

TEST_F(MatchAllOfTest_138, SingleMatcherDoesNotMatch_138) {

    ON_CALL(*matcher1, match(::testing::_)).WillByDefault(testing::Return(false));

    matchAllOf.m_matchers.push_back(matcher1.get());

    EXPECT_FALSE(matchAllOf.match(42));

}



TEST_F(MatchAllOfTest_138, MultipleMatchersOneDoesNotMatch_138) {

    ON_CALL(*matcher1, match(::testing::_)).WillByDefault(testing::Return(true));

    ON_CALL(*matcher2, match(::testing::_)).WillByDefault(testing::Return(false));

    matchAllOf.m_matchers.push_back(matcher1.get());

    matchAllOf.m_matchers.push_back(matcher2.get());

    EXPECT_FALSE(matchAllOf.match(42));

}



// Verification of external interactions

TEST_F(MatchAllOfTest_138, SingleMatcherInteraction_138) {

    matchAllOf.m_matchers.push_back(matcher1.get());

    matchAllOf.match(42);

    ::testing::Mock::VerifyAndClearExpectations(matcher1.get());

}



TEST_F(MatchAllOfTest_138, MultipleMatchersInteractions_138) {

    matchAllOf.m_matchers.push_back(matcher1.get());

    matchAllOf.m_matchers.push_back(matcher2.get());

    matchAllOf.match(42);

    ::testing::Mock::VerifyAndClearExpectations(matcher1.get());

    ::testing::Mock::VerifyAndClearExpectations(matcher2.get());

}



TEST_F(MatchAllOfTest_138, DescribeWithNoMatchers_138) {

    EXPECT_EQ(matchAllOf.describe(), "");

}



TEST_F(MatchAllOfTest_138, DescribeWithOneMatcher_138) {

    matchAllOf.m_matchers.push_back(matcher1.get());

    EXPECT_EQ(matchAllOf.describe(), "matcher1");

}



TEST_F(MatchAllOfTest_138, DescribeWithMultipleMatchers_138) {

    matchAllOf.m_matchers.push_back(matcher1.get());

    matchAllOf.m_matchers.push_back(matcher2.get());

    EXPECT_EQ(matchAllOf.describe(), "(matcher1 && matcher2)");

}
