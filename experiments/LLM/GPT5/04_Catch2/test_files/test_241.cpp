// File: exception_message_matches_matcher_test_241.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the class under test
#include "Catch2/src/catch2/matchers/catch_matchers_exception.hpp"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

/// A mock for the external collaborator StringMatcherType.
/// We only rely on its public describe() method being called by the SUT.
class MockStringMatcher {
public:
  MOCK_METHOD(std::string, describe, (), (const));
};

using Catch::Matchers::ExceptionMessageMatchesMatcher;

} // namespace

// Verifies that describe() prefixes with ` matches "` and appends a trailing quote,
// and that it delegates to the inner matcher exactly once.
TEST(ExceptionMessageMatchesMatcherTest_241, DescribeUsesInnerMatcher_241) {
  StrictMock<MockStringMatcher> inner;
  EXPECT_CALL(inner, describe()).WillOnce(Return("foo"));

  ExceptionMessageMatchesMatcher<MockStringMatcher> sut(std::move(inner));
  EXPECT_EQ(R"( matches "foo")", sut.describe());
}

// Verifies boundary condition: inner matcher returns empty string.
TEST(ExceptionMessageMatchesMatcherTest_241, DescribeWithEmptyInnerDescription_241) {
  StrictMock<MockStringMatcher> inner;
  EXPECT_CALL(inner, describe()).WillOnce(Return(""));

  ExceptionMessageMatchesMatcher<MockStringMatcher> sut(std::move(inner));
  EXPECT_EQ(R"( matches "")", sut.describe());
}

// Verifies special characters are passed through verbatim from the inner matcher.
// This includes quotes and newlines; the SUT should not alter/escape them,
// only surround with leading ` matches "` and a trailing `"`.
TEST(ExceptionMessageMatchesMatcherTest_241, DescribePreservesSpecialCharacters_241) {
  const std::string special = "a\"b\nc\t\\end";
  StrictMock<MockStringMatcher> inner;
  EXPECT_CALL(inner, describe()).WillOnce(Return(special));

  ExceptionMessageMatchesMatcher<MockStringMatcher> sut(std::move(inner));
  EXPECT_EQ(std::string(" matches \"") + special + "\"", sut.describe());
}
