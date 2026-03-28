// TEST_ID: 300
#include <gtest/gtest.h>

#include <limits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::carrier_uint;

// A minimal traits type to verify that float_bits::has_even_significand_bits()
// forwards to FormatTraits::has_even_significand_bits(u).
struct DummyFormatTraits {
  static constexpr bool has_even_significand_bits(carrier_uint u) noexcept {
    // Deterministic, easy-to-check behavior for tests (even/odd on the input).
    return (u % 2u) == 0u;
  }
};

using DummyFloatBits = YAML::jkj::dragonbox::float_bits<DummyFormatTraits>;

}  // namespace

TEST(FloatBitsHasEvenSignificandBitsTest_300, DelegatesToFormatTraits_300) {
  const carrier_uint patterns[] = {
      carrier_uint{0},
      carrier_uint{1},
      carrier_uint{2},
      carrier_uint{3},
      std::numeric_limits<carrier_uint>::max(),
  };

  for (carrier_uint p : patterns) {
    const DummyFloatBits fb(p);
    EXPECT_EQ(fb.has_even_significand_bits(),
              DummyFormatTraits::has_even_significand_bits(p))
        << "bit_pattern=" << static_cast<unsigned long long>(p);
  }
}

TEST(FloatBitsHasEvenSignificandBitsTest_300, BoundaryPatterns_300) {
  const DummyFloatBits zero_bits(carrier_uint{0});
  EXPECT_TRUE(zero_bits.has_even_significand_bits());

  const DummyFloatBits max_bits(std::numeric_limits<carrier_uint>::max());
  EXPECT_EQ(max_bits.has_even_significand_bits(),
            DummyFormatTraits::has_even_significand_bits(
                std::numeric_limits<carrier_uint>::max()));
}

TEST(FloatBitsHasEvenSignificandBitsTest_300, ConstexprAndNoexcept_300) {
  static_assert(noexcept(DummyFloatBits(carrier_uint{0}).has_even_significand_bits()),
                "has_even_significand_bits() must be noexcept");

  constexpr DummyFloatBits even_bits(carrier_uint{42});
  static_assert(even_bits.has_even_significand_bits(),
                "Expected even pattern to be reported as even by DummyFormatTraits");

  constexpr DummyFloatBits odd_bits(carrier_uint{41});
  static_assert(!odd_bits.has_even_significand_bits(),
                "Expected odd pattern to be reported as odd by DummyFormatTraits");
}