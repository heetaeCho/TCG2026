// TEST_ID: 272
#include <cstdint>
#include <limits>
#include <type_traits>

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

struct Format32_272 {
  static constexpr int total_bits = 32;
};

struct Format64_272 {
  static constexpr int total_bits = 64;
};

template <class Format, class CarrierUInt>
using Traits272 = YAML::jkj::dragonbox::ieee754_binary_traits<Format, CarrierUInt, int>;

template <class CarrierUInt>
constexpr CarrierUInt BitMask272(int bit_index) {
  return CarrierUInt(CarrierUInt{1} << bit_index);
}

}  // namespace

// -------------------- Normal operation --------------------

TEST(DragonboxIeee754BinaryTraitsTest_272, ZeroMapsToZero_272) {
  constexpr std::uint32_t r32 = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(0u);
  EXPECT_EQ(r32, 0u);

  constexpr std::uint64_t r64 = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(0ull);
  EXPECT_EQ(r64, 0ull);
}

TEST(DragonboxIeee754BinaryTraitsTest_272, SignBitOnlyBecomesZero_272) {
  constexpr std::uint32_t sign32 = BitMask272<std::uint32_t>(Format32_272::total_bits - 1);
  constexpr std::uint32_t r32 = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(sign32);
  EXPECT_EQ(r32, 0u);

  constexpr std::uint64_t sign64 = BitMask272<std::uint64_t>(Format64_272::total_bits - 1);
  constexpr std::uint64_t r64 = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(sign64);
  EXPECT_EQ(r64, 0ull);
}

TEST(DragonboxIeee754BinaryTraitsTest_272, OutputIsInvariantToSignBit_272) {
  // For any input u, toggling the sign bit should not change the output.
  constexpr std::uint32_t sign32 = BitMask272<std::uint32_t>(Format32_272::total_bits - 1);
  constexpr std::uint32_t u32 = 0x12345678u;
  constexpr auto a32 = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(u32);
  constexpr auto b32 = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(u32 ^ sign32);
  EXPECT_EQ(a32, b32);

  constexpr std::uint64_t sign64 = BitMask272<std::uint64_t>(Format64_272::total_bits - 1);
  constexpr std::uint64_t u64 = 0x1234567890ABCDEFull;
  constexpr auto a64 = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(u64);
  constexpr auto b64 = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(u64 ^ sign64);
  EXPECT_EQ(a64, b64);
}

TEST(DragonboxIeee754BinaryTraitsTest_272, SingleBitInLowerRegionShiftsUpByOne_272) {
  // For bit i (not the sign bit), it should move to i+1 after shifting.
  // Example: bit 0 -> bit 1, bit 1 -> bit 2, etc.
  {
    constexpr std::uint32_t u = 0u | BitMask272<std::uint32_t>(0);
    constexpr auto r = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(u);
    EXPECT_EQ(r, BitMask272<std::uint32_t>(1));
  }
  {
    constexpr int i = 10;
    constexpr std::uint32_t u = 0u | BitMask272<std::uint32_t>(i);
    constexpr auto r = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(u);
    EXPECT_EQ(r, BitMask272<std::uint32_t>(i + 1));
  }
  {
    constexpr int i = 20;
    constexpr std::uint64_t u = 0ull | BitMask272<std::uint64_t>(i);
    constexpr auto r = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(u);
    EXPECT_EQ(r, BitMask272<std::uint64_t>(i + 1));
  }
}

TEST(DragonboxIeee754BinaryTraitsTest_272, LeastSignificantBitOfResultIsAlwaysZero_272) {
  constexpr std::uint32_t inputs32[] = {
      0u, 1u, 2u, 3u, 0xFFFFFFFFu, 0x80000001u, 0x7FFFFFFFu,
  };
  for (std::uint32_t u : inputs32) {
    auto r = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(u);
    EXPECT_EQ((r & 1u), 0u) << "u=" << std::hex << u;
  }

  constexpr std::uint64_t inputs64[] = {
      0ull, 1ull, 2ull, 3ull, 0xFFFFFFFFFFFFFFFFull, 0x8000000000000001ull, 0x7FFFFFFFFFFFFFFFull,
  };
  for (std::uint64_t u : inputs64) {
    auto r = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(u);
    EXPECT_EQ((r & 1ull), 0ull) << "u=" << std::hex << u;
  }
}

// -------------------- Boundary conditions --------------------

TEST(DragonboxIeee754BinaryTraitsTest_272, TopNonSignBitMovesIntoSignPosition_272) {
  // The bit just below the sign bit (total_bits-2) should become the sign position (total_bits-1).
  constexpr std::uint32_t u32 = BitMask272<std::uint32_t>(Format32_272::total_bits - 2);
  constexpr auto r32 = Traits272<Format32_272, std::uint32_t>::remove_sign_bit_and_shift(u32);
  EXPECT_EQ(r32, BitMask272<std::uint32_t>(Format32_272::total_bits - 1));

  constexpr std::uint64_t u64 = BitMask272<std::uint64_t>(Format64_272::total_bits - 2);
  constexpr auto r64 = Traits272<Format64_272, std::uint64_t>::remove_sign_bit_and_shift(u64);
  EXPECT_EQ(r64, BitMask272<std::uint64_t>(Format64_272::total_bits - 1));
}

TEST(DragonboxIeee754BinaryTraitsTest_272, BitWidthMaskingClearsBitsAboveFormatTotalBits_272) {
  // Use a wider carrier than the format's total_bits and ensure higher bits are cleared in the result.
  // Format32 uses total_bits=32 but carrier is uint64_t here.
  constexpr std::uint64_t high_bits = 0xFFFF'FFFF'0000'0000ull;  // bits above 31 are set
  constexpr std::uint64_t low_bits = 0x0000'0000'1234'5678ull;
  constexpr std::uint64_t u = high_bits | low_bits;

  const std::uint64_t r = Traits272<Format32_272, std::uint64_t>::remove_sign_bit_and_shift(u);

  // All bits above bit (total_bits-1) should be cleared.
  constexpr std::uint64_t above_31_mask = 0xFFFF'FFFF'0000'0000ull;
  EXPECT_EQ((r & above_31_mask), 0ull);

  // Also ensure sign-bit toggling within the 32-bit "format space" doesn't change the result.
  constexpr std::uint64_t sign32_in_u64 = BitMask272<std::uint64_t>(Format32_272::total_bits - 1);
  const std::uint64_t r2 = Traits272<Format32_272, std::uint64_t>::remove_sign_bit_and_shift(u ^ sign32_in_u64);
  EXPECT_EQ(r, r2);
}

// -------------------- Exceptional / error cases --------------------
// The function is noexcept and takes an unsigned carrier; there are no observable error cases
// exposed through the interface (no exceptions, no error codes).
// This section is intentionally empty for TEST_ID 272.