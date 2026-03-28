// File: dragonbox_binary_significand_test_274.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <int SignificandBits>
struct Format_274 {
  static constexpr int significand_bits = SignificandBits;
};

// Helper to make the "implicit leading 1" bitmask without depending on internal logic.
// This is a simple, observable property of the interface: the result should have this bit set
// whenever exponent_bits != 0.
template <typename CarrierUInt, int SignificandBits>
constexpr CarrierUInt ImplicitLeadingOneMask_274() {
  static_assert(std::is_unsigned<CarrierUInt>::value, "CarrierUInt must be unsigned");
  return (CarrierUInt(1) << SignificandBits);
}

}  // namespace

class BinarySignificandTest_274 : public ::testing::Test {};

TEST_F(BinarySignificandTest_274, ExponentBitsZeroReturnsSignificandBitsUnchanged_274) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<23>, std::uint32_t, std::int32_t>;

  EXPECT_EQ(Traits::binary_significand(std::uint32_t{0}, std::int32_t{0}), std::uint32_t{0});
  EXPECT_EQ(Traits::binary_significand(std::uint32_t{1}, std::int32_t{0}), std::uint32_t{1});
  EXPECT_EQ(Traits::binary_significand(std::uint32_t{0x7FFFFF}, std::int32_t{0}), std::uint32_t{0x7FFFFF});
}

TEST_F(BinarySignificandTest_274, ExponentBitsNonZeroSetsImplicitLeadingOneBit_274) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<23>, std::uint32_t, std::int32_t>;
  constexpr std::uint32_t kMask = ImplicitLeadingOneMask_274<std::uint32_t, 23>();

  const std::uint32_t significand_bits = 0x123456u & 0x7FFFFFu;  // stay within 23 bits
  const std::uint32_t result = Traits::binary_significand(significand_bits, std::int32_t{1});

  // Observable properties:
  // 1) The implicit leading-one bit is set when exponent_bits != 0.
  EXPECT_NE((result & kMask), 0u);

  // 2) Lower significand bits are preserved.
  EXPECT_EQ((result & (kMask - 1u)), significand_bits);
}

TEST_F(BinarySignificandTest_274, ExponentBitsNonZeroWhenSignificandAlreadyHasLeadingBitKeepsItSet_274) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<5>, std::uint32_t, std::int32_t>;
  constexpr std::uint32_t kMask = ImplicitLeadingOneMask_274<std::uint32_t, 5>();

  // Provide a significand_bits value that already contains the "implicit" bit position.
  const std::uint32_t significand_bits = kMask | 0b10101u;
  const std::uint32_t result = Traits::binary_significand(significand_bits, std::int32_t{7});

  EXPECT_NE((result & kMask), 0u);
  // Since it was already set, the result should at least contain the original bits.
  EXPECT_EQ((result & significand_bits), significand_bits);
}

TEST_F(BinarySignificandTest_274, BoundarySignificandBitsZeroWithNonZeroExponentProducesOnlyImplicitBit_274) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<10>, std::uint32_t, std::int32_t>;
  constexpr std::uint32_t kMask = ImplicitLeadingOneMask_274<std::uint32_t, 10>();

  const std::uint32_t result = Traits::binary_significand(std::uint32_t{0}, std::int32_t{42});
  EXPECT_EQ(result, kMask);
}

TEST_F(BinarySignificandTest_274, BoundaryFormatWithZeroSignificandBits_274) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<0>, std::uint32_t, std::int32_t>;
  constexpr std::uint32_t kMask = ImplicitLeadingOneMask_274<std::uint32_t, 0>();  // == 1

  EXPECT_EQ(Traits::binary_significand(std::uint32_t{0}, std::int32_t{0}), std::uint32_t{0});
  EXPECT_EQ(Traits::binary_significand(std::uint32_t{0}, std::int32_t{1}), kMask);
  EXPECT_EQ(Traits::binary_significand(std::uint32_t{1}, std::int32_t{0}), std::uint32_t{1});
  EXPECT_EQ(Traits::binary_significand(std::uint32_t{1}, std::int32_t{2}), (std::uint32_t{1} | kMask));
}

TEST_F(BinarySignificandTest_274, WorksWith64BitCarrierAndLargeSignificandWidth_274) {
  // Typical double: 52 fraction bits.
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<52>, std::uint64_t, std::int32_t>;
  constexpr std::uint64_t kMask = ImplicitLeadingOneMask_274<std::uint64_t, 52>();

  const std::uint64_t significand_bits = (std::uint64_t{1} << 51) | 0x1234ull;
  const std::uint64_t result = Traits::binary_significand(significand_bits, std::int32_t{1});

  EXPECT_NE((result & kMask), 0ull);
  EXPECT_EQ((result & (kMask - 1ull)), significand_bits);
}

TEST_F(BinarySignificandTest_274, NegativeExponentBitsTreatedAsNonZeroBranch_274) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<Format_274<8>, std::uint32_t, std::int32_t>;
  constexpr std::uint32_t kMask = ImplicitLeadingOneMask_274<std::uint32_t, 8>();

  const std::uint32_t significand_bits = 0x5Au;  // within 8 bits
  const std::uint32_t result = Traits::binary_significand(significand_bits, std::int32_t{-1});

  EXPECT_NE((result & kMask), 0u);
  EXPECT_EQ((result & (kMask - 1u)), significand_bits);
}