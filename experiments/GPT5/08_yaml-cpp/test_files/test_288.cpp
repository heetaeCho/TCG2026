// TEST_ID: 288
// File: ./TestProjects/yaml-cpp/test/dragonbox_float_bits_extract_exponent_bits_test_288.cpp

#include <cstdint>
#include <type_traits>

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using ::YAML::jkj::dragonbox::float_bits;

// A constexpr-friendly traits type: extract_exponent_bits(u) == u (cast).
struct ConstexprTraits_288 {
  using carrier_uint = std::uint32_t;
  using exponent_int = std::int32_t;

  static constexpr exponent_int extract_exponent_bits(carrier_uint u) noexcept {
    return static_cast<exponent_int>(u);
  }
};

// A runtime-recording traits type to verify the external interaction (call + parameter).
struct RecordingTraits_288 {
  using carrier_uint = std::uint32_t;
  using exponent_int = std::int32_t;

  static inline int call_count = 0;
  static inline carrier_uint last_arg = 0;

  static exponent_int extract_exponent_bits(carrier_uint u) noexcept {
    ++call_count;
    last_arg = u;
    return static_cast<exponent_int>(u);
  }

  static void Reset() {
    call_count = 0;
    last_arg = 0;
  }
};

class FloatBitsTest_288 : public ::testing::Test {
 protected:
  void SetUp() override { RecordingTraits_288::Reset(); }
};

TEST_F(FloatBitsTest_288, ExtractExponentBits_ForwardsBitPattern_288) {
  // If float_bits forwards `u` to FormatTraits::extract_exponent_bits(u),
  // and our traits returns u, then the result should equal the bit pattern.
  float_bits<ConstexprTraits_288> fb0(ConstexprTraits_288::carrier_uint{0u});
  EXPECT_EQ(fb0.extract_exponent_bits(), 0);

  float_bits<ConstexprTraits_288> fb1(ConstexprTraits_288::carrier_uint{1u});
  EXPECT_EQ(fb1.extract_exponent_bits(), 1);

  float_bits<ConstexprTraits_288> fb2(ConstexprTraits_288::carrier_uint{0x12345678u});
  EXPECT_EQ(fb2.extract_exponent_bits(),
            static_cast<ConstexprTraits_288::exponent_int>(0x12345678u));

  float_bits<ConstexprTraits_288> fb3(ConstexprTraits_288::carrier_uint{0xFFFFFFFFu});
  EXPECT_EQ(fb3.extract_exponent_bits(),
            static_cast<ConstexprTraits_288::exponent_int>(0xFFFFFFFFu));
}

TEST_F(FloatBitsTest_288, ExtractExponentBits_InvokesTraitsWithStoredValue_288) {
  float_bits<RecordingTraits_288> fbA(RecordingTraits_288::carrier_uint{0xABCD1234u});
  const auto outA = fbA.extract_exponent_bits();

  EXPECT_EQ(RecordingTraits_288::call_count, 1);
  EXPECT_EQ(RecordingTraits_288::last_arg, 0xABCD1234u);
  EXPECT_EQ(outA, static_cast<RecordingTraits_288::exponent_int>(0xABCD1234u));

  float_bits<RecordingTraits_288> fbB(RecordingTraits_288::carrier_uint{0u});
  const auto outB = fbB.extract_exponent_bits();

  EXPECT_EQ(RecordingTraits_288::call_count, 2);
  EXPECT_EQ(RecordingTraits_288::last_arg, 0u);
  EXPECT_EQ(outB, 0);
}

TEST_F(FloatBitsTest_288, ExtractExponentBits_IsNoexcept_288) {
  using FB = float_bits<ConstexprTraits_288>;
  static_assert(noexcept(std::declval<const FB&>().extract_exponent_bits()),
                "extract_exponent_bits() must be noexcept");
  SUCCEED();
}

TEST_F(FloatBitsTest_288, ExtractExponentBits_IsConstexprEvaluatable_288) {
  // Verifies the method can be evaluated at compile time (given constexpr traits).
  using FB = float_bits<ConstexprTraits_288>;

  constexpr FB fb(ConstexprTraits_288::carrier_uint{42u});
  static_assert(fb.extract_exponent_bits() == 42, "constexpr evaluation failed");

  SUCCEED();
}

}  // namespace