#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Catch2/matchers/catch_matchers_templated.hpp>



using namespace Catch::Matchers::Detail;



// Mock class for Matcher interface

class MockMatcher {

public:

    MOCK_METHOD(bool, match, (const void* arg), (const));

};



TEST_F(MockMatcherTest_152, MatchAllOf_AllMatch_ReturnsTrue_152) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillOnce(::testing::Return(true));



    std::array<void const*, 2> matchers = { &matcher1, &matcher2 };

    bool result = match_all_of<MockMatcher, MockMatcher>(nullptr, matchers, std::index_sequence<0, 1>{});



    EXPECT_TRUE(result);

}



TEST_F(MockMatcherTest_152, MatchAllOf_OneDoesNotMatch_ReturnsFalse_152) {

    MockMatcher matcher1;

    MockMatcher matcher2;



    EXPECT_CALL(matcher1, match(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_CALL(matcher2, match(::testing::_)).WillOnce(::testing::Return(false));



    std::array<void const*, 2> matchers = { &matcher1, &matcher2 };

    bool result = match_all_of<MockMatcher, MockMatcher>(nullptr, matchers, std::index_sequence<0, 1>{});



    EXPECT_FALSE(result);

}



TEST_F(MockMatcherTest_152, MatchAllOf_NoMatchers_ReturnsTrue_152) {

    std::array<void const*, 0> matchers = {};

    bool result = match_all_of<>(nullptr, matchers, std::index_sequence<>{});



    EXPECT_TRUE(result);

}
