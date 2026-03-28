// TEST_ID: 276
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Include the header under test.
#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::ieee754_binary_traits;

// Minimal “format” types with the required constants used by is_positive().
struct Float32Format {
  static constexpr int significand_bits = 23;
  static constexpr int exponent_bits = 8;
};

struct Float64Format {
  static constexpr int significand_bits = 52;
  static constexpr int exponent_bits = 11;
};

template <typename UInt, int SigBits, int ExpBits>
constexpr UInt SignBitMask() {
  // sign bit is at position (significand_bits + exponent_bits)
  return (UInt(1) << (SigBits + ExpBits));
}

}  // namespace

// ---------- float32-like carrier (uint32_t) ----------

TEST(Ieee754BinaryTraitsIsPositiveTest_276, NoexceptAndConstexpr_276) {
  using Traits = ieee754_binary_traits<Float32Format, std::uint32_t, std::int32_t>;

  static_assert(noexcept(Traits::is_positive(std::uint32_t{0})),
                "is_positive(u) should be noexcept");
  static_assert(Traits::is_positive(std::uint32_t{0}),
                "is_positive should be usable in constant expressions");
}

TEST(Ieee754BinaryTraitsIsPositiveTest_276, ZeroIsPositive_276) {
  using Traits = ieee754_binary_traits<Float32Format, std::uint32_t, std::int32_t>;
  EXPECT_TRUE(Traits::is_positive(std::uint32_t{0}));
}

TEST(Ieee754BinaryTraitsIsPositiveTest_276, BelowSignBitThresholdIsPositive_276) {
  using Traits = ieee754_binary_traits<Float32Format, std::uint32_t, std::int32_t>;

  constexpr std::uint32_t sign_mask = SignBitMask<std::uint32_t, 23, 8>();
  ASSERT_NE(sign_mask, 0u);

  EXPECT_TRUE(Traits::is_positive(sign_mask - 1u));
}

TEST(Ieee754BinaryTraitsIsPositiveTest_276, AtSignBitThresholdIsNotPositive_276) {
  using Traits = ieee754_binary_traits<Float32Format, std::uint32_t, std::int32_t>;

  constexpr std::uint32_t sign_mask = SignBitMask<std::uint32_t, 23, 8>();
  EXPECT_FALSE(Traits::is_positive(sign_mask));
}

TEST(Ieee754BinaryTraitsIsPositiveTest_276, MaxValueIsNotPositive_276) {
  using Traits = ieee754_binary_traits<Float32Format, std::uint32_t, std::int32_t>;
  EXPECT_FALSE(Traits::is_positive(std::numeric_limits<std::uint32_t>::max()));
}

// ---------- float64-like carrier (uint64_t) ----------

TEST(Ieee754BinaryTraitsIsPositiveTest_276, BelowSignBitThresholdIsPositive_Uint64_276) {
  using Traits = ieee754_binary_traits<Float64Format, std::uint64_t, std::int32_t>;

  constexpr std::uint64_t sign_mask = SignBitMask<std::uint64_t, 52, 11>();
  ASSERT_NE(sign_mask, 0ull);

  EXPECT_TRUE(Traits::is_positive(sign_mask - 1ull));
}

TEST(Ieee754BinaryTraitsIsPositiveTest_276, AtSignBitThresholdIsNotPositive_Uint64_276) {
  using Traits = ieee754_binary_traits<Float64Format, std::uint64_t, std::int32_t>;

  constexpr std::uint64_t sign_mask = SignBitMask<std::uint64_t, 52, 11>();
  EXPECT_FALSE(Traits::is_positive(sign_mask));
}

TEST(Ieee754BinaryTraitsIsPositiveTest_276, MaxValueIsNotPositive_Uint64_276) {
  using Traits = ieee754_binary_traits<Float64Format, std::uint64_t, std::int32_t>;
  EXPECT_FALSE(Traits::is_positive(std::numeric_limits<std::uint64_t>::max()));
}