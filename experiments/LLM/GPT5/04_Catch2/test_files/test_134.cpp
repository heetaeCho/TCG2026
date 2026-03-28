// File: make_match_expr_tests_134.cpp
//
// Unit tests for Catch::makeMatchExpr interface using GoogleTest/GoogleMock.
// We only verify observable behavior via the public interface of MatchExpr
// and a matcher passed in (mocked via Google Mock when appropriate).

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Headers from Catch2 providing the interface under test and matcher base.
// The first header contains makeMatchExpr (as given in the prompt).
#include <catch2/matchers/internal/catch_matchers_impl.hpp>
#include <catch2/matchers/catch_matchers.hpp>

using ::testing::HasSubstr;
using ::testing::Return;
using ::testing::Truly;

// ---- Helpers (external collaborators we control) ----

// Mock matcher for ints. We derive from Catch2's MatcherBase so that
// MatchExpr can interact with it purely via the public matcher interface.
struct MockIntMatcher : public Catch::Matchers::MatcherBase<int> {
  MOCK_METHOD(bool, match, (int const&), (const, override));
  MOCK_METHOD(std::string, describe, (), (const, override));
};

// Simple concrete matcher used for type-deduction and happy-path checks.
struct IsEvenMatcher : public Catch::Matchers::MatcherBase<int> {
  bool match(int const& v) const override { return (v % 2) == 0; }
  std::string describe() const override { return "is even"; }
};

// A small user-defined type to observe that the exact object is forwarded
// to the matcher (address identity), without peeking into internal state.
struct Widget {
  int id{};
  // (No streaming or equality needed for these tests.)
};

struct MockWidgetMatcher : public Catch::Matchers::MatcherBase<Widget> {
  MOCK_METHOD(bool, match, (Widget const&), (const, override));
  MOCK_METHOD(std::string, describe, (), (const, override));
};

// ---------------------- Tests ------------------------

class MakeMatchExprTest_134 : public ::testing::Test {};

// Normal operation: successful match and failed match results are exposed
// via the observable result accessor.
TEST_F(MakeMatchExprTest_134, ReturnsTrueOrFalseBasedOnMatcher_134) {
  // True case with a concrete matcher
  {
    IsEvenMatcher matcher;
    auto expr = Catch::makeMatchExpr(4, matcher);
    EXPECT_TRUE(expr.getResult());
  }

  // False case with a concrete matcher
  {
    IsEvenMatcher matcher;
    auto expr = Catch::makeMatchExpr(5, matcher);
    EXPECT_FALSE(expr.getResult());
  }

  // True and false cases but verifying interaction with a mock matcher
  {
    MockIntMatcher mtrue;
    EXPECT_CALL(mtrue, match(::testing::Eq(42))).Times(1).WillOnce(Return(true));
    EXPECT_CALL(mtrue, describe()).Times(::testing::AnyNumber());
    auto expr = Catch::makeMatchExpr(42, mtrue);
    EXPECT_TRUE(expr.getResult());
  }
  {
    MockIntMatcher mfalse;
    EXPECT_CALL(mfalse, match(::testing::Eq(-1))).Times(1).WillOnce(Return(false));
    EXPECT_CALL(mfalse, describe()).Times(::testing::AnyNumber());
    auto expr = Catch::makeMatchExpr(-1, mfalse);
    EXPECT_FALSE(expr.getResult());
  }
}

// Boundary-ish value: still only checks observable behavior (matcher receives
// the exact value provided).
TEST_F(MakeMatchExprTest_134, PassesBoundaryLikeValuesToMatcher_134) {
  MockIntMatcher mm;
  const int big = std::numeric_limits<int>::max();
  EXPECT_CALL(mm, match(::testing::Eq(big))).Times(1).WillOnce(Return(true));
  EXPECT_CALL(mm, describe()).Times(::testing::AnyNumber());

  auto expr = Catch::makeMatchExpr(big, mm);
  EXPECT_TRUE(expr.getResult());
}

// External interaction verification: ensure the matcher is invoked with the
// very same object instance we passed (address identity).
TEST_F(MakeMatchExprTest_134, ForwardsTheExactObjectToMatcher_134) {
  MockWidgetMatcher mw;
  Widget w{123};

  EXPECT_CALL(mw, match(::testing::Truly([&](const Widget& seen) {
                return &seen == &w; // same object instance observed
              })))
      .Times(1)
      .WillOnce(Return(true));
  EXPECT_CALL(mw, describe()).Times(::testing::AnyNumber());

  auto expr = Catch::makeMatchExpr(w, mw);
  EXPECT_TRUE(expr.getResult());
}

// Streaming behavior: the reconstructed expression includes the argument and
// matcher description text (observable through the stream output only).
TEST_F(MakeMatchExprTest_134, StreamsArgumentAndMatcherDescription_134) {
  MockIntMatcher mm;
  ON_CALL(mm, match(::testing::An<const int&>())).WillByDefault(Return(true));
  ON_CALL(mm, describe()).WillByDefault(Return("is even (mock)"));

  auto expr = Catch::makeMatchExpr(42, mm);

  std::ostringstream oss;
  expr.streamReconstructedExpression(oss);

  // Observable expectations: contains argument and matcher text.
  EXPECT_THAT(oss.str(), HasSubstr("42"));
  EXPECT_THAT(oss.str(), HasSubstr("even"));
}

// Type-deduction smoke test: verify the returned type matches the
// documented template instantiation (ArgT, MatcherT).
TEST_F(MakeMatchExprTest_134, DeducesReturnTypeAsMatchExpr_134) {
  IsEvenMatcher matcher;
  auto expr = Catch::makeMatchExpr(0, matcher);
  // The exact type should be MatchExpr<int, IsEvenMatcher>.
  using Expected = Catch::MatchExpr<int, IsEvenMatcher>;
  static_assert(std::is_same<decltype(expr), Expected>::value,
                "makeMatchExpr must return MatchExpr<ArgT, MatcherT>");
  (void)expr; // silence unused warning in some builds
}

// Exceptional path: if the matcher throws during evaluation, that exception
// is observable to the caller. We do not assume whether evaluation happens
// in the constructor or in getResult(); we just force evaluation.
TEST_F(MakeMatchExprTest_134, PropagatesExceptionsFromMatcher_134) {
  struct BoomMatcher : public Catch::Matchers::MatcherBase<int> {
    bool match(int const&) const override { throw std::runtime_error("boom"); }
    std::string describe() const override { return "throws"; }
  } boom;

  EXPECT_THROW({
    auto expr = Catch::makeMatchExpr(7, boom);
    // Force any deferred evaluation path as well:
    (void)expr.getResult();
  }, std::runtime_error);
}
