// File: predicate_matcher_test_213.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_predicate.hpp"

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::Exactly;

// ----------------- Helpers (external collaborators) -----------------

// A mockable predicate interface we can wrap into a functor.
struct MockPredicate213 {
  MOCK_METHOD(bool, Call, (int), (const));
};

// A functor that delegates to the mock predicate via shared_ptr.
// This ensures the copy made by PredicateMatcher calls into the same mock.
struct WrappingFunctor213 {
  std::shared_ptr<MockPredicate213> mock;
  bool operator()(int v) const { return mock->Call(v); }
};

// A move-only predicate to validate rvalue/move construction works.
struct MoveOnlyPredicate213 {
  std::unique_ptr<int> target;
  explicit MoveOnlyPredicate213(int t) : target(new int(t)) {}
  MoveOnlyPredicate213(MoveOnlyPredicate213&&) = default;
  MoveOnlyPredicate213& operator=(MoveOnlyPredicate213&&) = default;
  MoveOnlyPredicate213(const MoveOnlyPredicate213&) = delete;
  MoveOnlyPredicate213& operator=(const MoveOnlyPredicate213&) = delete;

  bool operator()(int v) const { return v == *target; }
};

// A throwing predicate to verify exception propagation through match().
struct ThrowingPredicate213 {
  bool operator()(int) const { throw std::runtime_error("boom"); }
};

// ----------------- Tests -----------------

// Suite name includes TEST_ID as requested.
class PredicateMatcherTest_213 : public ::testing::Test {};

// [Normal] match returns true when predicate returns true.
TEST_F(PredicateMatcherTest_213, MatchReturnsTrueWhenPredicateTrue_213) {
  auto mock = std::make_shared<StrictMock<MockPredicate213>>();
  WrappingFunctor213 fun{mock};
  Catch::Matchers::PredicateMatcher<int, WrappingFunctor213> matcher(
      std::move(fun), "predicate is true");

  EXPECT_CALL(*mock, Call(42)).Times(Exactly(1)).WillOnce(Return(true));
  EXPECT_TRUE(matcher.match(42));
}

// [Normal] match returns false when predicate returns false.
TEST_F(PredicateMatcherTest_213, MatchReturnsFalseWhenPredicateFalse_213) {
  auto mock = std::make_shared<StrictMock<MockPredicate213>>();
  WrappingFunctor213 fun{mock};
  Catch::Matchers::PredicateMatcher<int, WrappingFunctor213> matcher(
      std::move(fun), "predicate is false");

  EXPECT_CALL(*mock, Call(-1)).Times(Exactly(1)).WillOnce(Return(false));
  EXPECT_FALSE(matcher.match(-1));
}

// [Interaction] Predicate is invoked with the exact item passed to match().
TEST_F(PredicateMatcherTest_213, MatchInvokesPredicateWithExactArgument_213) {
  auto mock = std::make_shared<StrictMock<MockPredicate213>>();
  WrappingFunctor213 fun{mock};
  Catch::Matchers::PredicateMatcher<int, WrappingFunctor213> matcher(
      std::move(fun), "called with item");

  // Verify exact forwarding of the input argument to the predicate.
  EXPECT_CALL(*mock, Call(12345)).Times(Exactly(1)).WillOnce(Return(true));
  EXPECT_TRUE(matcher.match(12345));
}

// [Boundary] Supports move-only predicates (constructed from rvalue).
TEST_F(PredicateMatcherTest_213, SupportsMoveOnlyPredicate_213) {
  Catch::Matchers::PredicateMatcher<int, MoveOnlyPredicate213> matcher(
      MoveOnlyPredicate213{7}, "equals 7");

  // Observable behavior only: check returned booleans.
  EXPECT_TRUE(matcher.match(7));
  EXPECT_FALSE(matcher.match(6));
}

// [Error/Exceptional] Exceptions from the predicate propagate out of match().
TEST_F(PredicateMatcherTest_213, MatchPropagatesExceptionsFromPredicate_213) {
  Catch::Matchers::PredicateMatcher<int, ThrowingPredicate213> matcher(
      ThrowingPredicate213{}, "throws");

  EXPECT_THROW(matcher.match(0), std::runtime_error);
}

// [Describe] The description includes (at least) the provided description text.
TEST_F(PredicateMatcherTest_213, DescribeContainsProvidedText_213) {
  const std::string provided = "is even number";
  // We do not assume formatting; we only assert the provided text appears.
  Catch::Matchers::PredicateMatcher<int, WrappingFunctor213> matcher(
      WrappingFunctor213{std::make_shared<StrictMock<MockPredicate213>>()},
      provided);

  const std::string desc = matcher.describe();
  EXPECT_NE(desc.find(provided), std::string::npos)
      << "describe() should include the provided description text";
}
