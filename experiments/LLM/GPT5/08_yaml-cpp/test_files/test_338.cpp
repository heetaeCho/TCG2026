// TEST_ID: 338
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

struct DummyFormat_338 {};

using YAML::jkj::dragonbox::policy::trailing_zero::remove_t;

template <class T>
constexpr T MaxOf() {
  return (std::numeric_limits<T>::max)();
}
template <class T>
constexpr T MinOf() {
  return (std::numeric_limits<T>::min)();
}

}  // namespace

class RemoveTTest_338 : public ::testing::Test {};

TEST_F(RemoveTTest_338, NoTrailingZeros_ReturnsExpectedValues_UInt32_Int32_338) {
  const std::uint32_t sig = 123456789u;
  const std::int32_t exp = -42;

  auto out = remove_t::template no_trailing_zeros<DummyFormat_338>(sig, exp);

  // Validate observable content via structured bindings (works for aggregates / tuple-like).
  auto [out_sig, out_exp] = out;
  EXPECT_EQ(out_sig, sig);
  EXPECT_EQ(out_exp, exp);
}

TEST_F(RemoveTTest_338, NoTrailingZeros_AllowsZeroSignificand_338) {
  const std::uint64_t sig = 0u;
  const int exp = 0;

  auto out = remove_t::template no_trailing_zeros<DummyFormat_338>(sig, exp);
  auto [out_sig, out_exp] = out;

  EXPECT_EQ(out_sig, sig);
  EXPECT_EQ(out_exp, exp);
}

TEST_F(RemoveTTest_338, NoTrailingZeros_HandlesExponentMinMax_338) {
  using ExpT = std::int16_t;
  const std::uint32_t sig = 7u;

  {
    const ExpT exp = MinOf<ExpT>();
    auto out = remove_t::template no_trailing_zeros<DummyFormat_338>(sig, exp);
    auto [out_sig, out_exp] = out;
    EXPECT_EQ(out_sig, sig);
    EXPECT_EQ(out_exp, exp);
  }
  {
    const ExpT exp = MaxOf<ExpT>();
    auto out = remove_t::template no_trailing_zeros<DummyFormat_338>(sig, exp);
    auto [out_sig, out_exp] = out;
    EXPECT_EQ(out_sig, sig);
    EXPECT_EQ(out_exp, exp);
  }
}

TEST_F(RemoveTTest_338, NoTrailingZeros_HandlesSignificandMax_338) {
  using SigT = std::uint16_t;
  using ExpT = std::int8_t;

  const SigT sig = MaxOf<SigT>();
  const ExpT exp = static_cast<ExpT>(-1);

  auto out = remove_t::template no_trailing_zeros<DummyFormat_338>(sig, exp);
  auto [out_sig, out_exp] = out;

  EXPECT_EQ(out_sig, sig);
  EXPECT_EQ(out_exp, exp);
}

TEST_F(RemoveTTest_338, NoTrailingZeros_IsNoexcept_338) {
  using SigT = std::uint32_t;
  using ExpT = int;

  static_assert(
      noexcept(remove_t::template no_trailing_zeros<DummyFormat_338>(SigT{1}, ExpT{2})),
      "no_trailing_zeros is expected to be noexcept");
  SUCCEED();
}

TEST_F(RemoveTTest_338, NoTrailingZeros_IsConstexprAndReturnsExpectedType_338) {
  using SigT = std::uint32_t;
  using ExpT = int;

  constexpr SigT sig = 99u;
  constexpr ExpT exp = -3;

  constexpr auto out = remove_t::template no_trailing_zeros<DummyFormat_338>(sig, exp);
  static_assert(std::is_same_v<decltype(out),
                                YAML::jkj::dragonbox::unsigned_decimal_fp<SigT, ExpT, false>>,
                "Return type must be unsigned_decimal_fp<Significand, Exponent, false>");

  // Also validate values at compile-time (where possible).
  constexpr auto out_sig = ([] {
    auto [s, e] = out;
    (void)e;
    return s;
  })();
  constexpr auto out_exp = ([] {
    auto [s, e] = out;
    (void)s;
    return e;
  })();

  static_assert(out_sig == sig, "Significand must be preserved");
  static_assert(out_exp == exp, "Exponent must be preserved");

  // And a runtime check (keeps the test observable in gtest output).
  auto [rs, re] = out;
  EXPECT_EQ(rs, sig);
  EXPECT_EQ(re, exp);
}