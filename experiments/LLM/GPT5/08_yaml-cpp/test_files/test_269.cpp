// File: dragonbox_ieee754_binary_traits_extract_exponent_bits_test.cpp
#include <cstdint>
#include <type_traits>

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::ieee754_binary_traits;

// Minimal format types to drive the template.
struct Float32Format_269 {
  static constexpr int significand_bits = 23;
  static constexpr int exponent_bits = 8;
};

struct Float64Format_269 {
  static constexpr int significand_bits = 52;
  static constexpr int exponent_bits = 11;
};

template <typename UInt>
constexpr UInt Mask_269(int bits) {
  return bits == 0 ? UInt{0} : (UInt{1} << bits) - UInt{1};
}

class Ieee754BinaryTraitsTest_269 : public ::testing::Test {};

TEST_F(Ieee754BinaryTraitsTest_269, IsNoexcept_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  EXPECT_TRUE(noexcept(Traits32::extract_exponent_bits(std::uint32_t{0})));
  EXPECT_TRUE(noexcept(Traits64::extract_exponent_bits(std::uint64_t{0})));
}

TEST_F(Ieee754BinaryTraitsTest_269, ExtractsZeroExponentWhenInputIsZero_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  EXPECT_EQ(Traits32::extract_exponent_bits(0u), 0);
  EXPECT_EQ(Traits64::extract_exponent_bits(0ull), 0);
}

TEST_F(Ieee754BinaryTraitsTest_269, ExtractsExponentBitsFromKnownFloat32Patterns_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;

  // 1.0f -> 0x3f800000, exponent bits = 127
  EXPECT_EQ(Traits32::extract_exponent_bits(0x3f800000u), 127);

  // 2.0f -> 0x40000000, exponent bits = 128
  EXPECT_EQ(Traits32::extract_exponent_bits(0x40000000u), 128);

  // +infinity -> 0x7f800000, exponent bits = 255
  EXPECT_EQ(Traits32::extract_exponent_bits(0x7f800000u), 255);

  // Smallest positive normal -> exponent bits = 1 (0x00800000)
  EXPECT_EQ(Traits32::extract_exponent_bits(0x00800000u), 1);

  // Subnormal (no exponent) -> exponent bits = 0 (0x00000001)
  EXPECT_EQ(Traits32::extract_exponent_bits(0x00000001u), 0);
}

TEST_F(Ieee754BinaryTraitsTest_269, ExtractsExponentBitsFromKnownFloat64Patterns_269) {
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  // 1.0 -> 0x3ff0000000000000, exponent bits = 1023
  EXPECT_EQ(Traits64::extract_exponent_bits(0x3ff0000000000000ull), 1023);

  // 2.0 -> 0x4000000000000000, exponent bits = 1024
  EXPECT_EQ(Traits64::extract_exponent_bits(0x4000000000000000ull), 1024);

  // +infinity -> 0x7ff0000000000000, exponent bits = 2047
  EXPECT_EQ(Traits64::extract_exponent_bits(0x7ff0000000000000ull), 2047);

  // Smallest positive normal -> exponent bits = 1 (0x0010000000000000)
  EXPECT_EQ(Traits64::extract_exponent_bits(0x0010000000000000ull), 1);

  // Subnormal -> exponent bits = 0 (0x0000000000000001)
  EXPECT_EQ(Traits64::extract_exponent_bits(0x0000000000000001ull), 0);
}

TEST_F(Ieee754BinaryTraitsTest_269, SignBitDoesNotAffectExtractedExponent_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  // 1.0f vs -1.0f: only sign bit differs.
  EXPECT_EQ(Traits32::extract_exponent_bits(0x3f800000u),
            Traits32::extract_exponent_bits(0xbf800000u));

  // 1.0 vs -1.0
  EXPECT_EQ(Traits64::extract_exponent_bits(0x3ff0000000000000ull),
            Traits64::extract_exponent_bits(0xbff0000000000000ull));
}

TEST_F(Ieee754BinaryTraitsTest_269, ExtractsAllOnesExponentWhenAllExponentBitsAreSet_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  // Construct u where exponent field is all ones; allow any significand bits.
  const std::uint32_t exp_all_ones_32 =
      (Mask_269<std::uint32_t>(Float32Format_269::exponent_bits) << Float32Format_269::significand_bits);
  const std::uint64_t exp_all_ones_64 =
      (Mask_269<std::uint64_t>(Float64Format_269::exponent_bits) << Float64Format_269::significand_bits);

  EXPECT_EQ(Traits32::extract_exponent_bits(exp_all_ones_32),
            static_cast<int>(Mask_269<std::uint32_t>(Float32Format_269::exponent_bits)));
  EXPECT_EQ(Traits64::extract_exponent_bits(exp_all_ones_64),
            static_cast<int>(Mask_269<std::uint64_t>(Float64Format_269::exponent_bits)));
}

TEST_F(Ieee754BinaryTraitsTest_269, MasksOffBitsAboveExponentField_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  // Put all ones in the whole word. Exponent extraction should still only return exponent_bits ones.
  EXPECT_EQ(Traits32::extract_exponent_bits(0xFFFFFFFFu),
            static_cast<int>(Mask_269<std::uint32_t>(Float32Format_269::exponent_bits)));
  EXPECT_EQ(Traits64::extract_exponent_bits(0xFFFFFFFFFFFFFFFFull),
            static_cast<int>(Mask_269<std::uint64_t>(Float64Format_269::exponent_bits)));
}

TEST_F(Ieee754BinaryTraitsTest_269, WorksInConstantEvaluationContext_269) {
  using Traits32 = ieee754_binary_traits<Float32Format_269, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<Float64Format_269, std::uint64_t, int>;

  static_assert(Traits32::extract_exponent_bits(0x3f800000u) == 127,
                "extract_exponent_bits should be usable in constant evaluation (float32)");
  static_assert(Traits64::extract_exponent_bits(0x3ff0000000000000ull) == 1023,
                "extract_exponent_bits should be usable in constant evaluation (float64)");
}

}  // namespace