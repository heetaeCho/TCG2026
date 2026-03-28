// TEST_ID: 295
#include <gtest/gtest.h>

#include <cstdint>

#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// A constexpr-friendly traits type for compile-time checks.
struct ConstexprFormatTraits_295 {
  using carrier_uint = std::uint32_t;
  using exponent_int = int;

  // Provide common IEEE-754 binary32-like constants in case dragonbox.h
  // references them in inline member function definitions.
  static constexpr int carrier_bits = 32;
  static constexpr int exponent_bits = 8;
  static constexpr int significand_bits = 23;
  static constexpr int exponent_bias = 127;

  static constexpr carrier_uint sign_mask = carrier_uint{0x80000000u};
  static constexpr carrier_uint exponent_mask = carrier_uint{0x7F800000u};
  static constexpr carrier_uint significand_mask = carrier_uint{0x007FFFFFu};

  static constexpr bool is_nonzero(carrier_uint v) noexcept { return v != 0; }
};

// A tracking traits type to verify external interaction (forwarding argument).
struct TrackingFormatTraits_295 {
  using carrier_uint = std::uint32_t;
  using exponent_int = int;

  static constexpr int carrier_bits = 32;
  static constexpr int exponent_bits = 8;
  static constexpr int significand_bits = 23;
  static constexpr int exponent_bias = 127;

  static constexpr carrier_uint sign_mask = carrier_uint{0x80000000u};
  static constexpr carrier_uint exponent_mask = carrier_uint{0x7F800000u};
  static constexpr carrier_uint significand_mask = carrier_uint{0x007FFFFFu};

  static inline int calls = 0;
  static inline carrier_uint last_arg = 0;

  static bool is_nonzero(carrier_uint v) noexcept {
    ++calls;
    last_arg = v;
    return v != 0;
  }

  static void Reset() {
    calls = 0;
    last_arg = 0;
  }
};

using FloatBitsConstexpr_295 = float_bits<ConstexprFormatTraits_295>;
using FloatBitsTracking_295 = float_bits<TrackingFormatTraits_295>;

// Compile-time (constexpr) behavior checks for is_nonzero().
static_assert(!FloatBitsConstexpr_295(0u).is_nonzero(),
              "0 bit-pattern should be reported as zero");
static_assert(FloatBitsConstexpr_295(1u).is_nonzero(),
              "non-zero bit-pattern should be reported as nonzero");

class FloatBitsIsNonzeroTest_295 : public ::testing::Test {
 protected:
  void SetUp() override { TrackingFormatTraits_295::Reset(); }
};

TEST_F(FloatBitsIsNonzeroTest_295, ZeroPatternReturnsFalse_295) {
  const FloatBitsTracking_295 fb(0u);

  EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_295, NonZeroPatternReturnsTrue_295) {
  const FloatBitsTracking_295 fb(1u);

  EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_295, BoundaryMaxCarrierUintIsNonZero_295) {
  const TrackingFormatTraits_295::carrier_uint max_v =
      static_cast<TrackingFormatTraits_295::carrier_uint>(~0u);
  const FloatBitsTracking_295 fb(max_v);

  EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_295, BoundaryHighBitOnlyIsNonZero_295) {
  const TrackingFormatTraits_295::carrier_uint high_bit =
      TrackingFormatTraits_295::sign_mask;  // 0x80000000
  const FloatBitsTracking_295 fb(high_bit);

  EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_295, ForwardsStoredBitPatternToFormatTraits_295) {
  const TrackingFormatTraits_295::carrier_uint pattern = 0x12345678u;
  const FloatBitsTracking_295 fb(pattern);

  (void)fb.is_nonzero();

  EXPECT_EQ(TrackingFormatTraits_295::calls, 1);
  EXPECT_EQ(TrackingFormatTraits_295::last_arg, pattern);
}

TEST_F(FloatBitsIsNonzeroTest_295, MultipleCallsInvokeFormatTraitsEachTime_295) {
  const TrackingFormatTraits_295::carrier_uint pattern = 0x00000001u;
  const FloatBitsTracking_295 fb(pattern);

  EXPECT_TRUE(fb.is_nonzero());
  EXPECT_TRUE(fb.is_nonzero());
  EXPECT_TRUE(fb.is_nonzero());

  EXPECT_EQ(TrackingFormatTraits_295::calls, 3);
  EXPECT_EQ(TrackingFormatTraits_295::last_arg, pattern);
}

}  // namespace