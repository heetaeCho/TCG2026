// File: dragonbox_float_bits_is_negative_test.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

// A runtime-observable traits type to verify that float_bits::is_negative()
// forwards the stored carrier value to format_traits::is_negative().
struct RecordingFormatTraits_297 {
  using carrier_uint = std::uint32_t;
  using exponent_int = int;

  static inline int call_count = 0;
  static inline carrier_uint last_arg = 0;

  static bool is_negative(carrier_uint u) noexcept {
    ++call_count;
    last_arg = u;
    // Define "negative" as MSB=1 for the purpose of this test traits.
    return (u & 0x80000000u) != 0;
  }
};

// A constexpr-friendly traits type so we can static_assert on constexpr behavior.
struct ConstexprFormatTraits_297 {
  using carrier_uint = std::uint32_t;
  using exponent_int = int;

  static constexpr bool is_negative(carrier_uint u) noexcept {
    return (u & 0x80000000u) != 0;
  }
};

template <typename Traits>
using FloatBits = YAML::jkj::dragonbox::float_bits<Traits>;

class FloatBitsIsNegativeTest_297 : public ::testing::Test {
 protected:
  void SetUp() override {
    RecordingFormatTraits_297::call_count = 0;
    RecordingFormatTraits_297::last_arg = 0;
  }
};

TEST_F(FloatBitsIsNegativeTest_297, DelegatesToFormatTraitsAndPassesStoredValue_297) {
  using Traits = RecordingFormatTraits_297;
  using Bits = FloatBits<Traits>;

  const Traits::carrier_uint pattern = 0x12345678u;
  Bits bits(pattern);

  EXPECT_EQ(Traits::call_count, 0);
  const bool result = bits.is_negative();

  EXPECT_EQ(Traits::call_count, 1);
  EXPECT_EQ(Traits::last_arg, pattern);
  EXPECT_FALSE(result);  // MSB not set in 0x12345678.
}

TEST_F(FloatBitsIsNegativeTest_297, ReturnsTrueWhenTraitsReportsNegative_MsbSet_297) {
  using Traits = RecordingFormatTraits_297;
  using Bits = FloatBits<Traits>;

  const Traits::carrier_uint pattern = 0x80000000u;  // MSB set.
  Bits bits(pattern);

  EXPECT_TRUE(bits.is_negative());
  EXPECT_EQ(Traits::last_arg, pattern);
}

TEST_F(FloatBitsIsNegativeTest_297, ReturnsFalseWhenTraitsReportsNotNegative_ZeroPattern_297) {
  using Traits = RecordingFormatTraits_297;
  using Bits = FloatBits<Traits>;

  const Traits::carrier_uint pattern = 0x00000000u;
  Bits bits(pattern);

  EXPECT_FALSE(bits.is_negative());
  EXPECT_EQ(Traits::last_arg, pattern);
}

TEST_F(FloatBitsIsNegativeTest_297, Boundary_MaxCarrierValueBehavesAccordingToTraits_297) {
  using Traits = RecordingFormatTraits_297;
  using Bits = FloatBits<Traits>;

  const Traits::carrier_uint pattern = 0xFFFFFFFFu;  // MSB set => negative per traits.
  Bits bits(pattern);

  EXPECT_TRUE(bits.is_negative());
  EXPECT_EQ(Traits::last_arg, pattern);
}

TEST_F(FloatBitsIsNegativeTest_297, MultipleCallsForwardEachTime_297) {
  using Traits = RecordingFormatTraits_297;
  using Bits = FloatBits<Traits>;

  Bits bits1(0x7FFFFFFFu);
  Bits bits2(0x80000001u);

  EXPECT_FALSE(bits1.is_negative());
  EXPECT_EQ(Traits::call_count, 1);
  EXPECT_EQ(Traits::last_arg, 0x7FFFFFFFu);

  EXPECT_TRUE(bits2.is_negative());
  EXPECT_EQ(Traits::call_count, 2);
  EXPECT_EQ(Traits::last_arg, 0x80000001u);

  EXPECT_FALSE(bits1.is_negative());
  EXPECT_EQ(Traits::call_count, 3);
  EXPECT_EQ(Traits::last_arg, 0x7FFFFFFFu);
}

// ---- Compile-time / type-property checks (observable via compilation) ----

TEST(FloatBitsIsNegativePropertiesTest_297, IsNoexcept_297) {
  using Bits = FloatBits<ConstexprFormatTraits_297>;
  Bits bits(0u);
  static_assert(noexcept(bits.is_negative()),
                "float_bits::is_negative() must be noexcept per interface.");
  (void)bits;
}

TEST(FloatBitsIsNegativePropertiesTest_297, CanBeEvaluatedInConstantExpressionWithConstexprTraits_297) {
  using Bits = FloatBits<ConstexprFormatTraits_297>;

  // If float_bits::is_negative is truly constexpr-capable (as declared),
  // this should compile and be evaluatable at compile time.
  constexpr Bits pos_bits(0x00000000u);
  constexpr Bits neg_bits(0x80000000u);

  static_assert(!pos_bits.is_negative(), "Expected non-negative for MSB=0.");
  static_assert(neg_bits.is_negative(), "Expected negative for MSB=1.");
}

}  // namespace