// TEST_ID: 341
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

struct DummyFormat_341 {};

using ReportT_341 = ::YAML::jkj::dragonbox::policy::trailing_zero::report_t;

// Compile-time checks (observable interface properties).
static_assert(noexcept(ReportT_341::on_trailing_zeros<DummyFormat_341>(std::uint32_t{0}, int{0})),
              "on_trailing_zeros should be noexcept");

static_assert(noexcept(ReportT_341::no_trailing_zeros<DummyFormat_341>(std::uint32_t{0}, int{0})),
              "no_trailing_zeros should be noexcept");

static_assert(std::is_same_v<
                  decltype(ReportT_341::on_trailing_zeros<DummyFormat_341>(std::uint32_t{1}, int{2})),
                  ::YAML::jkj::dragonbox::unsigned_decimal_fp<std::uint32_t, int, true>>,
              "Return type of on_trailing_zeros should match the declared unsigned_decimal_fp type");

static_assert(std::is_same_v<
                  decltype(ReportT_341::no_trailing_zeros<DummyFormat_341>(std::uint32_t{1}, int{2})),
                  ::YAML::jkj::dragonbox::unsigned_decimal_fp<std::uint32_t, int, true>>,
              "Return type of no_trailing_zeros should match the declared unsigned_decimal_fp type");

}  // namespace

TEST(ReportTrailingZeroPolicyTest_341, OnTrailingZerosPreservesInputsAndSetsFlagTrue_341) {
  const std::uint32_t significand = 123456u;
  const int exponent = -7;

  const auto fp = ReportT_341::on_trailing_zeros<DummyFormat_341>(significand, exponent);

  // Observe returned value via structured bindings (no reliance on member names).
  const auto [out_significand, out_exponent, has_trailing_zeros] = fp;

  EXPECT_EQ(out_significand, significand);
  EXPECT_EQ(out_exponent, exponent);
  EXPECT_TRUE(has_trailing_zeros);
}

TEST(ReportTrailingZeroPolicyTest_341, NoTrailingZerosPreservesInputsAndSetsFlagFalse_341) {
  const std::uint32_t significand = 42u;
  const int exponent = 0;

  const auto fp = ReportT_341::no_trailing_zeros<DummyFormat_341>(significand, exponent);

  const auto [out_significand, out_exponent, has_trailing_zeros] = fp;

  EXPECT_EQ(out_significand, significand);
  EXPECT_EQ(out_exponent, exponent);
  EXPECT_FALSE(has_trailing_zeros);
}

TEST(ReportTrailingZeroPolicyTest_341, BoundaryValuesZeroSignificandAndExtremeExponents_341) {
  {
    const auto fp = ReportT_341::on_trailing_zeros<DummyFormat_341>(std::uint64_t{0}, int{-1000});
    const auto [s, e, tz] = fp;
    EXPECT_EQ(s, 0u);
    EXPECT_EQ(e, -1000);
    EXPECT_TRUE(tz);
  }
  {
    const auto fp = ReportT_341::no_trailing_zeros<DummyFormat_341>(std::uint64_t{0}, int{1000});
    const auto [s, e, tz] = fp;
    EXPECT_EQ(s, 0u);
    EXPECT_EQ(e, 1000);
    EXPECT_FALSE(tz);
  }
}

TEST(ReportTrailingZeroPolicyTest_341, WorksWithDifferentIntegralTypes_341) {
  {
    const std::uint64_t significand = 0xFFFF'FFFF'FFFF'FFFFull;
    const std::int32_t exponent = -1;

    const auto fp = ReportT_341::on_trailing_zeros<DummyFormat_341>(significand, exponent);
    const auto [s, e, tz] = fp;

    EXPECT_EQ(s, significand);
    EXPECT_EQ(e, exponent);
    EXPECT_TRUE(tz);
  }
  {
    const std::uint16_t significand = static_cast<std::uint16_t>(65535);
    const std::int16_t exponent = static_cast<std::int16_t>(-32768);

    const auto fp = ReportT_341::no_trailing_zeros<DummyFormat_341>(significand, exponent);
    const auto [s, e, tz] = fp;

    EXPECT_EQ(s, significand);
    EXPECT_EQ(e, exponent);
    EXPECT_FALSE(tz);
  }
}

TEST(ReportTrailingZeroPolicyTest_341, IsConstexprEvaluable_341) {
  // Ensure the functions can be evaluated at compile-time (as declared constexpr).
  constexpr auto fp1 = ReportT_341::on_trailing_zeros<DummyFormat_341>(std::uint32_t{7}, int{9});
  constexpr auto fp2 = ReportT_341::no_trailing_zeros<DummyFormat_341>(std::uint32_t{7}, int{9});

  constexpr auto s1 = []() constexpr {
    const auto [s, e, tz] = fp1;
    return s;
  }();
  constexpr auto e1 = []() constexpr {
    const auto [s, e, tz] = fp1;
    return e;
  }();
  constexpr auto tz1 = []() constexpr {
    const auto [s, e, tz] = fp1;
    return tz;
  }();

  constexpr auto s2 = []() constexpr {
    const auto [s, e, tz] = fp2;
    return s;
  }();
  constexpr auto e2 = []() constexpr {
    const auto [s, e, tz] = fp2;
    return e;
  }();
  constexpr auto tz2 = []() constexpr {
    const auto [s, e, tz] = fp2;
    return tz;
  }();

  EXPECT_EQ(s1, 7u);
  EXPECT_EQ(e1, 9);
  EXPECT_TRUE(tz1);

  EXPECT_EQ(s2, 7u);
  EXPECT_EQ(e2, 9);
  EXPECT_FALSE(tz2);
}