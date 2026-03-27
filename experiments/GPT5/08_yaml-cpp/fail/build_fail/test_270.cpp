// TEST_ID: 270
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Minimal "Format" types for instantiating ieee754_binary_traits in a black-box way.
// We only rely on the public interface: extract_significand_bits(carrier_uint).
struct FormatSig0 {
  static constexpr int significand_bits = 0;
};
struct FormatSig1 {
  static constexpr int significand_bits = 1;
};
struct FormatSig5 {
  static constexpr int significand_bits = 5;
};
struct FormatSig16 {
  static constexpr int significand_bits = 16;
};
struct FormatSig31 {
  static constexpr int significand_bits = 31;  // safe for uint32_t shifts
};

template <typename CarrierUInt, int SigBits>
constexpr CarrierUInt ExpectedSignificandBits(CarrierUInt u) {
  if constexpr (SigBits <= 0) {
    return CarrierUInt{0};
  } else {
    // Keep the expected computation local to the test.
    const CarrierUInt mask = CarrierUInt((CarrierUInt(1) << SigBits) - CarrierUInt(1));
    return CarrierUInt(u & mask);
  }
}

}  // namespace

// ------------------------ Tests ------------------------

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, IsNoexcept_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig5, std::uint32_t, std::int32_t>;
  static_assert(noexcept(Traits::extract_significand_bits(std::uint32_t{0})),
                "extract_significand_bits must be noexcept");
  SUCCEED();
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, WorksInConstantEvaluation_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig16, std::uint32_t, std::int32_t>;
  constexpr std::uint32_t u = 0xABCD'1234u;
  constexpr std::uint32_t got = Traits::extract_significand_bits(u);
  constexpr std::uint32_t expected = ExpectedSignificandBits<std::uint32_t, FormatSig16::significand_bits>(u);
  static_assert(got == expected, "constexpr extract_significand_bits must match expected masking");
  EXPECT_EQ(got, expected);
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, ZeroSignificandBitsAlwaysReturnsZero_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig0, std::uint32_t, std::int32_t>;

  EXPECT_EQ(Traits::extract_significand_bits(0u), 0u);
  EXPECT_EQ(Traits::extract_significand_bits(1u), 0u);
  EXPECT_EQ(Traits::extract_significand_bits(0xFFFF'FFFFu), 0u);
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, OneSignificandBitExtractsLeastSignificantBit_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig1, std::uint32_t, std::int32_t>;

  EXPECT_EQ(Traits::extract_significand_bits(0u), 0u);
  EXPECT_EQ(Traits::extract_significand_bits(1u), 1u);
  EXPECT_EQ(Traits::extract_significand_bits(2u), 0u);
  EXPECT_EQ(Traits::extract_significand_bits(3u), 1u);
  EXPECT_EQ(Traits::extract_significand_bits(0xFFFF'FFFFu), 1u);
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, MasksOffHigherBits_NormalCase_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig5, std::uint32_t, std::int32_t>;

  const std::uint32_t u = 0b1010'1101'1111u;  // plenty of higher bits beyond 5 LSBs
  const std::uint32_t got = Traits::extract_significand_bits(u);
  const std::uint32_t expected =
      ExpectedSignificandBits<std::uint32_t, FormatSig5::significand_bits>(u);

  EXPECT_EQ(got, expected);
  // Extra sanity: result must be within [0, 2^SigBits - 1]
  EXPECT_LE(got, (std::uint32_t(1u) << FormatSig5::significand_bits) - 1u);
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, PreservesAllLowerBitsWhenAllOnes_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig16, std::uint32_t, std::int32_t>;

  const std::uint32_t u = std::numeric_limits<std::uint32_t>::max();
  const std::uint32_t got = Traits::extract_significand_bits(u);
  const std::uint32_t expected =
      ExpectedSignificandBits<std::uint32_t, FormatSig16::significand_bits>(u);

  EXPECT_EQ(got, expected);
  EXPECT_EQ(got, 0xFFFFu);
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, BoundaryNearWordSize_31Bits_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig31, std::uint32_t, std::int32_t>;

  const std::uint32_t u = 0xFFFF'FFFFu;
  const std::uint32_t got = Traits::extract_significand_bits(u);
  const std::uint32_t expected =
      ExpectedSignificandBits<std::uint32_t, FormatSig31::significand_bits>(u);

  EXPECT_EQ(got, expected);
  // For 31 bits, the top (bit 31) should be cleared.
  EXPECT_EQ(got & 0x8000'0000u, 0u);
  EXPECT_EQ(got, 0x7FFF'FFFFu);
}

TEST(Ieee754BinaryTraitsExtractSignificandBitsTest_270, DoesNotDependOnSignBitLikeValues_270) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatSig16, std::uint32_t, std::int32_t>;

  // Two inputs that differ only in the highest bit (often a "sign bit" in IEEE layouts),
  // but this test only checks the observable result of extract_significand_bits.
  const std::uint32_t base = 0x1234'5678u;
  const std::uint32_t flipped = base ^ 0x8000'0000u;

  EXPECT_EQ(Traits::extract_significand_bits(base),
            ExpectedSignificandBits<std::uint32_t, FormatSig16::significand_bits>(base));
  EXPECT_EQ(Traits::extract_significand_bits(flipped),
            ExpectedSignificandBits<std::uint32_t, FormatSig16::significand_bits>(flipped));

  // Lower 16 bits should match regardless of that highest-bit flip.
  EXPECT_EQ(Traits::extract_significand_bits(base),
            Traits::extract_significand_bits(flipped));
}