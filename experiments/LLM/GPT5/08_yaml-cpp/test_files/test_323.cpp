// TEST_ID: 323
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "yaml-cpp/src/contrib/dragonbox.h"

namespace {
using YAML::jkj::dragonbox::detail::log::floor_log5_pow2;

template <typename T>
static std::int64_t CallAsI64(T e) {
  // Cast result through int64_t so we can compare across ReturnType defaults.
  return static_cast<std::int64_t>(floor_log5_pow2(e));
}

template <typename Ret, typename T>
static std::int64_t CallAsI64ExplicitRet(T e) {
  return static_cast<std::int64_t>(floor_log5_pow2<-1831, 1831, Ret>(e));
}

template <stdr::int_least32_t MinE, stdr::int_least32_t MaxE, typename T>
static std::int64_t CallAsI64CustomBounds(T e) {
  return static_cast<std::int64_t>(floor_log5_pow2<MinE, MaxE>(e));
}
}  // namespace

TEST(FloorLog5Pow2Test_323, IsNoexcept_323) {
  static_assert(noexcept(floor_log5_pow2(0)), "floor_log5_pow2(e) must be noexcept");
  static_assert(noexcept(floor_log5_pow2(std::int32_t{0})), "noexcept must hold for int32");
  static_assert(noexcept(floor_log5_pow2(std::int64_t{0})), "noexcept must hold for int64");
  SUCCEED();
}

TEST(FloorLog5Pow2Test_323, IsConstexprEvaluable_323) {
  // We don't assume any particular numeric value; we only verify it can be evaluated at compile time
  // and is stable for the same input.
  constexpr auto a = floor_log5_pow2(0);
  constexpr auto b = floor_log5_pow2(0);
  static_assert(a == b, "constexpr calls with the same input should be equal");
  (void)a;
  (void)b;
  SUCCEED();
}

TEST(FloorLog5Pow2Test_323, DeterministicForSameInput_323) {
  const std::int32_t e = 123;
  const auto r1 = floor_log5_pow2(e);
  const auto r2 = floor_log5_pow2(e);
  const auto r3 = floor_log5_pow2(e);
  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r2, r3);
}

TEST(FloorLog5Pow2Test_323, SameNumericResultAcrossIntArgumentTypes_323) {
  // For a fixed numeric exponent value, calling with different signed integer types should
  // yield the same numeric result (after casting).
  const int values[] = {-10, -1, 0, 1, 2, 9, 10, 123, -123};

  for (int v : values) {
    const auto r_int = CallAsI64(static_cast<int>(v));
    const auto r_i32 = CallAsI64(static_cast<std::int32_t>(v));
    const auto r_i64 = CallAsI64(static_cast<std::int64_t>(v));
    const auto r_s16 = CallAsI64(static_cast<std::int16_t>(v));

    EXPECT_EQ(r_int, r_i32) << "v=" << v;
    EXPECT_EQ(r_int, r_i64) << "v=" << v;
    EXPECT_EQ(r_int, r_s16) << "v=" << v;
  }
}

TEST(FloorLog5Pow2Test_323, SameNumericResultAcrossExplicitReturnTypes_323) {
  // We don't assert what the result *is*, only that explicitly requesting a different signed
  // ReturnType yields the same numeric value (when representable) for typical inputs.
  const int values[] = {-10, -1, 0, 1, 2, 9, 10, 123, -123};

  for (int v : values) {
    const auto r_default = static_cast<std::int64_t>(floor_log5_pow2(v));

    const auto r_i32 = CallAsI64ExplicitRet<std::int32_t>(v);
    const auto r_i64 = CallAsI64ExplicitRet<std::int64_t>(v);
    const auto r_il32 = CallAsI64ExplicitRet<std::int_least32_t>(v);

    EXPECT_EQ(r_default, r_i32) << "v=" << v;
    EXPECT_EQ(r_default, r_i64) << "v=" << v;
    EXPECT_EQ(r_default, r_il32) << "v=" << v;
  }
}

TEST(FloorLog5Pow2Test_323, WorksAtDefaultTemplateBoundaryInputs_323) {
  // Boundary conditions based on the exposed default template parameters.
  // We do not assume any particular numeric output; we only verify it is callable and stable.
  const std::int32_t mins[] = {-1831, -1830};
  const std::int32_t maxs[] = {1830, 1831};

  for (auto e : mins) {
    auto r1 = floor_log5_pow2(e);
    auto r2 = floor_log5_pow2(e);
    EXPECT_EQ(r1, r2) << "e=" << e;
  }
  for (auto e : maxs) {
    auto r1 = floor_log5_pow2(e);
    auto r2 = floor_log5_pow2(e);
    EXPECT_EQ(r1, r2) << "e=" << e;
  }
}

TEST(FloorLog5Pow2Test_323, CustomBoundsAgreeWithDefaultWithinThoseBounds_323) {
  // When the input exponent is within the custom bounds, the result should match the default
  // instantiation for the same input (observed behavior consistency across template parameters).
  const int values[] = {-10, -1, 0, 1, 2, 9, 10};

  for (int v : values) {
    const auto r_default = static_cast<std::int64_t>(floor_log5_pow2(v));
    const auto r_custom = CallAsI64CustomBounds<-10, 10>(v);
    EXPECT_EQ(r_default, r_custom) << "v=" << v;
  }
}

TEST(FloorLog5Pow2Test_323, CustomBoundsCallableOutsideBounds_NoThrow_323) {
  // "Exceptional/error cases (if observable)": since the function is noexcept and returns a value,
  // we can at least verify calls are well-formed and do not throw even when e is outside custom bounds.
  // We do not assume how out-of-range inputs are handled; we only check the call is valid and stable.
  const int values[] = {-11, 11, -100, 100};

  for (int v : values) {
    const auto r1 = floor_log5_pow2<-10, 10>(v);
    const auto r2 = floor_log5_pow2<-10, 10>(v);
    EXPECT_EQ(r1, r2) << "v=" << v;
  }
}