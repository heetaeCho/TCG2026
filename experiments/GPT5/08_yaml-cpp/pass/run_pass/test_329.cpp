// TEST_ID: 329
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <typename SignificandT, typename ExponentT>
using UnsignedFp = YAML::jkj::dragonbox::unsigned_decimal_fp<SignificandT, ExponentT, true>;

template <typename SignificandT, typename ExponentT>
using SignedFp = YAML::jkj::dragonbox::signed_decimal_fp<SignificandT, ExponentT, true>;

template <typename SignificandT, typename ExponentT>
static constexpr SignedFp<SignificandT, ExponentT> CallAddSign(
    bool is_negative, UnsignedFp<SignificandT, ExponentT> r) {
  return YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<SignificandT, ExponentT>(is_negative, r);
}

template <typename SignificandT, typename ExponentT>
struct Pair {
  using S = SignificandT;
  using E = ExponentT;
};

using TypePairs_329 = ::testing::Types<
    Pair<std::uint32_t, std::int32_t>,
    Pair<std::uint64_t, std::int32_t>,
    Pair<std::uint64_t, std::int64_t>>;

template <typename T>
class AddSignToUnsignedDecimalFpTypedTest_329 : public ::testing::Test {};

TYPED_TEST_SUITE(AddSignToUnsignedDecimalFpTypedTest_329, TypePairs_329);

}  // namespace

TEST(AddSignToUnsignedDecimalFpTest_329, SetsNegativeFlagTrueWhenRequested_329) {
  using S = std::uint64_t;
  using E = std::int32_t;

  UnsignedFp<S, E> in{S{123}, E{-7}, true};
  auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<S, E>(true, in);

  EXPECT_EQ(out.significand, in.significand);
  EXPECT_EQ(out.exponent, in.exponent);
  EXPECT_EQ(out.may_have_trailing_zeros, in.may_have_trailing_zeros);
  EXPECT_TRUE(out.is_negative);
}

TEST(AddSignToUnsignedDecimalFpTest_329, SetsNegativeFlagFalseWhenRequested_329) {
  using S = std::uint64_t;
  using E = std::int32_t;

  UnsignedFp<S, E> in{S{456}, E{3}, false};
  auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<S, E>(false, in);

  EXPECT_EQ(out.significand, in.significand);
  EXPECT_EQ(out.exponent, in.exponent);
  EXPECT_EQ(out.may_have_trailing_zeros, in.may_have_trailing_zeros);
  EXPECT_FALSE(out.is_negative);
}

TYPED_TEST(AddSignToUnsignedDecimalFpTypedTest_329, PreservesFieldsForVariousValues_329) {
  using S = typename TypeParam::S;
  using E = typename TypeParam::E;

  const UnsignedFp<S, E> in{
      (std::numeric_limits<S>::max)(),
      (std::numeric_limits<E>::min)(),
      true};

  const auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<S, E>(false, in);

  EXPECT_EQ(out.significand, in.significand);
  EXPECT_EQ(out.exponent, in.exponent);
  EXPECT_EQ(out.may_have_trailing_zeros, in.may_have_trailing_zeros);
  EXPECT_FALSE(out.is_negative);
}

TYPED_TEST(AddSignToUnsignedDecimalFpTypedTest_329, BoundaryZeroSignificandAndExtremeExponent_329) {
  using S = typename TypeParam::S;
  using E = typename TypeParam::E;

  const UnsignedFp<S, E> in{S{0}, (std::numeric_limits<E>::max)(), false};
  const auto out = YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<S, E>(true, in);

  EXPECT_EQ(out.significand, S{0});
  EXPECT_EQ(out.exponent, (std::numeric_limits<E>::max)());
  EXPECT_FALSE(out.may_have_trailing_zeros);
  EXPECT_TRUE(out.is_negative);
}

TEST(AddSignToUnsignedDecimalFpTest_329, IsNoexcept_329) {
  using S = std::uint64_t;
  using E = std::int32_t;

  UnsignedFp<S, E> in{S{1}, E{0}, false};
  EXPECT_TRUE((noexcept(YAML::jkj::dragonbox::add_sign_to_unsigned_decimal_fp<S, E>(false, in))));
}

TEST(AddSignToUnsignedDecimalFpTest_329, WorksInConstexprContext_329) {
  using S = std::uint32_t;
  using E = std::int32_t;

  constexpr UnsignedFp<S, E> in{S{7}, E{-2}, true};
  constexpr auto out = CallAddSign<S, E>(true, in);

  static_assert(out.significand == S{7}, "significand should be preserved");
  static_assert(out.exponent == E{-2}, "exponent should be preserved");
  static_assert(out.may_have_trailing_zeros == true, "trailing-zeros flag should be preserved");
  static_assert(out.is_negative == true, "sign should be applied");
  SUCCEED();
}