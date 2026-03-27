// File: dragonbox_ieee754_binary_traits_is_nonzero_test_275.cpp

#include <cstdint>
#include <limits>

#include "gtest/gtest.h"

// Adjust include path if your build uses a different include root.
#include "contrib/dragonbox.h"

namespace {

struct DummyFormat32_275 {
  static constexpr int significand_bits = 23;
  static constexpr int exponent_bits = 8;
};

struct DummyFormat64_275 {
  static constexpr int significand_bits = 52;
  static constexpr int exponent_bits = 11;
};

using Traits32_275 =
    YAML::jkj::dragonbox::ieee754_binary_traits<DummyFormat32_275, std::uint32_t, int>;
using Traits64_275 =
    YAML::jkj::dragonbox::ieee754_binary_traits<DummyFormat64_275, std::uint64_t, int>;

template <typename CarrierUInt, int SigBits, int ExpBits>
constexpr CarrierUInt MaskNoSign_275() {
  // Mask covering significand+exponent bits (i.e., excluding the sign bit).
  return (CarrierUInt(1) << (SigBits + ExpBits)) - CarrierUInt(1);
}

}  // namespace

TEST(DragonboxIeee754BinaryTraitsTest_275, IsNonzeroReturnsFalseForZero_275) {
  EXPECT_FALSE(Traits32_275::is_nonzero(std::uint32_t{0}));
  EXPECT_FALSE(Traits64_275::is_nonzero(std::uint64_t{0}));

  static_assert(!Traits32_275::is_nonzero(std::uint32_t{0}), "constexpr check");
  static_assert(!Traits64_275::is_nonzero(std::uint64_t{0}), "constexpr check");
}

TEST(DragonboxIeee754BinaryTraitsTest_275, IsNonzeroIgnoresSignBitOnly_275) {
  // Construct value with only the sign bit set; the remaining bits are all zero.
  constexpr std::uint32_t sign_only_32 = (std::uint32_t{1} << (DummyFormat32_275::significand_bits +
                                                              DummyFormat32_275::exponent_bits));
  constexpr std::uint64_t sign_only_64 = (std::uint64_t{1} << (DummyFormat64_275::significand_bits +
                                                              DummyFormat64_275::exponent_bits));

  EXPECT_FALSE(Traits32_275::is_nonzero(sign_only_32));
  EXPECT_FALSE(Traits64_275::is_nonzero(sign_only_64));

  static_assert(!Traits32_275::is_nonzero(sign_only_32), "constexpr check");
  static_assert(!Traits64_275::is_nonzero(sign_only_64), "constexpr check");
}

TEST(DragonboxIeee754BinaryTraitsTest_275, IsNonzeroTrueWhenAnyMaskedBitIsSet_275) {
  // LSB set (within significand region).
  EXPECT_TRUE(Traits32_275::is_nonzero(std::uint32_t{1}));
  EXPECT_TRUE(Traits64_275::is_nonzero(std::uint64_t{1}));

  // A bit set somewhere inside the (significand+exponent) mask.
  constexpr std::uint32_t mid_32 = (std::uint32_t{1} << 10);
  constexpr std::uint64_t mid_64 = (std::uint64_t{1} << 10);
  EXPECT_TRUE(Traits32_275::is_nonzero(mid_32));
  EXPECT_TRUE(Traits64_275::is_nonzero(mid_64));
}

TEST(DragonboxIeee754BinaryTraitsTest_275, IsNonzeroTrueForMaxValueWithinMask_275) {
  constexpr std::uint32_t mask_32 =
      MaskNoSign_275<std::uint32_t, DummyFormat32_275::significand_bits, DummyFormat32_275::exponent_bits>();
  constexpr std::uint64_t mask_64 =
      MaskNoSign_275<std::uint64_t, DummyFormat64_275::significand_bits, DummyFormat64_275::exponent_bits>();

  EXPECT_TRUE(Traits32_275::is_nonzero(mask_32));
  EXPECT_TRUE(Traits64_275::is_nonzero(mask_64));

  static_assert(Traits32_275::is_nonzero(mask_32), "constexpr check");
  static_assert(Traits64_275::is_nonzero(mask_64), "constexpr check");
}

TEST(DragonboxIeee754BinaryTraitsTest_275, IsNonzeroTrueWhenAllBitsSetIncludingSign_275) {
  EXPECT_TRUE(Traits32_275::is_nonzero(std::numeric_limits<std::uint32_t>::max()));
  EXPECT_TRUE(Traits64_275::is_nonzero(std::numeric_limits<std::uint64_t>::max()));
}