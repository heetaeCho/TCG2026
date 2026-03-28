// TEST_ID: 408
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using ::YAML::jkj::dragonbox::detail::impl;

// ------------------------
// Small C++20 detection helpers
// ------------------------
template <class T>
concept HasMemberSignificand = requires(T v) { v.significand; };

template <class T>
concept HasMemberExponent = requires(T v) { v.exponent; };

template <class T>
concept HasMemberIsNegative = requires(T v) { v.is_negative; };

template <class T>
concept HasMemberNegative = requires(T v) { v.negative; };

template <class T>
static long double Pow10LD(int e) {
  // Avoid std::pow overload ambiguities; long double pow is fine for tests.
  return std::pow((long double)10.0, (long double)e);
}

template <class DecimalFP>
static long double DecimalToLongDouble(const DecimalFP& fp) {
  static_assert(HasMemberSignificand<DecimalFP>, "return_type must expose .significand");
  static_assert(HasMemberExponent<DecimalFP>, "return_type must expose .exponent");

  using SigT = std::remove_cvref_t<decltype(fp.significand)>;
  long double s = static_cast<long double>(fp.significand);
  long double v = s * Pow10LD<DecimalFP>(static_cast<int>(fp.exponent));

  if constexpr (HasMemberIsNegative<DecimalFP>) {
    if (fp.is_negative) v = -v;
  } else if constexpr (HasMemberNegative<DecimalFP>) {
    if (fp.negative) v = -v;
  } else if constexpr (std::is_signed_v<SigT>) {
    // If significand itself carries sign, v already has it.
  } else {
    // No explicit sign channel detected; assume v is already correct.
  }
  return v;
}

// ------------------------
// IEEE-754 decomposition to build (signed_significand_bits, exponent_bits)
// without relying on private state.
// ------------------------
template <class FormatTraits, class Float>
struct FloatBits;

template <class FormatTraits>
struct FloatBits<FormatTraits, float> {
  using UInt = std::uint32_t;
  static UInt ToUInt(float x) noexcept {
    UInt u{};
    static_assert(sizeof(u) == sizeof(x));
    std::memcpy(&u, &x, sizeof(u));
    return u;
  }
};

template <class FormatTraits>
struct FloatBits<FormatTraits, double> {
  using UInt = std::uint64_t;
  static UInt ToUInt(double x) noexcept {
    UInt u{};
    static_assert(sizeof(u) == sizeof(x));
    std::memcpy(&u, &x, sizeof(u));
    return u;
  }
};

template <class FormatTraits, class Float>
static auto MakeInputFromFloat(Float x) {
  using format = typename FormatTraits::format;
  using carrier_uint = typename FormatTraits::carrier_uint;

  const auto raw = FloatBits<FormatTraits, Float>::ToUInt(x);

  constexpr int significand_bits = format::significand_bits;
  constexpr int exponent_bits_count = format::exponent_bits;

  // Layout assumed IEEE-754 binary interchange:
  // sign: 1 bit (MSB), exponent: exponent_bits_count, significand: significand_bits.
  const carrier_uint sign =
      carrier_uint((raw >> (significand_bits + exponent_bits_count)) & 1u);

  const carrier_uint exp_mask =
      (carrier_uint(1) << exponent_bits_count) - carrier_uint(1);

  const carrier_uint sig_mask =
      (carrier_uint(1) << significand_bits) - carrier_uint(1);

  const carrier_uint exponent_bits =
      carrier_uint((raw >> significand_bits) & exp_mask);

  const carrier_uint significand =
      carrier_uint(raw & sig_mask);

  // Construct signed_significand_bits<FormatTraits>.
  // We intentionally use brace-init to be resilient to constructor signatures.
  ::YAML::jkj::dragonbox::detail::signed_significand_bits<FormatTraits> s{
      significand, static_cast<bool>(sign)};

  return std::pair{s, static_cast<::YAML::jkj::dragonbox::detail::exponent_int>(exponent_bits)};
}

// ------------------------
// Policy selection
// We use existing policies from the header (no reimplementation).
// ------------------------
namespace policy = ::YAML::jkj::dragonbox::policy;

// If your integration uses different names, these aliases are the only thing
// you should need to tweak (tests otherwise stay black-box).
using SignPolicy = policy::sign::return_sign;
using TrailingZeroPolicy = policy::trailing_zero::remove;
using CachePolicy = policy::cache::full;
using PreferredInts = policy::preferred_integer_types::standard;

// ------------------------
// A typed fixture over float/double
// ------------------------
template <class T>
struct RightClosedDirectedTest_408 : ::testing::Test {};

using TestedTypes_408 = ::testing::Types<float, double>;
TYPED_TEST_SUITE(RightClosedDirectedTest_408, TestedTypes_408);

template <class Float>
using TraitsFor =
    ::YAML::jkj::dragonbox::default_float_traits<Float>;

}  // namespace

// ------------------------
// Tests (TEST_ID appended)
// ------------------------

