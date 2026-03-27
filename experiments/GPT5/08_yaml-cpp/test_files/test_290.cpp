// TEST_ID: 290
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class To, class From>
To BitCast(const From& from) {
  static_assert(sizeof(To) == sizeof(From), "BitCast requires same-size types.");
  To to{};
  std::memcpy(&to, &from, sizeof(To));
  return to;
}

// Try hard to extract the underlying integer bits from signed_significand_bits<T>
// without assuming its exact internal layout.
// Preference order:
//  1) member `.u`
//  2) member `.value`
//  3) implicit/explicit conversion to an integer type
template <class T>
constexpr auto ExtractRawBits(const T& x) {
  if constexpr (requires { x.u; }) {
    return x.u;
  } else if constexpr (requires { x.value; }) {
    return x.value;
  } else if constexpr (std::is_convertible_v<T, std::uint64_t>) {
    return static_cast<std::uint64_t>(x);
  } else if constexpr (std::is_convertible_v<T, std::uint32_t>) {
    return static_cast<std::uint32_t>(x);
  } else if constexpr (std::is_convertible_v<T, std::int64_t>) {
    return static_cast<std::int64_t>(x);
  } else if constexpr (std::is_convertible_v<T, std::int32_t>) {
    return static_cast<std::int32_t>(x);
  } else {
    static_assert(sizeof(T) == 0, "Cannot extract raw bits from signed_significand_bits.");
  }
}

// Convert whatever we got into the carrier_uint expected by float_bits.
template <class CarrierUInt, class SignedOrUnsignedInt>
constexpr CarrierUInt ToCarrier(SignedOrUnsignedInt v) {
  using U = std::make_unsigned_t<std::remove_cv_t<std::remove_reference_t<SignedOrUnsignedInt>>>;
  return static_cast<CarrierUInt>(static_cast<U>(v));
}

}  // namespace

