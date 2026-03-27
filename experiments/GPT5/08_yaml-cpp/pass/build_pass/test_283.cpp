// TEST_ID: 283
// File: test_signed_significand_bits_283.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "contrib/dragonbox.h"

namespace {

// A traits type that records the last argument passed to remove_sign_bit_and_shift().
struct RecordingFormatTraits_283 {
  using carrier_uint = std::uint32_t;

  inline static carrier_uint last_arg = 0;

  static carrier_uint remove_sign_bit_and_shift(carrier_uint x) noexcept {
    last_arg = x;
    // Deterministic transform so tests can verify delegation without assuming bit semantics.
    return static_cast<carrier_uint>(x ^ 0xA5A5A5A5u);
  }

  static void Reset() { last_arg = 0; }
};

// A traits type usable in constant evaluation (no side effects).
struct ConstexprFormatTraits_283 {
  using carrier_uint = std::uint32_t;

  static constexpr carrier_uint remove_sign_bit_and_shift(carrier_uint x) noexcept {
    // Any deterministic pure transform is fine; we only verify delegation.
    return static_cast<carrier_uint>((x * 3u) + 1u);
  }
};

using SBitsRec_283 = YAML::jkj::dragonbox::signed_significand_bits<RecordingFormatTraits_283>;
using SBitsCx_283  = YAML::jkj::dragonbox::signed_significand_bits<ConstexprFormatTraits_283>;

}  // namespace

TEST(SignedSignificandBitsTest_283, RemoveSignBitAndShift_DelegatesAndReturnsValue_283) {
  RecordingFormatTraits_283::Reset();

  const RecordingFormatTraits_283::carrier_uint pattern = 0x12345678u;
  const SBitsRec_283 bits(pattern);

  const auto out = bits.remove_sign_bit_and_shift();

  EXPECT_EQ(RecordingFormatTraits_283::last_arg, pattern);
  EXPECT_EQ(out, RecordingFormatTraits_283::remove_sign_bit_and_shift(pattern));
}

TEST(SignedSignificandBitsTest_283, RemoveSignBitAndShift_BoundaryZero_283) {
  RecordingFormatTraits_283::Reset();

  const RecordingFormatTraits_283::carrier_uint pattern = 0u;
  const SBitsRec_283 bits(pattern);

  const auto out = bits.remove_sign_bit_and_shift();

  EXPECT_EQ(RecordingFormatTraits_283::last_arg, pattern);
  EXPECT_EQ(out, RecordingFormatTraits_283::remove_sign_bit_and_shift(pattern));
}

TEST(SignedSignificandBitsTest_283, RemoveSignBitAndShift_BoundaryMax_283) {
  RecordingFormatTraits_283::Reset();

  const RecordingFormatTraits_283::carrier_uint pattern =
      std::numeric_limits<RecordingFormatTraits_283::carrier_uint>::max();
  const SBitsRec_283 bits(pattern);

  const auto out = bits.remove_sign_bit_and_shift();

  EXPECT_EQ(RecordingFormatTraits_283::last_arg, pattern);
  EXPECT_EQ(out, RecordingFormatTraits_283::remove_sign_bit_and_shift(pattern));
}

TEST(SignedSignificandBitsTest_283, RemoveSignBitAndShift_IsNoexcept_283) {
  const SBitsRec_283 bits(0u);
  static_assert(noexcept(bits.remove_sign_bit_and_shift()),
                "remove_sign_bit_and_shift() must be noexcept");
  (void)bits;
}

TEST(SignedSignificandBitsTest_283, RemoveSignBitAndShift_IsConstexprEvaluable_283) {
  constexpr ConstexprFormatTraits_283::carrier_uint pattern = 42u;
  constexpr SBitsCx_283 bits(pattern);

  constexpr auto out = bits.remove_sign_bit_and_shift();
  static_assert(out == ConstexprFormatTraits_283::remove_sign_bit_and_shift(pattern),
                "remove_sign_bit_and_shift() should delegate in constexpr context");
}