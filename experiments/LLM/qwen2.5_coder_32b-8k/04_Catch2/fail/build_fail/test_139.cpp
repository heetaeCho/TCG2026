#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers.hpp"

#include <vector>



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock MatcherBase for testing MatchAnyOf

class MockMatcher : public MatcherBase<int> {

public:

    MOCK_METHOD1(match, bool(int const& arg)) override;

    MOCK_METHOD0(describe, std::string() const) override;

};



TEST_F(MatchAnyOfTest_139, EmptyMatchersAlwaysFails_139) {

    MatchAnyOf<int> match_any_of;

    EXPECT_FALSE(match_any_of.match(42));

}



TEST_F(MatchAnyOfTest_139, SingleMatcherSuccess_139) {

    MockMatcher mock_matcher;

    EXPECT_CALL(mock_matcher, match(42)).WillOnce(testing::Return(true));



    MatchAnyOf<int> match_any_of;

    match_any_of.m_matchers.push_back(&mock_matcher);



    EXPECT_TRUE(match_any_of.match(42));

}



TEST_F(MatchAnyOfTest_139, SingleMatcherFailure_139) {

    MockMatcher mock_matcher;

    EXPECT_CALL(mock_matcher, match(42)).WillOnce(testing::Return(false));



    MatchAnyOf<int> match_any_of;

    match_any_of.m_matchers.push_back(&mock_matcher);



    EXPECT_FALSE(match_any_of.match(42));

}



TEST_F(MatchAnyOfTest_139, MultipleMatchersFirstSuccess_139) {

    MockMatcher mock_matcher1, mock_matcher2;

    EXPECT_CALL(mock_matcher1, match(42)).WillOnce(testing::Return(true));

    EXPECT_CALL(mock_matcher2, match(42)).Times(0);



    MatchAnyOf<int> match_any_of;

    match_any_of.m_matchers.push_back(&mock_matcher1);

    match_any_of.m_matchers.push_back(&mock_matcher2);



    EXPECT_TRUE(match_any_of.match(42));

}



TEST_F(MatchAnyOfTest_139, MultipleMatchersLastSuccess_139) {

    MockMatcher mock_matcher1, mock_matcher2;

    EXPECT_CALL(mock_matcher1, match(42)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_matcher2, match(42)).WillOnce(testing::Return(true));



    MatchAnyOf<int> match_any_of;

    match_any_of.m_matchers.push_back(&mock_matcher1);

    match_any_of.m_matchers.push_back(&mock_matcher2);



    EXPECT_TRUE(match_any_of.match(42));

}



TEST_F(MatchAnyOfTest_139, MultipleMatchersAllFail_139) {

    MockMatcher mock_matcher1, mock_matcher2;

    EXPECT_CALL(mock_matcher1, match(42)).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_matcher2, match(42)).WillOnce(testing::Return(false));



    MatchAnyOf<int> match_any_of;

    match_any_of.m_matchers.push_back(&mock_matcher1);

    match_any_of.m_matchers.push_back(&mock_matcher2);



    EXPECT_FALSE(match_any_of.match(42));

}
