#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



using namespace Catch::Matchers;

using namespace Detail;



// Mock class for MatcherGenericBase to verify interactions

class MockMatcherGenericBase : public MatcherGenericBase {

public:

    MOCK_METHOD(std::string, describe, (), (const, override));

};



// Test fixture for MatchAllOfGeneric tests

class MatchAllOfGenericTest_158 : public ::testing::Test {

protected:

    using MatcherType = MatchAllOfGeneric<MockMatcherGenericBase>;

    std::array<const void *, 2> matchers;



    void SetUp() override {

        // Initialize matchers with mock objects

        matchers[0] = new MockMatcherGenericBase();

        matchers[1] = new MockMatcherGenericBase();

    }



    void TearDown() override {

        // Clean up allocated memory for matchers

        delete static_cast<MockMatcherGenericBase*>(matchers[0]);

        delete static_cast<MockMatcherGenericBase*>(matchers[1]);

    }

};



// Test normal operation of the constructor and describe method

TEST_F(MatchAllOfGenericTest_158, ConstructorAndDescribe_NormalOperation_158) {

    MatcherType matcher(matchers);

    EXPECT_EQ(matcher.describe(), "matches all of:");

}



// Test boundary condition with zero matchers (not applicable in this case since we need at least one matcher)

// This case is not valid as MatchAllOfGeneric requires at least one matcher



// Test boundary condition with one matcher

TEST_F(MatchAllOfGenericTest_158, ConstructorAndDescribe_OneMatcher_158) {

    std::array<const void *, 1> single_matcher = {new MockMatcherGenericBase()};

    MatcherType matcher(single_matcher);

    EXPECT_EQ(matcher.describe(), "matches all of:");

    delete static_cast<MockMatcherGenericBase*>(single_matcher[0]);

}



// Test boundary condition with multiple matchers

TEST_F(MatchAllOfGenericTest_158, ConstructorAndDescribe_MultipleMatchers_158) {

    MatcherType matcher(matchers);

    EXPECT_EQ(matcher.describe(), "matches all of:");

}



// Test exceptional or error cases (if observable through the interface)

// Since there are no observable exceptions in this interface, we skip this



// Verification of external interactions (e.g., mock handler calls and their parameters)

TEST_F(MatchAllOfGenericTest_158, Describe_CallsDescribeOnMatchers_158) {

    EXPECT_CALL(*static_cast<MockMatcherGenericBase*>(matchers[0]), describe()).WillOnce(::testing::Return("matcher1 description"));

    EXPECT_CALL(*static_cast<MockMatcherGenericBase*>(matchers[1]), describe()).WillOnce(::testing::Return("matcher2 description"));



    MatcherType matcher(matchers);

    std::string result = matcher.describe();

    EXPECT_EQ(result, "matches all of:\n  matcher1 description\n  matcher2 description");

}
