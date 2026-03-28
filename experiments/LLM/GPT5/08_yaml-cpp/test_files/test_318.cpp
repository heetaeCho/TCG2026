// TEST_ID: 318
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using ::YAML::jkj::dragonbox::detail::log::compute;

// These symbols are referenced by compute() itself in the provided header snippet.
// In the actual codebase they should be available in the same namespace.
using ::YAML::jkj::dragonbox::detail::log::min_exponent;
using ::YAML::jkj::dragonbox::detail::log::max_exponent;

template <class ReturnType, class Int>
constexpr ReturnType ComputeCE(Int e) noexcept {
  return compute<ReturnType, Int>(e);
}

}  // namespace

TEST(DragonboxLogComputeTest_318, IsNoexceptForCommonInstantiations_318) {
  // Verifies the "noexcept" part of the interface for a few representative instantiations.
  static_assert(noexcept(compute<int, int>(0)), "compute<int,int> must be noexcept");
  static_assert(noexcept(compute<long long, int>(0)), "compute<long long,int> must be noexcept");
  static_assert(noexcept(compute<int, long long>(0)), "compute<int,long long> must be noexcept");
}

TEST(DragonboxLogComputeTest_318, IsUsableInConstantEvaluation_318) {
  // Verifies the "constexpr" behavior by forcing compile-time evaluation.
  constexpr int kMin = static_cast<int>(min_exponent);
  constexpr int kMax = static_cast<int>(max_exponent);
  constexpr int kMid = kMin + (kMax - kMin) / 2;

  constexpr int v_min = ComputeCE<int>(kMin);
  constexpr int v_mid = ComputeCE<int>(kMid);
  constexpr int v_max = ComputeCE<int>(kMax);

  // Basic sanity: values exist and can be compared at runtime.
  EXPECT_EQ(v_min, compute<int>(kMin));
  EXPECT_EQ(v_mid, compute<int>(kMid));
  EXPECT_EQ(v_max, compute<int>(kMax));
}

TEST(DragonboxLogComputeTest_318, AcceptsBoundaryExponentsWithoutCrash_318) {
  const int kMin = static_cast<int>(min_exponent);
  const int kMax = static_cast<int>(max_exponent);

  // The primary observable behavior here is that calls succeed at boundaries.
  // Also check return type is as requested.
  (void)compute<int>(kMin);
  (void)compute<int>(kMax);
  (void)compute<long long>(kMin);
  (void)compute<long long>(kMax);

  SUCCEED();
}

TEST(DragonboxLogComputeTest_318, SameInputSameOutputForRepeatedCalls_318) {
  const int kMin = static_cast<int>(min_exponent);
  const int kMax = static_cast<int>(max_exponent);
  const int kMid = kMin + (kMax - kMin) / 2;

  const int a1 = compute<int>(kMid);
  const int a2 = compute<int>(kMid);
  EXPECT_EQ(a1, a2);

  const long long b1 = compute<long long>(kMin);
  const long long b2 = compute<long long>(kMin);
  EXPECT_EQ(b1, b2);

  const long long c1 = compute<long long>(kMax);
  const long long c2 = compute<long long>(kMax);
  EXPECT_EQ(c1, c2);
}

TEST(DragonboxLogComputeTest_318, WorksWithDifferentIntegralExponentTypes_318) {
  const int kMin = static_cast<int>(min_exponent);
  const int kMax = static_cast<int>(max_exponent);
  const int kMid = kMin + (kMax - kMin) / 2;

  const int r_int = compute<int, int>(kMid);
  const int r_ll  = compute<int, long long>(static_cast<long long>(kMid));
  EXPECT_EQ(r_int, r_ll);

  const long long r2_int = compute<long long, int>(kMin);
  const long long r2_ll  = compute<long long, long long>(static_cast<long long>(kMin));
  EXPECT_EQ(r2_int, r2_ll);

  const long long r3_int = compute<long long, int>(kMax);
  const long long r3_ll  = compute<long long, long long>(static_cast<long long>(kMax));
  EXPECT_EQ(r3_int, r3_ll);
}

#if defined(JKJ_HAS_CONSTEXPR14) && JKJ_HAS_CONSTEXPR14
// The provided snippet shows an assert guarding the exponent range when JKJ_HAS_CONSTEXPR14 is enabled.
// Only run death tests when asserts are active.
#ifndef NDEBUG
TEST(DragonboxLogComputeTest_318, DeathOnExponentBelowMinWhenAssertsEnabled_318) {
  const int kMin = static_cast<int>(min_exponent);
  ASSERT_DEATH((void)compute<int>(kMin - 1), ".*");
}

TEST(DragonboxLogComputeTest_318, DeathOnExponentAboveMaxWhenAssertsEnabled_318) {
  const int kMax = static_cast<int>(max_exponent);
  ASSERT_DEATH((void)compute<int>(kMax + 1), ".*");
}
#endif  // !NDEBUG
#endif  // JKJ_HAS_CONSTEXPR14