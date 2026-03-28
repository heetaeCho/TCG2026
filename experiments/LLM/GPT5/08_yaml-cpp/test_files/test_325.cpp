// TEST_ID: 325
#include <gtest/gtest.h>

#include <cstdint>

#include "contrib/dragonbox.h"

namespace {
template <int N, class UInt>
bool CallCheckDivisibilityAndDivideByPow10(UInt& n) {
  return YAML::jkj::dragonbox::detail::div::check_divisibility_and_divide_by_pow10<N>(n);
}
}  // namespace

TEST(CheckDivisibilityAndDivideByPow10Test_325, DivisibleBy10DividesAndReturnsTrue_U32_325) {
  std::uint32_t n = 20;
  const bool ok = CallCheckDivisibilityAndDivideByPow10<1>(n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 2u);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, NotDivisibleBy10DividesAndReturnsFalse_U32_325) {
  std::uint32_t n = 21;
  const bool ok = CallCheckDivisibilityAndDivideByPow10<1>(n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n, 2u);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, DivisibleBy100DividesAndReturnsTrue_U32_325) {
  std::uint32_t n = 300;
  const bool ok = CallCheckDivisibilityAndDivideByPow10<2>(n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 3u);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, NotDivisibleBy100DividesAndReturnsFalse_U32_325) {
  std::uint32_t n = 310;
  const bool ok = CallCheckDivisibilityAndDivideByPow10<2>(n);

  EXPECT_FALSE(ok);
  EXPECT_EQ(n, 3u);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, ZeroIsHandled_ReturnsTrueAndKeepsZero_U32_325) {
  std::uint32_t n = 0;
  const bool ok = CallCheckDivisibilityAndDivideByPow10<1>(n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 0u);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, UpperBoundAllowedInput_WorksAtMaxForN1_U32_325) {
  // For N=1, implementation asserts n <= 10^(N+1) == 100.
  std::uint32_t n = 100;
  const bool ok = CallCheckDivisibilityAndDivideByPow10<1>(n);

  EXPECT_TRUE(ok);
  EXPECT_EQ(n, 10u);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, WorksForU64AndHigherN_325) {
  // For N=3, implementation asserts n <= 10^(N+1) == 10000.
  std::uint64_t n1 = 9990;   // 9990 / 1000 == 9 remainder 990
  std::uint64_t n2 = 9000;   // divisible by 1000

  const bool ok1 = CallCheckDivisibilityAndDivideByPow10<3>(n1);
  const bool ok2 = CallCheckDivisibilityAndDivideByPow10<3>(n2);

  EXPECT_FALSE(ok1);
  EXPECT_EQ(n1, 9ull);

  EXPECT_TRUE(ok2);
  EXPECT_EQ(n2, 9ull);
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, ConstexprEvaluationIsPossible_325) {
  // The function is JKJ_CONSTEXPR14; verify it can be evaluated in a constant expression context.
  constexpr bool kOk = []() constexpr {
    std::uint32_t n = 20;
    const bool ok = YAML::jkj::dragonbox::detail::div::check_divisibility_and_divide_by_pow10<1>(n);
    return ok && (n == 2u);
  }();
  static_assert(kOk, "constexpr evaluation failed");

  EXPECT_TRUE(kOk);
}

#ifndef NDEBUG
TEST(CheckDivisibilityAndDivideByPow10Test_325, DiesWhenInputExceedsDocumentedPrecondition_N1_U32_325) {
  // For N=1, implementation asserts n <= 100; 101 should trip assert in debug builds.
  std::uint32_t n = 101;
  ASSERT_DEATH((void)CallCheckDivisibilityAndDivideByPow10<1>(n), ".*");
}

TEST(CheckDivisibilityAndDivideByPow10Test_325, DiesWhenInputExceedsDocumentedPrecondition_N2_U32_325) {
  // For N=2, implementation asserts n <= 1000; 1001 should trip assert in debug builds.
  std::uint32_t n = 1001;
  ASSERT_DEATH((void)CallCheckDivisibilityAndDivideByPow10<2>(n), ".*");
}
#endif