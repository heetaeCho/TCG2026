// File: match_any_of_or_operator_test_163.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <array>

// Include the partial header under test
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::MatchAnyOfGeneric;

// --- Simple external collaborator matchers (black-box to class under test) ---

struct TrueMatcher {
  template <typename T>
  bool match(const T&) const { return true; }
  std::string describe() const { return "true"; }
};

struct FalseMatcher {
  template <typename T>
  bool match(const T&) const { return false; }
  std::string describe() const { return "false"; }
};

struct IsEvenMatcher {
  template <typename T>
  bool match(const T& v) const { return (v % 2) == 0; }
  std::string describe() const { return "is even"; }
};

struct MultipleOf3Matcher {
  template <typename T>
  bool match(const T& v) const { return (v % 3) == 0; }
  std::string describe() const { return "multiple of 3"; }
};

// Helper to create an empty MatchAnyOfGeneric<> using the explicit array ctor
static MatchAnyOfGeneric<> MakeEmptyAnyOf() {
  // sizeof...(MatcherTs) == 0 here, so zero-sized array is OK
  return MatchAnyOfGeneric<>(
      std::array<void const*, 0>{});
}

// Helper to ensure we pass rvalues to operator||
template <typename... L>
static MatchAnyOfGeneric<L...> MakeAnyOf(L const&... l) {
  return MatchAnyOfGeneric<L...>(l...);
}

// ---- Tests ----

TEST(MatchAnyOfOrOperator_163, ReturnsTrueIfAnyLeftMatches_163) {
  auto lhs = MakeAnyOf(TrueMatcher{});     // always matches
  auto rhs = MakeAnyOf(FalseMatcher{});    // never matches

  auto combined = std::move(lhs) || std::move(rhs);

  EXPECT_TRUE(combined.match(123));
  EXPECT_TRUE(combined.match("anything"));
}

TEST(MatchAnyOfOrOperator_163, ReturnsTrueIfAnyRightMatches_163) {
  auto lhs = MakeAnyOf(FalseMatcher{});
  auto rhs = MakeAnyOf(TrueMatcher{});

  auto combined = std::move(lhs) || std::move(rhs);

  EXPECT_TRUE(combined.match(0));
  EXPECT_TRUE(combined.match(42));
}

TEST(MatchAnyOfOrOperator_163, ReturnsFalseIfNeitherSideMatches_163) {
  auto lhs = MakeAnyOf(FalseMatcher{}, FalseMatcher{});
  auto rhs = MakeAnyOf(FalseMatcher{});

  auto combined = std::move(lhs) || std::move(rhs);

  EXPECT_FALSE(combined.match(7));
  EXPECT_FALSE(combined.match("nope"));
}

TEST(MatchAnyOfOrOperator_163, WorksWithHeterogeneousMatchers_163) {
  auto lhs = MakeAnyOf(IsEvenMatcher{});
  auto rhs = MakeAnyOf(MultipleOf3Matcher{});

  auto combined = std::move(lhs) || std::move(rhs);

  // divisible by 2 -> true
  EXPECT_TRUE(combined.match(10));
  // divisible by 3 -> true
  EXPECT_TRUE(combined.match(9));
  // neither -> false
  EXPECT_FALSE(combined.match(7));
}

TEST(MatchAnyOfOrOperator_163, CombiningWithEmptyLeftBehavesLikeRight_163) {
  auto lhs = MakeEmptyAnyOf();
  auto rhs = MakeAnyOf(IsEvenMatcher{}, MultipleOf3Matcher{});

  auto combined = std::move(lhs) || std::move(rhs);

  EXPECT_TRUE(combined.match(12));  // both even and multiple of 3
  EXPECT_TRUE(combined.match(8));   // even
  EXPECT_TRUE(combined.match(9));   // multiple of 3
  EXPECT_FALSE(combined.match(7));  // neither
}

TEST(MatchAnyOfOrOperator_163, CombiningWithEmptyRightBehavesLikeLeft_163) {
  auto lhs = MakeAnyOf(IsEvenMatcher{});
  auto rhs = MakeEmptyAnyOf();

  auto combined = std::move(lhs) || std::move(rhs);

  EXPECT_TRUE(combined.match(2));
  EXPECT_FALSE(combined.match(3));
}

TEST(MatchAnyOfOrOperator_163, ResultTypeConcatenatesMatcherPacks_163) {
  using L = MatchAnyOfGeneric<IsEvenMatcher>;
  using R = MatchAnyOfGeneric<MultipleOf3Matcher, TrueMatcher>;

  // Build rvalues and apply operator||
  auto result = L(IsEvenMatcher{}) || R(MultipleOf3Matcher{}, TrueMatcher{});

  // The expression's type should be MatchAnyOfGeneric<IsEvenMatcher, MultipleOf3Matcher, TrueMatcher>
  using Expected =
      MatchAnyOfGeneric<IsEvenMatcher, MultipleOf3Matcher, TrueMatcher>;
  static_assert(std::is_same<decltype(result), Expected>::value,
                "operator|| should concatenate matcher parameter packs");
}
