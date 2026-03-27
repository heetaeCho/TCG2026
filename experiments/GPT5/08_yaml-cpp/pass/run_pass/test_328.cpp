// File: ./TestProjects/yaml-cpp/test/dragonbox_add_sign_to_unsigned_decimal_fp_test.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class SigT, class ExpT>
using UnsignedFp = YAML::jkj::dragonbox::unsigned_decimal_fp<SigT, ExpT, false>;

template <class SigT, class ExpT>
using SignedFp = YAML::jkj::dragonbox::signed_decimal_fp<SigT, ExpT, false>;

template <class SigT, class ExpT>
constexpr SignedFp<SigT, ExpT> CallAddSign(bool is_negative, UnsignedFp<SigT, ExpT> r) {
  return YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(is_negative, r);
}

}  // namespace

TEST(AddSignToUnsignedDecimalFpTest_328, PreservesSignificandAndExponent_PositiveSign_328) {
  using SigT = std::uint32_t;
  using ExpT = std::int32_t;

  UnsignedFp<SigT, ExpT> in{SigT{123456u}, ExpT{-42}};
  auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(false, in);

  EXPECT_EQ(out.significand, in.significand);
  EXPECT_EQ(out.exponent, in.exponent);
  EXPECT_FALSE(out.is_negative);
}

TEST(AddSignToUnsignedDecimalFpTest_328, PreservesSignificandAndExponent_NegativeSign_328) {
  using SigT = std::uint32_t;
  using ExpT = std::int32_t;

  UnsignedFp<SigT, ExpT> in{SigT{7u}, ExpT{0}};
  auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(true, in);

  EXPECT_EQ(out.significand, in.significand);
  EXPECT_EQ(out.exponent, in.exponent);
  EXPECT_TRUE(out.is_negative);
}

TEST(AddSignToUnsignedDecimalFpTest_328, WorksWithDifferentIntegralTypes_328) {
  using SigT = std::uint64_t;
  using ExpT = std::int16_t;

  UnsignedFp<SigT, ExpT> in{SigT{999999999999ull}, ExpT{123}};
  auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(true, in);

  EXPECT_EQ(out.significand, in.significand);
  EXPECT_EQ(out.exponent, in.exponent);
  EXPECT_TRUE(out.is_negative);
}

TEST(AddSignToUnsignedDecimalFpTest_328, BoundaryValues_ArePreserved_328) {
  using SigT = std::uint64_t;
  using ExpT = std::int32_t;

  const SigT sig_max = (std::numeric_limits<SigT>::max)();
  const ExpT exp_min = (std::numeric_limits<ExpT>::min)();
  const ExpT exp_max = (std::numeric_limits<ExpT>::max)();

  {
    UnsignedFp<SigT, ExpT> in{sig_max, exp_min};
    auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(false, in);
    EXPECT_EQ(out.significand, sig_max);
    EXPECT_EQ(out.exponent, exp_min);
    EXPECT_FALSE(out.is_negative);
  }

  {
    UnsignedFp<SigT, ExpT> in{SigT{0}, exp_max};
    auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(true, in);
    EXPECT_EQ(out.significand, SigT{0});
    EXPECT_EQ(out.exponent, exp_max);
    EXPECT_TRUE(out.is_negative);
  }
}

TEST(AddSignToUnsignedDecimalFpTest_328, IsNoexcept_328) {
  using SigT = std::uint32_t;
  using ExpT = std::int32_t;

  UnsignedFp<SigT, ExpT> in{SigT{1u}, ExpT{2}};
  static_assert(noexcept(
                    YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(false, in)),
                "add_sign_to_unsigned_decimal_fp must be noexcept");
  (void)in;
}

TEST(AddSignToUnsignedDecimalFpTest_328, IsConstexprUsable_328) {
  using SigT = std::uint32_t;
  using ExpT = std::int32_t;

  // Verify constexpr evaluation and field mapping.
  constexpr UnsignedFp<SigT, ExpT> in{SigT{42u}, ExpT{-7}};
  constexpr auto out_pos = CallAddSign<SigT, ExpT>(false, in);
  constexpr auto out_neg = CallAddSign<SigT, ExpT>(true, in);

  static_assert(out_pos.significand == SigT{42u}, "significand must be preserved");
  static_assert(out_pos.exponent == ExpT{-7}, "exponent must be preserved");
  static_assert(out_pos.is_negative == false, "sign must reflect is_negative=false");

  static_assert(out_neg.significand == SigT{42u}, "significand must be preserved");
  static_assert(out_neg.exponent == ExpT{-7}, "exponent must be preserved");
  static_assert(out_neg.is_negative == true, "sign must reflect is_negative=true");
}

TEST(AddSignToUnsignedDecimalFpTest_328, DoesNotAlterOriginalValueObject_328) {
  using SigT = std::uint32_t;
  using ExpT = std::int32_t;

  UnsignedFp<SigT, ExpT> in{SigT{31415u}, ExpT{2718}};
  auto in_copy = in;

  (void)YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SigT, ExpT>(true, in);

  EXPECT_EQ(in.significand, in_copy.significand);
  EXPECT_EQ(in.exponent, in_copy.exponent);
}