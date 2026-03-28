// TEST_ID: 285
// File: signed_significand_bits_is_negative_test_285.cpp

#include <cstdint>
#include <type_traits>

#include "gtest/gtest.h"

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::signed_significand_bits;

// A FormatTraits that lets us verify forwarding + returned value at runtime.
struct RecordingFormatTraits_285 {
  using carrier_uint = std::uint64_t;

  static inline int call_count = 0;
  static inline carrier_uint last_arg = 0;

  static bool is_negative(carrier_uint u) noexcept {
    ++call_count;
    last_arg = u;
    // Arbitrary, test-controlled behavior (NOT inferred from implementation):
    return (u & carrier_uint{1}) != 0;
  }

  static void Reset() noexcept {
    call_count = 0;
    last_arg = 0;
  }
};

// A constexpr-friendly FormatTraits to verify constexpr usability.
struct ConstexprFormatTraits_285 {
  using carrier_uint = std::uint64_t;
  static constexpr bool is_negative(carrier_uint u) noexcept {
    // Arbitrary, deterministic constexpr rule for testing.
    return (u & (carrier_uint{1} << 63)) != 0;
  }
};

// Compile-time check: is_negative is usable in constant expressions (as declared constexpr).
static_assert(!signed_significand_bits<ConstexprFormatTraits_285>(0).is_negative(),
              "is_negative should be constexpr-callable for ConstexprFormatTraits_285");
static_assert(signed_significand_bits<ConstexprFormatTraits_285>(std::uint64_t{1} << 63).is_negative(),
              "is_negative should reflect ConstexprFormatTraits_285 behavior");

}  // namespace

TEST(SignedSignificandBitsIsNegativeTest_285, ReturnsUnderlyingTraitsResult_285) {
  RecordingFormatTraits_285::Reset();

  signed_significand_bits<RecordingFormatTraits_285> a(0);
  EXPECT_FALSE(a.is_negative());

  signed_significand_bits<RecordingFormatTraits_285> b(1);
  EXPECT_TRUE(b.is_negative());
}

TEST(SignedSignificandBitsIsNegativeTest_285, CallsTraitsOnceAndForwardsBitPattern_285) {
  RecordingFormatTraits_285::Reset();

  constexpr std::uint64_t kPattern = 0xDEADBEEFCAFEBABEull;
  signed_significand_bits<RecordingFormatTraits_285> v(kPattern);

  const bool result = v.is_negative();

  EXPECT_EQ(RecordingFormatTraits_285::call_count, 1);
  EXPECT_EQ(RecordingFormatTraits_285::last_arg, kPattern);
  // Also sanity-check that the return equals the traits rule (odd => true).
  EXPECT_EQ(result, (kPattern & 1ull) != 0);
}

TEST(SignedSignificandBitsIsNegativeTest_285, MultipleCallsDelegateEachTime_285) {
  RecordingFormatTraits_285::Reset();

  signed_significand_bits<RecordingFormatTraits_285> v(2);  // even => false under our traits rule
  EXPECT_FALSE(v.is_negative());
  EXPECT_FALSE(v.is_negative());

  EXPECT_EQ(RecordingFormatTraits_285::call_count, 2);
  EXPECT_EQ(RecordingFormatTraits_285::last_arg, 2u);
}

TEST(SignedSignificandBitsIsNegativeTest_285, WorksWithBoundaryValues_285) {
  RecordingFormatTraits_285::Reset();

  signed_significand_bits<RecordingFormatTraits_285> z(0);
  EXPECT_FALSE(z.is_negative());

  // All bits set (max for uint64_t) is odd => true under our traits rule.
  signed_significand_bits<RecordingFormatTraits_285> m(~std::uint64_t{0});
  EXPECT_TRUE(m.is_negative());

  EXPECT_EQ(RecordingFormatTraits_285::call_count, 2);
  EXPECT_EQ(RecordingFormatTraits_285::last_arg, ~std::uint64_t{0});
}