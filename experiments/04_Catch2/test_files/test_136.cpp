#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MockMatcherBase : public MatcherBase<int> {

public:

    MOCK_METHOD(bool, match, (const int& arg), (const, override));

};



TEST_F(MatchAllOfTest_136, DefaultConstructorInitializesEmptyVector_136) {

    MatchAllOf<int> match_all_of;

    EXPECT_EQ(match_all_of.describe(), "()"); // Assuming describe returns "()" for an empty vector

}



TEST_F(MatchAllOfTest_136, DeletedCopyConstructorDoesNotCompile_136) {

    static_assert(!std::is_copy_constructible<MatchAllOf<int>>::value, "Copy constructor should be deleted");

}



TEST_F(MatchAllOfTest_136, MoveConstructorWorksCorrectly_136) {

    MatchAllOf<int> match_all_of;

    MockMatcherBase mock_matcher1;

    match_all_of.m_matchers.push_back(&mock_matcher1);

    

    MatchAllOf<int> moved_match_all_of(std::move(match_all_of));

    EXPECT_EQ(moved_match_all_of.describe(), "(  )"); // Assuming describe returns "()"

}



TEST_F(MatchAllOfTest_136, DeletedCopyAssignmentOperatorDoesNotCompile_136) {

    static_assert(!std::is_copy_assignable<MatchAllOf<int>>::value, "Copy assignment operator should be deleted");

}



TEST_F(MatchAllOfTest_136, MoveAssignmentOperatorWorksCorrectly_136) {

    MatchAllOf<int> match_all_of;

    MockMatcherBase mock_matcher1;

    match_all_of.m_matchers.push_back(&mock_matcher1);

    

    MatchAllOf<int> another_match_all_of;

    another_match_all_of = std::move(match_all_of);

    EXPECT_EQ(another_match_all_of.describe(), "(  )"); // Assuming describe returns "()"

}



TEST_F(MatchAllOfTest_136, DescribeReturnsCorrectStringForOneMatcher_136) {

    MatchAllOf<int> match_all_of;

    MockMatcherBase mock_matcher1;

    EXPECT_CALL(mock_matcher1, toString()).WillOnce(testing::Return("matcher1"));

    

    match_all_of.m_matchers.push_back(&mock_matcher1);

    EXPECT_EQ(match_all_of.describe(), "( matcher1 )");

}



TEST_F(MatchAllOfTest_136, DescribeReturnsCorrectStringForMultipleMatchers_136) {

    MatchAllOf<int> match_all_of;

    MockMatcherBase mock_matcher1;

    MockMatcherBase mock_matcher2;

    EXPECT_CALL(mock_matcher1, toString()).WillOnce(testing::Return("matcher1"));

    EXPECT_CALL(mock_matcher2, toString()).WillOnce(testing::Return("matcher2"));

    

    match_all_of.m_matchers.push_back(&mock_matcher1);

    match_all_of.m_matchers.push_back(&mock_matcher2);

    EXPECT_EQ(match_all_of.describe(), "( matcher1 and matcher2 )");

}