namespace YAML::jkj::dragonbox {

using FB32 = float_bits<ieee754_binary32>;
using FB64 = float_bits<ieee754_binary64>;

static_assert(noexcept(std::declval<const FB32&>().remove_exponent_bits()),
              "remove_exponent_bits() must be noexcept (FB32).");
static_assert(noexcept(std::declval<const FB64&>().remove_exponent_bits()),
              "remove_exponent_bits() must be noexcept (FB64).");

class FloatBitsRemoveExponentBitsTest_290 : public ::testing::Test {};

TEST_F(FloatBitsRemoveExponentBitsTest_290, RemovesExponentPreservesSignAndSignificand_Float_290) {
  const float v = 1.5f;
  const std::uint32_t bits = BitCast<std::uint32_t>(v);

  const FB32 fb(bits);
  const auto removed = fb.remove_exponent_bits();

  const auto raw = ExtractRawBits(removed);
  const std::uint32_t removed_bits = ToCarrier<std::uint32_t>(raw);
  const FB32 fb_removed(removed_bits);

  // Observable effects through the public interface:
  // - exponent bits should be removed (become 0 in the new bit pattern)
  // - sign and significand should match the original.
  EXPECT_EQ(fb_removed.extract_exponent_bits(), 0);
  EXPECT_EQ(fb_removed.extract_significand_bits(), fb.extract_significand_bits());
  EXPECT_EQ(fb_removed.is_negative(), fb.is_negative());
  EXPECT_EQ(fb_removed.is_positive(), fb.is_positive());
}

TEST_F(FloatBitsRemoveExponentBitsTest_290, RemovesExponentPreservesSignAndSignificand_NegativeFloat_290) {
  const float v = -2.75f;
  const std::uint32_t bits = BitCast<std::uint32_t>(v);

  const FB32 fb(bits);
  const auto removed = fb.remove_exponent_bits();

  const auto raw = ExtractRawBits(removed);
  const std::uint32_t removed_bits = ToCarrier<std::uint32_t>(raw);
  const FB32 fb_removed(removed_bits);

  EXPECT_EQ(fb_removed.extract_exponent_bits(), 0);
  EXPECT_EQ(fb_removed.extract_significand_bits(), fb.extract_significand_bits());
  EXPECT_TRUE(fb_removed.is_negative());
  EXPECT_FALSE(fb_removed.is_positive());
}

TEST_F(FloatBitsRemoveExponentBitsTest_290, HandlesZeroAndNegativeZero_Float_290) {
  for (float v : {0.0f, -0.0f}) {
    const std::uint32_t bits = BitCast<std::uint32_t>(v);
    const FB32 fb(bits);
    const auto removed = fb.remove_exponent_bits();

    const auto raw = ExtractRawBits(removed);
    const std::uint32_t removed_bits = ToCarrier<std::uint32_t>(raw);
    const FB32 fb_removed(removed_bits);

    EXPECT_EQ(fb_removed.extract_exponent_bits(), 0);
    EXPECT_EQ(fb_removed.extract_significand_bits(), fb.extract_significand_bits());
    EXPECT_EQ(fb_removed.is_negative(), fb.is_negative());
    EXPECT_EQ(fb_removed.is_positive(), fb.is_positive());
  }
}

TEST_F(FloatBitsRemoveExponentBitsTest_290, HandlesDenormMinSubnormal_Float_290) {
  const float v = std::numeric_limits<float>::denorm_min();
  const std::uint32_t bits = BitCast<std::uint32_t>(v);

  const FB32 fb(bits);
  ASSERT_TRUE(fb.is_nonzero());

  const auto removed = fb.remove_exponent_bits();
  const auto raw = ExtractRawBits(removed);
  const std::uint32_t removed_bits = ToCarrier<std::uint32_t>(raw);
  const FB32 fb_removed(removed_bits);

  EXPECT_EQ(fb_removed.extract_exponent_bits(), 0);
  EXPECT_EQ(fb_removed.extract_significand_bits(), fb.extract_significand_bits());
  EXPECT_EQ(fb_removed.is_negative(), fb.is_negative());
}

TEST_F(FloatBitsRemoveExponentBitsTest_290, HandlesInfinityAndNaN_Float_290) {
  const float inf = std::numeric_limits<float>::infinity();
  const float nan = std::numeric_limits<float>::quiet_NaN();

  for (float v : {inf, -inf, nan}) {
    const std::uint32_t bits = BitCast<std::uint32_t>(v);
    const FB32 fb(bits);

    const auto removed = fb.remove_exponent_bits();
    const auto raw = ExtractRawBits(removed);
    const std::uint32_t removed_bits = ToCarrier<std::uint32_t>(raw);
    const FB32 fb_removed(removed_bits);

    // We only assert the observable effect implied by the API name:
    // exponent bits are removed.
    EXPECT_EQ(fb_removed.extract_exponent_bits(), 0);
    // And that sign is preserved (NaN sign may vary by platform, but the input bitpattern is fixed).
    EXPECT_EQ(fb_removed.is_negative(), fb.is_negative());
  }
}

TEST_F(FloatBitsRemoveExponentBitsTest_290, RemovesExponentPreservesSignAndSignificand_Double_290) {
  const double v = -12345.6789;
  const std::uint64_t bits = BitCast<std::uint64_t>(v);

  const FB64 fb(bits);
  const auto removed = fb.remove_exponent_bits();

  const auto raw = ExtractRawBits(removed);
  const std::uint64_t removed_bits = ToCarrier<std::uint64_t>(raw);
  const FB64 fb_removed(removed_bits);

  EXPECT_EQ(fb_removed.extract_exponent_bits(), 0);
  EXPECT_EQ(fb_removed.extract_significand_bits(), fb.extract_significand_bits());
  EXPECT_EQ(fb_removed.is_negative(), fb.is_negative());
  EXPECT_EQ(fb_removed.is_positive(), fb.is_positive());
}

}  // namespace YAML::jkj::dragonbox