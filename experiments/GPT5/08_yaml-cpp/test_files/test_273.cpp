// File: ./TestProjects/yaml-cpp/test/dragonbox_ieee754_binary_exponent_test.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

struct TestFormat_273 {
  // Pick distinctive values to make mistakes obvious.
  static constexpr std::int32_t min_exponent = -1234;
  static constexpr std::int32_t exponent_bias = 567;
};

using Traits_273 = YAML::jkj::dragonbox::ieee754_binary_traits<TestFormat_273, std::uint32_t, std::int32_t>;

}  // namespace

TEST(Ieee754BinaryTraitsBinaryExponentTest_273, IsNoexcept_273) {
  static_assert(noexcept(Traits_273::binary_exponent(0)), "binary_exponent must be noexcept");
  EXPECT_TRUE(noexcept(Traits_273::binary_exponent(0)));
}

TEST(Ieee754BinaryTraitsBinaryExponentTest_273, ReturnsExponentIntType_273) {
  using ReturnT = decltype(Traits_273::binary_exponent(std::int32_t{0}));
  static_assert(std::is_same<ReturnT, std::int32_t>::value, "Return type must be ExponentInt");
  EXPECT_TRUE((std::is_same<ReturnT, std::int32_t>::value));
}

TEST(Ieee754BinaryTraitsBinaryExponentTest_273, ZeroExponentBitsUsesMinExponent_273) {
  EXPECT_EQ(Traits_273::binary_exponent(0), TestFormat_273::min_exponent);

  // Also verify it is usable in constant evaluation.
  static_assert(Traits_273::binary_exponent(0) == TestFormat_273::min_exponent,
                "constexpr: zero exponent bits should map to min_exponent");
}

TEST(Ieee754BinaryTraitsBinaryExponentTest_273, NonZeroExponentBitsAddsBias_273) {
  EXPECT_EQ(Traits_273::binary_exponent(1), 1 + TestFormat_273::exponent_bias);
  EXPECT_EQ(Traits_273::binary_exponent(2), 2 + TestFormat_273::exponent_bias);

  static_assert(Traits_273::binary_exponent(1) == 1 + TestFormat_273::exponent_bias,
                "constexpr: nonzero exponent bits should add exponent_bias");
}

TEST(Ieee754BinaryTraitsBinaryExponentTest_273, BoundaryTypicalLargeExponentBits_273) {
  // Use a "large but safe" value for the chosen ExponentInt.
  const std::int32_t bits = 255;
  EXPECT_EQ(Traits_273::binary_exponent(bits), bits + TestFormat_273::exponent_bias);
}

TEST(Ieee754BinaryTraitsBinaryExponentTest_273, NegativeExponentBitsAreTreatedAsNonZero_273) {
  // The interface accepts exponent_int; only zero is special-cased.
  const std::int32_t bits = -1;
  EXPECT_EQ(Traits_273::binary_exponent(bits), bits + TestFormat_273::exponent_bias);
}