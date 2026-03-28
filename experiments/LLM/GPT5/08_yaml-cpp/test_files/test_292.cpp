// TEST_ID: 292
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class Bits>
constexpr auto MakeInterestingPatterns() {
  using CU = decltype(std::declval<Bits>().extract_significand_bits());
  static_assert(std::is_integral_v<CU>, "carrier_uint/significand bits should be integral");

  // A small, diverse set of bit patterns (no assumptions about IEEE layout).
  return std::array<CU, 8>{
      CU{0},
      CU{1},
      CU{2},
      CU{3},
      CU{~CU{0}},
      CU{CU{1} << (std::numeric_limits<CU>::digits - 1)},   // top bit set
      CU{(CU{1} << (std::numeric_limits<CU>::digits - 1)) | CU{1}}, // top bit + low bit
      CU{CU{0xA5A5A5A5u}} // will truncate/extend appropriately via cast below if needed
  };
}

template <class Bits, class CU>
constexpr Bits MakeBitsFrom(CU pattern) {
  // The constructor takes the Bits' carrier_uint type; we rely only on interface.
  using Carrier = std::remove_cv_t<std::remove_reference_t<decltype(
      std::declval<Bits>().binary_significand())>>;
  return Bits(static_cast<Carrier>(pattern));
}

}  // namespace

namespace YAML::jkj::dragonbox {

// Try to cover common instantiations used by Dragonbox in yaml-cpp.
// If your codebase uses different trait names, update these aliases accordingly.
using Bits32_292 = float_bits<ieee754_binary32>;
using Bits64_292 = float_bits<ieee754_binary64>;

class FloatBitsBinaryExponentTest_292 : public ::testing::Test {};

TEST_F(FloatBitsBinaryExponentTest_292, NoexceptQualification_292) {
  static_assert(noexcept(std::declval<const Bits32_292&>().binary_exponent()));
  static_assert(noexcept(std::declval<const Bits64_292&>().binary_exponent()));
}

TEST_F(FloatBitsBinaryExponentTest_292, DefaultConstructedMatchesStaticComposition_292) {
  // Black-box invariant from the provided implementation:
  // binary_exponent() == binary_exponent(extract_exponent_bits()).
  const Bits32_292 b32;
  EXPECT_EQ(b32.binary_exponent(), Bits32_292::binary_exponent(b32.extract_exponent_bits()));

  const Bits64_292 b64;
  EXPECT_EQ(b64.binary_exponent(), Bits64_292::binary_exponent(b64.extract_exponent_bits()));
}

TEST_F(FloatBitsBinaryExponentTest_292, VariousBitPatternsMatchStaticComposition_292) {
  // Validate the observable relationship for a variety of carrier bit patterns,
  // without assuming IEEE-754 layout.
  for (auto p : MakeInterestingPatterns<Bits32_292>()) {
    const Bits32_292 b(static_cast<decltype(std::declval<Bits32_292>().extract_significand_bits())>(p));
    EXPECT_EQ(b.binary_exponent(), Bits32_292::binary_exponent(b.extract_exponent_bits()))
        << "Pattern (32): " << +static_cast<std::uint64_t>(p);
  }

  for (auto p : MakeInterestingPatterns<Bits64_292>()) {
    const Bits64_292 b(static_cast<decltype(std::declval<Bits64_292>().extract_significand_bits())>(p));
    EXPECT_EQ(b.binary_exponent(), Bits64_292::binary_exponent(b.extract_exponent_bits()))
        << "Pattern (64): " << +static_cast<std::uint64_t>(p);
  }
}

TEST_F(FloatBitsBinaryExponentTest_292, ConstexprEvaluationForSimplePatterns_292) {
  // Ensure the method is usable in constant evaluation (as declared constexpr),
  // checking only the provided composition behavior.
  {
    constexpr Bits32_292 b0(static_cast<decltype(std::declval<Bits32_292>().binary_significand())>(0));
    static_assert(b0.binary_exponent() == Bits32_292::binary_exponent(b0.extract_exponent_bits()));
  }
  {
    constexpr Bits64_292 b1(static_cast<decltype(std::declval<Bits64_292>().binary_significand())>(1));
    static_assert(b1.binary_exponent() == Bits64_292::binary_exponent(b1.extract_exponent_bits()));
  }
}

TEST_F(FloatBitsBinaryExponentTest_292, BoundaryLikePatternsMatchStaticComposition_292) {
  // Boundary-ish inputs for the underlying carrier integer:
  // all-zeros, all-ones, and top-bit-only.
  using CU32 = decltype(std::declval<Bits32_292>().extract_significand_bits());
  using CU64 = decltype(std::declval<Bits64_292>().extract_significand_bits());

  const CU32 z32 = CU32{0};
  const CU32 o32 = CU32{~CU32{0}};
  const CU32 t32 = CU32{CU32{1} << (std::numeric_limits<CU32>::digits - 1)};

  const Bits32_292 bz32(z32), bo32(o32), bt32(t32);
  EXPECT_EQ(bz32.binary_exponent(), Bits32_292::binary_exponent(bz32.extract_exponent_bits()));
  EXPECT_EQ(bo32.binary_exponent(), Bits32_292::binary_exponent(bo32.extract_exponent_bits()));
  EXPECT_EQ(bt32.binary_exponent(), Bits32_292::binary_exponent(bt32.extract_exponent_bits()));

  const CU64 z64 = CU64{0};
  const CU64 o64 = CU64{~CU64{0}};
  const CU64 t64 = CU64{CU64{1} << (std::numeric_limits<CU64>::digits - 1)};

  const Bits64_292 bz64(z64), bo64(o64), bt64(t64);
  EXPECT_EQ(bz64.binary_exponent(), Bits64_292::binary_exponent(bz64.extract_exponent_bits()));
  EXPECT_EQ(bo64.binary_exponent(), Bits64_292::binary_exponent(bo64.extract_exponent_bits()));
  EXPECT_EQ(bt64.binary_exponent(), Bits64_292::binary_exponent(bt64.extract_exponent_bits()));
}

}  // namespace YAML::jkj::dragonb