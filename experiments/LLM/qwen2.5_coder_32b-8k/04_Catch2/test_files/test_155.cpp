#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <catch2/matchers/catch_matchers_templated.hpp>



using namespace Catch::Matchers::Detail;



// Mock Matchers for testing

class MockMatcher {

public:

    MOCK_METHOD(std::string, toString, (), (const));

};



TEST_F(CatchTemplateMatchTest_155, SingleMatcherDescription_155) {

    MockMatcher matcher;

    EXPECT_CALL(matcher, toString()).WillOnce(::testing::Return("MockMatcherDescription"));



    std::array<void const*, 1> matchers = { &matcher };

    std::string result = describe_multi_matcher<MockMatcher>("combine", matchers, std::index_sequence_for<MockMatcher>{});

    

    EXPECT_EQ(result, "combine(MockMatcherDescription)");

}



TEST_F(CatchTemplateMatchTest_155, MultipleMatchersDescription_155) {

    MockMatcher matcher1;

    MockMatcher matcher2;

    EXPECT_CALL(matcher1, toString()).WillOnce(::testing::Return("MockMatcherDescription1"));

    EXPECT_CALL(matcher2, toString()).WillOnce(::testing::Return("MockMatcherDescription2"));



    std::array<void const*, 2> matchers = { &matcher1, &matcher2 };

    std::string result = describe_multi_matcher<MockMatcher, MockMatcher>("combine", matchers, std::index_sequence_for<MockMatcher, MockMatcher>{});

    

    EXPECT_EQ(result, "combine(MockMatcherDescription1, MockMatcherDescription2)");

}



TEST_F(CatchTemplateMatchTest_155, EmptyMatchersDescription_155) {

    std::array<void const*, 0> matchers = {};

    std::string result = describe_multi_matcher<>("combine", matchers, std::index_sequence<>{});

    

    EXPECT_EQ(result, "combine()");

}
