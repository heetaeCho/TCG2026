// File: ./TestProjects/yaml-cpp/test/dragonbox_policy_decimal_to_binary_rounding_nearest_toward_zero_t_367_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

namespace rounding =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A functor that exposes what delegate() passes as the first argument.
struct FirstArgIsNearestTag_367 {
  template <class First, class... Rest>
  constexpr bool operator()(First, Rest...) const noexcept {
    return std::is_same_v<std::decay_t<First>, rounding::nearest_toward_zero_t>;
  }
};

// A functor that returns a unique value; ignores all inputs.
// Used to verify return value propagation.
struct ReturnSentinel_367 {
  template <class... Ts>
  constexpr int operator()(Ts...) const noexcept {
    return 1234567;
  }
};

// A functor that returns the count of forwarded args excluding the first tag.
struct CountArgsAfterTag_367 {
  template <class First, class... Rest>
  constexpr std::size_t operator()(First, Rest... /*rest*/) const noexcept {
    return sizeof...(Rest);
  }
};

// A functor that returns a type-based value to ensure decltype propagation works.
struct ReturnTypeProbe_367 {
  template <class First, class T>
  constexpr auto operator()(First, T) const noexcept -> std::remove_reference_t<T> {
    return std::remove_reference_t<T>{};
  }
};

}  // namespace

TEST(DecimalToBinaryRoundingNearestTowardZeroPolicyTest_367,
     DelegatePassesNearestTowardZeroTagAsFirstArgument_367) {
  using Policy = rounding::nearest_toward_zero_t;

  // "SignedSignificandBits" parameter is intentionally unused by the policy interface;
  // we just supply something of an integral type.
  constexpr auto result = Policy::delegate(0, FirstArgIsNearestTag_367{}, 1, 2, 3);

  EXPECT_TRUE(result);
}

TEST(DecimalToBinaryRoundingNearestTowardZeroPolicyTest_367,
     DelegateReturnsValueFromFunctor_367) {
  using Policy = rounding::nearest_toward_zero_t;

  constexpr int value = Policy::delegate(42, ReturnSentinel_367{}, 9, 8, 7);
  EXPECT_EQ(value, 1234567);
}

TEST(DecimalToBinaryRoundingNearestTowardZeroPolicyTest_367,
     DelegateForwardsArgumentCountAfterTag_367) {
  using Policy = rounding::nearest_toward_zero_t;

  constexpr std::size_t n0 = Policy::delegate(0, CountArgsAfterTag_367{});
  constexpr std::size_t n1 = Policy::delegate(0, CountArgsAfterTag_367{}, 1);
  constexpr std::size_t n3 = Policy::delegate(0, CountArgsAfterTag_367{}, 1, 2, 3);

  EXPECT_EQ(n0, 0u);
  EXPECT_EQ(n1, 1u);
  EXPECT_EQ(n3, 3u);
}

TEST(DecimalToBinaryRoundingNearestTowardZeroPolicyTest_367,
     DelegatePropagatesReturnTypeExactly_367) {
  using Policy = rounding::nearest_toward_zero_t;

  // Ensure the returned type matches what the functor declares (after tag).
  using Ret = decltype(Policy::delegate(0, ReturnTypeProbe_367{}, int{}));
  static_assert(std::is_same_v<Ret, int>, "delegate() should propagate decltype of Func call");
  EXPECT_TRUE((std::is_same_v<Ret, int>));
}

TEST(DecimalToBinaryRoundingNearestTowardZeroPolicyTest_367,
     DelegateIsNoexceptWhenFunctorCallIsNoexcept_367) {
  using Policy = rounding::nearest_toward_zero_t;

  // The provided functors are noexcept; delegate() should be noexcept as declared.
  EXPECT_TRUE(noexcept(Policy::delegate(0, ReturnSentinel_367{}, 1, 2, 3)));
  EXPECT_TRUE(noexcept(Policy::delegate(0, CountArgsAfterTag_367{}, 1)));
}

TEST(DecimalToBinaryRoundingNearestTowardZeroPolicyTest_367,
     DelegateWorksWithDifferentSignedSignificandBitsTypes_367) {
  using Policy = rounding::nearest_toward_zero_t;

  // The first parameter is a template type; verify it accepts different integral types.
  constexpr int a = Policy::delegate(std::int32_t{7}, ReturnSentinel_367{}, 1);
  constexpr int b = Policy::delegate(std::int64_t{7}, ReturnSentinel_367{}, 1);

  EXPECT_EQ(a, 1234567);
  EXPECT_EQ(b, 1234567);
}