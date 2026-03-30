// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_plus_infinity_static_boundary_379_test.cpp

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_away_from_zero;
using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_zero;

// The policy under test (name as it appears in dragonbox.h).
using PolicyUnderTest =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::
        nearest_toward_plus_infinity_static_boundary_t;

// A minimal "SignedSignificandBits" test double: the production code only
// requires .is_negative().
struct FakeSignedSignificandBits {
  bool negative = false;
  constexpr bool is_negative() const noexcept { return negative; }
};

// A spy functor that returns different values depending on which rounding policy
// object it receives, and also incorporates arguments to verify they are passed.
struct SpyFunc {
  template <class PolicyObj, class... Args>
  constexpr int operator()(PolicyObj /*policy*/, int base, Args... args) const noexcept {
    // Distinguish which policy object was selected by delegate().
    constexpr bool kTowardZero =
        std::is_same_v<std::decay_t<PolicyObj>,
                       std::decay_t<decltype(nearest_toward_zero)>>;

    constexpr bool kAwayFromZero =
        std::is_same_v<std::decay_t<PolicyObj>,
                       std::decay_t<decltype(nearest_away_from_zero)>>;

    // Make the branch observable in the return value.
    int policy_code = kTowardZero ? 1000 : (kAwayFromZero ? 2000 : 3000);

    // Also fold in the number of extra args (observable forwarding/passing).
    int extra = static_cast<int>(sizeof...(args));
    return policy_code + base * 10 + extra;
  }
};

// Another spy that returns a different type, to validate return-type deduction.
struct BoolSpyFunc {
  template <class PolicyObj>
  constexpr bool operator()(PolicyObj /*policy*/, bool v) const noexcept {
    constexpr bool kTowardZero =
        std::is_same_v<std::decay_t<PolicyObj>,
                       std::decay_t<decltype(nearest_toward_zero)>>;
    // Flip for toward_zero to make it observable.
    return kTowardZero ? !v : v;
  }
};

class NearestTowardPlusInfinityStaticBoundaryTest_379 : public ::testing::Test {};

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379,
       NegativeSignificandDelegatesToNearestTowardZero_379) {
  FakeSignedSignificandBits s{true};

  // For negative: delegate should select nearest_toward_zero -> policy_code 1000.
  const int result = PolicyUnderTest::delegate(s, SpyFunc{}, /*base=*/7, 1, 2, 3);
  EXPECT_EQ(result, 1000 + 7 * 10 + 3);  // 3 extra args after base
}

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379,
       NonNegativeSignificandDelegatesToNearestAwayFromZero_379) {
  FakeSignedSignificandBits s{false};

  // For non-negative: delegate should select nearest_away_from_zero -> policy_code 2000.
  const int result = PolicyUnderTest::delegate(s, SpyFunc{}, /*base=*/7, 1, 2);
  EXPECT_EQ(result, 2000 + 7 * 10 + 2);
}

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379,
       ZeroLikeNonNegativeDelegatesToNearestAwayFromZero_379) {
  // Boundary-style check: "zero" is typically non-negative; our fake models that via false.
  FakeSignedSignificandBits s{/*negative=*/false};

  const int result = PolicyUnderTest::delegate(s, SpyFunc{}, /*base=*/0);
  EXPECT_EQ(result, 2000 + 0 * 10 + 0);
}

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379,
       DelegatePreservesReturnTypeFromFunc_379) {
  FakeSignedSignificandBits neg{true};
  FakeSignedSignificandBits nonneg{false};

  // Return type should be exactly what the functor returns.
  static_assert(std::is_same_v<decltype(PolicyUnderTest::delegate(neg, BoolSpyFunc{}, true)),
                               bool>);
  static_assert(std::is_same_v<decltype(PolicyUnderTest::delegate(nonneg, BoolSpyFunc{}, true)),
                               bool>);

  EXPECT_EQ(PolicyUnderTest::delegate(neg, BoolSpyFunc{}, /*v=*/true), false);     // flipped
  EXPECT_EQ(PolicyUnderTest::delegate(nonneg, BoolSpyFunc{}, /*v=*/true), true);  // unchanged
}

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379,
       DelegateIsNoexceptWhenFuncIsNoexcept_379) {
  FakeSignedSignificandBits s{true};

  // Observable error/exception case: verify the interface guarantees noexcept.
  // (If this stops being noexcept, this test will fail to compile.)
  static_assert(noexcept(PolicyUnderTest::delegate(s, SpyFunc{}, 1)));
}

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379,
       DelegateWorksInConstexprContext_379) {
  constexpr FakeSignedSignificandBits neg{true};
  constexpr FakeSignedSignificandBits nonneg{false};

  constexpr int r1 = PolicyUnderTest::delegate(neg, SpyFunc{}, /*base=*/3, 9);
  constexpr int r2 = PolicyUnderTest::delegate(nonneg, SpyFunc{}, /*base=*/3, 9, 8);

  static_assert(r1 == (1000 + 3 * 10 + 1));
  static_assert(r2 == (2000 + 3 * 10 + 2));

  EXPECT_EQ(r1, 1000 + 3 * 10 + 1);
  EXPECT_EQ(r2, 2000 + 3 * 10 + 2);
}

}  // namespace