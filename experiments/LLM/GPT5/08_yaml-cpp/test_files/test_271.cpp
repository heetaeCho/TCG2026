// File: ./TestProjects/yaml-cpp/test/dragonbox_remove_exponent_bits_271_test.cpp

#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::ieee754_binary_traits;

struct DummyFormat32 {
  static constexpr int significand_bits = 23;
  static constexpr int exponent_bits = 8;
};

struct DummyFormat64 {
  static constexpr int significand_bits = 52;
  static constexpr int exponent_bits = 11;
};

template <typename UInt, typename Format>
constexpr UInt MakeBits(UInt sign_bit, UInt exponent_bits, UInt significand_bits) {
  // Layout: [sign | exponent | significand], where exponent is shifted by significand_bits.
  constexpr int sig = Format::significand_bits;
  constexpr int exp = Format::exponent_bits;

  const UInt sign_shift = UInt(sig + exp);
  return (sign_bit << sign_shift) | (exponent_bits << UInt(sig)) | significand_bits;
}

class Ieee754BinaryTraitsRemoveExponentBitsTest_271 : public ::testing::Test {};

TEST_F(Ieee754BinaryTraitsRemoveExponentBitsTest_271, ClearsExponentBitsFor32BitCarrier_271) {
  using Traits = ieee754_binary_traits<DummyFormat32, std::uint32_t, std::int32_t>;

  const std::uint32_t sign = 0;
  const std::uint32_t significand = 0x0055AAu;  // within 23 bits
  const std::uint32_t exponent1 = 0x01u;
  const std::uint32_t exponent2 = 0x7Fu;

  const std::uint32_t u1 = MakeBits<std::uint32_t, DummyFormat32>(sign, exponent1, significand);
  const std::uint32_t u2 = MakeBits<std::uint32_t, DummyFormat32>(sign, exponent2, significand);

  const std::uint32_t r1 = Traits::remove_exponent_bits(u1);
  const std::uint32_t r2 = Traits::remove_exponent_bits(u2);

  const std::uint32_t expected = MakeBits<std::uint32_t, DummyFormat32>(sign, 0u, significand);
  EXPECT_EQ(r1, expected);
  EXPECT_EQ(r2, expected);
}

TEST_F(Ieee754BinaryTraitsRemoveExponentBitsTest_271, PreservesSignAndSignificandFor32BitCarrier_271) {
  using Traits = ieee754_binary_traits<DummyFormat32, std::uint32_t, std::int32_t>;

  const std::uint32_t sign = 1;
  const std::uint32_t significand = 0x7FFFFFu;  // all ones in 23 bits
  const std::uint32_t exponent = 0x55u;

  const std::uint32_t u = MakeBits<std::uint32_t, DummyFormat32>(sign, exponent, significand);
  const std::uint32_t r = Traits::remove_exponent_bits(u);

  // Exponent should be cleared; sign and significand should remain.
  const std::uint32_t expected = MakeBits<std::uint32_t, DummyFormat32>(sign, 0u, significand);
  EXPECT_EQ(r, expected);
}

TEST_F(Ieee754BinaryTraitsRemoveExponentBitsTest_271, HandlesAllOnesExponentFor32BitCarrier_271) {
  using Traits = ieee754_binary_traits<DummyFormat32, std::uint32_t, std::int32_t>;

  const std::uint32_t sign = 0;
  const std::uint32_t significand = 0x000001u;
  const std::uint32_t exponent_all_ones = (std::uint32_t(1u) << DummyFormat32::exponent_bits) - 1u;

  const std::uint32_t u =
      MakeBits<std::uint32_t, DummyFormat32>(sign, exponent_all_ones, significand);
  const std::uint32_t r = Traits::remove_exponent_bits(u);

  const std::uint32_t expected = MakeBits<std::uint32_t, DummyFormat32>(sign, 0u, significand);
  EXPECT_EQ(r, expected);
}

TEST_F(Ieee754BinaryTraitsRemoveExponentBitsTest_271, ClearsExponentBitsFor64BitCarrier_271) {
  using Traits = ieee754_binary_traits<DummyFormat64, std::uint64_t, std::int32_t>;

  const std::uint64_t sign = 1;
  const std::uint64_t significand = 0x000F'FFFF'FFFF'FFFFull & ((std::uint64_t(1) << DummyFormat64::significand_bits) - 1);
  const std::uint64_t exponent = 0x3FFull;  // typical bias for double exponent bits (value here is just a bit-pattern)

  const std::uint64_t u = MakeBits<std::uint64_t, DummyFormat64>(sign, exponent, significand);
  const std::uint64_t r = Traits::remove_exponent_bits(u);

  const std::uint64_t expected = MakeBits<std::uint64_t, DummyFormat64>(sign, 0ull, significand);
  EXPECT_EQ(r, expected);
}

TEST_F(Ieee754BinaryTraitsRemoveExponentBitsTest_271, IsConstexprEvaluable_271) {
  using Traits32 = ieee754_binary_traits<DummyFormat32, std::uint32_t, std::int32_t>;

  constexpr std::uint32_t sign = 1;
  constexpr std::uint32_t significand = 0x123456u & ((std::uint32_t(1u) << DummyFormat32::significand_bits) - 1u);
  constexpr std::uint32_t exponent = 0x42u;

  constexpr std::uint32_t u = MakeBits<std::uint32_t, DummyFormat32>(sign, exponent, significand);
  constexpr std::uint32_t r = Traits32::remove_exponent_bits(u);
  constexpr std::uint32_t expected = MakeBits<std::uint32_t, DummyFormat32>(sign, 0u, significand);

  static_assert(r == expected, "remove_exponent_bits should be constexpr and clear exponent bits.");
  EXPECT_EQ(r, expected);
}

}  // namespace