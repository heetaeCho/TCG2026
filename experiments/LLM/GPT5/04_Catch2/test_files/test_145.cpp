// File: tests/matchers_operator_and_and_145_test.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// Include the interface under test
#include <catch2/matchers/catch_matchers.hpp>

// Short aliases for readability
namespace C  = Catch;
namespace CM = Catch::Matchers;

// Helper: SFINAE detector for the expression LHS && RHS
template <typename L, typename R, typename = void>
struct is_and_valid : std::false_type {};

template <typename L, typename R>
struct is_and_valid<L, R, std::void_t<decltype(std::declval<L>() && std::declval<R>())>>
    : std::true_type {};

// ---- Tests ----

// Normal operation: two MatcherBase<T> should compose via operator&& and
// yield Detail::MatchAllOf<T>.
TEST(MatchersOperatorAndAnd_145, ReturnTypeIsMatchAllOf_Int_145) {
  using MB  = CM::MatcherBase<int>;
  using Ret = decltype(std::declval<const MB&>() && std::declval<const MB&>());
  static_assert(std::is_same<Ret, CM::Detail::MatchAllOf<int>>::value,
                "operator&& must return Detail::MatchAllOf<T> for same-T matchers");
  SUCCEED(); // Run-time no-op; compile-time checks are above.
}

// Boundary: chaining three operands (a && b && c) should still be well-formed
// and produce Detail::MatchAllOf<T>.
TEST(MatchersOperatorAndAnd_145, ChainingThreeOperandsYieldsMatchAllOf_145) {
  using MB  = CM::MatcherBase<int>;
  using Ret = decltype(
      std::declval<const MB&>() &&
      std::declval<const MB&>() &&
      std::declval<const MB&>());

  static_assert(std::is_same<Ret, CM::Detail::MatchAllOf<int>>::value,
                "Chaining with three operands should produce MatchAllOf<T>");
  SUCCEED();
}

// Normal operation with derived types: operator&& should work when operands are
// any types derived from MatcherBase<T> (common in real code).
struct DummyDerivedA : CM::MatcherBase<int> { /* abstract; not instantiated */ };
struct DummyDerivedB : CM::MatcherBase<int> { /* abstract; not instantiated */ };

TEST(MatchersOperatorAndAnd_145, AcceptsDerivedFromMatcherBase_145) {
  using A   = DummyDerivedA;
  using B   = DummyDerivedB;
  using Ret = decltype(std::declval<const A&>() && std::declval<const B&>());
  static_assert(std::is_same<Ret, CM::Detail::MatchAllOf<int>>::value,
                "Derived matchers should compose to MatchAllOf<T>");
  SUCCEED();
}

// Error/exceptional (type-compatibility) case: mixing different T's should NOT
// select this operator&& (ill-formed). We check that via SFINAE detector.
TEST(MatchersOperatorAndAnd_145, DifferentTDoesNotSelectOperator_145) {
  using MBi = CM::MatcherBase<int>;
  using MBd = CM::MatcherBase<double>;
  static_assert( is_and_valid<const MBi&, const MBi&>::value,
                 "Same-T operands must be valid" );
  static_assert(!is_and_valid<const MBi&, const MBd&>::value,
                 "Different-T operands must be ill-formed for this operator&&");
  SUCCEED();
}

// Boundary: ensure the resulting type from (a && b) can itself be chained with
// another MatcherBase<T> (i.e., (a && b) && c is well-formed).
TEST(MatchersOperatorAndAnd_145, ResultIsComposableFurther_145) {
  using MB  = CM::MatcherBase<int>;
  using AB  = decltype(std::declval<const MB&>() && std::declval<const MB&>());
  using Ret = decltype(std::declval<AB>() && std::declval<const MB&>());
  static_assert(std::is_same<Ret, CM::Detail::MatchAllOf<int>>::value,
                "Result of (a && b) must be chainable with another matcher");
  SUCCEED();
}
