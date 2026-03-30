#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers::Detail;



// Mock Matchers for testing MatchAllOfGeneric

class MockMatcher {

public:

    MOCK_METHOD1(match, bool(const std::string& arg));

    MOCK_CONST_METHOD0(describe, std::string());

};



TEST_F(MatchAllOfGenericTest_156, ConstructWithMultipleMatchers_156) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    MatchAllOfGeneric<MockMatcher, MockMatcher> matchAll(matcher1, matcher2);

}



TEST_F(MatchAllOfGenericTest_156, MatchReturnsTrueIfAllMatch_156) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match("test")).WillOnce(::testing::Return(true));

    EXPECT_CALL(matcher2, match("test")).WillOnce(::testing::Return(true));



    MatchAllOfGeneric<MockMatcher, MockMatcher> matchAll(matcher1, matcher2);

    ASSERT_TRUE(matchAll.match("test"));

}



TEST_F(MatchAllOfGenericTest_156, MatchReturnsFalseIfOneDoesNotMatch_156) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match("test")).WillOnce(::testing::Return(true));

    EXPECT_CALL(matcher2, match("test")).WillOnce(::testing::Return(false));



    MatchAllOfGeneric<MockMatcher, MockMatcher> matchAll(matcher1, matcher2);

    ASSERT_FALSE(matchAll.match("test"));

}



TEST_F(MatchAllOfGenericTest_156, DescribeConcatenatesDescriptions_156) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, describe()).WillOnce(::testing::Return("matcher1 description"));

    EXPECT_CALL(matcher2, describe()).WillOnce(::testing::Return("matcher2 description"));



    MatchAllOfGeneric<MockMatcher, MockMatcher> matchAll(matcher1, matcher2);

    ASSERT_EQ(matchAll.describe(), "matcher1 description and matcher2 description");

}



TEST_F(MatchAllOfGenericTest_156, DeletedCopyConstructorAndAssignment_156) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    MatchAllOfGeneric<MockMatcher, MockMatcher> matchAll(matcher1, matcher2);

    static_assert(!std::is_copy_constructible_v<decltype(matchAll)>);

    static_assert(!std::is_copy_assignable_v<decltype(matchAll)>);

}



TEST_F(MatchAllOfGenericTest_156, MoveConstructorAndAssignmentAllowed_156) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    MatchAllOfGeneric<MockMatcher, MockMatcher> matchAll(matcher1, matcher2);



    // Check move construction

    MatchAllOfGeneric<MockMatcher, MockMatcher> movedMatchAll(std::move(matchAll));



    // Check move assignment

    MatchAllOfGeneric<MockMatcher, MockMatcher> anotherMatchAll(matcher1, matcher2);

    anotherMatchAll = std::move(movedMatchAll);

}
