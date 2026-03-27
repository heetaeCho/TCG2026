// TEST_ID: 319
// File: dragonbox_log_compute_test_319.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <cmath>

// Include the header under test.
#include "contrib/dragonbox.h"

namespace {

class LogComputeTest_319 : public ::testing::Test {};

template <class T>
void ExpectSameFloatOrNaNOrInf(T runtime_v, T constexpr_v) {
  if (std::isnan(runtime_v)) {
    EXPECT_TRUE(std::isnan(constexpr_v));
    return;
  }
  if (std::isinf(runtime_v)) {
    EXPECT_TRUE(std::isinf(constexpr_v));
    EXPECT_EQ(std::signbit(runtime_v), std::signbit(constexpr_v));
    return;
  }
  EXPECT_EQ(runtime_v, constexpr_v);
}

}  // namespace

TEST_F(LogComputeTest_319, ReturnTypeMatchesTemplateParameter_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  static_assert(std::is_same_v<decltype(compute<int>(0)), int>);
  static_assert(std::is_same_v<decltype(compute<std::uint64_t>(0)), std::uint64_t>);
  static_assert(std::is_same_v<decltype(compute<double>(0)), double>);
}

TEST_F(LogComputeTest_319, IsNoexceptForCommonInstantiations_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  static_assert(noexcept(compute<int>(0)));
  static_assert(noexcept(compute<std::uint64_t>(0)));
  static_assert(noexcept(compute<double>(0)));

  static_assert(noexcept(compute<int>(std::int32_t{0})));
  static_assert(noexcept(compute<int>(std::int64_t{0})));
  static_assert(noexcept(compute<double>(std::uint32_t{0})));
}

TEST_F(LogComputeTest_319, ConstexprEvaluationMatchesRuntimeForIntReturn_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  constexpr int c0 = compute<int>(0);
  constexpr int c1 = compute<int>(1);
  constexpr int cneg = compute<int>(-1);

  EXPECT_EQ(compute<int>(0), c0);
  EXPECT_EQ(compute<int>(1), c1);
  EXPECT_EQ(compute<int>(-1), cneg);
}

TEST_F(LogComputeTest_319, ConstexprEvaluationMatchesRuntimeForUint64Return_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  constexpr std::uint64_t c0 = compute<std::uint64_t>(0);
  constexpr std::uint64_t c7 = compute<std::uint64_t>(7);
  constexpr std::uint64_t c42 = compute<std::uint64_t>(42);

  EXPECT_EQ(compute<std::uint64_t>(0), c0);
  EXPECT_EQ(compute<std::uint64_t>(7), c7);
  EXPECT_EQ(compute<std::uint64_t>(42), c42);
}

TEST_F(LogComputeTest_319, ConstexprEvaluationMatchesRuntimeForDoubleReturn_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  constexpr double c0 = compute<double>(0);
  constexpr double c3 = compute<double>(3);
  constexpr double cneg2 = compute<double>(-2);

  ExpectSameFloatOrNaNOrInf(compute<double>(0), c0);
  ExpectSameFloatOrNaNOrInf(compute<double>(3), c3);
  ExpectSameFloatOrNaNOrInf(compute<double>(-2), cneg2);
}

TEST_F(LogComputeTest_319, AcceptsBoundarySignedInputsWithoutFailure_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  const int imin = (std::numeric_limits<int>::min)();
  const int imax = (std::numeric_limits<int>::max)();
  const long long llmin = (std::numeric_limits<long long>::min)();
  const long long llmax = (std::numeric_limits<long long>::max)();

  // Observable behavior here: the function is callable for boundary values and returns a value.
  // (It is also noexcept by contract; these calls should not throw.)
  (void)compute<int>(imin);
  (void)compute<int>(imax);
  (void)compute<std::uint64_t>(imin);
  (void)compute<std::uint64_t>(imax);

  (void)compute<int>(llmin);
  (void)compute<int>(llmax);
  (void)compute<double>(llmin);
  (void)compute<double>(llmax);

  SUCCEED();
}

TEST_F(LogComputeTest_319, AcceptsBoundaryUnsignedInputsWithoutFailure_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  const std::uint32_t u32max = (std::numeric_limits<std::uint32_t>::max)();
  const std::uint64_t u64max = (std::numeric_limits<std::uint64_t>::max)();

  (void)compute<int>(u32max);
  (void)compute<std::uint64_t>(u32max);
  (void)compute<double>(u32max);

  (void)compute<int>(u64max);
  (void)compute<std::uint64_t>(u64max);
  (void)compute<double>(u64max);

  SUCCEED();
}

TEST_F(LogComputeTest_319, SameInputIsDeterministicAtRuntime_319) {
  using YAML::jkj::dragonbox::detail::log::compute;

  const int e = 5;

  const auto a = compute<std::uint64_t>(e);
  const auto b = compute<std::uint64_t>(e);
  EXPECT_EQ(a, b);

  const auto da = compute<double>(e);
  const auto db = compute<double>(e);
  if (std::isnan(da)) {
    EXPECT_TRUE(std::isnan(db));
  } else if (std::isinf(da)) {
    EXPECT_TRUE(std::isinf(db));
    EXPECT_EQ(std::signbit(da), std::signbit(db));
  } else {
    EXPECT_EQ(da, db);
  }
}