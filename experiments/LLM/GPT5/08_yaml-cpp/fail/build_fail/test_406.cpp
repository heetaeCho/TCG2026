// File: ./TestProjects/yaml-cpp/test/dragonbox_impl_test_406.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <string>

#include "contrib/dragonbox.h"

namespace {

template <class T>
struct BitsOf;

template <>
struct BitsOf<float> {
  using UInt = std::uint_least32_t;
};

template <>
struct BitsOf<double> {
  using UInt = std::uint_least64_t;
};

template <class T>
typename BitsOf<T>::UInt BitCastToUInt(T v) {
  typename BitsOf<T>::UInt u{};
  static_assert(sizeof(u) == sizeof(v), "Unexpected float size");
  std::memcpy(&u, &v, sizeof(v));
  return u;
}

template <class T>
T BitCastFromUInt(typename BitsOf<T>::UInt u) {
  T v{};
  static_assert(sizeof(u) == sizeof(v), "Unexpected float size");
  std::memcpy(&v, &u, sizeof(v));
  return v;
}

template <class DecimalFp>
std::string ToENotationString(const DecimalFp& r) {
  // decimal_fp represents: significand * 10^exponent (plus sign if present).
  // Using "e" notation avoids needing to insert decimal points.
  std::string s;
  if constexpr (requires { r.is_negative; }) {
    if (r.is_negative) s.push_back('-');
  }

  s += std::to_string(static_cast<unsigned long long>(r.significand));
  s.push_back('e');
  s += std::to_string(static_cast<long long>(r.exponent));
  return s;
}

template <class T>
T ParseENotationTo(const std::string& s) {
  // Use strtof/strtod via std::strtod for portability.
  // For float, parse as double then cast; this matches typical parsing behavior
  // and is sufficient for round-trip checks.
  char* end = nullptr;
  double d = std::strtod(s.c_str(), &end);
  (void)end;
  return static_cast<T>(d);
}

template <class T>
struct DragonboxFixture_406 : ::testing::Test {};

using TestedTypes_406 = ::testing::Types<float, double>;
TYPED_TEST_SUITE(DragonboxFixture_406, TestedTypes_406);

}  // namespace

TEST(DragonboxImplMinMaxTest_406, MinBasicCases_406) {
  using FT = YAML::jkj::dragonbox::ieee754_binary_traits<
      YAML::jkj::dragonbox::ieee754_binary32, std::uint_least32_t, int>;
  using Impl = YAML::jkj::dragonbox::detail::impl<FT>;

  EXPECT_EQ(Impl::min(1, 2), 1);
  EXPECT_EQ(Impl::min(2, 1), 1);
  EXPECT_EQ(Impl::min(-5, 3), -5);
  EXPECT_EQ(Impl::min(7, 7), 7);  // boundary: equal values
}

TEST(DragonboxImplMinMaxTest_406, MaxBasicCases_406) {
  using FT = YAML::jkj::dragonbox::ieee754_binary_traits<
      YAML::jkj::dragonbox::ieee754_binary32, std::uint_least32_t, int>;
  using Impl = YAML::jkj::dragonbox::detail::impl<FT>;

  EXPECT_EQ(Impl::max(1, 2), 2);
  EXPECT_EQ(Impl::max(2, 1), 2);
  EXPECT_EQ(Impl::max(-5, 3), 3);
  EXPECT_EQ(Impl::max(7, 7), 7);  // boundary: equal values
}

