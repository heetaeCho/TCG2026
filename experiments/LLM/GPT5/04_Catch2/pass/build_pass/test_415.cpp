// optional_bool_op_tests_415.cpp
#include <gtest/gtest.h>

// Include the provided header (adjust the include path if needed)
#include "Catch2/src/catch2/internal/catch_optional.hpp"

using Catch::Optional;

// A simple non-trivial type to ensure operator bool doesn't depend on T's triviality
struct Widget {
  Widget() : x(0) {}
  explicit Widget(int v) : x(v) {}
  Widget(Widget const&) = default;
  Widget(Widget&&) noexcept = default;
  Widget& operator=(Widget const&) = default;
  Widget& operator=(Widget&&) noexcept = default;
  int x;
};

// --- Tests ---

TEST(OptionalBoolTest_415, DefaultConstructedIsFalse_415) {
  Optional<int> o;
  EXPECT_FALSE(static_cast<bool>(o));
  EXPECT_TRUE(!o);           // Cross-check with operator! (observable)
  EXPECT_TRUE(o.none());     // Cross-check with none() (observable)
  EXPECT_FALSE(o.some());
}

TEST(OptionalBoolTest_415, ValueConstructedIsTrue_Lvalue_415) {
  int v = 42;
  Optional<int> o(v);
  EXPECT_TRUE(static_cast<bool>(o));
  EXPECT_FALSE(!o);
  EXPECT_TRUE(o.some());
  EXPECT_FALSE(o.none());
}

TEST(OptionalBoolTest_415, ValueConstructedIsTrue_Rvalue_415) {
  Optional<int> o(7);
  EXPECT_TRUE(static_cast<bool>(o));
  EXPECT_FALSE(!o);
  EXPECT_TRUE(o.some());
  EXPECT_FALSE(o.none());
}

TEST(OptionalBoolTest_415, ResetMakesItFalse_415) {
  Optional<int> o(1);
  ASSERT_TRUE(static_cast<bool>(o)); // precondition
  o.reset();
  EXPECT_FALSE(static_cast<bool>(o));
  EXPECT_TRUE(!o);
  EXPECT_TRUE(o.none());
}

TEST(OptionalBoolTest_415, CopyConstructFromEngaged_PreservesTruthiness_415) {
  Optional<int> a(5);
  Optional<int> b(a);
  EXPECT_TRUE(static_cast<bool>(a));   // original remains engaged
  EXPECT_TRUE(static_cast<bool>(b));   // copy is engaged
}

TEST(OptionalBoolTest_415, CopyConstructFromDisengaged_PreservesFalseness_415) {
  Optional<int> a;
  Optional<int> b(a);
  EXPECT_FALSE(static_cast<bool>(a));
  EXPECT_FALSE(static_cast<bool>(b));
}

TEST(OptionalBoolTest_415, MoveConstructFromEngaged_PreservesTruthiness_415) {
  Optional<Widget> a(Widget{10});
  Optional<Widget> b(std::move(a));
  // As a black box, we only assert observable truthiness of both objects.
  EXPECT_TRUE(static_cast<bool>(b));
  // The source's state after move is unspecified for many types; however,
  // Catch::Optional's interface keeps it observable via bool/none/some.
  // We only assert that the destination is engaged.
}

TEST(OptionalBoolTest_415, AssignmentsAffectTruthiness_415) {
  Optional<int> o;                  // false
  EXPECT_FALSE(static_cast<bool>(o));

  o = 3;                            // assign value
  EXPECT_TRUE(static_cast<bool>(o));

  Optional<int> other;              // empty
  o = other;                        // copy-assign from empty
  EXPECT_FALSE(static_cast<bool>(o));

  other = 9;                        // make other engaged
  o = other;                        // copy-assign from engaged
  EXPECT_TRUE(static_cast<bool>(o));

  o = Optional<int>();              // assign from temporary empty
  EXPECT_FALSE(static_cast<bool>(o));

  o = Optional<int>(11);            // assign from temporary engaged
  EXPECT_TRUE(static_cast<bool>(o));
}

TEST(OptionalBoolTest_415, BoolConsistencyWithSomeAndNone_415) {
  Optional<Widget> empty;
  Optional<Widget> full(Widget{1});

  // For empty
  EXPECT_EQ(static_cast<bool>(empty), empty.some());
  EXPECT_NE(static_cast<bool>(empty), empty.none());

  // For engaged
  EXPECT_EQ(static_cast<bool>(full), full.some());
  EXPECT_NE(static_cast<bool>(full), full.none());
}
