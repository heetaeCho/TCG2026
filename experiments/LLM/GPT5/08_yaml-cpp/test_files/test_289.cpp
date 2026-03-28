// File: ./TestProjects/yaml-cpp/test/dragonbox_float_bits_extract_significand_bits_test_289.cpp

#include <cstdint>
#include <type_traits>

#include "gtest/gtest.h"

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::carrier_uint;

// A controllable FormatTraits used to observe calls made by float_bits<FormatTraits>.
struct RecordingFormatTraits_289 {
  // Keep these types simple; float_bits only needs carrier_uint for this test file.
  using carrier_uint = ::YAML::jkj::dragonbox::carrier_uint;

  inline static carrier_uint last_arg = 0;
  inline static int call_count = 0;
  inline static carrier_uint return_value = 0;

  static constexpr carrier_uint extract_significand_bits(carrier_uint u) noexcept {
    // Not relying on float_bits internals; this is our external collaborator.
    ++call_count;
    last_arg = u;
    return return_value;
  }

  static void Reset() {
    last_arg = 0;
    call_count = 0;
    return_value = 0;
  }
};

using FloatBits_289 = ::YAML::jkj::dragonbox::float_bits<RecordingFormatTraits_289>;

class FloatBitsExtractSignificandBitsTest_289 : public ::testing::Test {
protected:
  void SetUp() override { RecordingFormatTraits_289::Reset(); }
};

}  // namespace

TEST_F(FloatBitsExtractSignificandBitsTest_289, ReturnsValueFromTraits_289) {
  RecordingFormatTraits_289::return_value = static_cast<carrier_uint>(0xA5A5u);

  const FloatBits_289 fb(static_cast<carrier_uint>(0x1234u));
  const carrier_uint out = fb.extract_significand_bits();

  EXPECT_EQ(out, static_cast<carrier_uint>(0xA5A5u));
  EXPECT_EQ(RecordingFormatTraits_289::call_count, 1);
}

TEST_F(FloatBitsExtractSignificandBitsTest_289, ForwardsBitPatternToTraits_289) {
  RecordingFormatTraits_289::return_value = static_cast<carrier_uint>(0x1u);

  const carrier_uint pattern = static_cast<carrier_uint>(0xDEADBEEFu);
  const FloatBits_289 fb(pattern);
  (void)fb.extract_significand_bits();

  EXPECT_EQ(RecordingFormatTraits_289::last_arg, pattern);
  EXPECT_EQ(RecordingFormatTraits_289::call_count, 1);
}

TEST_F(FloatBitsExtractSignificandBitsTest_289, CanBeCalledMultipleTimes_289) {
  RecordingFormatTraits_289::return_value = static_cast<carrier_uint>(0x7u);

  const carrier_uint pattern = static_cast<carrier_uint>(0x5555u);
  const FloatBits_289 fb(pattern);

  EXPECT_EQ(fb.extract_significand_bits(), static_cast<carrier_uint>(0x7u));
  EXPECT_EQ(fb.extract_significand_bits(), static_cast<carrier_uint>(0x7u));
  EXPECT_EQ(RecordingFormatTraits_289::call_count, 2);
  EXPECT_EQ(RecordingFormatTraits_289::last_arg, pattern);
}

TEST_F(FloatBitsExtractSignificandBitsTest_289, BoundaryBitPatternsForwarded_289) {
  RecordingFormatTraits_289::return_value = static_cast<carrier_uint>(0x42u);

  {
    const carrier_uint pattern0 = static_cast<carrier_uint>(0);
    const FloatBits_289 fb0(pattern0);
    EXPECT_EQ(fb0.extract_significand_bits(), static_cast<carrier_uint>(0x42u));
    EXPECT_EQ(RecordingFormatTraits_289::last_arg, pattern0);
  }

  RecordingFormatTraits_289::Reset();
  RecordingFormatTraits_289::return_value = static_cast<carrier_uint>(0x99u);

  {
    const carrier_uint pattern_max = ~static_cast<carrier_uint>(0);
    const FloatBits_289 fbmax(pattern_max);
    EXPECT_EQ(fbmax.extract_significand_bits(), static_cast<carrier_uint>(0x99u));
    EXPECT_EQ(RecordingFormatTraits_289::last_arg, pattern_max);
  }
}

TEST(FloatBitsExtractSignificandBitsCompileTimeTest_289, IsNoexcept_289) {
  // Construct with a known pattern (avoid default construction).
  const FloatBits_289 fb(static_cast<carrier_uint>(0));
  static_assert(noexcept(fb.extract_significand_bits()),
                "extract_significand_bits() must be noexcept");
  (void)fb;
}

TEST(FloatBitsExtractSignificandBitsCompileTimeTest_289, WorksInConstexprContext_289) {
  // A constexpr traits for a compile-time check (no runtime state).
  struct ConstexprTraits_289 {
    using carrier_uint = ::YAML::jkj::dragonbox::carrier_uint;
    static constexpr carrier_uint extract_significand_bits(carrier_uint u) noexcept {
      // Any deterministic constexpr mapping is fine; we only verify float_bits forwards and returns.
      return static_cast<carrier_uint>(u ^ static_cast<carrier_uint>(0xFFu));
    }
  };

  using ConstexprFloatBits_289 = ::YAML::jkj::dragonbox::float_bits<ConstexprTraits_289>;

  constexpr carrier_uint pattern = static_cast<carrier_uint>(0x1234u);
  constexpr ConstexprFloatBits_289 fb(pattern);
  constexpr carrier_uint out = fb.extract_significand_bits();

  static_assert(out == static_cast<carrier_uint>(pattern ^ static_cast<carrier_uint>(0xFFu)),
                "constexpr extract_significand_bits() should return the traits result");
}