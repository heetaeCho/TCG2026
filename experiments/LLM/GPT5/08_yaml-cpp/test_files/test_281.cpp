// TEST_ID: 281
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <typename Float>
class DefaultFloatBitCarrierConversionTraitsTest_281 : public ::testing::Test {};

using TestedFloats_281 = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(DefaultFloatBitCarrierConversionTraitsTest_281, TestedFloats_281);

// Helper: run a round-trip purely via the public interface, comparing carrier values.
// This avoids relying on Float equality (e.g., NaNs) and avoids inspecting private state.
template <typename Float>
void ExpectCarrierRoundTrip_281(Float x) {
  using Traits = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<Float>;
  const auto c1 = Traits::float_to_carrier(x);
  const Float y = Traits::carrier_to_float(c1);
  const auto c2 = Traits::float_to_carrier(y);
  EXPECT_EQ(c1, c2);
}

}  // namespace

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_281, FunctionsAreNoexcept_281) {
  using Float = TypeParam;
  using Traits = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<Float>;

  static_assert(noexcept(Traits::float_to_carrier(std::declval<Float>())),
                "float_to_carrier should be noexcept");
  static_assert(noexcept(Traits::carrier_to_float(std::declval<decltype(Traits::float_to_carrier(
                              std::declval<Float>()))>())),
                "carrier_to_float should be noexcept");
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_281, RoundTripPreservesCarrierForCommonFiniteValues_281) {
  using Float = TypeParam;

  // Normal operation: typical finite values.
  ExpectCarrierRoundTrip_281<Float>(Float{0});
  ExpectCarrierRoundTrip_281<Float>(Float{1});
  ExpectCarrierRoundTrip_281<Float>(Float{-1});
  ExpectCarrierRoundTrip_281<Float>(Float{2});
  ExpectCarrierRoundTrip_281<Float>(Float{-2});
  ExpectCarrierRoundTrip_281<Float>(Float{123.5});
  ExpectCarrierRoundTrip_281<Float>(Float{-9876.25});
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_281, RoundTripPreservesCarrierForBoundaryMagnitudes_281) {
  using Float = TypeParam;
  const auto lim = std::numeric_limits<Float>{};

  // Boundary conditions: min/max, smallest normal, and denorm min when available.
  if (std::numeric_limits<Float>::is_iec559) {
    ExpectCarrierRoundTrip_281<Float>(lim.min());        // smallest positive normal
    ExpectCarrierRoundTrip_281<Float>(lim.max());        // largest finite
    ExpectCarrierRoundTrip_281<Float>(lim.lowest());     // most negative finite
    ExpectCarrierRoundTrip_281<Float>(lim.epsilon());    // smallest increment around 1
    ExpectCarrierRoundTrip_281<Float>(-lim.epsilon());
  } else {
    // Even if not IEC559, the trait should still round-trip its own carrier.
    ExpectCarrierRoundTrip_281<Float>(lim.min());
    ExpectCarrierRoundTrip_281<Float>(lim.max());
    ExpectCarrierRoundTrip_281<Float>(lim.lowest());
  }

  if (lim.has_denorm == std::denorm_present) {
    ExpectCarrierRoundTrip_281<Float>(lim.denorm_min());
    ExpectCarrierRoundTrip_281<Float>(-lim.denorm_min());
  }
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_281, RoundTripPreservesCarrierForSignedZero_281) {
  using Float = TypeParam;

  // Boundary condition: +0 and -0.
  // We don't assume their carriers differ; we only assert each round-trips its own carrier.
  const Float pz = Float{0};
  const Float nz = -Float{0};

  ExpectCarrierRoundTrip_281<Float>(pz);
  ExpectCarrierRoundTrip_281<Float>(nz);
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_281, RoundTripPreservesCarrierForInfinitiesWhenAvailable_281) {
  using Float = TypeParam;
  const auto lim = std::numeric_limits<Float>{};

  if (lim.has_infinity) {
    ExpectCarrierRoundTrip_281<Float>(lim.infinity());
    ExpectCarrierRoundTrip_281<Float>(-lim.infinity());
  } else {
    GTEST_SKIP() << "Infinity not supported for this Float type";
  }
}

TYPED_TEST(DefaultFloatBitCarrierConversionTraitsTest_281, RoundTripPreservesCarrierForNaNsWhenAvailable_281) {
  using Float = TypeParam;
  const auto lim = std::numeric_limits<Float>{};

  if (lim.has_quiet_NaN) {
    const Float qnan = lim.quiet_NaN();
    ExpectCarrierRoundTrip_281<Float>(qnan);
  } else {
    GTEST_SKIP() << "quiet_NaN not supported for this Float type";
  }

  if (lim.has_signaling_NaN) {
    const Float snan = lim.signaling_NaN();
    ExpectCarrierRoundTrip_281<Float>(snan);
  } else {
    // Not all platforms expose signaling NaNs reliably.
    SUCCEED();
  }
}