// File: matchers_operator_and_generic_tests_169.cpp
#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers_templated.hpp>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {

using Catch::Matchers::Detail::MatchAllOfGeneric;
using Catch::Matchers::MatcherGenericBase;

// === Minimal external collaborators (generic matchers) used by the tests ===
// They derive from MatcherGenericBase to be recognized as "generic matchers"
// by the operator&& SFINAE constraint. They are test doubles, not simulating
// any internal logic of operator&& itself.

struct AlwaysTrueA : MatcherGenericBase {
  template <typename T>
  bool match(T const&) const { return true; }
  std::string describe() const override { return "AlwaysTrueA"; }
};

struct AlwaysTrueB : MatcherGenericBase {
  template <typename T>
  bool match(T const&) const { return true; }
  std::string describe() const override { return "AlwaysTrueB"; }
};

struct AlwaysFalse : MatcherGenericBase {
  template <typename T>
  bool match(T const&) const { return false; }
  std::string describe() const override { return "AlwaysFalse"; }
};

// Helper that records how many times match(T) is invoked.
// We do NOT rely on any specific evaluation order or short-circuiting;
// we only assert that when the overall result must be true, both sub-matchers
// are evaluated at least once.
struct CountingTrue : MatcherGenericBase {
  explicit CountingTrue(std::shared_ptr<int> counter) : counter_(std::move(counter)) {}
  template <typename T>
  bool match(T const&) const {
    ++(*counter_);
    return true;
  }
  std::string describe() const override { return "CountingTrue"; }
private:
  std::shared_ptr<int> counter_;
};

} // namespace

// ------------------------------ Tests ------------------------------

TEST(MatchersOperatorAndGeneric_169, ReturnTypeIsMatchAllOfGeneric_169) {
  // Compile-time assertion that the operator&& returns the documented type.
  AlwaysTrueA lhs;
  AlwaysTrueB rhs;
  using Ret = decltype(lhs && rhs);
  static_assert(std::is_same<Ret, MatchAllOfGeneric<AlwaysTrueA, AlwaysTrueB>>::value,
                "operator&& must return MatchAllOfGeneric<MatcherLHS, MatcherRHS>");
  (void)lhs; (void)rhs; // silence unused in non-constexpr contexts
}

TEST(MatchersOperatorAndGeneric_169, TrueAndTrueMatchesValue_Int_169) {
  auto composite = AlwaysTrueA{} && AlwaysTrueB{};
  EXPECT_TRUE(composite.match(42));
}

TEST(MatchersOperatorAndGeneric_169, TrueAndTrueMatchesValue_String_169) {
  AlwaysTrueA a;
  AlwaysTrueB b;
  auto composite = a && b;
  EXPECT_TRUE(composite.match(std::string{"hello"}));
}

TEST(MatchersOperatorAndGeneric_169, TrueAndFalseYieldsFalse_169) {
  auto composite = AlwaysTrueA{} && AlwaysFalse{};
  EXPECT_FALSE(composite.match(123));
}

TEST(MatchersOperatorAndGeneric_169, FalseAndTrueYieldsFalse_169) {
  auto composite = AlwaysFalse{} && AlwaysTrueB{};
  EXPECT_FALSE(composite.match(std::string{"catch2"}));
}

TEST(MatchersOperatorAndGeneric_169, WorksWithTemporaries_Rvalues_169) {
  // Both sides are temporaries
  auto composite = AlwaysTrueA{} && AlwaysTrueB{};
  EXPECT_TRUE(composite.match('x'));
}

TEST(MatchersOperatorAndGeneric_169, WorksWithMixedValueCategories_169) {
  AlwaysTrueA a;
  AlwaysTrueB b;

  // lvalue && rvalue
  auto comp1 = a && AlwaysTrueB{};
  EXPECT_TRUE(comp1.match(3.14));

  // rvalue && lvalue
  auto comp2 = AlwaysTrueA{} && b;
  EXPECT_TRUE(comp2.match(std::vector<int>{1, 2, 3}));
}

TEST(MatchersOperatorAndGeneric_169, CompositeIsCopyAndMoveUsable_169) {
  auto original = AlwaysTrueA{} && AlwaysTrueB{};

  // Copy
  auto copy = original;
  EXPECT_TRUE(copy.match(0));

  // Move
  auto moved = std::move(original);
  EXPECT_TRUE(moved.match(0));
}

TEST(MatchersOperatorAndGeneric_169, BothSubMatchersAreConsultedWhenOverallTrue_169) {
  // When both sub-matchers must succeed to yield true, both should be consulted.
  auto c1 = std::make_shared<int>(0);
  auto c2 = std::make_shared<int>(0);

  CountingTrue lhs{c1};
  CountingTrue rhs{c2};

  auto composite = lhs && rhs;
  EXPECT_TRUE(composite.match(7));  // overall true

  EXPECT_EQ(*c1, 1);
  EXPECT_EQ(*c2, 1);
}

