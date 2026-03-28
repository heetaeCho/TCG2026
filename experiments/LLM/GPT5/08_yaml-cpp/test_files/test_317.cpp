// File: test_dragonbox_log_is_in_range_317.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

// Minimal Info template required by the interface.
template <stdr::size_t>
struct DummyInfo {};

// Convenience alias for the fully-qualified name.
template <template <stdr::size_t> class Info,
          stdr::int_least32_t MinExp,
          stdr::int_least32_t MaxExp,
          stdr::size_t Tier>
constexpr bool CallIsInRange() {
  return YAML::jkj::dragonbox::detail::log::is_in_range<Info, MinExp, MaxExp, Tier>();
}

}  // namespace

TEST(DragonboxIsInRangeTest_317, ReturnsFalseForValidExponentRange_317) {
  // Note: The function contains a static_assert that requires MinExp > MaxExp to compile.
  constexpr bool v =
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 1, 0, 0>();
  static_assert(v == false, "Expected is_in_range to return false for this overload.");
  EXPECT_FALSE(v);
}

TEST(DragonboxIsInRangeTest_317, IsConstexprEvaluatable_317) {
  // If this compiles, it is usable in constant evaluation contexts.
  constexpr bool v =
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 10, 0, 3>(123);
  static_assert(!v, "Expected false in constexpr evaluation.");
  EXPECT_FALSE(v);
}

TEST(DragonboxIsInRangeTest_317, IsNoexcept_317) {
  // The interface promises noexcept.
  EXPECT_TRUE((noexcept(
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 2, 1, 0>())));

  // Also verify that calling with arguments is still noexcept.
  EXPECT_TRUE((noexcept(
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 2, 1, 0>(1, 2, 3))));
}

TEST(DragonboxIsInRangeTest_317, AcceptsArbitraryArgumentsViaEllipsis_317) {
  // Signature is (...) so it should accept any argument list.
  EXPECT_FALSE((YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 5, 0, 0>()));
  EXPECT_FALSE((YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 5, 0, 0>(0)));
  EXPECT_FALSE((YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 5, 0, 0>(1, 2.0)));
  EXPECT_FALSE((YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 5, 0, 0>(
      "text", nullptr, 42u)));
}

TEST(DragonboxIsInRangeTest_317, BoundaryMinIsJustGreaterThanMax_317) {
  // Boundary condition to satisfy the compile-time requirement MinExp > MaxExp.
  constexpr bool v =
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 0, -1, 0>();
  static_assert(!v, "Expected false at boundary (MinExp == MaxExp + 1).");
  EXPECT_FALSE(v);
}

TEST(DragonboxIsInRangeTest_317, CurrentTierDoesNotChangeResult_317) {
  // For this overload, return value is observable and should be consistent.
  constexpr bool v0 =
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 3, 2, 0>();
  constexpr bool v1 =
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 3, 2, 1>();
  constexpr bool v9 =
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 3, 2, 9>();

  static_assert(!v0 && !v1 && !v9, "Expected all tiers to return false for this overload.");
  EXPECT_FALSE(v0);
  EXPECT_FALSE(v1);
  EXPECT_FALSE(v9);
}

TEST(DragonboxIsInRangeTest_317, ReturnsBoolType_317) {
  using Ret = decltype(
      YAML::jkj::dragonbox::detail::log::is_in_range<DummyInfo, 7, 6, 0>());
  EXPECT_TRUE((std::is_same<Ret, bool>::value));
}

/*
  Note on "exceptional/error cases":
  The only observable error behavior here is compile-time: instantiating this overload with
  parameters that do NOT satisfy its internal static_assert will fail compilation.
  Such "negative compile" tests are typically handled by separate build/compile-fail test targets,
  which are outside the scope of a runtime GoogleTest suite.
*/