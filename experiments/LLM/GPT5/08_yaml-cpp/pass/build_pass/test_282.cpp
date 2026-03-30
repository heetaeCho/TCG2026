// TEST_ID: 282
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <typename Float>
using Traits282 = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<Float>;

template <typename Float>
using Carrier282 =
    decltype(Traits282<Float>::float_to_carrier(std::declval<Float>()));

template <typename UInt>
constexpr UInt MakeAlternatingPattern282(bool start_with_one) {
  // Builds a pattern like 1010... or 0101... across the full bit-width of UInt.
  UInt v = 0;
  const int bits = std::numeric_limits<UInt>::digits;
  for (int i = 0; i < bits; ++i) {
    const bool set = ((i % 2) == 0) ? start_with_one : !start_with_one;
    if (set) v |= (UInt{1} << i);
  }
  return v;
}

template <typename UInt>
constexpr UInt HighBit282() {
  constexpr int bits = std::numeric_limits<UInt>::digits;
  return (bits > 0) ? (UInt{1} << (bits - 1)) : UInt{0};
}

template <typename Float>
class DefaultFloatBitCarrierConversionTraitsTest_282 : public ::testing::Test {};

using TestFloats282 = ::testing::Types<float, double>;
TYPED_TEST_SUITE(DefaultFloatBitCarrierConversionTraitsTest_282, TestFloats282);

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_282,
           CarrierToFloatIsNoexcept_282) {
  using Float = TypeParam;
  using Traits = Traits282<Float>;
  using Carrier = Carrier282<Float>;

  static_assert(noexcept(Traits::carrier_to_float(std::declval<Carrier>())),
                "carrier_to_float must be noexcept");
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_282,
           RoundTripPreservesCarrierBits_CommonPatterns_282) {
  using Float = TypeParam;
  using Traits = Traits282<Float>;
  using Carrier = Carrier282<Float>;

  const Carrier patterns[] = {
      Carrier{0},
      Carrier{1},
      HighBit282<Carrier>(),
      std::numeric_limits<Carrier>::max(),
      MakeAlternatingPattern282<Carrier>(true),
      MakeAlternatingPattern282<Carrier>(false),
  };

  for (Carrier c : patterns) {
    const Float f = Traits::carrier_to_float(c);
    const Carrier back = Traits::float_to_carrier(f);
    EXPECT_EQ(back, c) << "Carrier pattern was not preserved on round-trip.";
  }
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_282,
           CarrierToFloatMatchesFloatToCarrierForFiniteValues_282) {
  using Float = TypeParam;
  using Traits = Traits282<Float>;

  const Float values[] = {
      Float{0},
      -Float{0},
      Float{1},
      -Float{1},
      std::numeric_limits<Float>::min(),
      std::numeric_limits<Float>::max(),
      std::numeric_limits<Float>::denorm_min(),
  };

  for (Float v : values) {
    const auto c = Traits::float_to_carrier(v);
    const Float out = Traits::carrier_to_float(c);

    // For finite non-NaN values, equality is observable and appropriate.
    EXPECT_EQ(out, v);
    // Also ensure bit-pattern stays stable under convert-back.
    EXPECT_EQ(Traits::float_to_carrier(out), c);
  }
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_282,
           CarrierToFloatHandlesInfinities_282) {
  using Float = TypeParam;
  using Traits = Traits282<Float>;

  const Float pos_inf = std::numeric_limits<Float>::infinity();
  const Float neg_inf = -std::numeric_limits<Float>::infinity();

  const auto c_pos = Traits::float_to_carrier(pos_inf);
  const auto c_neg = Traits::float_to_carrier(neg_inf);

  const Float out_pos = Traits::carrier_to_float(c_pos);
  const Float out_neg = Traits::carrier_to_float(c_neg);

  EXPECT_TRUE(std::isinf(out_pos));
  EXPECT_FALSE(std::signbit(out_pos));

  EXPECT_TRUE(std::isinf(out_neg));
  EXPECT_TRUE(std::signbit(out_neg));

  EXPECT_EQ(Traits::float_to_carrier(out_pos), c_pos);
  EXPECT_EQ(Traits::float_to_carrier(out_neg), c_neg);
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_282,
           CarrierToFloatHandlesNaNs_RoundTripPreservesCarrier_282) {
  using Float = TypeParam;
  using Traits = Traits282<Float>;
  using Carrier = Carrier282<Float>;

  // Create a few "likely-NaN" carriers without assuming a specific IEEE layout:
  // We start from an arbitrary carrier pattern, convert to float, then assert
  // that converting back preserves the original carrier bits (observable behavior
  // via the public API).
  const Carrier patterns[] = {
      MakeAlternatingPattern282<Carrier>(true),
      MakeAlternatingPattern282<Carrier>(false),
      std::numeric_limits<Carrier>::max(),
  };

  for (Carrier c : patterns) {
    const Float f = Traits::carrier_to_float(c);
    const Carrier back = Traits::float_to_carrier(f);
    EXPECT_EQ(back, c) << "NaN/bit-pattern carrier was not preserved.";
    // If it happens to be NaN, it must at least be NaN.
    if (std::isnan(f)) {
      EXPECT_TRUE(std::isnan(Traits::carrier_to_float(c)));
    }
  }

  // Also check behavior when starting from a standard quiet NaN value.
  const Float qnan = std::numeric_limits<Float>::quiet_NaN();
  const auto c_qnan = Traits::float_to_carrier(qnan);
  const Float out = Traits::carrier_to_float(c_qnan);
  EXPECT_TRUE(std::isnan(out));
  EXPECT_EQ(Traits::float_to_carrier(out), c_qnan);
}

}  // namespace