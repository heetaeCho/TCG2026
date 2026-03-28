// TEST_ID: 287
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "contrib/dragonbox.h"

namespace {

struct RecordingFormatTraits_287 {
  using carrier_uint = std::uint64_t;

  static inline carrier_uint last_arg = 0;
  static inline int call_count = 0;

  // Intentionally non-constexpr so we can record observable external interaction.
  static bool has_even_significand_bits(carrier_uint u) noexcept {
    last_arg = u;
    ++call_count;
    return (u % 2u) == 0u;
  }

  static void Reset() {
    last_arg = 0;
    call_count = 0;
  }
};

struct ConstexprFormatTraits_287 {
  using carrier_uint = std::uint64_t;
  static constexpr bool has_even_significand_bits(carrier_uint u) noexcept {
    return (u % 2u) == 0u;
  }
};

using SignedBitsRecording_287 =
    YAML::jkj::dragonbox::signed_significand_bits<RecordingFormatTraits_287>;
using SignedBitsConstexpr_287 =
    YAML::jkj::dragonbox::signed_significand_bits<ConstexprFormatTraits_287>;

class HasEvenSignificandBitsTest_287 : public ::testing::Test {
 protected:
  void SetUp() override { RecordingFormatTraits_287::Reset(); }
};

TEST_F(HasEvenSignificandBitsTest_287, EvenBitPatternReturnsTrue_287) {
  const SignedBitsRecording_287 v(static_cast<RecordingFormatTraits_287::carrier_uint>(4));

  EXPECT_NO_THROW({
    const bool result = v.has_even_significand_bits();
    EXPECT_TRUE(result);
  });

  EXPECT_EQ(RecordingFormatTraits_287::call_count, 1);
  EXPECT_EQ(RecordingFormatTraits_287::last_arg, 4u);
}

TEST_F(HasEvenSignificandBitsTest_287, OddBitPatternReturnsFalse_287) {
  const SignedBitsRecording_287 v(static_cast<RecordingFormatTraits_287::carrier_uint>(5));

  const bool result = v.has_even_significand_bits();
  EXPECT_FALSE(result);

  EXPECT_EQ(RecordingFormatTraits_287::call_count, 1);
  EXPECT_EQ(RecordingFormatTraits_287::last_arg, 5u);
}

TEST_F(HasEvenSignificandBitsTest_287, ZeroBitPatternBoundary_287) {
  const SignedBitsRecording_287 v(static_cast<RecordingFormatTraits_287::carrier_uint>(0));

  const bool result = v.has_even_significand_bits();
  EXPECT_TRUE(result);  // Based on RecordingFormatTraits_287 definition.

  EXPECT_EQ(RecordingFormatTraits_287::call_count, 1);
  EXPECT_EQ(RecordingFormatTraits_287::last_arg, 0u);
}

TEST_F(HasEvenSignificandBitsTest_287, MaxBitPatternBoundary_287) {
  const auto maxv = std::numeric_limits<RecordingFormatTraits_287::carrier_uint>::max();
  const SignedBitsRecording_287 v(maxv);

  const bool result = v.has_even_significand_bits();
  EXPECT_FALSE(result);  // max for uint64_t is odd

  EXPECT_EQ(RecordingFormatTraits_287::call_count, 1);
  EXPECT_EQ(RecordingFormatTraits_287::last_arg, maxv);
}

TEST_F(HasEvenSignificandBitsTest_287, MultipleCallsInvokeFormatTraitsEachTime_287) {
  const SignedBitsRecording_287 v(static_cast<RecordingFormatTraits_287::carrier_uint>(10));

  EXPECT_TRUE(v.has_even_significand_bits());
  EXPECT_TRUE(v.has_even_significand_bits());
  EXPECT_TRUE(v.has_even_significand_bits());

  EXPECT_EQ(RecordingFormatTraits_287::call_count, 3);
  EXPECT_EQ(RecordingFormatTraits_287::last_arg, 10u);
}

// Verifies the API is usable in constant evaluation when the FormatTraits hook is constexpr.
static_assert(SignedBitsConstexpr_287(0u).has_even_significand_bits(),
              "Expected even bit-pattern to report true in constexpr context (TEST_ID 287)");
static_assert(!SignedBitsConstexpr_287(1u).has_even_significand_bits(),
              "Expected odd bit-pattern to report false in constexpr context (TEST_ID 287)");

}  // namespace