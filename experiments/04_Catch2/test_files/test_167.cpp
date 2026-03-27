#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers::Detail;



class MockMatcher {

public:

    MOCK_METHOD(std::string, toString, (), (const));

    MOCK_METHOD(bool, match, (int), (const));

};



TEST_F(MockMatcherTest_167, DefaultConstructorDeleted_167) {

    // This test is more of a conceptual one since the default constructor

    // being deleted cannot be directly tested without trying to instantiate it.

}



TEST_F(MockMatcherTest_167, CopyConstructorDeleted_167) {

    MockMatcher matcher;

    EXPECT_FALSE((std::is_copy_constructible<MatchNotOfGeneric<MockMatcher>>::value));

}



TEST_F(MockMatcherTest_167, MoveConstructorAvailable_167) {

    MockMatcher matcher;

    MatchNotOfGeneric<MockMatcher> movedMatcher(std::move(matcher));

}



TEST_F(MockMatcherTest_167, CopyAssignmentDeleted_167) {

    MatchNotOfGeneric<MockMatcher> matcher(MockMatcher());

    EXPECT_FALSE((std::is_copy_assignable<MatchNotOfGeneric<MockMatcher>>::value));

}



TEST_F(MockMatcherTest_167, MoveAssignmentAvailable_167) {

    MatchNotOfGeneric<MockMatcher> matcher(MockMatcher());

    MatchNotOfGeneric<MockMatcher> movedMatcher = std::move(matcher);

}



TEST_F(MockMatcherTest_167, DescribeReturnsExpectedString_167) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, toString()).WillOnce(::testing::Return("some description"));

    MatchNotOfGeneric<MockMatcher> notMatcher(mockMatcher);



    EXPECT_EQ(notMatcher.describe(), "not some description");

}



TEST_F(MockMatcherTest_167, MatchDelegatesToProvidedMatcher_167) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(true));

    MatchNotOfGeneric<MockMatcher> notMatcher(mockMatcher);



    EXPECT_FALSE(notMatcher.match(42));

}



TEST_F(MockMatcherTest_167, MatchDelegatesToProvidedMatcherFalseCase_167) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(false));

    MatchNotOfGeneric<MockMatcher> notMatcher(mockMatcher);



    EXPECT_TRUE(notMatcher.match(42));

}
