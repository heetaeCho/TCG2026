// File: dragonbox_bit_cast_tests_268.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <type_traits>

#if __has_include(<bit>)
  #include <bit>
#endif

#include "contrib/dragonbox.h"

namespace {

class BitCastTest_268 : public ::testing::Test {};

template <typename To, typename From>
To ExpectedBitCast(const From& from) {
#if defined(__cpp_lib_bit_cast) && (__cpp_lib_bit_cast >= 201806L)
  return std::bit_cast<To>(from);
#else
  static_assert(sizeof(To) == sizeof(From), "ExpectedBitCast requires same-size types");
  static_assert(std::is_trivially_copyable<To>::value, "To must be trivially copyable");
  static_assert(std::is_trivially_copyable<From>::value, "From must be trivially copyable");
  To to{};
  std::memcpy(&to, &from, sizeof(To));
  return to;
#endif
}

}  // namespace

TEST_F(BitCastTest_268, Uint32ToFloatKnownBitPattern_268) {
  const std::uint32_t bits = 0x3f800000u;  // IEEE-754 1.0f
  const float got =
      YAML::jkj::dragonbox::detail::bit_cast<float>(bits);

  EXPECT_FLOAT_EQ(got, 1.0f);
}

TEST_F(BitCastTest_268, FloatToUint32MatchesExpected_268) {
  const float value = 1.0f;
  const std::uint32_t got =
      YAML::jkj::dragonbox::detail::bit_cast<std::uint32_t>(value);

  const std::uint32_t expected = ExpectedBitCast<std::uint32_t>(value);
  EXPECT_EQ(got, expected);
}

TEST_F(BitCastTest_268, FloatRoundTripPreservesAllBits_268) {
  // Use a value with a distinct bit pattern (not a simple power-of-two).
  const std::uint32_t original_bits = 0x40490fdbu;  // ~3.1415927f
  const float as_float =
      YAML::jkj::dragonbox::detail::bit_cast<float>(original_bits);

  const std::uint32_t roundtrip_bits =
      YAML::jkj::dragonbox::detail::bit_cast<std::uint32_t>(as_float);

  EXPECT_EQ(roundtrip_bits, original_bits);
}

TEST_F(BitCastTest_268, DoubleUint64RoundTripPreservesAllBits_268) {
  // A quiet NaN with a payload (bit pattern should be preserved by bit-cast).
  const std::uint64_t original_bits = 0x7ff8'0000'0000'00a5ULL;
  const double as_double =
      YAML::jkj::dragonbox::detail::bit_cast<double>(original_bits);

  const std::uint64_t roundtrip_bits =
      YAML::jkj::dragonbox::detail::bit_cast<std::uint64_t>(as_double);

  EXPECT_EQ(roundtrip_bits, original_bits);
}

TEST_F(BitCastTest_268, StructToUint32BitwiseCopyMatchesExpected_268) {
  struct Pair16 {
    std::uint16_t a;
    std::uint16_t b;
  };
  static_assert(std::is_trivially_copyable<Pair16>::value, "Pair16 must be trivially copyable");
  static_assert(sizeof(Pair16) == sizeof(std::uint32_t), "Pair16 must be 32-bit for this test");

  const Pair16 p{0x1122u, 0x3344u};

  const std::uint32_t got =
      YAML::jkj::dragonbox::detail::bit_cast<std::uint32_t>(p);

  const std::uint32_t expected = ExpectedBitCast<std::uint32_t>(p);
  EXPECT_EQ(got, expected);
}

TEST_F(BitCastTest_268, WorksWithConstInputReference_268) {
  const std::uint32_t bits = 0xbf800000u;  // IEEE-754 -1.0f
  const float got =
      YAML::jkj::dragonbox::detail::bit_cast<float>(bits);

  EXPECT_FLOAT_EQ(got, -1.0f);
}

TEST_F(BitCastTest_268, ConstexprEvaluationWhenAvailable_268) {
  // This test compiles as long as bit_cast is usable in constant evaluation.
  // (JKJ_CONSTEXPR20 suggests it is intended to be constexpr in C++20 mode.)
  constexpr std::uint32_t bits = 0x3f800000u;  // 1.0f
  constexpr float f = YAML::jkj::dragonbox::detail::bit_cast<float>(bits);
  static_assert(f == 1.0f, "bit_cast should preserve the 1.0f bit pattern at compile time");
  (void)f;

  SUCCEED();
}