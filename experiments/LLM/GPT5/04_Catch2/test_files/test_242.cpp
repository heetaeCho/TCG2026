// File: message_matches_tests_242.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Header under test
#include "catch2/matchers/catch_matchers_exception.hpp"

namespace {

struct DummyMatcher {};

// Move-only matcher to verify perfect-forwarding works with rvalues.
struct MoveOnlyMatcher {
  MoveOnlyMatcher() = default;
  MoveOnlyMatcher(const MoveOnlyMatcher&) = delete;
  MoveOnlyMatcher& operator=(const MoveOnlyMatcher&) = delete;
  MoveOnlyMatcher(MoveOnlyMatcher&&) noexcept = default;
  MoveOnlyMatcher& operator=(MoveOnlyMatcher&&) noexcept = default;
};

} // namespace

// 1) Lvalue argument: template parameter should be deduced as T&,
//    and the return type should be ExceptionMessageMatchesMatcher<T&>.
TEST(MessageMatchesTest_242, ReturnsWrapperTypeForLvalue_242) {
  DummyMatcher m{};
  using Ret = decltype(Catch::Matchers::MessageMatches(m));
  using Expected =
      Catch::Matchers::ExceptionMessageMatchesMatcher<DummyMatcher&>;
  static_assert(std::is_same<Ret, Expected>::value,
                "Return type should wrap the deduced lvalue reference type");
  (void)sizeof(Ret); // silence unused in case of non-generic builds
}

// 2) Rvalue argument: template parameter should be deduced as T (no reference),
//    and the return type should be ExceptionMessageMatchesMatcher<T>.
TEST(MessageMatchesTest_242, ReturnsWrapperTypeForRvalue_242) {
  using Ret = decltype(Catch::Matchers::MessageMatches(DummyMatcher{}));
  using Expected =
      Catch::Matchers::ExceptionMessageMatchesMatcher<DummyMatcher>;
  static_assert(std::is_same<Ret, Expected>::value,
                "Return type should wrap the deduced value type for rvalues");
  (void)sizeof(Ret);
}

// 3) Const lvalue argument: template parameter should be deduced as const T&,
//    and the return type should be ExceptionMessageMatchesMatcher<const T&>.
TEST(MessageMatchesTest_242, PreservesConstForConstLvalue_242) {
  const DummyMatcher m{};
  using Ret = decltype(Catch::Matchers::MessageMatches(m));
  using Expected =
      Catch::Matchers::ExceptionMessageMatchesMatcher<const DummyMatcher&>;
  static_assert(std::is_same<Ret, Expected>::value,
                "Return type should preserve const on lvalue references");
  (void)sizeof(Ret);
}

// 4) Move-only rvalue: expression should be well-formed for move-only types,
//    demonstrating that the function can accept and forward rvalues that
//    are not copyable. We only check that the type is as expected.
TEST(MessageMatchesTest_242, AcceptsMoveOnlyMatcherAsRvalue_242) {
  using Ret = decltype(Catch::Matchers::MessageMatches(MoveOnlyMatcher{}));
  using Expected =
      Catch::Matchers::ExceptionMessageMatchesMatcher<MoveOnlyMatcher>;
  static_assert(std::is_same<Ret, Expected>::value,
                "Return type should wrap move-only matcher for rvalues");
  (void)sizeof(Ret);
}

// 5) Lvalue of move-only matcher: the expression should still be well-formed,
//    and the deduced type should carry an lvalue reference (no move occurs here).
TEST(MessageMatchesTest_242, LvalueMoveOnlyMatcherYieldsRefParam_242) {
  MoveOnlyMatcher m{};
  using Ret = decltype(Catch::Matchers::MessageMatches(m));
  using Expected =
      Catch::Matchers::ExceptionMessageMatchesMatcher<MoveOnlyMatcher&>;
  static_assert(std::is_same<Ret, Expected>::value,
                "Return type should wrap an lvalue reference for lvalue args");
  (void)sizeof(Ret);
}