TYPED_TEST(RightClosedDirectedTest_408, ZeroAndNegativeZeroBracketCorrectly_408) {
  using Float = TypeParam;
  using Traits = TraitsFor<Float>;
  using Impl = impl<Traits>;

  for (Float x : {Float(0.0), Float(-0.0)}) {
    auto [s, e] = MakeInputFromFloat<Traits>(x);

    const auto left = Impl::template compute_left_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

    const auto right = Impl::template compute_right_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

    const long double v_left = DecimalToLongDouble(left);
    const long double v_right = DecimalToLongDouble(right);
    const long double v_exact = static_cast<long double>(x);

    // For zero/-zero we at least expect the directed interval to contain the exact value.
    const long double lo = std::min(v_left, v_right);
    const long double hi = std::max(v_left, v_right);
    EXPECT_LE(lo, v_exact);
    EXPECT_GE(hi, v_exact);
  }
}

TYPED_TEST(RightClosedDirectedTest_408, BracketsCommonFiniteValues_408) {
  using Float = TypeParam;
  using Traits = TraitsFor<Float>;
  using Impl = impl<Traits>;

  // A variety of “normal” values.
  const Float values[] = {
      Float(1.0),
      Float(-1.0),
      Float(0.5),
      Float(-0.5),
      Float(2.0),
      Float(10.0),
      Float(123.25),
      Float(-123.25),
      std::numeric_limits<Float>::min(),        // smallest positive normal
      -std::numeric_limits<Float>::min(),
      std::numeric_limits<Float>::max() / Float(2),
  };

  for (Float x : values) {
    auto [s, e] = MakeInputFromFloat<Traits>(x);

    const auto left = Impl::template compute_left_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

    const auto right = Impl::template compute_right_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

    const long double v_left = DecimalToLongDouble(left);
    const long double v_right = DecimalToLongDouble(right);
    const long double v_exact = static_cast<long double>(x);

    const long double lo = std::min(v_left, v_right);
    const long double hi = std::max(v_left, v_right);

    // Black-box invariant: left-closed and right-closed directed computations
    // should produce an interval that contains the exact value.
    EXPECT_LE(lo, v_exact) << "x=" << static_cast<double>(x);
    EXPECT_GE(hi, v_exact) << "x=" << static_cast<double>(x);
  }
}

TYPED_TEST(RightClosedDirectedTest_408, BracketsSubnormalValuesWhenSupported_408) {
  using Float = TypeParam;
  using Traits = TraitsFor<Float>;
  using Impl = impl<Traits>;

  // Some platforms support denormals; if they flush-to-zero, this test still
  // behaves like the zero-bracketing case.
  const Float denorm_min = std::numeric_limits<Float>::denorm_min();
  const Float vals[] = {denorm_min, -denorm_min};

  for (Float x : vals) {
    auto [s, e] = MakeInputFromFloat<Traits>(x);

    const auto left = Impl::template compute_left_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

    const auto right = Impl::template compute_right_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

    const long double v_left = DecimalToLongDouble(left);
    const long double v_right = DecimalToLongDouble(right);
    const long double v_exact = static_cast<long double>(x);

    const long double lo = std::min(v_left, v_right);
    const long double hi = std::max(v_left, v_right);
    EXPECT_LE(lo, v_exact);
    EXPECT_GE(hi, v_exact);
  }
}

TYPED_TEST(RightClosedDirectedTest_408, DeterministicForSameInput_408) {
  using Float = TypeParam;
  using Traits = TraitsFor<Float>;
  using Impl = impl<Traits>;

  const Float x = Float(3.1415926535897932384626L);

  auto [s, e] = MakeInputFromFloat<Traits>(x);

  const auto r1 = Impl::template compute_right_closed_directed<
      SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

  const auto r2 = Impl::template compute_right_closed_directed<
      SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);

  // Observable black-box determinism: identical inputs => identical outputs.
  ASSERT_TRUE(HasMemberSignificand<decltype(r1)>);
  ASSERT_TRUE(HasMemberExponent<decltype(r1)>);

  EXPECT_EQ(r1.significand, r2.significand);
  EXPECT_EQ(r1.exponent, r2.exponent);

  if constexpr (HasMemberIsNegative<decltype(r1)>) {
    EXPECT_EQ(r1.is_negative, r2.is_negative);
  } else if constexpr (HasMemberNegative<decltype(r1)>) {
    EXPECT_EQ(r1.negative, r2.negative);
  }
}

TYPED_TEST(RightClosedDirectedTest_408, IntervalOrderingIsConsistentAroundNextafter_408) {
  using Float = TypeParam;
  using Traits = TraitsFor<Float>;
  using Impl = impl<Traits>;

  // Pick a value and its neighbors; the directed interval should shift consistently.
  const Float x = Float(1.0);
  const Float up = std::nextafter(x, std::numeric_limits<Float>::infinity());
  const Float down = std::nextafter(x, -std::numeric_limits<Float>::infinity());

  auto eval_right = [&](Float v) {
    auto [s, e] = MakeInputFromFloat<Traits>(v);
    const auto r = Impl::template compute_right_closed_directed<
        SignPolicy, TrailingZeroPolicy, CachePolicy, PreferredInts>(s, e);
    return DecimalToLongDouble(r);
  };

  const long double vr_down = eval_right(down);
  const long double vr_x = eval_right(x);
  const long double vr_up = eval_right(up);

  // We avoid assuming exact rounding semantics; we only assert the mapping is not “wildly”
  // non-monotonic in a tiny neighborhood.
  const long double lo = std::min({vr_down, vr_x, vr_up});
  const long double hi = std::max({vr_down, vr_x, vr_up});

  EXPECT_LE(lo, static_cast<long double>(up));
  EXPECT_GE(hi, static_cast<long double>(down));
}