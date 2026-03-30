#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if any were present



// Since the provided code snippet is a template function and not a class,

// we will create mock tests based on hypothetical usage of such a matcher.

// Let's assume there's a function that uses this matcher to test some behavior.



// Hypothetical function using the matcher

bool checkConditionWithMatcher(int value, const Catch::Matchers::MatcherBase<int>& matcher) {

    return matcher.match(value);

}



// Mock class to simulate the usage of the matcher

class MatcherUser {

public:

    virtual bool useMatcher(int value, const Catch::Matchers::MatcherBase<int>& matcher) = 0;

};



// Concrete implementation of MatcherUser for testing

class ConcreteMatcherUser : public MatcherUser {

public:

    bool useMatcher(int value, const Catch::Matchers::MatcherBase<int>& matcher) override {

        return checkConditionWithMatcher(value, matcher);

    }

};



// Mock class to simulate the behavior of a matcher

class MockMatcher : public Catch::Matchers::MatcherBase<int> {

public:

    MOCK_METHOD(bool, match, (int), (const, override));

    MOCK_METHOD(std::string, describe, (), (const, override));

};



TEST_F(MatcherUserTest_171, MatcherReturnsTrueForMatchingValue_171) {

    MockMatcher mockMatcher;

    ConcreteMatcherUser matcherUser;



    EXPECT_CALL(mockMatcher, match(5)).WillOnce(::testing::Return(true));



    bool result = matcherUser.useMatcher(5, mockMatcher);

    EXPECT_TRUE(result);

}



TEST_F(MatcherUserTest_171, MatcherReturnsFalseForNonMatchingValue_171) {

    MockMatcher mockMatcher;

    ConcreteMatcherUser matcherUser;



    EXPECT_CALL(mockMatcher, match(10)).WillOnce(::testing::Return(false));



    bool result = matcherUser.useMatcher(10, mockMatcher);

    EXPECT_FALSE(result);

}



TEST_F(MatcherUserTest_171, MatcherDescribeCalledOnce_171) {

    MockMatcher mockMatcher;

    ConcreteMatcherUser matcherUser;



    EXPECT_CALL(mockMatcher, match(5)).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockMatcher, describe()).Times(1);



    bool result = matcherUser.useMatcher(5, mockMatcher);

    EXPECT_TRUE(result);

}