TEST(DragonboxImplEndpointIntegerTest_406, EndpointPredicatesAreConstexprCallable_406) {
  using FT = YAML::jkj::dragonbox::ieee754_binary_traits<
      YAML::jkj::dragonbox::ieee754_binary64, std::uint_least64_t, int>;
  using Impl = YAML::jkj::dragonbox::detail::impl<FT>;

  // “Exceptional/error cases” aren’t directly observable here (all are noexcept),
  // so we at least validate compile-time usability across a few representative inputs.
  constexpr bool r1 = Impl::is_right_endpoint_integer_shorter_interval(0);
  constexpr bool l1 = Impl::is_left_endpoint_integer_shorter_interval(0);
  constexpr bool r2 = Impl::is_right_endpoint_integer_shorter_interval(Impl::case_shorter_interval_right_endpoint_lower_threshold);
  constexpr bool l2 = Impl::is_left_endpoint_integer_shorter_interval(Impl::case_shorter_interval_left_endpoint_lower_threshold);

  // Runtime should match constexpr evaluation for the same inputs.
  EXPECT_EQ(Impl::is_right_endpoint_integer_shorter_interval(0), r1);
  EXPECT_EQ(Impl::is_left_endpoint_integer_shorter_interval(0), l1);
  EXPECT_EQ(Impl::is_right_endpoint_integer_shorter_interval(
                Impl::case_shorter_interval_right_endpoint_lower_threshold),
            r2);
  EXPECT_EQ(Impl::is_left_endpoint_integer_shorter_interval(
                Impl::case_shorter_interval_left_endpoint_lower_threshold),
            l2);
}

TYPED_TEST(DragonboxFixture_406, ComputeNearest_RoundTripsCommonFiniteValues_406) {
  using T = TypeParam;

  using Format = std::conditional_t<std::is_same_v<T, float>,
                                   YAML::jkj::dragonbox::ieee754_binary32,
                                   YAML::jkj::dragonbox::ieee754_binary64>;
  using Carrier = std::conditional_t<std::is_same_v<T, float>, std::uint_least32_t, std::uint_least64_t>;

  using FT = YAML::jkj::dragonbox::ieee754_binary_traits<Format, Carrier, int>;
  using Impl = YAML::jkj::dragonbox::detail::impl<FT>;

  using SignPolicy = YAML::jkj::dragonbox::policy::sign::return_sign_t;
  using TrailingZeroPolicy = YAML::jkj::dragonbox::policy::trailing_zero::report_t;
  using IntervalTypeProvider = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;
  using BinaryToDecimalRoundingPolicy = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::do_not_care_t;
  using CachePolicy = YAML::jkj::dragonbox::policy::cache::full_t;
  using PreferredInts = YAML::jkj::dragonbox::policy::preferred_integer_types::match_t;

  auto round_trip_check = [&](T v) {
    const auto bits = BitCastToUInt(v);

    YAML::jkj::dragonbox::float_bits<FT> fb(static_cast<Carrier>(bits));
    const auto exponent_bits = fb.extract_exponent_bits();
    const auto s = fb.remove_exponent_bits();

    const auto r = Impl::template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider,
                                                  BinaryToDecimalRoundingPolicy, CachePolicy, PreferredInts>(s, exponent_bits);

    const std::string str = ToENotationString(r);
    const T parsed = ParseENotationTo<T>(str);

    EXPECT_EQ(BitCastToUInt(parsed), BitCastToUInt(v)) << "failed round-trip for: " << str;
  };

  // Normal operation: typical values.
  round_trip_check(static_cast<T>(0.0));
  round_trip_check(static_cast<T>(1.0));
  round_trip_check(static_cast<T>(-1.0));
  round_trip_check(static_cast<T>(0.1));
  round_trip_check(static_cast<T>(3.1415926535897932384626L));

  // Boundary-ish: negative zero (distinct sign bit).
  round_trip_check(static_cast<T>(-0.0));
}

