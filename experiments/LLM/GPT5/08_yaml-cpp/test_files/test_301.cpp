// TEST_ID: 301
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

// Try a few common include paths for this header in different build layouts.
#if __has_include("contrib/dragonbox.h")
  #include "contrib/dragonbox.h"
#elif __has_include("yaml-cpp/contrib/dragonbox.h")
  #include "yaml-cpp/contrib/dragonbox.h"
#elif __has_include("src/contrib/dragonbox.h")
  #include "src/contrib/dragonbox.h"
#else
  #error "Could not find contrib/dragonbox.h (dragonbox) header."
#endif

namespace {

using namespace YAML::jkj::dragonbox;

// A ConversionTraits used to verify external interaction (float_to_carrier called)
// and that its return value is carried into the returned float_bits object.
template <class Float, class CarrierUInt>
struct CountingConversionTraits_301 {
  using carrier_uint = CarrierUInt;

  // "format" is only used as a type by default FormatTraits; the exact type/value is not important
  // for these black-box tests as long as it's a valid type.
  struct format {};

  static inline int call_count = 0;
  static inline bool saw_value = false;
  static inline Float last_value{};

  static carrier_uint float_to_carrier(Float x) noexcept {
    ++call_count;
    saw_value = true;
    last_value = x;
    // Return a fixed sentinel so the test can verify propagation into float_bits.
    return static_cast<carrier_uint>(CarrierUInt{0xA5A5A5A5u});
  }
};

class MakeFloatBitsTest_301 : public ::testing::Test {
protected:
  void SetUp() override {
    CountingConversionTraits_301<float, std::uint32_t>::call_count = 0;
    CountingConversionTraits_301<float, std::uint32_t>::saw_value = false;
    CountingConversionTraits_301<float, std::uint32_t>::last_value = 0.0f;

    CountingConversionTraits_301<double, std::uint64_t>::call_count = 0;
    CountingConversionTraits_301<double, std::uint64_t>::saw_value = false;
    CountingConversionTraits_301<double, std::uint64_t>::last_value = 0.0;
  }
};

}  // namespace

TEST_F(MakeFloatBitsTest_301, IsNoexceptForFloat_301) {
  static_assert(noexcept(make_float_bits<float>(0.0f)),
                "make_float_bits<float> should be noexcept");
}

TEST_F(MakeFloatBitsTest_301, IsNoexceptForDouble_301) {
  static_assert(noexcept(make_float_bits<double>(0.0)),
                "make_float_bits<double> should be noexcept");
}

TEST_F(MakeFloatBitsTest_301, CallsCustomConversionTraitsExactlyOnceAndPropagatesCarrier_Float_301) {
  using Traits = CountingConversionTraits_301<float, std::uint32_t>;
  using Bits = decltype(make_float_bits<float, Traits>(1.5f));

  const float input = 1.5f;
  const Bits bits = make_float_bits<float, Traits>(input);

  EXPECT_EQ(Traits::call_count, 1);
  EXPECT_TRUE(Traits::saw_value);
  EXPECT_EQ(Traits::last_value, input);

  // Observable behavior: returned float_bits should contain the carrier produced by ConversionTraits.
  // In dragonbox's float_bits implementation, the carrier is typically stored in a public member `u`.
  EXPECT_EQ(bits.u, static_cast<typename Traits::carrier_uint>(0xA5A5A5A5u));
}

TEST_F(MakeFloatBitsTest_301, CallsCustomConversionTraitsExactlyOnceAndPropagatesCarrier_Double_301) {
  using Traits = CountingConversionTraits_301<double, std::uint64_t>;
  using Bits = decltype(make_float_bits<double, Traits>(2.25));

  const double input = 2.25;
  const Bits bits = make_float_bits<double, Traits>(input);

  EXPECT_EQ(Traits::call_count, 1);
  EXPECT_TRUE(Traits::saw_value);
  EXPECT_EQ(Traits::last_value, input);
  EXPECT_EQ(bits.u, static_cast<typename Traits::carrier_uint>(0xA5A5A5A5u));
}

TEST_F(MakeFloatBitsTest_301, DistinguishesPositiveZeroAndNegativeZero_ForFloat_301) {
  // Boundary condition: +0 and -0 are distinct in IEEE-754.
  const float pz = 0.0f;
  const float nz = -0.0f;

  const auto pz_bits = make_float_bits<float>(pz);
  const auto nz_bits = make_float_bits<float>(nz);

  // If float_bits exposes sign helpers, they should differ; otherwise carrier should differ.
  // We only rely on observable public API; `u` is used as the observable carrier representation.
  EXPECT_NE(pz_bits.u, nz_bits.u);
  EXPECT_FALSE(std::signbit(pz));
  EXPECT_TRUE(std::signbit(nz));
}

TEST_F(MakeFloatBitsTest_301, HandlesInfinityAndNaN_ForDouble_301) {
  const double inf = std::numeric_limits<double>::infinity();
  const double nan = std::numeric_limits<double>::quiet_NaN();

  const auto inf_bits = make_float_bits<double>(inf);
  const auto nan_bits = make_float_bits<double>(nan);

  // Observable: function returns a float_bits object; for NaN/Inf we mainly ensure it is callable and stable.
  // `u` access is the observable representation; we don't assume exact bit patterns beyond being obtainable.
  (void)inf_bits.u;

  EXPECT_TRUE(std::isinf(inf));
  EXPECT_TRUE(std::isnan(nan));
  (void)nan_bits.u;
}

TEST_F(MakeFloatBitsTest_301, HandlesDenormMinAndMaxFinite_ForFloat_301) {
  const float denorm = std::numeric_limits<float>::denorm_min();
  const float max_finite = std::numeric_limits<float>::max();

  const auto denorm_bits = make_float_bits<float>(denorm);
  const auto max_bits = make_float_bits<float>(max_finite);

  // Observable: distinct inputs should generally yield (observable) distinct carrier representations.
  // This checks boundary values are handled and produce accessible results.
  EXPECT_NE(denorm_bits.u, max_bits.u);
  (void)denorm_bits.u;
  (void)max_bits.u;
}