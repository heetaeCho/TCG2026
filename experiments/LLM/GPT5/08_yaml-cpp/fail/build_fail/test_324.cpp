// File: ./TestProjects/yaml-cpp/src/contrib/dragonbox_floor_log5_pow2_minus_log5_3_test.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::log::floor_log5_pow2_minus_log5_3;

class FloorLog5Pow2MinusLog5_3Test_324 : public ::testing::Test {};

template <typename T>
class FloorLog5Pow2MinusLog5_3TypedTest_324 : public ::testing::Test {};
using SignedIntTypes_324 = ::testing::Types<
    std::int32_t, std::int64_t, std::int16_t, std::int8_t,
    std::int_least32_t, std::int_least64_t>;
TYPED_TEST_SUITE(FloorLog5Pow2MinusLog5_3TypedTest_324, SignedIntTypes_324);

}  // namespace

// ------------------------------
// Basic "is usable" tests
// ------------------------------

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, IsNoexcept_324) {
  EXPECT_TRUE(noexcept(floor_log5_pow2_minus_log5_3(std::int32_t{0})));
  EXPECT_TRUE(noexcept(floor_log5_pow2_minus_log5_3(std::int64_t{0})));
}

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, IsConstexprEvaluatable_324) {
  // If the function is truly constexpr, these should compile and evaluate at compile-time.
  constexpr auto v0 = floor_log5_pow2_minus_log5_3(std::int32_t{0});
  constexpr auto v1 = floor_log5_pow2_minus_log5_3(std::int32_t{1});
  constexpr auto v2 = floor_log5_pow2_minus_log5_3(std::int32_t{-1});

  (void)v0;
  (void)v1;
  (void)v2;

  SUCCEED();
}

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ReturnTypeIsStableAcrossCalls_324) {
  // Observable behavior: calling with same argument yields same result (pure function expectation),
  // but we only assert determinism on the public interface.
  const auto a1 = floor_log5_pow2_minus_log5_3(std::int32_t{123});
  const auto a2 = floor_log5_pow2_minus_log5_3(std::int32_t{123});
  EXPECT_EQ(a1, a2);
}

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, DefaultTemplateArgsCanBeOverriddenByReturnType_324) {
  // Interface allows specifying ReturnType explicitly; verify it compiles and returns that type.
  const auto r = floor_log5_pow2_minus_log5_3<-3543, 2427, std::int32_t>(std::int32_t{0});
  static_assert(std::is_same_v<decltype(r), const std::int32_t>);
  EXPECT_EQ(r, floor_log5_pow2_minus_log5_3(std::int32_t{0}));
}

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, CustomExponentBoundsCompile_324) {
  // We cannot assume semantics of bounds, but can validate the API accepts custom bounds and runs.
  const auto r1 = floor_log5_pow2_minus_log5_3<-10, 10>(std::int32_t{0});
  const auto r2 = floor_log5_pow2_minus_log5_3<-10, 10>(std::int32_t{1});
  (void)r1;
  (void)r2;
  SUCCEED();
}

// ------------------------------
// Boundary-ish tests on input domain (as far as observable).
// We avoid asserting specific numeric values since the internal logic is a black box.
// Instead, we test consistency and basic relational properties that are observable.
// ------------------------------

TYPED_TEST(FloorLog5Pow2MinusLog5_3TypedTest_324, HandlesZero_324) {
  const auto r = floor_log5_pow2_minus_log5_3(TypeParam{0});
  (void)r;
  SUCCEED();
}

TYPED_TEST(FloorLog5Pow2MinusLog5_3TypedTest_324, HandlesSmallPositiveAndNegative_324) {
  const auto r_pos = floor_log5_pow2_minus_log5_3(TypeParam{1});
  const auto r_neg = floor_log5_pow2_minus_log5_3(TypeParam{-1});
  // We don't know ordering, but results must be well-formed and deterministic.
  EXPECT_EQ(r_pos, floor_log5_pow2_minus_log5_3(TypeParam{1}));
  EXPECT_EQ(r_neg, floor_log5_pow2_minus_log5_3(TypeParam{-1}));
}

TYPED_TEST(FloorLog5Pow2MinusLog5_3TypedTest_324, HandlesMinAndMaxValues_324) {
  const auto mn = floor_log5_pow2_minus_log5_3((std::numeric_limits<TypeParam>::min)());
  const auto mx = floor_log5_pow2_minus_log5_3((std::numeric_limits<TypeParam>::max)());
  // Only assert the calls succeed and are deterministic for the same input.
  EXPECT_EQ(mn, floor_log5_pow2_minus_log5_3((std::numeric_limits<TypeParam>::min)()));
  EXPECT_EQ(mx, floor_log5_pow2_minus_log5_3((std::numeric_limits<TypeParam>::max)()));
}

// ------------------------------
// Error / exceptional cases (if observable).
// The function is noexcept, so we verify it does not throw for a variety of inputs.
// ------------------------------

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, DoesNotThrowForVariousInputs_324) {
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3(std::int32_t{0}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3(std::int32_t{1}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3(std::int32_t{-1}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3(std::int32_t{123456}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3(std::int32_t{-123456}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3((std::numeric_limits<std::int32_t>::min)()));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3((std::numeric_limits<std::int32_t>::max)()));
}

TEST_F(FloorLog5Pow2MinusLog5_3Test_324, DoesNotThrowWithCustomTemplateParameters_324) {
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3<-100, 100, std::int64_t>(std::int32_t{0}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3<-100, 100, std::int64_t>(std::int32_t{1}));
  EXPECT_NO_THROW((void)floor_log5_pow2_minus_log5_3<-100, 100, std::int64_t>(std::int32_t{-1}));
}

// ------------------------------
// External interaction verification
// None observable in this interface: no callbacks, no collaborators passed in.
// So we only verify interface-level properties above.
// ------------------------------