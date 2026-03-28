// TEST_ID: 294
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

template <typename FormatTraits>
void ExpectBinarySignificandMatchesStatic(YAML::jkj::dragonbox::carrier_uint bit_pattern) {
  using FB = YAML::jkj::dragonbox::float_bits<FormatTraits>;

  constexpr bool kIsNoexcept =
      noexcept(std::declval<const FB&>().binary_significand()) &&
      noexcept(FB::binary_significand(std::declval<YAML::jkj::dragonbox::carrier_uint>(),
                                      std::declval<YAML::jkj::dragonbox::exponent_int>()));
  (void)kIsNoexcept;  // keeps -Wunused-variable away in some builds

  const FB fb(bit_pattern);

  const auto sig_bits = fb.extract_significand_bits();
  const auto exp_bits = fb.extract_exponent_bits();

  const auto expected = FB::binary_significand(sig_bits, exp_bits);
  const auto actual = fb.binary_significand();

  EXPECT_EQ(actual, expected) << "bit_pattern=" << static_cast<unsigned long long>(bit_pattern);
}

template <typename FormatTraits>
void RunCommonPatterns() {
  using CU = YAML::jkj::dragonbox::carrier_uint;

  // Normal-ish patterns.
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{1});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{2});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{3});

  // Boundary-ish patterns.
  ExpectBinarySignificandMatchesStatic<FormatTraits>((std::numeric_limits<CU>::max)());
  ExpectBinarySignificandMatchesStatic<FormatTraits>((std::numeric_limits<CU>::max)() - CU{1});

  // Some mixed bit patterns (portable constants).
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0xAAAAAAAAAAAAAAAAull});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0x5555555555555555ull});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0x8000000000000000ull});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0x7FFFFFFFFFFFFFFFull});

  // A few "random-looking" patterns.
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0x0123456789ABCDEFull});
  ExpectBinarySignificandMatchesStatic<FormatTraits>(CU{0xFEDCBA9876543210ull});
}

}  // namespace

class FloatBitsBinarySignificandTest_294 : public ::testing::Test {};

TEST_F(FloatBitsBinarySignificandTest_294, MatchesStaticForBinary32_294) {
  // Uses the public interface only:
  // - extract_significand_bits()
  // - extract_exponent_bits()
  // - static binary_significand(sig_bits, exp_bits)
  // - member binary_significand()
  RunCommonPatterns<YAML::jkj::dragonbox::ieee754_binary32>();
}

TEST_F(FloatBitsBinarySignificandTest_294, MatchesStaticForBinary64_294) {
  RunCommonPatterns<YAML::jkj::dragonbox::ieee754_binary64>();
}

TEST_F(FloatBitsBinarySignificandTest_294, ConstexprEvaluationAgreesWithRuntime_294) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary64;
  using FB = YAML::jkj::dragonbox::float_bits<Traits>;
  using CU = YAML::jkj::dragonbox::carrier_uint;

  constexpr CU kPattern = CU{0x0123456789ABCDEFull};
  constexpr FB kFb(kPattern);

  constexpr auto kExpected =
      FB::binary_significand(kFb.extract_significand_bits(), kFb.extract_exponent_bits());
  constexpr auto kActual = kFb.binary_significand();

  static_assert(kActual == kExpected, "binary_significand() should match static computation");

  // Also verify the same relationship at runtime (observable behavior).
  const FB fb_rt(kPattern);
  EXPECT_EQ(fb_rt.binary_significand(),
            FB::binary_significand(fb_rt.extract_significand_bits(), fb_rt.extract_exponent_bits()));
}

TEST_F(FloatBitsBinarySignificandTest_294, DoesNotDependOnObjectMutability_294) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary32;
  using FB = YAML::jkj::dragonbox::float_bits<Traits>;
  using CU = YAML::jkj::dragonbox::carrier_uint;

  const FB fb(CU{0xFEDCBA9876543210ull});

  const auto first = fb.binary_significand();
  const auto second = fb.binary_significand();

  EXPECT_EQ(first, second);
}