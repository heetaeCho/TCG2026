// TEST_ID: 334
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "contrib/dragonbox.h"

namespace {

struct FakeSignedSignificandBits {
  bool neg{};
  constexpr bool is_negative() const noexcept { return neg; }
};

}  // namespace

namespace YAML::jkj::dragonbox::policy::sign {

TEST(ReturnSignTTest_334, HandleSign_PositiveSignPreservesMagnitude_334) {
  using U = std::uint64_t;
  using UnsignedFp = ::YAML::jkj::dragonbox::detail::unsigned_decimal_fp<U>;

  const FakeSignedSignificandBits s{false};
  const UnsignedFp r{U{12345}, -7};

  const auto out = return_sign_t::handle_sign(s, r);

  EXPECT_FALSE(out.is_negative);
  EXPECT_EQ(out.significand, r.significand);
  EXPECT_EQ(out.exponent, r.exponent);
}

TEST(ReturnSignTTest_334, HandleSign_NegativeSignSetsNegativeAndPreservesMagnitude_334) {
  using U = std::uint64_t;
  using UnsignedFp = ::YAML::jkj::dragonbox::detail::unsigned_decimal_fp<U>;

  const FakeSignedSignificandBits s{true};
  const UnsignedFp r{U{9876543210ULL}, 3};

  const auto out = return_sign_t::handle_sign(s, r);

  EXPECT_TRUE(out.is_negative);
  EXPECT_EQ(out.significand, r.significand);
  EXPECT_EQ(out.exponent, r.exponent);
}

TEST(ReturnSignTTest_334, HandleSign_ZeroSignificandBoundary_334) {
  using U = std::uint32_t;
  using UnsignedFp = ::YAML::jkj::dragonbox::detail::unsigned_decimal_fp<U>;

  const UnsignedFp r{U{0}, 0};

  const auto out_pos = return_sign_t::handle_sign(FakeSignedSignificandBits{false}, r);
  EXPECT_FALSE(out_pos.is_negative);
  EXPECT_EQ(out_pos.significand, r.significand);
  EXPECT_EQ(out_pos.exponent, r.exponent);

  const auto out_neg = return_sign_t::handle_sign(FakeSignedSignificandBits{true}, r);
  EXPECT_TRUE(out_neg.is_negative);
  EXPECT_EQ(out_neg.significand, r.significand);
  EXPECT_EQ(out_neg.exponent, r.exponent);
}

TEST(ReturnSignTTest_334, HandleSign_ExponentExtremesBoundary_334) {
  using U = std::uint64_t;
  using UnsignedFp = ::YAML::jkj::dragonbox::detail::unsigned_decimal_fp<U>;

  const UnsignedFp r_min{U{1}, (std::numeric_limits<int>::min)()};
  const UnsignedFp r_max{U{1}, (std::numeric_limits<int>::max)()};

  const auto out_min = return_sign_t::handle_sign(FakeSignedSignificandBits{true}, r_min);
  EXPECT_TRUE(out_min.is_negative);
  EXPECT_EQ(out_min.significand, r_min.significand);
  EXPECT_EQ(out_min.exponent, r_min.exponent);

  const auto out_max = return_sign_t::handle_sign(FakeSignedSignificandBits{false}, r_max);
  EXPECT_FALSE(out_max.is_negative);
  EXPECT_EQ(out_max.significand, r_max.significand);
  EXPECT_EQ(out_max.exponent, r_max.exponent);
}

TEST(ReturnSignTTest_334, HandleSign_IsNoexcept_334) {
  using U = std::uint64_t;
  using UnsignedFp = ::YAML::jkj::dragonbox::detail::unsigned_decimal_fp<U>;

  const FakeSignedSignificandBits s{false};
  const UnsignedFp r{U{42}, -1};

  static_assert(noexcept(return_sign_t::handle_sign(s, r)),
                "return_sign_t::handle_sign must be noexcept");

  EXPECT_NO_THROW({
    (void)return_sign_t::handle_sign(s, r);
  });
}

TEST(ReturnSignTTest_334, HandleSign_UsableInConstantEvaluation_334) {
  using U = std::uint64_t;
  using UnsignedFp = ::YAML::jkj::dragonbox::detail::unsigned_decimal_fp<U>;

  constexpr FakeSignedSignificandBits s{true};
  constexpr UnsignedFp r{U{3141592653ULL}, -9};

  constexpr auto out = return_sign_t::handle_sign(s, r);

  static_assert(out.is_negative, "Expected negative sign to be applied");
  static_assert(out.significand == r.significand, "Significand must be preserved");
  static_assert(out.exponent == r.exponent, "Exponent must be preserved");

  EXPECT_TRUE(out.is_negative);
  EXPECT_EQ(out.significand, r.significand);
  EXPECT_EQ(out.exponent, r.exponent);
}

}  // namespace YAML::jkj::dragonbox::policy::sign