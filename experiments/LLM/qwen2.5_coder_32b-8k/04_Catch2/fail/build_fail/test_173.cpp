#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace ::testing;



// Since the provided code snippet is a template operator overload and not a class,

// we will create a mock scenario where this operator might be used.

// We'll assume some generic use case for testing.



// Mock classes to simulate external collaborators

template<typename T>

class MockMatcher : public MatcherBase<T> {

public:

    MOCK_CONST_METHOD1(match, bool(T const&));

};



TEST(AndOperatorTest_173, BothMatchersReturnTrue_173) {

    MockMatcher<int> mockMatcher1;

    MockMatcher<int> mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(_)).WillOnce(Return(true));

    EXPECT_CALL(mockMatcher2, match(_)).WillOnce(Return(true));



    auto combinedMatcher = mockMatcher1 && mockMatcher2;



    EXPECT_TRUE(combinedMatcher.match(42));

}



TEST(AndOperatorTest_173, FirstMatcherReturnsFalse_173) {

    MockMatcher<int> mockMatcher1;

    MockMatcher<int> mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(_)).WillOnce(Return(false));

    EXPECT_CALL(mockMatcher2, match(_)).Times(0); // Should not be called



    auto combinedMatcher = mockMatcher1 && mockMatcher2;



    EXPECT_FALSE(combinedMatcher.match(42));

}



TEST(AndOperatorTest_173, SecondMatcherReturnsFalse_173) {

    MockMatcher<int> mockMatcher1;

    MockMatcher<int> mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(_)).WillOnce(Return(true));

    EXPECT_CALL(mockMatcher2, match(_)).WillOnce(Return(false));



    auto combinedMatcher = mockMatcher1 && mockMatcher2;



    EXPECT_FALSE(combinedMatcher.match(42));

}



TEST(AndOperatorTest_173, BothMatchersReturnFalse_173) {

    MockMatcher<int> mockMatcher1;

    MockMatcher<int> mockMatcher2;



    EXPECT_CALL(mockMatcher1, match(_)).WillOnce(Return(false));

    EXPECT_CALL(mockMatcher2, match(_)).Times(0); // Should not be called



    auto combinedMatcher = mockMatcher1 && mockMatcher2;



    EXPECT_FALSE(combinedMatcher.match(42));

}
