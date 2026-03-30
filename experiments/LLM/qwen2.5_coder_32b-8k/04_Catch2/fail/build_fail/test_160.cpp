#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock Matcher for testing purposes

class MockMatcher {

public:

    MOCK_CONST_METHOD1(match, bool(const std::string&));

    MOCK_CONST_METHOD0(describe, std::string());

};



TEST(MatchAllOfGenericTest_160, Match_ReturnsTrueWhenAllMatchersMatch_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcher2, match(::testing::_)).WillOnce(::testing::Return(true));



    MatchAllOfGeneric<MockMatcher, MockMatcher> matcher(mockMatcher1, mockMatcher2);

    bool result = matcher.match("test");



    ASSERT_TRUE(result);

}



TEST(MatchAllOfGenericTest_160, Match_ReturnsFalseWhenAnyMatcherDoesNotMatch_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcher2, match(::testing::_)).WillOnce(::testing::Return(false));



    MatchAllOfGeneric<MockMatcher, MockMatcher> matcher(mockMatcher1, mockMatcher2);

    bool result = matcher.match("test");



    ASSERT_FALSE(result);

}



TEST(MatchAllOfGenericTest_160, Describe_ReturnsConcatenatedDescription_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, describe()).WillOnce(::testing::Return("matcher1"));

    EXPECT_CALL(mockMatcher2, describe()).WillOnce(::testing::Return("matcher2"));



    MatchAllOfGeneric<MockMatcher, MockMatcher> matcher(mockMatcher1, mockMatcher2);

    std::string description = matcher.describe();



    ASSERT_EQ(description, "matcher1 and matcher2");

}



TEST(MatchAllOfGenericTest_160, CopyConstructor_IsDeleted_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    MatchAllOfGeneric<MockMatcher, MockMatcher> original(mockMatcher1, mockMatcher2);



    static_assert(!std::is_copy_constructible_v<decltype(original)>, "Copy constructor should be deleted");

}



TEST(MatchAllOfGenericTest_160, MoveConstructor_IsDefaulted_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    MatchAllOfGeneric<MockMatcher, MockMatcher> original(mockMatcher1, mockMatcher2);

    MatchAllOfGeneric<MockMatcher, MockMatcher> moved = std::move(original);



    // No specific assertions needed here as the move constructor is defaulted

}



TEST(MatchAllOfGenericTest_160, CopyAssignment_IsDeleted_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    MatchAllOfGeneric<MockMatcher, MockMatcher> original(mockMatcher1, mockMatcher2);



    static_assert(!std::is_copy_assignable_v<decltype(original)>, "Copy assignment should be deleted");

}



TEST(MatchAllOfGenericTest_160, MoveAssignment_IsDefaulted_160) {

    MockMatcher mockMatcher1, mockMatcher2;

    MatchAllOfGeneric<MockMatcher, MockMatcher> original(mockMatcher1, mockMatcher2);

    MatchAllOfGeneric<MockMatcher, MockMatcher> moved;

    moved = std::move(original);



    // No specific assertions needed here as the move assignment is defaulted

}
