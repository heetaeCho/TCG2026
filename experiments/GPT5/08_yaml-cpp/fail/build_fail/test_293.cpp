// TEST_ID: 293
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::carrier_uint;
using YAML::jkj::dragonbox::exponent_int;

// A controllable FormatTraits used as an external collaborator for float_bits<FormatTraits>.
struct DummyFormatTraits_293 {
  static constexpr carrier_uint binary_significand(carrier_uint significand_bits,
                                                   exponent_int exponent_bits) noexcept {
    // Deliberately simple, deterministic mapping to validate forwarding.
    // (We are NOT testing dragonbox's math; only that float_bits forwards correctly.)
    return static_cast<carrier_uint>(significand_bits + static_cast<carrier_uint>(exponent_bits) +
                                     static_cast<carrier_uint>(0x1234u));
  }
};

using FloatBitsDummy_293 = YAML::jkj::dragonbox::float_bits<DummyFormatTraits_293>;

}  // namespace

TEST(FloatBitsBinarySignificandTest_293, IsNoexcept_293) {
  EXPECT_TRUE((noexcept(FloatBitsDummy_293::binary_significand(carrier_uint{0}, exponent_int{0}))));
}

TEST(FloatBitsBinarySignificandTest_293, ReturnsSameAsFormatTraits_TypicalValues_293) {
  const carrier_uint s = static_cast<carrier_uint>(0x00ABCDEFu);
  const exponent_int e = static_cast<exponent_int>(17);

  const carrier_uint expected = DummyFormatTraits_293::binary_significand(s, e);
  const carrier_uint actual = FloatBitsDummy_293::binary_significand(s, e);

  EXPECT_EQ(actual, expected);
}

TEST(FloatBitsBinarySignificandTest_293, ReturnsSameAsFormatTraits_ZeroInputs_293) {
  const carrier_uint s = static_cast<carrier_uint>(0);
  const exponent_int e = static_cast<exponent_int>(0);

  EXPECT_EQ(FloatBitsDummy_293::binary_significand(s, e),
            DummyFormatTraits_293::binary_significand(s, e));
}

TEST(FloatBitsBinarySignificandTest_293, ReturnsSameAsFormatTraits_MaxCarrierUint_293) {
  const carrier_uint s = (std::numeric_limits<carrier_uint>::max)();
  const exponent_int e = static_cast<exponent_int>(0);

  EXPECT_EQ(FloatBitsDummy_293::binary_significand(s, e),
            DummyFormatTraits_293::binary_significand(s, e));
}

TEST(FloatBitsBinarySignificandTest_293, ReturnsSameAsFormatTraits_LargeExponentBits_293) {
  // Avoid assuming exponent_int signedness; use a value that is representable either way.
  const carrier_uint s = static_cast<carrier_uint>(1);
  const exponent_int e = static_cast<exponent_int>(std::numeric_limits<unsigned short>::max());

  EXPECT_EQ(FloatBitsDummy_293::binary_significand(s, e),
            DummyFormatTraits_293::binary_significand(s, e));
}

TEST(FloatBitsBinarySignificandTest_293, WorksInConstantExpressionContext_293) {
  constexpr carrier_uint s = static_cast<carrier_uint>(42);
  constexpr exponent_int e = static_cast<exponent_int>(5);

  constexpr carrier_uint expected = DummyFormatTraits_293::binary_significand(s, e);
  constexpr carrier_uint actual = FloatBitsDummy_293::binary_significand(s, e);

  static_assert(actual == expected, "float_bits::binary_significand should forward to FormatTraits");
  EXPECT_EQ(actual, expected);
}