#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



// Mock MatcherBase for testing purposes

class MockMatcher : public MatcherBase<int> {

public:

    MOCK_METHOD(bool, match, (int const& arg), (const, override));

    MOCK_METHOD(std::string, describe, (), (const, override));

};



TEST_F(MatchAllOfTest_135, EmptyMatchersMatchAlwaysTrue_135) {

    MatchAllOf<int> matchAll;

    EXPECT_TRUE(matchAll.match(42));

}



TEST_F(MatchAllOfTest_135, SingleMatcherMatchReturnsTrue_135) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(true));



    MatchAllOf<int> matchAll;

    matchAll.m_matchers.push_back(&mockMatcher);

    

    EXPECT_TRUE(matchAll.match(42));

}



TEST_F(MatchAllOfTest_135, SingleMatcherMatchReturnsFalse_135) {

    MockMatcher mockMatcher;

    EXPECT_CALL(mockMatcher, match(42)).WillOnce(::testing::Return(false));



    MatchAllOf<int> matchAll;

    matchAll.m_matchers.push_back(&mockMatcher);

    

    EXPECT_FALSE(matchAll.match(42));

}



TEST_F(MatchAllOfTest_135, MultipleMatchersAllMatchReturnsTrue_135) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(::testing::Return(true));



    MatchAllOf<int> matchAll;

    matchAll.m_matchers.push_back(&mockMatcher1);

    matchAll.m_matchers.push_back(&mockMatcher2);



    EXPECT_TRUE(matchAll.match(42));

}



TEST_F(MatchAllOfTest_135, MultipleMatchersOneDoesNotMatchReturnsFalse_135) {

    MockMatcher mockMatcher1, mockMatcher2;

    EXPECT_CALL(mockMatcher1, match(42)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcher2, match(42)).WillOnce(::testing::Return(false));



    MatchAllOf<int> matchAll;

    matchAll.m_matchers.push_back(&mockMatcher1);

    matchAll.m_matchers.push_back(&mockMatcher2);



    EXPECT_FALSE(matchAll.match(42));

}
