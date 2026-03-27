#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers::Detail;



// Mock Matcher for testing purposes

class MockMatcher {

public:

    MOCK_METHOD1(match, bool(int));

    MOCK_CONST_METHOD0(describe, std::string());

};



TEST_F(Catch2_MatchAnyOfGenericTest_164, MatchWithSingleMatcher_164) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(5)).WillOnce(testing::Return(true));



    MatchAnyOfGeneric<MockMatcher> matcher(mockMatcher);

    ASSERT_TRUE(matcher.match(5));

}



TEST_F(Catch2_MatchAnyOfGenericTest_164, MatchWithMultipleMatchers_Success_164) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(5)).WillOnce(testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(5)).WillOnce(testing::Return(true));



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matcher(mockMatcher1, mockMatcher2);

    ASSERT_TRUE(matcher.match(5));

}



TEST_F(Catch2_MatchAnyOfGenericTest_164, MatchWithMultipleMatchers_Failure_164) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(5)).WillOnce(testing::Return(false));

    EXPECT_CALL(mockMatcher2, match(5)).WillOnce(testing::Return(false));



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matcher(mockMatcher1, mockMatcher2);

    ASSERT_FALSE(matcher.match(5));

}



TEST_F(Catch2_MatchAnyOfGenericTest_164, Describe_ReturnsConcatenatedDescriptions_164) {

    MockMatcher mockMatcher1;

    MockMatcher mockMatcher2;



    EXPECT_CALL(mockMatcher1, describe()).WillOnce(testing::Return("Matcher1"));

    EXPECT_CALL(mockMatcher2, describe()).WillOnce(testing::Return("Matcher2"));



    MatchAnyOfGeneric<MockMatcher, MockMatcher> matcher(mockMatcher1, mockMatcher2);

    ASSERT_EQ(matcher.describe(), "Matcher1 or Matcher2");

}



TEST_F(Catch2_MatchAnyOfGenericTest_164, MoveConstructor_TransfersState_164) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(5)).WillOnce(testing::Return(true));



    MatchAnyOfGeneric<MockMatcher> matcher(mockMatcher);

    auto movedMatcher = std::move(matcher);



    ASSERT_TRUE(movedMatcher.match(5));

}



TEST_F(Catch2_MatchAnyOfGenericTest_164, DeletedCopyConstructor_164) {

    MockMatcher mockMatcher;

    MatchAnyOfGeneric<MockMatcher> matcher(mockMatcher);



    // The copy constructor is deleted, so this will cause a compile-time error if uncommented.

    // MatchAnyOfGeneric<MockMatcher> copiedMatcher = matcher;

}



TEST_F(Catch2_MatchAnyOfGenericTest_164, DeletedCopyAssignmentOperator_164) {

    MockMatcher mockMatcher;

    MatchAnyOfGeneric<MockMatcher> matcher(mockMatcher);

    MatchAnyOfGeneric<MockMatcher> otherMatcher(mockMatcher);



    // The copy assignment operator is deleted, so this will cause a compile-time error if uncommented.

    // otherMatcher = matcher;

}
