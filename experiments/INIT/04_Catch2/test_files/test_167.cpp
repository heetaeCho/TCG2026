// File: tests/match_not_of_generic_describe_167_tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

// Under test:
#include "catch2/matchers/catch_matchers_templated.hpp"

using ::testing::Return;
using ::testing::Exactly;

namespace {

struct MockMatcher {
    // The collaborator API that MatchNotOfGeneric is expected to use.
    MOCK_METHOD(std::string, toString, (), (const));
};

using Catch::Matchers::Detail::MatchNotOfGeneric;

class MatchNotOfGenericTest_167 : public ::testing::Test {};

} // namespace

// [Normal] Basic description prefixes "not " to underlying matcher string.
TEST_F(MatchNotOfGenericTest_167, Describe_PrefixesWithNotAndSpace_167) {
    MockMatcher mock;
    EXPECT_CALL(mock, toString()).Times(Exactly(1)).WillOnce(Return("is-even"));

    MatchNotOfGeneric<MockMatcher> notMatcher{mock};
    const std::string desc = notMatcher.describe();

    EXPECT_EQ(desc, "not is-even");
}

// [Boundary] Underlying matcher describes as empty => result should be "not ".
TEST_F(MatchNotOfGenericTest_167, Describe_EmptyUnderlyingString_167) {
    MockMatcher mock;
    EXPECT_CALL(mock, toString()).Times(Exactly(1)).WillOnce(Return(""));

    MatchNotOfGeneric<MockMatcher> notMatcher{mock};
    EXPECT_EQ(notMatcher.describe(), "not ");
}

// [Normal/Special chars] Ensure special characters are preserved verbatim.
TEST_F(MatchNotOfGenericTest_167, Describe_PreservesSpecialCharacters_167) {
    MockMatcher mock;
    EXPECT_CALL(mock, toString()).Times(Exactly(1))
        .WillOnce(Return("x && y || z==42"));

    MatchNotOfGeneric<MockMatcher> notMatcher{mock};
    EXPECT_EQ(notMatcher.describe(), "not x && y || z==42");
}

// [Const-correctness + interaction] Calling describe() on a const object still delegates once.
TEST_F(MatchNotOfGenericTest_167, Describe_OnConstObject_DelegatesOnce_167) {
    MockMatcher mock;
    EXPECT_CALL(mock, toString()).Times(Exactly(1)).WillOnce(Return("ready"));

    const MatchNotOfGeneric<MockMatcher> notMatcher{mock};
    EXPECT_EQ(notMatcher.describe(), "not ready");
}
