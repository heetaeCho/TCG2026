#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock MatcherBase for testing purposes

class MockMatcher : public MatcherBase<int> {

public:

    MOCK_CONST_METHOD1(match, bool(int const&));

    MOCK_CONST_METHOD0(describe, std::string());

};



class MatchAllOfTest_137 : public ::testing::Test {

protected:

    MatchAllOf<int> match_all_of;

};



TEST_F(MatchAllOfTest_137, NoMatchers_ReturnsTrue_137) {

    EXPECT_TRUE(match_all_of.match(42));

}



TEST_F(MatchAllOfTest_137, SingleMatcher_Matches_ReturnsTrue_137) {

    MockMatcher matcher;

    EXPECT_CALL(matcher, match(::testing::_)).WillOnce(::testing::Return(true));



    match_all_of.m_matchers.push_back(&matcher);

    EXPECT_TRUE(match_all_of.match(42));

}



TEST_F(MatchAllOfTest_137, SingleMatcher_DoesNotMatch_ReturnsFalse_137) {

    MockMatcher matcher;

    EXPECT_CALL(matcher, match(::testing::_)).WillOnce(::testing::Return(false));



    match_all_of.m_matchers.push_back(&matcher);

    EXPECT_FALSE(match_all_of.match(42));

}



TEST_F(MatchAllOfTest_137, MultipleMatchers_AllMatch_ReturnsTrue_137) {

    MockMatcher matcher1, matcher2;

    EXPECT_CALL(matcher1, match(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillOnce(::testing::Return(true));



    match_all_of.m_matchers.push_back(&matcher1);

    match_all_of.m_matchers.push_back(&matcher2);

    EXPECT_TRUE(match_all_of.match(42));

}



TEST_F(MatchAllOfTest_137, MultipleMatchers_OneDoesNotMatch_ReturnsFalse_137) {

    MockMatcher matcher1, matcher2;

    EXPECT_CALL(matcher1, match(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillOnce(::testing::Return(false));



    match_all_of.m_matchers.push_back(&matcher1);

    match_all_of.m_matchers.push_back(&matcher2);

    EXPECT_FALSE(match_all_of.match(42));

}



TEST_F(MatchAllOfTest_137, Describe_NoMatchers_ReturnsEmptyString_137) {

    EXPECT_EQ(match_all_of.describe(), "");

}



TEST_F(MatchAllOfTest_137, Describe_SingleMatcher_ReturnsDescription_137) {

    MockMatcher matcher;

    EXPECT_CALL(matcher, describe()).WillOnce(::testing::Return("description"));



    match_all_of.m_matchers.push_back(&matcher);

    EXPECT_EQ(match_all_of.describe(), "description");

}



TEST_F(MatchAllOfTest_137, Describe_MultipleMatchers_ReturnsCombinedDescription_137) {

    MockMatcher matcher1, matcher2;

    EXPECT_CALL(matcher1, describe()).WillOnce(::testing::Return("description1"));

    EXPECT_CALL(matcher2, describe()).WillOnce(::testing::Return("description2"));



    match_all_of.m_matchers.push_back(&matcher1);

    match_all_of.m_matchers.push_back(&matcher2);

    EXPECT_EQ(match_all_of.describe(), "description1 and description2");

}
