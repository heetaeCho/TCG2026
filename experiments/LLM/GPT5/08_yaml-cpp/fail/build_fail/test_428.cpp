// TEST_ID: 428
#include <gtest/gtest.h>

#include <cstring>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class T>
void ExpectToDecimalReturnEqual(const T& a, const T& b) {
  // Prefer member-wise comparison when common members exist.
  if constexpr (requires { a.significand; b.significand; }) {
    EXPECT_EQ(a.significand, b.significand);
  }
  if constexpr (requires { a.exponent; b.exponent; }) {
    EXPECT_EQ(a.exponent, b.exponent);
  }
  if constexpr (requires { a.is_negative; b.is_negative; }) {
    EXPECT_EQ(a.is_negative, b.is_negative);
  }
  if constexpr (requires { a.may_have_trailing_zeros; b.may_have_trailing_zeros; }) {
    EXPECT_EQ(a.may_have_trailing_zeros, b.may_have_trailing_zeros);
  }
  if constexpr (requires { a.has_trailing_zeros; b.has_trailing_zeros; }) {
    EXPECT_EQ(a.has_trailing_zeros, b.has_trailing_zeros);
  }

  // Fallback: bitwise compare for trivially copyable return types.
  if constexpr (std::is_trivially_copyable_v<T>) {
    EXPECT_EQ(0, std::memcmp(&a, &b, sizeof(T)));
  }
}

class ToDecimalExTest_428 : public ::testing::Test {};

using Dragonbox = YAML::jkj::dragonbox;

}  // namespace

TEST_F(ToDecimalExTest_428, IsNoexceptForTypicalInstantiation_428) {
  using FormatTraits = Dragonbox::ieee754_binary32;
  using S = Dragonbox::signed_significand_bits<FormatTraits>;
  using E = unsigned;  // just to bind a type; ExponentBits is deduced from the argument.

  // This checks the interface contract: the function is declared noexcept.
  static_assert(noexcept(Dragonbox::to_decimal_ex<FormatTraits>(
      S{0}, E{0})));
}

TEST_F(ToDecimalExTest_428, DelegatesToPolicyHolderForEmptyPolicies_428) {
  using FormatTraits = Dragonbox::ieee754_binary32;
  using S = Dragonbox::signed_significand_bits<FormatTraits>;
  using E = std::uint32_t;

  const S s = S{1};
  const E e = E{0};

  const auto via_wrapper = Dragonbox::to_decimal_ex<FormatTraits>(s, e);

  using PolicyHolder = Dragonbox::detail::to_decimal_policy_holder<>;
  const auto via_delegate = PolicyHolder::delegate(
      s, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s, e);

  ExpectToDecimalReturnEqual(via_wrapper, via_delegate);
}

TEST_F(ToDecimalExTest_428, HandlesZeroSignificand_428) {
  using FormatTraits = Dragonbox::ieee754_binary32;
  using S = Dragonbox::signed_significand_bits<FormatTraits>;
  using E = std::uint32_t;

  const S s = S{0};
  const E e = E{0};

  const auto r1 = Dragonbox::to_decimal_ex<FormatTraits>(s, e);

  using PolicyHolder = Dragonbox::detail::to_decimal_policy_holder<>;
  const auto r2 = PolicyHolder::delegate(
      s, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s, e);

  ExpectToDecimalReturnEqual(r1, r2);
}

TEST_F(ToDecimalExTest_428, BoundaryValuesForSignificandAndExponent_428) {
  using FormatTraits = Dragonbox::ieee754_binary64;
  using S = Dragonbox::signed_significand_bits<FormatTraits>;
  using E = std::uint64_t;

  const S s_min = (std::numeric_limits<S>::min)();
  const S s_max = (std::numeric_limits<S>::max)();
  const E e_min = (std::numeric_limits<E>::min)();
  const E e_max = (std::numeric_limits<E>::max)();

  const auto r_minmin = Dragonbox::to_decimal_ex<FormatTraits>(s_min, e_min);
  const auto r_maxmax = Dragonbox::to_decimal_ex<FormatTraits>(s_max, e_max);
  const auto r_minmax = Dragonbox::to_decimal_ex<FormatTraits>(s_min, e_max);
  const auto r_maxmin = Dragonbox::to_decimal_ex<FormatTraits>(s_max, e_min);

  using PolicyHolder = Dragonbox::detail::to_decimal_policy_holder<>;
  const auto d_minmin = PolicyHolder::delegate(
      s_min, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s_min, e_min);
  const auto d_maxmax = PolicyHolder::delegate(
      s_max, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s_max, e_max);
  const auto d_minmax = PolicyHolder::delegate(
      s_min, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s_min, e_max);
  const auto d_maxmin = PolicyHolder::delegate(
      s_max, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s_max, e_min);

  ExpectToDecimalReturnEqual(r_minmin, d_minmin);
  ExpectToDecimalReturnEqual(r_maxmax, d_maxmax);
  ExpectToDecimalReturnEqual(r_minmax, d_minmax);
  ExpectToDecimalReturnEqual(r_maxmin, d_maxmin);
}

TEST_F(ToDecimalExTest_428, WorksWithNegativeSignificand_428) {
  using FormatTraits = Dragonbox::ieee754_binary32;
  using S = Dragonbox::signed_significand_bits<FormatTraits>;
  using E = std::uint32_t;

  const S s = S{-1};
  const E e = E{1};

  const auto via_wrapper = Dragonbox::to_decimal_ex<FormatTraits>(s, e);

  using PolicyHolder = Dragonbox::detail::to_decimal_policy_holder<>;
  const auto via_delegate = PolicyHolder::delegate(
      s, Dragonbox::detail::to_decimal_dispatcher<FormatTraits, PolicyHolder>{}, s, e);

  ExpectToDecimalReturnEqual(via_wrapper, via_delegate);
}