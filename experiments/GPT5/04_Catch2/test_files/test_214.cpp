// predicate_matcher_tests_214.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_predicate.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

using Catch::Matchers::PredicateMatcher;

// A mockable predicate functor to verify external interaction (argument & call count).
struct MockPredicate {
  MOCK_METHOD(bool, Call, (int v), (const));
  bool operator()(int v) const { return Call(v); }
};

// --- Normal operation ---

TEST(PredicateMatcherTest_214, Match_ReturnsTrueWhenPredicateIsSatisfied_214) {
  auto is_even = [](int v) { return v % 2 == 0; };
  PredicateMatcher<int, decltype(is_even)> matcher(is_even, "is even");

  EXPECT_TRUE(matcher.match(2));
  EXPECT_TRUE(matcher.match(0));  // also even
}

TEST(PredicateMatcherTest_214, Match_ReturnsFalseWhenPredicateIsNotSatisfied_214) {
  auto is_positive = [](int v) { return v > 0; };
  PredicateMatcher<int, decltype(is_positive)> matcher(is_positive, "is positive");

  EXPECT_FALSE(matcher.match(0));
  EXPECT_FALSE(matcher.match(-1));
}

// --- Boundary-ish values (as observable via the predicate) ---

TEST(PredicateMatcherTest_214, Match_HandlesBoundaryValuesFromPredicatePerspective_214) {
  auto ge_zero = [](int v) { return v >= 0; };
  PredicateMatcher<int, decltype(ge_zero)> matcher(ge_zero, ">= 0");

  EXPECT_TRUE(matcher.match(0));   // boundary
  EXPECT_FALSE(matcher.match(-1)); // just below boundary
}

// --- Description behavior ---

TEST(PredicateMatcherTest_214, Describe_ReturnsProvidedDescription_214) {
  auto any = [](int) { return true; };
  const std::string description = "custom description";
  PredicateMatcher<int, decltype(any)> matcher(any, description);

  // Observable contract: describe() returns the description string
  EXPECT_EQ(matcher.describe(), description);
}

TEST(PredicateMatcherTest_214, Describe_AllowsEmptyDescription_214) {
  auto any = [](int) { return true; };
  PredicateMatcher<int, decltype(any)> matcher(any, "");

  EXPECT_EQ(matcher.describe(), "");
}

// --- Verification of external interactions (predicate invocation) ---

TEST(PredicateMatcherTest_214, Match_InvokesProvidedPredicateWithItem_214) {
  StrictMock<MockPredicate> mock_pred;
  PredicateMatcher<int, MockPredicate> matcher(mock_pred, "mocked predicate");

  // Verify argument forwarding and single invocation
  EXPECT_CALL(mock_pred, Call(42)).WillOnce(Return(true));
  EXPECT_TRUE(matcher.match(42));
}

}  // namespace
