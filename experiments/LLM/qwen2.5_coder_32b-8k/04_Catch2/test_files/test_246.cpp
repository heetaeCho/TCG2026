#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;



class MatcherUntypedBaseTest : public ::testing::Test {

protected:

    MatcherUntypedBase matcher;

};



TEST_F(MatcherUntypedBaseTest_246, ToStringReturnsDescriptionOnce_246) {

    EXPECT_EQ(matcher.toString(), matcher.describe());

}



TEST_F(MatcherUntypedBaseTest_246, ToStringCachesResult_246) {

    const std::string firstCall = matcher.toString();

    const std::string secondCall = matcher.toString();

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(MatcherUntypedBaseTest_246, DescribeCalledOncePerInstance_246) {

    class MockMatcher : public MatcherUntypedBase {

    public:

        MOCK_METHOD(const std::string, describe, (), (override, protected));

    };



    NiceMock<MockMatcher> mockMatcher;

    EXPECT_CALL(mockMatcher, describe()).Times(1);

    mockMatcher.toString();

}
