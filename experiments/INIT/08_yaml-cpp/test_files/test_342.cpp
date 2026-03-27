// TEST_ID: 342
// File: ./TestProjects/yaml-cpp/test/report_t_no_trailing_zeros_test_342.cpp

#include <gtest/gtest.h>

#include <limits>
#include <optional>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

struct DummyFormat342 {};

// Detection helpers (only observe public interface; no assumptions about internals).
template <class T>
concept HasSignificandMember342 = requires(const T& v) { v.significand; };

template <class T>
concept HasExponentMember342 = requires(const T& v) { v.exponent; };

template <class T>
concept HasTrailingZerosMember342 = requires(const T& v) { v.trailing_zeros; };

template <class T>
concept HasHasTrailingZerosMember342 = requires(const T& v) { v.has_trailing_zeros; };

template <class T>
concept HasMayHaveTrailingZerosMember342 = requires(const T& v) { v.may_have_trailing_zeros; };

template <class T>
concept HasNoTrailingZerosMember342 = requires(const T& v) { v.no_trailing_zeros; };

template <class T>
constexpr std::optional<bool> ReadTrailingZeroFlag342(const T& v) {
  if constexpr (HasTrailingZerosMember342<T>) {
    return static_cast<bool>(v.trailing_zeros);
  } else if constexpr (HasHasTrailingZerosMember342<T>) {
    return static_cast<bool>(v.has_trailing_zeros);
  } else if constexpr (HasMayHaveTrailingZerosMember342<T>) {
    return static_cast<bool>(v.may_have_trailing_zeros);
  } else if constexpr (HasNoTrailingZerosMember342<T>) {
    // If a type exposes the inverse flag, interpret it.
    return !static_cast<bool>(v.no_trailing_zeros);
  } else {
    return std::nullopt;
  }
}

template <class T>
concept HasEquality342 = requires(const T& a, const T& b) {
  { a == b } -> std::convertible_to<bool>;
};

}  // namespace

TEST(ReportTNoTrailingZerosTest_342, IsNoexcept_342) {
  using YAML::jkj::dragonbox::policy::trailing_zero::report_t;

  static_assert(noexcept(report_t::no_trailing_zeros<DummyFormat342>(0u, 0)),
                "no_trailing_zeros should be noexcept (observable via signature).");

  // Also check runtime compilation path.
  EXPECT_TRUE((noexcept(report_t::no_trailing_zeros<DummyFormat342>(0u, 0))));
}

TEST(ReportTNoTrailingZerosTest_342, PreservesSignificandAndExponent_Runtime_342) {
  using YAML::jkj::dragonbox::policy::trailing_zero::report_t;

  const std::uint64_t significand = 123456789ULL;
  const int exponent = -37;

  const auto r = report_t::no_trailing_zeros<DummyFormat342>(significand, exponent);

  if constexpr (HasSignificandMember342<decltype(r)>) {
    EXPECT_EQ(r.significand, significand);
  }

  if constexpr (HasExponentMember342<decltype(r)>) {
    EXPECT_EQ(r.exponent, exponent);
  }

  const auto flag = ReadTrailingZeroFlag342(r);
  if (flag.has_value()) {
    EXPECT_FALSE(*flag) << "Expected the returned value to indicate 'no trailing zeros' via its public flag.";
  }
}

TEST(ReportTNoTrailingZerosTest_342, PreservesSignificandAndExponent_Constexpr_342) {
  using YAML::jkj::dragonbox::policy::trailing_zero::report_t;

  constexpr std::uint32_t significand = 42u;
  constexpr int exponent = 7;

  constexpr auto r = report_t::no_trailing_zeros<DummyFormat342>(significand, exponent);

  if constexpr (HasSignificandMember342<decltype(r)>) {
    static_assert(r.significand == significand, "significand should be preserved.");
  }
  if constexpr (HasExponentMember342<decltype(r)>) {
    static_assert(r.exponent == exponent, "exponent should be preserved.");
  }

  constexpr auto flag = ReadTrailingZeroFlag342(r);
  if constexpr (flag.has_value()) {
    static_assert(flag.value() == false, "Flag should indicate no trailing zeros.");
  }

  SUCCEED();
}

TEST(ReportTNoTrailingZerosTest_342, BoundaryValues_Runtime_342) {
  using YAML::jkj::dragonbox::policy::trailing_zero::report_t;

  using SigT = std::uint64_t;
  using ExpT = int;

  const SigT sig_min = std::numeric_limits<SigT>::min();
  const SigT sig_max = std::numeric_limits<SigT>::max();
  const ExpT exp_min = std::numeric_limits<ExpT>::min();
  const ExpT exp_max = std::numeric_limits<ExpT>::max();

  const auto r1 = report_t::no_trailing_zeros<DummyFormat342>(sig_min, exp_min);
  const auto r2 = report_t::no_trailing_zeros<DummyFormat342>(sig_max, exp_max);

  if constexpr (HasSignificandMember342<decltype(r1)>) {
    EXPECT_EQ(r1.significand, sig_min);
    EXPECT_EQ(r2.significand, sig_max);
  }
  if constexpr (HasExponentMember342<decltype(r1)>) {
    EXPECT_EQ(r1.exponent, exp_min);
    EXPECT_EQ(r2.exponent, exp_max);
  }

  const auto f1 = ReadTrailingZeroFlag342(r1);
  const auto f2 = ReadTrailingZeroFlag342(r2);
  if (f1.has_value()) EXPECT_FALSE(*f1);
  if (f2.has_value()) EXPECT_FALSE(*f2);
}

TEST(ReportTNoTrailingZerosTest_342, ReturnTypeIsUnsignedDecimalFpWithTrailingFlagEnabled_342) {
  using YAML::jkj::dragonbox::policy::trailing_zero::report_t;

  // This test only checks the *declared* return type shape via the public template name.
  // It does not assume any member layout.
  using SigT = std::uint32_t;
  using ExpT = int;

  using Expected = YAML::jkj::dragonbox::unsigned_decimal_fp<SigT, ExpT, true>;
  using Actual = decltype(report_t::no_trailing_zeros<DummyFormat342>(SigT{1}, ExpT{2}));

  static_assert(std::is_same_v<Actual, Expected>,
                "no_trailing_zeros must return unsigned_decimal_fp<Significand, Exponent, true> per its interface.");
  SUCCEED();
}

TEST(ReportTNoTrailingZerosTest_342, RepeatedCallsWithSameInputsProduceEqualObjectsWhenEqualityIsAvailable_342) {
  using YAML::jkj::dragonbox::policy::trailing_zero::report_t;

  const std::uint64_t significand = 9001ULL;
  const int exponent = 0;

  const auto a = report_t::no_trailing_zeros<DummyFormat342>(significand, exponent);
  const auto b = report_t::no_trailing_zeros<DummyFormat342>(significand, exponent);

  if constexpr (HasEquality342<decltype(a)>) {
    EXPECT_TRUE(a == b);
  } else {
    // If equality is not available publicly, we still validate observable fields when present.
    if constexpr (HasSignificandMember342<decltype(a)>) {
      EXPECT_EQ(a.significand, b.significand);
    }
    if constexpr (HasExponentMember342<decltype(a)>) {
      EXPECT_EQ(a.exponent, b.exponent);
    }
    const auto fa = ReadTrailingZeroFlag342(a);
    const auto fb = ReadTrailingZeroFlag342(b);
    if (fa.has_value() && fb.has_value()) {
      EXPECT_EQ(*fa, *fb);
    }
  }
}