TYPED_TEST(DragonboxFixture_406, ComputeNearest_RoundTripsExtremes_SubnormalAndMaxFinite_406) {
  using T = TypeParam;

  using Format = std::conditional_t<std::is_same_v<T, float>,
                                   YAML::jkj::dragonbox::ieee754_binary32,
                                   YAML::jkj::dragonbox::ieee754_binary64>;
  using Carrier = std::conditional_t<std::is_same_v<T, float>, std::uint_least32_t, std::uint_least64_t>;

  using FT = YAML::jkj::dragonbox::ieee754_binary_traits<Format, Carrier, int>;
  using Impl = YAML::jkj::dragonbox::detail::impl<FT>;

  using SignPolicy = YAML::jkj::dragonbox::policy::sign::return_sign_t;
  using TrailingZeroPolicy = YAML::jkj::dragonbox::policy::trailing_zero::report_t;
  using IntervalTypeProvider = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;
  using BinaryToDecimalRoundingPolicy = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::do_not_care_t;
  using CachePolicy = YAML::jkj::dragonbox::policy::cache::full_t;
  using PreferredInts = YAML::jkj::dragonbox::policy::preferred_integer_types::match_t;

  auto round_trip_check = [&](T v) {
    const auto bits = BitCastToUInt(v);

    YAML::jkj::dragonbox::float_bits<FT> fb(static_cast<Carrier>(bits));
    const auto exponent_bits = fb.extract_exponent_bits();
    const auto s = fb.remove_exponent_bits();

    const auto r = Impl::template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider,
                                                  BinaryToDecimalRoundingPolicy, CachePolicy, PreferredInts>(s, exponent_bits);

    const std::string str = ToENotationString(r);
    const T parsed = ParseENotationTo<T>(str);

    EXPECT_EQ(BitCastToUInt(parsed), BitCastToUInt(v)) << "failed round-trip for: " << str;
  };

  // Boundary conditions:
  // - Smallest positive subnormal (denorm_min)
  // - Largest finite
  round_trip_check(std::numeric_limits<T>::denorm_min());
  round_trip_check(std::numeric_limits<T>::max());
}

TEST(DragonboxImplSignPolicyTest_406, ComputeNearest_WithIgnoreSignPolicyProducesNonSignedDecimalFp_406) {
  using FT = YAML::jkj::dragonbox::ieee754_binary_traits<
      YAML::jkj::dragonbox::ieee754_binary32, std::uint_least32_t, int>;
  using Impl = YAML::jkj::dragonbox::detail::impl<FT>;

  using SignPolicy = YAML::jkj::dragonbox::policy::sign::ignore_t;
  using TrailingZeroPolicy = YAML::jkj::dragonbox::policy::trailing_zero::report_t;
  using IntervalTypeProvider = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;
  using BinaryToDecimalRoundingPolicy = YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::do_not_care_t;
  using CachePolicy = YAML::jkj::dragonbox::policy::cache::full_t;
  using PreferredInts = YAML::jkj::dragonbox::policy::preferred_integer_types::match_t;

  // Use a negative value; ignore_t should not expose sign in the return type.
  const float v = -1.25f;
  const auto bits = BitCastToUInt(v);

  YAML::jkj::dragonbox::float_bits<FT> fb(static_cast<std::uint_least32_t>(bits));
  const auto exponent_bits = fb.extract_exponent_bits();
  const auto s = fb.remove_exponent_bits();

  const auto r = Impl::template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider,
                                                BinaryToDecimalRoundingPolicy, CachePolicy, PreferredInts>(s, exponent_bits);

  // Verification of external interactions (observable via return type):
  // ignore_t means return_has_sign == false, so decimal_fp specialization should not have `is_negative`.
  static_assert(!SignPolicy::return_has_sign, "Test expects ignore_t to not return sign.");
  static_assert(!requires { r.is_negative; }, "decimal_fp should not expose is_negative when sign is ignored.");

  // Still should be parsable and round-trip in magnitude.
  const std::string str = ToENotationString(r);
  const float parsed = ParseENotationTo<float>(str);
  EXPECT_EQ(BitCastToUInt(parsed), BitCastToUInt(static_cast<float>(+1.25f)))
      << "ignore sign policy should behave like magnitude-only: " << str;
}