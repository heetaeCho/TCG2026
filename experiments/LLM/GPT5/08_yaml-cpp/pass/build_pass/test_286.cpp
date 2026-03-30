// TEST_ID: 286
#include <cstdint>
#include <type_traits>

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

struct FormatTraits286 {
  using carrier_uint = std::uint32_t;

  // Pure, deterministic "trait" behavior so tests can verify delegation.
  static constexpr bool has_all_zero_significand_bits(carrier_uint v) noexcept {
    // Define "significand bits" here purely for testing (collaborator behavior).
    // The class under test must simply forward `u` into this function.
    constexpr carrier_uint kSignificandMask = 0x00FFFFFFu;  // low 24 bits
    return (v & kSignificandMask) == 0;
  }
};

using Bits286 = YAML::jkj::dragonbox::signed_significand_bits<FormatTraits286>;

class SignedSignificandBitsHasAllZeroSignificandBitsTest_286 : public ::testing::Test {};

TEST_F(SignedSignificandBitsHasAllZeroSignificandBitsTest_286,
       ReturnsTrueWhenTraitsReturnTrue_286) {
  // Low 24 bits are zero => trait returns true.
  constexpr FormatTraits286::carrier_uint pattern = 0xAB000000u;
  const Bits286 bits(pattern);

  EXPECT_TRUE(bits.has_all_zero_significand_bits());
  EXPECT_TRUE(FormatTraits286::has_all_zero_significand_bits(pattern));
}

TEST_F(SignedSignificandBitsHasAllZeroSignificandBitsTest_286,
       ReturnsFalseWhenTraitsReturnFalse_286) {
  // Low 24 bits contain 1 => trait returns false.
  constexpr FormatTraits286::carrier_uint pattern = 0x00000001u;
  const Bits286 bits(pattern);

  EXPECT_FALSE(bits.has_all_zero_significand_bits());
  EXPECT_FALSE(FormatTraits286::has_all_zero_significand_bits(pattern));
}

TEST_F(SignedSignificandBitsHasAllZeroSignificandBitsTest_286,
       MatchesTraitsForVariousPatterns_BoundaryValues_286) {
  const FormatTraits286::carrier_uint patterns[] = {
      0x00000000u,  // all zeros
      0xFFFFFFFFu,  // all ones
      0x00FFFFFFu,  // all significand bits set (per trait mask)
      0xFF000000u,  // significand bits all zero, high bits set
      0x00010000u,  // one significand bit set
  };

  for (auto p : patterns) {
    const Bits286 bits(p);
    EXPECT_EQ(bits.has_all_zero_significand_bits(),
              FormatTraits286::has_all_zero_significand_bits(p))
        << "pattern=0x" << std::hex << p;
  }
}

TEST_F(SignedSignificandBitsHasAllZeroSignificandBitsTest_286,
       IsNoexcept_286) {
  const Bits286 bits(0u);
  EXPECT_TRUE(noexcept(bits.has_all_zero_significand_bits()));
  EXPECT_NO_THROW((void)bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsHasAllZeroSignificandBitsTest_286,
       SupportsConstexprEvaluation_286) {
  // If the implementation is truly constexpr-forwarding, this will compile.
  static_assert(Bits286(0x12000000u).has_all_zero_significand_bits(),
                "Expected true for pattern with masked significand bits == 0");
  static_assert(!Bits286(0x00000002u).has_all_zero_significand_bits(),
                "Expected false for pattern with masked significand bits != 0");

  SUCCEED();
}

}  // namespace