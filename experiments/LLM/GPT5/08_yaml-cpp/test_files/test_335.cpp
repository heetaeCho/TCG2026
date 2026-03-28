// File: ./TestProjects/yaml-cpp/test/dragonbox_trailing_zero_ignore_t_test_335.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

struct DummyFormat335 {};

template <class R>
constexpr auto Decompose2(const R& r) {
  // Use structured bindings to avoid relying on member names.
  auto [s, e] = r;
  return std::pair<decltype(s), decltype(e)>(s, e);
}

}  // namespace

TEST(TrailingZeroIgnoreTTest_335, OnTrailingZerosPreservesInputs_335) {
  using YAML::jkj::dragonbox::policy::trailing_zero::ignore_t;

  const std::uint64_t sig = 1234567890123456789ULL;
  const int exp = -42;

  const auto r = ignore_t::on_trailing_zeros<DummyFormat335>(sig, exp);
  const auto [out_sig, out_exp] = Decompose2(r);

  EXPECT_EQ(out_sig, sig);
  EXPECT_EQ(out_exp, exp);
}

TEST(TrailingZeroIgnoreTTest_335, OnTrailingZerosWorksWithZeroValues_335) {
  using YAML::jkj::dragonbox::policy::trailing_zero::ignore_t;

  const std::uint32_t sig = 0u;
  const std::int32_t exp = 0;

  const auto r = ignore_t::on_trailing_zeros<DummyFormat335>(sig, exp);
  const auto [out_sig, out_exp] = Decompose2(r);

  EXPECT_EQ(out_sig, sig);
  EXPECT_EQ(out_exp, exp);
}

TEST(TrailingZeroIgnoreTTest_335, OnTrailingZerosBoundaryValues_335) {
  using YAML::jkj::dragonbox::policy::trailing_zero::ignore_t;

  const std::uint64_t sig_max = (std::numeric_limits<std::uint64_t>::max)();
  const std::int32_t exp_min = (std::numeric_limits<std::int32_t>::min)();
  const std::int32_t exp_max = (std::numeric_limits<std::int32_t>::max)();

  {
    const auto r = ignore_t::on_trailing_zeros<DummyFormat335>(sig_max, exp_min);
    const auto [out_sig, out_exp] = Decompose2(r);
    EXPECT_EQ(out_sig, sig_max);
    EXPECT_EQ(out_exp, exp_min);
  }
  {
    const auto r = ignore_t::on_trailing_zeros<DummyFormat335>(sig_max, exp_max);
    const auto [out_sig, out_exp] = Decompose2(r);
    EXPECT_EQ(out_sig, sig_max);
    EXPECT_EQ(out_exp, exp_max);
  }
}

TEST(TrailingZeroIgnoreTTest_335, OnTrailingZerosIsConstexprAndNoexcept_335) {
  using YAML::jkj::dragonbox::policy::trailing_zero::ignore_t;

  static_assert(noexcept(ignore_t::on_trailing_zeros<DummyFormat335>(0u, 0)),
                "on_trailing_zeros should be noexcept");

  constexpr std::uint32_t sig = 77u;
  constexpr int exp = 5;
  constexpr auto r = ignore_t::on_trailing_zeros<DummyFormat335>(sig, exp);

  constexpr auto decomp = Decompose2(r);
  static_assert(decomp.first == sig, "significand should be preserved");
  static_assert(decomp.second == exp, "exponent should be preserved");
}

TEST(TrailingZeroIgnoreTTest_335, NoTrailingZerosIsCallableAndNoexcept_335) {
  using YAML::jkj::dragonbox::policy::trailing_zero::ignore_t;

  // This test only verifies observable interface properties:
  // - the function can be called
  // - it is noexcept (as declared)
  // - it returns the same type as on_trailing_zeros for the same inputs
  static_assert(noexcept(ignore_t::no_trailing_zeros<DummyFormat335>(0u, 0)),
                "no_trailing_zeros should be noexcept");

  using R1 = decltype(ignore_t::on_trailing_zeros<DummyFormat335>(0u, 0));
  using R2 = decltype(ignore_t::no_trailing_zeros<DummyFormat335>(0u, 0));
  static_assert(std::is_same<R1, R2>::value,
                "Return type should match for on_trailing_zeros and no_trailing_zeros");

  // Also exercise at runtime to ensure it links and runs.
  const auto r = ignore_t::no_trailing_zeros<DummyFormat335>(123u, -1);
  (void)r;
  SUCCEED();
}